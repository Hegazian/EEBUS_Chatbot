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

#include <keo_datagram/timeseries/TimeSeriesConstraintsData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesConstraintsData::TimeSeriesConstraintsData()
    : m_timeSeriesIdIsSet(false), m_timeSeriesId(0), m_slotCountMinIsSet(false),
      m_slotCountMin(0), m_slotCountMaxIsSet(false), m_slotCountMax(0),
      m_slotDurationMinIsSet(false), m_slotDurationMin(xs_duration()),
      m_slotDurationMaxIsSet(false), m_slotDurationMax(xs_duration()),
      m_slotDurationStepSizeIsSet(false), m_slotDurationStepSize(xs_duration()),
      m_earliestTimeSeriesStartTimeIsSet(false),
      m_earliestTimeSeriesStartTime(AbsoluteOrRelativeTime()),
      m_latestTimeSeriesEndTimeIsSet(false),
      m_latestTimeSeriesEndTime(AbsoluteOrRelativeTime()),
      m_slotValueMinIsSet(false), m_slotValueMin(ScaledNumber()),
      m_slotValueMaxIsSet(false), m_slotValueMax(ScaledNumber()),
      m_slotValueStepSizeIsSet(false), m_slotValueStepSize(ScaledNumber())

{}

bool TimeSeriesConstraintsData::
operator==(const TimeSeriesConstraintsData &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet ||
      (m_timeSeriesIdIsSet &&
       (m_timeSeriesId != c_classObject.m_timeSeriesId))) {
    return false;
  }
  if (m_slotCountMinIsSet != c_classObject.m_slotCountMinIsSet ||
      (m_slotCountMinIsSet &&
       (m_slotCountMin != c_classObject.m_slotCountMin))) {
    return false;
  }
  if (m_slotCountMaxIsSet != c_classObject.m_slotCountMaxIsSet ||
      (m_slotCountMaxIsSet &&
       (m_slotCountMax != c_classObject.m_slotCountMax))) {
    return false;
  }
  if (m_slotDurationMinIsSet != c_classObject.m_slotDurationMinIsSet ||
      (m_slotDurationMinIsSet &&
       (m_slotDurationMin != c_classObject.m_slotDurationMin))) {
    return false;
  }
  if (m_slotDurationMaxIsSet != c_classObject.m_slotDurationMaxIsSet ||
      (m_slotDurationMaxIsSet &&
       (m_slotDurationMax != c_classObject.m_slotDurationMax))) {
    return false;
  }
  if (m_slotDurationStepSizeIsSet !=
          c_classObject.m_slotDurationStepSizeIsSet ||
      (m_slotDurationStepSizeIsSet &&
       (m_slotDurationStepSize != c_classObject.m_slotDurationStepSize))) {
    return false;
  }
  if (m_earliestTimeSeriesStartTimeIsSet !=
          c_classObject.m_earliestTimeSeriesStartTimeIsSet ||
      (m_earliestTimeSeriesStartTimeIsSet &&
       (m_earliestTimeSeriesStartTime !=
        c_classObject.m_earliestTimeSeriesStartTime))) {
    return false;
  }
  if (m_latestTimeSeriesEndTimeIsSet !=
          c_classObject.m_latestTimeSeriesEndTimeIsSet ||
      (m_latestTimeSeriesEndTimeIsSet &&
       (m_latestTimeSeriesEndTime !=
        c_classObject.m_latestTimeSeriesEndTime))) {
    return false;
  }
  if (m_slotValueMinIsSet != c_classObject.m_slotValueMinIsSet ||
      (m_slotValueMinIsSet &&
       (m_slotValueMin != c_classObject.m_slotValueMin))) {
    return false;
  }
  if (m_slotValueMaxIsSet != c_classObject.m_slotValueMaxIsSet ||
      (m_slotValueMaxIsSet &&
       (m_slotValueMax != c_classObject.m_slotValueMax))) {
    return false;
  }
  if (m_slotValueStepSizeIsSet != c_classObject.m_slotValueStepSizeIsSet ||
      (m_slotValueStepSizeIsSet &&
       (m_slotValueStepSize != c_classObject.m_slotValueStepSize))) {
    return false;
  }

  return true;
}

bool TimeSeriesConstraintsData::
operator!=(const TimeSeriesConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesConstraintsData::isEmpty() const {
  return !m_timeSeriesIdIsSet && !m_slotCountMinIsSet && !m_slotCountMaxIsSet &&
         !m_slotDurationMinIsSet && !m_slotDurationMaxIsSet &&
         !m_slotDurationStepSizeIsSet && !m_earliestTimeSeriesStartTimeIsSet &&
         !m_latestTimeSeriesEndTimeIsSet && !m_slotValueMinIsSet &&
         !m_slotValueMaxIsSet && !m_slotValueStepSizeIsSet;
}

void TimeSeriesConstraintsData::setTimeSeriesId(
    const xs_unsignedInt &timeSeriesId) {
  m_timeSeriesId = timeSeriesId;
  m_timeSeriesIdIsSet = true;
}

const xs_unsignedInt &TimeSeriesConstraintsData::getTimeSeriesId() const {
  return m_timeSeriesId;
}

void TimeSeriesConstraintsData::cleanTimeSeriesId() {
  m_timeSeriesId = 0;
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesConstraintsData::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

void TimeSeriesConstraintsData::setSlotCountMin(
    const xs_unsignedInt &slotCountMin) {
  m_slotCountMin = slotCountMin;
  m_slotCountMinIsSet = true;
}

const xs_unsignedInt &TimeSeriesConstraintsData::getSlotCountMin() const {
  return m_slotCountMin;
}

void TimeSeriesConstraintsData::cleanSlotCountMin() {
  m_slotCountMin = 0;
  m_slotCountMinIsSet = false;
}

bool TimeSeriesConstraintsData::getSlotCountMinIsSet() const {
  return m_slotCountMinIsSet;
}

void TimeSeriesConstraintsData::setSlotCountMax(
    const xs_unsignedInt &slotCountMax) {
  m_slotCountMax = slotCountMax;
  m_slotCountMaxIsSet = true;
}

const xs_unsignedInt &TimeSeriesConstraintsData::getSlotCountMax() const {
  return m_slotCountMax;
}

void TimeSeriesConstraintsData::cleanSlotCountMax() {
  m_slotCountMax = 0;
  m_slotCountMaxIsSet = false;
}

bool TimeSeriesConstraintsData::getSlotCountMaxIsSet() const {
  return m_slotCountMaxIsSet;
}

void TimeSeriesConstraintsData::setSlotDurationMin(
    const xs_duration &slotDurationMin) {
  m_slotDurationMin = slotDurationMin;
  m_slotDurationMinIsSet = true;
}

const xs_duration &TimeSeriesConstraintsData::getSlotDurationMin() const {
  return m_slotDurationMin;
}

void TimeSeriesConstraintsData::cleanSlotDurationMin() {
  m_slotDurationMin = xs_duration();
  m_slotDurationMinIsSet = false;
}

bool TimeSeriesConstraintsData::getSlotDurationMinIsSet() const {
  return m_slotDurationMinIsSet;
}

void TimeSeriesConstraintsData::setSlotDurationMax(
    const xs_duration &slotDurationMax) {
  m_slotDurationMax = slotDurationMax;
  m_slotDurationMaxIsSet = true;
}

const xs_duration &TimeSeriesConstraintsData::getSlotDurationMax() const {
  return m_slotDurationMax;
}

void TimeSeriesConstraintsData::cleanSlotDurationMax() {
  m_slotDurationMax = xs_duration();
  m_slotDurationMaxIsSet = false;
}

bool TimeSeriesConstraintsData::getSlotDurationMaxIsSet() const {
  return m_slotDurationMaxIsSet;
}

void TimeSeriesConstraintsData::setSlotDurationStepSize(
    const xs_duration &slotDurationStepSize) {
  m_slotDurationStepSize = slotDurationStepSize;
  m_slotDurationStepSizeIsSet = true;
}

const xs_duration &TimeSeriesConstraintsData::getSlotDurationStepSize() const {
  return m_slotDurationStepSize;
}

void TimeSeriesConstraintsData::cleanSlotDurationStepSize() {
  m_slotDurationStepSize = xs_duration();
  m_slotDurationStepSizeIsSet = false;
}

bool TimeSeriesConstraintsData::getSlotDurationStepSizeIsSet() const {
  return m_slotDurationStepSizeIsSet;
}

void TimeSeriesConstraintsData::setEarliestTimeSeriesStartTime(
    const AbsoluteOrRelativeTime &earliestTimeSeriesStartTime) {
  m_earliestTimeSeriesStartTime = earliestTimeSeriesStartTime;
  m_earliestTimeSeriesStartTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
TimeSeriesConstraintsData::getEarliestTimeSeriesStartTime() const {
  return m_earliestTimeSeriesStartTime;
}

void TimeSeriesConstraintsData::cleanEarliestTimeSeriesStartTime() {
  m_earliestTimeSeriesStartTime = AbsoluteOrRelativeTime();
  m_earliestTimeSeriesStartTimeIsSet = false;
}

bool TimeSeriesConstraintsData::getEarliestTimeSeriesStartTimeIsSet() const {
  return m_earliestTimeSeriesStartTimeIsSet;
}

void TimeSeriesConstraintsData::setLatestTimeSeriesEndTime(
    const AbsoluteOrRelativeTime &latestTimeSeriesEndTime) {
  m_latestTimeSeriesEndTime = latestTimeSeriesEndTime;
  m_latestTimeSeriesEndTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
TimeSeriesConstraintsData::getLatestTimeSeriesEndTime() const {
  return m_latestTimeSeriesEndTime;
}

void TimeSeriesConstraintsData::cleanLatestTimeSeriesEndTime() {
  m_latestTimeSeriesEndTime = AbsoluteOrRelativeTime();
  m_latestTimeSeriesEndTimeIsSet = false;
}

bool TimeSeriesConstraintsData::getLatestTimeSeriesEndTimeIsSet() const {
  return m_latestTimeSeriesEndTimeIsSet;
}

void TimeSeriesConstraintsData::setSlotValueMin(
    const ScaledNumber &slotValueMin) {
  m_slotValueMin = slotValueMin;
  m_slotValueMinIsSet = true;
}

const ScaledNumber &TimeSeriesConstraintsData::getSlotValueMin() const {
  return m_slotValueMin;
}

void TimeSeriesConstraintsData::cleanSlotValueMin() {
  m_slotValueMin = ScaledNumber();
  m_slotValueMinIsSet = false;
}

bool TimeSeriesConstraintsData::getSlotValueMinIsSet() const {
  return m_slotValueMinIsSet;
}

void TimeSeriesConstraintsData::setSlotValueMax(
    const ScaledNumber &slotValueMax) {
  m_slotValueMax = slotValueMax;
  m_slotValueMaxIsSet = true;
}

const ScaledNumber &TimeSeriesConstraintsData::getSlotValueMax() const {
  return m_slotValueMax;
}

void TimeSeriesConstraintsData::cleanSlotValueMax() {
  m_slotValueMax = ScaledNumber();
  m_slotValueMaxIsSet = false;
}

bool TimeSeriesConstraintsData::getSlotValueMaxIsSet() const {
  return m_slotValueMaxIsSet;
}

void TimeSeriesConstraintsData::setSlotValueStepSize(
    const ScaledNumber &slotValueStepSize) {
  m_slotValueStepSize = slotValueStepSize;
  m_slotValueStepSizeIsSet = true;
}

const ScaledNumber &TimeSeriesConstraintsData::getSlotValueStepSize() const {
  return m_slotValueStepSize;
}

void TimeSeriesConstraintsData::cleanSlotValueStepSize() {
  m_slotValueStepSize = ScaledNumber();
  m_slotValueStepSizeIsSet = false;
}

bool TimeSeriesConstraintsData::getSlotValueStepSizeIsSet() const {
  return m_slotValueStepSizeIsSet;
}

bool TimeSeriesConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesId", "slotCountMin", "slotCountMax",
                   "slotDurationMin", "slotDurationMax", "slotDurationStepSize",
                   "earliestTimeSeriesStartTime", "latestTimeSeriesEndTime",
                   "slotValueMin", "slotValueMax", "slotValueStepSize"})) {
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
                                   "slotCountMin", &m_slotCountMin)) {
      m_slotCountMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotCountMax", &m_slotCountMax)) {
      m_slotCountMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotDurationMin", &m_slotDurationMin)) {
      m_slotDurationMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotDurationMax", &m_slotDurationMax)) {
      m_slotDurationMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotDurationStepSize",
                                   &m_slotDurationStepSize)) {
      m_slotDurationStepSizeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "earliestTimeSeriesStartTime",
                                   &m_earliestTimeSeriesStartTime)) {
      m_earliestTimeSeriesStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "latestTimeSeriesEndTime",
                                   &m_latestTimeSeriesEndTime)) {
      m_latestTimeSeriesEndTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotValueMin", &m_slotValueMin)) {
      m_slotValueMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotValueMax", &m_slotValueMax)) {
      m_slotValueMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotValueStepSize", &m_slotValueStepSize)) {
      m_slotValueStepSizeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesConstraintsData::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesId", m_timeSeriesId);
  }
  if (m_slotCountMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotCountMin", m_slotCountMin);
  }
  if (m_slotCountMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotCountMax", m_slotCountMax);
  }
  if (m_slotDurationMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("slotDurationMin", m_slotDurationMin);
  }
  if (m_slotDurationMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("slotDurationMax", m_slotDurationMax);
  }
  if (m_slotDurationStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotDurationStepSize",
                                           m_slotDurationStepSize);
  }
  if (m_earliestTimeSeriesStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("earliestTimeSeriesStartTime",
                                           m_earliestTimeSeriesStartTime);
  }
  if (m_latestTimeSeriesEndTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("latestTimeSeriesEndTime",
                                           m_latestTimeSeriesEndTime);
  }
  if (m_slotValueMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotValueMin", m_slotValueMin);
  }
  if (m_slotValueMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotValueMax", m_slotValueMax);
  }
  if (m_slotValueStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("slotValueStepSize", m_slotValueStepSize);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram