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

#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceScheduleDataElements::PowerSequenceScheduleDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_startTimeIsSet(false),
      m_endTimeIsSet(false)

{}

PowerSequenceScheduleDataElements::PowerSequenceScheduleDataElements(
    xs_boolean c_sequenceIdIsSet, xs_boolean c_startTimeIsSet,
    xs_boolean c_endTimeIsSet)
    : DataElements(), m_sequenceIdIsSet(c_sequenceIdIsSet),
      m_startTimeIsSet(c_startTimeIsSet), m_endTimeIsSet(c_endTimeIsSet)

{}

bool PowerSequenceScheduleDataElements::
operator==(const PowerSequenceScheduleDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_startTimeIsSet != c_classObject.m_startTimeIsSet) {
    return false;
  }
  if (m_endTimeIsSet != c_classObject.m_endTimeIsSet) {
    return false;
  }

  return true;
}

bool PowerSequenceScheduleDataElements::
operator!=(const PowerSequenceScheduleDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceScheduleDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_startTimeIsSet && !m_endTimeIsSet;
}

DataElements::Type PowerSequenceScheduleDataElements::getDataType() const {
  return DataElements::Type::POWER_SEQUENCE_SCHEDULE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerSequenceScheduleDataElements::clone() const {
  return std::make_shared<PowerSequenceScheduleDataElements>(*this);
}

void PowerSequenceScheduleDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerSequenceScheduleDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerSequenceScheduleDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceScheduleDataElements::setStartTime() {
  m_startTimeIsSet = true;
}

void PowerSequenceScheduleDataElements::cleanStartTime() {
  m_startTimeIsSet = false;
}

bool PowerSequenceScheduleDataElements::getStartTimeIsSet() const {
  return m_startTimeIsSet;
}

void PowerSequenceScheduleDataElements::setEndTime() { m_endTimeIsSet = true; }

void PowerSequenceScheduleDataElements::cleanEndTime() {
  m_endTimeIsSet = false;
}

bool PowerSequenceScheduleDataElements::getEndTimeIsSet() const {
  return m_endTimeIsSet;
}

bool PowerSequenceScheduleDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "startTime", "endTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "startTime")) {
      m_startTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "endTime")) {
      m_endTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceScheduleDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_startTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("startTime");
  }
  if (m_endTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("endTime");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram