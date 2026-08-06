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

#include <keo_datagram/core/BindingManagementEntryDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BindingManagementEntryDataElements::BindingManagementEntryDataElements()
    : DataElements(), m_bindingIdIsSet(false), m_clientAddressIsSet(false),
      m_clientAddress(FeatureAddressElements()), m_serverAddressIsSet(false),
      m_serverAddress(FeatureAddressElements()), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool BindingManagementEntryDataElements::
operator==(const BindingManagementEntryDataElements &c_classObject) const {
  if (m_bindingIdIsSet != c_classObject.m_bindingIdIsSet) {
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

bool BindingManagementEntryDataElements::
operator!=(const BindingManagementEntryDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool BindingManagementEntryDataElements::isEmpty() const {
  return !m_bindingIdIsSet && !m_clientAddressIsSet && !m_serverAddressIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type BindingManagementEntryDataElements::getDataType() const {
  return DataElements::Type::BINDING_MANAGEMENT_ENTRY_DATA_ELEMENTS_TYPE;
}

DataElementsPtr BindingManagementEntryDataElements::clone() const {
  return std::make_shared<BindingManagementEntryDataElements>(*this);
}

void BindingManagementEntryDataElements::setBindingId() {
  m_bindingIdIsSet = true;
}

void BindingManagementEntryDataElements::cleanBindingId() {
  m_bindingIdIsSet = false;
}

bool BindingManagementEntryDataElements::getBindingIdIsSet() const {
  return m_bindingIdIsSet;
}

void BindingManagementEntryDataElements::setClientAddress(
    const FeatureAddressElements &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddressElements &
BindingManagementEntryDataElements::getClientAddress() const {
  return m_clientAddress;
}

void BindingManagementEntryDataElements::cleanClientAddress() {
  m_clientAddress = FeatureAddressElements();
  m_clientAddressIsSet = false;
}

bool BindingManagementEntryDataElements::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void BindingManagementEntryDataElements::setServerAddress(
    const FeatureAddressElements &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddressElements &
BindingManagementEntryDataElements::getServerAddress() const {
  return m_serverAddress;
}

void BindingManagementEntryDataElements::cleanServerAddress() {
  m_serverAddress = FeatureAddressElements();
  m_serverAddressIsSet = false;
}

bool BindingManagementEntryDataElements::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

void BindingManagementEntryDataElements::setLabel() { m_labelIsSet = true; }

void BindingManagementEntryDataElements::cleanLabel() { m_labelIsSet = false; }

bool BindingManagementEntryDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void BindingManagementEntryDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void BindingManagementEntryDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool BindingManagementEntryDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool BindingManagementEntryDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"bindingId", "clientAddress", "serverAddress", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "bindingId")) {
      m_bindingIdIsSet = true;
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

std::string BindingManagementEntryDataElements::toJson() const {
  std::string result = "[";
  if (m_bindingIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("bindingId");
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