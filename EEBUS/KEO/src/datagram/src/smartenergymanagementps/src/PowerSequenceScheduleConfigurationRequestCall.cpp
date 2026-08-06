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

#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConfigurationRequestCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceScheduleConfigurationRequestCall::
    PowerSequenceScheduleConfigurationRequestCall()
    : CmdData(), m_sequenceIdIsSet(false), m_sequenceId(0)

{}

PowerSequenceScheduleConfigurationRequestCall::
    PowerSequenceScheduleConfigurationRequestCall(
        const xs_unsignedInt &c_sequenceId) {
  setSequenceId(c_sequenceId);
}

bool PowerSequenceScheduleConfigurationRequestCall::operator==(
    const PowerSequenceScheduleConfigurationRequestCall &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool PowerSequenceScheduleConfigurationRequestCall::operator!=(
    const PowerSequenceScheduleConfigurationRequestCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceScheduleConfigurationRequestCall::isEmpty() const {
  return !m_sequenceIdIsSet;
}

CmdData::Type
PowerSequenceScheduleConfigurationRequestCall::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_TYPE;
}

CmdDataPtr PowerSequenceScheduleConfigurationRequestCall::clone() const {
  return std::make_shared<PowerSequenceScheduleConfigurationRequestCall>(*this);
}

void PowerSequenceScheduleConfigurationRequestCall::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerSequenceScheduleConfigurationRequestCall::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceScheduleConfigurationRequestCall::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequenceScheduleConfigurationRequestCall::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

CmdDataPtr PowerSequenceScheduleConfigurationRequestCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<PowerSequenceScheduleConfigurationRequestCall>(*this);
}

bool PowerSequenceScheduleConfigurationRequestCall::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceScheduleConfigurationRequestCall::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram