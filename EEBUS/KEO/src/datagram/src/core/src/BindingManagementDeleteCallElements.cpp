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

#include <keo_datagram/core/BindingManagementDeleteCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BindingManagementDeleteCallElements::BindingManagementDeleteCallElements()
    : DataElements(), m_bindingIdIsSet(false), m_clientAddressIsSet(false),
      m_clientAddress(FeatureAddressElements()), m_serverAddressIsSet(false),
      m_serverAddress(FeatureAddressElements())

{}

BindingManagementDeleteCallElements::BindingManagementDeleteCallElements(
    xs_boolean c_bindingIdIsSet, const FeatureAddressElements &c_clientAddress,
    const FeatureAddressElements &c_serverAddress)
    : DataElements(), m_bindingIdIsSet(c_bindingIdIsSet),
      m_clientAddressIsSet(true), m_clientAddress(c_clientAddress),
      m_serverAddressIsSet(true), m_serverAddress(c_serverAddress)

{}

bool BindingManagementDeleteCallElements::
operator==(const BindingManagementDeleteCallElements &c_classObject) const {
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

  return true;
}

bool BindingManagementDeleteCallElements::
operator!=(const BindingManagementDeleteCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool BindingManagementDeleteCallElements::isEmpty() const {
  return !m_bindingIdIsSet && !m_clientAddressIsSet && !m_serverAddressIsSet;
}

DataElements::Type BindingManagementDeleteCallElements::getDataType() const {
  return DataElements::Type::BINDING_MANAGEMENT_DELETE_CALL_ELEMENTS_TYPE;
}

DataElementsPtr BindingManagementDeleteCallElements::clone() const {
  return std::make_shared<BindingManagementDeleteCallElements>(*this);
}

void BindingManagementDeleteCallElements::setBindingId() {
  m_bindingIdIsSet = true;
}

void BindingManagementDeleteCallElements::cleanBindingId() {
  m_bindingIdIsSet = false;
}

bool BindingManagementDeleteCallElements::getBindingIdIsSet() const {
  return m_bindingIdIsSet;
}

void BindingManagementDeleteCallElements::setClientAddress(
    const FeatureAddressElements &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddressElements &
BindingManagementDeleteCallElements::getClientAddress() const {
  return m_clientAddress;
}

void BindingManagementDeleteCallElements::cleanClientAddress() {
  m_clientAddress = FeatureAddressElements();
  m_clientAddressIsSet = false;
}

bool BindingManagementDeleteCallElements::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void BindingManagementDeleteCallElements::setServerAddress(
    const FeatureAddressElements &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddressElements &
BindingManagementDeleteCallElements::getServerAddress() const {
  return m_serverAddress;
}

void BindingManagementDeleteCallElements::cleanServerAddress() {
  m_serverAddress = FeatureAddressElements();
  m_serverAddressIsSet = false;
}

bool BindingManagementDeleteCallElements::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

bool BindingManagementDeleteCallElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"bindingId", "clientAddress", "serverAddress"})) {
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
  }
  return true;
}

std::string BindingManagementDeleteCallElements::toJson() const {
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
  result += "]";
  return result;
}

} // namespace keo_datagram