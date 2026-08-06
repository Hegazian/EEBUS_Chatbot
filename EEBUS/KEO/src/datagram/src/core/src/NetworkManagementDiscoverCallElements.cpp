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

#include <keo_datagram/core/NetworkManagementDiscoverCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementDiscoverCallElements::NetworkManagementDiscoverCallElements()
    : DataElements(), m_discoverAddressIsSet(false),
      m_discoverAddress(FeatureAddressElements())

{}

NetworkManagementDiscoverCallElements::NetworkManagementDiscoverCallElements(
    const FeatureAddressElements &c_discoverAddress) {
  setDiscoverAddress(c_discoverAddress);
}

bool NetworkManagementDiscoverCallElements::
operator==(const NetworkManagementDiscoverCallElements &c_classObject) const {
  if (m_discoverAddressIsSet != c_classObject.m_discoverAddressIsSet ||
      (m_discoverAddressIsSet &&
       (m_discoverAddress != c_classObject.m_discoverAddress))) {
    return false;
  }

  return true;
}

bool NetworkManagementDiscoverCallElements::
operator!=(const NetworkManagementDiscoverCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementDiscoverCallElements::isEmpty() const {
  return !m_discoverAddressIsSet;
}

DataElements::Type NetworkManagementDiscoverCallElements::getDataType() const {
  return DataElements::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementDiscoverCallElements::clone() const {
  return std::make_shared<NetworkManagementDiscoverCallElements>(*this);
}

void NetworkManagementDiscoverCallElements::setDiscoverAddress(
    const FeatureAddressElements &discoverAddress) {
  m_discoverAddress = discoverAddress;
  m_discoverAddressIsSet = true;
}

const FeatureAddressElements &
NetworkManagementDiscoverCallElements::getDiscoverAddress() const {
  return m_discoverAddress;
}

void NetworkManagementDiscoverCallElements::cleanDiscoverAddress() {
  m_discoverAddress = FeatureAddressElements();
  m_discoverAddressIsSet = false;
}

bool NetworkManagementDiscoverCallElements::getDiscoverAddressIsSet() const {
  return m_discoverAddressIsSet;
}

bool NetworkManagementDiscoverCallElements::fromJson(KeoJsonValue *json) {
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

std::string NetworkManagementDiscoverCallElements::toJson() const {
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