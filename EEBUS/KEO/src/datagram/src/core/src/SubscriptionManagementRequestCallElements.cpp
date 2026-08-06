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

#include <keo_datagram/core/SubscriptionManagementRequestCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SubscriptionManagementRequestCallElements::
    SubscriptionManagementRequestCallElements()
    : DataElements(), m_clientAddressIsSet(false),
      m_clientAddress(FeatureAddressElements()), m_serverAddressIsSet(false),
      m_serverAddress(FeatureAddressElements()), m_serverFeatureTypeIsSet(false)

{}

SubscriptionManagementRequestCallElements::
    SubscriptionManagementRequestCallElements(
        const FeatureAddressElements &c_clientAddress,
        const FeatureAddressElements &c_serverAddress,
        xs_boolean c_serverFeatureTypeIsSet)
    : DataElements(), m_clientAddressIsSet(true),
      m_clientAddress(c_clientAddress), m_serverAddressIsSet(true),
      m_serverAddress(c_serverAddress),
      m_serverFeatureTypeIsSet(c_serverFeatureTypeIsSet)

{}

bool SubscriptionManagementRequestCallElements::operator==(
    const SubscriptionManagementRequestCallElements &c_classObject) const {
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
  if (m_serverFeatureTypeIsSet != c_classObject.m_serverFeatureTypeIsSet) {
    return false;
  }

  return true;
}

bool SubscriptionManagementRequestCallElements::operator!=(
    const SubscriptionManagementRequestCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SubscriptionManagementRequestCallElements::isEmpty() const {
  return !m_clientAddressIsSet && !m_serverAddressIsSet &&
         !m_serverFeatureTypeIsSet;
}

DataElements::Type
SubscriptionManagementRequestCallElements::getDataType() const {
  return DataElements::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_ELEMENTS_TYPE;
}

DataElementsPtr SubscriptionManagementRequestCallElements::clone() const {
  return std::make_shared<SubscriptionManagementRequestCallElements>(*this);
}

void SubscriptionManagementRequestCallElements::setClientAddress(
    const FeatureAddressElements &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddressElements &
SubscriptionManagementRequestCallElements::getClientAddress() const {
  return m_clientAddress;
}

void SubscriptionManagementRequestCallElements::cleanClientAddress() {
  m_clientAddress = FeatureAddressElements();
  m_clientAddressIsSet = false;
}

bool SubscriptionManagementRequestCallElements::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void SubscriptionManagementRequestCallElements::setServerAddress(
    const FeatureAddressElements &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddressElements &
SubscriptionManagementRequestCallElements::getServerAddress() const {
  return m_serverAddress;
}

void SubscriptionManagementRequestCallElements::cleanServerAddress() {
  m_serverAddress = FeatureAddressElements();
  m_serverAddressIsSet = false;
}

bool SubscriptionManagementRequestCallElements::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

void SubscriptionManagementRequestCallElements::setServerFeatureType() {
  m_serverFeatureTypeIsSet = true;
}

void SubscriptionManagementRequestCallElements::cleanServerFeatureType() {
  m_serverFeatureTypeIsSet = false;
}

bool SubscriptionManagementRequestCallElements::getServerFeatureTypeIsSet()
    const {
  return m_serverFeatureTypeIsSet;
}

bool SubscriptionManagementRequestCallElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"clientAddress", "serverAddress", "serverFeatureType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
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
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "serverFeatureType")) {
      m_serverFeatureTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SubscriptionManagementRequestCallElements::toJson() const {
  std::string result = "[";
  if (m_clientAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("clientAddress", m_clientAddress);
  }
  if (m_serverAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("serverAddress", m_serverAddress);
  }
  if (m_serverFeatureTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("serverFeatureType");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram