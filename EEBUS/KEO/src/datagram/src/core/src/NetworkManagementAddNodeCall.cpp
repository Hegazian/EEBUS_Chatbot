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

#include <keo_datagram/core/NetworkManagementAddNodeCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementAddNodeCall::NetworkManagementAddNodeCall()
    : CmdData(), m_nodeAddressIsSet(false), m_nodeAddress(FeatureAddress()),
      m_nativeSetupIsSet(false), m_nativeSetup(""), m_timeoutIsSet(false),
      m_timeout(xs_duration()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool NetworkManagementAddNodeCall::
operator==(const NetworkManagementAddNodeCall &c_classObject) const {
  if (m_nodeAddressIsSet != c_classObject.m_nodeAddressIsSet ||
      (m_nodeAddressIsSet && (m_nodeAddress != c_classObject.m_nodeAddress))) {
    return false;
  }
  if (m_nativeSetupIsSet != c_classObject.m_nativeSetupIsSet ||
      (m_nativeSetupIsSet && (m_nativeSetup != c_classObject.m_nativeSetup))) {
    return false;
  }
  if (m_timeoutIsSet != c_classObject.m_timeoutIsSet ||
      (m_timeoutIsSet && (m_timeout != c_classObject.m_timeout))) {
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

bool NetworkManagementAddNodeCall::
operator!=(const NetworkManagementAddNodeCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementAddNodeCall::isEmpty() const {
  return !m_nodeAddressIsSet && !m_nativeSetupIsSet && !m_timeoutIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

CmdData::Type NetworkManagementAddNodeCall::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_TYPE;
}

CmdDataPtr NetworkManagementAddNodeCall::clone() const {
  return std::make_shared<NetworkManagementAddNodeCall>(*this);
}

void NetworkManagementAddNodeCall::setNodeAddress(
    const FeatureAddress &nodeAddress) {
  m_nodeAddress = nodeAddress;
  m_nodeAddressIsSet = true;
}

const FeatureAddress &NetworkManagementAddNodeCall::getNodeAddress() const {
  return m_nodeAddress;
}

void NetworkManagementAddNodeCall::cleanNodeAddress() {
  m_nodeAddress = FeatureAddress();
  m_nodeAddressIsSet = false;
}

bool NetworkManagementAddNodeCall::getNodeAddressIsSet() const {
  return m_nodeAddressIsSet;
}

void NetworkManagementAddNodeCall::setNativeSetup(
    const xs_string &nativeSetup) {
  m_nativeSetup = nativeSetup;
  m_nativeSetupIsSet = true;
}

const xs_string &NetworkManagementAddNodeCall::getNativeSetup() const {
  return m_nativeSetup;
}

void NetworkManagementAddNodeCall::cleanNativeSetup() {
  m_nativeSetup = "";
  m_nativeSetupIsSet = false;
}

bool NetworkManagementAddNodeCall::getNativeSetupIsSet() const {
  return m_nativeSetupIsSet;
}

void NetworkManagementAddNodeCall::setTimeout(const xs_duration &timeout) {
  m_timeout = timeout;
  m_timeoutIsSet = true;
}

const xs_duration &NetworkManagementAddNodeCall::getTimeout() const {
  return m_timeout;
}

void NetworkManagementAddNodeCall::cleanTimeout() {
  m_timeout = xs_duration();
  m_timeoutIsSet = false;
}

bool NetworkManagementAddNodeCall::getTimeoutIsSet() const {
  return m_timeoutIsSet;
}

void NetworkManagementAddNodeCall::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &NetworkManagementAddNodeCall::getLabel() const {
  return m_label;
}

void NetworkManagementAddNodeCall::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool NetworkManagementAddNodeCall::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementAddNodeCall::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &NetworkManagementAddNodeCall::getDescription() const {
  return m_description;
}

void NetworkManagementAddNodeCall::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool NetworkManagementAddNodeCall::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

CmdDataPtr
NetworkManagementAddNodeCall::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementAddNodeCall>(*this);
}

bool NetworkManagementAddNodeCall::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"nodeAddress", "nativeSetup", "timeout", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "nodeAddress", &m_nodeAddress)) {
      m_nodeAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "nativeSetup", &m_nativeSetup)) {
      m_nativeSetupIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeout", &m_timeout)) {
      m_timeoutIsSet = true;
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

std::string NetworkManagementAddNodeCall::toJson() const {
  std::string result = "[";
  if (m_nodeAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nodeAddress", m_nodeAddress);
  }
  if (m_nativeSetupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nativeSetup", m_nativeSetup);
  }
  if (m_timeoutIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeout", m_timeout);
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