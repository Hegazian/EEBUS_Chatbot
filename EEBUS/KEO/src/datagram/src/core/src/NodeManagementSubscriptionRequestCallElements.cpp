/*
 *     Copyright KEO GmbH 2019 - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright
 * notice.
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

#include <keo_datagram/core/NodeManagementSubscriptionRequestCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementSubscriptionRequestCallElements::
    NodeManagementSubscriptionRequestCallElements()
    : DataElements(), m_subscriptionRequestIsSet(false),
      m_subscriptionRequest(SubscriptionManagementRequestCallElements())

{}

NodeManagementSubscriptionRequestCallElements::
    NodeManagementSubscriptionRequestCallElements(
        const SubscriptionManagementRequestCallElements
            &c_subscriptionRequest) {
  setSubscriptionRequest(c_subscriptionRequest);
}

bool NodeManagementSubscriptionRequestCallElements::operator==(
    const NodeManagementSubscriptionRequestCallElements &c_classObject) const {
  if (m_subscriptionRequestIsSet != c_classObject.m_subscriptionRequestIsSet ||
      (m_subscriptionRequestIsSet &&
       (m_subscriptionRequest != c_classObject.m_subscriptionRequest))) {
    return false;
  }

  return true;
}

bool NodeManagementSubscriptionRequestCallElements::operator!=(
    const NodeManagementSubscriptionRequestCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementSubscriptionRequestCallElements::isEmpty() const {
  return !m_subscriptionRequestIsSet;
}

DataElements::Type
NodeManagementSubscriptionRequestCallElements::getDataType() const {
  return DataElements::Type::
      NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_ELEMENTS_TYPE;
}

DataElementsPtr NodeManagementSubscriptionRequestCallElements::clone() const {
  return std::make_shared<NodeManagementSubscriptionRequestCallElements>(*this);
}

void NodeManagementSubscriptionRequestCallElements::setSubscriptionRequest(
    const SubscriptionManagementRequestCallElements &subscriptionRequest) {
  m_subscriptionRequest = subscriptionRequest;
  m_subscriptionRequestIsSet = true;
}

const SubscriptionManagementRequestCallElements &
NodeManagementSubscriptionRequestCallElements::getSubscriptionRequest() const {
  return m_subscriptionRequest;
}

void NodeManagementSubscriptionRequestCallElements::cleanSubscriptionRequest() {
  m_subscriptionRequest = SubscriptionManagementRequestCallElements();
  m_subscriptionRequestIsSet = false;
}

bool NodeManagementSubscriptionRequestCallElements::
    getSubscriptionRequestIsSet() const {
  return m_subscriptionRequestIsSet;
}

bool NodeManagementSubscriptionRequestCallElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"subscriptionRequest"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "subscriptionRequest",
                                   &m_subscriptionRequest)) {
      m_subscriptionRequestIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementSubscriptionRequestCallElements::toJson() const {
  std::string result = "[";
  if (m_subscriptionRequestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("subscriptionRequest",
                                           m_subscriptionRequest);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram