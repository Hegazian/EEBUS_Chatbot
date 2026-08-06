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

#include <keo_datagram/core/NetworkManagementDiscoverCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementDiscoverCall::NetworkManagementDiscoverCall()
    : CmdData(), m_discoverAddressIsSet(false),
      m_discoverAddress(FeatureAddress())

{}

NetworkManagementDiscoverCall::NetworkManagementDiscoverCall(
    const FeatureAddress &c_discoverAddress) {
  setDiscoverAddress(c_discoverAddress);
}

bool NetworkManagementDiscoverCall::
operator==(const NetworkManagementDiscoverCall &c_classObject) const {
  if (m_discoverAddressIsSet != c_classObject.m_discoverAddressIsSet ||
      (m_discoverAddressIsSet &&
       (m_discoverAddress != c_classObject.m_discoverAddress))) {
    return false;
  }

  return true;
}

bool NetworkManagementDiscoverCall::
operator!=(const NetworkManagementDiscoverCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementDiscoverCall::isEmpty() const {
  return !m_discoverAddressIsSet;
}

CmdData::Type NetworkManagementDiscoverCall::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_TYPE;
}

CmdDataPtr NetworkManagementDiscoverCall::clone() const {
  return std::make_shared<NetworkManagementDiscoverCall>(*this);
}

void NetworkManagementDiscoverCall::setDiscoverAddress(
    const FeatureAddress &discoverAddress) {
  m_discoverAddress = discoverAddress;
  m_discoverAddressIsSet = true;
}

const FeatureAddress &
NetworkManagementDiscoverCall::getDiscoverAddress() const {
  return m_discoverAddress;
}

void NetworkManagementDiscoverCall::cleanDiscoverAddress() {
  m_discoverAddress = FeatureAddress();
  m_discoverAddressIsSet = false;
}

bool NetworkManagementDiscoverCall::getDiscoverAddressIsSet() const {
  return m_discoverAddressIsSet;
}

CmdDataPtr NetworkManagementDiscoverCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementDiscoverCall>(*this);
}

bool NetworkManagementDiscoverCall::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"discoverAddress"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "discoverAddress", &m_discoverAddress)) {
      m_discoverAddressIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementDiscoverCall::toJson() const {
  std::string result = "[";
  if (m_discoverAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("discoverAddress", m_discoverAddress);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram