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
 *     @brief      ClientFeature class definition
 *
 *     @par        Module description
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/******************************************************************************* *
 * project header files                                                          *
 ******************************************************************************* */

#include <keo_spine/ClientFeature.h>
#include <keo_spine/DeviceDefinition.h>

/******************************************************************************* *
 * KEO header files                                                              *
 ******************************************************************************* */

#include <keo_datagram/core/BindingManagementDeleteCall.h>
#include <keo_datagram/core/Header.h>
#include <keo_datagram/core/NodeManagementBindingDeleteCall.h>
#include <keo_datagram/core/NodeManagementSubscriptionDeleteCall.h>
#include <keo_datagram/core/SubscriptionManagementDeleteCall.h>
#include <keo_util/KELogging.h>

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */

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

ClientFeature::ClientFeature()
{
}

ClientFeature::ClientFeature(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription)
    : Feature(featureDescription)
{
}

ClientFeature::~ClientFeature()
{
}

keo_datagram::xs_unsignedLong ClientFeature::subscribe(const keo_datagram::FeatureAddress& destinationServerFeature,
    keo_datagram::FeatureType featureType, bool expectResult)
{
    const keo_datagram::FeatureAddress destinationNodeManagementFeature
        = keo_datagram::FeatureAddress(destinationServerFeature.getDevice(),
            DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero);
    keo_datagram::Header header = keo_datagram::Header(
        getFullFeatureAddress(), destinationNodeManagementFeature, keo_datagram::CmdClassifier::Value::CALL);
    if (expectResult)
    {
        header.setAckRequest(true);
    }

    auto subscriptionRequestCall = std::make_shared<keo_datagram::NodeManagementSubscriptionRequestCall>(
        keo_datagram::SubscriptionManagementRequestCall(
            getFullFeatureAddress(), destinationServerFeature, featureType));

    assert(subscriptionRequestCall);
    keo_datagram::Cmd cmd = keo_datagram::Cmd(subscriptionRequestCall);
    assert(!cmd.isEmpty());
    keo_datagram::Datagram datagram(header, cmd);
    pendingSubscriptions.insert(std::make_pair(datagram.getMsgCounter(), subscriptionRequestCall));
    LOG_INFO() << "Subscribing to feature at " << destinationServerFeature.toString();
    if (expectResult)
    {
        return sendPendingDatagram(keo_datagram::Datagram(header, cmd));
    }
    else
    {
        return sendDatagram(keo_datagram::Datagram(header, cmd));
    }
}

keo_datagram::xs_unsignedLong ClientFeature::unsubscribe(
    const keo_datagram::FeatureAddress& destinationServerFeature, bool expectResult)
{
    const keo_datagram::FeatureAddress destinationNodeManagementFeature
        = keo_datagram::FeatureAddress(destinationServerFeature.getDevice(),
            DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero);
    keo_datagram::Header header = keo_datagram::Header(
        getFullFeatureAddress(), destinationNodeManagementFeature, keo_datagram::CmdClassifier::Value::CALL);
    if (expectResult)
    {
        header.setAckRequest(true);
    }

    keo_datagram::SubscriptionManagementDeleteCall deleteRequest;
    deleteRequest.setClientAddress(getFullFeatureAddress());
    deleteRequest.setServerAddress(destinationServerFeature);
    auto subscriptionDeleteCall = std::make_shared<keo_datagram::NodeManagementSubscriptionDeleteCall>(deleteRequest);

    assert(subscriptionDeleteCall);
    keo_datagram::Cmd cmd = keo_datagram::Cmd(subscriptionDeleteCall);
    assert(!cmd.isEmpty());
    LOG_INFO() << "Unsubscribing from feature at " << destinationServerFeature.toString();
    if (expectResult)
    {
        return sendPendingDatagram(keo_datagram::Datagram(header, cmd));
    }
    else
    {
        return sendDatagram(keo_datagram::Datagram(header, cmd));
    }
}

keo_datagram::NodeManagementSubscriptionRequestCallPtr ClientFeature::killPendingSubscription(
    keo_datagram::xs_unsignedLong messageCounterReference)
{
    keo_datagram::NodeManagementSubscriptionRequestCallPtr subCall;
    auto iter = pendingSubscriptions.find(messageCounterReference);
    if (iter != pendingSubscriptions.end())
    {
        subCall = iter->second;
        pendingSubscriptions.erase(iter);
    }
    return subCall;
}

keo_datagram::xs_unsignedLong ClientFeature::bind(const keo_datagram::FeatureAddress& destinationServerFeature,
    keo_datagram::FeatureType featureType, bool expectResult)
{
    const keo_datagram::FeatureAddress destinationNodeManagementFeature
        = keo_datagram::FeatureAddress(destinationServerFeature.getDevice(),
            DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero);
    keo_datagram::Header header = keo_datagram::Header(
        getFullFeatureAddress(), destinationNodeManagementFeature, keo_datagram::CmdClassifier::Value::CALL);
    if (expectResult)
    {
        header.setAckRequest(true);
    }

    auto bindingRequestCall = std::make_shared<keo_datagram::NodeManagementBindingRequestCall>(
        keo_datagram::BindingManagementRequestCall(getFullFeatureAddress(), destinationServerFeature, featureType));

    assert(bindingRequestCall);
    keo_datagram::Cmd cmd = keo_datagram::Cmd(bindingRequestCall);
    assert(!cmd.isEmpty());
    keo_datagram::Datagram datagram(header, cmd);
    pendingBindings.insert(std::make_pair(datagram.getMsgCounter(), bindingRequestCall));
    LOG_INFO() << "Binding to feature at " << destinationServerFeature.toString();
    if (expectResult)
    {
        return sendPendingDatagram(keo_datagram::Datagram(header, cmd));
    }
    else
    {
        return sendDatagram(keo_datagram::Datagram(header, cmd));
    }
}

keo_datagram::xs_unsignedLong ClientFeature::unbind(
    const keo_datagram::FeatureAddress& destinationServerFeature, bool expectResult)
{
    const keo_datagram::FeatureAddress destinationNodeManagementFeature
        = keo_datagram::FeatureAddress(destinationServerFeature.getDevice(),
            DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero);
    keo_datagram::Header header = keo_datagram::Header(
        getFullFeatureAddress(), destinationNodeManagementFeature, keo_datagram::CmdClassifier::Value::CALL);
    if (expectResult)
    {
        header.setAckRequest(true);
    }

    keo_datagram::BindingManagementDeleteCall deleteRequest;
    deleteRequest.setClientAddress(getFullFeatureAddress());
    deleteRequest.setServerAddress(destinationServerFeature);
    auto bindingDeleteCall = std::make_shared<keo_datagram::NodeManagementBindingDeleteCall>(deleteRequest);

    assert(bindingDeleteCall);
    keo_datagram::Cmd cmd = keo_datagram::Cmd(bindingDeleteCall);
    assert(!cmd.isEmpty());
    LOG_INFO() << "Unbind from feature at " << destinationServerFeature.toString();
    if (expectResult)
    {
        return sendPendingDatagram(keo_datagram::Datagram(header, cmd));
    }
    else
    {
        return sendDatagram(keo_datagram::Datagram(header, cmd));
    }
}

keo_datagram::NodeManagementBindingRequestCallPtr ClientFeature::killPendingBinding(
    keo_datagram::xs_unsignedLong messageCounterReference)
{
    keo_datagram::NodeManagementBindingRequestCallPtr subCall;
    auto iter = pendingBindings.find(messageCounterReference);
    if (iter != pendingBindings.end())
    {
        subCall = iter->second;
        pendingBindings.erase(iter);
    }
    return subCall;
}

std::map<keo_datagram::xs_unsignedLong, keo_datagram::NodeManagementSubscriptionRequestCallPtr>
ClientFeature::getPendingSubscriptions()
{
    return pendingSubscriptions;
}

std::map<keo_datagram::xs_unsignedLong, keo_datagram::NodeManagementBindingRequestCallPtr>
ClientFeature::getPendingBindings()
{
    return pendingBindings;
}

bool ClientFeature::timeoutHandler(const DatagramMemo& memo)
{
    return killPendingSubscription(memo.getMsgCounter()) || killPendingBinding(memo.getMsgCounter());
}

} /* namespace keo_spine */
