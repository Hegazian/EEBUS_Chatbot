/*
 *     Copyright KEO GmbH 2018 - All rights reserved!
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

#include "ExampleClientApplication.h"
#include "AppConfiguration.h"
#include "MeasurementClientFeature.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_spine/DeviceCallbackInterface.h>
#include <keo_spine/DeviceClassificationFeature.h>
#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/PrimaryDeviceInformationEntity.h>
#include <keo_spine/PrimaryNodeManagementFeature.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine_example_client
{

ExampleClientApplication::ExampleClientApplication()
    : device()
    , spineLink()
    , shipConnector(NULL)
{
    DEBUG_FUNC();
}

ExampleClientApplication::~ExampleClientApplication()
{
    DEBUG_FUNC();
    if (shipConnector)
    {
        delete shipConnector;
    }
}

bool ExampleClientApplication::start(const std::string& configurationFileName)
{
    DEBUG_FUNC();

    // Read the configuration file.
    AppConfiguration config;

    if (AppConfiguration::readConfiguration(config, configurationFileName))
    {
        //
        // First, prepare the main device with entities and features, along with the SPINE link.
        //

        // Create SPINE link
        spineLink = std::make_shared<keo_spine::SpineLink>();

        // Create the main SPINE device. Each device needs its device
        // description. See the SPINE documents how to represent the device.
        device = std::make_shared<keo_spine::SmartDevice>(getNetworkManagementDeviceDescriptionData(config), this);

        // Create the Network Management entity and add it to the device
        addNetworkManagementEntity(device);

        // Create a generic entity with a measurement server feature
        // and add it to the device
        addGenericEntityWithMeasurementFeature(device);

        // Initialize device
        if (!device->initialize())
        {
            LOG_ERROR() << "Cannot initialize device!";
            return false;
        }

        // Set the main device on the SPINE link
        spineLink->setMainDevice(device);

        // Initialize and start AutoConnectTrustAllShipConnectorHandler
        shipConnector = new AutoConnectTrustAllShipConnectorHandler(config, spineLink);
        if (!shipConnector->initialize())
        {
            LOG_ERROR() << "Cannot initialize ShipTransportConnector!";
            return false;
        }

        // Start with enabled autoconnect
        if (!shipConnector->start())
        {
            LOG_ERROR() << "Cannot start ShipTransportConnector!";
            return false;
        }

        return true;
    }
    else
    {
        LOG_ERROR() << "Cannot read configuration file '" << configurationFileName << "'.";
        return false;
    }
}

void ExampleClientApplication::stop()
{
    DEBUG_FUNC();
    if (shipConnector)
    {
        shipConnector->stop();
    }
    if (spineLink)
    {
        spineLink->close();
    }

    if (device)
    {
        device->close();
    }
}

keo_datagram::NetworkManagementDeviceDescriptionData
ExampleClientApplication::getNetworkManagementDeviceDescriptionData(const AppConfiguration& config)
{
    DEBUG_FUNC();
    keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription;

    // Set the device name from the configuration
    deviceDescription.setDeviceAddress(keo_datagram::DeviceAddress(config.getSpineDevice()));

    // Set feature set
    deviceDescription.setNetworkFeatureSet(keo_datagram::NetworkManagementFeatureSet::Value::SMART);

    // SPINE defines several DeviceTypes. It is recommended to use only these for the device.
    deviceDescription.setDeviceType(keo_datagram::DeviceType::Value::GENERIC);

    return deviceDescription;
}

void ExampleClientApplication::addNetworkManagementEntity(keo_spine::SmartDevicePtr device)
{
    DEBUG_FUNC();
    keo_spine::PrimaryDeviceInformationEntityPtr entityZero
        = keo_spine::PrimaryDeviceInformationEntity::createBasicDeviceInformationEntity();

    keo_spine::PrimaryNodeManagementFeaturePtr nodeManagementFeature
        = keo_spine::PrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, true);
    entityZero->setNodeManagementFeature(nodeManagementFeature);

    keo_spine::DeviceClassificationFeaturePtr deviceClassificationFeature
        = keo_spine::DeviceClassificationFeature::createBasicDeviceClassificationFeature();
    keo_datagram::DeviceClassificationManufacturerData deviceClassificationManufacturerData;
    deviceClassificationFeature->setDeviceClassificationManufacturerData(deviceClassificationManufacturerData);
    entityZero->setDeviceClassificationFeature(deviceClassificationFeature);

    device->setPrimaryDeviceInformationEntity(entityZero);
}

void ExampleClientApplication::addGenericEntityWithMeasurementFeature(keo_spine::SmartDevicePtr device)
{
    DEBUG_FUNC();
    keo_datagram::NetworkManagementEntityDescriptionData description;
    description.setEntityAddress(keo_datagram::EntityAddress(std::string(), 1LL));
    description.setEntityType(keo_datagram::EntityType::Value::GENERIC);
    description.setDescription("Measurement test client entity");
    auto entityOne = std::make_shared<keo_spine::Entity>(description);
    entityOne->addFeature(std::make_shared<MeasurementClientFeature>());
    device->addEntity(entityOne);
}

void ExampleClientApplication::onConnected(const std::string& transportId)
{
    DEBUG_FUNC();
    LOG_INFO() << "New connection " << transportId;
}

void ExampleClientApplication::onDisconnect(const std::string& transportId)
{
    DEBUG_FUNC();
    LOG_INFO() << "Connection removed " << transportId;
}

void ExampleClientApplication::onDetailedDiscoveryFailed(const std::string& transportId)
{
    DEBUG_FUNC();
    LOG_INFO() << "Detailed discovery on connection " << transportId << " failed!";
    shipConnector->closeConnection(transportId);
}

void ExampleClientApplication::onNewDevices(const std::vector<std::string>& devices)
{
    DEBUG_FUNC();
    for (const std::string& device : devices)
    {
        LOG_INFO() << "New device " << device;
    }
}

void ExampleClientApplication::onRemovedDevices(const std::vector<std::string>& devices)
{
    for (const std::string& device : devices)
    {
        LOG_INFO() << "Device removed " << device;
    }
}

void ExampleClientApplication::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    std::string message
        = static_cast<keo_datagram::KeoJsonTransformable*>(detailedDiscovery.getDetailedDiscoveryDataPtr().get())
              ->toJson();
    LOG_INFO() << "Device connected " << deviceName << " " << message;
}

void ExampleClientApplication::onDetailedDiscoveryPartial(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    std::string message
        = static_cast<keo_datagram::KeoJsonTransformable*>(detailedDiscoveryPartial.getDetailedDiscoveryDataPtr().get())
              ->toJson();
    LOG_INFO() << "Partial detailed discovery received from device " << deviceName << " " << message;
}

} // namespace keo_spine_example_client
