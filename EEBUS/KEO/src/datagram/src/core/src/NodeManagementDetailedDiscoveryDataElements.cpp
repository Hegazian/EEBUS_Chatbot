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

#include <keo_datagram/core/NodeManagementDetailedDiscoveryDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementDetailedDiscoveryDataElements::
    NodeManagementDetailedDiscoveryDataElements()
    : DataElements(), m_specificationVersionListIsSet(false),
      m_specificationVersionList(
          NodeManagementSpecificationVersionListElements()),
      m_deviceInformationIsSet(false),
      m_deviceInformation(
          NodeManagementDetailedDiscoveryDeviceInformationElements()),
      m_entityInformationIsSet(false),
      m_entityInformation(
          NodeManagementDetailedDiscoveryEntityInformationElements()),
      m_featureInformationIsSet(false),
      m_featureInformation(
          NodeManagementDetailedDiscoveryFeatureInformationElements())

{}

bool NodeManagementDetailedDiscoveryDataElements::operator==(
    const NodeManagementDetailedDiscoveryDataElements &c_classObject) const {
  if (m_specificationVersionListIsSet !=
          c_classObject.m_specificationVersionListIsSet ||
      (m_specificationVersionListIsSet &&
       (m_specificationVersionList !=
        c_classObject.m_specificationVersionList))) {
    return false;
  }
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

bool NodeManagementDetailedDiscoveryDataElements::operator!=(
    const NodeManagementDetailedDiscoveryDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementDetailedDiscoveryDataElements::isEmpty() const {
  return !m_specificationVersionListIsSet && !m_deviceInformationIsSet &&
         !m_entityInformationIsSet && !m_featureInformationIsSet;
}

DataElements::Type
NodeManagementDetailedDiscoveryDataElements::getDataType() const {
  return DataElements::Type::
      NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NodeManagementDetailedDiscoveryDataElements::clone() const {
  return std::make_shared<NodeManagementDetailedDiscoveryDataElements>(*this);
}

void NodeManagementDetailedDiscoveryDataElements::setSpecificationVersionList(
    const NodeManagementSpecificationVersionListElements
        &specificationVersionList) {
  m_specificationVersionList = specificationVersionList;
  m_specificationVersionListIsSet = true;
}

const NodeManagementSpecificationVersionListElements &
NodeManagementDetailedDiscoveryDataElements::getSpecificationVersionList()
    const {
  return m_specificationVersionList;
}

void NodeManagementDetailedDiscoveryDataElements::
    cleanSpecificationVersionList() {
  m_specificationVersionList = NodeManagementSpecificationVersionListElements();
  m_specificationVersionListIsSet = false;
}

bool NodeManagementDetailedDiscoveryDataElements::
    getSpecificationVersionListIsSet() const {
  return m_specificationVersionListIsSet;
}

void NodeManagementDetailedDiscoveryDataElements::setDeviceInformation(
    const NodeManagementDetailedDiscoveryDeviceInformationElements
        &deviceInformation) {
  m_deviceInformation = deviceInformation;
  m_deviceInformationIsSet = true;
}

const NodeManagementDetailedDiscoveryDeviceInformationElements &
NodeManagementDetailedDiscoveryDataElements::getDeviceInformation() const {
  return m_deviceInformation;
}

void NodeManagementDetailedDiscoveryDataElements::cleanDeviceInformation() {
  m_deviceInformation =
      NodeManagementDetailedDiscoveryDeviceInformationElements();
  m_deviceInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryDataElements::getDeviceInformationIsSet()
    const {
  return m_deviceInformationIsSet;
}

void NodeManagementDetailedDiscoveryDataElements::setEntityInformation(
    const NodeManagementDetailedDiscoveryEntityInformationElements
        &entityInformation) {
  m_entityInformation = entityInformation;
  m_entityInformationIsSet = true;
}

const NodeManagementDetailedDiscoveryEntityInformationElements &
NodeManagementDetailedDiscoveryDataElements::getEntityInformation() const {
  return m_entityInformation;
}

void NodeManagementDetailedDiscoveryDataElements::cleanEntityInformation() {
  m_entityInformation =
      NodeManagementDetailedDiscoveryEntityInformationElements();
  m_entityInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryDataElements::getEntityInformationIsSet()
    const {
  return m_entityInformationIsSet;
}

void NodeManagementDetailedDiscoveryDataElements::setFeatureInformation(
    const NodeManagementDetailedDiscoveryFeatureInformationElements
        &featureInformation) {
  m_featureInformation = featureInformation;
  m_featureInformationIsSet = true;
}

const NodeManagementDetailedDiscoveryFeatureInformationElements &
NodeManagementDetailedDiscoveryDataElements::getFeatureInformation() const {
  return m_featureInformation;
}

void NodeManagementDetailedDiscoveryDataElements::cleanFeatureInformation() {
  m_featureInformation =
      NodeManagementDetailedDiscoveryFeatureInformationElements();
  m_featureInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryDataElements::getFeatureInformationIsSet()
    const {
  return m_featureInformationIsSet;
}

bool NodeManagementDetailedDiscoveryDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"specificationVersionList", "deviceInformation",
                   "entityInformation", "featureInformation"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "specificationVersionList",
                                   &m_specificationVersionList)) {
      m_specificationVersionListIsSet = true;
      ++iter;
    }
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

std::string NodeManagementDetailedDiscoveryDataElements::toJson() const {
  std::string result = "[";
  if (m_specificationVersionListIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("specificationVersionList",
                                           m_specificationVersionList);
  }
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