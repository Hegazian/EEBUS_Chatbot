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

#include <keo_datagram/core/NodeManagementSubscriptionRequestCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementSubscriptionRequestCall::NodeManagementSubscriptionRequestCall()
    : CmdData(), m_subscriptionRequestIsSet(false),
      m_subscriptionRequest(SubscriptionManagementRequestCall())

{}

NodeManagementSubscriptionRequestCall::NodeManagementSubscriptionRequestCall(
    const SubscriptionManagementRequestCall &c_subscriptionRequest) {
  setSubscriptionRequest(c_subscriptionRequest);
}

bool NodeManagementSubscriptionRequestCall::
operator==(const NodeManagementSubscriptionRequestCall &c_classObject) const {
  if (m_subscriptionRequestIsSet != c_classObject.m_subscriptionRequestIsSet ||
      (m_subscriptionRequestIsSet &&
       (m_subscriptionRequest != c_classObject.m_subscriptionRequest))) {
    return false;
  }

  return true;
}

bool NodeManagementSubscriptionRequestCall::
operator!=(const NodeManagementSubscriptionRequestCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementSubscriptionRequestCall::isEmpty() const {
  return !m_subscriptionRequestIsSet;
}

CmdData::Type NodeManagementSubscriptionRequestCall::getDataType() const {
  return CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE;
}

CmdDataPtr NodeManagementSubscriptionRequestCall::clone() const {
  return std::make_shared<NodeManagementSubscriptionRequestCall>(*this);
}

void NodeManagementSubscriptionRequestCall::setSubscriptionRequest(
    const SubscriptionManagementRequestCall &subscriptionRequest) {
  m_subscriptionRequest = subscriptionRequest;
  m_subscriptionRequestIsSet = true;
}

const SubscriptionManagementRequestCall &
NodeManagementSubscriptionRequestCall::getSubscriptionRequest() const {
  return m_subscriptionRequest;
}

void NodeManagementSubscriptionRequestCall::cleanSubscriptionRequest() {
  m_subscriptionRequest = SubscriptionManagementRequestCall();
  m_subscriptionRequestIsSet = false;
}

bool NodeManagementSubscriptionRequestCall::getSubscriptionRequestIsSet()
    const {
  return m_subscriptionRequestIsSet;
}

CmdDataPtr NodeManagementSubscriptionRequestCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NodeManagementSubscriptionRequestCall>(*this);
}

bool NodeManagementSubscriptionRequestCall::fromJson(KeoJsonValue *json) {
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

std::string NodeManagementSubscriptionRequestCall::toJson() const {
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