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

#include <keo_datagram/core/NetworkManagementFeatureDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementFeatureDescriptionDataElements::
    NetworkManagementFeatureDescriptionDataElements()
    : DataElements(), m_featureAddressIsSet(false),
      m_featureAddress(FeatureAddressElements()), m_featureTypeIsSet(false),
      m_specificUsageIsSet(false), m_featureGroupIsSet(false),
      m_roleIsSet(false), m_supportedFunctionIsSet(false),
      m_supportedFunction(FunctionPropertyElements()),
      m_lastStateChangeIsSet(false), m_minimumTrustLevelIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false),
      m_maxResponseDelayIsSet(false)

{}

bool NetworkManagementFeatureDescriptionDataElements::
operator==(const NetworkManagementFeatureDescriptionDataElements &c_classObject)
    const {
  if (m_featureAddressIsSet != c_classObject.m_featureAddressIsSet ||
      (m_featureAddressIsSet &&
       (m_featureAddress != c_classObject.m_featureAddress))) {
    return false;
  }
  if (m_featureTypeIsSet != c_classObject.m_featureTypeIsSet) {
    return false;
  }
  if (m_specificUsageIsSet != c_classObject.m_specificUsageIsSet) {
    return false;
  }
  if (m_featureGroupIsSet != c_classObject.m_featureGroupIsSet) {
    return false;
  }
  if (m_roleIsSet != c_classObject.m_roleIsSet) {
    return false;
  }
  if (m_supportedFunctionIsSet != c_classObject.m_supportedFunctionIsSet ||
      (m_supportedFunctionIsSet &&
       (m_supportedFunction != c_classObject.m_supportedFunction))) {
    return false;
  }
  if (m_lastStateChangeIsSet != c_classObject.m_lastStateChangeIsSet) {
    return false;
  }
  if (m_minimumTrustLevelIsSet != c_classObject.m_minimumTrustLevelIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }
  if (m_maxResponseDelayIsSet != c_classObject.m_maxResponseDelayIsSet) {
    return false;
  }

  return true;
}

bool NetworkManagementFeatureDescriptionDataElements::
operator!=(const NetworkManagementFeatureDescriptionDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool NetworkManagementFeatureDescriptionDataElements::isEmpty() const {
  return !m_featureAddressIsSet && !m_featureTypeIsSet &&
         !m_specificUsageIsSet && !m_featureGroupIsSet && !m_roleIsSet &&
         !m_supportedFunctionIsSet && !m_lastStateChangeIsSet &&
         !m_minimumTrustLevelIsSet && !m_labelIsSet && !m_descriptionIsSet &&
         !m_maxResponseDelayIsSet;
}

DataElements::Type
NetworkManagementFeatureDescriptionDataElements::getDataType() const {
  return DataElements::Type::
      NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementFeatureDescriptionDataElements::clone() const {
  return std::make_shared<NetworkManagementFeatureDescriptionDataElements>(
      *this);
}

void NetworkManagementFeatureDescriptionDataElements::setFeatureAddress(
    const FeatureAddressElements &featureAddress) {
  m_featureAddress = featureAddress;
  m_featureAddressIsSet = true;
}

const FeatureAddressElements &
NetworkManagementFeatureDescriptionDataElements::getFeatureAddress() const {
  return m_featureAddress;
}

void NetworkManagementFeatureDescriptionDataElements::cleanFeatureAddress() {
  m_featureAddress = FeatureAddressElements();
  m_featureAddressIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getFeatureAddressIsSet()
    const {
  return m_featureAddressIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setFeatureType() {
  m_featureTypeIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanFeatureType() {
  m_featureTypeIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getFeatureTypeIsSet()
    const {
  return m_featureTypeIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setSpecificUsage() {
  m_specificUsageIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanSpecificUsage() {
  m_specificUsageIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getSpecificUsageIsSet()
    const {
  return m_specificUsageIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setFeatureGroup() {
  m_featureGroupIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanFeatureGroup() {
  m_featureGroupIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getFeatureGroupIsSet()
    const {
  return m_featureGroupIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setRole() {
  m_roleIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanRole() {
  m_roleIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getRoleIsSet() const {
  return m_roleIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setSupportedFunction(
    const FunctionPropertyElements &supportedFunction) {
  m_supportedFunction = supportedFunction;
  m_supportedFunctionIsSet = true;
}

const FunctionPropertyElements &
NetworkManagementFeatureDescriptionDataElements::getSupportedFunction() const {
  return m_supportedFunction;
}

void NetworkManagementFeatureDescriptionDataElements::cleanSupportedFunction() {
  m_supportedFunction = FunctionPropertyElements();
  m_supportedFunctionIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::
    getSupportedFunctionIsSet() const {
  return m_supportedFunctionIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setLastStateChange() {
  m_lastStateChangeIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanLastStateChange() {
  m_lastStateChangeIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getLastStateChangeIsSet()
    const {
  return m_lastStateChangeIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setMinimumTrustLevel() {
  m_minimumTrustLevelIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanMinimumTrustLevel() {
  m_minimumTrustLevelIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::
    getMinimumTrustLevelIsSet() const {
  return m_minimumTrustLevelIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getDescriptionIsSet()
    const {
  return m_descriptionIsSet;
}

void NetworkManagementFeatureDescriptionDataElements::setMaxResponseDelay() {
  m_maxResponseDelayIsSet = true;
}

void NetworkManagementFeatureDescriptionDataElements::cleanMaxResponseDelay() {
  m_maxResponseDelayIsSet = false;
}

bool NetworkManagementFeatureDescriptionDataElements::getMaxResponseDelayIsSet()
    const {
  return m_maxResponseDelayIsSet;
}

bool NetworkManagementFeatureDescriptionDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"featureAddress", "featureType", "specificUsage",
                   "featureGroup", "role", "supportedFunction",
                   "lastStateChange", "minimumTrustLevel", "label",
                   "description", "maxResponseDelay"})) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "featureType")) {
      m_featureTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "specificUsage")) {
      m_specificUsageIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "featureGroup")) {
      m_featureGroupIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "role")) {
      m_roleIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "supportedFunction", &m_supportedFunction)) {
      m_supportedFunctionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "lastStateChange")) {
      m_lastStateChangeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "minimumTrustLevel")) {
      m_minimumTrustLevelIsSet = true;
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
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxResponseDelay")) {
      m_maxResponseDelayIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementFeatureDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_featureAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("featureAddress", m_featureAddress);
  }
  if (m_featureTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("featureType");
  }
  if (m_specificUsageIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("specificUsage");
  }
  if (m_featureGroupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("featureGroup");
  }
  if (m_roleIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("role");
  }
  if (m_supportedFunctionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("supportedFunction", m_supportedFunction);
  }
  if (m_lastStateChangeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("lastStateChange");
  }
  if (m_minimumTrustLevelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("minimumTrustLevel");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  if (m_maxResponseDelayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxResponseDelay");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram