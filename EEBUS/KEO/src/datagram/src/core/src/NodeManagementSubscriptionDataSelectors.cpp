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

#include <keo_datagram/core/NodeManagementSubscriptionDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementSubscriptionDataSelectors::
    NodeManagementSubscriptionDataSelectors()
    : DataSelectors(), m_subscriptionEntryIsSet(false),
      m_subscriptionEntry(SubscriptionManagementEntryListDataSelectors())

{}

NodeManagementSubscriptionDataSelectors::
    NodeManagementSubscriptionDataSelectors(
        const SubscriptionManagementEntryListDataSelectors
            &c_subscriptionEntry) {
  setSubscriptionEntry(c_subscriptionEntry);
}

bool NodeManagementSubscriptionDataSelectors::
operator==(const NodeManagementSubscriptionDataSelectors &c_classObject) const {
  if (m_subscriptionEntryIsSet != c_classObject.m_subscriptionEntryIsSet ||
      (m_subscriptionEntryIsSet &&
       (m_subscriptionEntry != c_classObject.m_subscriptionEntry))) {
    return false;
  }

  return true;
}

bool NodeManagementSubscriptionDataSelectors::
operator!=(const NodeManagementSubscriptionDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementSubscriptionDataSelectors::isEmpty() const {
  return !m_subscriptionEntryIsSet;
}

DataSelectors::Type
NodeManagementSubscriptionDataSelectors::getDataType() const {
  return DataSelectors::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr NodeManagementSubscriptionDataSelectors::clone() const {
  return std::make_shared<NodeManagementSubscriptionDataSelectors>(*this);
}

void NodeManagementSubscriptionDataSelectors::setSubscriptionEntry(
    const SubscriptionManagementEntryListDataSelectors &subscriptionEntry) {
  m_subscriptionEntry = subscriptionEntry;
  m_subscriptionEntryIsSet = true;
}

const SubscriptionManagementEntryListDataSelectors &
NodeManagementSubscriptionDataSelectors::getSubscriptionEntry() const {
  return m_subscriptionEntry;
}

void NodeManagementSubscriptionDataSelectors::cleanSubscriptionEntry() {
  m_subscriptionEntry = SubscriptionManagementEntryListDataSelectors();
  m_subscriptionEntryIsSet = false;
}

bool NodeManagementSubscriptionDataSelectors::getSubscriptionEntryIsSet()
    const {
  return m_subscriptionEntryIsSet;
}

bool NodeManagementSubscriptionDataSelectors::fromJson(KeoJsonValue *json) {
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

std::string NodeManagementSubscriptionDataSelectors::toJson() const {
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