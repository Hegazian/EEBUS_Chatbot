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

#include "AutoConnectTrustAllShipConnectorHandler.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_json_security_handler/JsonSecurityHandler.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

#define REGISTER_TIMEOUT (2 * 60 * 1000)

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine_example_client
{

/**
 * Helper function for logging
 *
 * @param service
 *            ShipService
 */
void dump(const keo_ship_discovery::ShipService& service)
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

AutoConnectTrustAllShipConnectorHandler::AutoConnectTrustAllShipConnectorHandler(
    const AppConfiguration& config, keo_spine::SpineLinkPtr spineLink)
    : config(config)
    , shipSecurityHandler(std::make_shared<keo_json_security_handler::JsonSecurityHandler>())
    , shipDiscovery("_ship._tcp", "local", this)
    , timer(this)
    , registerTimerId(0)
{
    shipConnector.setSimpleShipTransportConnectorHandler(this);
    shipConnector.setSpineLinkTransportConnectionHandler(spineLink->getConnectionHandler());
}

AutoConnectTrustAllShipConnectorHandler::~AutoConnectTrustAllShipConnectorHandler()
{
    stop();
}

bool AutoConnectTrustAllShipConnectorHandler::initialize()
{
    DEBUG_FUNC();

    if (config.getShipId().empty() || config.getSpineDevice().empty())
    {
        return false;
    }

    if (!shipSecurityHandler->init(config.getCertificateFullFilename(), config.getPrivateKeyFullFilename(),
            config.getTruststoreFullFilename()))
    {
        LOG_ERROR()
            << "AutoConnectTrustAllShipConnectorHandler::initialize() failed! Cannot initialize SHIP security handler!";
        return false;
    }

    if (!shipConnector.initializeShipStack(config.getShipConfiguration(), shipSecurityHandler))
    {
        LOG_ERROR() << "AutoConnectTrustAllShipConnectorHandler::initialize(): Cannot initialize SHIP stack!";
        return false;
    }

    return true;
}

bool AutoConnectTrustAllShipConnectorHandler::start()
{
    if (shipConnector.startServer(config.getSHIPHostAddress(), config.getSHIPHostPort()))
    {
        shipDiscovery.setTxtRecordBrand(config.getBrand());
        shipDiscovery.setTxtRecordModel(config.getModel());
        shipDiscovery.setTxtRecordType(config.getType());
        shipDiscovery.setTxtRecordRegister(true);
        shipDiscovery.setServiceInstanceLabel(config.getInstanceName());

        LOG_TRACE() << "Register own service: " << config.getShipId();
        shipDiscovery.registerService(
            config.getShipId(), "/ship/", shipSecurityHandler->getOwnSKI(), config.getSHIPHostPort());

        LOG_TRACE() << "Start service resolver..";
        shipDiscovery.startServiceResolver();
        registerTimerId = timer.start(REGISTER_TIMEOUT);
        return true;
    }

    LOG_ERROR() << "Cannot start server!";
    return false;
}

void AutoConnectTrustAllShipConnectorHandler::stop()
{
    shipConnector.stopShip();
    shipDiscovery.unregisterService();
    shipDiscovery.stopServiceResolver();
}

void AutoConnectTrustAllShipConnectorHandler::setRegisterFlag(bool registerFlag)
{
    shipDiscovery.setTxtRecordRegister(registerFlag);
    if (shipDiscovery.isServiceRegistered() && true == registerFlag)
    {
        registerTimerId = timer.start(REGISTER_TIMEOUT);
    }
}

void AutoConnectTrustAllShipConnectorHandler::closeConnection(std::string id)
{
    shipConnector.closeConnectionByTransportId(id);
}

unsigned short AutoConnectTrustAllShipConnectorHandler::onTrustCertificate(
    keo_simple_ship_transport::ShipTransportConnectionWeakPtr connection, const std::string& ski,
    const keo_ship::X509Certificate& certificate)
{
    (void)connection;
    (void)certificate;
    LOG_INFO() << "Trust certificate with ski " << ski;
    // Everyone is trusted
    return keo_ship::TrustLevel::TRUST_VALUE_USER_AUTO_ACCEPT;
}

void AutoConnectTrustAllShipConnectorHandler::onPinRequest(
    keo_simple_ship_transport::ShipTransportConnectionWeakPtr connection)
{
    if (auto spt = connection.lock())
    {
        LOG_INFO() << "Peer ask for a pin - requirement is "
                   << (spt->getPinRequirement() == keo_ship::PinRequirement::PIN_OPTIONAL ? "\"optional\""
                                                                                          : "\"required\"");
        spt->setPin("AFFE1234");
    }
}

void AutoConnectTrustAllShipConnectorHandler::onServiceAdded(const keo_ship_discovery::ShipService& service)
{
    DEBUG_INFO() << "++++++++++++++++++++++++++++++++";
    DEBUG_INFO() << "Service added or modified";
    dump(service);
    DEBUG_INFO() << "Register   : " << (service.isRegister() ? "true" : "false");
    DEBUG_INFO() << "================================";

    if (!shipConnector.isConnectedBySKI(service.getSki()))
    {
        // Connect if register flag is set or the peer is trusted
        if (service.isRegister()
            || keo_ship::TrustLevel::TRUST_VALUE_USER_UNTRUSTED
                != shipSecurityHandler->getTrustLevel(service.getIdentifier(), service.getSki()).getUserTrust())
        {
            LOG_INFO() << "Connect to " << service.getURI();
            shipConnector.connectTo(keo_ship::Uri(service.getURI()));
        }
    }
    else
    {
        DEBUG_INFO() << "Device " << service.getInstanceName() << " already connected!";
    }
}

void AutoConnectTrustAllShipConnectorHandler::onServiceRemoved(const keo_ship_discovery::ShipService& service)
{
    DEBUG_INFO() << "--------------------------------";
    DEBUG_INFO() << "Service removed";
    dump(service);
    DEBUG_INFO() << "================================";
}

void AutoConnectTrustAllShipConnectorHandler::onOwnServiceRegistered(const keo_ship_discovery::ShipService& service)
{
    DEBUG_INFO() << "--------------------------------";
    DEBUG_INFO() << "Own service registered";
    dump(service);
    DEBUG_INFO() << "================================";
}

void AutoConnectTrustAllShipConnectorHandler::onOwnServiceRemoved(const keo_ship_discovery::ShipService&)
{
    DEBUG_INFO() << "ShipDiscovery Own service removed";
}

void AutoConnectTrustAllShipConnectorHandler::handleTimer(keo_util::Timer::id_t timerId)
{
    if (timerId == registerTimerId)
    {
        // reset register flag of mDNS to false
        // Note: connections are still available as long as the SHIP server is running
        shipDiscovery.setTxtRecordRegister(false);
    }
}

} // namespace keo_spine_example_client
