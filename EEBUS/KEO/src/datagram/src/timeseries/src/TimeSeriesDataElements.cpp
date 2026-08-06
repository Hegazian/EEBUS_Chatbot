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

#include <keo_datagram/timeseries/TimeSeriesDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesDataElements::TimeSeriesDataElements()
    : DataElements(), m_timeSeriesIdIsSet(false), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriodElements()), m_timeSeriesSlotIsSet(false),
      m_timeSeriesSlot(TimeSeriesSlotElements())

{}

TimeSeriesDataElements::TimeSeriesDataElements(
    xs_boolean c_timeSeriesIdIsSet, const TimePeriodElements &c_timePeriod,
    const TimeSeriesSlotElements &c_timeSeriesSlot)
    : DataElements(), m_timeSeriesIdIsSet(c_timeSeriesIdIsSet),
      m_timePeriodIsSet(true), m_timePeriod(c_timePeriod),
      m_timeSeriesSlotIsSet(true), m_timeSeriesSlot(c_timeSeriesSlot)

{}

bool TimeSeriesDataElements::
operator==(const TimeSeriesDataElements &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_timeSeriesSlotIsSet != c_classObject.m_timeSeriesSlotIsSet ||
      (m_timeSeriesSlotIsSet &&
       (m_timeSeriesSlot != c_classObject.m_timeSeriesSlot))) {
    return false;
  }

  return true;
}

bool TimeSeriesDataElements::
operator!=(const TimeSeriesDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesDataElements::isEmpty() const {
  return !m_timeSeriesIdIsSet && !m_timePeriodIsSet && !m_timeSeriesSlotIsSet;
}

DataElements::Type TimeSeriesDataElements::getDataType() const {
  return DataElements::Type::TIME_SERIES_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimeSeriesDataElements::clone() const {
  return std::make_shared<TimeSeriesDataElements>(*this);
}

void TimeSeriesDataElements::setTimeSeriesId() { m_timeSeriesIdIsSet = true; }

void TimeSeriesDataElements::cleanTimeSeriesId() {
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesDataElements::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

void TimeSeriesDataElements::setTimePeriod(
    const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &TimeSeriesDataElements::getTimePeriod() const {
  return m_timePeriod;
}

void TimeSeriesDataElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool TimeSeriesDataElements::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void TimeSeriesDataElements::setTimeSeriesSlot(
    const TimeSeriesSlotElements &timeSeriesSlot) {
  m_timeSeriesSlot = timeSeriesSlot;
  m_timeSeriesSlotIsSet = true;
}

const TimeSeriesSlotElements &
TimeSeriesDataElements::getTimeSeriesSlot() const {
  return m_timeSeriesSlot;
}

void TimeSeriesDataElements::cleanTimeSeriesSlot() {
  m_timeSeriesSlot = TimeSeriesSlotElements();
  m_timeSeriesSlotIsSet = false;
}

bool TimeSeriesDataElements::getTimeSeriesSlotIsSet() const {
  return m_timeSeriesSlotIsSet;
}

bool TimeSeriesDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesId", "timePeriod", "timeSeriesSlot"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSeriesId")) {
      m_timeSeriesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timePeriod", &m_timePeriod)) {
      m_timePeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesSlot", &m_timeSeriesSlot)) {
      m_timeSeriesSlotIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesDataElements::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSeriesId");
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_timeSeriesSlotIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesSlot", m_timeSeriesSlot);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram