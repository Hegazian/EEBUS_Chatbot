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

#include <keo_datagram/core/NetworkManagementFeatureDescriptionData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementFeatureDescriptionData::
    NetworkManagementFeatureDescriptionData()
    : m_featureAddressIsSet(false), m_featureAddress(FeatureAddress()),
      m_featureTypeIsSet(false), m_featureType(FeatureType()),
      m_specificUsageIsSet(false),
      m_specificUsage(std::vector<FeatureSpecificUsage>()),
      m_featureGroupIsSet(false), m_featureGroup(""), m_roleIsSet(false),
      m_role(Role()), m_supportedFunctionIsSet(false),
      m_supportedFunction(std::vector<FunctionProperty>()),
      m_lastStateChangeIsSet(false),
      m_lastStateChange(NetworkManagementStateChange()),
      m_minimumTrustLevelIsSet(false), m_minimumTrustLevel(""),
      m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description(""), m_maxResponseDelayIsSet(false),
      m_maxResponseDelay(xs_duration())

{}

bool NetworkManagementFeatureDescriptionData::
operator==(const NetworkManagementFeatureDescriptionData &c_classObject) const {
  if (m_featureAddressIsSet != c_classObject.m_featureAddressIsSet ||
      (m_featureAddressIsSet &&
       (m_featureAddress != c_classObject.m_featureAddress))) {
    return false;
  }
  if (m_featureTypeIsSet != c_classObject.m_featureTypeIsSet ||
      (m_featureTypeIsSet && (m_featureType != c_classObject.m_featureType))) {
    return false;
  }
  if (m_specificUsageIsSet != c_classObject.m_specificUsageIsSet ||
      (m_specificUsageIsSet &&
       (m_specificUsage != c_classObject.m_specificUsage))) {
    return false;
  }
  if (m_featureGroupIsSet != c_classObject.m_featureGroupIsSet ||
      (m_featureGroupIsSet &&
       (m_featureGroup != c_classObject.m_featureGroup))) {
    return false;
  }
  if (m_roleIsSet != c_classObject.m_roleIsSet ||
      (m_roleIsSet && (m_role != c_classObject.m_role))) {
    return false;
  }
  if (m_supportedFunctionIsSet != c_classObject.m_supportedFunctionIsSet ||
      (m_supportedFunctionIsSet &&
       (m_supportedFunction != c_classObject.m_supportedFunction))) {
    return false;
  }
  if (m_lastStateChangeIsSet != c_classObject.m_lastStateChangeIsSet ||
      (m_lastStateChangeIsSet &&
       (m_lastStateChange != c_classObject.m_lastStateChange))) {
    return false;
  }
  if (m_minimumTrustLevelIsSet != c_classObject.m_minimumTrustLevelIsSet ||
      (m_minimumTrustLevelIsSet &&
       (m_minimumTrustLevel != c_classObject.m_minimumTrustLevel))) {
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
  if (m_maxResponseDelayIsSet != c_classObject.m_maxResponseDelayIsSet ||
      (m_maxResponseDelayIsSet &&
       (m_maxResponseDelay != c_classObject.m_maxResponseDelay))) {
    return false;
  }

  return true;
}

bool NetworkManagementFeatureDescriptionData::
operator!=(const NetworkManagementFeatureDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementFeatureDescriptionData::isEmpty() const {
  return !m_featureAddressIsSet && !m_featureTypeIsSet &&
         !m_specificUsageIsSet && !m_featureGroupIsSet && !m_roleIsSet &&
         !m_supportedFunctionIsSet && !m_lastStateChangeIsSet &&
         !m_minimumTrustLevelIsSet && !m_labelIsSet && !m_descriptionIsSet &&
         !m_maxResponseDelayIsSet;
}

void NetworkManagementFeatureDescriptionData::setFeatureAddress(
    const FeatureAddress &featureAddress) {
  m_featureAddress = featureAddress;
  m_featureAddressIsSet = true;
}

const FeatureAddress &
NetworkManagementFeatureDescriptionData::getFeatureAddress() const {
  return m_featureAddress;
}

void NetworkManagementFeatureDescriptionData::cleanFeatureAddress() {
  m_featureAddress = FeatureAddress();
  m_featureAddressIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getFeatureAddressIsSet() const {
  return m_featureAddressIsSet;
}

void NetworkManagementFeatureDescriptionData::setFeatureType(
    const FeatureType &featureType) {
  m_featureType = featureType;
  m_featureTypeIsSet = true;
}

const FeatureType &
NetworkManagementFeatureDescriptionData::getFeatureType() const {
  return m_featureType;
}

void NetworkManagementFeatureDescriptionData::cleanFeatureType() {
  m_featureType = FeatureType();
  m_featureTypeIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getFeatureTypeIsSet() const {
  return m_featureTypeIsSet;
}

void NetworkManagementFeatureDescriptionData::setSpecificUsage(
    const std::vector<FeatureSpecificUsage> &specificUsage) {
  m_specificUsage = specificUsage;
  m_specificUsageIsSet = true;
}

const std::vector<FeatureSpecificUsage> &
NetworkManagementFeatureDescriptionData::getSpecificUsage() const {
  return m_specificUsage;
}

void NetworkManagementFeatureDescriptionData::cleanSpecificUsage() {
  m_specificUsage.clear();
  m_specificUsageIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getSpecificUsageIsSet() const {
  return m_specificUsageIsSet;
}

void NetworkManagementFeatureDescriptionData::setFeatureGroup(
    const xs_string &featureGroup) {
  m_featureGroup = featureGroup;
  m_featureGroupIsSet = true;
}

const xs_string &
NetworkManagementFeatureDescriptionData::getFeatureGroup() const {
  return m_featureGroup;
}

void NetworkManagementFeatureDescriptionData::cleanFeatureGroup() {
  m_featureGroup = "";
  m_featureGroupIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getFeatureGroupIsSet() const {
  return m_featureGroupIsSet;
}

void NetworkManagementFeatureDescriptionData::setRole(const Role &role) {
  m_role = role;
  m_roleIsSet = true;
}

const Role &NetworkManagementFeatureDescriptionData::getRole() const {
  return m_role;
}

void NetworkManagementFeatureDescriptionData::cleanRole() {
  m_role = Role();
  m_roleIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getRoleIsSet() const {
  return m_roleIsSet;
}

void NetworkManagementFeatureDescriptionData::setSupportedFunction(
    const std::vector<FunctionProperty> &supportedFunction) {
  m_supportedFunction = supportedFunction;
  m_supportedFunctionIsSet = true;
}

const std::vector<FunctionProperty> &
NetworkManagementFeatureDescriptionData::getSupportedFunction() const {
  return m_supportedFunction;
}

void NetworkManagementFeatureDescriptionData::cleanSupportedFunction() {
  m_supportedFunction.clear();
  m_supportedFunctionIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getSupportedFunctionIsSet()
    const {
  return m_supportedFunctionIsSet;
}

void NetworkManagementFeatureDescriptionData::setLastStateChange(
    const NetworkManagementStateChange &lastStateChange) {
  m_lastStateChange = lastStateChange;
  m_lastStateChangeIsSet = true;
}

const NetworkManagementStateChange &
NetworkManagementFeatureDescriptionData::getLastStateChange() const {
  return m_lastStateChange;
}

void NetworkManagementFeatureDescriptionData::cleanLastStateChange() {
  m_lastStateChange = NetworkManagementStateChange();
  m_lastStateChangeIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getLastStateChangeIsSet() const {
  return m_lastStateChangeIsSet;
}

void NetworkManagementFeatureDescriptionData::setMinimumTrustLevel(
    const xs_string &minimumTrustLevel) {
  m_minimumTrustLevel = minimumTrustLevel;
  m_minimumTrustLevelIsSet = true;
}

const xs_string &
NetworkManagementFeatureDescriptionData::getMinimumTrustLevel() const {
  return m_minimumTrustLevel;
}

void NetworkManagementFeatureDescriptionData::cleanMinimumTrustLevel() {
  m_minimumTrustLevel = "";
  m_minimumTrustLevelIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getMinimumTrustLevelIsSet()
    const {
  return m_minimumTrustLevelIsSet;
}

void NetworkManagementFeatureDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &NetworkManagementFeatureDescriptionData::getLabel() const {
  return m_label;
}

void NetworkManagementFeatureDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementFeatureDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &
NetworkManagementFeatureDescriptionData::getDescription() const {
  return m_description;
}

void NetworkManagementFeatureDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void NetworkManagementFeatureDescriptionData::setMaxResponseDelay(
    const xs_duration &maxResponseDelay) {
  m_maxResponseDelay = maxResponseDelay;
  m_maxResponseDelayIsSet = true;
}

const xs_duration &
NetworkManagementFeatureDescriptionData::getMaxResponseDelay() const {
  return m_maxResponseDelay;
}

void NetworkManagementFeatureDescriptionData::cleanMaxResponseDelay() {
  m_maxResponseDelay = xs_duration();
  m_maxResponseDelayIsSet = false;
}

bool NetworkManagementFeatureDescriptionData::getMaxResponseDelayIsSet() const {
  return m_maxResponseDelayIsSet;
}

bool NetworkManagementFeatureDescriptionData::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "featureType", &m_featureType)) {
      m_featureTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<FeatureSpecificUsage>(
            static_cast<KeoJsonValue *>(&(*iter)), "specificUsage",
            &m_specificUsage)) {
      m_specificUsageIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "featureGroup", &m_featureGroup)) {
      m_featureGroupIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "role", &m_role)) {
      m_roleIsSet = true;
      ++iter;
    }
    if (iter != json->end() && KeoJsonTransformation::getList<FunctionProperty>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "supportedFunction", &m_supportedFunction)) {
      m_supportedFunctionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "lastStateChange", &m_lastStateChange)) {
      m_lastStateChangeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "minimumTrustLevel", &m_minimumTrustLevel)) {
      m_minimumTrustLevelIsSet = true;
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
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxResponseDelay", &m_maxResponseDelay)) {
      m_maxResponseDelayIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementFeatureDescriptionData::toJson() const {
  std::string result = "[";
  if (m_featureAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("featureAddress", m_featureAddress);
  }
  if (m_featureTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("featureType", m_featureType);
  }
  if (m_specificUsageIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<FeatureSpecificUsage>(
        "specificUsage", m_specificUsage);
  }
  if (m_featureGroupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("featureGroup", m_featureGroup);
  }
  if (m_roleIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("role", m_role);
  }
  if (m_supportedFunctionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<FunctionProperty>(
        "supportedFunction", m_supportedFunction);
  }
  if (m_lastStateChangeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("lastStateChange", m_lastStateChange);
  }
  if (m_minimumTrustLevelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("minimumTrustLevel", m_minimumTrustLevel);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  if (m_maxResponseDelayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("maxResponseDelay", m_maxResponseDelay);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram