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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsData::SmartEnergyManagementPsData()
    : CmdData(), m_nodeScheduleInformationIsSet(false),
      m_nodeScheduleInformation(PowerSequenceNodeScheduleInformationData()),
      m_alternativesIsSet(false),
      m_alternatives(std::vector<SmartEnergyManagementPsAlternatives>())

{}

SmartEnergyManagementPsData::SmartEnergyManagementPsData(
    const PowerSequenceNodeScheduleInformationData &c_nodeScheduleInformation,
    const std::vector<SmartEnergyManagementPsAlternatives> &c_alternatives)
    : CmdData(), m_nodeScheduleInformationIsSet(true),
      m_nodeScheduleInformation(c_nodeScheduleInformation),
      m_alternativesIsSet(true), m_alternatives(c_alternatives)

{}

bool SmartEnergyManagementPsData::
operator==(const SmartEnergyManagementPsData &c_classObject) const {
  if (m_nodeScheduleInformationIsSet !=
          c_classObject.m_nodeScheduleInformationIsSet ||
      (m_nodeScheduleInformationIsSet &&
       (m_nodeScheduleInformation !=
        c_classObject.m_nodeScheduleInformation))) {
    return false;
  }
  if (m_alternativesIsSet != c_classObject.m_alternativesIsSet ||
      (m_alternativesIsSet &&
       (m_alternatives != c_classObject.m_alternatives))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsData::
operator!=(const SmartEnergyManagementPsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsData::isEmpty() const {
  return !m_nodeScheduleInformationIsSet && !m_alternativesIsSet;
}

CmdData::Type SmartEnergyManagementPsData::getDataType() const {
  return CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_TYPE;
}

CmdDataPtr SmartEnergyManagementPsData::clone() const {
  return std::make_shared<SmartEnergyManagementPsData>(*this);
}

void SmartEnergyManagementPsData::setNodeScheduleInformation(
    const PowerSequenceNodeScheduleInformationData &nodeScheduleInformation) {
  m_nodeScheduleInformation = nodeScheduleInformation;
  m_nodeScheduleInformationIsSet = true;
}

const PowerSequenceNodeScheduleInformationData &
SmartEnergyManagementPsData::getNodeScheduleInformation() const {
  return m_nodeScheduleInformation;
}

void SmartEnergyManagementPsData::cleanNodeScheduleInformation() {
  m_nodeScheduleInformation = PowerSequenceNodeScheduleInformationData();
  m_nodeScheduleInformationIsSet = false;
}

bool SmartEnergyManagementPsData::getNodeScheduleInformationIsSet() const {
  return m_nodeScheduleInformationIsSet;
}

void SmartEnergyManagementPsData::setAlternatives(
    const std::vector<SmartEnergyManagementPsAlternatives> &alternatives) {
  m_alternatives = alternatives;
  m_alternativesIsSet = true;
}

const std::vector<SmartEnergyManagementPsAlternatives> &
SmartEnergyManagementPsData::getAlternatives() const {
  return m_alternatives;
}

void SmartEnergyManagementPsData::cleanAlternatives() {
  m_alternatives.clear();
  m_alternativesIsSet = false;
}

bool SmartEnergyManagementPsData::getAlternativesIsSet() const {
  return m_alternativesIsSet;
}

CmdDataPtr
SmartEnergyManagementPsData::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<SmartEnergyManagementPsData>(*this);
}

bool SmartEnergyManagementPsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"nodeScheduleInformation", "alternatives"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "nodeScheduleInformation",
                                   &m_nodeScheduleInformation)) {
      m_nodeScheduleInformationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<SmartEnergyManagementPsAlternatives>(
            static_cast<KeoJsonValue *>(&(*iter)), "alternatives",
            &m_alternatives)) {
      m_alternativesIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsData::toJson() const {
  std::string result = "[";
  if (m_nodeScheduleInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nodeScheduleInformation",
                                           m_nodeScheduleInformation);
  }
  if (m_alternativesIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<SmartEnergyManagementPsAlternatives>(
            "alternatives", m_alternatives);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram