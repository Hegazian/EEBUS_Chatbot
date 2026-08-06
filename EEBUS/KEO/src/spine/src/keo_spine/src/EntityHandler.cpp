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

#include "EntityHandler.h"
#include <keo_spine/DeviceDefinition.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include "keo_spineVersion.h"
#include <algorithm>
#include <assert.h>
#include <keo_datagram/core/SpineResultErrors.h>
#include <keo_tool/KEJobRunner.h>
#include <keo_util/KELogging.h>

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

EntityHandler::EntityHandler(EntityHandlerInterface* entityHandlerCallback)
    : entityHandlerInterface(entityHandlerCallback)
    , entityMap()
    , mtx()
{
    jobRunner = keo_tool::KEJobRunner::start();
}

EntityHandler::~EntityHandler()
{
    if (jobRunner->isRunning())
    {
        keo_tool::KEJobRunner::stop(jobRunner);
    }
    delete jobRunner;
}

bool EntityHandler::initialize(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription)
{
    DEBUG_FUNC();
    keo_datagram::DetailedDiscovery detailedDiscovery;
    detailedDiscovery.setDetailedDiscoveryData(getNodeManagementDetailedDiscoveryData(deviceDescription));
    keo_spine::PrimaryNodeManagementFeaturePtr feature = getNodeManagementFeature();
    if (feature)
    {
        feature->setDetailedDiscovery(detailedDiscovery);
        return true;
    }
    else
    {
        LOG_WARN() << "No primary NodeManagement feature in device";
    }
    return false;
}

bool EntityHandler::validate()
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);

    bool validatedAllEntities = true;
    for (auto iter = entityMap.begin(); iter != entityMap.end() && validatedAllEntities; ++iter)
    {
        validatedAllEntities &= iter->second->validate();
    }

    return validatedAllEntities;
}

keo_datagram::DetailedDiscoveryConstPtr EntityHandler::getDetailedDiscovery(
    const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription) const
{
    DEBUG_FUNC();

    // Even though getNodeManagementFeature aquires the lock (through getFeature) we still need to make sure the lock is
    // held during the whole execution of this method, to make sure that no calls to initalize and this method interfere
    std::lock_guard<std::recursive_mutex> locker(mtx);

    keo_spine::PrimaryNodeManagementFeaturePtr feature = getNodeManagementFeature();
    if (feature)
    {
        return feature->getDetailedDiscovery();
    }
    else
    {
        LOG_WARN() << "No primary NodeManagement feature in device";

        keo_datagram::DetailedDiscoveryPtr detailedDiscovery = std::make_shared<keo_datagram::DetailedDiscovery>();
        detailedDiscovery->setDeviceDescription(deviceDescription);

        return detailedDiscovery;
    }
}

void EntityHandler::close()
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    // TODO needed anymore??
    // Hot fix for shutdown deadlock: avoid reentrance when shutting down
    // closing = true;

    for (auto iter = entityMap.begin(); iter != entityMap.end(); ++iter)
    {
        if (iter->second)
        {
            iter->second->onClose();
        }
        else
        {
            LOG_WARN() << "invalid entity object for entity '" << iter->second->addressToString() << "'";
        }
    }
    entityMap.clear();
    // closing = false;
}

void EntityHandler::addEntity(const EntityPtr& entityClass)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    entityMap.insert(std::make_pair(entityClass->getEntity(), entityClass));
}

void EntityHandler::removeEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = entityMap.find(entity);
    if (iter != entityMap.end())
    {
        std::string name = (*iter).second->toString();
        entityMap.erase(iter);
        LOG_INFO() << "Successfully removed " << name;
    }
    else
    {
        LOG_WARNING() << "Cannot find the entity to remove'";
    }
}

EntityPtr EntityHandler::getEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity) const
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = entityMap.find(entity);
    return (iter != entityMap.end()) ? iter->second : EntityPtr();
}

std::vector<EntityPtr> EntityHandler::getEntities() const
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    std::vector<EntityPtr> resultList;
    for (auto iter = entityMap.begin(); iter != entityMap.end(); ++iter)
    {
        resultList.push_back(iter->second);
    }
    return resultList;
}

std::vector<EntityPtr> EntityHandler::getEntityChildren(const std::vector<keo_datagram::xs_unsignedInt>& entity) const
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    std::vector<EntityPtr> childs;
    for (auto iter = entityMap.begin(); iter != entityMap.end(); ++iter)
    {
        if (entity.size() < iter->first.size()) // child entity has more elements then parent entity
        {
            // check if act entity starts with parent entity
            auto foundIter = std::search(iter->first.begin(), iter->first.end(), entity.begin(), entity.end());
            if (foundIter == iter->first.begin())
            {
                if (iter->second)
                {
                    childs.push_back(iter->second);
                }
                else
                {
                    LOG_WARN() << "invalid entity object for entity '" << iter->second->addressToString() << "'";
                }
            }
        }
    }
    return childs;
}

void EntityHandler::addEntityAndFeatureInformation(
    keo_datagram::NodeManagementDetailedDiscoveryData& nodeManagementDetailedDiscoveryData)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    // Hot fix for shutdown deadlock: avoid reentrance when shutting down
    // Can be removed after cleaning up the architecture
    // TODO neededclosing ??
    if (true) //! closing)
    {
        std::vector<keo_datagram::NodeManagementDetailedDiscoveryEntityInformation> entityInformationList;
        std::vector<keo_datagram::NodeManagementDetailedDiscoveryFeatureInformation> featureInformationList;
        for (const auto& entityEntry : entityMap)
        {
            auto entityDescription = entityEntry.second->getEntityDescription();
            // Copy entity address and remove device part
            keo_datagram::EntityAddress entityAddress(entityDescription.getEntityAddress());
            entityAddress.cleanDevice();
            entityDescription.setEntityAddress(entityAddress);

            keo_datagram::NodeManagementDetailedDiscoveryEntityInformation entityInformation;
            entityInformation.setDescription(entityDescription);
            entityInformationList.push_back(entityInformation);

            for (const auto& feature : entityEntry.second->getFeatures())
            {
                auto featureDescription = feature->getFeatureDescription();
                // Copy feature address and remove device part
                keo_datagram::FeatureAddress featureAddress(featureDescription.getFeatureAddress());
                featureAddress.cleanDevice();
                featureDescription.setFeatureAddress(featureAddress);

                keo_datagram::NodeManagementDetailedDiscoveryFeatureInformation featureInformation;
                featureInformation.setDescription(featureDescription);
                featureInformationList.push_back(featureInformation);
            }
        }
        nodeManagementDetailedDiscoveryData.setEntityInformation(entityInformationList);
        nodeManagementDetailedDiscoveryData.setFeatureInformation(featureInformationList);
    }
}

FeaturePtr EntityHandler::getFeature(
    const std::vector<keo_datagram::xs_unsignedInt>& entity, keo_datagram::xs_unsignedInt feature) const
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    FeaturePtr featurePtr;
    auto iter = entityMap.find(entity);
    if (iter != entityMap.end())
    {
        if (iter->second)
        {
            featurePtr = iter->second->getFeature(feature);
        }
        else
        {
            LOG_WARNING() << "Feature not found for'"
                          << keo_datagram::FeatureAddress(std::string(), entity, feature).toString() << "'";
        }
    }
    return featurePtr;
}

PrimaryNodeManagementFeaturePtr EntityHandler::getNodeManagementFeature() const
{
    // TODO This should be refactored to use the member set by SmartDevice::setPrimaryDeviceInformationEntity
    DEBUG_FUNC();
    FeaturePtr featurePtr
        = getFeature(DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero);
    PrimaryNodeManagementFeaturePtr nodeManagement
        = std::dynamic_pointer_cast<PrimaryNodeManagementFeature>(featurePtr);
    if (nodeManagement)
    {
        return nodeManagement;
    }
    return PrimaryNodeManagementFeaturePtr();
}

keo_datagram::xs_unsignedInt EntityHandler::handleDatagram(
    const DatagramRecord& datagramRecord, const keo_datagram::FeatureAddress& featureAddress)
{
    DEBUG_FUNC();
    keo_datagram::xs_unsignedInt handled = keo_datagram::SpineResultErrors::DESTINATION_UNKNOWN;
    std::unique_lock<std::recursive_mutex> locker(mtx);
    auto iter = entityMap.find(featureAddress.getEntity());
    if (iter != entityMap.end())
    {
        EntityPtr entity = iter->second;
        if (entity)
        {
            mtx.unlock();
            handled = entity->handleDatagram(datagramRecord, featureAddress.getFeature());
        }
        else
        {
            mtx.unlock();
            LOG_WARNING() << "Cannot handle datagram (msgCounter=" << datagramRecord.getDatagram().getMsgCounter()
                          << ") for feature address '" << featureAddress.toString() << "' (invalid entity object)";
        }
    }
    else
    {
        mtx.unlock();
        LOG_WARNING() << "Cannot handle datagram (msgCounter=" << datagramRecord.getDatagram().getMsgCounter()
                      << ") for entity address '" << featureAddress.toString() << "' (entity unknown)";
    }
    return handled;
}

keo_datagram::xs_unsignedInt EntityHandler::handleDatagramResponse(
    const DatagramRecord& datagramRecord, const keo_datagram::FeatureAddress& featureAddress)
{
    DEBUG_FUNC();
    keo_datagram::xs_unsignedInt handled = keo_datagram::SpineResultErrors::DESTINATION_UNKNOWN;
    std::unique_lock<std::recursive_mutex> locker(mtx);
    auto iter = entityMap.find(featureAddress.getEntity());
    if (iter != entityMap.end())
    {
        EntityPtr entity = iter->second;

        if (entity)
        {
            mtx.unlock();
            handled = entity->handleDatagramResponse(datagramRecord, featureAddress.getFeature());
        }
        else
        {
            mtx.unlock();
            LOG_WARNING() << "Cannot handle datagram response (msgCounter="
                          << datagramRecord.getDatagram().getMsgCounter()
                          << ", msgCounterRef=" << datagramRecord.getDatagram().getMsgCounterReference()
                          << " for feature address '" << featureAddress.toString() << "' (invalid entity object)";
        }
    }
    else
    {
        mtx.unlock();
        LOG_WARNING() << "Cannot handle datagram response (msgCounter=" << datagramRecord.getDatagram().getMsgCounter()
                      << ", msgCounterRef=" << datagramRecord.getDatagram().getMsgCounterReference()
                      << " for feature address '" << featureAddress.toString() << "' (entity unknown)";
    }
    return handled;
}

void EntityHandler::handleTimeout(const keo_datagram::FeatureAddress& source, keo_datagram::xs_unsignedLong msgCounter)
{
    DEBUG_FUNC();
    std::unique_lock<std::recursive_mutex> locker(mtx);
    auto iter = entityMap.find(source.getEntity());
    if (iter != entityMap.end())
    {
        EntityPtr entity = iter->second;
        if (entity)
        {
            mtx.unlock();
            entity->handleTimeout(source, msgCounter);
        }
        else
        {
            mtx.unlock();
            LOG_WARNING() << "Cannot handle timeout for feature address '" << source.toString()
                          << "' (invalid entity object)";
        }
    }
    else
    {
        mtx.unlock();
        LOG_WARNING() << "Cannot handle timeout for entity address '" << source.toString() << "' (entity unknown)";
    }
}

bool EntityHandler::addSubDevice(
    const std::vector<keo_datagram::NetworkManagementDeviceDescriptionData>& descriptionData)
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    keo_spine::PrimaryNodeManagementFeaturePtr feature = getNodeManagementFeature();
    if (feature)
    {
        return feature->addSubDevice(descriptionData);
    }
    else
    {
        LOG_WARNING() << "No primary NodeManagement feature in device";
    }
    return false;
}

bool EntityHandler::removeSubDevice(std::vector<std::string> deviceNameList)
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    keo_spine::PrimaryNodeManagementFeaturePtr feature = getNodeManagementFeature();
    if (feature)
    {
        return feature->removeSubDevice(deviceNameList);
    }
    else
    {
        LOG_WARNING() << "No primary NodeManagement feature in device";
    }
    return false;
}

keo_datagram::NodeManagementDetailedDiscoveryData EntityHandler::getNodeManagementDetailedDiscoveryData(
    const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription)
{
    keo_datagram::NodeManagementDetailedDiscoveryData detailedDiscoveryData;
    // SpecificationVersion
    keo_datagram::NodeManagementSpecificationVersionList specificationVersionList;
    std::vector<std::string> specificationVersion;
    specificationVersion.push_back(SPINE_VERSION_STRING);
    specificationVersionList.setSpecificationVersion(specificationVersion);
    detailedDiscoveryData.setSpecificationVersionList(specificationVersionList);
    // DeviceInformation
    keo_datagram::NodeManagementDetailedDiscoveryDeviceInformation deviceInformation;
    deviceInformation.setDescription(deviceDescription);
    detailedDiscoveryData.setDeviceInformation(deviceInformation);
    // EntityInformation && FeatureInformation
    addEntityAndFeatureInformation(detailedDiscoveryData);

    return detailedDiscoveryData;
}

bool EntityHandler::addSubscription(
    unsigned int subscriptionId, const keo_datagram::SubscriptionManagementRequestCall& subscriptionCall)
{
    keo_datagram::FeatureAddress serverAddress = subscriptionCall.getServerAddress();
    FeaturePtr feature = getFeature(serverAddress.getEntity(), serverAddress.getFeature());
    ServerFeaturePtr serverFeature = std::dynamic_pointer_cast<ServerFeature>(feature);
    if (serverFeature)
    {
        return serverFeature->addSubscription(subscriptionId, subscriptionCall);
    }
    return false;
}

bool EntityHandler::removeSubscription(const keo_datagram::SubscriptionManagementDeleteCall& deleteCall)
{
    keo_datagram::FeatureAddress serverAddress = deleteCall.getServerAddress();
    FeaturePtr feature = getFeature(serverAddress.getEntity(), serverAddress.getFeature());
    ServerFeaturePtr serverFeature = std::dynamic_pointer_cast<ServerFeature>(feature);
    if (serverFeature)
    {
        return serverFeature->removeSubscription(deleteCall);
    }
    return false;
}

bool EntityHandler::addBinding(unsigned int bindingId, const keo_datagram::BindingManagementRequestCall& bindingCall)
{
    keo_datagram::FeatureAddress serverAddress = bindingCall.getServerAddress();
    FeaturePtr feature = getFeature(serverAddress.getEntity(), serverAddress.getFeature());
    ServerFeaturePtr serverFeature = std::dynamic_pointer_cast<ServerFeature>(feature);
    if (serverFeature)
    {
        return serverFeature->addBinding(bindingId, bindingCall);
    }
    return false;
}

bool EntityHandler::removeBinding(const keo_datagram::BindingManagementDeleteCall& deleteCall)
{
    keo_datagram::FeatureAddress serverAddress = deleteCall.getServerAddress();
    FeaturePtr feature = getFeature(serverAddress.getEntity(), serverAddress.getFeature());
    ServerFeaturePtr serverFeature = std::dynamic_pointer_cast<ServerFeature>(feature);
    if (serverFeature)
    {
        return serverFeature->removeBinding(deleteCall);
    }
    return false;
}

void EntityHandler::onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId)
{
    entityHandlerInterface->onNewDevices(devices, transportId);
    // TODO (also in JAVA)
    // When at some point this callback should also be forwarded to features, start a thread for that.
}

void EntityHandler::onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId)
{
    entityHandlerInterface->onRemovedDevices(devices, transportId);

    std::lock_guard<std::recursive_mutex> locker(mtx);

    class Runner : public keo_tool::KEJobRunnerJob
    {
    public:
        Runner(const std::map<std::vector<keo_datagram::xs_unsignedInt>, EntityPtr>& entityMap,
            const std::vector<std::string>& devices)
            : devices(devices)
        {
            for (auto entityMapEntry : entityMap)
            {
                entityList.push_back(entityMapEntry.second);
            }
        }

        virtual void run()
        {
            for (std::weak_ptr<Entity> entityPtr : entityList)
            {
                if (auto entity = entityPtr.lock())
                {
                    for (FeaturePtr feature : entity->getFeatures())
                    {
                        feature->onRemovedDevices(devices);
                    }
                }
            }
        }

    private:
        std::vector<std::weak_ptr<Entity>> entityList;
        const std::vector<std::string> devices;
    };

    jobRunner->addJob(new Runner(entityMap, devices));
}

void EntityHandler::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    entityHandlerInterface->onDetailedDiscovery(deviceName, detailedDiscovery);

    std::lock_guard<std::recursive_mutex> locker(mtx);

    class Runner : public keo_tool::KEJobRunnerJob
    {
    public:
        Runner(const std::map<std::vector<keo_datagram::xs_unsignedInt>, EntityPtr>& entityMap,
            const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
            : deviceName(deviceName)
            , detailedDiscovery(detailedDiscovery)
        {
            for (auto entityMapEntry : entityMap)
            {
                entityList.push_back(entityMapEntry.second);
            }
        }

        virtual void run()
        {
            for (std::weak_ptr<Entity> entityPtr : entityList)
            {
                if (auto entity = entityPtr.lock())
                {
                    for (FeaturePtr feature : entity->getFeatures())
                    {
                        feature->onDetailedDiscovery(
                            std::string(deviceName), keo_datagram::DetailedDiscovery(detailedDiscovery));
                    }
                }
            }
        }

    private:
        std::vector<std::weak_ptr<Entity>> entityList;
        std::string deviceName;
        keo_datagram::DetailedDiscovery detailedDiscovery;
    };

    jobRunner->addJob(new Runner(entityMap, deviceName, detailedDiscovery));
}

void EntityHandler::onDetailedDiscoveryPartial(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    entityHandlerInterface->onDetailedDiscoveryPartial(deviceName, detailedDiscoveryPartial);

    std::lock_guard<std::recursive_mutex> locker(mtx);

    class Runner : public keo_tool::KEJobRunnerJob
    {
    public:
        Runner(const std::map<std::vector<keo_datagram::xs_unsignedInt>, EntityPtr>& entityMap,
            const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
            : deviceName(deviceName)
            , detailedDiscoveryPartial(detailedDiscoveryPartial)
        {
            for (auto entityMapEntry : entityMap)
            {
                entityList.push_back(entityMapEntry.second);
            }
        }

        virtual void run()
        {
            for (std::weak_ptr<Entity> entityPtr : entityList)
            {
                if (auto entity = entityPtr.lock())
                {
                    for (FeaturePtr feature : entity->getFeatures())
                    {
                        feature->onDetailedDiscoveryPartial(
                            std::string(deviceName), keo_datagram::DetailedDiscoveryPartial(detailedDiscoveryPartial));
                    }
                }
            }
        }

    private:
        std::vector<std::weak_ptr<Entity>> entityList;
        std::string deviceName;
        keo_datagram::DetailedDiscoveryPartial detailedDiscoveryPartial;
    };

    jobRunner->addJob(new Runner(entityMap, deviceName, detailedDiscoveryPartial));
}

void EntityHandler::onUseCaseDiscovery(
    const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
{
    entityHandlerInterface->onUseCaseDiscovery(deviceName, useCaseDiscovery);

    std::lock_guard<std::recursive_mutex> locker(mtx);

    class Runner : public keo_tool::KEJobRunnerJob
    {
    public:
        Runner(const std::map<std::vector<keo_datagram::xs_unsignedInt>, EntityPtr>& entityMap,
            const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
            : deviceName(deviceName)
            , useCaseDiscovery(useCaseDiscovery)
        {
            for (auto entityMapEntry : entityMap)
            {
                entityList.push_back(entityMapEntry.second);
            }
        }

        virtual void run()
        {
            for (std::weak_ptr<Entity> entityPtr : entityList)
            {
                if (auto entity = entityPtr.lock())
                {
                    for (FeaturePtr feature : entity->getFeatures())
                    {
                        feature->onUseCaseDiscovery(
                            std::string(deviceName), keo_datagram::UseCaseDiscovery(useCaseDiscovery));
                    }
                }
            }
        }

    private:
        std::vector<std::weak_ptr<Entity>> entityList;
        std::string deviceName;
        keo_datagram::UseCaseDiscovery useCaseDiscovery;
    };

    jobRunner->addJob(new Runner(entityMap, deviceName, useCaseDiscovery));
}

const std::map<keo_datagram::FeatureAddress, std::vector<Association>> EntityHandler::getSubscriptions() const
{
    DEBUG_FUNC();
    std::map<keo_datagram::FeatureAddress, std::vector<Association>> allSubscriptions;
    std::lock_guard<std::recursive_mutex> locker(mtx);

    for (auto entityIter = entityMap.begin(); entityIter != entityMap.end(); ++entityIter)
    {
        const std::vector<FeaturePtr> features = entityIter->second->getFeatures();
        for (auto featureIter = features.begin(); featureIter != features.end(); ++featureIter)
        {
            ServerFeature* serverFeature = dynamic_cast<ServerFeature*>(featureIter->get());
            if (serverFeature)
            {
                const std::vector<Association> subscriptions = serverFeature->getSubscriptions();
                const keo_datagram::FeatureAddress serverAddress(
                    serverFeature->getFeatureDescription().getFeatureAddress());

                for (auto subscriptionIter = subscriptions.begin(); subscriptionIter != subscriptions.end();
                     ++subscriptionIter)
                {
                    if (allSubscriptions.find(serverAddress) == allSubscriptions.end())
                    {
                        allSubscriptions[serverAddress] = std::vector<Association>();
                    }
                    // Map the address of a server feature to its subscriptions
                    allSubscriptions[serverAddress].push_back(Association(*subscriptionIter));
                    // TODO This hangs when I use serverFeature->getFullFeatureAddress(). Why?
                }
            }
        }
    }
    return allSubscriptions;
}

const std::map<keo_datagram::FeatureAddress, std::vector<Association>> EntityHandler::getBindings() const
{
    DEBUG_FUNC();
    std::map<keo_datagram::FeatureAddress, std::vector<Association>> allBindings;
    std::lock_guard<std::recursive_mutex> locker(mtx);

    for (auto entityIter = entityMap.begin(); entityIter != entityMap.end(); ++entityIter)
    {
        const std::vector<FeaturePtr> features = entityIter->second->getFeatures();
        for (auto featureIter = features.begin(); featureIter != features.end(); ++featureIter)
        {
            ServerFeature* serverFeature = dynamic_cast<ServerFeature*>(featureIter->get());
            if (serverFeature)
            {
                const std::vector<Association> bindings = serverFeature->getBindings();
                const keo_datagram::FeatureAddress serverAddress(
                    serverFeature->getFeatureDescription().getFeatureAddress());

                for (auto bindingIter = bindings.begin(); bindingIter != bindings.end(); ++bindingIter)
                {
                    if (allBindings.find(serverAddress) == allBindings.end())
                    {
                        allBindings[serverAddress] = std::vector<Association>();
                    }

                    // Map the address of a server feature to its bindings
                    allBindings[serverAddress].push_back(Association(*bindingIter));
                    // TODO This hangs when I use serverFeature->getFullFeatureAddress(). Why?
                }
            }
        }
    }
    return allBindings;
}

long EntityHandler::getRemoteFeatureTimeout(const keo_datagram::FeatureAddress& remoteFeatureAddress)
{
    keo_spine::PrimaryNodeManagementFeaturePtr feature = getNodeManagementFeature();
    if (nullptr != feature)
    {
        if (feature->hasRemoteFeatureTimeout(remoteFeatureAddress))
        {
            return feature->getRemoteFeatureTimeout(remoteFeatureAddress);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        LOG_WARN() << "No primary NodeManagement feature in device";
    }
    return 0;
}

} /* namespace keo_spine */
