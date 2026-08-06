/*     Copyright KEO GmbH 2016 - All rights reserved!
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

#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/PrimaryDeviceInformationEntity.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <assert.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine
{

/**
 * This class is used to pass data from the primary NodeManagement feature
 * to the device (via this primary DeviceInformation entity).
 */
class PrimaryDeviceInformationEntity::EntityNodeManagementInterface : public PrimaryNodeManagementInterface
{
public:
    explicit EntityNodeManagementInterface(PrimaryDeviceInformationEntity& primaryEntity)
        : parent(primaryEntity)
    {
    }

    bool addSubscription(unsigned int subscriptionId,
                                 const keo_datagram::SubscriptionManagementRequestCall& subscriptionCall) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            return parent.deviceNodeManagementService->addSubscription(subscriptionId, subscriptionCall);
        }
        return false;
    }

    bool removeSubscription(const keo_datagram::SubscriptionManagementDeleteCall& deleteCall) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            return parent.deviceNodeManagementService->removeSubscription(deleteCall);
        }
        return false;
    }

    bool addBinding(unsigned int bindingId, const keo_datagram::BindingManagementRequestCall& bindingCall) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            return parent.deviceNodeManagementService->addBinding(bindingId, bindingCall);
        }
        return false;
    }

    bool removeBinding(const keo_datagram::BindingManagementDeleteCall& deleteCall) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            return parent.deviceNodeManagementService->removeBinding(deleteCall);
        }
        return false;
    }

    void onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            parent.deviceNodeManagementService->onNewDevices(devices, transportId);
        }
    }

    void onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            parent.deviceNodeManagementService->onRemovedDevices(devices, transportId);
        }
    }

    void onDetailedDiscovery(const std::string& deviceName,
                                     const keo_datagram::DetailedDiscovery& detailedDiscovery) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            parent.deviceNodeManagementService->onDetailedDiscovery(deviceName, detailedDiscovery);
        }
    }

    void onDetailedDiscoveryPartial(const std::string& deviceName,
                                            const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            parent.deviceNodeManagementService->onDetailedDiscoveryPartial(deviceName, detailedDiscoveryPartial);
        }
    }

    void onUseCaseDiscovery(
        const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery) override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            parent.deviceNodeManagementService->onUseCaseDiscovery(deviceName, useCaseDiscovery);
        }
    }

    const std::map<keo_datagram::FeatureAddress, std::vector<Association> > getSubscriptions() const override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            return parent.deviceNodeManagementService->getSubscriptions();
        }
        return std::map<keo_datagram::FeatureAddress, std::vector<Association> >();
    }

    const std::map<keo_datagram::FeatureAddress, std::vector<Association> > getBindings() const override
    {
        if (parent.deviceNodeManagementService != NULL)
        {
            return parent.deviceNodeManagementService->getBindings();
        }
        return std::map<keo_datagram::FeatureAddress, std::vector<Association> >();
    }

    PrimaryDeviceInformationEntity& parent;
};

PrimaryDeviceInformationEntity::PrimaryDeviceInformationEntity(
    const keo_datagram::NetworkManagementEntityDescriptionData& description)
    : Entity(description)
    , nodeManagementFeature()
    , entityNodeManagementService(new PrimaryDeviceInformationEntity::EntityNodeManagementInterface(*this))
    , deviceNodeManagementService(NULL)
{
}

PrimaryDeviceInformationEntity::~PrimaryDeviceInformationEntity()
{
    delete (entityNodeManagementService);
}

void PrimaryDeviceInformationEntity::setNodeManagementFeature(
    const PrimaryNodeManagementFeaturePtr& primaryNodeManagementFeature)
{
    nodeManagementFeature = primaryNodeManagementFeature;
    nodeManagementFeature->setPrimaryNodeManagementInterface(entityNodeManagementService);
    // TODO maybe this should return the return value of Entity::addFeature
    Entity::addFeature(primaryNodeManagementFeature);
}

PrimaryNodeManagementFeaturePtr PrimaryDeviceInformationEntity::getNodeManagementFeature()
{
    return nodeManagementFeature;
}

void PrimaryDeviceInformationEntity::setDeviceClassificationFeature(const DeviceClassificationFeaturePtr& feature)
{
    this->deviceClassificationFeature = feature;
    // TODO maybe this should return the return value of Entity::addFeature
    Entity::addFeature(feature);
}

DeviceClassificationFeaturePtr PrimaryDeviceInformationEntity::getDeviceClassificationFeature()
{
    return deviceClassificationFeature;
}

bool PrimaryDeviceInformationEntity::validate()
{
    if (Entity::validate())
    {
        keo_datagram::NetworkManagementEntityDescriptionData edd = getEntityDescription();
        keo_datagram::NetworkManagementFeatureDescriptionData nodeManagementDescription = nodeManagementFeature
            ? nodeManagementFeature->getFeatureDescription()
            : keo_datagram::NetworkManagementFeatureDescriptionData();
        keo_datagram::NetworkManagementFeatureDescriptionData deviceClassificationDescription
            = deviceClassificationFeature ? deviceClassificationFeature->getFeatureDescription()
                                          : keo_datagram::NetworkManagementFeatureDescriptionData();
        bool correctNodeManagementFeatureType = nodeManagementDescription.getFeatureTypeIsSet()
            && nodeManagementDescription.getFeatureType().getValue()
                == keo_datagram::FeatureType::Value::NODE_MANAGEMENT;
        bool correctDeviceClassificationFeatureType = deviceClassificationDescription.getFeatureTypeIsSet()
            && deviceClassificationDescription.getFeatureType().getValue()
                == keo_datagram::FeatureType::Value::DEVICE_CLASSIFICATION;
        bool correctEntityType = edd.getEntityTypeIsSet()
            && edd.getEntityType().getValue() == keo_datagram::EntityType::Value::DEVICE_INFORMATION;

        // TODO These failures might also throw exceptions as an uninitialized device is not of much use...

        if (!edd.getEntityAddressIsSet())
        {
            LOG_WARN() << "There is no entity description data in " << this->toString();
        }
        else if (!correctEntityType)
        {
            LOG_ERROR() << this->toString() << " is not of type DEVICE_INFORMATION";
        }
        else if (!nodeManagementFeature || !correctNodeManagementFeatureType)
        {
            LOG_WARN() << this->toString() << " has no node management feature";
        }
        else if (!correctDeviceClassificationFeatureType)
        {
            LOG_WARN() << this->toString() << " has no device classification feature";
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool PrimaryDeviceInformationEntity::addFeature(FeaturePtr feature)
{
    if (feature->getFeatureDescription().getFeatureAddress().getEntity()
            == DeviceDefinition::EntityAddressZero.getEntity()
        && feature->getFeatureDescription().getFeatureAddress().getFeature() == DeviceDefinition::FeatureAddressZero)
    {
        // TODO This should not be a log message but a runtime error
        LOG_WARN() << "Cannot add " << feature->toString()
                   << ". Use PrimaryDeviceInformationEntity::setNodeManagementFeature instead.";
        return false;
    }
    else if (feature->getFeatureDescription().getFeatureAddress().getEntity()
            == DeviceDefinition::EntityAddressZero.getEntity()
        && feature->getFeatureDescription().getFeatureAddress().getFeature() == DeviceDefinition::FeatureAddressOne)
    {
        // TODO This should not be a log message but a runtime error
        LOG_WARN() << "Cannot add " << feature->toString()
                   << ". Use PrimaryDeviceInformationEntity::setDeviceClassificationFeature instead.";
        return false;
    }
    return Entity::addFeature(feature);
}

bool PrimaryDeviceInformationEntity::removeFeature(keo_datagram::xs_unsignedInt featureId)
{
    bool removed = Entity::removeFeature(featureId);
    if (removed)
    {
        if (featureId == nodeManagementFeature->getFullFeatureAddress().getFeature())
        {
            nodeManagementFeature = PrimaryNodeManagementFeaturePtr();
        }
        else if (featureId == deviceClassificationFeature->getFullFeatureAddress().getFeature())
        {
            deviceClassificationFeature = DeviceClassificationFeaturePtr();
        }
    }
    return removed;
}

void PrimaryDeviceInformationEntity::setPrimaryNodeManagementInterface(
    PrimaryNodeManagementInterface* primaryNodeManagementInterface)
{
    deviceNodeManagementService = primaryNodeManagementInterface;
}

PrimaryDeviceInformationEntityPtr PrimaryDeviceInformationEntity::createBasicDeviceInformationEntity()
{
    keo_datagram::NetworkManagementEntityDescriptionData descriptionData;
    descriptionData.setEntityType(DeviceDefinition::EntityZeroEntityType);
    descriptionData.setEntityAddress(DeviceDefinition::EntityAddressZero);

    return std::make_shared<PrimaryDeviceInformationEntity>(descriptionData);
}

} /* namespace keo_spine */
