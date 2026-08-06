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

#include "ExampleServerApplication.h"
#include "MeasurementServerFeature.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_default_ship_transport/ShipTransportConfiguration.h>
#include <keo_spine/DeviceClassificationFeature.h>
#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/PrimaryDeviceInformationEntity.h>
#include <keo_spine/PrimaryNodeManagementFeature.h>
#include <keo_util/KELogging.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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

namespace keo_spine_example_server
{

const char* SECTION = "DeviceConfiguration";

keo_default_ship_transport::ShipTransportConfigurationPtr readShipConfiguration(keo_util::KEIniReader const& ini)
{
    DEBUG_FUNC();
    auto cfg = std::make_shared<keo_default_ship_transport::ShipTransportConfiguration>();
    cfg->setSHIPHostAddress(ini.get(SECTION, "ConnectionHost", "localhost"));
    cfg->setSHIPHostPort(ini.get<std::int32_t>(SECTION, "ConnectionPort", 0));
    cfg->setCertificateFullFilename(ini.get(SECTION, "CertificateFullFilename", "prime256v1CertDER.bin"));
    cfg->setPrivateKeyFullFilename(ini.get(SECTION, "PrivateKeyFullFilename", "prime256v1KeyDER.bin"));
    cfg->setTruststoreFullFilename(ini.get(SECTION, "TruststoreFullFilename", "truststore.json"));
    cfg->setShipId(ini.get(SECTION, "ShipId", "ShipId"));
    cfg->setShipPin(ini.get(SECTION, "ShipPin", ""));
    cfg->setShipPinRequirement(ini.get(SECTION, "ShipPinRequirement", ""));
    cfg->setBrand(ini.get(SECTION, "DeviceBrand", "devicebrand"));
    cfg->setType(ini.get(SECTION, "DeviceType", "devicetype"));
    cfg->setModel(ini.get(SECTION, "DeviceModel", "devicemodel"));
    cfg->setInstanceName(ini.get(SECTION, "InstanceName", "instancename"));
    return cfg;
}

ExampleServerApplication::ExampleServerApplication()
    : device()
    , spineLink()
    , shipConnector(NULL)
{
    DEBUG_FUNC();
}

ExampleServerApplication::~ExampleServerApplication()
{
    DEBUG_FUNC();

    if (shipConnector)
        delete shipConnector;
}

bool ExampleServerApplication::start(const std::string& configFilename)
{
    DEBUG_FUNC();

    bool started = false;

    keo_default_ship_transport::ShipTransportConfigurationPtr shipConfig;
    std::string spineDeviceName;

    // The configuration is read from a file
    struct stat buffer;
    if (stat(configFilename.c_str(), &buffer) == 0)
    {
        keo_util::KEIniReader ini;
        if (ini.parse(configFilename))
        {
            if (ini.hasSection(SECTION))
            {
                // The device name is needed to create the SPINE device
                spineDeviceName = ini.get(SECTION, "SpineDevice", "d:_i:47859_KEO-SimpleDeviceServer");

                // The remaining configuration parameters are used to configure the SHIP stack
                shipConfig = readShipConfiguration(ini);
            }
            else
            {
                LOG_WARNING() << "Configuration '" << configFilename << "' contains no 'DeviceConfiguration' section";
            }
        }
        else
        {
            LOG_ERROR() << "Configuration '" << configFilename << "' parse error " << ini.getLastError();
        }
    }
    else
    {
        LOG_ERROR() << "File not found '" << configFilename << "'";
    }

    if (shipConfig)
    {
        // First, prepare the main device with entities and features, along with the SPINE link.
        //
        // The SPINE link is created
        spineLink = std::make_shared<keo_spine::SpineLink>();

        // Create the SPINE device. Each device needs its device
        // description. See the SPINE documents how to represent the device.
        device = std::make_shared<keo_spine::SmartDevice>(
            getNetworkManagementDeviceDescriptionData(spineDeviceName), this);

        // Create the networkManagement entity and add it to the device
        setNetworkManagementEntity(device);

        // Create a generic entity with a measurement server feature and
        // add it to the device
        addGenericEntityWithMeasurementFeature(device);

        // Initialize device
        if (!device->initialize())
        {
            LOG_ERROR() << "Cannot initialize device";
            return false;
        }

        // Set the main device on the SPINE link
        spineLink->setMainDevice(device);

        // Initialize and start ShipTransportConnector
        shipConnector = new TrustAllShipTransportConnector(shipConfig, spineLink);
        if (!shipConnector->initialize())
        {
            LOG_ERROR() << "Cannot initialize ShipTransportConnector";
            return false;
        }

        // Start with enabled autoconnect
        if (!shipConnector->start(true))
        {
            LOG_ERROR() << "Cannot start ShipTransportConnector";
            return false;
        }

        return true;
    }
    else
    {
        LOG_ERROR() << "Cannot read configuration file '" << configFilename << "'";
    }

    return started;
}

void ExampleServerApplication::close()
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
ExampleServerApplication::getNetworkManagementDeviceDescriptionData(const std::string& spineDeviceName)
{
    keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription;

    // The device name from the configuration is set
    deviceDescription.setDeviceAddress(keo_datagram::DeviceAddress(spineDeviceName));

    // Set feature set
    deviceDescription.setNetworkFeatureSet(keo_datagram::NetworkManagementFeatureSet::Value::SMART);

    // EEBus defines several DeviceTypes. It is recommended to use only these for the device.
    deviceDescription.setDeviceType(keo_datagram::DeviceType::Value::GENERIC);

    return deviceDescription;
}

void ExampleServerApplication::setNetworkManagementEntity(keo_spine::SmartDevicePtr device)
{
    DEBUG_FUNC();
    // The entity zero is created
    keo_spine::PrimaryDeviceInformationEntityPtr entityZero
        = keo_spine::PrimaryDeviceInformationEntity::createBasicDeviceInformationEntity();

    // PrimaryNodeManagementFeature is created
    keo_spine::PrimaryNodeManagementFeaturePtr nodeManagementFeature
        = keo_spine::PrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, true);
    // and added to the entity
    entityZero->setNodeManagementFeature(nodeManagementFeature);
    // NodeManagementDeviceClassificationFeature is created
    keo_spine::DeviceClassificationFeaturePtr deviceClassificationFeature
        = keo_spine::DeviceClassificationFeature::createBasicDeviceClassificationFeature();
    keo_datagram::DeviceClassificationManufacturerData deviceClassificationManufacturerData;
    deviceClassificationFeature->setDeviceClassificationManufacturerData(deviceClassificationManufacturerData);
    // and added to the entity
    entityZero->setDeviceClassificationFeature(deviceClassificationFeature);
    // The device is initialized with its mandatory entity zero
    device->setPrimaryDeviceInformationEntity(entityZero);
}

void ExampleServerApplication::addGenericEntityWithMeasurementFeature(keo_spine::SmartDevicePtr device)
{
    keo_datagram::NetworkManagementEntityDescriptionData entityDescription;

    // The entity has the entity address 1
    entityDescription.setEntityAddress(keo_datagram::EntityAddress(std::string(), 1LL));

    // EEBus defines several EntityTypes. It is recommended to use only
    // these for an entity.
    entityDescription.setEntityType(keo_datagram::EntityType::Value::GENERIC);

    // A new entity with its description is created
    entityDescription.setDescription("Measurement test server entity");

    // Create and add the measurement server feature
    auto entityOne = std::make_shared<keo_spine::Entity>(entityDescription);

    // Add measurement feature
    entityOne->addFeature(std::make_shared<MeasurementServerFeature>());

    // All others entities are added to the device with addEntity
    device->addEntity(entityOne);
}

void ExampleServerApplication::onConnected(const std::string& transportId)
{
    LOG_INFO() << "New connection " << transportId;
}

void ExampleServerApplication::onDisconnect(const std::string& transportId)
{
    LOG_INFO() << "Connection removed " << transportId;
}

void ExampleServerApplication::onDetailedDiscoveryFailed(const std::string& transportId)
{
    LOG_INFO() << "Detailed discovery on connection " << transportId << " failed";
    shipConnector->closeConnection(transportId);
}

void ExampleServerApplication::onNewDevices(const std::vector<std::string>& devices)
{
    for (const std::string& device : devices)
    {
        LOG_INFO() << "New device " << device;
    }
}

void ExampleServerApplication::onRemovedDevices(const std::vector<std::string>& devices)
{
    for (const std::string& device : devices)
    {
        LOG_INFO() << "Device removed " << device;
    }
}

void ExampleServerApplication::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    std::string message
        = static_cast<keo_datagram::KeoJsonTransformable*>(detailedDiscovery.getDetailedDiscoveryDataPtr().get())
              ->toJson();
    LOG_INFO() << "Device connected " << deviceName << " " << message;
}

void ExampleServerApplication::onDetailedDiscoveryPartial(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    std::string message
        = static_cast<keo_datagram::KeoJsonTransformable*>(detailedDiscoveryPartial.getDetailedDiscoveryDataPtr().get())
              ->toJson();
    LOG_INFO() << "Partial detailed discovery received from device " << deviceName << " " << message;
}

} // namespace keo_spine_example_server
