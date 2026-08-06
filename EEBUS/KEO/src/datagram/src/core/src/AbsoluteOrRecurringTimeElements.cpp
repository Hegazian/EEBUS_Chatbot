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

#include <keo_datagram/core/AbsoluteOrRecurringTimeElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

AbsoluteOrRecurringTimeElements::AbsoluteOrRecurringTimeElements()
    : m_dateTimeIsSet(false), m_monthIsSet(false), m_dayOfMonthIsSet(false),
      m_calendarWeekIsSet(false), m_dayOfWeekOccurrenceIsSet(false),
      m_daysOfWeekIsSet(false), m_timeIsSet(false), m_relativeIsSet(false)

{}

bool AbsoluteOrRecurringTimeElements::
operator==(const AbsoluteOrRecurringTimeElements &c_classObject) const {
  if (m_dateTimeIsSet != c_classObject.m_dateTimeIsSet) {
    return false;
  }
  if (m_monthIsSet != c_classObject.m_monthIsSet) {
    return false;
  }
  if (m_dayOfMonthIsSet != c_classObject.m_dayOfMonthIsSet) {
    return false;
  }
  if (m_calendarWeekIsSet != c_classObject.m_calendarWeekIsSet) {
    return false;
  }
  if (m_dayOfWeekOccurrenceIsSet != c_classObject.m_dayOfWeekOccurrenceIsSet) {
    return false;
  }
  if (m_daysOfWeekIsSet != c_classObject.m_daysOfWeekIsSet) {
    return false;
  }
  if (m_timeIsSet != c_classObject.m_timeIsSet) {
    return false;
  }
  if (m_relativeIsSet != c_classObject.m_relativeIsSet) {
    return false;
  }

  return true;
}

bool AbsoluteOrRecurringTimeElements::
operator!=(const AbsoluteOrRecurringTimeElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool AbsoluteOrRecurringTimeElements::isEmpty() const {
  return !m_dateTimeIsSet && !m_monthIsSet && !m_dayOfMonthIsSet &&
         !m_calendarWeekIsSet && !m_dayOfWeekOccurrenceIsSet &&
         !m_daysOfWeekIsSet && !m_timeIsSet && !m_relativeIsSet;
}

void AbsoluteOrRecurringTimeElements::setDateTime() { m_dateTimeIsSet = true; }

void AbsoluteOrRecurringTimeElements::cleanDateTime() {
  m_dateTimeIsSet = false;
}

bool AbsoluteOrRecurringTimeElements::getDateTimeIsSet() const {
  return m_dateTimeIsSet;
}

void AbsoluteOrRecurringTimeElements::setMonth() { m_monthIsSet = true; }

void AbsoluteOrRecurringTimeElements::cleanMonth() { m_monthIsSet = false; }

bool AbsoluteOrRecurringTimeElements::getMonthIsSet() const {
  return m_monthIsSet;
}

void AbsoluteOrRecurringTimeElements::setDayOfMonth() {
  m_dayOfMonthIsSet = true;
}

void AbsoluteOrRecurringTimeElements::cleanDayOfMonth() {
  m_dayOfMonthIsSet = false;
}

bool AbsoluteOrRecurringTimeElements::getDayOfMonthIsSet() const {
  return m_dayOfMonthIsSet;
}

void AbsoluteOrRecurringTimeElements::setCalendarWeek() {
  m_calendarWeekIsSet = true;
}

void AbsoluteOrRecurringTimeElements::cleanCalendarWeek() {
  m_calendarWeekIsSet = false;
}

bool AbsoluteOrRecurringTimeElements::getCalendarWeekIsSet() const {
  return m_calendarWeekIsSet;
}

void AbsoluteOrRecurringTimeElements::setDayOfWeekOccurrence() {
  m_dayOfWeekOccurrenceIsSet = true;
}

void AbsoluteOrRecurringTimeElements::cleanDayOfWeekOccurrence() {
  m_dayOfWeekOccurrenceIsSet = false;
}

bool AbsoluteOrRecurringTimeElements::getDayOfWeekOccurrenceIsSet() const {
  return m_dayOfWeekOccurrenceIsSet;
}

void AbsoluteOrRecurringTimeElements::setDaysOfWeek() {
  m_daysOfWeekIsSet = true;
}

void AbsoluteOrRecurringTimeElements::cleanDaysOfWeek() {
  m_daysOfWeekIsSet = false;
}

bool AbsoluteOrRecurringTimeElements::getDaysOfWeekIsSet() const {
  return m_daysOfWeekIsSet;
}

void AbsoluteOrRecurringTimeElements::setTime() { m_timeIsSet = true; }

void AbsoluteOrRecurringTimeElements::cleanTime() { m_timeIsSet = false; }

bool AbsoluteOrRecurringTimeElements::getTimeIsSet() const {
  return m_timeIsSet;
}

void AbsoluteOrRecurringTimeElements::setRelative() { m_relativeIsSet = true; }

void AbsoluteOrRecurringTimeElements::cleanRelative() {
  m_relativeIsSet = false;
}

bool AbsoluteOrRecurringTimeElements::getRelativeIsSet() const {
  return m_relativeIsSet;
}

bool AbsoluteOrRecurringTimeElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"dateTime", "month", "dayOfMonth", "calendarWeek",
                   "dayOfWeekOccurrence", "daysOfWeek", "time", "relative"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "dateTime")) {
      m_dateTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "month")) {
      m_monthIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "dayOfMonth")) {
      m_dayOfMonthIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "calendarWeek")) {
      m_calendarWeekIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "dayOfWeekOccurrence")) {
      m_dayOfWeekOccurrenceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "daysOfWeek")) {
      m_daysOfWeekIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "time")) {
      m_timeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "relative")) {
      m_relativeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string AbsoluteOrRecurringTimeElements::toJson() const {
  std::string result = "[";
  if (m_dateTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("dateTime");
  }
  if (m_monthIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("month");
  }
  if (m_dayOfMonthIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("dayOfMonth");
  }
  if (m_calendarWeekIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("calendarWeek");
  }
  if (m_dayOfWeekOccurrenceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("dayOfWeekOccurrence");
  }
  if (m_daysOfWeekIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("daysOfWeek");
  }
  if (m_timeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("time");
  }
  if (m_relativeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("relative");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram