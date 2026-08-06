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

#include <keo_datagram/core/BindingManagementEntryListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BindingManagementEntryListDataSelectors::
    BindingManagementEntryListDataSelectors()
    : DataSelectors(), m_bindingIdIsSet(false), m_bindingId(0),
      m_clientAddressIsSet(false), m_clientAddress(FeatureAddress()),
      m_serverAddressIsSet(false), m_serverAddress(FeatureAddress())

{}

BindingManagementEntryListDataSelectors::
    BindingManagementEntryListDataSelectors(
        const xs_unsignedInt &c_bindingId,
        const FeatureAddress &c_clientAddress,
        const FeatureAddress &c_serverAddress)
    : DataSelectors(), m_bindingIdIsSet(true), m_bindingId(c_bindingId),
      m_clientAddressIsSet(true), m_clientAddress(c_clientAddress),
      m_serverAddressIsSet(true), m_serverAddress(c_serverAddress)

{}

bool BindingManagementEntryListDataSelectors::
operator==(const BindingManagementEntryListDataSelectors &c_classObject) const {
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

  return true;
}

bool BindingManagementEntryListDataSelectors::
operator!=(const BindingManagementEntryListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool BindingManagementEntryListDataSelectors::isEmpty() const {
  return !m_bindingIdIsSet && !m_clientAddressIsSet && !m_serverAddressIsSet;
}

DataSelectors::Type
BindingManagementEntryListDataSelectors::getDataType() const {
  return DataSelectors::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr BindingManagementEntryListDataSelectors::clone() const {
  return std::make_shared<BindingManagementEntryListDataSelectors>(*this);
}

void BindingManagementEntryListDataSelectors::setBindingId(
    const xs_unsignedInt &bindingId) {
  m_bindingId = bindingId;
  m_bindingIdIsSet = true;
}

const xs_unsignedInt &
BindingManagementEntryListDataSelectors::getBindingId() const {
  return m_bindingId;
}

void BindingManagementEntryListDataSelectors::cleanBindingId() {
  m_bindingId = 0;
  m_bindingIdIsSet = false;
}

bool BindingManagementEntryListDataSelectors::getBindingIdIsSet() const {
  return m_bindingIdIsSet;
}

void BindingManagementEntryListDataSelectors::setClientAddress(
    const FeatureAddress &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddress &
BindingManagementEntryListDataSelectors::getClientAddress() const {
  return m_clientAddress;
}

void BindingManagementEntryListDataSelectors::cleanClientAddress() {
  m_clientAddress = FeatureAddress();
  m_clientAddressIsSet = false;
}

bool BindingManagementEntryListDataSelectors::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void BindingManagementEntryListDataSelectors::setServerAddress(
    const FeatureAddress &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddress &
BindingManagementEntryListDataSelectors::getServerAddress() const {
  return m_serverAddress;
}

void BindingManagementEntryListDataSelectors::cleanServerAddress() {
  m_serverAddress = FeatureAddress();
  m_serverAddressIsSet = false;
}

bool BindingManagementEntryListDataSelectors::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

bool BindingManagementEntryListDataSelectors::selects(
    const BindingManagementEntryData &data) const {
  if (getBindingIdIsSet() &&
      (!data.getBindingIdIsSet() || getBindingId() != data.getBindingId())) {
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

bool BindingManagementEntryListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"bindingId", "clientAddress", "serverAddress"})) {
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
  }
  return true;
}

std::string BindingManagementEntryListDataSelectors::toJson() const {
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
  result += "]";
  return result;
}

} // namespace keo_datagram