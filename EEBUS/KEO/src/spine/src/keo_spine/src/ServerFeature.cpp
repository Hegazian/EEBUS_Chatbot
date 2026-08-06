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
 *     @brief      ServerFeature class definition
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

#include <keo_spine/ServerFeature.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

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

// Use lambdas as static initializers
const keo_datagram::PossibleOperations ServerFeature::NO_OPERATIONS = keo_datagram::PossibleOperations();

const keo_datagram::PossibleOperations ServerFeature::READ_ONLY = []() {
    keo_datagram::PossibleOperations op;
    op.setRead(keo_datagram::PossibleOperationsRead());
    return op;
}();

const keo_datagram::PossibleOperations ServerFeature::READ_PARTIAL = []() {
    keo_datagram::PossibleOperations op;
    op.setRead(keo_datagram::PossibleOperationsRead(true));
    return op;
}();

const keo_datagram::PossibleOperations ServerFeature::WRITE_ONLY = []() {
    keo_datagram::PossibleOperations op;
    op.setWrite(keo_datagram::PossibleOperationsWrite());
    return op;
}();

const keo_datagram::PossibleOperations ServerFeature::WRITE_PARTIAL = []() {
    keo_datagram::PossibleOperations op;
    op.setWrite(keo_datagram::PossibleOperationsWrite(true));
    return op;
}();

const keo_datagram::PossibleOperations ServerFeature::READ_PARTIAL_WRITE = []() {
    keo_datagram::PossibleOperations op;
    op.setRead(keo_datagram::PossibleOperationsRead(true));
    op.setWrite(keo_datagram::PossibleOperationsWrite());
    return op;
}();

const keo_datagram::PossibleOperations ServerFeature::READ_WRITE_PARTIAL = []() {
    keo_datagram::PossibleOperations op;
    op.setRead(keo_datagram::PossibleOperationsRead());
    op.setWrite(keo_datagram::PossibleOperationsWrite(true));
    return op;
}();

const keo_datagram::PossibleOperations ServerFeature::READ_WRITE = []() {
    keo_datagram::PossibleOperations op;
    op.setRead(keo_datagram::PossibleOperationsRead());
    op.setWrite(keo_datagram::PossibleOperationsWrite());
    return op;
}();

const keo_datagram::PossibleOperations ServerFeature::READ_PARTIAL_WRITE_PARTIAL = []() {
    keo_datagram::PossibleOperations op;
    op.setRead(keo_datagram::PossibleOperationsRead(true));
    op.setWrite(keo_datagram::PossibleOperationsWrite(true));
    return op;
}();

ServerFeature::ServerFeature()
{
}

ServerFeature::ServerFeature(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription)
    : Feature(featureDescription)
{
}

bool ServerFeature::addBinding(unsigned int bindingId, const keo_datagram::BindingManagementRequestCall& bindingRequest)
{
    keo_datagram::FeatureAddress clientAddress = bindingRequest.getClientAddress();
    bool added = false;
    if (!bindingRequest.getServerFeatureTypeIsSet()
        || bindingRequest.getServerFeatureType() == getFeatureDescription().getFeatureType())
    {
        if (hasBinding(clientAddress))
        {
            LOG_WARN() << "Client '" << clientAddress.toString() << "' already has a binding to " << this->toString();
            added = true;
        }
        else if (allowBinding(clientAddress))
        {
            std::lock_guard<std::mutex> locker(mtx);
            Association binding(bindingId, clientAddress, "", "");
            bindingList.push_back(binding);
            LOG_INFO() << "Client '" << clientAddress.toString() << "' creates a binding to " << this->toString()
                       << " with binding id '" << bindingId << "'";
            added = true;
        }
    }
    else
    {
        LOG_WARN() << "Not accepting binding request from client '" << bindingRequest.getClientAddress().toString()
                   << "' to " << this->toString() << " (feature type mismatch)";
    }
    return added;
}

bool ServerFeature::removeBinding(const keo_datagram::BindingManagementDeleteCall& bindingDelete)
{
    bool removed = false;
    const keo_datagram::FeatureAddress& featureAddress = bindingDelete.getClientAddress();
    std::lock_guard<std::mutex> locker(mtx);
    for (auto iter = bindingList.begin(); iter != bindingList.end();)
    {
        auto actIter = iter++;
        if (actIter->clientAddress.equalsWeak(featureAddress))
        {
            bindingList.erase(actIter);
            removed = true;
            break;
        }
    }
    return removed;
}

bool ServerFeature::addSubscription(
    unsigned int subscriptionId, const keo_datagram::SubscriptionManagementRequestCall& subscriptionRequest)
{
    keo_datagram::FeatureAddress clientAddress = subscriptionRequest.getClientAddress();
    bool added = false;
    if (!subscriptionRequest.getServerFeatureTypeIsSet()
        || subscriptionRequest.getServerFeatureType() == getFeatureDescription().getFeatureType())
    {
        if (hasSubscription(clientAddress))
        {
            LOG_INFO() << "Client '" << clientAddress.toString() << "' already has a subscription to "
                       << this->toString();
            added = true;
        }
        else if (allowSubscription(clientAddress))
        {
            std::lock_guard<std::mutex> locker(mtx);
            Association subscription(subscriptionId, clientAddress, "", "");
            subscriptionList.push_back(subscription);
            LOG_INFO() << "Client '" << clientAddress.toString() << "' creates a subscription to " << this->toString()
                       << "' with subscription id '" << subscriptionId << "'";
            added = true;
        }
    }
    else
    {
        LOG_WARN() << "Not accepting subscription request from client '"
                   << subscriptionRequest.getClientAddress().toString() << "' to " << this->toString()
                   << " (feature type mismatch)";
    }
    return added;
}

bool ServerFeature::removeSubscription(const keo_datagram::SubscriptionManagementDeleteCall& subscriptionDelete)
{
    bool removed = false;
    const keo_datagram::FeatureAddress& featureAddress = subscriptionDelete.getClientAddress();
    std::lock_guard<std::mutex> locker(mtx);
    for (auto iter = subscriptionList.begin(); iter != subscriptionList.end();)
    {
        auto actIter = iter++;
        if (actIter->clientAddress.equalsWeak(featureAddress))
        {
            subscriptionList.erase(actIter);
            removed = true;
            break;
        }
    }
    return removed;
}

bool ServerFeature::allowSubscription(const keo_datagram::FeatureAddress& clientAddress) const
{
    (void)clientAddress;
    return false;
}

bool ServerFeature::allowBinding(const keo_datagram::FeatureAddress& clientAddress) const
{
    (void)clientAddress;
    return false;
}

bool ServerFeature::hasBinding(const keo_datagram::FeatureAddress& featureAddress) const
{
    bool bound = false;
    std::lock_guard<std::mutex> locker(mtx);
    for (auto iter = bindingList.begin(); iter != bindingList.end(); ++iter)
    {
        if (iter->clientAddress == featureAddress)
        {
            bound = true;
            break;
        }
    }
    return bound;
}

bool ServerFeature::hasSubscription(const keo_datagram::FeatureAddress& featureAddress) const
{
    bool subscribed = false;
    std::lock_guard<std::mutex> locker(mtx);
    for (auto iter = subscriptionList.begin(); iter != subscriptionList.end(); ++iter)
    {
        if (iter->clientAddress == featureAddress)
        {
            subscribed = true;
            break;
        }
    }
    return subscribed;
}

const std::vector<Association> ServerFeature::getSubscriptions() const
{
    std::lock_guard<std::mutex> locker(mtx);
    return subscriptionList;
}

const std::vector<Association> ServerFeature::getBindings() const
{
    std::lock_guard<std::mutex> locker(mtx);
    return bindingList;
}

bool ServerFeature::isSupported(
    const keo_datagram::Function& function, const keo_datagram::CmdClassifier& classifier, bool partial) const
{
    if (getFeatureDescription().getSupportedFunctionIsSet())
    {
        for (const auto& supportedFunction : getFeatureDescription().getSupportedFunction())
        {
            if (supportedFunction.getFunction() == function && supportedFunction.getPossibleOperationsIsSet())
            {
                switch (classifier.getValue())
                {
                    case keo_datagram::CmdClassifier::Value::READ:
                    {
                        if (supportedFunction.getPossibleOperations().getReadIsSet())
                        {
                            return !partial || supportedFunction.getPossibleOperations().getRead().getPartialIsSet();
                        }
                        break;
                    }
                    case keo_datagram::CmdClassifier::Value::WRITE:
                    {
                        if (supportedFunction.getPossibleOperations().getWriteIsSet())
                        {
                            return !partial || supportedFunction.getPossibleOperations().getWrite().getPartialIsSet();
                        }
                        break;
                    }
                    case keo_datagram::CmdClassifier::Value::CALL:
                    {
                        // A call is modeled by explicitly setting neither read nor write
                        if (!partial && !supportedFunction.getPossibleOperations().getReadIsSet()
                            && !supportedFunction.getPossibleOperations().getWriteIsSet())
                        {
                            return true;
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    }
    return false;
}

bool ServerFeature::isSupported(const keo_datagram::Datagram& datagram) const
{
    bool isPartial = datagram.getCmd().getFilterIsSet() && !datagram.getCmd().getFilter().empty();
    auto function = keo_datagram::CmdData::getFunctionFromType(datagram.getCmdDataType());
    return isSupported(function, datagram.getCmdClassifier(), isPartial);
}

} /* namespace keo_spine */
