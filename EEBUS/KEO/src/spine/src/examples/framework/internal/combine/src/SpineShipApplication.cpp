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

#include "SpineShipApplication.h"

#include <keo_util/KELogging.h>

#include <functional>
#include <memory>
#include <random>

namespace keo_spine_combine_app
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

SpineShipApplication::SpineShipApplication()
    : shipSecurityHandler(new keo_json_security_handler::JsonSecurityHandler())
    , shipDiscovery("_ship._tcp", "local", this)
    , publishShipService(false)
    , shipPort(0)
    , registerFlag(false)
    , ignoreRegisterFlag(false)
    , startShipServer(true)
    , measurementServer(false)
    , modifyDDTimeoutInSec(0)
    , disconnectTimeoutInSec(0)
    , timer(this)
    , modifyDDTimerId(0)
    , disconnectTimerId(0)
{
    shipConnector.setSimpleShipTransportConnectorHandler(this);
    shipConnector.setSpineLinkTransportConnectionHandler(spineLink.getConnectionHandler());
}

SpineShipApplication::~SpineShipApplication()
{
}

bool SpineShipApplication::start(const std::string& certificateFullFilename, const std::string& privateKeyFullFilename,
    const std::string& truststoreFullFilename)
{
    LOG_TRACE() << "SpineShipApplication::start()";

    if (shipId.empty() || deviceName.empty())
    {
        return false;
    }

    if (measurementServer)
    {
        device = SpineMeasurement::createSmartDeviceMeasurementServer(deviceName, this);
    }
    else
    {
        device = SpineMeasurement::createSmartDeviceMeasurementClient(deviceName, this);
    }

    spineLink.setMainDevice(device);

    if (!shipSecurityHandler->init(certificateFullFilename, privateKeyFullFilename, truststoreFullFilename))
    {
        LOG_ERROR() << "SpineShipApplication::start() failed! Cannot initialize SHIP security handler!";
        return false;
    }

    keo_ship::ShipStackConfiguration shipStackConfiguration;
    shipStackConfiguration.setShipId(shipId);
    shipStackConfiguration.setPinRequirement(keo_ship::PinRequirement::PIN_NONE);
    // shipStackConfiguration.setPin()

    if (shipConnector.initializeShipStack(shipStackConfiguration, shipSecurityHandler))
    {
        bool retval = false;

        if (startShipServer)
        {
            if (0 == shipPort)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1024, 65535);

                while (!retval)
                {
                    shipPort = dis(gen);
                    retval = shipConnector.startServer("0.0.0.0", shipPort);
                }
            }
            else
            {
                retval = shipConnector.startServer("0.0.0.0", shipPort);
            }

            LOG_TRACE() << "SHIP Server started on port " << shipPort;
        }
        else
        {
            retval = true;
        }

        if (retval)
        {
            shipDiscovery.setTxtRecordBrand(brand);
            shipDiscovery.setTxtRecordModel(model);
            shipDiscovery.setTxtRecordType(type);
            shipDiscovery.setTxtRecordRegister(registerFlag);
            shipDiscovery.setServiceInstanceLabel(instanceLabel);

            if (publishShipService)
            {
                LOG_TRACE() << "Register own service: " << shipStackConfiguration.getShipId();
                shipDiscovery.registerService(
                    shipStackConfiguration.getShipId(), "/ship/", shipSecurityHandler->getOwnSKI(), shipPort);
            }

            LOG_TRACE() << "Start service resolver..";
            shipDiscovery.startServiceResolver();

            if (0 != modifyDDTimeoutInSec)
            {
                modifyDDTimerId = timer.start(modifyDDTimeoutInSec * 1000);
            }

            if (0 != disconnectTimeoutInSec)
            {
                disconnectTimerId = timer.start(disconnectTimeoutInSec * 1000, disconnectTimeoutInSec * 1000);
            }

            return true;
        }
        else
        {
            LOG_ERROR() << "SpineShipApplication::start() failed! Cannot start SHIP server!";
        }
    }
    else
    {
        LOG_ERROR() << "SpineShipApplication::start() failed! Cannot initialize SHIP stack!";
    }
    return false;
}

void SpineShipApplication::stop()
{
    shipConnector.stopShip();
}

unsigned short SpineShipApplication::onTrustCertificate(
    keo_simple_ship_transport::ShipTransportConnectionWeakPtr connection, const std::string& ski,
    const keo_ship::X509Certificate& certificate)
{
    (void)connection;
    (void)certificate;
    LOG_INFO() << "Trust certificate with ski " << ski;
    // Everyone is trusted
    return keo_ship::TrustLevel::TRUST_VALUE_USER_AUTO_ACCEPT;
}

void SpineShipApplication::onPinRequest(keo_simple_ship_transport::ShipTransportConnectionWeakPtr connection)
{
    if (auto spt = connection.lock())
    {
        LOG_INFO() << "Peer ask for a pin - requirement is "
                   << (spt->getPinRequirement() == keo_ship::PinRequirement::PIN_OPTIONAL ? "\"optional\""
                                                                                          : "\"required\"");
        spt->setPin("AFFE1234");
    }
}

void SpineShipApplication::onServiceAdded(const keo_ship_discovery::ShipService& service)
{
    DEBUG_INFO() << "++++++++++++++++++++++++++++++++";
    DEBUG_INFO() << "Service added or modified";
    dump(service);
    DEBUG_INFO() << "Register   : " << (service.isRegister() ? "true" : "false");
    DEBUG_INFO() << "================================";

    if (!shipConnector.isConnectedBySKI(service.getSki()))
    {
        if (ignoreRegisterFlag || service.isRegister())
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

void SpineShipApplication::onServiceRemoved(const keo_ship_discovery::ShipService& service)
{
    DEBUG_INFO() << "--------------------------------";
    DEBUG_INFO() << "Service removed";
    dump(service);
    DEBUG_INFO() << "================================";
}

void SpineShipApplication::onOwnServiceRegistered(const keo_ship_discovery::ShipService& service)
{
    DEBUG_INFO() << "--------------------------------";
    DEBUG_INFO() << "Own service registered";
    dump(service);
    DEBUG_INFO() << "================================";
}

void SpineShipApplication::onOwnServiceRemoved(const keo_ship_discovery::ShipService&)
{
    DEBUG_INFO() << "ShipDiscovery Own service removed";
}

void SpineShipApplication::onConnected(const std::string& transportId)
{
    DEBUG_FUNC();
    LOG_INFO() << "New connection " << transportId;
}

void SpineShipApplication::onDisconnect(const std::string& transportId)
{
    DEBUG_FUNC();
    LOG_INFO() << "Connection removed " << transportId;
}

void SpineShipApplication::onDetailedDiscoveryFailed(const std::string& transportId)
{
    DEBUG_FUNC();
    LOG_INFO() << "Detailed discovery on connection " << transportId << " failed!";
    shipConnector.closeConnectionByTransportId(transportId);
}

void SpineShipApplication::onNewDevices(const std::vector<std::string>& devices)
{
    DEBUG_FUNC();
    auto iter = devices.begin();
    auto iterEnd = devices.end();
    for (; iter != iterEnd; ++iter)
    {
        LOG_INFO() << "New device " << *iter;
    }
}

void SpineShipApplication::onRemovedDevices(const std::vector<std::string>& devices)
{
    auto iter = devices.begin();
    auto iterEnd = devices.end();
    for (; iter != iterEnd; ++iter)
    {
        LOG_INFO() << "Device removed " << *iter;
    }
}

void SpineShipApplication::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    std::string message
        = static_cast<keo_datagram::KeoJsonTransformable*>(detailedDiscovery.getDetailedDiscoveryDataPtr().get())
              ->toJson();

    LOG_INFO() << "Device connected " << deviceName << " " << message;
}

void SpineShipApplication::onDetailedDiscoveryPartial(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    std::string message
        = static_cast<keo_datagram::KeoJsonTransformable*>(detailedDiscoveryPartial.getDetailedDiscoveryDataPtr().get())
              ->toJson();

    LOG_INFO() << "Partial detailed discovery received from device " << deviceName << " " << message;
}

void SpineShipApplication::handleTimer(keo_util::Timer::id_t timerId)
{
    if (timerId == modifyDDTimerId)
    {
        int id = device->getEntities().size();
        LOG_INFO() << "Add entity " << id;
        if (measurementServer)
        {
            device->addEntity(SpineMeasurement::createGenericEntityWithMeasurementServerFeature(id));
        }
        else
        {
            device->addEntity(SpineMeasurement::createGenericEntityWithMeasurementClientFeature(id));
        }

        if (!device->initialize())
        {
            LOG_ERROR() << "Cannot initialize device!";
        }

        modifyDDTimerId = timer.start(modifyDDTimeoutInSec * 1000);
    }

    if (timerId == disconnectTimerId)
    {
        std::vector<keo_spine::TransportId> transportIds = device->getTransportIds();

        for (auto id : transportIds)
        {
            shipConnector.closeConnectionByTransportId(id);
        }

        std::list<keo_ship_discovery::ShipService> services = shipDiscovery.getDiscoveredServiceList();

        for (auto service : services)
        {
            onServiceAdded(service);
        }
    }
}
}
