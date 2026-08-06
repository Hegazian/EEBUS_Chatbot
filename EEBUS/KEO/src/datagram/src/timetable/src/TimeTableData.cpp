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

#include <keo_datagram/timetable/TimeTableData.h>

#include <keo_datagram/timetable/TimeTableDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableData::TimeTableData()
    : m_timeTableIdIsSet(false), m_timeTableId(0), m_timeSlotIdIsSet(false),
      m_timeSlotId(0), m_recurrenceInformationIsSet(false),
      m_recurrenceInformation(RecurrenceInformation()), m_startTimeIsSet(false),
      m_startTime(AbsoluteOrRecurringTime()), m_endTimeIsSet(false),
      m_endTime(AbsoluteOrRecurringTime())

{}

bool TimeTableData::operator==(const TimeTableData &c_classObject) const {
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
    return false;
  }
  if (m_timeSlotIdIsSet != c_classObject.m_timeSlotIdIsSet ||
      (m_timeSlotIdIsSet && (m_timeSlotId != c_classObject.m_timeSlotId))) {
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

bool TimeTableData::operator!=(const TimeTableData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableData::isEmpty() const {
  return !m_timeTableIdIsSet && !m_timeSlotIdIsSet &&
         !m_recurrenceInformationIsSet && !m_startTimeIsSet && !m_endTimeIsSet;
}

void TimeTableData::setTimeTableId(const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &TimeTableData::getTimeTableId() const {
  return m_timeTableId;
}

void TimeTableData::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool TimeTableData::getTimeTableIdIsSet() const { return m_timeTableIdIsSet; }

void TimeTableData::setTimeSlotId(const xs_unsignedInt &timeSlotId) {
  m_timeSlotId = timeSlotId;
  m_timeSlotIdIsSet = true;
}

const xs_unsignedInt &TimeTableData::getTimeSlotId() const {
  return m_timeSlotId;
}

void TimeTableData::cleanTimeSlotId() {
  m_timeSlotId = 0;
  m_timeSlotIdIsSet = false;
}

bool TimeTableData::getTimeSlotIdIsSet() const { return m_timeSlotIdIsSet; }

void TimeTableData::setRecurrenceInformation(
    const RecurrenceInformation &recurrenceInformation) {
  m_recurrenceInformation = recurrenceInformation;
  m_recurrenceInformationIsSet = true;
}

const RecurrenceInformation &TimeTableData::getRecurrenceInformation() const {
  return m_recurrenceInformation;
}

void TimeTableData::cleanRecurrenceInformation() {
  m_recurrenceInformation = RecurrenceInformation();
  m_recurrenceInformationIsSet = false;
}

bool TimeTableData::getRecurrenceInformationIsSet() const {
  return m_recurrenceInformationIsSet;
}

void TimeTableData::setStartTime(const AbsoluteOrRecurringTime &startTime) {
  m_startTime = startTime;
  m_startTimeIsSet = true;
}

const AbsoluteOrRecurringTime &TimeTableData::getStartTime() const {
  return m_startTime;
}

void TimeTableData::cleanStartTime() {
  m_startTime = AbsoluteOrRecurringTime();
  m_startTimeIsSet = false;
}

bool TimeTableData::getStartTimeIsSet() const { return m_startTimeIsSet; }

void TimeTableData::setEndTime(const AbsoluteOrRecurringTime &endTime) {
  m_endTime = endTime;
  m_endTimeIsSet = true;
}

const AbsoluteOrRecurringTime &TimeTableData::getEndTime() const {
  return m_endTime;
}

void TimeTableData::cleanEndTime() {
  m_endTime = AbsoluteOrRecurringTime();
  m_endTimeIsSet = false;
}

bool TimeTableData::getEndTimeIsSet() const { return m_endTimeIsSet; }

TimeTableData
TimeTableData::reduce(const TimeTableDataElements &elements) const {
  TimeTableData dataOut;
  if (getTimeTableIdIsSet() && elements.getTimeTableIdIsSet()) {
    dataOut.setTimeTableId(getTimeTableId());
  }
  if (getTimeSlotIdIsSet() && elements.getTimeSlotIdIsSet()) {
    dataOut.setTimeSlotId(getTimeSlotId());
  }
  if (getRecurrenceInformationIsSet() &&
      elements.getRecurrenceInformationIsSet()) {
    dataOut.setRecurrenceInformation(
        getRecurrenceInformation().reduce(elements.getRecurrenceInformation()));
  }
  if (getStartTimeIsSet() && elements.getStartTimeIsSet()) {
    dataOut.setStartTime(getStartTime().reduce(elements.getStartTime()));
  }
  if (getEndTimeIsSet() && elements.getEndTimeIsSet()) {
    dataOut.setEndTime(getEndTime().reduce(elements.getEndTime()));
  }
  return dataOut;
}

bool TimeTableData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeTableId", "timeSlotId", "recurrenceInformation",
                   "startTime", "endTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeTableId", &m_timeTableId)) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSlotId", &m_timeSlotId)) {
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

std::string TimeTableData::toJson() const {
  std::string result = "[";
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  if (m_timeSlotIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSlotId", m_timeSlotId);
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