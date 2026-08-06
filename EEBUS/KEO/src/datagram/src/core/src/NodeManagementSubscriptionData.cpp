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

#include <keo_datagram/core/NodeManagementSubscriptionData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementSubscriptionData::NodeManagementSubscriptionData()
    : CmdData(), m_subscriptionEntryIsSet(false),
      m_subscriptionEntry(std::vector<SubscriptionManagementEntryData>())

{}

NodeManagementSubscriptionData::NodeManagementSubscriptionData(
    const std::vector<SubscriptionManagementEntryData> &c_subscriptionEntry) {
  setSubscriptionEntry(c_subscriptionEntry);
}

bool NodeManagementSubscriptionData::
operator==(const NodeManagementSubscriptionData &c_classObject) const {
  if (m_subscriptionEntryIsSet != c_classObject.m_subscriptionEntryIsSet ||
      (m_subscriptionEntryIsSet &&
       (m_subscriptionEntry != c_classObject.m_subscriptionEntry))) {
    return false;
  }

  return true;
}

bool NodeManagementSubscriptionData::
operator!=(const NodeManagementSubscriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementSubscriptionData::isEmpty() const {
  return !m_subscriptionEntryIsSet;
}

CmdData::Type NodeManagementSubscriptionData::getDataType() const {
  return CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_TYPE;
}

CmdDataPtr NodeManagementSubscriptionData::clone() const {
  return std::make_shared<NodeManagementSubscriptionData>(*this);
}

void NodeManagementSubscriptionData::setSubscriptionEntry(
    const std::vector<SubscriptionManagementEntryData> &subscriptionEntry) {
  m_subscriptionEntry = subscriptionEntry;
  m_subscriptionEntryIsSet = true;
}

const std::vector<SubscriptionManagementEntryData> &
NodeManagementSubscriptionData::getSubscriptionEntry() const {
  return m_subscriptionEntry;
}

void NodeManagementSubscriptionData::cleanSubscriptionEntry() {
  m_subscriptionEntry.clear();
  m_subscriptionEntryIsSet = false;
}

bool NodeManagementSubscriptionData::getSubscriptionEntryIsSet() const {
  return m_subscriptionEntryIsSet;
}

CmdDataPtr NodeManagementSubscriptionData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NodeManagementSubscriptionData>(*this);
}

bool NodeManagementSubscriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"subscriptionEntry"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<SubscriptionManagementEntryData>(
            static_cast<KeoJsonValue *>(&(*iter)), "subscriptionEntry",
            &m_subscriptionEntry)) {
      m_subscriptionEntryIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementSubscriptionData::toJson() const {
  std::string result = "[";
  if (m_subscriptionEntryIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<SubscriptionManagementEntryData>(
        "subscriptionEntry", m_subscriptionEntry);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram