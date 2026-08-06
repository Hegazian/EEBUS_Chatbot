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

#include <keo_datagram/timeseries/TimeSeriesData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesData::TimeSeriesData()
    : m_timeSeriesIdIsSet(false), m_timeSeriesId(0), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriod()), m_timeSeriesSlotIsSet(false),
      m_timeSeriesSlot(std::vector<TimeSeriesSlot>())

{}

TimeSeriesData::TimeSeriesData(
    const xs_unsignedInt &c_timeSeriesId, const TimePeriod &c_timePeriod,
    const std::vector<TimeSeriesSlot> &c_timeSeriesSlot)
    : m_timeSeriesIdIsSet(true), m_timeSeriesId(c_timeSeriesId),
      m_timePeriodIsSet(true), m_timePeriod(c_timePeriod),
      m_timeSeriesSlotIsSet(true), m_timeSeriesSlot(c_timeSeriesSlot)

{}

bool TimeSeriesData::operator==(const TimeSeriesData &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet ||
      (m_timeSeriesIdIsSet &&
       (m_timeSeriesId != c_classObject.m_timeSeriesId))) {
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

bool TimeSeriesData::operator!=(const TimeSeriesData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesData::isEmpty() const {
  return !m_timeSeriesIdIsSet && !m_timePeriodIsSet && !m_timeSeriesSlotIsSet;
}

void TimeSeriesData::setTimeSeriesId(const xs_unsignedInt &timeSeriesId) {
  m_timeSeriesId = timeSeriesId;
  m_timeSeriesIdIsSet = true;
}

const xs_unsignedInt &TimeSeriesData::getTimeSeriesId() const {
  return m_timeSeriesId;
}

void TimeSeriesData::cleanTimeSeriesId() {
  m_timeSeriesId = 0;
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesData::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

void TimeSeriesData::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &TimeSeriesData::getTimePeriod() const { return m_timePeriod; }

void TimeSeriesData::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool TimeSeriesData::getTimePeriodIsSet() const { return m_timePeriodIsSet; }

void TimeSeriesData::setTimeSeriesSlot(
    const std::vector<TimeSeriesSlot> &timeSeriesSlot) {
  m_timeSeriesSlot = timeSeriesSlot;
  m_timeSeriesSlotIsSet = true;
}

const std::vector<TimeSeriesSlot> &TimeSeriesData::getTimeSeriesSlot() const {
  return m_timeSeriesSlot;
}

void TimeSeriesData::cleanTimeSeriesSlot() {
  m_timeSeriesSlot.clear();
  m_timeSeriesSlotIsSet = false;
}

bool TimeSeriesData::getTimeSeriesSlotIsSet() const {
  return m_timeSeriesSlotIsSet;
}

bool TimeSeriesData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesId", "timePeriod", "timeSeriesSlot"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesId", &m_timeSeriesId)) {
      m_timeSeriesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timePeriod", &m_timePeriod)) {
      m_timePeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() && KeoJsonTransformation::getList<TimeSeriesSlot>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesSlot", &m_timeSeriesSlot)) {
      m_timeSeriesSlotIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesData::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesId", m_timeSeriesId);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_timeSeriesSlotIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TimeSeriesSlot>(
        "timeSeriesSlot", m_timeSeriesSlot);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram