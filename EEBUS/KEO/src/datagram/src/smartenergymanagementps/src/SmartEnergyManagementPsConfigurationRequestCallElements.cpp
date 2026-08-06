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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsConfigurationRequestCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsConfigurationRequestCallElements::
    SmartEnergyManagementPsConfigurationRequestCallElements()
    : DataElements(), m_scheduleConfigurationRequestIsSet(false),
      m_scheduleConfigurationRequest(
          PowerSequenceScheduleConfigurationRequestCallElements())

{}

SmartEnergyManagementPsConfigurationRequestCallElements::
    SmartEnergyManagementPsConfigurationRequestCallElements(
        const PowerSequenceScheduleConfigurationRequestCallElements
            &c_scheduleConfigurationRequest) {
  setScheduleConfigurationRequest(c_scheduleConfigurationRequest);
}

bool SmartEnergyManagementPsConfigurationRequestCallElements::
operator==(const SmartEnergyManagementPsConfigurationRequestCallElements
               &c_classObject) const {
  if (m_scheduleConfigurationRequestIsSet !=
          c_classObject.m_scheduleConfigurationRequestIsSet ||
      (m_scheduleConfigurationRequestIsSet &&
       (m_scheduleConfigurationRequest !=
        c_classObject.m_scheduleConfigurationRequest))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsConfigurationRequestCallElements::
operator!=(const SmartEnergyManagementPsConfigurationRequestCallElements
               &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsConfigurationRequestCallElements::isEmpty() const {
  return !m_scheduleConfigurationRequestIsSet;
}

DataElements::Type
SmartEnergyManagementPsConfigurationRequestCallElements::getDataType() const {
  return DataElements::Type::
      SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_ELEMENTS_TYPE;
}

DataElementsPtr
SmartEnergyManagementPsConfigurationRequestCallElements::clone() const {
  return std::make_shared<
      SmartEnergyManagementPsConfigurationRequestCallElements>(*this);
}

void SmartEnergyManagementPsConfigurationRequestCallElements::
    setScheduleConfigurationRequest(
        const PowerSequenceScheduleConfigurationRequestCallElements
            &scheduleConfigurationRequest) {
  m_scheduleConfigurationRequest = scheduleConfigurationRequest;
  m_scheduleConfigurationRequestIsSet = true;
}

const PowerSequenceScheduleConfigurationRequestCallElements &
SmartEnergyManagementPsConfigurationRequestCallElements::
    getScheduleConfigurationRequest() const {
  return m_scheduleConfigurationRequest;
}

void SmartEnergyManagementPsConfigurationRequestCallElements::
    cleanScheduleConfigurationRequest() {
  m_scheduleConfigurationRequest =
      PowerSequenceScheduleConfigurationRequestCallElements();
  m_scheduleConfigurationRequestIsSet = false;
}

bool SmartEnergyManagementPsConfigurationRequestCallElements::
    getScheduleConfigurationRequestIsSet() const {
  return m_scheduleConfigurationRequestIsSet;
}

bool SmartEnergyManagementPsConfigurationRequestCallElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"scheduleConfigurationRequest"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scheduleConfigurationRequest",
                                   &m_scheduleConfigurationRequest)) {
      m_scheduleConfigurationRequestIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
SmartEnergyManagementPsConfigurationRequestCallElements::toJson() const {
  std::string result = "[";
  if (m_scheduleConfigurationRequestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scheduleConfigurationRequest",
                                           m_scheduleConfigurationRequest);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram