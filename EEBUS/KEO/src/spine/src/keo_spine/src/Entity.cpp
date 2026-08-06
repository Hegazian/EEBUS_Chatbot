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
 *     @brief      Entity class definition
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

#include <keo_spine/Entity.h>
#include <keo_spine/Feature.h>
#include <keo_datagram/core/SpineResultErrors.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <algorithm>
#include <assert.h>
#include <vector>
#include <map>
#include <sstream>

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

class Entity::EntityPriv
{
public:
    EntityPriv(const std::vector<keo_datagram::xs_unsignedInt>& entity, const keo_datagram::EntityType& entityType)
        : sendService(NULL)
        , entitySendService()
    {
        entityDescription.setEntityAddress(keo_datagram::EntityAddress(entity));
        entityDescription.setEntityType(entityType);
    }

    explicit EntityPriv(const keo_datagram::NetworkManagementEntityDescriptionData& entityDescription)
        : sendService(NULL)
        , entitySendService()
        , entityDescription(entityDescription)
    {
    }

    ~EntityPriv()
    {
        featureMap.clear();
    }

    std::string toString() const;

    // Send service for this entity
    class EntitySendService : public SendServiceInterface
    {
        SendServiceInterface* sendService;

    public:
        EntitySendService();

        void setSendService(SendServiceInterface* sendServiceInterface);

        virtual bool sendDatagram(DatagramRecord& datagramRecord) override;

        virtual keo_datagram::xs_unsignedLong sendPendingDatagram(DatagramRecord& datagramRecord) override;

        virtual keo_datagram::xs_unsignedLong sendPendingDatagram(
            DatagramRecord& datagramRecord, long timeout) override;

        virtual bool removeTimeoutByMsgCounter(keo_datagram::xs_unsignedLong msgCounter) override;

        virtual std::string getDeviceName() const override;

        virtual bool isConnected(const std::string& deviceName) const override;
    }; // EntitySendService

    SendServiceInterface* sendService;
    EntitySendService entitySendService;
    keo_datagram::NetworkManagementEntityDescriptionData entityDescription;
    std::map<keo_datagram::xs_unsignedInt, FeaturePtr> featureMap;
    mutable std::mutex mtx;
};

Entity::Entity(const std::vector<keo_datagram::xs_unsignedInt>& entity, const keo_datagram::EntityType& entityType)
    : p(new EntityPriv(entity, entityType))
{
}

Entity::Entity(const keo_datagram::NetworkManagementEntityDescriptionData& entityDescription)
    : p(new EntityPriv(entityDescription))
{
}

Entity::~Entity()
{
    delete p;
}

std::string Entity::getDeviceName() const
{
    assert(NULL != p->sendService);
    return p->sendService->getDeviceName();
}

void Entity::setSendService(SendServiceInterface* sendServiceInterface)
{
    p->sendService = sendServiceInterface;
    p->entitySendService.setSendService(sendServiceInterface);
}

const keo_datagram::NetworkManagementEntityDescriptionData& Entity::getEntityDescription() const
{
    return p->entityDescription;
}

std::vector<keo_datagram::xs_unsignedInt> Entity::getEntity() const
{
    if (p->entityDescription.getEntityAddressIsSet())
    {
        return p->entityDescription.getEntityAddress().getEntity();
    }
    return std::vector<keo_datagram::xs_unsignedInt>();
}

void Entity::onClose()
{
    std::lock_guard<std::mutex> locker(p->mtx);
    for (auto it = p->featureMap.begin(); it != p->featureMap.end(); ++it)
    {
        if (it->second)
        {
            it->second->onClose();
        }
        else
        {
            LOG_WARN() << "featureMap contains invalid feature object at  '" << this->toString();
        }
    }
    p->featureMap.clear();
}

bool Entity::addFeature(FeaturePtr feature)
{
    bool added = false;
    if (feature)
    {
        const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription
            = feature->getFeatureDescription();
        // TODO Refactor. Are these checks really needed when there is a validate() method?
        if (featureDescription.getFeatureAddressIsSet())
        {
            const keo_datagram::FeatureAddress& featureAddress = featureDescription.getFeatureAddress();
            if (featureAddress.getFeatureIsSet())
            {
                feature->setSendService(&p->entitySendService);

                std::lock_guard<std::mutex> locker(p->mtx);

                auto it = p->featureMap.find(featureAddress.getFeature());
                if (it == p->featureMap.end())
                {
                    p->featureMap.insert(std::make_pair(featureAddress.getFeature(), feature));

                    LOG_INFO() << "Successfully added " << feature->toString() << " to " << this->toString();
                    added = true;
                }
                else
                {
                    LOG_INFO() << "Successfully overwrote existing " << feature->toString() << " in "
                               << this->toString();
                    added = true;
                }
            }
            else
            {
                LOG_WARN() << "Cannot add " << feature->toString() << " to " << this->toString()
                           << "'. Feature part of FeatureAddress is not set.";
            }
        }
        else
        {
            LOG_WARN() << "Cannot add " << feature->toString() << " to " << this->toString()
                       << "'. FeatureAddress is not set.";
        }
    }
    else
    {
        LOG_WARN() << "Cannot add invalid feature object to " << this->toString();
    }
    return added;
}

bool Entity::removeFeature(keo_datagram::xs_unsignedInt feature)
{
    bool removed = false;
    std::lock_guard<std::mutex> locker(p->mtx);
    auto it = p->featureMap.find(feature);
    if (it != p->featureMap.end())
    {
        if (!it->second)
        {
            LOG_WARN() << "invalid feature object removed from " << this->toString();
        }
        else
        {
            LOG_INFO() << it->second->toString() << " removed from " << this->toString();
        }
        p->featureMap.erase(feature);
        removed = true;
    }
    else
    {
        LOG_WARN() << "Cannot remove feature from " << this->toString() << ". There is no feature at address "
                   << feature;
    }
    return removed;
}

std::vector<FeaturePtr> Entity::getFeatures() const
{
    std::vector<FeaturePtr> featureList;
    std::lock_guard<std::mutex> locker(p->mtx);
    for (auto it = p->featureMap.begin(); it != p->featureMap.end(); ++it)
    {
        featureList.push_back(it->second);
    }

    return featureList;
}

FeaturePtr Entity::getFeature(keo_datagram::xs_unsignedInt feature) const
{
    FeaturePtr featurePtr;
    std::lock_guard<std::mutex> locker(p->mtx);
    auto it = p->featureMap.find(feature);
    if (it != p->featureMap.end())
    {
        featurePtr = it->second;
    }
    else
    {
        LOG_WARN() << "Cannot get feature from " << this->toString() << ". There is no feature at address " << feature
                   << ".";
    }
    return featurePtr;
}

keo_datagram::xs_unsignedInt Entity::handleDatagram(const DatagramRecord& datagramRecord, keo_datagram::xs_unsignedInt feature)
{
    int handled = keo_datagram::SpineResultErrors::DESTINATION_UNKNOWN;
    FeaturePtr featureObj = getFeature(feature);
    if (featureObj)
    {
        handled = featureObj->handleDatagram(datagramRecord) ? keo_datagram::SpineResultErrors::OK
                                                             : keo_datagram::SpineResultErrors::COMMAND_NOT_SUPPORTED;
    }
    else
    {
        LOG_WARN() << "Cannot handle datagram. Invalid feature object for feature " << feature << " at "
                   << this->toString();
    }
    return handled;
}

keo_datagram::xs_unsignedInt Entity::handleDatagramResponse(const DatagramRecord& datagramRecord, keo_datagram::xs_unsignedInt feature)
{
    int handled = keo_datagram::SpineResultErrors::DESTINATION_UNKNOWN;
    FeaturePtr featureObj = getFeature(feature);
    if (featureObj)
    {
        handled = featureObj->handlePendingDatagramResponse(datagramRecord)
            ? keo_datagram::SpineResultErrors::OK
            : keo_datagram::SpineResultErrors::COMMAND_NOT_SUPPORTED;
    }
    else
    {
        LOG_WARN() << "Cannot handle reply datagram for feature " << feature << " at " << this->toString()
                   << ". Feature does not exist.";
    }
    return handled;
}

void Entity::handleTimeout(const keo_datagram::FeatureAddress& address, keo_datagram::xs_unsignedLong msgCounter)
{
    FeaturePtr featureObj = getFeature(address.getFeature());
    if (featureObj)
    {
        featureObj->timeout(msgCounter);
    }
}

bool Entity::validate()
{
    bool validatedEntity = true;
    bool validatedAllFeatures = true;

    std::lock_guard<std::mutex> locker(p->mtx);
    // TODO need mutex?
    auto iter = p->featureMap.begin();
    auto iterEnd = p->featureMap.end();

    if (!getEntityDescription().getEntityTypeIsSet())
    {
        LOG_WARN() << this->toString() << " does not have an entity type set";
        validatedEntity = false;
    }

    for (; iter != iterEnd; ++iter)
    {
        FeaturePtr feature = iter->second;

        keo_datagram::FeatureAddress featureAddress = feature->getFeatureDescription().getFeatureAddress();
        if (!feature->validate())
        {
            validatedAllFeatures = false;
        }
        if (featureAddress.getEntity() != getEntity())
        {
            LOG_WARN() << feature->toString() << " has a different entity address than its entity " << this->toString();
            validatedAllFeatures = false;
        }
    }

    return validatedEntity && validatedAllFeatures;
}

Entity::EntityPriv::EntitySendService::EntitySendService()
    : sendService(0)
{
    DEBUG_FUNC();
}

void Entity::EntityPriv::EntitySendService::setSendService(SendServiceInterface* sendServiceInterface)
{
    assert(sendServiceInterface);
    sendService = sendServiceInterface;
}

bool Entity::EntityPriv::EntitySendService::sendDatagram(DatagramRecord& datagramRecord)
{
    if (sendService)
    {
        return sendService->sendDatagram(datagramRecord);
    }
    LOG_WARN() << "SendService is not initialized. Cannot send datagram from entity";
    return false;
}

keo_datagram::xs_unsignedLong Entity::EntityPriv::EntitySendService::sendPendingDatagram(DatagramRecord& datagramRecord)
{
    if (sendService)
    {
        return sendService->sendPendingDatagram(datagramRecord);
    }
    LOG_WARN() << "SendService is not initialized. Cannot send pending datagram from entity";
    return false;
}

keo_datagram::xs_unsignedLong Entity::EntityPriv::EntitySendService::sendPendingDatagram(
    DatagramRecord& datagramRecord, long timeout)
{
    if (sendService)
    {
        return sendService->sendPendingDatagram(datagramRecord, timeout);
    }
    LOG_WARN() << "SendService is not initialized. Cannot send pending datagram from entity";
    return false;
}

bool Entity::EntityPriv::EntitySendService::removeTimeoutByMsgCounter(keo_datagram::xs_unsignedLong msgCounter)
{
    if (sendService)
    {
        return sendService->removeTimeoutByMsgCounter(msgCounter);
    }
    LOG_WARN() << "SendService is not initialized. Cannot remove timeout from entity";
    return false;
}

std::string Entity::EntityPriv::EntitySendService::getDeviceName() const
{
    if (sendService)
    {
        return sendService->getDeviceName();
    }
    LOG_WARN() << "SendService is not initialized. Cannot get device name from entity";
    return "";
}

bool Entity::EntityPriv::EntitySendService::isConnected(const std::string& deviceName) const
{
    if (sendService)
    {
        return sendService->isConnected(deviceName);
    }
    LOG_WARN() << "SendService is not initialized. Cannot ask connected from entity";
    return false;
}

std::string Entity::toString() const
{
    return p->toString();
}

std::string Entity::addressToString() const
{
    if (getEntityDescription().getEntityAddressIsSet())
    {
        return getEntityDescription().getEntityAddress().toString();
    }
    else
    {
        return "";
    }
}

std::string Entity::EntityPriv::toString() const
{
    // Example String: "Entity /0/ (Battery)"
    std::stringstream ss;
    ss << "Entity";
    if (entityDescription.getEntityAddressIsSet() && !entityDescription.getEntityAddress().isEmpty())
    {
        ss << " " << entityDescription.getEntityAddress().toString();
    }
    if (entityDescription.getEntityTypeIsSet())
    {
        ss << " (" << entityDescription.getEntityType().toString() << ")";
    }
    return ss.str();
}

} /* namespace keo_spine */
