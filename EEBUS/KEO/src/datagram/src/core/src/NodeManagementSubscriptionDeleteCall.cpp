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

#include <keo_datagram/core/NodeManagementSubscriptionDeleteCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementSubscriptionDeleteCall::NodeManagementSubscriptionDeleteCall()
    : CmdData(), m_subscriptionDeleteIsSet(false),
      m_subscriptionDelete(SubscriptionManagementDeleteCall())

{}

NodeManagementSubscriptionDeleteCall::NodeManagementSubscriptionDeleteCall(
    const SubscriptionManagementDeleteCall &c_subscriptionDelete) {
  setSubscriptionDelete(c_subscriptionDelete);
}

bool NodeManagementSubscriptionDeleteCall::
operator==(const NodeManagementSubscriptionDeleteCall &c_classObject) const {
  if (m_subscriptionDeleteIsSet != c_classObject.m_subscriptionDeleteIsSet ||
      (m_subscriptionDeleteIsSet &&
       (m_subscriptionDelete != c_classObject.m_subscriptionDelete))) {
    return false;
  }

  return true;
}

bool NodeManagementSubscriptionDeleteCall::
operator!=(const NodeManagementSubscriptionDeleteCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementSubscriptionDeleteCall::isEmpty() const {
  return !m_subscriptionDeleteIsSet;
}

CmdData::Type NodeManagementSubscriptionDeleteCall::getDataType() const {
  return CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE;
}

CmdDataPtr NodeManagementSubscriptionDeleteCall::clone() const {
  return std::make_shared<NodeManagementSubscriptionDeleteCall>(*this);
}

void NodeManagementSubscriptionDeleteCall::setSubscriptionDelete(
    const SubscriptionManagementDeleteCall &subscriptionDelete) {
  m_subscriptionDelete = subscriptionDelete;
  m_subscriptionDeleteIsSet = true;
}

const SubscriptionManagementDeleteCall &
NodeManagementSubscriptionDeleteCall::getSubscriptionDelete() const {
  return m_subscriptionDelete;
}

void NodeManagementSubscriptionDeleteCall::cleanSubscriptionDelete() {
  m_subscriptionDelete = SubscriptionManagementDeleteCall();
  m_subscriptionDeleteIsSet = false;
}

bool NodeManagementSubscriptionDeleteCall::getSubscriptionDeleteIsSet() const {
  return m_subscriptionDeleteIsSet;
}

CmdDataPtr NodeManagementSubscriptionDeleteCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NodeManagementSubscriptionDeleteCall>(*this);
}

bool NodeManagementSubscriptionDeleteCall::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"subscriptionDelete"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "subscriptionDelete",
                                   &m_subscriptionDelete)) {
      m_subscriptionDeleteIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementSubscriptionDeleteCall::toJson() const {
  std::string result = "[";
  if (m_subscriptionDeleteIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("subscriptionDelete",
                                           m_subscriptionDelete);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram