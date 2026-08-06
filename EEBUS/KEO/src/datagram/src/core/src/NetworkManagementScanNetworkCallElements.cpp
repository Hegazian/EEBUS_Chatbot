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

#include <keo_datagram/core/NetworkManagementScanNetworkCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementScanNetworkCallElements::
    NetworkManagementScanNetworkCallElements()
    : DataElements(), m_scanSetupIsSet(false), m_timeoutIsSet(false)

{}

NetworkManagementScanNetworkCallElements::
    NetworkManagementScanNetworkCallElements(xs_boolean c_scanSetupIsSet,
                                             xs_boolean c_timeoutIsSet)
    : DataElements(), m_scanSetupIsSet(c_scanSetupIsSet),
      m_timeoutIsSet(c_timeoutIsSet)

{}

bool NetworkManagementScanNetworkCallElements::operator==(
    const NetworkManagementScanNetworkCallElements &c_classObject) const {
  if (m_scanSetupIsSet != c_classObject.m_scanSetupIsSet) {
    return false;
  }
  if (m_timeoutIsSet != c_classObject.m_timeoutIsSet) {
    return false;
  }

  return true;
}

bool NetworkManagementScanNetworkCallElements::operator!=(
    const NetworkManagementScanNetworkCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementScanNetworkCallElements::isEmpty() const {
  return !m_scanSetupIsSet && !m_timeoutIsSet;
}

DataElements::Type
NetworkManagementScanNetworkCallElements::getDataType() const {
  return DataElements::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementScanNetworkCallElements::clone() const {
  return std::make_shared<NetworkManagementScanNetworkCallElements>(*this);
}

void NetworkManagementScanNetworkCallElements::setScanSetup() {
  m_scanSetupIsSet = true;
}

void NetworkManagementScanNetworkCallElements::cleanScanSetup() {
  m_scanSetupIsSet = false;
}

bool NetworkManagementScanNetworkCallElements::getScanSetupIsSet() const {
  return m_scanSetupIsSet;
}

void NetworkManagementScanNetworkCallElements::setTimeout() {
  m_timeoutIsSet = true;
}

void NetworkManagementScanNetworkCallElements::cleanTimeout() {
  m_timeoutIsSet = false;
}

bool NetworkManagementScanNetworkCallElements::getTimeoutIsSet() const {
  return m_timeoutIsSet;
}

bool NetworkManagementScanNetworkCallElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"scanSetup", "timeout"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scanSetup")) {
      m_scanSetupIsSet = true;
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

std::string NetworkManagementScanNetworkCallElements::toJson() const {
  std::string result = "[";
  if (m_scanSetupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scanSetup");
  }
  if (m_timeoutIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeout");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram