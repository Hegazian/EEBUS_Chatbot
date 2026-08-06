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

#include <keo_datagram/core/NodeManagementDetailedDiscoveryData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementDetailedDiscoveryData::NodeManagementDetailedDiscoveryData()
    : CmdData(), m_specificationVersionListIsSet(false),
      m_specificationVersionList(NodeManagementSpecificationVersionList()),
      m_deviceInformationIsSet(false),
      m_deviceInformation(NodeManagementDetailedDiscoveryDeviceInformation()),
      m_entityInformationIsSet(false),
      m_entityInformation(
          std::vector<NodeManagementDetailedDiscoveryEntityInformation>()),
      m_featureInformationIsSet(false),
      m_featureInformation(
          std::vector<NodeManagementDetailedDiscoveryFeatureInformation>())

{}

bool NodeManagementDetailedDiscoveryData::
operator==(const NodeManagementDetailedDiscoveryData &c_classObject) const {
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

bool NodeManagementDetailedDiscoveryData::
operator!=(const NodeManagementDetailedDiscoveryData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementDetailedDiscoveryData::isEmpty() const {
  return !m_specificationVersionListIsSet && !m_deviceInformationIsSet &&
         !m_entityInformationIsSet && !m_featureInformationIsSet;
}

CmdData::Type NodeManagementDetailedDiscoveryData::getDataType() const {
  return CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE;
}

CmdDataPtr NodeManagementDetailedDiscoveryData::clone() const {
  return std::make_shared<NodeManagementDetailedDiscoveryData>(*this);
}

void NodeManagementDetailedDiscoveryData::setSpecificationVersionList(
    const NodeManagementSpecificationVersionList &specificationVersionList) {
  m_specificationVersionList = specificationVersionList;
  m_specificationVersionListIsSet = true;
}

const NodeManagementSpecificationVersionList &
NodeManagementDetailedDiscoveryData::getSpecificationVersionList() const {
  return m_specificationVersionList;
}

void NodeManagementDetailedDiscoveryData::cleanSpecificationVersionList() {
  m_specificationVersionList = NodeManagementSpecificationVersionList();
  m_specificationVersionListIsSet = false;
}

bool NodeManagementDetailedDiscoveryData::getSpecificationVersionListIsSet()
    const {
  return m_specificationVersionListIsSet;
}

void NodeManagementDetailedDiscoveryData::setDeviceInformation(
    const NodeManagementDetailedDiscoveryDeviceInformation &deviceInformation) {
  m_deviceInformation = deviceInformation;
  m_deviceInformationIsSet = true;
}

const NodeManagementDetailedDiscoveryDeviceInformation &
NodeManagementDetailedDiscoveryData::getDeviceInformation() const {
  return m_deviceInformation;
}

void NodeManagementDetailedDiscoveryData::cleanDeviceInformation() {
  m_deviceInformation = NodeManagementDetailedDiscoveryDeviceInformation();
  m_deviceInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryData::getDeviceInformationIsSet() const {
  return m_deviceInformationIsSet;
}

void NodeManagementDetailedDiscoveryData::setEntityInformation(
    const std::vector<NodeManagementDetailedDiscoveryEntityInformation>
        &entityInformation) {
  m_entityInformation = entityInformation;
  m_entityInformationIsSet = true;
}

const std::vector<NodeManagementDetailedDiscoveryEntityInformation> &
NodeManagementDetailedDiscoveryData::getEntityInformation() const {
  return m_entityInformation;
}

void NodeManagementDetailedDiscoveryData::cleanEntityInformation() {
  m_entityInformation.clear();
  m_entityInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryData::getEntityInformationIsSet() const {
  return m_entityInformationIsSet;
}

void NodeManagementDetailedDiscoveryData::setFeatureInformation(
    const std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
        &featureInformation) {
  m_featureInformation = featureInformation;
  m_featureInformationIsSet = true;
}

const std::vector<NodeManagementDetailedDiscoveryFeatureInformation> &
NodeManagementDetailedDiscoveryData::getFeatureInformation() const {
  return m_featureInformation;
}

void NodeManagementDetailedDiscoveryData::cleanFeatureInformation() {
  m_featureInformation.clear();
  m_featureInformationIsSet = false;
}

bool NodeManagementDetailedDiscoveryData::getFeatureInformationIsSet() const {
  return m_featureInformationIsSet;
}

CmdDataPtr NodeManagementDetailedDiscoveryData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NodeManagementDetailedDiscoveryData>(*this);
}

bool NodeManagementDetailedDiscoveryData::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::getList<
            NodeManagementDetailedDiscoveryEntityInformation>(
            static_cast<KeoJsonValue *>(&(*iter)), "entityInformation",
            &m_entityInformation)) {
      m_entityInformationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            NodeManagementDetailedDiscoveryFeatureInformation>(
            static_cast<KeoJsonValue *>(&(*iter)), "featureInformation",
            &m_featureInformation)) {
      m_featureInformationIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementDetailedDiscoveryData::toJson() const {
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
    result += KeoJsonTransformation::writeList<
        NodeManagementDetailedDiscoveryEntityInformation>("entityInformation",
                                                          m_entityInformation);
  }
  if (m_featureInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        NodeManagementDetailedDiscoveryFeatureInformation>(
        "featureInformation", m_featureInformation);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram