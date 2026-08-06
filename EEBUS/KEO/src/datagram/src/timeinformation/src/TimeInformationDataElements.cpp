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

#include <keo_datagram/timeinformation/TimeInformationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeInformationDataElements::TimeInformationDataElements()
    : DataElements(), m_utcIsSet(false), m_utcOffsetIsSet(false),
      m_dayOfWeekIsSet(false), m_calendarWeekIsSet(false)

{}

bool TimeInformationDataElements::
operator==(const TimeInformationDataElements &c_classObject) const {
  if (m_utcIsSet != c_classObject.m_utcIsSet) {
    return false;
  }
  if (m_utcOffsetIsSet != c_classObject.m_utcOffsetIsSet) {
    return false;
  }
  if (m_dayOfWeekIsSet != c_classObject.m_dayOfWeekIsSet) {
    return false;
  }
  if (m_calendarWeekIsSet != c_classObject.m_calendarWeekIsSet) {
    return false;
  }

  return true;
}

bool TimeInformationDataElements::
operator!=(const TimeInformationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeInformationDataElements::isEmpty() const {
  return !m_utcIsSet && !m_utcOffsetIsSet && !m_dayOfWeekIsSet &&
         !m_calendarWeekIsSet;
}

DataElements::Type TimeInformationDataElements::getDataType() const {
  return DataElements::Type::TIME_INFORMATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimeInformationDataElements::clone() const {
  return std::make_shared<TimeInformationDataElements>(*this);
}

void TimeInformationDataElements::setUtc() { m_utcIsSet = true; }

void TimeInformationDataElements::cleanUtc() { m_utcIsSet = false; }

bool TimeInformationDataElements::getUtcIsSet() const { return m_utcIsSet; }

void TimeInformationDataElements::setUtcOffset() { m_utcOffsetIsSet = true; }

void TimeInformationDataElements::cleanUtcOffset() { m_utcOffsetIsSet = false; }

bool TimeInformationDataElements::getUtcOffsetIsSet() const {
  return m_utcOffsetIsSet;
}

void TimeInformationDataElements::setDayOfWeek() { m_dayOfWeekIsSet = true; }

void TimeInformationDataElements::cleanDayOfWeek() { m_dayOfWeekIsSet = false; }

bool TimeInformationDataElements::getDayOfWeekIsSet() const {
  return m_dayOfWeekIsSet;
}

void TimeInformationDataElements::setCalendarWeek() {
  m_calendarWeekIsSet = true;
}

void TimeInformationDataElements::cleanCalendarWeek() {
  m_calendarWeekIsSet = false;
}

bool TimeInformationDataElements::getCalendarWeekIsSet() const {
  return m_calendarWeekIsSet;
}

bool TimeInformationDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"utc", "utcOffset", "dayOfWeek", "calendarWeek"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "utc")) {
      m_utcIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "utcOffset")) {
      m_utcOffsetIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "dayOfWeek")) {
      m_dayOfWeekIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "calendarWeek")) {
      m_calendarWeekIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeInformationDataElements::toJson() const {
  std::string result = "[";
  if (m_utcIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("utc");
  }
  if (m_utcOffsetIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("utcOffset");
  }
  if (m_dayOfWeekIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("dayOfWeek");
  }
  if (m_calendarWeekIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("calendarWeek");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram