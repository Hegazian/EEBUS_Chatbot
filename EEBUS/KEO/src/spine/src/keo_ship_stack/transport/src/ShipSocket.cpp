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
#include "ShipSocket.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <assert.h>
#include <iomanip>
#include <keo_tool/KEJobRunner.h>
#include <keo_util/KELogging.h>
#include <stddef.h>
#include <vector>

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

const long ShipSocket::PING_TIMEOUT = (50 * 1000);
const long ShipSocket::PONG_EXPIRED_TIMEOUT = (10 * 1000);
const int ShipSocket::CLOSE_STATUS_CODE_GENERAL_ERROR = 4100;
const int ShipSocket::CLOSE_STATUS_CODE_CLOSED_BY_PEER = 4101;
const int ShipSocket::CLOSE_STATUS_CODE_PING_EXPIRED = 4102;

std::string vectorToHexString(const std::vector<char>& data)
{
    std::stringstream retVal;
    for (auto i : data)
    {
        retVal << std::hex << std::setfill('0') << std::setw(2) << (int)i << " ";
    }
    return retVal.str();
}

ShipSocket::ShipSocket(ShipSocketConnectionStatusListener* statusListener,
    SocketRole role)
    : mtx()
    , // non recursive
    jobRunner(NULL)
    , wsListener(*this)
    , secureConnection(nullptr)
    , timerMtx()
    , statusListener(statusListener)
    , messageListener(NULL)
    , message()
    , remoteSki()
    , remoteCertificate()
    , role(role)
    , closing(false)
    , displayName()
    , acceptMessages(0, 0)
    , websocket(&wsListener)
{
    DEBUG_FUNC();
}

ShipSocket::~ShipSocket()
{
    DEBUG_FUNC();
    timerMtx.lock();
    timerMtx.unlock();
    finalize();

    if (nullptr != secureConnection)
    {
        delete secureConnection;
        secureConnection = nullptr;
    }
}

void ShipSocket::finalize()
{
    mtx.lock();
    if (NULL != jobRunner)
    {
        keo_tool::KEJobRunner::stop(jobRunner);
        delete jobRunner;
        jobRunner = NULL;
    }
    websocket.finalize();
    mtx.unlock();
}

void ShipSocket::setShipSocketMessageListener(ShipSocketMessageListener* listener)
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    this->messageListener = listener;
    if (NULL != listener)
    {
        LOG_TRACE() << displayName << " accepting Messages";
        acceptMessages.post();
    }
}

bool ShipSocket::initialize()
{
    DEBUG_FUNC();
    bool success = websocket.initialize();
    if (success)
    {
        mtx.lock();
        jobRunner = keo_tool::KEJobRunner::start();
        success = NULL != jobRunner;
        mtx.unlock();
    }
    return success;
}

ShipSocket::SocketRole ShipSocket::getRole() const
{
    return role;
}

std::string ShipSocket::getRemoteSki() const
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return remoteSki;
}

std::string ShipSocket::getIP() const
{
    return websocket.getPeerIp();
}

int ShipSocket::getPort() const
{
    return websocket.getPeerPort();
}

std::string ShipSocket::getDisplayName() const
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return displayName;
}

keo_ship::X509Certificate ShipSocket::getRemoteCertificate() const
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return secureConnection->getPeerCertificate();
}

bool ShipSocket::openClient(OpenSSLConnection* secureConnection, const Uri& destinationURI)
{
    DEBUG_FUNC();

    this->secureConnection = secureConnection;
    if (setSKI(secureConnection->getPeerCertificate().getSki()))
    {
        {
            std::lock_guard<std::recursive_mutex> locker(mtx);
            DEBUG_INFO() << "Opening client websocket";
            if (websocket.openClient(secureConnection, destinationURI))
            {
                wsListener.startPingTimer();
                statusListener->onConnect(this);
                return true;
            }
        }

        secureConnection->close();
        return false;
    }
    else
    {
        LOG_WARN() << "Invalid Certificate!";
    }
    return false;
}

bool ShipSocket::openServer(OpenSSLConnection* secureConnection)
{
    DEBUG_FUNC();

    this->secureConnection = secureConnection;

    if (setSKI(secureConnection->getPeerCertificate().getSki()))
    {
        {
            std::lock_guard<std::recursive_mutex> locker(mtx);
            LOG_INFO() << "Opening server websocket";
            if (websocket.openServer(secureConnection))
            {
                wsListener.startPingTimer();
                statusListener->onConnect(this);
                return true;
            }
        }

        secureConnection->close();
        return false;
    }
    else
    {
        LOG_WARN() << "Invalid Certificate!";
    }
    return false;
}

void ShipSocket::close(int statusCode, const std::string& reason)
{
    DEBUG_FUNC();
    if (!isClosing())
    {
        setClosing();
        LOG_TRACE() << getDisplayName() << " Close connection. status " << std::dec << " reason " << reason;
        acceptMessages.post();
        websocket.close(statusCode, reason);
    }
}

bool ShipSocket::isClosing()
{
    return closing;
}

void ShipSocket::setClosing()
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    closing = true;
}

bool ShipSocket::sendMessage(const std::vector<char>& payload)
{
    bool success = false;
    if (!isClosing())
    {
        success = websocket.send(WebSocketHandler::OpcodeBinary, payload);
        if (!success)
        {
            LOG_ERROR() << getDisplayName() << " Sending failed - retry not close";
            //close(CLOSE_STATUS_CODE_GENERAL_ERROR, "websocket send error.");
        }
    }
    else
    {
        LOG_ERROR() << getDisplayName() << " Send message failed! Socket already closed.";
    }
    if (success)
    {
        wsListener.startPingTimer();
    }

    return success;
}

/* ****************************************************************************** *
 *  Private part                                                                  *
 * ****************************************************************************** */

ShipSocketMessageListener* ShipSocket::getShipSocketMessageListener() const
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return messageListener;
}

ShipSocketConnectionStatusListener* ShipSocket::getShipSocketConnectionStatusListener() const
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return statusListener;
}

keo_tool::KEJobRunner* ShipSocket::getJobRunner() const
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return jobRunner;
}

void ShipSocket::setDisplayName(const std::string& displayName)
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    this->displayName = displayName;
}

bool ShipSocket::setSKI(const std::string& remoteSKI)
{
    std::lock_guard<std::recursive_mutex> locker(mtx);

    if (!remoteSKI.empty())
    {
        LOG_INFO() << "Received valid certificate for SKI " << remoteSKI;

        this->remoteSki = remoteSKI;
        setDisplayName(remoteSKI);
        return true;
    }
    else
    {
        // TODO see X509Certificate for the "compute SKI" reminder
        LOG_ERROR() << "Received valid certificate, but it contains no SKI.";
    }

    return false;
}

ShipSocket::WebSocketListener::WebSocketListener(ShipSocket& parent)
    : parent(parent)
    , pingTimer(std::bind(&ShipSocket::WebSocketListener::onPingTimeout, this))
    , pongExpiredTimer(std::bind(&ShipSocket::WebSocketListener::onPongExpiredTimeout, this))
{
}

ShipSocket::WebSocketListener::~WebSocketListener()
{
    pingTimer.stop();
    pongExpiredTimer.stop();
}

void ShipSocket::WebSocketListener::onPongExpiredTimeout()
{
    parent.timerMtx.lock();
    pingTimer.stop();
    pongExpiredTimer.stop();
    parent.timerMtx.unlock();

    LOG_WARNING() << parent.displayName << " Pong expired, closing connection";
    parent.close(CLOSE_STATUS_CODE_PING_EXPIRED, "Pong response time expired");
}

void ShipSocket::WebSocketListener::startPingTimer()
{
    pingTimer.start(PING_TIMEOUT);
}

void ShipSocket::WebSocketListener::onPingTimeout()
{
    LOG_TRACE() << parent.getDisplayName() << " Send ping";

    if (!parent.isClosing())
    {
        parent.timerMtx.lock();
        pingTimer.stop();
        pongExpiredTimer.start(PONG_EXPIRED_TIMEOUT);
        parent.timerMtx.unlock();

        parent.websocket.send(WebSocketHandler::OpcodePing, std::vector<char>());
    }
    else
    {
        parent.timerMtx.lock();
        pingTimer.stop();
        pongExpiredTimer.stop();
        parent.timerMtx.unlock();

        LOG_WARNING() << parent.displayName << " Send ping failed! Socket already closed.";
    }
}

void ShipSocket::WebSocketListener::onClose(WebSocket* client, unsigned short statusCode, const std::string& reason)
{
    std::lock_guard<std::recursive_mutex> locker(parent.mtx);

    DEBUG_FUNC();
    ShipSocketConnectionStatusListener* statusListener = parent.getShipSocketConnectionStatusListener();
    assert(NULL != statusListener);
    if (NULL != statusListener)
    {
        (void)client;
        assert(client == &parent.websocket);

        LOG_INFO() << parent.displayName << " Closing socket. Status: " << statusCode << ". Reason: " << reason;

        parent.setClosing();

        parent.timerMtx.lock();
        pingTimer.stop();
        pongExpiredTimer.stop();
        parent.timerMtx.unlock();

        class CloseJob : public keo_tool::KEJobRunnerJob
        {
            ShipSocket& parent;
            ShipSocketConnectionStatusListener* statusListener;
            unsigned short statusCode;
            std::string reason;

        public:
            CloseJob(ShipSocket& parent, ShipSocketConnectionStatusListener* statusListener, unsigned short statusCode,
                const std::string& reason)
                : parent(parent)
                , statusListener(statusListener)
                , statusCode(statusCode)
                , reason(reason)
            {
            }

            void run() override
            {
                statusListener->onClose(&parent, statusCode, reason);
            }
        };

        parent.getJobRunner()->addJob(new CloseJob(parent, statusListener, statusCode, reason));
    }
}

void ShipSocket::WebSocketListener::onMessage(
    WebSocket* client, WebSocketHandler::Opcode opcode, const std::vector<char>& data, size_t dataSize, bool bFinal)
{
    DEBUG_FUNC();

    assert(client == &parent.websocket);

    if (!parent.isClosing())
    {
        switch (opcode)
        {
            case WebSocketHandler::OpcodePing: // ==> send WebSocket::OpcodePong to client
            {
                LOG_TRACE() << parent.displayName << " Ping received";

                parent.timerMtx.lock();
                pingTimer.start(PING_TIMEOUT);
                parent.timerMtx.unlock();

                if (!parent.isClosing())
                {
                    LOG_TRACE() << parent.displayName << " send Pong";
                    if (!client->send(WebSocketHandler::OpcodePong, data))
                    {
                        LOG_ERROR() << parent.displayName << " Send pong failed!.";
                    }
                }
                else
                {
                    LOG_ERROR() << parent.displayName << " Send pong failed! Socket already closed.";
                }
                break;
            }
            case WebSocketHandler::OpcodePong: // ==> reset timeout
            {
                LOG_TRACE() << parent.displayName << " Pong received";

                parent.timerMtx.lock();
                pongExpiredTimer.stop();
                pingTimer.start(PING_TIMEOUT);
                parent.timerMtx.unlock();
                break;
            }
            case WebSocketHandler::OpcodeText: // ==> not valid for SHIP
            {
                LOG_WARNING() << "Unexpected wss opcode " << std::dec << opcode << " received. Closing connection";
                parent.close(CLOSE_STATUS_CODE_GENERAL_ERROR, "invalid opcode");
                break;
            }
            case WebSocketHandler::OpcodeContinuation: // continuation frame received
            // fall through
            case WebSocketHandler::OpcodeBinary: // binary frame received
            {
                LOG_VERBOSE(2) << parent.displayName
                               << (((WebSocketHandler::Opcode)opcode == WebSocketHandler::OpcodeBinary)
                                          ? " Binary "
                                          : " Continuation ")
                               << ((bFinal) ? "frame" : "chunk") << " received: " << vectorToHexString(data);
                if (receivedMessages.empty())
                {
                    receivedMessages.push_back(std::vector<char>());
                }

                parent.timerMtx.lock();
                pingTimer.start(PING_TIMEOUT);
                parent.timerMtx.unlock();

                std::vector<char>& messageChunks = receivedMessages.back();
                messageChunks.insert(messageChunks.end(), data.begin(), data.begin() + dataSize);
                if (bFinal)
                {
                    receivedMessages.push_back(std::vector<char>());
                    // ToDo ensure
                    parent.acceptMessages.wait();
                    parent.acceptMessages.post();
                    if (!parent.isClosing())
                    {
                        class MessageJob : public keo_tool::KEJobRunnerJob
                        {
                            ShipSocketMessageListener* listener;
                            const std::vector<char> message;

                        public:
                            MessageJob(ShipSocketMessageListener* listener, const std::vector<char>& message)
                                : listener(listener)
                                , message(message)
                            {
                                DEBUG_FUNC() << (void*)this;
                            }
                            virtual void run()
                            {
                                DEBUG_FUNC() << (void*)this;
                                listener->onShipMessage(message);
                            };
                        };

                        ShipSocketMessageListener* messageListener = parent.getShipSocketMessageListener();
                        keo_tool::KEJobRunner* jobRunner = parent.getJobRunner();

                        if (NULL != messageListener && NULL != jobRunner)
                        {
                            // Note: Last element in receivedMessages contains not finalized message chunk's
                            while (receivedMessages.size() > 1)
                            {
                                MessageJob* job = new MessageJob(messageListener, receivedMessages.front());
                                receivedMessages.erase(receivedMessages.begin());

                                int jobResult = jobRunner->addJob(job);
                                if (0 != jobResult)
                                {
                                    delete job;
                                    LOG_ERROR() << parent.displayName << ": Cannot add job at onMessage() result "
                                                << std::dec << jobResult;
                                }
                            }
                            return;
                        }
                    }
                }
                break;
            }
            case WebSocketHandler::OpcodeClose:
            {
                LOG_INFO() << parent.displayName << " Connection close indication by peer. Closing connection!";

                parent.close(CLOSE_STATUS_CODE_CLOSED_BY_PEER, "Connection closed by peer.");

                break;
            }
            default: // ==> not valid for SHIP
            {
                LOG_WARNING() << "Unexpected wss opcode " << std::dec << opcode << " received. Closing connection";
                parent.close(CLOSE_STATUS_CODE_GENERAL_ERROR, "invalid opcode");
            }
        }
    }
    else
    {
        LOG_INFO() << parent.displayName << " Socket in state closing. Discard message.";
    }
}

} /* namespace keo_ship */
