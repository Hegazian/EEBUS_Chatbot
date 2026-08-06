/*
 *     Copyright KEO GmbH 2017 - All rights reserved!
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

#include "ShipTransportConnectionCreator.h"
#include "SimpleShipConnection.h"
#include <keo_simple_ship_transport/SimpleShipTransportConnector.h>

#include <mutex>
#include <vector>

namespace keo_simple_ship_transport
{

typedef std::vector<SimpleShipConnectionPtr> TransportConnectionListType;

class SimpleShipTransportConnector::ShipTransportConnectorImpl : public SimpleShipConnectionHandler,
                                                                 public ShipTransportConnectionCreatorHandler
{
public:
    ShipTransportConnectorImpl()
        : spineTransportConnectionHandler(nullptr)
        , simpleShipTransportConnectionHandler(nullptr)
        , shipTransportConnectionCreator(new ShipTransportConnectionCreator(this, this))
        , pShipStack(nullptr)
    {
    }

    ~ShipTransportConnectorImpl()
    {
        if (pShipStack != nullptr)
        {
            delete pShipStack;
        }
    }

    void setSpineLinkTransportConnectionHandler(keo_spine::TransportConnectionHandler* transportConnectionHandler)
    {
        std::lock_guard<std::mutex> locker(mtx);
        spineTransportConnectionHandler = transportConnectionHandler;
    }

    void setSimpleShipTransportConnectorHandler(SimpleShipTransportConnectorHandler* handler)
    {
        std::lock_guard<std::mutex> locker(mtx);
        simpleShipTransportConnectionHandler = handler;
    }

    TransportConnectionListType getConnections() const
    {
        std::lock_guard<std::mutex> locker(mtx);
        return transportConnections;
    }

private:
    virtual void onConnect(ShipTransportConnection* connection) override
    {
        SimpleShipConnectionPtr ptr = getConnection(connection);
        if (ptr && nullptr != simpleShipTransportConnectionHandler)
        {
            simpleShipTransportConnectionHandler->onConnect(ptr);
        }
    }

    virtual void onClose(
        ShipTransportConnection* connection, int status, const std::string& reason, bool dataExchangeEnabled) override
    {
        keo_spine::TransportId id;
        SimpleShipConnectionPtr ptr;
        {
            std::lock_guard<std::mutex> locker(mtx);
            TransportConnectionListType::iterator iter = transportConnections.begin();
            TransportConnectionListType::iterator iterEnd = transportConnections.end();
            for (; iter != iterEnd;)
            {
                TransportConnectionListType::iterator actIter = iter++;
                if (actIter->get() == connection)
                {
                    if (dataExchangeEnabled)
                    {
                        id = actIter->get()->getTransportId();
                    }
                    ptr = *actIter;
                    transportConnections.erase(actIter);
                }
            }
        }

        if (0 != simpleShipTransportConnectionHandler)
        {
            simpleShipTransportConnectionHandler->onClose(ptr, status, reason);
        }

        if (dataExchangeEnabled && 0 != spineTransportConnectionHandler)
        {
            spineTransportConnectionHandler->removeConnection(id);
        }
    }

    virtual void onDataExchangeEnabled(ShipTransportConnection* connection) override
    {
        SimpleShipConnectionPtr ptr = getConnection(connection);

        if (ptr)
        {
            if (nullptr != simpleShipTransportConnectionHandler)
            {
                simpleShipTransportConnectionHandler->onDataExchangeEnabled(ptr);
            }

            if (nullptr != spineTransportConnectionHandler)
            {
                spineTransportConnectionHandler->addConnection(
                    std::static_pointer_cast<keo_spine::TransportConnection>(ptr));
            }
        }
    }

    virtual unsigned short onTrustCertificate(ShipTransportConnection* connection, const std::string& ski,
        const keo_ship::X509Certificate& certificate) override
    {
        SimpleShipConnectionPtr ptr = getConnection(connection);

        if (ptr && nullptr != simpleShipTransportConnectionHandler)
        {
            return simpleShipTransportConnectionHandler->onTrustCertificate(ptr, ski, certificate);
        }

        return keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_NONE;
    }

    virtual unsigned short onValidatePin(ShipTransportConnection* connection, const std::string& pin) override
    {
        SimpleShipConnectionPtr ptr = getConnection(connection);

        if (ptr && nullptr != simpleShipTransportConnectionHandler)
        {
            return simpleShipTransportConnectionHandler->onValidatePin(ptr, pin);
        }

        return keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_NONE;
    }

    virtual void onPinRequest(ShipTransportConnection* connection) override
    {
        SimpleShipConnectionPtr ptr = getConnection(connection);

        if (ptr && nullptr != simpleShipTransportConnectionHandler)
        {
            simpleShipTransportConnectionHandler->onPinRequest(ptr);
        }
    }

    virtual void onPinRecallTimeout(ShipTransportConnection* connection) override
    {
        SimpleShipConnectionPtr ptr = getConnection(connection);

        if (ptr && nullptr != simpleShipTransportConnectionHandler)
        {
            simpleShipTransportConnectionHandler->onPinRecallTimeout(ptr);
        }
    }

    virtual void onPinWrong(ShipTransportConnection* connection) override
    {
        SimpleShipConnectionPtr ptr = getConnection(connection);

        if (ptr && nullptr != simpleShipTransportConnectionHandler)
        {
            simpleShipTransportConnectionHandler->onPinWrong(ptr);
        }
    }

    virtual void onDatagram(ShipTransportConnection* connection, const keo_datagram::Datagram& datagram) override
    {
        if (spineTransportConnectionHandler)
        {
            spineTransportConnectionHandler->onDatagram(datagram, connection->getTransportId());
        }
    }

    SimpleShipConnectionPtr getConnection(ShipTransportConnection* connection)
    {
        SimpleShipConnectionPtr ptr;

        std::lock_guard<std::mutex> locker(mtx);
        TransportConnectionListType::iterator iter = transportConnections.begin();
        TransportConnectionListType::iterator iterEnd = transportConnections.end();
        for (; iter != iterEnd;)
        {
            TransportConnectionListType::iterator actIter = iter++;
            if (actIter->get() == connection)
            {
                ptr = *actIter;
                break;
            }
        }

        return ptr;
    }

private:
    virtual void onNewShipTransportConnection(SimpleShipConnectionPtr connection) override
    {
        std::lock_guard<std::mutex> locker(mtx);
        transportConnections.push_back(connection);
    }

private:
    // Handler for connections
    keo_spine::TransportConnectionHandler* spineTransportConnectionHandler;

    SimpleShipTransportConnectorHandler* simpleShipTransportConnectionHandler;
    TransportConnectionListType transportConnections;

public:
    mutable std::mutex mtx;
    keo_ship::ShipNodeFactoryPtr shipTransportConnectionCreator;
    keo_ship::ShipStack* pShipStack;
};

SimpleShipTransportConnector::SimpleShipTransportConnector()
    : p(new ShipTransportConnectorImpl())
{
}

SimpleShipTransportConnector::~SimpleShipTransportConnector()
{
    delete p;
}

void SimpleShipTransportConnector::setSpineLinkTransportConnectionHandler(
    keo_spine::TransportConnectionHandler* transportConnectionHandler)
{
    p->setSpineLinkTransportConnectionHandler(transportConnectionHandler);
}

void SimpleShipTransportConnector::setSimpleShipTransportConnectorHandler(SimpleShipTransportConnectorHandler* handler)
{
    p->setSimpleShipTransportConnectorHandler(handler);
}

bool SimpleShipTransportConnector::connectTo(const keo_ship::Uri& uri)
{
    if (nullptr != p->pShipStack)
    {
        return p->pShipStack->connectTo(uri);
    }
    return false;
}

bool SimpleShipTransportConnector::initializeShipStack(
    const keo_ship::ShipStackConfiguration& shipStackConfiguration, keo_ship::SecurityHandlerPtr shipSecurityData)
{
    if (nullptr == p->pShipStack)
    {
        p->pShipStack
            = new keo_ship::ShipStack(shipStackConfiguration, shipSecurityData, p->shipTransportConnectionCreator);
        return p->pShipStack->initialize() == keo_ship::ShipStackResult::StackResultOk;
    }
    return false;
}

bool SimpleShipTransportConnector::startServer(
    const std::string& host, int serverPort, const std::string& websocketpath)
{
    if (nullptr != p->pShipStack)
    {
        std::list<std::string> hosts;
        hosts.push_back(host);
        p->pShipStack->initializeServer(hosts, serverPort, websocketpath);
        return p->pShipStack->startServer();
    }
    return false;
}

void SimpleShipTransportConnector::stopShip()
{
    if (nullptr != p->pShipStack)
    {
        p->pShipStack->stopServer();
        p->pShipStack->serverJoin();
        p->pShipStack->shutdown();
    }
}

bool SimpleShipTransportConnector::isConnectedBySKI(const std::string& ski) const
{
    ShipTransportConnectionWeakPtr ptr = getShipTransportConnectionBySKI(ski);
    return !ptr.expired();
}

void SimpleShipTransportConnector::closeConnectionBySKI(const std::string& ski)
{
    ShipTransportConnectionWeakPtr ptr = getShipTransportConnectionBySKI(ski);
    if (auto spt = ptr.lock())
    {
        spt->closeConnection();
    }
}

void SimpleShipTransportConnector::closeConnectionByShipId(const std::string& shipId)
{
    ShipTransportConnectionWeakPtr ptr = getShipTransportConnectionByShipId(shipId);
    if (auto spt = ptr.lock())
    {
        spt->closeConnection();
    }
}

void SimpleShipTransportConnector::closeConnectionByTransportId(const std::string& transportId)
{
    ShipTransportConnectionWeakPtr ptr = getShipTransportConnectionByTransportId(transportId);
    if (auto spt = ptr.lock())
    {
        spt->closeConnection();
    }
}

ShipTransportConnectionWeakPtr SimpleShipTransportConnector::getShipTransportConnectionBySKI(
    const std::string& ski) const
{
    ShipTransportConnectionWeakPtr ptr;
    for (auto const c : p->getConnections())
    {
        ptr = c;
        std::lock_guard<std::mutex> locker(p->mtx);
        if (auto spt = ptr.lock())
        {
            if (spt->getSki() == ski)
            {
                break;
            }
        }
    }

    return ptr;
}

ShipTransportConnectionWeakPtr SimpleShipTransportConnector::getShipTransportConnectionByShipId(
    const std::string& shipId) const
{
    ShipTransportConnectionWeakPtr ptr;
    for (auto const c : p->getConnections())
    {
        ptr = c;
        std::lock_guard<std::mutex> locker(p->mtx);
        if (auto spt = ptr.lock())
        {
            if (spt->getShipId() == shipId)
            {
                break;
            }
        }
    }

    return ptr;
}

ShipTransportConnectionWeakPtr SimpleShipTransportConnector::getShipTransportConnectionByTransportId(
    const std::string& transportId) const
{
    ShipTransportConnectionWeakPtr ptr;
    for (auto const c : p->getConnections())
    {
        ptr = c;
        std::lock_guard<std::mutex> locker(p->mtx);
        if (auto spt = ptr.lock())
        {
            if (spt->getTransportId() == transportId)
            {
                break;
            }
        }
    }

    return ptr;
}

std::list<std::string> SimpleShipTransportConnector::getSKIs() const
{
    // TODO replace with std::vector
    std::list<std::string> list;
    for (auto const& c : p->getConnections())
    {
        list.push_back(c->getSki());
    }
    return list;
}

std::list<std::string> SimpleShipTransportConnector::getShipIds() const
{
    // TODO replace with std::vector
    std::list<std::string> list;
    for (auto const& c : p->getConnections())
    {
        list.push_back(c->getShipId());
    }
    return list;
}

std::list<std::string> SimpleShipTransportConnector::getTransportIds() const
{
    // TODO replace with std::vector
    std::list<std::string> list;
    for (auto const& c : p->getConnections())
    {
        if (!c->getTransportId().empty())
        {
            list.push_back(c->getTransportId());
        }
    }
    return list;
}

} /* namespace keo_simple_ship_transport */
