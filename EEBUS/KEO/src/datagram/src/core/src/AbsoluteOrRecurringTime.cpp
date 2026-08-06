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

#include <keo_datagram/core/AbsoluteOrRecurringTime.h>

#include <keo_datagram/core/AbsoluteOrRecurringTimeElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

AbsoluteOrRecurringTime::AbsoluteOrRecurringTime()
    : m_dateTimeIsSet(false), m_dateTime(xs_dateTime()), m_monthIsSet(false),
      m_month(Month()), m_dayOfMonthIsSet(false), m_dayOfMonth(0),
      m_calendarWeekIsSet(false), m_calendarWeek(0),
      m_dayOfWeekOccurrenceIsSet(false), m_dayOfWeekOccurrence(Occurrence()),
      m_daysOfWeekIsSet(false), m_daysOfWeek(DaysOfWeek()), m_timeIsSet(false),
      m_time(xs_time()), m_relativeIsSet(false), m_relative(xs_duration())

{}

bool AbsoluteOrRecurringTime::
operator==(const AbsoluteOrRecurringTime &c_classObject) const {
  if (m_dateTimeIsSet != c_classObject.m_dateTimeIsSet ||
      (m_dateTimeIsSet && (m_dateTime != c_classObject.m_dateTime))) {
    return false;
  }
  if (m_monthIsSet != c_classObject.m_monthIsSet ||
      (m_monthIsSet && (m_month != c_classObject.m_month))) {
    return false;
  }
  if (m_dayOfMonthIsSet != c_classObject.m_dayOfMonthIsSet ||
      (m_dayOfMonthIsSet && (m_dayOfMonth != c_classObject.m_dayOfMonth))) {
    return false;
  }
  if (m_calendarWeekIsSet != c_classObject.m_calendarWeekIsSet ||
      (m_calendarWeekIsSet &&
       (m_calendarWeek != c_classObject.m_calendarWeek))) {
    return false;
  }
  if (m_dayOfWeekOccurrenceIsSet != c_classObject.m_dayOfWeekOccurrenceIsSet ||
      (m_dayOfWeekOccurrenceIsSet &&
       (m_dayOfWeekOccurrence != c_classObject.m_dayOfWeekOccurrence))) {
    return false;
  }
  if (m_daysOfWeekIsSet != c_classObject.m_daysOfWeekIsSet ||
      (m_daysOfWeekIsSet && (m_daysOfWeek != c_classObject.m_daysOfWeek))) {
    return false;
  }
  if (m_timeIsSet != c_classObject.m_timeIsSet ||
      (m_timeIsSet && (m_time != c_classObject.m_time))) {
    return false;
  }
  if (m_relativeIsSet != c_classObject.m_relativeIsSet ||
      (m_relativeIsSet && (m_relative != c_classObject.m_relative))) {
    return false;
  }

  return true;
}

bool AbsoluteOrRecurringTime::
operator!=(const AbsoluteOrRecurringTime &c_classObject) const {
  return !(*this == c_classObject);
}

bool AbsoluteOrRecurringTime::isEmpty() const {
  return !m_dateTimeIsSet && !m_monthIsSet && !m_dayOfMonthIsSet &&
         !m_calendarWeekIsSet && !m_dayOfWeekOccurrenceIsSet &&
         !m_daysOfWeekIsSet && !m_timeIsSet && !m_relativeIsSet;
}

void AbsoluteOrRecurringTime::setDateTime(const xs_dateTime &dateTime) {
  m_dateTime = dateTime;
  m_dateTimeIsSet = true;
}

const xs_dateTime &AbsoluteOrRecurringTime::getDateTime() const {
  return m_dateTime;
}

void AbsoluteOrRecurringTime::cleanDateTime() {
  m_dateTime = xs_dateTime();
  m_dateTimeIsSet = false;
}

bool AbsoluteOrRecurringTime::getDateTimeIsSet() const {
  return m_dateTimeIsSet;
}

void AbsoluteOrRecurringTime::setMonth(const Month &month) {
  m_month = month;
  m_monthIsSet = true;
}

const Month &AbsoluteOrRecurringTime::getMonth() const { return m_month; }

void AbsoluteOrRecurringTime::cleanMonth() {
  m_month = Month();
  m_monthIsSet = false;
}

bool AbsoluteOrRecurringTime::getMonthIsSet() const { return m_monthIsSet; }

void AbsoluteOrRecurringTime::setDayOfMonth(const xs_unsignedByte &dayOfMonth) {
  m_dayOfMonth = dayOfMonth;
  m_dayOfMonthIsSet = true;
}

const xs_unsignedByte &AbsoluteOrRecurringTime::getDayOfMonth() const {
  return m_dayOfMonth;
}

void AbsoluteOrRecurringTime::cleanDayOfMonth() {
  m_dayOfMonth = 0;
  m_dayOfMonthIsSet = false;
}

bool AbsoluteOrRecurringTime::getDayOfMonthIsSet() const {
  return m_dayOfMonthIsSet;
}

void AbsoluteOrRecurringTime::setCalendarWeek(
    const xs_unsignedByte &calendarWeek) {
  m_calendarWeek = calendarWeek;
  m_calendarWeekIsSet = true;
}

const xs_unsignedByte &AbsoluteOrRecurringTime::getCalendarWeek() const {
  return m_calendarWeek;
}

void AbsoluteOrRecurringTime::cleanCalendarWeek() {
  m_calendarWeek = 0;
  m_calendarWeekIsSet = false;
}

bool AbsoluteOrRecurringTime::getCalendarWeekIsSet() const {
  return m_calendarWeekIsSet;
}

void AbsoluteOrRecurringTime::setDayOfWeekOccurrence(
    const Occurrence &dayOfWeekOccurrence) {
  m_dayOfWeekOccurrence = dayOfWeekOccurrence;
  m_dayOfWeekOccurrenceIsSet = true;
}

const Occurrence &AbsoluteOrRecurringTime::getDayOfWeekOccurrence() const {
  return m_dayOfWeekOccurrence;
}

void AbsoluteOrRecurringTime::cleanDayOfWeekOccurrence() {
  m_dayOfWeekOccurrence = Occurrence();
  m_dayOfWeekOccurrenceIsSet = false;
}

bool AbsoluteOrRecurringTime::getDayOfWeekOccurrenceIsSet() const {
  return m_dayOfWeekOccurrenceIsSet;
}

void AbsoluteOrRecurringTime::setDaysOfWeek(const DaysOfWeek &daysOfWeek) {
  m_daysOfWeek = daysOfWeek;
  m_daysOfWeekIsSet = true;
}

const DaysOfWeek &AbsoluteOrRecurringTime::getDaysOfWeek() const {
  return m_daysOfWeek;
}

void AbsoluteOrRecurringTime::cleanDaysOfWeek() {
  m_daysOfWeek = DaysOfWeek();
  m_daysOfWeekIsSet = false;
}

bool AbsoluteOrRecurringTime::getDaysOfWeekIsSet() const {
  return m_daysOfWeekIsSet;
}

void AbsoluteOrRecurringTime::setTime(const xs_time &time) {
  m_time = time;
  m_timeIsSet = true;
}

const xs_time &AbsoluteOrRecurringTime::getTime() const { return m_time; }

void AbsoluteOrRecurringTime::cleanTime() {
  m_time = xs_time();
  m_timeIsSet = false;
}

bool AbsoluteOrRecurringTime::getTimeIsSet() const { return m_timeIsSet; }

void AbsoluteOrRecurringTime::setRelative(const xs_duration &relative) {
  m_relative = relative;
  m_relativeIsSet = true;
}

const xs_duration &AbsoluteOrRecurringTime::getRelative() const {
  return m_relative;
}

void AbsoluteOrRecurringTime::cleanRelative() {
  m_relative = xs_duration();
  m_relativeIsSet = false;
}

bool AbsoluteOrRecurringTime::getRelativeIsSet() const {
  return m_relativeIsSet;
}

AbsoluteOrRecurringTime AbsoluteOrRecurringTime::reduce(
    const AbsoluteOrRecurringTimeElements &elements) const {
  AbsoluteOrRecurringTime dataOut;
  if (getDateTimeIsSet() && elements.getDateTimeIsSet()) {
    dataOut.setDateTime(getDateTime());
  }
  if (getMonthIsSet() && elements.getMonthIsSet()) {
    dataOut.setMonth(getMonth());
  }
  if (getDayOfMonthIsSet() && elements.getDayOfMonthIsSet()) {
    dataOut.setDayOfMonth(getDayOfMonth());
  }
  if (getCalendarWeekIsSet() && elements.getCalendarWeekIsSet()) {
    dataOut.setCalendarWeek(getCalendarWeek());
  }
  if (getDayOfWeekOccurrenceIsSet() && elements.getDayOfWeekOccurrenceIsSet()) {
    dataOut.setDayOfWeekOccurrence(getDayOfWeekOccurrence());
  }
  if (getDaysOfWeekIsSet() && elements.getDaysOfWeekIsSet()) {
    dataOut.setDaysOfWeek(getDaysOfWeek());
  }
  if (getTimeIsSet() && elements.getTimeIsSet()) {
    dataOut.setTime(getTime());
  }
  if (getRelativeIsSet() && elements.getRelativeIsSet()) {
    dataOut.setRelative(getRelative());
  }
  return dataOut;
}

bool AbsoluteOrRecurringTime::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"dateTime", "month", "dayOfMonth", "calendarWeek",
                   "dayOfWeekOccurrence", "daysOfWeek", "time", "relative"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "dateTime", &m_dateTime)) {
      m_dateTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "month", &m_month)) {
      m_monthIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "dayOfMonth", &m_dayOfMonth)) {
      m_dayOfMonthIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "calendarWeek", &m_calendarWeek)) {
      m_calendarWeekIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "dayOfWeekOccurrence",
                                   &m_dayOfWeekOccurrence)) {
      m_dayOfWeekOccurrenceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "daysOfWeek", &m_daysOfWeek)) {
      m_daysOfWeekIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "time", &m_time)) {
      m_timeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "relative", &m_relative)) {
      m_relativeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string AbsoluteOrRecurringTime::toJson() const {
  std::string result = "[";
  if (m_dateTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("dateTime", m_dateTime);
  }
  if (m_monthIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("month", m_month);
  }
  if (m_dayOfMonthIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("dayOfMonth", m_dayOfMonth);
  }
  if (m_calendarWeekIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("calendarWeek", m_calendarWeek);
  }
  if (m_dayOfWeekOccurrenceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("dayOfWeekOccurrence",
                                           m_dayOfWeekOccurrence);
  }
  if (m_daysOfWeekIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("daysOfWeek", m_daysOfWeek);
  }
  if (m_timeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("time", m_time);
  }
  if (m_relativeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("relative", m_relative);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram