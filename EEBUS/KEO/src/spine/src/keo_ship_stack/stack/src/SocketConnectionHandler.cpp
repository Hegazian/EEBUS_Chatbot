/*
 *     Copyright KEO GmbH 2016 - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright notice.
 *     This software may not be provided or otherwise made available to, or used
 *     by, any other person. No title to or ownership of the software is hereby
 *     transferred. The information contained in this document is considered the
 *     @b confidential and @b proprietary information of KEO GmbH
 *     and may not be disclosed or discussed with anyone who is not employed by
 *     KEO GmbH, unless the individual or company
 *     - has an express need to know such information, and
 *     - disclosure of information is subject to the terms of a duly
 *     executed "Confidentiality and Non-Disclosure Agreement" between
 *     KEO GmbH and the individual or company.
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "SocketConnectionHandler.h"
#include "ShipMessageExchange.h"
#include <keo_ship/ShipSecurity.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <algorithm>
#include <assert.h>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <keo_tool/KEJobRunner.h>
#include <keo_util/KELogging.h>
#include <mutex>
#include <sstream>
#include <KELogging.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_ship
{

const std::string SocketConnectionHandler::WSS_STRING("wss://");
const int SocketConnectionHandler::CLOSE_STATUS_CODE_GENERAL_ERROR = 4200;
const int SocketConnectionHandler::CLOSE_STATUS_CODE_DOUBLE_CONNECTION = 4201;
const int SocketConnectionHandler::CLOSE_STATUS_CODE_DENY_CONNECTION = 4202;

class SocketConnectionHandler::ShipStateSocket
{
public:
    enum SocketStateType
    {
        SME_ENABLED, //!> SME is active
        PENDING_DOUBLE_CONNECTION, //!> awaiting double connection handling
        DOUBLE_CONNECTION_CLOSING //!> this double connection is already closed

    };

    static const long PEER_CLOSE_TIMEOUT; // seconds
    static const long REMOTE_DOUBLE_CONNECTION_TIMEOUT; // seconds
    SocketConnectionHandler* connectionHandler;
    ShipSocket* shipSocket;
    ShipNodePtr shipNode;
    SecurityHandlerPtr securityHandler;
    ShipStackConfiguration shipStackConfiguration;
    std::string serverUri;
    SocketStateType state;

private:
    ShipTimer timer;

public:
    ShipStateSocket(SocketConnectionHandler* connectionHandler, ShipSocket* shipSocket, SocketStateType state,
        SecurityHandlerPtr securityHandler, const ShipStackConfiguration& shipStackConfiguration,
        const std::string& serverUri)

        : connectionHandler(connectionHandler)
        , shipSocket(shipSocket)
        , securityHandler(securityHandler)
        , shipStackConfiguration(shipStackConfiguration)
        , serverUri(serverUri)
        , state(state)
        , timer(std::bind(&ShipStateSocket::handleDoubleConnectionTimer, this))
    {
        assert(nullptr != shipSocket);
        /*LOG_TRACE() << "New ShipStateSocket " << (void*)this << " shipSocket " << (void*)shipSocket << " state "
                    << state;
                    */
    }
    

    ~ShipStateSocket()
    {
        timer.stop();
        if (shipNode)
        {
            shipNode->getMessageExchange()->onFinalize();
        }
        delete shipSocket;
        shipSocket = nullptr;
    }

    ShipSocket* getShipSocket() const
    {
        return shipSocket;
    }

    void onConnect(ShipNodePtr shipNode)
    {
        if (!this->shipNode)
        {
            this->shipNode = shipNode;
            this->shipNode->getMessageExchange()->onConnect(
                connectionHandler, shipSocket, securityHandler, shipStackConfiguration, serverUri);
            this->shipNode->onConnect();
        }
    }

    void onClose(int statusCode, const std::string& reason)
    {
        timer.stop();
        if (shipNode)
        {
            shipNode->getMessageExchange()->onFinalize();
            shipNode->onClose(statusCode, reason);
        }
    }

    void startDoubleConnectionTimer()
    {
        timer.start(REMOTE_DOUBLE_CONNECTION_TIMEOUT * 1000);
    }

    void stopDoubleConnectionTimer()
    {
        timer.stop();
    }

    struct ShipSocketPtrCmp
    {
        explicit ShipSocketPtrCmp(const ShipSocket* shipSocket)
            : filter(shipSocket)
        {
        }
        inline bool operator()(const ShipStateSocket* rhs) const
        {
            return (filter == rhs->shipSocket);
        }

    private:
        const ShipSocket* filter;
    };

    struct StateCmp
    {
        explicit StateCmp(const ShipStateSocket::SocketStateType state)
            : filter(state)
        {
        }
        inline bool operator()(const ShipStateSocket* rhs) const
        {
            return (filter == rhs->state);
        }

    private:
        const ShipStateSocket::SocketStateType filter;
    };

private:
    void handleDoubleConnectionTimer()
    {
        const std::string& remoteSki = shipSocket->getRemoteSki();

        std::unique_lock<std::recursive_mutex> locker(connectionHandler->mtx);

        ShipStateSocketMapType::iterator mapIter = connectionHandler->connectedPeers.find(remoteSki);
        if (mapIter != connectionHandler->connectedPeers.end())
        {
            /*LOG_TRACE() << "Peer did not handle double connection (SKI=" << remoteSki
                        << ", numStateSockets=" << mapIter->second.size()
                        << "). Old connection will now be closed and the new connection will be accepted.";
*/
            for (auto stateSocket : mapIter->second)
            {
                if (stateSocket->state != SocketStateType::PENDING_DOUBLE_CONNECTION)
                {
                    // Finally close double connection...
                    stateSocket->getShipSocket()->close(CLOSE_STATUS_CODE_DOUBLE_CONNECTION, "Double connection");
                }
                else
                {
                    // ...and accept pending connection
                    locker.unlock();
                    //LOG_TRACE() << "Starting SME on new connection (SKI=" << remoteSki << ")";
                    stateSocket->state = ShipStateSocket::SME_ENABLED;
                    ShipNodePtr shipNode = connectionHandler->shipNodeFactory->createShipNode();
                    stateSocket->onConnect(shipNode);
                    locker.lock();
                }
            }
        }
    }
};

/**
 * The time to wait when closing connections in seconds.
 */
const long SocketConnectionHandler::ShipStateSocket::PEER_CLOSE_TIMEOUT = 1;

/**
 * The time to wait before closing a double connection when the remote end should have but failed to close it.
 */
const long SocketConnectionHandler::ShipStateSocket::REMOTE_DOUBLE_CONNECTION_TIMEOUT = 3;

SocketConnectionHandler::SocketConnectionHandler(ShipStackConfiguration& shipStackConfiguration,
    SecurityHandlerPtr shipSecurityData, ShipNodeFactoryPtr shipNodeFactoryPtr)
    : mtx()
    , connectedPeers()
    , shipSecurityData(shipSecurityData)
    , serverInfo(ShipServerInfo(shipStackConfiguration,
          (shipSecurityData) ? shipSecurityData->getOwnSKI()
                             : std::string())) // FIXME using an empty string as the SKI makes no sense
    , shipNodeFactory(shipNodeFactoryPtr)
    , denyConnectionsFlag(false)
    , finalizing(false)
{
    //DEBUG_FUNC();
    jobRunner = keo_tool::KEJobRunner::start();
}

SocketConnectionHandler::~SocketConnectionHandler()
{
    //DEBUG_FUNC();
    finalize();
    delete jobRunner;
}

ShipStackResult SocketConnectionHandler::initialize()
{
    //DEBUG_FUNC();
    ShipStackResult result = ShipStackResult::StackResultOk;
    if (serverInfo.getSki().empty())
    {
        //LOG_ERROR() << "Cannot create socket connection handler! KeyStore contains empty SKI";
        result = StackResultSkiError;
    }
    else
    {
        //LOG_TRACE() << "Own SKI '" << serverInfo.getSki() << "'";
    }
    return result;
}

ShipStackResult SocketConnectionHandler::finalize()
{
    //DEBUG_FUNC();
    std::unique_lock<std::recursive_mutex> locker(mtx);
    finalizing = true;

    auto mapIter = connectedPeers.begin();
    for (; mapIter != connectedPeers.end(); ++mapIter)
    {
        std::list<ShipStateSocket*>& list = mapIter->second;
        auto listIter = list.begin();
        for (; listIter != list.end(); ++listIter)
        {
            ShipStateSocket* stateSocket = *listIter;
            if (nullptr != stateSocket)
            {
                ShipSocket* shipSocket = stateSocket->shipSocket;
                if (nullptr != shipSocket)
                {
                    // TODO rework ShipSocket/WebSocket to change/streamline close handling
                    shipSocket->close(CLOSE_STATUS_CODE_GENERAL_ERROR, "shutdown");
                }
            }
        }
    }
    if (!connectedPeers.empty())
    {
        //DEBUG_INFO() << "Finalizing! " << connectedPeers.size() << " connections open!";

        int timeoutMilliSec = 1000 * connectedPeers.size() * ShipStateSocket::PEER_CLOSE_TIMEOUT;

        if (!cv_peersClosed.wait_for(
                locker, std::chrono::milliseconds(timeoutMilliSec), [&] { return connectedPeers.empty(); }))
        {
            LOG_ERROR() << "Could not close all connections";
            ShipStateSocketMapType::iterator iter = connectedPeers.begin();
            while (iter != connectedPeers.end())
            {
                while (!iter->second.empty())
                {
                    ShipStateSocket* stateSocket = *(iter->second.begin());
                    delete stateSocket;
                    iter->second.pop_front();
                }
                iter = connectedPeers.erase(iter);
            }
        }
        else
        {
            DEBUG_INFO() << "All connections closed!";
        }
    }

    if (jobRunner->isRunning())
    {
        // if a job is still running, leave critical section.
        // otherwise the job will never finish
        locker.unlock();
        keo_tool::KEJobRunner::stop(jobRunner);
        locker.lock();
    }

    return ShipStackResult::StackResultOk;
}

bool SocketConnectionHandler::isConnected(const std::string& ski) const
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return connectedPeers.find(Ski::normalize(ski)) != connectedPeers.end();
}

const ShipServerInfo& SocketConnectionHandler::getServerInfo() const
{
    return serverInfo;
}

void SocketConnectionHandler::denyConnections(bool flag)
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    denyConnectionsFlag = flag;
}

void SocketConnectionHandler::onConnect(ShipSocket* shipSocket)
{
    if (nullptr == shipSocket)
    {
        //LOG_ERROR() << "SocketConnectionHandler onConnect(): Invalid socket !";
        return;
    }

    std::lock_guard<std::recursive_mutex> locker(mtx);

    class OnConnectJob : public keo_tool::KEJobRunnerJob
    {
        SocketConnectionHandler& connectionHandler;
        ShipSocket* shipSocket;

    public:
        OnConnectJob(SocketConnectionHandler& connectionHandler, ShipSocket* shipSocket)
            : connectionHandler(connectionHandler)
            , shipSocket(shipSocket)
        {
        }
        virtual void run()
        {
            std::lock_guard<std::recursive_mutex> locker(connectionHandler.mtx);

            DEBUG_INFO() << "Socket connection handler onConnect() " << shipSocket->getDisplayName();

            const std::string& remoteSki = shipSocket->getRemoteSki();

            if (connectionHandler.serverInfo.getSki() == remoteSki)
            {
                // State SKI_ERR_CLOSING
                LOG_WARN() << "Connection with SKI '" << remoteSki << "' equals own SKI '"
                           << connectionHandler.serverInfo.getSki() << "'. Connection denied.";
                shipSocket->close(CLOSE_STATUS_CODE_GENERAL_ERROR, "Wrong SKI");
                return;
            }

            ShipStateSocketMapType::iterator mapIter = connectionHandler.connectedPeers.find(remoteSki);
            bool skiIsKnown = mapIter != connectionHandler.connectedPeers.end();
            std::list<ShipStateSocket*>& list
                = skiIsKnown ? mapIter->second : connectionHandler.connectedPeers[remoteSki];
            if (skiIsKnown)
            {
                // State DOUBLE_CONNECTION
                if (std::find_if(list.begin(), list.end(), ShipStateSocket::ShipSocketPtrCmp(shipSocket)) != list.end())
                {
                    LOG_WARN() << "Ignoring connection (already connected)";
                    return;
                }

                int cmpResult = Ski::compare(connectionHandler.serverInfo.getSki(), remoteSki);
                if (cmpResult > 0)
                {
                    // State: DOUBLE_CONNECTION_CLOSING
                    LOG_TRACE() << "SKI " << remoteSki << " is already connected. Closing...";

                    bool waitForConnectionToBeClosed = false;

                    // Close the old connection...
                    for (auto existingShipSocket : list)
                    {
                        if (existingShipSocket->getShipSocket()->isClosing())
                        {
                            // The connection is already marked as closing. This means that closing it again here,
                            // calling close here again, will return right away. In that case the new connection must
                            // not be transferred to state SME_ENABLED, but only when the connection is fully closed.
                            // When the connection is not already marked as closing, calling close here will block until
                            // the connection is fully closed. In which case the new connection can be transferred to
                            // state SME_ENABLED right away.
                            waitForConnectionToBeClosed = true;
                        }
                        existingShipSocket->getShipSocket()->close(
                            CLOSE_STATUS_CODE_DOUBLE_CONNECTION, "Double connection");
                    }

                    ShipStateSocket* stateSocket = new ShipStateSocket(&connectionHandler, shipSocket,
                        waitForConnectionToBeClosed ? ShipStateSocket::PENDING_DOUBLE_CONNECTION
                                                     : ShipStateSocket::SME_ENABLED,
                        connectionHandler.shipSecurityData, connectionHandler.serverInfo.getShipStackConfiguration(),
                        connectionHandler.getServerUri(shipSocket));
                    list.push_back(stateSocket);

                    if (waitForConnectionToBeClosed)
                    {
                        // Mark new connection as pending. It will be transferred to state SME_ENABLED in the OnCloseJob
                        // of the old/double connection.
                        LOG_TRACE() << "Double connection has already been marked closing from another context. New "
                                    << "connection with SKI '" << remoteSki
                                    << "' will be marked as pending until the double connection is fully closed.";
                    }
                    else
                    {
                        // Accept the new connection right away
                        LOG_TRACE() << "New Connection with SKI '" << remoteSki << "'. Starting SME";

                        ShipNodePtr shipNode = connectionHandler.shipNodeFactory->createShipNode();
                        stateSocket->onConnect(shipNode);
                    }
                }
                else
                {
                    // This node has detected a double connection, but has a smaller SKI than the remote end.
                    // Start double connection timer on old connection (to wait for it to be closed by the remote
                    // end)...
                    for (auto existingShipSocket : list)
                    {
                        existingShipSocket->startDoubleConnectionTimer();
                    }

                    // ... and keep the new connection in state PENDING_DOUBLE_CONNECTION
                    LOG_TRACE() << "Connection with SKI " << remoteSki
                                << " already connected. Expecting peer to handle double connection.";
                    ShipStateSocket* stateSocket = new ShipStateSocket(&connectionHandler, shipSocket,
                        ShipStateSocket::PENDING_DOUBLE_CONNECTION, connectionHandler.shipSecurityData,
                        connectionHandler.serverInfo.getShipStackConfiguration(),
                        connectionHandler.getServerUri(shipSocket));
                    list.push_back(stateSocket);
                }
            }
            else
            {
                // Connection is not already connected
                if (connectionHandler.denyConnectionsFlag && shipSocket->getRole() == ShipSocket::ROLE_SERVER)
                {
                    shipSocket->close(CLOSE_STATUS_CODE_DENY_CONNECTION, "Connections are currently denied.");
                    return;
                }

                // State: SME_READY

                LOG_TRACE() << "New Connection with SKI '" << remoteSki << "'. Starting SME";

                ShipStateSocket* stateSocket
                    = new ShipStateSocket(&connectionHandler, shipSocket, ShipStateSocket::SME_ENABLED,
                        connectionHandler.shipSecurityData, connectionHandler.serverInfo.getShipStackConfiguration(),
                        connectionHandler.getServerUri(shipSocket));
                ShipNodePtr shipNode = connectionHandler.shipNodeFactory->createShipNode();
                list.push_back(stateSocket);

                stateSocket->onConnect(shipNode);
            }
        }
    };

    if (finalizing)
    {
        //LOG_WARN() << "Incoming connection in state finalizing!";
    }
    else
    {
        auto job = new OnConnectJob(*this, shipSocket);
        if (jobRunner->addJob(job) != 0)
        {
            //LOG_ERROR() << "SocketConnectionHandler could not schedule job";
            delete job;
        }
    }
}

void SocketConnectionHandler::onClose(ShipSocket* shipSocket, int statusCode, const std::string& reason)
{
    if (nullptr == shipSocket)
    {
       //LOG_ERROR() << "SocketConnectionHandler onClose(): Invalid socket !";
        return;
    }

    std::lock_guard<std::recursive_mutex> locker(mtx);

    if (finalizing)
    {
        //DEBUG_INFO() << "onClose() finalizing, number of remaining connections: " << connectedPeers.size();
    }

    class OnCloseJob : public keo_tool::KEJobRunnerJob
    {
        SocketConnectionHandler& connectionHandler;
        ShipSocket* shipSocket;
        int statusCode;
        std::string reason;

    public:
        OnCloseJob(SocketConnectionHandler& connectionHandler, ShipSocket* shipSocket, int statusCode,
            const std::string& reason)
            : connectionHandler(connectionHandler)
            , shipSocket(shipSocket)
            , statusCode(statusCode)
            , reason(reason)
        {
        }

        virtual void run()
        {
            std::unique_lock<std::recursive_mutex> locker(connectionHandler.mtx);

            const std::string& remoteSki = shipSocket->getRemoteSki();

            ShipStateSocketMapType::iterator mapIter = connectionHandler.connectedPeers.find(remoteSki);
            bool skiIsKnown = mapIter != connectionHandler.connectedPeers.end();

            /*LOG_TRACE() << shipSocket->getDisplayName() << ":Connection with SKI '" << remoteSki << "' closed."
                        << " Status code " << std::dec << statusCode << ", reason '" << reason << "'"
                        << " (connection is " << (skiIsKnown ? "known)" : "unknown)");
                        */

            if (skiIsKnown)
            {
                std::list<ShipStateSocket*>& list = mapIter->second;
                auto stateSocketPos
                    = std::find_if(list.begin(), list.end(), ShipStateSocket::ShipSocketPtrCmp(shipSocket));

                if (stateSocketPos != list.end())
                {
                    ShipStateSocket* stateSocket = *stateSocketPos;
                    assert(stateSocket && shipSocket == stateSocket->getShipSocket());

                    stateSocket->stopDoubleConnectionTimer();

                    LOG_TRACE() << "Socket state " << stateSocket->state;

                    // remove from connected peers
                    list.erase(stateSocketPos);
                    if (list.empty())
                    {
                        connectionHandler.connectedPeers.erase(mapIter);
                    }
                    else
                    {
                        LOG_TRACE() << "Double connection " << remoteSki << " closed";

                        auto iter = list.begin();

                        while (iter != list.end())
                        {
                            ShipStateSocket* nextStateSocket = *iter;

                            switch (nextStateSocket->state)
                            {
                                case ShipStateSocket::SME_ENABLED:
                                {
                                    LOG_TRACE() << "Remaining connection for " << remoteSki << " already enabled!";
                                    iter = list.end();
                                    break;
                                }

                                case ShipStateSocket::DOUBLE_CONNECTION_CLOSING:
                                {
                                    LOG_TRACE() << "Remaining connection for " << remoteSki << " in state closing!";
                                    iter++;
                                    break;
                                }

                                case ShipStateSocket::PENDING_DOUBLE_CONNECTION:
                                {
                                    LOG_TRACE() << "Create new ShipNode and enable SME for " << remoteSki;
                                    nextStateSocket->stopDoubleConnectionTimer();
                                    ShipNodePtr shipNode = connectionHandler.shipNodeFactory->createShipNode();
                                    nextStateSocket->state = ShipStateSocket::SME_ENABLED;
                                    nextStateSocket->onConnect(shipNode);
                                    iter = list.end();
                                    break;
                                }
                            }
                        }
                    }

                    // unblock finalize() when all peers are disconnected
                    if (connectionHandler.finalizing && connectionHandler.connectedPeers.empty())
                    {
                        // this will release the timeout in finalize()
                        // JobRunner::stop() will wait to finish this job afterwards
                        connectionHandler.cv_peersClosed.notify_all();
                    }

                    locker.unlock();
                    stateSocket->onClose(statusCode, reason);
                    locker.lock();
                    delete stateSocket;
                }
            }
            else
            {
                //LOG_WARN() << "Unexpected Connection with SKI '" << remoteSki << "' closed. "
                           << " Code " << std::dec << statusCode << ", reason '" << reason << "'";
                delete shipSocket;
                shipSocket = nullptr;
            }
        }
    };

    auto job = new OnCloseJob(*this, shipSocket, statusCode, reason);
    if (jobRunner->addJob(job) != 0)
    {
        //LOG_ERROR() << "SocketConnectionHandler could not schedule job";
        delete job;
    }
}

void SocketConnectionHandler::onConnectionConfirmed(ShipSocket* shipSocket, const std::string& id)
{
    //DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);

    if (nullptr == shipSocket)
    {
        //LOG_ERROR() << ": Invalid shipSocket id '" << id << "'";
        return;
    }

    //DEBUG_INFO() << "Socket connection handler onConnectionConfirmed() " << shipSocket->getDisplayName();

    const std::string remoteSki = shipSocket->getRemoteSki();
    //LOG_TRACE() << shipSocket->getDisplayName() << ": Confirm connection ID '" << id << "' SKI '" << remoteSki << "'";

    // get all connections for this ski
    auto mapIter = connectedPeers.find(remoteSki);
    if (mapIter != connectedPeers.end())
    {
        std::list<ShipStateSocket*>& list = mapIter->second;
        // get state socket for this ShipSocket
        auto pos = std::find_if(list.begin(), list.end(), ShipStateSocket::ShipSocketPtrCmp(shipSocket));
        if (pos != list.end())
        {
            ShipStateSocket* stateSocket = *pos;
            stateSocket->stopDoubleConnectionTimer();
            stateSocket->state = ShipStateSocket::SME_ENABLED;
            stateSocket->shipSocket->setDisplayName(id);
        }
        // else: The ShipSocket is already closed. See SocketConnectionHandler::onClose
    }
    else
    {
        LOG_ERROR() << "Unknown SKI '" << remoteSki << "'! Cannot establish connection";
        shipSocket->close(CLOSE_STATUS_CODE_GENERAL_ERROR, "Unknown SKI!");
    }
}

void SocketConnectionHandler::onTimeout(ShipSocket* shipSocket)
{
    //DEBUG_FUNC();

    if (nullptr != shipSocket)
    {
        std::lock_guard<std::recursive_mutex> locker(mtx);
        auto mapIter = connectedPeers.find(shipSocket->getRemoteSki());
        if (mapIter != connectedPeers.end())
        {
            std::list<ShipStateSocket*>& list = mapIter->second;
            auto stateSocketPos = std::find_if(list.begin(), list.end(), ShipStateSocket::ShipSocketPtrCmp(shipSocket));

            if (stateSocketPos != list.end())
            {
                (*stateSocketPos)->state = ShipStateSocket::DOUBLE_CONNECTION_CLOSING;
            }
        }

        //LOG_WARNING() << shipSocket->getDisplayName() << ": Timeout SKI '" << shipSocket->getRemoteSki() << "'";
        shipSocket->close(CLOSE_STATUS_CODE_GENERAL_ERROR, "timeout");
    }
    else
    {
        //LOG_ERROR() << ": Invalid socket";
    }
}

std::string SocketConnectionHandler::getServerUri(ShipSocket* socket)
{
    if (nullptr != socket)
    {
        if (socket->getRole() == ShipSocket::ROLE_SERVER)
        {
            std::ostringstream serverUri;
            serverUri << WSS_STRING << socket->getIP() << ":" << std::dec << serverInfo.getServerPort()
                      << serverInfo.getSocketPath();

            //LOG_INFO() << "ServerUri '" << serverUri.str() << "'";
            return serverUri.str();
        }
        const std::list<std::string>& hosts = serverInfo.getHosts();
        if (hosts.empty())
        {
            return std::string();
        }
        std::ostringstream serverUri;
        if (hosts.size() == 1)
        {
            serverUri << WSS_STRING << hosts.front() << ":" << std::dec << serverInfo.getServerPort()
                      << serverInfo.getSocketPath();
        }
        else
        {
            // TODO compare IPV6/V4 to select fitting IPv4/v6 interface
            serverUri << WSS_STRING << hosts.front() << ":" << std::dec << serverInfo.getServerPort()
                      << serverInfo.getSocketPath();
        }
        //LOG_INFO() << "ServerUri '" << serverUri.str() << "'";
        return serverUri.str();
    }
    else
    {
        //LOG_ERROR() << "Cannot get server URI from invalid socket.";
    }
    return std::string();
}

} /* namespace keo_ship */
