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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsDataElements::SmartEnergyManagementPsDataElements()
    : DataElements(), m_nodeScheduleInformationIsSet(false),
      m_nodeScheduleInformation(
          PowerSequenceNodeScheduleInformationDataElements()),
      m_alternativesIsSet(false),
      m_alternatives(SmartEnergyManagementPsAlternativesElements())

{}

SmartEnergyManagementPsDataElements::SmartEnergyManagementPsDataElements(
    const PowerSequenceNodeScheduleInformationDataElements
        &c_nodeScheduleInformation,
    const SmartEnergyManagementPsAlternativesElements &c_alternatives)
    : DataElements(), m_nodeScheduleInformationIsSet(true),
      m_nodeScheduleInformation(c_nodeScheduleInformation),
      m_alternativesIsSet(true), m_alternatives(c_alternatives)

{}

bool SmartEnergyManagementPsDataElements::
operator==(const SmartEnergyManagementPsDataElements &c_classObject) const {
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

bool SmartEnergyManagementPsDataElements::
operator!=(const SmartEnergyManagementPsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsDataElements::isEmpty() const {
  return !m_nodeScheduleInformationIsSet && !m_alternativesIsSet;
}

DataElements::Type SmartEnergyManagementPsDataElements::getDataType() const {
  return DataElements::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SmartEnergyManagementPsDataElements::clone() const {
  return std::make_shared<SmartEnergyManagementPsDataElements>(*this);
}

void SmartEnergyManagementPsDataElements::setNodeScheduleInformation(
    const PowerSequenceNodeScheduleInformationDataElements
        &nodeScheduleInformation) {
  m_nodeScheduleInformation = nodeScheduleInformation;
  m_nodeScheduleInformationIsSet = true;
}

const PowerSequenceNodeScheduleInformationDataElements &
SmartEnergyManagementPsDataElements::getNodeScheduleInformation() const {
  return m_nodeScheduleInformation;
}

void SmartEnergyManagementPsDataElements::cleanNodeScheduleInformation() {
  m_nodeScheduleInformation =
      PowerSequenceNodeScheduleInformationDataElements();
  m_nodeScheduleInformationIsSet = false;
}

bool SmartEnergyManagementPsDataElements::getNodeScheduleInformationIsSet()
    const {
  return m_nodeScheduleInformationIsSet;
}

void SmartEnergyManagementPsDataElements::setAlternatives(
    const SmartEnergyManagementPsAlternativesElements &alternatives) {
  m_alternatives = alternatives;
  m_alternativesIsSet = true;
}

const SmartEnergyManagementPsAlternativesElements &
SmartEnergyManagementPsDataElements::getAlternatives() const {
  return m_alternatives;
}

void SmartEnergyManagementPsDataElements::cleanAlternatives() {
  m_alternatives = SmartEnergyManagementPsAlternativesElements();
  m_alternativesIsSet = false;
}

bool SmartEnergyManagementPsDataElements::getAlternativesIsSet() const {
  return m_alternativesIsSet;
}

bool SmartEnergyManagementPsDataElements::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "alternatives", &m_alternatives)) {
      m_alternativesIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsDataElements::toJson() const {
  std::string result = "[";
  if (m_nodeScheduleInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nodeScheduleInformation",
                                           m_nodeScheduleInformation);
  }
  if (m_alternativesIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("alternatives", m_alternatives);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram