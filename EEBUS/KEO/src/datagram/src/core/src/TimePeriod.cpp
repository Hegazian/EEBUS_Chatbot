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

#include <keo_datagram/core/TimePeriod.h>

#include <keo_datagram/core/TimePeriodElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimePeriod::TimePeriod()
    : m_startTimeIsSet(false), m_startTime(AbsoluteOrRelativeTime()),
      m_endTimeIsSet(false), m_endTime(AbsoluteOrRelativeTime())

{}

TimePeriod::TimePeriod(const AbsoluteOrRelativeTime &c_startTime,
                       const AbsoluteOrRelativeTime &c_endTime)
    : m_startTimeIsSet(true), m_startTime(c_startTime), m_endTimeIsSet(true),
      m_endTime(c_endTime)

{}

bool TimePeriod::operator==(const TimePeriod &c_classObject) const {
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

bool TimePeriod::operator!=(const TimePeriod &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimePeriod::isEmpty() const {
  return !m_startTimeIsSet && !m_endTimeIsSet;
}

void TimePeriod::setStartTime(const AbsoluteOrRelativeTime &startTime) {
  m_startTime = startTime;
  m_startTimeIsSet = true;
}

const AbsoluteOrRelativeTime &TimePeriod::getStartTime() const {
  return m_startTime;
}

void TimePeriod::cleanStartTime() {
  m_startTime = AbsoluteOrRelativeTime();
  m_startTimeIsSet = false;
}

bool TimePeriod::getStartTimeIsSet() const { return m_startTimeIsSet; }

void TimePeriod::setEndTime(const AbsoluteOrRelativeTime &endTime) {
  m_endTime = endTime;
  m_endTimeIsSet = true;
}

const AbsoluteOrRelativeTime &TimePeriod::getEndTime() const {
  return m_endTime;
}

void TimePeriod::cleanEndTime() {
  m_endTime = AbsoluteOrRelativeTime();
  m_endTimeIsSet = false;
}

bool TimePeriod::getEndTimeIsSet() const { return m_endTimeIsSet; }

TimePeriod TimePeriod::reduce(const TimePeriodElements &elements) const {
  TimePeriod dataOut;
  if (getStartTimeIsSet() && elements.getStartTimeIsSet()) {
    dataOut.setStartTime(getStartTime());
  }
  if (getEndTimeIsSet() && elements.getEndTimeIsSet()) {
    dataOut.setEndTime(getEndTime());
  }
  return dataOut;
}

bool TimePeriod::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"startTime", "endTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
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

std::string TimePeriod::toJson() const {
  std::string result = "[";
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