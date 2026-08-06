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

#include <keo_datagram/core/SubscriptionManagementDeleteCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SubscriptionManagementDeleteCallElements::
    SubscriptionManagementDeleteCallElements()
    : DataElements(), m_subscriptionIdIsSet(false), m_clientAddressIsSet(false),
      m_clientAddress(FeatureAddressElements()), m_serverAddressIsSet(false),
      m_serverAddress(FeatureAddressElements())

{}

SubscriptionManagementDeleteCallElements::
    SubscriptionManagementDeleteCallElements(
        xs_boolean c_subscriptionIdIsSet,
        const FeatureAddressElements &c_clientAddress,
        const FeatureAddressElements &c_serverAddress)
    : DataElements(), m_subscriptionIdIsSet(c_subscriptionIdIsSet),
      m_clientAddressIsSet(true), m_clientAddress(c_clientAddress),
      m_serverAddressIsSet(true), m_serverAddress(c_serverAddress)

{}

bool SubscriptionManagementDeleteCallElements::operator==(
    const SubscriptionManagementDeleteCallElements &c_classObject) const {
  if (m_subscriptionIdIsSet != c_classObject.m_subscriptionIdIsSet) {
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

bool SubscriptionManagementDeleteCallElements::operator!=(
    const SubscriptionManagementDeleteCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SubscriptionManagementDeleteCallElements::isEmpty() const {
  return !m_subscriptionIdIsSet && !m_clientAddressIsSet &&
         !m_serverAddressIsSet;
}

DataElements::Type
SubscriptionManagementDeleteCallElements::getDataType() const {
  return DataElements::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_ELEMENTS_TYPE;
}

DataElementsPtr SubscriptionManagementDeleteCallElements::clone() const {
  return std::make_shared<SubscriptionManagementDeleteCallElements>(*this);
}

void SubscriptionManagementDeleteCallElements::setSubscriptionId() {
  m_subscriptionIdIsSet = true;
}

void SubscriptionManagementDeleteCallElements::cleanSubscriptionId() {
  m_subscriptionIdIsSet = false;
}

bool SubscriptionManagementDeleteCallElements::getSubscriptionIdIsSet() const {
  return m_subscriptionIdIsSet;
}

void SubscriptionManagementDeleteCallElements::setClientAddress(
    const FeatureAddressElements &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddressElements &
SubscriptionManagementDeleteCallElements::getClientAddress() const {
  return m_clientAddress;
}

void SubscriptionManagementDeleteCallElements::cleanClientAddress() {
  m_clientAddress = FeatureAddressElements();
  m_clientAddressIsSet = false;
}

bool SubscriptionManagementDeleteCallElements::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void SubscriptionManagementDeleteCallElements::setServerAddress(
    const FeatureAddressElements &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddressElements &
SubscriptionManagementDeleteCallElements::getServerAddress() const {
  return m_serverAddress;
}

void SubscriptionManagementDeleteCallElements::cleanServerAddress() {
  m_serverAddress = FeatureAddressElements();
  m_serverAddressIsSet = false;
}

bool SubscriptionManagementDeleteCallElements::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

bool SubscriptionManagementDeleteCallElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"subscriptionId", "clientAddress", "serverAddress"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "subscriptionId")) {
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

std::string SubscriptionManagementDeleteCallElements::toJson() const {
  std::string result = "[";
  if (m_subscriptionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("subscriptionId");
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