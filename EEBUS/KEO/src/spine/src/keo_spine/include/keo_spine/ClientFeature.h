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

#ifndef KEO_FRAMEWORK_DEVICE_SRC_CLIENTFEATURE_H_
#define KEO_FRAMEWORK_DEVICE_SRC_CLIENTFEATURE_H_

/******************************************************************************* *
 * keo_spine header files                                                          *
 ******************************************************************************* */

#include <keo_spine/DatagramRecord.h>
#include <keo_spine/Feature.h>

/******************************************************************************* *
 * KEO header files                                                              *
 ******************************************************************************* */

#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/FeatureType.h>
#include <keo_datagram/core/NetworkManagementFeatureDescriptionData.h>
#include <keo_datagram/core/NodeManagementBindingRequestCall.h>
#include <keo_datagram/core/NodeManagementSubscriptionRequestCall.h>

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */

#include <map>

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

/**
 * @ingroup framework
 * @{
 */

/**
 * The base class for all client features. This adds methods for basic client-side subscription and binding management
 * to a feature.
 * <p>
 * If you need to react on DetailedDiscoveries and/or DestinationList updates, you can override
 * {@link #onDetailedDiscovery()} and/or {@link #onRemovedDevices()}.
 */
class ClientFeature : public keo_spine::Feature
{
public:
    /**
     * Constructor
     */
    ClientFeature();

    /**
     * Constructor
     *
     * @param featureDescription
     *            Description of the feature
     */
    explicit ClientFeature(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription);

    /**
     * Virtual Destructor
     */
    virtual ~ClientFeature();

    /**
     * Subscribe to a server feature of the given type at the given feature
     * address. This method only sends a NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL to the destination feature.
     * The answer has to be handled manually in {@link handlePendingDatagramResponse}.
     *
     * @param destination
     *            the server address
     * @param featureType
     *            the feature type of the server feature (can be empty)
     * @param expectResult
     *            if true, the request will be sent with ackRequest=true and a corresponding result
     *            datagram has to be handled
     * @return messageCounter of the sent datagram (>0 if successful)
     */
    keo_datagram::xs_unsignedLong subscribe(const keo_datagram::FeatureAddress& destination,
        keo_datagram::FeatureType featureType, bool expectResult = true);

    /**
     * Unsubscribe from a server feature at the feature address.
     *
     * @param destination
     *            Server address
     * @param expectResult
     *            if true, the request will be sent with ackRequest=true and a corresponding result
     *            datagram has to be handled
     * @return messageCounter of the sent datagram (>0 if successful)
     */
    keo_datagram::xs_unsignedLong unsubscribe(
        const keo_datagram::FeatureAddress& destination, bool expectResult = true);

    /**
     * Bind to a server feature of the given type at the given feature address. This method only
     * sends a NODE_MANAGEMENT_BINDING_REQUEST_CALL to the destination feature. The answer has to be
     * handled manually in {@link handlePendingDatagramResponse}.
     *
     * @param destination
     *            Server address
     * @param featureType
     *            the Feature type of the server feature (can be empty)
     * @param expectResult
     *            if true, the request will be sent with ackRequest=true and a corresponding result
     *            datagram has to be handled
     * @return messageCounter of the sent datagram (>0 if successful)
     */
    keo_datagram::xs_unsignedLong bind(const keo_datagram::FeatureAddress& destination,
        keo_datagram::FeatureType featureType, bool expectResult = true);

    /**
     * Unbind from a server feature at the feature address.
     *
     * @param destination
     *            Server address
     * @param expectResult
     *            if true, the request will be sent with ackRequest=true and a corresponding result
     *            datagram has to be handled
     * @return messageCounter of the sent datagram (>0 if successful)
     */
    keo_datagram::xs_unsignedLong unbind(const keo_datagram::FeatureAddress& destination, bool expectResult = true);

    /**
     * Returns the pending subscriptions of this feature as a mapping of message
     * counters (see {@link Header#getMsgCounter()}) to
     * {@link NodeManagementSubscriptionRequestCall}.
     *
     * @return a mapping pending subscriptions
     */
    std::map<keo_datagram::xs_unsignedLong, keo_datagram::NodeManagementSubscriptionRequestCallPtr>
    getPendingSubscriptions();

    /**
     * Returns the pending bindings of this feature as a mapping of message
     * counters (see {@link Header#getMsgCounter()}) to
     * {@link NodeManagementBindingRequestCall}.
     *
     * @return a mapping pending subscriptions
     */
    std::map<keo_datagram::xs_unsignedLong, keo_datagram::NodeManagementBindingRequestCallPtr> getPendingBindings();

protected:
    /**
     * Kill pending subscription.
     *
     * @param messageCounterReference
     *            the message counter reference
     * @return pending subscription request if a subscription for messageCounterReference is pending otherwise it
     * returns a null pointer
     */
    keo_datagram::NodeManagementSubscriptionRequestCallPtr killPendingSubscription(
        keo_datagram::xs_unsignedLong messageCounterReference);

    /**
     * Kill a pending binding.
     *
     * @param messageCounterReference
     *            the message counter reference
     * @return pending binding request if a binding for messageCounterReference is pending otherwise it
     * returns a null pointer
     */
    keo_datagram::NodeManagementBindingRequestCallPtr killPendingBinding(
        keo_datagram::xs_unsignedLong messageCounterReference);

    /**
     * Called when a pending datagram sent from this feature was not replied to in time.
     *
     * The default implementation of this method removes memory of subscription and binding requests initiated by {@link
     * ClientFeature#subscribe()} and {@link ClientFeature#bind()}. If you override this method make sure to clean up
     * {@link ClientFeature#pendingSubscriptions} and {@link ClientFeature#pendingBindings} or do something along the
     * lines of
     *
     *     bool MyFeature::timeoutHandler(const DatagramMemo& memo) override
     *     {
     *         if (!ClientFeature::timeoutHandler(memo))
     *         {
     *             // own timeout handling
     *         }
     *     }
     *
     * @param memo information about the initial request
     * @return true if timeout was handled
     */
    bool timeoutHandler(const DatagramMemo& memo) override;

protected:
    /**
     * Maps the msgCounter of a datagram sent by {@link ClientFeature#subscribe()} to the
     * NodeManagementSubscriptionRequestCall in that datagram.
     */
    std::map<keo_datagram::xs_unsignedLong, keo_datagram::NodeManagementSubscriptionRequestCallPtr>
        pendingSubscriptions;

    /**
     * Maps the msgCounter of a datagram sent by {@link ClientFeature#bind()} to the
     * NodeManagementBindingRequestCall in that datagram.
     */
    std::map<keo_datagram::xs_unsignedLong, keo_datagram::NodeManagementBindingRequestCallPtr> pendingBindings;
};

//! typedef for non-const smart pointer type ClientFeature
typedef std::shared_ptr<ClientFeature> ClientFeaturePtr;

//! typedef for const type ClientFeature
typedef const ClientFeature ClientFeatureConst;

//! typedef for const smart pointer type ClientFeature
typedef std::shared_ptr<ClientFeatureConst> ClientFeatureConstPtr;

/** @} */ //  end of group framework
} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_DEVICE_SRC_CLIENTFEATURE_H_ */
