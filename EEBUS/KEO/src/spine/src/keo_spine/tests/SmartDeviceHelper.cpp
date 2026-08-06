#include "SmartDeviceHelper.h"
#include <keo_spine/DeviceClassificationFeature.h>
#include <keo_spine/DeviceDefinition.h>

SmartDeviceHelper::SmartDeviceHelper()
{
    // TODO Auto-generated constructor stub
}

SmartDeviceHelper::~SmartDeviceHelper()
{
    // TODO Auto-generated destructor stub
}
NetworkManagementDeviceDescriptionData SmartDeviceHelper::getNetworkManagementDeviceDescriptionData(
    const std::string& deviceName)
{
    NetworkManagementDeviceDescriptionData deviceDescription;
    deviceDescription.setDeviceAddress(DeviceAddress(deviceName));
    deviceDescription.setDeviceType(DeviceType(DeviceType::Value::GENERIC));
    return deviceDescription;
}

NetworkManagementEntityDescriptionData SmartDeviceHelper::getNetworkManagementEntityDescriptionData()
{
    // EntityDescriptionData
    NetworkManagementEntityDescriptionData description;
    EntityAddress entityAddress("", DeviceDefinition::EntityAddressZero.getEntity());
    description.setEntityAddress(entityAddress);
    description.setEntityType(EntityType(DeviceDefinition::EntityZeroEntityType));
    return description;
}

NetworkManagementFeatureDescriptionData SmartDeviceHelper::getNetworkManagementEntitFeatureDescriptionData(
    FeatureAddress featureAddress, FeatureType featureType)
{
    // EntityDescriptionData
    NetworkManagementFeatureDescriptionData description;
    description.setFeatureAddress(featureAddress);
    description.setRole(Role::Value::CLIENT);
    description.setFeatureType(featureType);
    description.setDescription("Feature description");
    return description;
}

GenericClientFeaturePtr SmartDeviceHelper::setNetworkManagementEntity(
    SmartDevicePtr device, PrimaryDeviceInformationEntityPtr entityNull)
{
    // NodeManagement
    PrimaryNodeManagementFeaturePtr nodeManagementFeature
        = PrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false);
    entityNull->addFeature(nodeManagementFeature);
    // DeviceClassification
    DeviceClassificationFeaturePtr deviceClassificationFeature
        = DeviceClassificationFeature::createBasicDeviceClassificationFeature();
    DeviceClassificationManufacturerData deviceClassificationManufacturerData;
    deviceClassificationFeature->setDeviceClassificationManufacturerData(deviceClassificationManufacturerData);
    entityNull->addFeature(deviceClassificationFeature);

    GenericClientFeaturePtr clientFeature = addGenericClientEntity(device);

    device->setPrimaryDeviceInformationEntity(entityNull);

    return clientFeature;
}

SmartDevicePtr SmartDeviceHelper::createSimpleSmartDevice(
    const std::string& deviceName, DeviceCallbackListener* deviceCallbackListener)
{
    SmartDevicePtr device = SmartDevicePtr(new SmartDevice(
        SmartDeviceHelper::getNetworkManagementDeviceDescriptionData(deviceName), deviceCallbackListener));
    PrimaryDeviceInformationEntityPtr entityNull = PrimaryDeviceInformationEntityPtr(
        new PrimaryDeviceInformationEntity(getNetworkManagementEntityDescriptionData()));
    entityNull->setNodeManagementFeature(PrimaryNodeManagementFeature::createBasicNodeManagementFeature(false, false));
    SmartDeviceHelper::setNetworkManagementEntity(device, entityNull);
    device->initialize();
    return device;
}

GenericClientFeaturePtr SmartDeviceHelper::addGenericClientEntity(SmartDevicePtr device)
{
    // EntityDescriptionData
    NetworkManagementEntityDescriptionData description;
    // Intentionally set the Entity Address to a different value than the GenericClientFeature
    EntityAddress entityAddress("", 3);
    description.setEntityAddress(entityAddress);
    description.setEntityType(EntityType(EntityType::Value::GENERIC));

    EntityPtr entityClass = EntityPtr(new Entity(description));

    GenericClientFeaturePtr genericClientFeature = GenericClientFeature::createGenericClientFeature();
    entityClass->addFeature(genericClientFeature);
    device->addEntity(entityClass);
    return genericClientFeature;
}
