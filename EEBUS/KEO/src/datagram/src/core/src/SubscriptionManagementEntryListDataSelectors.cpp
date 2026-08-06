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

#include <keo_datagram/core/SubscriptionManagementEntryListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SubscriptionManagementEntryListDataSelectors::
    SubscriptionManagementEntryListDataSelectors()
    : DataSelectors(), m_subscriptionIdIsSet(false), m_subscriptionId(0),
      m_clientAddressIsSet(false), m_clientAddress(FeatureAddress()),
      m_serverAddressIsSet(false), m_serverAddress(FeatureAddress())

{}

SubscriptionManagementEntryListDataSelectors::
    SubscriptionManagementEntryListDataSelectors(
        const xs_unsignedInt &c_subscriptionId,
        const FeatureAddress &c_clientAddress,
        const FeatureAddress &c_serverAddress)
    : DataSelectors(), m_subscriptionIdIsSet(true),
      m_subscriptionId(c_subscriptionId), m_clientAddressIsSet(true),
      m_clientAddress(c_clientAddress), m_serverAddressIsSet(true),
      m_serverAddress(c_serverAddress)

{}

bool SubscriptionManagementEntryListDataSelectors::operator==(
    const SubscriptionManagementEntryListDataSelectors &c_classObject) const {
  if (m_subscriptionIdIsSet != c_classObject.m_subscriptionIdIsSet ||
      (m_subscriptionIdIsSet &&
       (m_subscriptionId != c_classObject.m_subscriptionId))) {
    return false;
  }
  if (m_clientAddressIsSet != c_classObject.m_clientAddressIsSet ||
      (m_clientAddressIsSet &&
       (m_clientAddress != c_classObject.m_clientAddress))) {
    return false;
  }
  if (m_serverAddressIsSet != c_classObject.m_serverAddressIsSet ||
      (m_serverAddressIsSet &&
       (m_serverAddress != c_classObject.m_serverAddress))) {
    return false;
  }

  return true;
}

bool SubscriptionManagementEntryListDataSelectors::operator!=(
    const SubscriptionManagementEntryListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SubscriptionManagementEntryListDataSelectors::isEmpty() const {
  return !m_subscriptionIdIsSet && !m_clientAddressIsSet &&
         !m_serverAddressIsSet;
}

DataSelectors::Type
SubscriptionManagementEntryListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SubscriptionManagementEntryListDataSelectors::clone() const {
  return std::make_shared<SubscriptionManagementEntryListDataSelectors>(*this);
}

void SubscriptionManagementEntryListDataSelectors::setSubscriptionId(
    const xs_unsignedInt &subscriptionId) {
  m_subscriptionId = subscriptionId;
  m_subscriptionIdIsSet = true;
}

const xs_unsignedInt &
SubscriptionManagementEntryListDataSelectors::getSubscriptionId() const {
  return m_subscriptionId;
}

void SubscriptionManagementEntryListDataSelectors::cleanSubscriptionId() {
  m_subscriptionId = 0;
  m_subscriptionIdIsSet = false;
}

bool SubscriptionManagementEntryListDataSelectors::getSubscriptionIdIsSet()
    const {
  return m_subscriptionIdIsSet;
}

void SubscriptionManagementEntryListDataSelectors::setClientAddress(
    const FeatureAddress &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddress &
SubscriptionManagementEntryListDataSelectors::getClientAddress() const {
  return m_clientAddress;
}

void SubscriptionManagementEntryListDataSelectors::cleanClientAddress() {
  m_clientAddress = FeatureAddress();
  m_clientAddressIsSet = false;
}

bool SubscriptionManagementEntryListDataSelectors::getClientAddressIsSet()
    const {
  return m_clientAddressIsSet;
}

void SubscriptionManagementEntryListDataSelectors::setServerAddress(
    const FeatureAddress &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddress &
SubscriptionManagementEntryListDataSelectors::getServerAddress() const {
  return m_serverAddress;
}

void SubscriptionManagementEntryListDataSelectors::cleanServerAddress() {
  m_serverAddress = FeatureAddress();
  m_serverAddressIsSet = false;
}

bool SubscriptionManagementEntryListDataSelectors::getServerAddressIsSet()
    const {
  return m_serverAddressIsSet;
}

bool SubscriptionManagementEntryListDataSelectors::selects(
    const SubscriptionManagementEntryData &data) const {
  if (getSubscriptionIdIsSet() &&
      (!data.getSubscriptionIdIsSet() ||
       getSubscriptionId() != data.getSubscriptionId())) {
    return false;
  }
  if (getClientAddressIsSet() &&
      (!data.getClientAddressIsSet() ||
       getClientAddress() != data.getClientAddress())) {
    return false;
  }
  if (getServerAddressIsSet() &&
      (!data.getServerAddressIsSet() ||
       getServerAddress() != data.getServerAddress())) {
    return false;
  }
  return true;
}

bool SubscriptionManagementEntryListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"subscriptionId", "clientAddress", "serverAddress"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "subscriptionId", &m_subscriptionId)) {
      m_subscriptionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "clientAddress", &m_clientAddress)) {
      m_clientAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "serverAddress", &m_serverAddress)) {
      m_serverAddressIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SubscriptionManagementEntryListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_subscriptionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("subscriptionId", m_subscriptionId);
  }
  if (m_clientAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("clientAddress", m_clientAddress);
  }
  if (m_serverAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("serverAddress", m_serverAddress);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram