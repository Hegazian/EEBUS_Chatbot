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

#include <keo_datagram/timeinformation/TimeInformationData.h>

#include <keo_datagram/timeinformation/TimeInformationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeInformationData::TimeInformationData()
    : CmdData(), m_utcIsSet(false), m_utc(xs_dateTime()),
      m_utcOffsetIsSet(false), m_utcOffset(xs_duration()),
      m_dayOfWeekIsSet(false), m_dayOfWeek(DayOfWeek()),
      m_calendarWeekIsSet(false), m_calendarWeek(0)

{}

bool TimeInformationData::
operator==(const TimeInformationData &c_classObject) const {
  if (m_utcIsSet != c_classObject.m_utcIsSet ||
      (m_utcIsSet && (m_utc != c_classObject.m_utc))) {
    return false;
  }
  if (m_utcOffsetIsSet != c_classObject.m_utcOffsetIsSet ||
      (m_utcOffsetIsSet && (m_utcOffset != c_classObject.m_utcOffset))) {
    return false;
  }
  if (m_dayOfWeekIsSet != c_classObject.m_dayOfWeekIsSet ||
      (m_dayOfWeekIsSet && (m_dayOfWeek != c_classObject.m_dayOfWeek))) {
    return false;
  }
  if (m_calendarWeekIsSet != c_classObject.m_calendarWeekIsSet ||
      (m_calendarWeekIsSet &&
       (m_calendarWeek != c_classObject.m_calendarWeek))) {
    return false;
  }

  return true;
}

bool TimeInformationData::
operator!=(const TimeInformationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeInformationData::isEmpty() const {
  return !m_utcIsSet && !m_utcOffsetIsSet && !m_dayOfWeekIsSet &&
         !m_calendarWeekIsSet;
}

CmdData::Type TimeInformationData::getDataType() const {
  return CmdData::Type::TIME_INFORMATION_DATA_TYPE;
}

CmdDataPtr TimeInformationData::clone() const {
  return std::make_shared<TimeInformationData>(*this);
}

void TimeInformationData::setUtc(const xs_dateTime &utc) {
  m_utc = utc;
  m_utcIsSet = true;
}

const xs_dateTime &TimeInformationData::getUtc() const { return m_utc; }

void TimeInformationData::cleanUtc() {
  m_utc = xs_dateTime();
  m_utcIsSet = false;
}

bool TimeInformationData::getUtcIsSet() const { return m_utcIsSet; }

void TimeInformationData::setUtcOffset(const xs_duration &utcOffset) {
  m_utcOffset = utcOffset;
  m_utcOffsetIsSet = true;
}

const xs_duration &TimeInformationData::getUtcOffset() const {
  return m_utcOffset;
}

void TimeInformationData::cleanUtcOffset() {
  m_utcOffset = xs_duration();
  m_utcOffsetIsSet = false;
}

bool TimeInformationData::getUtcOffsetIsSet() const { return m_utcOffsetIsSet; }

void TimeInformationData::setDayOfWeek(const DayOfWeek &dayOfWeek) {
  m_dayOfWeek = dayOfWeek;
  m_dayOfWeekIsSet = true;
}

const DayOfWeek &TimeInformationData::getDayOfWeek() const {
  return m_dayOfWeek;
}

void TimeInformationData::cleanDayOfWeek() {
  m_dayOfWeek = DayOfWeek();
  m_dayOfWeekIsSet = false;
}

bool TimeInformationData::getDayOfWeekIsSet() const { return m_dayOfWeekIsSet; }

void TimeInformationData::setCalendarWeek(const xs_unsignedByte &calendarWeek) {
  m_calendarWeek = calendarWeek;
  m_calendarWeekIsSet = true;
}

const xs_unsignedByte &TimeInformationData::getCalendarWeek() const {
  return m_calendarWeek;
}

void TimeInformationData::cleanCalendarWeek() {
  m_calendarWeek = 0;
  m_calendarWeekIsSet = false;
}

bool TimeInformationData::getCalendarWeekIsSet() const {
  return m_calendarWeekIsSet;
}

CmdDataPtr
TimeInformationData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      TimeInformationDataElementsPtr elements =
          std::dynamic_pointer_cast<TimeInformationDataElements>(
              filter.getDataElements());
      if (elements) {
        TimeInformationDataPtr dataOut =
            std::make_shared<TimeInformationData>();
        // TODO make sure to always set identifier

        if (getUtcIsSet() && elements->getUtcIsSet()) {
          dataOut->setUtc(getUtc());
        }

        if (getUtcOffsetIsSet() && elements->getUtcOffsetIsSet()) {
          dataOut->setUtcOffset(getUtcOffset());
        }

        if (getDayOfWeekIsSet() && elements->getDayOfWeekIsSet()) {
          dataOut->setDayOfWeek(getDayOfWeek());
        }

        if (getCalendarWeekIsSet() && elements->getCalendarWeekIsSet()) {
          dataOut->setCalendarWeek(getCalendarWeek());
        }

        return dataOut;
      } else {
        return std::make_shared<TimeInformationData>(*this);
      }
    } else {
      return std::make_shared<TimeInformationData>(*this);
    }
  } else {
    return std::make_shared<TimeInformationData>(*this);
  }
}

bool TimeInformationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"utc", "utcOffset", "dayOfWeek", "calendarWeek"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)), "utc",
                                   &m_utc)) {
      m_utcIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "utcOffset", &m_utcOffset)) {
      m_utcOffsetIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "dayOfWeek", &m_dayOfWeek)) {
      m_dayOfWeekIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "calendarWeek", &m_calendarWeek)) {
      m_calendarWeekIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeInformationData::toJson() const {
  std::string result = "[";
  if (m_utcIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("utc", m_utc);
  }
  if (m_utcOffsetIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("utcOffset", m_utcOffset);
  }
  if (m_dayOfWeekIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("dayOfWeek", m_dayOfWeek);
  }
  if (m_calendarWeekIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("calendarWeek", m_calendarWeek);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram