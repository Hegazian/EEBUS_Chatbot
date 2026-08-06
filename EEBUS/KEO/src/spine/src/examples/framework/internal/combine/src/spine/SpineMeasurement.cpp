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

#include "MeasurementClientFeature.h"
#include "MeasurementServerFeature.h"
#include "SpineMeasurement.h"

#include <keo_datagram/core/Core_All.h>

#include <keo_spine/DeviceClassificationFeature.h>
#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/PrimaryDeviceInformationEntity.h>
#include <keo_spine/PrimaryNodeManagementFeature.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <assert.h>



namespace keo_spine_combine_app
{


keo_spine::SmartDevicePtr SpineMeasurement::createSmartDeviceMeasurementClient(const std::string& deviceName,
    keo_spine::DeviceCallbackInterface* deviceCallbackHandler)
{
    // Create Smart Device
    keo_spine::SmartDevicePtr device = createSmartDevice(deviceName, deviceCallbackHandler);

    // Create a generic entity with a measurement client feature
    // and add it to the device
    device->addEntity(createGenericEntityWithMeasurementClientFeature(1LL));

    // Initialize device
    if (!device->initialize())
    {
        LOG_ERROR()<< "Cannot initialize device!";
    }

    return device;
}

keo_spine::SmartDevicePtr SpineMeasurement::createSmartDeviceMeasurementServer(const std::string& deviceName,
    keo_spine::DeviceCallbackInterface* deviceCallbackHandler)
{
    // Create Smart Device
    keo_spine::SmartDevicePtr device = createSmartDevice(deviceName, deviceCallbackHandler);

    // Create a generic entity with a measurement server feature
    // and add it to the device
    device->addEntity(createGenericEntityWithMeasurementServerFeature(1LL));

    // Initialize device
    if (!device->initialize())
    {
        LOG_ERROR()<< "Cannot initialize device!";
    }

    return device;
}

keo_spine::SmartDevicePtr SpineMeasurement::createSmartDevice(const std::string& deviceName,
    keo_spine::DeviceCallbackInterface* deviceCallbackHandler)
{
    keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription;

    // Set the device name from the configuration
    deviceDescription.setDeviceAddress(keo_datagram::DeviceAddress(deviceName));

    // Set feature set
    deviceDescription.setNetworkFeatureSet(keo_datagram::NetworkManagementFeatureSet::Value::SMART);

    // EEBus defines several DeviceTypes. It is recommended to use only
    // these for the device.
    deviceDescription.setDeviceType(keo_datagram::DeviceType(keo_datagram::DeviceType::Value::GENERIC));

    // Create the main SPINE device. Each device needs its device
    // description. See the SPINE documents how to represent the device.
    keo_spine::SmartDevicePtr device = keo_spine::SmartDevicePtr(
        new keo_spine::SmartDevice(deviceDescription, deviceCallbackHandler));

    // Create the Network Management entity and add it to the device
    addNetworkManagementEntity(device);

    return device;
}

void SpineMeasurement::addNetworkManagementEntity(keo_spine::SmartDevicePtr device)
{
    // The entity zero is created
    keo_spine::PrimaryDeviceInformationEntityPtr entityZero =
        keo_spine::PrimaryDeviceInformationEntity::createBasicDeviceInformationEntity();

    // PrimaryNodeManagementFeature is created
    keo_spine::PrimaryNodeManagementFeaturePtr nodeManagementFeature =
        keo_spine::PrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, true);
    // and added to the entity
    entityZero->setNodeManagementFeature(nodeManagementFeature);
    // NodeManagementDeviceClassificationFeature is created
    keo_spine::DeviceClassificationFeaturePtr deviceClassificationFeature =
        keo_spine::DeviceClassificationFeature::createBasicDeviceClassificationFeature();
    keo_datagram::DeviceClassificationManufacturerData deviceClassificationManufacturerData;
    deviceClassificationFeature->setDeviceClassificationManufacturerData(deviceClassificationManufacturerData);
    // and added to the entity
    entityZero->addFeature(deviceClassificationFeature);
    // The device is initialized with its mandatory entity zero
    device->setPrimaryDeviceInformationEntity(entityZero);
}

keo_spine::EntityPtr SpineMeasurement::createGenericEntityWithMeasurementClientFeature(
    const keo_datagram::xs_unsignedInt entityNo)
{
    keo_datagram::NetworkManagementEntityDescriptionData entityDescription;

    // The entity has the entity address 1
    entityDescription.setEntityAddress(keo_datagram::EntityAddress(std::string(), entityNo));

    // EEBus defines several EntityTypes. It is recommended to use only
    // these for an entity.
    entityDescription.setEntityType(
        keo_datagram::EntityType(keo_datagram::EntityType(keo_datagram::EntityType::Value::GENERIC)));

    // A new entity with its description is created
    entityDescription.setDescription("Measurement client entity");

    // Create entity
    keo_spine::EntityPtr entity = keo_spine::EntityPtr(new keo_spine::Entity(entityDescription));
    assert(entity);

    // Create and add feature
    entity->addFeature(std::make_shared<MeasurementClientFeature>(entityDescription.getEntityAddress().getEntity()));

    return entity;
}


keo_spine::EntityPtr SpineMeasurement::createGenericEntityWithMeasurementServerFeature(
    const keo_datagram::xs_unsignedInt entityNo)
{
    keo_datagram::NetworkManagementEntityDescriptionData entityDescription;

    // The entity has the entity address 1
    entityDescription.setEntityAddress(keo_datagram::EntityAddress(std::string(), entityNo));

    // EEBus defines several EntityTypes. It is recommended to use only
    // these for an entity.
    entityDescription.setEntityType(
        keo_datagram::EntityType(keo_datagram::EntityType(keo_datagram::EntityType::Value::GENERIC)));

    // A new entity with its description is created
    entityDescription.setDescription("Measurement server entity");

    // Create and add the measurement server feature
    keo_spine::EntityPtr entity = keo_spine::EntityPtr(new keo_spine::Entity(entityDescription));
    assert(entity);

    // Create and add feature
    entity->addFeature(std::make_shared<MeasurementServerFeature>(entityDescription.getEntityAddress().getEntity()));

    return entity;
}


}
