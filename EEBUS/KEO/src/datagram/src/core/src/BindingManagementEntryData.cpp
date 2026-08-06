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

#include <keo_datagram/core/BindingManagementEntryData.h>

#include <keo_datagram/core/BindingManagementEntryDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BindingManagementEntryData::BindingManagementEntryData()
    : m_bindingIdIsSet(false), m_bindingId(0), m_clientAddressIsSet(false),
      m_clientAddress(FeatureAddress()), m_serverAddressIsSet(false),
      m_serverAddress(FeatureAddress()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool BindingManagementEntryData::
operator==(const BindingManagementEntryData &c_classObject) const {
  if (m_bindingIdIsSet != c_classObject.m_bindingIdIsSet ||
      (m_bindingIdIsSet && (m_bindingId != c_classObject.m_bindingId))) {
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
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool BindingManagementEntryData::
operator!=(const BindingManagementEntryData &c_classObject) const {
  return !(*this == c_classObject);
}

bool BindingManagementEntryData::isEmpty() const {
  return !m_bindingIdIsSet && !m_clientAddressIsSet && !m_serverAddressIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

void BindingManagementEntryData::setBindingId(const xs_unsignedInt &bindingId) {
  m_bindingId = bindingId;
  m_bindingIdIsSet = true;
}

const xs_unsignedInt &BindingManagementEntryData::getBindingId() const {
  return m_bindingId;
}

void BindingManagementEntryData::cleanBindingId() {
  m_bindingId = 0;
  m_bindingIdIsSet = false;
}

bool BindingManagementEntryData::getBindingIdIsSet() const {
  return m_bindingIdIsSet;
}

void BindingManagementEntryData::setClientAddress(
    const FeatureAddress &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddress &BindingManagementEntryData::getClientAddress() const {
  return m_clientAddress;
}

void BindingManagementEntryData::cleanClientAddress() {
  m_clientAddress = FeatureAddress();
  m_clientAddressIsSet = false;
}

bool BindingManagementEntryData::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void BindingManagementEntryData::setServerAddress(
    const FeatureAddress &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddress &BindingManagementEntryData::getServerAddress() const {
  return m_serverAddress;
}

void BindingManagementEntryData::cleanServerAddress() {
  m_serverAddress = FeatureAddress();
  m_serverAddressIsSet = false;
}

bool BindingManagementEntryData::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

void BindingManagementEntryData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &BindingManagementEntryData::getLabel() const {
  return m_label;
}

void BindingManagementEntryData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool BindingManagementEntryData::getLabelIsSet() const { return m_labelIsSet; }

void BindingManagementEntryData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &BindingManagementEntryData::getDescription() const {
  return m_description;
}

void BindingManagementEntryData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool BindingManagementEntryData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

BindingManagementEntryData BindingManagementEntryData::reduce(
    const BindingManagementEntryDataElements &elements) const {
  BindingManagementEntryData dataOut;
  if (getBindingIdIsSet() && elements.getBindingIdIsSet()) {
    dataOut.setBindingId(getBindingId());
  }
  if (getClientAddressIsSet() && elements.getClientAddressIsSet()) {
    dataOut.setClientAddress(
        getClientAddress().reduce(elements.getClientAddress()));
  }
  if (getServerAddressIsSet() && elements.getServerAddressIsSet()) {
    dataOut.setServerAddress(
        getServerAddress().reduce(elements.getServerAddress()));
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool BindingManagementEntryData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"bindingId", "clientAddress", "serverAddress", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "bindingId", &m_bindingId)) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BindingManagementEntryData::toJson() const {
  std::string result = "[";
  if (m_bindingIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("bindingId", m_bindingId);
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
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram