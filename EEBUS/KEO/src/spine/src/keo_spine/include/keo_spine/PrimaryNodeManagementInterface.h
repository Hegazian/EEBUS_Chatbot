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

#ifndef KEO_SPINE_EVENT_SRC_PRIMARYNODEMANAGEMENT_INTERFACE_H_
#define KEO_SPINE_EVENT_SRC_PRIMARYNODEMANAGEMENT_INTERFACE_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include <keo_datagram/core/BindingManagementDeleteCall.h>
#include <keo_datagram/core/BindingManagementRequestCall.h>
#include <keo_datagram/core/DetailedDiscovery.h>
#include <keo_datagram/core/DetailedDiscoveryPartial.h>
#include <keo_datagram/core/SubscriptionManagementDeleteCall.h>
#include <keo_datagram/core/SubscriptionManagementRequestCall.h>
#include <keo_datagram/core/UseCaseDiscovery.h>
#include <keo_spine/ServerFeature.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <map>
#include <string>
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

namespace keo_spine
{

/** @ingroup framework
 * @{
 */

/**
 * This interface allows the {@link PrimaryNodeManagementFeature} to pass data
 * out. Usually, this data will be passed to a {@link SmartDevice} via a
 * {@link PrimaryDeviceInformationEntity}.
 *
 */
class PrimaryNodeManagementInterface
{
public:
    virtual ~PrimaryNodeManagementInterface()
    {
    }
    /**
     * Directs an incoming subscription call to the correct feature.
     *
     * @param subscriptionId
     *            the id of the new subscription (this is chosen by the PrimaryNodeManagementFeature)
     * @param subscriptionCall
     *            the subscription call
     * @return true, if the subscription was added successfully
     */
    virtual bool addSubscription(
        unsigned int subscriptionId, const keo_datagram::SubscriptionManagementRequestCall& subscriptionCall)
        = 0;

    /**
     * Directs an incoming subscription delete call to the correct feature.
     *
     * @param deleteCall
     *            the delete call
     * @return true, if the subscription has been deleted successfully
     */
    virtual bool removeSubscription(const keo_datagram::SubscriptionManagementDeleteCall& deleteCall) = 0;

    /**
     * Directs an incoming binding call to the correct feature.
     *
     * @param bindingCall
     *            the binding call
     * @param bindingId
     *            the id of the new binding  (this is chosen by the PrimaryNodeManagementFeature)
     * @return true, if the binding has been added successfully
     */
    virtual bool addBinding(unsigned int bindingId, const keo_datagram::BindingManagementRequestCall& bindingCall) = 0;

    /**
     * Directs an incoming binding delete call to the correct feature.
     *
     * @param deleteCall
     *            the delete call
     * @return true, if the binding has been deleted successfully
     */
    virtual bool removeBinding(const keo_datagram::BindingManagementDeleteCall& deleteCall) = 0;

    /**
     * Announce new peer devices to all features and the smart device.
     *
     * @param devices
     *            List of new discovered devices
     * @param transportId
     *            Transport identifier
     */
    virtual void onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId) = 0;

    /**
     * Announce removed peer devices to all features and the smart device.
     *
     * @param devices
     *            List of removed devices
     * @param transportId
     *            Transport identifier
     */
    virtual void onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId) = 0;

    /**
     * Announce the detailed discovery of a peer (sub-)device to all feature.
     *
     * @param deviceName
     *            Spine device name
     * @param detailedDiscovery
     *            Detailed discovery information
     */
    virtual void onDetailedDiscovery(
        const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
        = 0;

    /**
     * Announce the partial detailed discovery of a peer (sub-)device to all feature.
     *
     * @param deviceName
     *            Spine device name
     * @param detailedDiscoveryPartial
     *            Partial detailed discovery information
     */
    virtual void onDetailedDiscoveryPartial(
        const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
        = 0;

    /**
     * Callback to announce use case data of another device.
     *
     * @param deviceName
     *            Name of the device of the UseCaseData
     * @param useCaseDiscovery
     *            a UseCaseDiscovery object containing local and remote NodeManagementUseCaseData
     */
    virtual void onUseCaseDiscovery(
        const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
        = 0;

    /**
     * Get all subscriptions of all features in the form of a mapping between
     * the server feature's address and an {@link Association} that represents a
     * subscription.
     *
     * @return all subscriptions
     */
    virtual const std::map<keo_datagram::FeatureAddress, std::vector<Association>> getSubscriptions() const = 0;

    /**
     * Get all bindings of all features in the form of a mapping between the
     * server feature's address and an {@link Association} that represents a
     * binding.
     *
     * @return all bindings
     */
    virtual const std::map<keo_datagram::FeatureAddress, std::vector<Association>> getBindings() const = 0;
};

/**
 * typedef for non-const smart pointer type PrimaryNodeManagementInterface
 */
typedef std::shared_ptr<PrimaryNodeManagementInterface> PrimaryNodeManagementInterfacePtr;

/**
 * typedef for const type PrimaryNodeManagementInterface
 */
typedef const PrimaryNodeManagementInterface PrimaryNodeManagementInterfaceConst;

/**
 * typedef for const smart pointer type PrimaryNodeManagementInterface
 */
typedef std::shared_ptr<PrimaryNodeManagementInterfaceConst> PrimaryNodeManagementInterfaceConstPtr;

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_SPINE_EVENT_SRC_PRIMARYNODEMANAGEMENT_INTERFACE_H_ */
