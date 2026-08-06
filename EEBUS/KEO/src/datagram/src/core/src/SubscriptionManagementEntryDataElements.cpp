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

#include <keo_datagram/core/SubscriptionManagementEntryDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SubscriptionManagementEntryDataElements::
    SubscriptionManagementEntryDataElements()
    : DataElements(), m_subscriptionIdIsSet(false), m_clientAddressIsSet(false),
      m_clientAddress(FeatureAddressElements()), m_serverAddressIsSet(false),
      m_serverAddress(FeatureAddressElements()), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool SubscriptionManagementEntryDataElements::
operator==(const SubscriptionManagementEntryDataElements &c_classObject) const {
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
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool SubscriptionManagementEntryDataElements::
operator!=(const SubscriptionManagementEntryDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SubscriptionManagementEntryDataElements::isEmpty() const {
  return !m_subscriptionIdIsSet && !m_clientAddressIsSet &&
         !m_serverAddressIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type
SubscriptionManagementEntryDataElements::getDataType() const {
  return DataElements::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SubscriptionManagementEntryDataElements::clone() const {
  return std::make_shared<SubscriptionManagementEntryDataElements>(*this);
}

void SubscriptionManagementEntryDataElements::setSubscriptionId() {
  m_subscriptionIdIsSet = true;
}

void SubscriptionManagementEntryDataElements::cleanSubscriptionId() {
  m_subscriptionIdIsSet = false;
}

bool SubscriptionManagementEntryDataElements::getSubscriptionIdIsSet() const {
  return m_subscriptionIdIsSet;
}

void SubscriptionManagementEntryDataElements::setClientAddress(
    const FeatureAddressElements &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddressElements &
SubscriptionManagementEntryDataElements::getClientAddress() const {
  return m_clientAddress;
}

void SubscriptionManagementEntryDataElements::cleanClientAddress() {
  m_clientAddress = FeatureAddressElements();
  m_clientAddressIsSet = false;
}

bool SubscriptionManagementEntryDataElements::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void SubscriptionManagementEntryDataElements::setServerAddress(
    const FeatureAddressElements &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddressElements &
SubscriptionManagementEntryDataElements::getServerAddress() const {
  return m_serverAddress;
}

void SubscriptionManagementEntryDataElements::cleanServerAddress() {
  m_serverAddress = FeatureAddressElements();
  m_serverAddressIsSet = false;
}

bool SubscriptionManagementEntryDataElements::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

void SubscriptionManagementEntryDataElements::setLabel() {
  m_labelIsSet = true;
}

void SubscriptionManagementEntryDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool SubscriptionManagementEntryDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void SubscriptionManagementEntryDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void SubscriptionManagementEntryDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool SubscriptionManagementEntryDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool SubscriptionManagementEntryDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"subscriptionId", "clientAddress", "serverAddress", "label",
                   "description"})) {
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
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SubscriptionManagementEntryDataElements::toJson() const {
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
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram