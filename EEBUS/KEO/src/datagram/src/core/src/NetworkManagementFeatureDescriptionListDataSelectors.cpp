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

#include <keo_datagram/core/NetworkManagementFeatureDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementFeatureDescriptionListDataSelectors::
    NetworkManagementFeatureDescriptionListDataSelectors()
    : DataSelectors(), m_featureAddressIsSet(false),
      m_featureAddress(FeatureAddress()), m_featureTypeIsSet(false),
      m_featureType(FeatureType())

{}

NetworkManagementFeatureDescriptionListDataSelectors::
    NetworkManagementFeatureDescriptionListDataSelectors(
        const FeatureAddress &c_featureAddress,
        const FeatureType &c_featureType)
    : DataSelectors(), m_featureAddressIsSet(true),
      m_featureAddress(c_featureAddress), m_featureTypeIsSet(true),
      m_featureType(c_featureType)

{}

bool NetworkManagementFeatureDescriptionListDataSelectors::operator==(
    const NetworkManagementFeatureDescriptionListDataSelectors &c_classObject)
    const {
  if (m_featureAddressIsSet != c_classObject.m_featureAddressIsSet ||
      (m_featureAddressIsSet &&
       (m_featureAddress != c_classObject.m_featureAddress))) {
    return false;
  }
  if (m_featureTypeIsSet != c_classObject.m_featureTypeIsSet ||
      (m_featureTypeIsSet && (m_featureType != c_classObject.m_featureType))) {
    return false;
  }

  return true;
}

bool NetworkManagementFeatureDescriptionListDataSelectors::operator!=(
    const NetworkManagementFeatureDescriptionListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool NetworkManagementFeatureDescriptionListDataSelectors::isEmpty() const {
  return !m_featureAddressIsSet && !m_featureTypeIsSet;
}

DataSelectors::Type
NetworkManagementFeatureDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
NetworkManagementFeatureDescriptionListDataSelectors::clone() const {
  return std::make_shared<NetworkManagementFeatureDescriptionListDataSelectors>(
      *this);
}

void NetworkManagementFeatureDescriptionListDataSelectors::setFeatureAddress(
    const FeatureAddress &featureAddress) {
  m_featureAddress = featureAddress;
  m_featureAddressIsSet = true;
}

const FeatureAddress &
NetworkManagementFeatureDescriptionListDataSelectors::getFeatureAddress()
    const {
  return m_featureAddress;
}

void NetworkManagementFeatureDescriptionListDataSelectors::
    cleanFeatureAddress() {
  m_featureAddress = FeatureAddress();
  m_featureAddressIsSet = false;
}

bool NetworkManagementFeatureDescriptionListDataSelectors::
    getFeatureAddressIsSet() const {
  return m_featureAddressIsSet;
}

void NetworkManagementFeatureDescriptionListDataSelectors::setFeatureType(
    const FeatureType &featureType) {
  m_featureType = featureType;
  m_featureTypeIsSet = true;
}

const FeatureType &
NetworkManagementFeatureDescriptionListDataSelectors::getFeatureType() const {
  return m_featureType;
}

void NetworkManagementFeatureDescriptionListDataSelectors::cleanFeatureType() {
  m_featureType = FeatureType();
  m_featureTypeIsSet = false;
}

bool NetworkManagementFeatureDescriptionListDataSelectors::getFeatureTypeIsSet()
    const {
  return m_featureTypeIsSet;
}

bool NetworkManagementFeatureDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"featureAddress", "featureType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "featureAddress", &m_featureAddress)) {
      m_featureAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "featureType", &m_featureType)) {
      m_featureTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
NetworkManagementFeatureDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_featureAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("featureAddress", m_featureAddress);
  }
  if (m_featureTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("featureType", m_featureType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram