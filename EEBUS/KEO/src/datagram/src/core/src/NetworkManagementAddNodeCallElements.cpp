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

#include <keo_datagram/core/NetworkManagementAddNodeCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementAddNodeCallElements::NetworkManagementAddNodeCallElements()
    : DataElements(), m_nodeAddressIsSet(false),
      m_nodeAddress(FeatureAddressElements()), m_nativeSetupIsSet(false),
      m_timeoutIsSet(false), m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool NetworkManagementAddNodeCallElements::
operator==(const NetworkManagementAddNodeCallElements &c_classObject) const {
  if (m_nodeAddressIsSet != c_classObject.m_nodeAddressIsSet ||
      (m_nodeAddressIsSet && (m_nodeAddress != c_classObject.m_nodeAddress))) {
    return false;
  }
  if (m_nativeSetupIsSet != c_classObject.m_nativeSetupIsSet) {
    return false;
  }
  if (m_timeoutIsSet != c_classObject.m_timeoutIsSet) {
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

bool NetworkManagementAddNodeCallElements::
operator!=(const NetworkManagementAddNodeCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementAddNodeCallElements::isEmpty() const {
  return !m_nodeAddressIsSet && !m_nativeSetupIsSet && !m_timeoutIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type NetworkManagementAddNodeCallElements::getDataType() const {
  return DataElements::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementAddNodeCallElements::clone() const {
  return std::make_shared<NetworkManagementAddNodeCallElements>(*this);
}

void NetworkManagementAddNodeCallElements::setNodeAddress(
    const FeatureAddressElements &nodeAddress) {
  m_nodeAddress = nodeAddress;
  m_nodeAddressIsSet = true;
}

const FeatureAddressElements &
NetworkManagementAddNodeCallElements::getNodeAddress() const {
  return m_nodeAddress;
}

void NetworkManagementAddNodeCallElements::cleanNodeAddress() {
  m_nodeAddress = FeatureAddressElements();
  m_nodeAddressIsSet = false;
}

bool NetworkManagementAddNodeCallElements::getNodeAddressIsSet() const {
  return m_nodeAddressIsSet;
}

void NetworkManagementAddNodeCallElements::setNativeSetup() {
  m_nativeSetupIsSet = true;
}

void NetworkManagementAddNodeCallElements::cleanNativeSetup() {
  m_nativeSetupIsSet = false;
}

bool NetworkManagementAddNodeCallElements::getNativeSetupIsSet() const {
  return m_nativeSetupIsSet;
}

void NetworkManagementAddNodeCallElements::setTimeout() {
  m_timeoutIsSet = true;
}

void NetworkManagementAddNodeCallElements::cleanTimeout() {
  m_timeoutIsSet = false;
}

bool NetworkManagementAddNodeCallElements::getTimeoutIsSet() const {
  return m_timeoutIsSet;
}

void NetworkManagementAddNodeCallElements::setLabel() { m_labelIsSet = true; }

void NetworkManagementAddNodeCallElements::cleanLabel() {
  m_labelIsSet = false;
}

bool NetworkManagementAddNodeCallElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementAddNodeCallElements::setDescription() {
  m_descriptionIsSet = true;
}

void NetworkManagementAddNodeCallElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool NetworkManagementAddNodeCallElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool NetworkManagementAddNodeCallElements::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "nativeSetup")) {
      m_nativeSetupIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeout")) {
      m_timeoutIsSet = true;
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

std::string NetworkManagementAddNodeCallElements::toJson() const {
  std::string result = "[";
  if (m_nodeAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nodeAddress", m_nodeAddress);
  }
  if (m_nativeSetupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("nativeSetup");
  }
  if (m_timeoutIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeout");
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