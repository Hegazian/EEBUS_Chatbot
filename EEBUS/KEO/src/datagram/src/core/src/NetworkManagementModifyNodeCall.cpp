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

#include <keo_datagram/core/NetworkManagementModifyNodeCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementModifyNodeCall::NetworkManagementModifyNodeCall()
    : CmdData(), m_nodeAddressIsSet(false), m_nodeAddress(FeatureAddress()),
      m_nativeSetupIsSet(false), m_nativeSetup(""), m_timeoutIsSet(false),
      m_timeout(xs_duration()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool NetworkManagementModifyNodeCall::
operator==(const NetworkManagementModifyNodeCall &c_classObject) const {
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

bool NetworkManagementModifyNodeCall::
operator!=(const NetworkManagementModifyNodeCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementModifyNodeCall::isEmpty() const {
  return !m_nodeAddressIsSet && !m_nativeSetupIsSet && !m_timeoutIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

CmdData::Type NetworkManagementModifyNodeCall::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_TYPE;
}

CmdDataPtr NetworkManagementModifyNodeCall::clone() const {
  return std::make_shared<NetworkManagementModifyNodeCall>(*this);
}

void NetworkManagementModifyNodeCall::setNodeAddress(
    const FeatureAddress &nodeAddress) {
  m_nodeAddress = nodeAddress;
  m_nodeAddressIsSet = true;
}

const FeatureAddress &NetworkManagementModifyNodeCall::getNodeAddress() const {
  return m_nodeAddress;
}

void NetworkManagementModifyNodeCall::cleanNodeAddress() {
  m_nodeAddress = FeatureAddress();
  m_nodeAddressIsSet = false;
}

bool NetworkManagementModifyNodeCall::getNodeAddressIsSet() const {
  return m_nodeAddressIsSet;
}

void NetworkManagementModifyNodeCall::setNativeSetup(
    const xs_string &nativeSetup) {
  m_nativeSetup = nativeSetup;
  m_nativeSetupIsSet = true;
}

const xs_string &NetworkManagementModifyNodeCall::getNativeSetup() const {
  return m_nativeSetup;
}

void NetworkManagementModifyNodeCall::cleanNativeSetup() {
  m_nativeSetup = "";
  m_nativeSetupIsSet = false;
}

bool NetworkManagementModifyNodeCall::getNativeSetupIsSet() const {
  return m_nativeSetupIsSet;
}

void NetworkManagementModifyNodeCall::setTimeout(const xs_duration &timeout) {
  m_timeout = timeout;
  m_timeoutIsSet = true;
}

const xs_duration &NetworkManagementModifyNodeCall::getTimeout() const {
  return m_timeout;
}

void NetworkManagementModifyNodeCall::cleanTimeout() {
  m_timeout = xs_duration();
  m_timeoutIsSet = false;
}

bool NetworkManagementModifyNodeCall::getTimeoutIsSet() const {
  return m_timeoutIsSet;
}

void NetworkManagementModifyNodeCall::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &NetworkManagementModifyNodeCall::getLabel() const {
  return m_label;
}

void NetworkManagementModifyNodeCall::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool NetworkManagementModifyNodeCall::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementModifyNodeCall::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &NetworkManagementModifyNodeCall::getDescription() const {
  return m_description;
}

void NetworkManagementModifyNodeCall::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool NetworkManagementModifyNodeCall::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

CmdDataPtr NetworkManagementModifyNodeCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementModifyNodeCall>(*this);
}

bool NetworkManagementModifyNodeCall::fromJson(KeoJsonValue *json) {
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

std::string NetworkManagementModifyNodeCall::toJson() const {
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