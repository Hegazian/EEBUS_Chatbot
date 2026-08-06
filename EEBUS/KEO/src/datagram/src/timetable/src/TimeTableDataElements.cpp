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

#include <keo_datagram/timetable/TimeTableDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableDataElements::TimeTableDataElements()
    : DataElements(), m_timeTableIdIsSet(false), m_timeSlotIdIsSet(false),
      m_recurrenceInformationIsSet(false),
      m_recurrenceInformation(RecurrenceInformationElements()),
      m_startTimeIsSet(false), m_startTime(AbsoluteOrRecurringTimeElements()),
      m_endTimeIsSet(false), m_endTime(AbsoluteOrRecurringTimeElements())

{}

bool TimeTableDataElements::
operator==(const TimeTableDataElements &c_classObject) const {
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet) {
    return false;
  }
  if (m_timeSlotIdIsSet != c_classObject.m_timeSlotIdIsSet) {
    return false;
  }
  if (m_recurrenceInformationIsSet !=
          c_classObject.m_recurrenceInformationIsSet ||
      (m_recurrenceInformationIsSet &&
       (m_recurrenceInformation != c_classObject.m_recurrenceInformation))) {
    return false;
  }
  if (m_startTimeIsSet != c_classObject.m_startTimeIsSet ||
      (m_startTimeIsSet && (m_startTime != c_classObject.m_startTime))) {
    return false;
  }
  if (m_endTimeIsSet != c_classObject.m_endTimeIsSet ||
      (m_endTimeIsSet && (m_endTime != c_classObject.m_endTime))) {
    return false;
  }

  return true;
}

bool TimeTableDataElements::
operator!=(const TimeTableDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableDataElements::isEmpty() const {
  return !m_timeTableIdIsSet && !m_timeSlotIdIsSet &&
         !m_recurrenceInformationIsSet && !m_startTimeIsSet && !m_endTimeIsSet;
}

DataElements::Type TimeTableDataElements::getDataType() const {
  return DataElements::Type::TIME_TABLE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimeTableDataElements::clone() const {
  return std::make_shared<TimeTableDataElements>(*this);
}

void TimeTableDataElements::setTimeTableId() { m_timeTableIdIsSet = true; }

void TimeTableDataElements::cleanTimeTableId() { m_timeTableIdIsSet = false; }

bool TimeTableDataElements::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TimeTableDataElements::setTimeSlotId() { m_timeSlotIdIsSet = true; }

void TimeTableDataElements::cleanTimeSlotId() { m_timeSlotIdIsSet = false; }

bool TimeTableDataElements::getTimeSlotIdIsSet() const {
  return m_timeSlotIdIsSet;
}

void TimeTableDataElements::setRecurrenceInformation(
    const RecurrenceInformationElements &recurrenceInformation) {
  m_recurrenceInformation = recurrenceInformation;
  m_recurrenceInformationIsSet = true;
}

const RecurrenceInformationElements &
TimeTableDataElements::getRecurrenceInformation() const {
  return m_recurrenceInformation;
}

void TimeTableDataElements::cleanRecurrenceInformation() {
  m_recurrenceInformation = RecurrenceInformationElements();
  m_recurrenceInformationIsSet = false;
}

bool TimeTableDataElements::getRecurrenceInformationIsSet() const {
  return m_recurrenceInformationIsSet;
}

void TimeTableDataElements::setStartTime(
    const AbsoluteOrRecurringTimeElements &startTime) {
  m_startTime = startTime;
  m_startTimeIsSet = true;
}

const AbsoluteOrRecurringTimeElements &
TimeTableDataElements::getStartTime() const {
  return m_startTime;
}

void TimeTableDataElements::cleanStartTime() {
  m_startTime = AbsoluteOrRecurringTimeElements();
  m_startTimeIsSet = false;
}

bool TimeTableDataElements::getStartTimeIsSet() const {
  return m_startTimeIsSet;
}

void TimeTableDataElements::setEndTime(
    const AbsoluteOrRecurringTimeElements &endTime) {
  m_endTime = endTime;
  m_endTimeIsSet = true;
}

const AbsoluteOrRecurringTimeElements &
TimeTableDataElements::getEndTime() const {
  return m_endTime;
}

void TimeTableDataElements::cleanEndTime() {
  m_endTime = AbsoluteOrRecurringTimeElements();
  m_endTimeIsSet = false;
}

bool TimeTableDataElements::getEndTimeIsSet() const { return m_endTimeIsSet; }

bool TimeTableDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeTableId", "timeSlotId", "recurrenceInformation",
                   "startTime", "endTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeTableId")) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSlotId")) {
      m_timeSlotIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "recurrenceInformation",
                                   &m_recurrenceInformation)) {
      m_recurrenceInformationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "startTime", &m_startTime)) {
      m_startTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "endTime", &m_endTime)) {
      m_endTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableDataElements::toJson() const {
  std::string result = "[";
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeTableId");
  }
  if (m_timeSlotIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSlotId");
  }
  if (m_recurrenceInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("recurrenceInformation",
                                           m_recurrenceInformation);
  }
  if (m_startTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("startTime", m_startTime);
  }
  if (m_endTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("endTime", m_endTime);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram