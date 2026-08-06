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

#include <keo_datagram/timeseries/TimeSeriesSlotElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesSlotElements::TimeSeriesSlotElements()
    : m_timeSeriesSlotIdIsSet(false), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriodElements()), m_durationIsSet(false),
      m_recurrenceInformationIsSet(false),
      m_recurrenceInformation(AbsoluteOrRecurringTimeElements()),
      m_valueIsSet(false), m_minValueIsSet(false), m_maxValueIsSet(false)

{}

bool TimeSeriesSlotElements::
operator==(const TimeSeriesSlotElements &c_classObject) const {
  if (m_timeSeriesSlotIdIsSet != c_classObject.m_timeSeriesSlotIdIsSet) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_durationIsSet != c_classObject.m_durationIsSet) {
    return false;
  }
  if (m_recurrenceInformationIsSet !=
          c_classObject.m_recurrenceInformationIsSet ||
      (m_recurrenceInformationIsSet &&
       (m_recurrenceInformation != c_classObject.m_recurrenceInformation))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet) {
    return false;
  }
  if (m_minValueIsSet != c_classObject.m_minValueIsSet) {
    return false;
  }
  if (m_maxValueIsSet != c_classObject.m_maxValueIsSet) {
    return false;
  }

  return true;
}

bool TimeSeriesSlotElements::
operator!=(const TimeSeriesSlotElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesSlotElements::isEmpty() const {
  return !m_timeSeriesSlotIdIsSet && !m_timePeriodIsSet && !m_durationIsSet &&
         !m_recurrenceInformationIsSet && !m_valueIsSet && !m_minValueIsSet &&
         !m_maxValueIsSet;
}

void TimeSeriesSlotElements::setTimeSeriesSlotId() {
  m_timeSeriesSlotIdIsSet = true;
}

void TimeSeriesSlotElements::cleanTimeSeriesSlotId() {
  m_timeSeriesSlotIdIsSet = false;
}

bool TimeSeriesSlotElements::getTimeSeriesSlotIdIsSet() const {
  return m_timeSeriesSlotIdIsSet;
}

void TimeSeriesSlotElements::setTimePeriod(
    const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &TimeSeriesSlotElements::getTimePeriod() const {
  return m_timePeriod;
}

void TimeSeriesSlotElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool TimeSeriesSlotElements::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void TimeSeriesSlotElements::setDuration() { m_durationIsSet = true; }

void TimeSeriesSlotElements::cleanDuration() { m_durationIsSet = false; }

bool TimeSeriesSlotElements::getDurationIsSet() const {
  return m_durationIsSet;
}

void TimeSeriesSlotElements::setRecurrenceInformation(
    const AbsoluteOrRecurringTimeElements &recurrenceInformation) {
  m_recurrenceInformation = recurrenceInformation;
  m_recurrenceInformationIsSet = true;
}

const AbsoluteOrRecurringTimeElements &
TimeSeriesSlotElements::getRecurrenceInformation() const {
  return m_recurrenceInformation;
}

void TimeSeriesSlotElements::cleanRecurrenceInformation() {
  m_recurrenceInformation = AbsoluteOrRecurringTimeElements();
  m_recurrenceInformationIsSet = false;
}

bool TimeSeriesSlotElements::getRecurrenceInformationIsSet() const {
  return m_recurrenceInformationIsSet;
}

void TimeSeriesSlotElements::setValue() { m_valueIsSet = true; }

void TimeSeriesSlotElements::cleanValue() { m_valueIsSet = false; }

bool TimeSeriesSlotElements::getValueIsSet() const { return m_valueIsSet; }

void TimeSeriesSlotElements::setMinValue() { m_minValueIsSet = true; }

void TimeSeriesSlotElements::cleanMinValue() { m_minValueIsSet = false; }

bool TimeSeriesSlotElements::getMinValueIsSet() const {
  return m_minValueIsSet;
}

void TimeSeriesSlotElements::setMaxValue() { m_maxValueIsSet = true; }

void TimeSeriesSlotElements::cleanMaxValue() { m_maxValueIsSet = false; }

bool TimeSeriesSlotElements::getMaxValueIsSet() const {
  return m_maxValueIsSet;
}

bool TimeSeriesSlotElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesSlotId", "timePeriod", "duration",
                   "recurrenceInformation", "value", "minValue", "maxValue"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSeriesSlotId")) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "duration")) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "value")) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "minValue")) {
      m_minValueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxValue")) {
      m_maxValueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesSlotElements::toJson() const {
  std::string result = "[";
  if (m_timeSeriesSlotIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSeriesSlotId");
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_durationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("duration");
  }
  if (m_recurrenceInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("recurrenceInformation",
                                           m_recurrenceInformation);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("value");
  }
  if (m_minValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("minValue");
  }
  if (m_maxValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxValue");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram