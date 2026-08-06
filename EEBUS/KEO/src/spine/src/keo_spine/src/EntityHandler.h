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
 *     @brief      Entity class declaration
 *
 *     @par        Module description
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_FRAMEWORK_DEVICE_SRC_ENTITYHANDLER_H_
#define KEO_FRAMEWORK_DEVICE_SRC_ENTITYHANDLER_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/Entity.h>
#include <keo_spine/PrimaryNodeManagementFeature.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <map>
#include <mutex>
#include <vector>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */
namespace keo_tool
{
class KEJobRunner;
}

namespace keo_spine
{

/** @ingroup framework
 * @{
 */

/**
 * Handler for all entities of the device
 *
 * This class is the root element of the hierarchy which is ranged from all
 * entities and features of the device.
 * All entities are sorted by the address
 *
 */
class EntityHandler : public PrimaryNodeManagementInterface
{
public:
    class EntityHandlerInterface
    {
    public:
        virtual void onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId) = 0;

        virtual void onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId) = 0;

        virtual void onDetailedDiscovery(
            const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
            = 0;

        virtual void onDetailedDiscoveryPartial(
            const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
            = 0;

        virtual void onUseCaseDiscovery(
            const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
            = 0;
    };

    /**
     * Constructor
     *
     * @param eventInterface
     *            Callback interface of the EntityHandler
     */
    explicit EntityHandler(EntityHandlerInterface* entityHandlerInterface);

    virtual ~EntityHandler();

    /**
     * Create the DetailedDiscovery
     *
     * Call this method after setting up the device with its entities and
     * features
     *
     * @param deviceDescription
     *            Description of this device
     * @return true
     */
    bool initialize(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription);

    /**
     * Getter for DetailedDiscovery
     *
     * @param deviceDescription
     *           Network management device description. This description is used in case
     *           of an uninitialized device.
     * @return DetailedDiscovery
     */
    keo_datagram::DetailedDiscoveryConstPtr getDetailedDiscovery(
        const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription) const;

    /**
     * Validate all entities, which in turn ensures that all features addresses
     * are set correctly.
     *
     * @return true, if the entity handler has been validated successfully
     */
    bool validate();

    /**
     * Clear the entities
     */
    void close();

    /**
     * Add an entity and set for its feature the device interfaces
     *
     * @param entityClass
     *            Entity class to add
     */
    void addEntity(const EntityPtr& entityClass);

    /**
     * Remove the entity with all its features
     *
     * @param entity
     *            Entity number of the entity class
     */
    void removeEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity);

    /**
     * Get entity class
     *
     * @param entity
     *            Entity number of the entity class
     * @return Entity class if present
     */
    EntityPtr getEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity) const;

    /**
     * Get all entities
     *
     * @return list of entities of the device
     */
    std::vector<EntityPtr> getEntities() const;

    /**
     * Get all "children" of a "parent" entity
     *
     * @param entity
     *            Entity number of the entity class
     * @return Collection of all children of the parent
     */
    std::vector<EntityPtr> getEntityChildren(const std::vector<keo_datagram::xs_unsignedInt>& entity) const;

    /**
     * Add the entity and feature information to the given detailedDiscovery
     * data
     *
     * @param nodeManagementDetailedDiscoveryData
     *            DetailedDiscovery initial data
     */
    void addEntityAndFeatureInformation(
        keo_datagram::NodeManagementDetailedDiscoveryData& nodeManagementDetailedDiscoveryData);

    /**
     * Get the feature class for an entity and feature number
     *
     * @param entity
     *            Entity number
     * @param feature
     *            Feature number
     * @return Feature class if present, otherwise null
     */
    FeaturePtr getFeature(
        const std::vector<keo_datagram::xs_unsignedInt>& entity, keo_datagram::xs_unsignedInt feature) const;

    /**
     * Get the PrimaryNodeManagementFeature
     *
     * @return PrimaryNodeManagementFeature if present, otherwise null
     */
    PrimaryNodeManagementFeaturePtr getNodeManagementFeature() const;

    /**
     * Delegate a received datagram to the corresponding entity
     *
     * @param datagramRecord
     *            Received datagram
     * @return SpineResultErrors: Destination unknown if entity didn't exists,
     *         or result from entity.handleDatagram
     */
    keo_datagram::xs_unsignedInt handleDatagram(
        const DatagramRecord& datagramRecord, const keo_datagram::FeatureAddress& featureAddress);

    /**
     * Delegate a received response datagram to the corresponding entity
     *
     * @param datagramRecord
     *            Received response datagram
     * @return SpineResultErrors.OK if handled
     */
    keo_datagram::xs_unsignedInt handleDatagramResponse(
        const DatagramRecord& datagramRecord, const keo_datagram::FeatureAddress& featureAddress);

    /**
     * Timeout handling for pending datagrams
     *
     * @param source
     *            Sender of the datagram
     * @param msgCounter
     *            MessageCounter from the sending datagram
     */
    void handleTimeout(const keo_datagram::FeatureAddress& source, keo_datagram::xs_unsignedLong msgCounter);

    /**
     * Add a sub device to the device
     *
     * @param descriptionData
     *            Detailed information of the device
     * @return true, if added
     */
    bool addSubDevice(const std::vector<keo_datagram::NetworkManagementDeviceDescriptionData>& descriptionData);

    /**
     * Remove a list of sub devices
     *
     * @param deviceNameList
     *            List of device names to remove
     * @return true, if the devices successful removed
     */
    bool removeSubDevice(std::vector<std::string> deviceNameList);

    /**
     * Get the detailed discovery data of its own device. This is created from
     * all its entities and features
     *
     * @return DetailedDiscoveryData
     */
    keo_datagram::NodeManagementDetailedDiscoveryData getNodeManagementDetailedDiscoveryData(
        const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription);

    bool addSubscription(
        unsigned int subscriptionId, const keo_datagram::SubscriptionManagementRequestCall& subscriptionCall) override;

    bool removeSubscription(const keo_datagram::SubscriptionManagementDeleteCall& deleteCall) override;

    bool addBinding(unsigned int bindingId, const keo_datagram::BindingManagementRequestCall& bindingCall) override;

    bool removeBinding(const keo_datagram::BindingManagementDeleteCall& deleteCall) override;

    void onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId) override;

    void onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId) override;

    void onDetailedDiscovery(
        const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery) override;

    void onDetailedDiscoveryPartial(
        const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial) override;

    void onUseCaseDiscovery(
        const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery) override;

    const std::map<keo_datagram::FeatureAddress, std::vector<Association>> getSubscriptions() const override;

    const std::map<keo_datagram::FeatureAddress, std::vector<Association>> getBindings() const override;

    /**
     * Get the timeout (maxResponseDelay) of a remote feature.
     * @param remoteFeatureAddress the address of the remote feature
     * @return the timeout (maxResponseDelay) or 0 if no timeout is specified for the feature
     */
    long getRemoteFeatureTimeout(const keo_datagram::FeatureAddress& remoteFeatureAddress);

private:
    EntityHandlerInterface* entityHandlerInterface;
    std::map<std::vector<keo_datagram::xs_unsignedInt>, EntityPtr> entityMap;
    keo_tool::KEJobRunner* jobRunner;
    mutable std::recursive_mutex mtx; /// guard
};
/** @} */ //  end of group framework
} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_DEVICE_SRC_ENTITYHANDLER_H_ */
