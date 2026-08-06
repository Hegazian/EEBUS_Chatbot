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

#include <keo_datagram/core/NodeManagementSubscriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementSubscriptionDataElements::NodeManagementSubscriptionDataElements()
    : DataElements(), m_subscriptionEntryIsSet(false),
      m_subscriptionEntry(SubscriptionManagementEntryDataElements())

{}

NodeManagementSubscriptionDataElements::NodeManagementSubscriptionDataElements(
    const SubscriptionManagementEntryDataElements &c_subscriptionEntry) {
  setSubscriptionEntry(c_subscriptionEntry);
}

bool NodeManagementSubscriptionDataElements::
operator==(const NodeManagementSubscriptionDataElements &c_classObject) const {
  if (m_subscriptionEntryIsSet != c_classObject.m_subscriptionEntryIsSet ||
      (m_subscriptionEntryIsSet &&
       (m_subscriptionEntry != c_classObject.m_subscriptionEntry))) {
    return false;
  }

  return true;
}

bool NodeManagementSubscriptionDataElements::
operator!=(const NodeManagementSubscriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementSubscriptionDataElements::isEmpty() const {
  return !m_subscriptionEntryIsSet;
}

DataElements::Type NodeManagementSubscriptionDataElements::getDataType() const {
  return DataElements::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NodeManagementSubscriptionDataElements::clone() const {
  return std::make_shared<NodeManagementSubscriptionDataElements>(*this);
}

void NodeManagementSubscriptionDataElements::setSubscriptionEntry(
    const SubscriptionManagementEntryDataElements &subscriptionEntry) {
  m_subscriptionEntry = subscriptionEntry;
  m_subscriptionEntryIsSet = true;
}

const SubscriptionManagementEntryDataElements &
NodeManagementSubscriptionDataElements::getSubscriptionEntry() const {
  return m_subscriptionEntry;
}

void NodeManagementSubscriptionDataElements::cleanSubscriptionEntry() {
  m_subscriptionEntry = SubscriptionManagementEntryDataElements();
  m_subscriptionEntryIsSet = false;
}

bool NodeManagementSubscriptionDataElements::getSubscriptionEntryIsSet() const {
  return m_subscriptionEntryIsSet;
}

bool NodeManagementSubscriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"subscriptionEntry"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "subscriptionEntry", &m_subscriptionEntry)) {
      m_subscriptionEntryIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementSubscriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_subscriptionEntryIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("subscriptionEntry", m_subscriptionEntry);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram