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

#include <keo_datagram/core/NetworkManagementRemoveNodeCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementRemoveNodeCall::NetworkManagementRemoveNodeCall()
    : CmdData(), m_nodeAddressIsSet(false), m_nodeAddress(FeatureAddress()),
      m_timeoutIsSet(false), m_timeout(xs_duration())

{}

NetworkManagementRemoveNodeCall::NetworkManagementRemoveNodeCall(
    const FeatureAddress &c_nodeAddress, const xs_duration &c_timeout)
    : CmdData(), m_nodeAddressIsSet(true), m_nodeAddress(c_nodeAddress),
      m_timeoutIsSet(true), m_timeout(c_timeout)

{}

bool NetworkManagementRemoveNodeCall::
operator==(const NetworkManagementRemoveNodeCall &c_classObject) const {
  if (m_nodeAddressIsSet != c_classObject.m_nodeAddressIsSet ||
      (m_nodeAddressIsSet && (m_nodeAddress != c_classObject.m_nodeAddress))) {
    return false;
  }
  if (m_timeoutIsSet != c_classObject.m_timeoutIsSet ||
      (m_timeoutIsSet && (m_timeout != c_classObject.m_timeout))) {
    return false;
  }

  return true;
}

bool NetworkManagementRemoveNodeCall::
operator!=(const NetworkManagementRemoveNodeCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementRemoveNodeCall::isEmpty() const {
  return !m_nodeAddressIsSet && !m_timeoutIsSet;
}

CmdData::Type NetworkManagementRemoveNodeCall::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_TYPE;
}

CmdDataPtr NetworkManagementRemoveNodeCall::clone() const {
  return std::make_shared<NetworkManagementRemoveNodeCall>(*this);
}

void NetworkManagementRemoveNodeCall::setNodeAddress(
    const FeatureAddress &nodeAddress) {
  m_nodeAddress = nodeAddress;
  m_nodeAddressIsSet = true;
}

const FeatureAddress &NetworkManagementRemoveNodeCall::getNodeAddress() const {
  return m_nodeAddress;
}

void NetworkManagementRemoveNodeCall::cleanNodeAddress() {
  m_nodeAddress = FeatureAddress();
  m_nodeAddressIsSet = false;
}

bool NetworkManagementRemoveNodeCall::getNodeAddressIsSet() const {
  return m_nodeAddressIsSet;
}

void NetworkManagementRemoveNodeCall::setTimeout(const xs_duration &timeout) {
  m_timeout = timeout;
  m_timeoutIsSet = true;
}

const xs_duration &NetworkManagementRemoveNodeCall::getTimeout() const {
  return m_timeout;
}

void NetworkManagementRemoveNodeCall::cleanTimeout() {
  m_timeout = xs_duration();
  m_timeoutIsSet = false;
}

bool NetworkManagementRemoveNodeCall::getTimeoutIsSet() const {
  return m_timeoutIsSet;
}

CmdDataPtr NetworkManagementRemoveNodeCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementRemoveNodeCall>(*this);
}

bool NetworkManagementRemoveNodeCall::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeout", &m_timeout)) {
      m_timeoutIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementRemoveNodeCall::toJson() const {
  std::string result = "[";
  if (m_nodeAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nodeAddress", m_nodeAddress);
  }
  if (m_timeoutIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeout", m_timeout);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram