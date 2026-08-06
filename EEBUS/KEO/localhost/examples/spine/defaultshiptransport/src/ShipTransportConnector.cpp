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
/**
 *     @brief      ShipControl class definition
 *
 *     @par        Module description
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "ShipConnectionHandler.h"
#include "ShipConnectionImplementation.h"

#include <keo_ship/ShipSecurity.h>
#include <keo_ship_discovery/ShipDiscovery.h>

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <mutex>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_default_ship_transport
{

class ShipTransportConnector::ShipTransportConnectorPriv : public ShipControlInterface,
                                                           public keo_ship_discovery::ShipDiscoveryInterface
{
public:
    ShipTransportConnectorPriv(ShipTransportConnector* shipControl, ShipTransportConfigurationPtr shipConfiguration)
        : parent(shipControl)
        , flagIsAutoAccept(false)
        , autoAcceptHandler(*this)
        , autoAcceptTimer(&autoAcceptHandler)
        , flagIsAutoConnect(false)
        , connectionCountClient(0)
        , connectionCountServer(0)
        , connectionCountMax(0)
        , shipDiscoveryListener(0)
        , shipDiscovery(nullptr)
        , shipSecurityHandler()
        , configuration(shipConfiguration)
        , shipStack(nullptr)
        , domain("local")
        , wssPath("/ship/")
        , pShipTransportConnectionHandler(nullptr)
    {
    }

    virtual ~ShipTransportConnectorPriv()
    {
        if (shipStack != nullptr)
        {
            delete shipStack;
            shipStack = nullptr;
        }
        if (shipDiscovery != nullptr)
        {
            delete shipDiscovery;
            shipDiscovery = nullptr;
        }
        if (pShipTransportConnectionHandler != nullptr)
        {
            delete pShipTransportConnectionHandler;
            pShipTransportConnectionHandler = nullptr;
        }
    }

    bool shouldDelegateToDiscoveryListener() const
    {
        return shipDiscovery != nullptr && shipDiscovery->isServiceResolverStarted()
            && shipDiscoveryListener != nullptr;
    }

    void setDiscoveryListener(ShipDiscoveryListener* listener)
    {
        shipDiscoveryListener = listener;
    }

    void setAutoAccept(time_t duration)
    {
        autoAcceptTimer.stop();
        if (duration > 0)
        {
            autoAcceptTimer.start(duration * 1000);
            flagIsAutoAccept = true;
            if (shipDiscovery != nullptr)
            {
                shipDiscovery->setTxtRecordRegister(true);
            }
        }
        else
        {
            flagIsAutoAccept = false;
            if (shipDiscovery != nullptr)
            {
                shipDiscovery->setTxtRecordRegister(false);
            }
        }
    }

    void onConnect(ShipConnection* node)
    {
        if (!node->isClient())
        {
            connectionCountServer++;
        }
        else
        {
            connectionCountClient++;
        }

        if (connectionCountMax > 0 && (connectionCountServer + connectionCountClient) > connectionCountMax)
        {
            LOG_INFO() << "Too many connections - close connection";
            node->closeConnection();
        }

        if (connectionCountMax > 0
            && (connectionCountServer + connectionCountClient == connectionCountMax
                   || connectionCountServer == connectionCountMax - 1))
        {
            if (parent->shouldBlockServerConnections())
            {
                LOG_INFO() << "Too many connections - blocking server connections";
                if (shipDiscovery != nullptr)
                {
                    shipDiscovery->unregisterService();
                }
                shipStack->setRejectConnections(true);
            }
        }

        parent->onConnect(node);
    }

    void onClose(ShipConnection* node, int status, const std::string& reason, bool dataExchangeEnabled)
    {
        if (node->isClient())
        {
            connectionCountClient--;
            if (connectionCountMax == 1)
            {
                if (parent->shouldActivateServerConnections())
                {
                    LOG_TRACE() << "Reactivate server connections";
                    shipStack->setRejectConnections(false);
                    if (shipDiscovery != nullptr)
                    {
                        shipDiscovery->setServiceInstanceLabel(configuration->getInstanceName());
                        shipDiscovery->setTxtRecordRegister(true);
                        shipDiscovery->registerService(configuration->getShipId(), wssPath, shipStack->getSki(),
                            configuration->getSHIPHostAddress(), configuration->getSHIPHostPort());
                    }
                }
            }
        }
        else
        {
            connectionCountServer--;
        }

        if (dataExchangeEnabled)
        {
            LOG_INFO() << "Ship connection " << node->getId() << " disconnected. Reason: " << reason;
        }
        else
        {
            LOG_INFO() << "Ship connection disconnected. Data exchange not active. Closing reason: " << reason;
        }

        parent->onClose(node, status, reason);
        pShipTransportConnectionHandler->removeConnection(node, dataExchangeEnabled);
    }

    virtual void onDataExchangeEnabled(ShipConnection* node)
    {
        pShipTransportConnectionHandler->onDataExchangeEnabled(node);
        parent->onDataExchangeEnabled(node);
    }

    virtual unsigned short onTrustCertificate(
        ShipConnection* node, const std::string& ski, const keo_ship::X509Certificate& certificate)
    {
        return parent->onTrustCertificate(node, ski, certificate);
    }

    virtual unsigned short onValidatePin(ShipConnection* node, const std::string& pin)
    {
        return parent->onValidatePin(node, pin);
    }

    virtual void onPinRequest(ShipConnection* node)
    {
        parent->onPinRequest(node);
    }

    virtual void onPinRecallTimeout(ShipConnection* node)
    {
        parent->onPinRecallTimeout(node);
    }

    virtual void onPinWrong(ShipConnection* node)
    {
        parent->onPinWrong(node);
    }

    void onServiceAdded(const keo_ship_discovery::ShipService& service)
    {
        DEBUG_INFO() << "++++++++++++++++++++++++++++++++";
        DEBUG_INFO() << "Service added or modified";
        dump(service);
        DEBUG_INFO() << "Register   : " << (service.isRegister() ? "true" : "false");
        DEBUG_INFO() << "================================";

        if (shouldDelegateToDiscoveryListener())
        {
            // In any case notify the registered listener.
            shipDiscoveryListener->serviceAdded(service);
        }

        if (parent->isAutoConnect() && keo_ship::Ski::compare(service.getSki(), shipStack->getSki()) != 0)
        {
            // User has explicitly enabled some internal logic to automatically connect
            // to the remote SHIP node.
            if (!isConnected(service))
            {
                keo_ship::Uri serviceUri(service.getURI());
                if (hasValidCertificate(service))
                {
                    // The certificate is valid, however there is no check concerning any
                    // trust level value!
                    LOG_INFO() << "Connect to the remote SHIP node (SKI=" << service.getSki()
                               << ", ID=" << service.getIdentifier() << "), because certificate is known.";
                    shipStack->connectTo(serviceUri);
                }
                else
                {
                    if (parent->isAutoAccept())
                    {
                        LOG_INFO() << "Connect to the remote SHIP node (SKI=" << service.getSki()
                                   << ", ID=" << service.getIdentifier() << "), because of active auto accept mode.";
                        shipStack->connectTo(serviceUri);
                    }
                }
            }
            else
            {
                LOG_INFO() << "Remote SHIP node (SKI=" << service.getSki() << ", ID=" << service.getIdentifier()
                           << ") is already connected.";
            }
        }
    }

    void onServiceRemoved(const keo_ship_discovery::ShipService& service)
    {
        DEBUG_INFO() << "--------------------------------";
        DEBUG_INFO() << "Service removed";
        dump(service);
        DEBUG_INFO() << "================================";

        if (shouldDelegateToDiscoveryListener())
        {
            shipDiscoveryListener->serviceRemoved(service);
        }
    }

    void onOwnServiceRegistered(const keo_ship_discovery::ShipService& service)
    {
        DEBUG_INFO() << "--------------------------------";
        DEBUG_INFO() << "Own service registered";
        dump(service);
        DEBUG_INFO() << "================================";

        if (shouldDelegateToDiscoveryListener())
        {
            shipDiscoveryListener->ownServiceRegistered(service);
        }
    }

    void onOwnServiceRemoved(const keo_ship_discovery::ShipService& service)
    {
        DEBUG_INFO() << "--------------------------------";
        DEBUG_INFO() << "Own service removed";
        dump(service);
        DEBUG_INFO() << "================================";

        if (shouldDelegateToDiscoveryListener())
        {
            shipDiscoveryListener->ownServiceRemoved(service);
        }
    }

    bool isConnected(const keo_ship_discovery::ShipService& service) const
    {
        return shipStack->isConnected(service.getSki());
    }

    bool hasValidCertificate(const keo_ship_discovery::ShipService& service) const
    {
        if (shipSecurityHandler)
        {
            keo_ship::X509Certificate certificate
                = shipSecurityHandler->getCertificate(service.getIdentifier(), service.getSki());
            return certificate.isValid();
        }
        LOG_ERROR() << "Access to trust management failed!";
        return false;
    }

    /**
     * Timeout handler for auto accept
     */
    class AutoAcceptExpiredTimerHandler : public keo_util::TimerHandlerInterface
    {
        ShipTransportConnector::ShipTransportConnectorPriv& parent;

    public:
        AutoAcceptExpiredTimerHandler(ShipTransportConnector::ShipTransportConnectorPriv& parent)
            : parent(parent)
        {
        }

    protected:
        virtual void handleTimer(keo_util::Timer::id_t timerId)
        {
            (void)timerId;
            parent.setAutoAccept(0);
        }
    };

    /**
     * Helper function for logging
     *
     * @param service
     *            ShipService
     */
    static void dump(const keo_ship_discovery::ShipService& service)
    {
        DEBUG_INFO() << "Identifier : " << service.getIdentifier();
        DEBUG_INFO() << "SKI        : " << service.getSki();
        DEBUG_INFO() << "Hostname   : " << service.getHostname();
        DEBUG_INFO() << "Port       : " << service.getPort();
        DEBUG_INFO() << "Path       : " << service.getPath();
        DEBUG_INFO() << "Brand      : " << service.getBrand();
        DEBUG_INFO() << "Model      : " << service.getModel();
        DEBUG_INFO() << "Type       : " << service.getType();
    }

    ShipTransportConnector* parent;

    // Flag for auto accept an untrusted node (push button mode)
    bool flagIsAutoAccept;

    AutoAcceptExpiredTimerHandler autoAcceptHandler;
    // Timer for auto accept
    keo_util::Timer autoAcceptTimer;
    // Flag for auto connect trusted nodes
    bool flagIsAutoConnect;
    // Counter for all connected client connections
    int connectionCountClient;
    // Counter for all connected server connections
    int connectionCountServer;
    // Maximum connection counter
    int connectionCountMax;
    // Callback for an application
    ShipDiscoveryListener* shipDiscoveryListener;
    // ShipDiscovery
    keo_ship_discovery::ShipDiscovery* shipDiscovery;
    // Security Handler
    keo_ship::SecurityHandlerPtr shipSecurityHandler;
    // Driver for the SHIP stack
    // keo_ship::ShipDriver* shipDriver;
    // SHIP configuration
    ShipTransportConfigurationPtr configuration;
    // SHIP stack
    keo_ship::ShipStack* shipStack;
    // Domain
    std::string domain;
    // WSS Path
    std::string wssPath;

    // ShipTransportConnectionHandler tansportConnectionHandler;

    /**
     * The creator for SHIP connection. Each {@link ShipConnection} is handled
     * in the {@link ShipConnectionHandler}
     */
    ShipConnectionHandler* pShipTransportConnectionHandler;
};

ShipTransportConnector::ShipTransportConnector(ShipTransportConfigurationPtr shipConfiguration)
    : p(new ShipTransportConnectorPriv(this, shipConfiguration))
{
    if (!shipConfiguration)
    {
        LOG_ERROR() << "Error in initializing ShipControl";
    }
}

ShipTransportConnector::~ShipTransportConnector()
{
    delete p;
}

bool ShipTransportConnector::initializeShip(
    const std::string& instanceName, keo_ship::SecurityHandlerPtr securityHandler, keo_spine::SpineLinkPtr pSpineLink)

{
    bool isInitialized = false;

    if (securityHandler)
    {
        p->pShipTransportConnectionHandler = new ShipConnectionHandler(pSpineLink->getConnectionHandler(), p);
        p->shipSecurityHandler = securityHandler;
        p->configuration->setInstanceName(instanceName);
        p->shipStack = new keo_ship::ShipStack(p->configuration->getShipConfiguration(), p->shipSecurityHandler,
            p->pShipTransportConnectionHandler->getShipNodeFactory());
        keo_ship::ShipStackResult result = p->shipStack->initialize();
        if (result == keo_ship::ShipStackResult::StackResultOk)
        {
            isInitialized = true;
        }
    }
    else
    {
        LOG_ERROR() << "Invalid security handler. Cannot initialize SHIP.";
    }

    if (!isInitialized)
    {
        LOG_ERROR() << "Error initializing SHIP stack in ShipTransportConnector";
    }

    return isInitialized;
}

void ShipTransportConnector::setDiscoveryListener(ShipDiscoveryListener* listener)
{
    p->setDiscoveryListener(listener);
}

bool ShipTransportConnector::startServer()
{
    bool success = false;
    DEBUG_INFO() << "Start SHIP server...";
    if (p->shipStack != nullptr)
    {
        std::list<std::string> serverHosts;

        std::string s = p->configuration->getSHIPHostAddress();

        // Split comma-separated list of hosts
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(",")) != std::string::npos)
        {
            token = s.substr(0, pos);
            serverHosts.push_back(token);
            s.erase(0, pos + 1);
        }
        serverHosts.push_back(s);

        p->shipStack->initializeServer(serverHosts, p->configuration->getSHIPHostPort(), p->wssPath);
        success = p->shipStack->startServer();
    }

    return success;
}

bool ShipTransportConnector::startDiscovery(bool registerFlag)
{
    bool success = false;
    DEBUG_INFO() << "Start SHIP discovery...";
    if (nullptr == p->shipDiscovery)
    {
        std::string serviceType("_");
        const char* serviceTypeFromEnvironment = getenv("SHIP_WS_PROTOCOL");
        if (serviceTypeFromEnvironment != nullptr)
        {
            serviceType += serviceTypeFromEnvironment;
        }
        else
        {
            serviceType += "ship";
        }
        serviceType += "._tcp";

        p->shipDiscovery = new keo_ship_discovery::ShipDiscovery(serviceType, p->domain, p);
        p->shipDiscovery->setTxtRecordBrand(p->configuration->getBrand());
        p->shipDiscovery->setTxtRecordModel(p->configuration->getModel());
        p->shipDiscovery->setTxtRecordType(p->configuration->getType());
        p->shipDiscovery->setTxtRecordRegister(registerFlag);
        p->shipDiscovery->setServiceInstanceLabel(p->configuration->getInstanceName());

        p->shipDiscovery->registerService(p->configuration->getShipId(), p->wssPath, p->shipStack->getSki(),
            p->configuration->getSHIPHostAddress(), p->configuration->getSHIPHostPort());
        p->shipDiscovery->startServiceResolver();
        success = (p->shipDiscovery->isServiceRegistered() && p->shipDiscovery->isServiceResolverStarted());
    }
    return success;
}

void ShipTransportConnector::stopServer()
{
    if (p->shipStack != nullptr)
    {
        p->shipStack->stopServer();
        p->shipStack->serverJoin();
    }
}

void ShipTransportConnector::stopDiscovery()
{
    if (p->shipDiscovery != nullptr)
    {
        p->shipDiscovery->unregisterService();
        p->shipDiscovery->stopServiceResolver();
    }
}

bool ShipTransportConnector::connectToShip(const keo_ship::Uri& uri)
{
    bool success = false;
    if (p->shipStack != nullptr)
    {
        success = p->shipStack->connectTo(uri);
    }
    return success;
}

void ShipTransportConnector::closeConnection(std::string id)
{
    p->pShipTransportConnectionHandler->closeConnection(id);
}

void ShipTransportConnector::closeConnections()
{
    p->pShipTransportConnectionHandler->closeConnections();
}

void ShipTransportConnector::setAutoAccept(time_t duration)
{
    p->setAutoAccept(duration);
}

bool ShipTransportConnector::isAutoAccept() const
{
    return isRegister() && p->flagIsAutoAccept;
}

void ShipTransportConnector::setAutoConnect(bool on)
{
    p->flagIsAutoConnect = on;
}

bool ShipTransportConnector::isAutoConnect() const
{
    return p->flagIsAutoConnect;
}

bool ShipTransportConnector::isRegister() const
{
    bool registerFlag = false;
    if (p->shipDiscovery != nullptr)
    {
        registerFlag = p->shipDiscovery->getTxtRecordRegister();
    }
    return registerFlag;
}

std::vector<keo_ship_discovery::ShipService> ShipTransportConnector::getDiscoveredServices() const
{
    std::vector<keo_ship_discovery::ShipService> result;
    if (p->shipDiscovery)
    {
        for (auto const& service : p->shipDiscovery->getDiscoveredServiceList())
        {
            result.push_back(service);
        }
    }
    return result;
}

int ShipTransportConnector::getMaximumConnections() const
{
    return p->connectionCountMax;
}

bool ShipTransportConnector::isConnected(const keo_ship_discovery::ShipService& service) const
{
    bool connected = false;
    if (p->shipStack != nullptr)
    {
        connected = p->shipStack->isConnected(service.getSki());
    }
    return connected;
}

bool ShipTransportConnector::hasValidCertificate(const keo_ship_discovery::ShipService& service) const
{
    return p->hasValidCertificate(service);
}

void ShipTransportConnector::setMaximumConnections(int maximumConnections)
{
    p->connectionCountMax = maximumConnections;
}

bool ShipTransportConnector::shouldBlockServerConnections() const
{
    return false;
}

bool ShipTransportConnector::shouldActivateServerConnections() const
{
    return true;
}

unsigned short ShipTransportConnector::onValidatePin(ShipConnection* node, const std::string& pin)
{
    (void)node;
    (void)pin;
    return keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_NONE;
}

void ShipTransportConnector::onPinRequest(ShipConnection* node)
{
    (void)node;
}

void ShipTransportConnector::onPinRecallTimeout(ShipConnection* node)
{
    (void)node;
}

void ShipTransportConnector::onPinWrong(ShipConnection* node)
{
    (void)node;
}

} /* namespace keo_default_ship_transport */
