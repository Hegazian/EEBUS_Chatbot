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

#include <keo_datagram/timetable/TimeTableDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableDescriptionListDataSelectors::TimeTableDescriptionListDataSelectors()
    : DataSelectors(), m_timeTableIdIsSet(false), m_timeTableId(0)

{}

TimeTableDescriptionListDataSelectors::TimeTableDescriptionListDataSelectors(
    const xs_unsignedInt &c_timeTableId) {
  setTimeTableId(c_timeTableId);
}

bool TimeTableDescriptionListDataSelectors::
operator==(const TimeTableDescriptionListDataSelectors &c_classObject) const {
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
    return false;
  }

  return true;
}

bool TimeTableDescriptionListDataSelectors::
operator!=(const TimeTableDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableDescriptionListDataSelectors::isEmpty() const {
  return !m_timeTableIdIsSet;
}

DataSelectors::Type TimeTableDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TimeTableDescriptionListDataSelectors::clone() const {
  return std::make_shared<TimeTableDescriptionListDataSelectors>(*this);
}

void TimeTableDescriptionListDataSelectors::setTimeTableId(
    const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &
TimeTableDescriptionListDataSelectors::getTimeTableId() const {
  return m_timeTableId;
}

void TimeTableDescriptionListDataSelectors::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool TimeTableDescriptionListDataSelectors::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

bool TimeTableDescriptionListDataSelectors::selects(
    const TimeTableDescriptionData &data) const {
  if (getTimeTableIdIsSet() && (!data.getTimeTableIdIsSet() ||
                                getTimeTableId() != data.getTimeTableId())) {
    return false;
  }
  return true;
}

bool TimeTableDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"timeTableId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeTableId", &m_timeTableId)) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram