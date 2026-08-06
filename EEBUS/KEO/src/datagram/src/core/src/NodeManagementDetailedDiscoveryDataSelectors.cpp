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

#include <keo_datagram/core/NodeManagementDetailedDiscoveryDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementDetailedDiscoveryDataSelectors::
    NodeManagementDetailedDiscoveryDataSelectors()
    : DataSelectors(), m_deviceInformationIsSet(false),
      m_deviceInformation(
          NetworkManagementDeviceDescriptionListDataSelectors()),
      m_entityInformationIsSet(false),
      m_entityInformation(
          NetworkManagementEntityDescriptionListDataSelectors()),
      m_featureInformationIsSet(false),
      m_featureInformation(
          NetworkManagementFeatureDescriptionListDataSelectors())

{}

NodeManagementDetailedDiscoveryDataSelectors::
    NodeManagementDetailedDiscoveryDataSelectors(
        const NetworkManagementDeviceDescriptionListDataSelectors
            &c_deviceInformation,
        const NetworkManagementEntityDescriptionListDataSelectors
            &c_entityInformation,
        const NetworkManagementFeatureDescriptionListDataSelectors
            &c_featureInformation)
    : DataSelectors(), m_deviceInformationIsSet(true),
      m_deviceInformation(c_deviceInformation), m_entityInformationIsSet(true),
      m_entityInformation(c_entityInformation), m_featureInformationIsSet(true),
      m_featureInformation(c_featureInformation)

{}

bool NodeManagementDetailedDiscoveryDataSelectors::operator==(
    const NodeManagementDetailedDiscoveryDataSelectors &c_classObject) const {
  if (m_deviceInformationIsSet != c_classObject.m_deviceInformationIsSet ||
      (m_deviceInformationIsSet &&
       (m_deviceInformation != c_classObject.m_deviceInformation))) {
    return false;
  }
  if (m_entityInformationIsSet != c_classObject.m_entityInformationIsSet ||
      (m_entityInformationIsSet &&
       (m_entityInformation != c_classObject.m_entityInformation))) {
    return false;
  }
  if (m_featureInformationIsSet != c_classObject.m_featureInformationIsSet ||
      (m_featureInformationIsSet &&
       (m_featureInformation != c_classObject.m_featureInformation))) {
    return false;
  }

  return true;
}

bool NodeManagementDetailedDiscoveryDataSelectors::operator!=(
    const NodeManagementDetailedDiscoveryDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementDetailedDiscoveryDataSelectors::isEmpty() const {
  return !m_deviceInformationIsSet && !m_entityInformationIsSet &&
         !m_featureInformationIsSet;
}

DataSelectors::Type
NodeManagementDetailedDiscoveryDataSelectors::getDataType() const {
  return DataSelectors::Type::
      NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr NodeManagementDetailedDiscoveryDataSelectors::clone() const {
  return std::make_shared<NodeManagementDetailedDiscoveryDataSelectors>(*this);
}

void NodeManagementDetailedDiscoveryDataSelectors::setDeviceInformation(
    const NetworkManagementDeviceDescriptionListDataSelectors
        &deviceInformation) {
  m_deviceInformation = deviceInformation;
  m_deviceInformationIsSet = true;
}

const NetworkManagementDeviceDescriptionListDataSelectors &
NodeManagementDetailedDiscoveryDataSelectors::getDeviceInformation() const {
  return m_deviceInformation;
}

void NodeManagementDetailedDiscoveryDataSelectors::cleanDeviceInformation() {
  m_deviceInformation = NetworkManagementDeviceDescriptionListDataSelectors();
  m_deviceInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryDataSelectors::getDeviceInformationIsSet()
    const {
  return m_deviceInformationIsSet;
}

void NodeManagementDetailedDiscoveryDataSelectors::setEntityInformation(
    const NetworkManagementEntityDescriptionListDataSelectors
        &entityInformation) {
  m_entityInformation = entityInformation;
  m_entityInformationIsSet = true;
}

const NetworkManagementEntityDescriptionListDataSelectors &
NodeManagementDetailedDiscoveryDataSelectors::getEntityInformation() const {
  return m_entityInformation;
}

void NodeManagementDetailedDiscoveryDataSelectors::cleanEntityInformation() {
  m_entityInformation = NetworkManagementEntityDescriptionListDataSelectors();
  m_entityInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryDataSelectors::getEntityInformationIsSet()
    const {
  return m_entityInformationIsSet;
}

void NodeManagementDetailedDiscoveryDataSelectors::setFeatureInformation(
    const NetworkManagementFeatureDescriptionListDataSelectors
        &featureInformation) {
  m_featureInformation = featureInformation;
  m_featureInformationIsSet = true;
}

const NetworkManagementFeatureDescriptionListDataSelectors &
NodeManagementDetailedDiscoveryDataSelectors::getFeatureInformation() const {
  return m_featureInformation;
}

void NodeManagementDetailedDiscoveryDataSelectors::cleanFeatureInformation() {
  m_featureInformation = NetworkManagementFeatureDescriptionListDataSelectors();
  m_featureInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryDataSelectors::getFeatureInformationIsSet()
    const {
  return m_featureInformationIsSet;
}

bool NodeManagementDetailedDiscoveryDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"deviceInformation", "entityInformation", "featureInformation"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "deviceInformation", &m_deviceInformation)) {
      m_deviceInformationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "entityInformation", &m_entityInformation)) {
      m_entityInformationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "featureInformation",
                                   &m_featureInformation)) {
      m_featureInformationIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementDetailedDiscoveryDataSelectors::toJson() const {
  std::string result = "[";
  if (m_deviceInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("deviceInformation", m_deviceInformation);
  }
  if (m_entityInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("entityInformation", m_entityInformation);
  }
  if (m_featureInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("featureInformation",
                                           m_featureInformation);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram