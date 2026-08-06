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

#include <keo_datagram/core/NetworkManagementRemoveNodeCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementRemoveNodeCallElements::
    NetworkManagementRemoveNodeCallElements()
    : DataElements(), m_nodeAddressIsSet(false),
      m_nodeAddress(FeatureAddressElements()), m_timeoutIsSet(false)

{}

NetworkManagementRemoveNodeCallElements::
    NetworkManagementRemoveNodeCallElements(
        const FeatureAddressElements &c_nodeAddress, xs_boolean c_timeoutIsSet)
    : DataElements(), m_nodeAddressIsSet(true), m_nodeAddress(c_nodeAddress),
      m_timeoutIsSet(c_timeoutIsSet)

{}

bool NetworkManagementRemoveNodeCallElements::
operator==(const NetworkManagementRemoveNodeCallElements &c_classObject) const {
  if (m_nodeAddressIsSet != c_classObject.m_nodeAddressIsSet ||
      (m_nodeAddressIsSet && (m_nodeAddress != c_classObject.m_nodeAddress))) {
    return false;
  }
  if (m_timeoutIsSet != c_classObject.m_timeoutIsSet) {
    return false;
  }

  return true;
}

bool NetworkManagementRemoveNodeCallElements::
operator!=(const NetworkManagementRemoveNodeCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementRemoveNodeCallElements::isEmpty() const {
  return !m_nodeAddressIsSet && !m_timeoutIsSet;
}

DataElements::Type
NetworkManagementRemoveNodeCallElements::getDataType() const {
  return DataElements::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementRemoveNodeCallElements::clone() const {
  return std::make_shared<NetworkManagementRemoveNodeCallElements>(*this);
}

void NetworkManagementRemoveNodeCallElements::setNodeAddress(
    const FeatureAddressElements &nodeAddress) {
  m_nodeAddress = nodeAddress;
  m_nodeAddressIsSet = true;
}

const FeatureAddressElements &
NetworkManagementRemoveNodeCallElements::getNodeAddress() const {
  return m_nodeAddress;
}

void NetworkManagementRemoveNodeCallElements::cleanNodeAddress() {
  m_nodeAddress = FeatureAddressElements();
  m_nodeAddressIsSet = false;
}

bool NetworkManagementRemoveNodeCallElements::getNodeAddressIsSet() const {
  return m_nodeAddressIsSet;
}

void NetworkManagementRemoveNodeCallElements::setTimeout() {
  m_timeoutIsSet = true;
}

void NetworkManagementRemoveNodeCallElements::cleanTimeout() {
  m_timeoutIsSet = false;
}

bool NetworkManagementRemoveNodeCallElements::getTimeoutIsSet() const {
  return m_timeoutIsSet;
}

bool NetworkManagementRemoveNodeCallElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"nodeAddress", "timeout"})) {
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
                                     "timeout")) {
      m_timeoutIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementRemoveNodeCallElements::toJson() const {
  std::string result = "[";
  if (m_nodeAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nodeAddress", m_nodeAddress);
  }
  if (m_timeoutIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeout");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram