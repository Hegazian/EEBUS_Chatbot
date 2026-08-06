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

#include <keo_datagram/core/NetworkManagementScanNetworkCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementScanNetworkCall::NetworkManagementScanNetworkCall()
    : CmdData(), m_scanSetupIsSet(false), m_scanSetup(""),
      m_timeoutIsSet(false), m_timeout(xs_duration())

{}

NetworkManagementScanNetworkCall::NetworkManagementScanNetworkCall(
    const xs_string &c_scanSetup, const xs_duration &c_timeout)
    : CmdData(), m_scanSetupIsSet(true), m_scanSetup(c_scanSetup),
      m_timeoutIsSet(true), m_timeout(c_timeout)

{}

bool NetworkManagementScanNetworkCall::
operator==(const NetworkManagementScanNetworkCall &c_classObject) const {
  if (m_scanSetupIsSet != c_classObject.m_scanSetupIsSet ||
      (m_scanSetupIsSet && (m_scanSetup != c_classObject.m_scanSetup))) {
    return false;
  }
  if (m_timeoutIsSet != c_classObject.m_timeoutIsSet ||
      (m_timeoutIsSet && (m_timeout != c_classObject.m_timeout))) {
    return false;
  }

  return true;
}

bool NetworkManagementScanNetworkCall::
operator!=(const NetworkManagementScanNetworkCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementScanNetworkCall::isEmpty() const {
  return !m_scanSetupIsSet && !m_timeoutIsSet;
}

CmdData::Type NetworkManagementScanNetworkCall::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_TYPE;
}

CmdDataPtr NetworkManagementScanNetworkCall::clone() const {
  return std::make_shared<NetworkManagementScanNetworkCall>(*this);
}

void NetworkManagementScanNetworkCall::setScanSetup(
    const xs_string &scanSetup) {
  m_scanSetup = scanSetup;
  m_scanSetupIsSet = true;
}

const xs_string &NetworkManagementScanNetworkCall::getScanSetup() const {
  return m_scanSetup;
}

void NetworkManagementScanNetworkCall::cleanScanSetup() {
  m_scanSetup = "";
  m_scanSetupIsSet = false;
}

bool NetworkManagementScanNetworkCall::getScanSetupIsSet() const {
  return m_scanSetupIsSet;
}

void NetworkManagementScanNetworkCall::setTimeout(const xs_duration &timeout) {
  m_timeout = timeout;
  m_timeoutIsSet = true;
}

const xs_duration &NetworkManagementScanNetworkCall::getTimeout() const {
  return m_timeout;
}

void NetworkManagementScanNetworkCall::cleanTimeout() {
  m_timeout = xs_duration();
  m_timeoutIsSet = false;
}

bool NetworkManagementScanNetworkCall::getTimeoutIsSet() const {
  return m_timeoutIsSet;
}

CmdDataPtr NetworkManagementScanNetworkCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementScanNetworkCall>(*this);
}

bool NetworkManagementScanNetworkCall::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"scanSetup", "timeout"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scanSetup", &m_scanSetup)) {
      m_scanSetupIsSet = true;
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

std::string NetworkManagementScanNetworkCall::toJson() const {
  std::string result = "[";
  if (m_scanSetupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scanSetup", m_scanSetup);
  }
  if (m_timeoutIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeout", m_timeout);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram