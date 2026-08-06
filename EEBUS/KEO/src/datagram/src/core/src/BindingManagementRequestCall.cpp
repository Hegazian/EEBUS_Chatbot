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

#include <keo_datagram/core/BindingManagementRequestCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BindingManagementRequestCall::BindingManagementRequestCall()
    : CmdData(), m_clientAddressIsSet(false), m_clientAddress(FeatureAddress()),
      m_serverAddressIsSet(false), m_serverAddress(FeatureAddress()),
      m_serverFeatureTypeIsSet(false), m_serverFeatureType(FeatureType())

{}

BindingManagementRequestCall::BindingManagementRequestCall(
    const FeatureAddress &c_clientAddress,
    const FeatureAddress &c_serverAddress,
    const FeatureType &c_serverFeatureType)
    : CmdData(), m_clientAddressIsSet(true), m_clientAddress(c_clientAddress),
      m_serverAddressIsSet(true), m_serverAddress(c_serverAddress),
      m_serverFeatureTypeIsSet(true), m_serverFeatureType(c_serverFeatureType)

{}

bool BindingManagementRequestCall::
operator==(const BindingManagementRequestCall &c_classObject) const {
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
  if (m_serverFeatureTypeIsSet != c_classObject.m_serverFeatureTypeIsSet ||
      (m_serverFeatureTypeIsSet &&
       (m_serverFeatureType != c_classObject.m_serverFeatureType))) {
    return false;
  }

  return true;
}

bool BindingManagementRequestCall::
operator!=(const BindingManagementRequestCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool BindingManagementRequestCall::isEmpty() const {
  return !m_clientAddressIsSet && !m_serverAddressIsSet &&
         !m_serverFeatureTypeIsSet;
}

CmdData::Type BindingManagementRequestCall::getDataType() const {
  return CmdData::Type::BINDING_MANAGEMENT_REQUEST_CALL_TYPE;
}

CmdDataPtr BindingManagementRequestCall::clone() const {
  return std::make_shared<BindingManagementRequestCall>(*this);
}

void BindingManagementRequestCall::setClientAddress(
    const FeatureAddress &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddress &BindingManagementRequestCall::getClientAddress() const {
  return m_clientAddress;
}

void BindingManagementRequestCall::cleanClientAddress() {
  m_clientAddress = FeatureAddress();
  m_clientAddressIsSet = false;
}

bool BindingManagementRequestCall::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void BindingManagementRequestCall::setServerAddress(
    const FeatureAddress &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddress &BindingManagementRequestCall::getServerAddress() const {
  return m_serverAddress;
}

void BindingManagementRequestCall::cleanServerAddress() {
  m_serverAddress = FeatureAddress();
  m_serverAddressIsSet = false;
}

bool BindingManagementRequestCall::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

void BindingManagementRequestCall::setServerFeatureType(
    const FeatureType &serverFeatureType) {
  m_serverFeatureType = serverFeatureType;
  m_serverFeatureTypeIsSet = true;
}

const FeatureType &BindingManagementRequestCall::getServerFeatureType() const {
  return m_serverFeatureType;
}

void BindingManagementRequestCall::cleanServerFeatureType() {
  m_serverFeatureType = FeatureType();
  m_serverFeatureTypeIsSet = false;
}

bool BindingManagementRequestCall::getServerFeatureTypeIsSet() const {
  return m_serverFeatureTypeIsSet;
}

CmdDataPtr
BindingManagementRequestCall::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<BindingManagementRequestCall>(*this);
}

bool BindingManagementRequestCall::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "serverFeatureType", &m_serverFeatureType)) {
      m_serverFeatureTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BindingManagementRequestCall::toJson() const {
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
    result +=
        KeoJsonTransformation::write("serverFeatureType", m_serverFeatureType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram