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

#ifndef KEO_FRAMEWORK_SRC_SERVERFEATURE_H_
#define KEO_FRAMEWORK_SRC_SERVERFEATURE_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/Feature.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/BindingManagementDeleteCall.h>
#include <keo_datagram/core/BindingManagementRequestCall.h>
#include <keo_datagram/core/SubscriptionManagementDeleteCall.h>
#include <keo_datagram/core/SubscriptionManagementRequestCall.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <mutex>

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
 * An Association represents either a Subscription or a Binding to a client.
 */
struct Association
{
    /** A unique Id of this association. This Id is chosen by the PrimaryNodeManagementFeature.*/
    long id;
    /** The feature address of the client feature that is subscribed/bound */
    keo_datagram::FeatureAddress clientAddress;
    /** A label for this subscription/binding (the server can choose this freely) */
    std::string label;
    /** A description for this subscription/binding (the server can choose this freely) */
    std::string description;

    Association()
        : id(-1)
        , clientAddress(keo_datagram::FeatureAddress())
        , label("")
        , description("")
    {
    }

    Association(long id, const keo_datagram::FeatureAddress& clientAddress, const std::string& label,
                const std::string& description)
        : id(id)
        , clientAddress(clientAddress)
        , label(label)
        , description(description)
    {
    }
};

/**
 * A base class for server features. This extends the generic feature with
 * binding and subscription handling.
 * <p>
 * Note, that when you feature is supposed to support subscriptions and
 * bindings, you need to overwrite
 * {@link allowSubscription()} and
 * {@link allowBinding()}.
 * <p>
 * If you need to react on DetailedDiscoveries and/or DestinationList updates, you can override
 * {@link #onDetailedDiscovery()} and/or {@link #onRemovedDevices()}.
 *
 */
class ServerFeature : public keo_spine::Feature
{
public:
    /**
     * No operations
     */
    static const keo_datagram::PossibleOperations NO_OPERATIONS;

    /**
     * Read only
     */
    static const keo_datagram::PossibleOperations READ_ONLY;

    /**
     * Partial Read, No Write
     */
    static const keo_datagram::PossibleOperations READ_PARTIAL;

    /**
     * Write only
     */
    static const keo_datagram::PossibleOperations WRITE_ONLY;

    /**
     * No Read, Partial Write
     */
    static const keo_datagram::PossibleOperations WRITE_PARTIAL;

    /**
     * Partial Read, Write
     */
    static const keo_datagram::PossibleOperations READ_PARTIAL_WRITE;

    /**
     * Read, Partial Write
     */
    static const keo_datagram::PossibleOperations READ_WRITE_PARTIAL;

    /**
     * Read, Write
     */
    static const keo_datagram::PossibleOperations READ_WRITE;

    /**
     * Partial Read, Partial Write
     */
    static const keo_datagram::PossibleOperations READ_PARTIAL_WRITE_PARTIAL;

    /**
     * Constructor
     */
    ServerFeature();

    /**
     * Constructor
     *
     * @param featureDescription
     *            Description of the feature
     */
    explicit ServerFeature(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription);

    /**
     * Add a binding to this feature. This method is called automatically when the PrimaryNodeManagementFeature receives
     * a BindingManagementRequestCall. The binding is only added when there does not already exist a binding to that
     * client address.
     *
     * To disallow bindings to certain client addresses, overwrite {@link ServerFeature#allowBinding}.
     *
     * @param bindingId the bindingId for the new binding
     * @param bindingRequest Binding to add
     *
     * @return true if binding has been added or was already present
     */
    bool addBinding(unsigned int bindingId, const keo_datagram::BindingManagementRequestCall& bindingRequest);

    /**
     * Remove a binding from this feature. This method is called automatically when the PrimaryNodeManagementFeature
     * receives a BindingManagementDeleteCall.
     *
     * @param bindingDelete Binding to remove
     *
     * @return true if binding has been removed
     */
    bool removeBinding(const keo_datagram::BindingManagementDeleteCall& bindingDelete);

    /**
     * Add a subscription to this feature. This method is called automatically when the PrimaryNodeManagementFeature
     * receives a SubscriptionManagementRequestCall. The subscription is only added when there does not already exist a
     * subscription from that client address.
     *
     * To disallow subscriptions from certain client addresses, overwrite {@link ServerFeature#allowSubscription}.
     *
     * @param subscriptionId the subscriptionId for the new subscription
     * @param subscriptionRequest the request for the new subscription
     *
     * @return true if  the subscription has been added or was already present
     */
    bool addSubscription(unsigned int subscriptionId,
                         const keo_datagram::SubscriptionManagementRequestCall& subscriptionRequest);

    /**
     * Remove a subscription. This method is called automatically when the PrimaryNodeManagementFeature
     * receives a SubscriptionManagementDeleteCall.
     *
     * @param subscriptionDelete the request to remove the subscription
     *
     * @return true if the subscription was removed
     */
    bool removeSubscription(const keo_datagram::SubscriptionManagementDeleteCall& subscriptionDelete);

    /**
     * Returns all current subscriptions of this feature.
     */
    const std::vector<Association> getSubscriptions() const;

    /**
     * Returns all current bindings of this feature.
     */
    const std::vector<Association> getBindings() const;

    /**
     * Checks whether this feature supports a given operation.
     * For CmdClassifiers that are not considered to be requests, but responses (i.e. NOTIFY, RESULT, REPLY and ACK),
     * this will always return false.
     * @param function the function the operation should be executed on
     * @param classifier the operation that should be executed
     * @param partial a flag, indicating whether the operation is restricted ("partial")
     * @return true, if the operation is supported
     */
    bool isSupported(const keo_datagram::Function& function,
            const keo_datagram::CmdClassifier& classifier, bool partial) const;

    /**
     * Checks whether this feature supports the operation of a datagram.
     * For datagrams that are not considered to be requests, but responses (i.e. NOTIFY, RESULT, REPLY and ACK),
     * this will always return false.
     * @param datagram the datagram to check
     * @return true, if the operation is supported
     */
    bool isSupported(const keo_datagram::Datagram& datagram) const;

protected:
    /**
     * Check whether a binding request from a client should be accepted. This
     * default implementation disallows all binding requests. Overwrite this
     * method if your feature should allow bindings.
     *
     * @param clientAddress
     *           Feature address of the client
     * @return true, if binding should be allowed
     */
    virtual bool allowBinding(const keo_datagram::FeatureAddress& clientAddress) const;

    /**
     * Check whether a subscription request from a client should be accepted.
     * This default implementation disallows all subscriptions. Overwrite this
     * method if your feature should allow subscriptions.
     *
     * @param clientAddress
     *            Feature address of the client
     * @return true, if subscription should be allowed
     */
    virtual bool allowSubscription(const keo_datagram::FeatureAddress& clientAddress) const;

    /**
     * Checks whether this feature has a binding to a client address.
     *
     * @param featureAddress the client address to check
     * @return true, if a binding to the client address exists
     */
    bool hasBinding(const keo_datagram::FeatureAddress& featureAddress) const;

    /**
     * Checks whether this feature has a subscription from a client address.
     *
     * @param featureAddress the client address to check
     * @return true, if a subscription from the client address exists
     */
    bool hasSubscription(const keo_datagram::FeatureAddress& featureAddress) const;

private:
    std::vector<Association> bindingList;
    std::vector<Association> subscriptionList;
    mutable std::mutex mtx;
};

//! typedef for non-const smart pointer type ServerFeature
typedef std::shared_ptr<ServerFeature> ServerFeaturePtr;

//! typedef for const type ServerFeature
typedef const ServerFeature ServerFeatureConst;

//! typedef for const smart pointer type ServerFeature
typedef std::shared_ptr<ServerFeatureConst> ServerFeatureConstPtr;

/** @} */ //  end of group framework
} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_SRC_SERVERFEATURE_H_ */
