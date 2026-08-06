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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsConfigurationRequestCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsConfigurationRequestCall::
    SmartEnergyManagementPsConfigurationRequestCall()
    : CmdData(), m_scheduleConfigurationRequestIsSet(false),
      m_scheduleConfigurationRequest(
          PowerSequenceScheduleConfigurationRequestCall())

{}

SmartEnergyManagementPsConfigurationRequestCall::
    SmartEnergyManagementPsConfigurationRequestCall(
        const PowerSequenceScheduleConfigurationRequestCall
            &c_scheduleConfigurationRequest) {
  setScheduleConfigurationRequest(c_scheduleConfigurationRequest);
}

bool SmartEnergyManagementPsConfigurationRequestCall::
operator==(const SmartEnergyManagementPsConfigurationRequestCall &c_classObject)
    const {
  if (m_scheduleConfigurationRequestIsSet !=
          c_classObject.m_scheduleConfigurationRequestIsSet ||
      (m_scheduleConfigurationRequestIsSet &&
       (m_scheduleConfigurationRequest !=
        c_classObject.m_scheduleConfigurationRequest))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsConfigurationRequestCall::
operator!=(const SmartEnergyManagementPsConfigurationRequestCall &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsConfigurationRequestCall::isEmpty() const {
  return !m_scheduleConfigurationRequestIsSet;
}

CmdData::Type
SmartEnergyManagementPsConfigurationRequestCall::getDataType() const {
  return CmdData::Type::
      SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_TYPE;
}

CmdDataPtr SmartEnergyManagementPsConfigurationRequestCall::clone() const {
  return std::make_shared<SmartEnergyManagementPsConfigurationRequestCall>(
      *this);
}

void SmartEnergyManagementPsConfigurationRequestCall::
    setScheduleConfigurationRequest(
        const PowerSequenceScheduleConfigurationRequestCall
            &scheduleConfigurationRequest) {
  m_scheduleConfigurationRequest = scheduleConfigurationRequest;
  m_scheduleConfigurationRequestIsSet = true;
}

const PowerSequenceScheduleConfigurationRequestCall &
SmartEnergyManagementPsConfigurationRequestCall::
    getScheduleConfigurationRequest() const {
  return m_scheduleConfigurationRequest;
}

void SmartEnergyManagementPsConfigurationRequestCall::
    cleanScheduleConfigurationRequest() {
  m_scheduleConfigurationRequest =
      PowerSequenceScheduleConfigurationRequestCall();
  m_scheduleConfigurationRequestIsSet = false;
}

bool SmartEnergyManagementPsConfigurationRequestCall::
    getScheduleConfigurationRequestIsSet() const {
  return m_scheduleConfigurationRequestIsSet;
}

CmdDataPtr SmartEnergyManagementPsConfigurationRequestCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<SmartEnergyManagementPsConfigurationRequestCall>(
      *this);
}

bool SmartEnergyManagementPsConfigurationRequestCall::fromJson(
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

std::string SmartEnergyManagementPsConfigurationRequestCall::toJson() const {
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