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

#include <keo_datagram/timetable/TimeTableListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableListDataSelectors::TimeTableListDataSelectors()
    : DataSelectors(), m_timeTableIdIsSet(false), m_timeTableId(0),
      m_timeSlotIdIsSet(false), m_timeSlotId(0)

{}

TimeTableListDataSelectors::TimeTableListDataSelectors(
    const xs_unsignedInt &c_timeTableId, const xs_unsignedInt &c_timeSlotId)
    : DataSelectors(), m_timeTableIdIsSet(true), m_timeTableId(c_timeTableId),
      m_timeSlotIdIsSet(true), m_timeSlotId(c_timeSlotId)

{}

bool TimeTableListDataSelectors::
operator==(const TimeTableListDataSelectors &c_classObject) const {
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
    return false;
  }
  if (m_timeSlotIdIsSet != c_classObject.m_timeSlotIdIsSet ||
      (m_timeSlotIdIsSet && (m_timeSlotId != c_classObject.m_timeSlotId))) {
    return false;
  }

  return true;
}

bool TimeTableListDataSelectors::
operator!=(const TimeTableListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableListDataSelectors::isEmpty() const {
  return !m_timeTableIdIsSet && !m_timeSlotIdIsSet;
}

DataSelectors::Type TimeTableListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIME_TABLE_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TimeTableListDataSelectors::clone() const {
  return std::make_shared<TimeTableListDataSelectors>(*this);
}

void TimeTableListDataSelectors::setTimeTableId(
    const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &TimeTableListDataSelectors::getTimeTableId() const {
  return m_timeTableId;
}

void TimeTableListDataSelectors::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool TimeTableListDataSelectors::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TimeTableListDataSelectors::setTimeSlotId(
    const xs_unsignedInt &timeSlotId) {
  m_timeSlotId = timeSlotId;
  m_timeSlotIdIsSet = true;
}

const xs_unsignedInt &TimeTableListDataSelectors::getTimeSlotId() const {
  return m_timeSlotId;
}

void TimeTableListDataSelectors::cleanTimeSlotId() {
  m_timeSlotId = 0;
  m_timeSlotIdIsSet = false;
}

bool TimeTableListDataSelectors::getTimeSlotIdIsSet() const {
  return m_timeSlotIdIsSet;
}

bool TimeTableListDataSelectors::selects(const TimeTableData &data) const {
  if (getTimeTableIdIsSet() && (!data.getTimeTableIdIsSet() ||
                                getTimeTableId() != data.getTimeTableId())) {
    return false;
  }
  if (getTimeSlotIdIsSet() &&
      (!data.getTimeSlotIdIsSet() || getTimeSlotId() != data.getTimeSlotId())) {
    return false;
  }
  return true;
}

bool TimeTableListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeTableId", "timeSlotId"})) {
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
  }
  return true;
}

std::string TimeTableListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  if (m_timeSlotIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSlotId", m_timeSlotId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram