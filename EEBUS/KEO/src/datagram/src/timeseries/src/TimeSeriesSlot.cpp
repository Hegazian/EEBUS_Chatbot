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

#include <keo_datagram/timeseries/TimeSeriesSlot.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesSlot::TimeSeriesSlot()
    : m_timeSeriesSlotIdIsSet(false), m_timeSeriesSlotId(0),
      m_timePeriodIsSet(false), m_timePeriod(TimePeriod()),
      m_durationIsSet(false), m_duration(xs_duration()),
      m_recurrenceInformationIsSet(false),
      m_recurrenceInformation(AbsoluteOrRecurringTime()), m_valueIsSet(false),
      m_value(ScaledNumber()), m_minValueIsSet(false),
      m_minValue(ScaledNumber()), m_maxValueIsSet(false),
      m_maxValue(ScaledNumber())

{}

bool TimeSeriesSlot::operator==(const TimeSeriesSlot &c_classObject) const {
  if (m_timeSeriesSlotIdIsSet != c_classObject.m_timeSeriesSlotIdIsSet ||
      (m_timeSeriesSlotIdIsSet &&
       (m_timeSeriesSlotId != c_classObject.m_timeSeriesSlotId))) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_durationIsSet != c_classObject.m_durationIsSet ||
      (m_durationIsSet && (m_duration != c_classObject.m_duration))) {
    return false;
  }
  if (m_recurrenceInformationIsSet !=
          c_classObject.m_recurrenceInformationIsSet ||
      (m_recurrenceInformationIsSet &&
       (m_recurrenceInformation != c_classObject.m_recurrenceInformation))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }
  if (m_minValueIsSet != c_classObject.m_minValueIsSet ||
      (m_minValueIsSet && (m_minValue != c_classObject.m_minValue))) {
    return false;
  }
  if (m_maxValueIsSet != c_classObject.m_maxValueIsSet ||
      (m_maxValueIsSet && (m_maxValue != c_classObject.m_maxValue))) {
    return false;
  }

  return true;
}

bool TimeSeriesSlot::operator!=(const TimeSeriesSlot &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesSlot::isEmpty() const {
  return !m_timeSeriesSlotIdIsSet && !m_timePeriodIsSet && !m_durationIsSet &&
         !m_recurrenceInformationIsSet && !m_valueIsSet && !m_minValueIsSet &&
         !m_maxValueIsSet;
}

void TimeSeriesSlot::setTimeSeriesSlotId(
    const xs_unsignedInt &timeSeriesSlotId) {
  m_timeSeriesSlotId = timeSeriesSlotId;
  m_timeSeriesSlotIdIsSet = true;
}

const xs_unsignedInt &TimeSeriesSlot::getTimeSeriesSlotId() const {
  return m_timeSeriesSlotId;
}

void TimeSeriesSlot::cleanTimeSeriesSlotId() {
  m_timeSeriesSlotId = 0;
  m_timeSeriesSlotIdIsSet = false;
}

bool TimeSeriesSlot::getTimeSeriesSlotIdIsSet() const {
  return m_timeSeriesSlotIdIsSet;
}

void TimeSeriesSlot::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &TimeSeriesSlot::getTimePeriod() const { return m_timePeriod; }

void TimeSeriesSlot::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool TimeSeriesSlot::getTimePeriodIsSet() const { return m_timePeriodIsSet; }

void TimeSeriesSlot::setDuration(const xs_duration &duration) {
  m_duration = duration;
  m_durationIsSet = true;
}

const xs_duration &TimeSeriesSlot::getDuration() const { return m_duration; }

void TimeSeriesSlot::cleanDuration() {
  m_duration = xs_duration();
  m_durationIsSet = false;
}

bool TimeSeriesSlot::getDurationIsSet() const { return m_durationIsSet; }

void TimeSeriesSlot::setRecurrenceInformation(
    const AbsoluteOrRecurringTime &recurrenceInformation) {
  m_recurrenceInformation = recurrenceInformation;
  m_recurrenceInformationIsSet = true;
}

const AbsoluteOrRecurringTime &
TimeSeriesSlot::getRecurrenceInformation() const {
  return m_recurrenceInformation;
}

void TimeSeriesSlot::cleanRecurrenceInformation() {
  m_recurrenceInformation = AbsoluteOrRecurringTime();
  m_recurrenceInformationIsSet = false;
}

bool TimeSeriesSlot::getRecurrenceInformationIsSet() const {
  return m_recurrenceInformationIsSet;
}

void TimeSeriesSlot::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &TimeSeriesSlot::getValue() const { return m_value; }

void TimeSeriesSlot::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool TimeSeriesSlot::getValueIsSet() const { return m_valueIsSet; }

void TimeSeriesSlot::setMinValue(const ScaledNumber &minValue) {
  m_minValue = minValue;
  m_minValueIsSet = true;
}

const ScaledNumber &TimeSeriesSlot::getMinValue() const { return m_minValue; }

void TimeSeriesSlot::cleanMinValue() {
  m_minValue = ScaledNumber();
  m_minValueIsSet = false;
}

bool TimeSeriesSlot::getMinValueIsSet() const { return m_minValueIsSet; }

void TimeSeriesSlot::setMaxValue(const ScaledNumber &maxValue) {
  m_maxValue = maxValue;
  m_maxValueIsSet = true;
}

const ScaledNumber &TimeSeriesSlot::getMaxValue() const { return m_maxValue; }

void TimeSeriesSlot::cleanMaxValue() {
  m_maxValue = ScaledNumber();
  m_maxValueIsSet = false;
}

bool TimeSeriesSlot::getMaxValueIsSet() const { return m_maxValueIsSet; }

bool TimeSeriesSlot::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesSlotId", "timePeriod", "duration",
                   "recurrenceInformation", "value", "minValue", "maxValue"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesSlotId", &m_timeSeriesSlotId)) {
      m_timeSeriesSlotIdIsSet = true;
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
                                   "duration", &m_duration)) {
      m_durationIsSet = true;
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
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "minValue", &m_minValue)) {
      m_minValueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxValue", &m_maxValue)) {
      m_maxValueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesSlot::toJson() const {
  std::string result = "[";
  if (m_timeSeriesSlotIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timeSeriesSlotId", m_timeSeriesSlotId);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_durationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("duration", m_duration);
  }
  if (m_recurrenceInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("recurrenceInformation",
                                           m_recurrenceInformation);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  if (m_minValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("minValue", m_minValue);
  }
  if (m_maxValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("maxValue", m_maxValue);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram