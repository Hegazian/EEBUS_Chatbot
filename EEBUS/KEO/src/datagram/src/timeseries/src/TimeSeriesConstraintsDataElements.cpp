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

#include <keo_datagram/timeseries/TimeSeriesConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesConstraintsDataElements::TimeSeriesConstraintsDataElements()
    : DataElements(), m_timeSeriesIdIsSet(false), m_slotCountMinIsSet(false),
      m_slotCountMaxIsSet(false), m_slotDurationMinIsSet(false),
      m_slotDurationMaxIsSet(false), m_slotDurationStepSizeIsSet(false),
      m_earliestTimeSeriesStartTimeIsSet(false),
      m_latestTimeSeriesEndTimeIsSet(false), m_slotValueMinIsSet(false),
      m_slotValueMin(ScaledNumberElements()), m_slotValueMaxIsSet(false),
      m_slotValueMax(ScaledNumberElements()), m_slotValueStepSizeIsSet(false),
      m_slotValueStepSize(ScaledNumberElements())

{}

bool TimeSeriesConstraintsDataElements::
operator==(const TimeSeriesConstraintsDataElements &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet) {
    return false;
  }
  if (m_slotCountMinIsSet != c_classObject.m_slotCountMinIsSet) {
    return false;
  }
  if (m_slotCountMaxIsSet != c_classObject.m_slotCountMaxIsSet) {
    return false;
  }
  if (m_slotDurationMinIsSet != c_classObject.m_slotDurationMinIsSet) {
    return false;
  }
  if (m_slotDurationMaxIsSet != c_classObject.m_slotDurationMaxIsSet) {
    return false;
  }
  if (m_slotDurationStepSizeIsSet !=
      c_classObject.m_slotDurationStepSizeIsSet) {
    return false;
  }
  if (m_earliestTimeSeriesStartTimeIsSet !=
      c_classObject.m_earliestTimeSeriesStartTimeIsSet) {
    return false;
  }
  if (m_latestTimeSeriesEndTimeIsSet !=
      c_classObject.m_latestTimeSeriesEndTimeIsSet) {
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

bool TimeSeriesConstraintsDataElements::
operator!=(const TimeSeriesConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesConstraintsDataElements::isEmpty() const {
  return !m_timeSeriesIdIsSet && !m_slotCountMinIsSet && !m_slotCountMaxIsSet &&
         !m_slotDurationMinIsSet && !m_slotDurationMaxIsSet &&
         !m_slotDurationStepSizeIsSet && !m_earliestTimeSeriesStartTimeIsSet &&
         !m_latestTimeSeriesEndTimeIsSet && !m_slotValueMinIsSet &&
         !m_slotValueMaxIsSet && !m_slotValueStepSizeIsSet;
}

DataElements::Type TimeSeriesConstraintsDataElements::getDataType() const {
  return DataElements::Type::TIME_SERIES_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimeSeriesConstraintsDataElements::clone() const {
  return std::make_shared<TimeSeriesConstraintsDataElements>(*this);
}

void TimeSeriesConstraintsDataElements::setTimeSeriesId() {
  m_timeSeriesIdIsSet = true;
}

void TimeSeriesConstraintsDataElements::cleanTimeSeriesId() {
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

void TimeSeriesConstraintsDataElements::setSlotCountMin() {
  m_slotCountMinIsSet = true;
}

void TimeSeriesConstraintsDataElements::cleanSlotCountMin() {
  m_slotCountMinIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getSlotCountMinIsSet() const {
  return m_slotCountMinIsSet;
}

void TimeSeriesConstraintsDataElements::setSlotCountMax() {
  m_slotCountMaxIsSet = true;
}

void TimeSeriesConstraintsDataElements::cleanSlotCountMax() {
  m_slotCountMaxIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getSlotCountMaxIsSet() const {
  return m_slotCountMaxIsSet;
}

void TimeSeriesConstraintsDataElements::setSlotDurationMin() {
  m_slotDurationMinIsSet = true;
}

void TimeSeriesConstraintsDataElements::cleanSlotDurationMin() {
  m_slotDurationMinIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getSlotDurationMinIsSet() const {
  return m_slotDurationMinIsSet;
}

void TimeSeriesConstraintsDataElements::setSlotDurationMax() {
  m_slotDurationMaxIsSet = true;
}

void TimeSeriesConstraintsDataElements::cleanSlotDurationMax() {
  m_slotDurationMaxIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getSlotDurationMaxIsSet() const {
  return m_slotDurationMaxIsSet;
}

void TimeSeriesConstraintsDataElements::setSlotDurationStepSize() {
  m_slotDurationStepSizeIsSet = true;
}

void TimeSeriesConstraintsDataElements::cleanSlotDurationStepSize() {
  m_slotDurationStepSizeIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getSlotDurationStepSizeIsSet() const {
  return m_slotDurationStepSizeIsSet;
}

void TimeSeriesConstraintsDataElements::setEarliestTimeSeriesStartTime() {
  m_earliestTimeSeriesStartTimeIsSet = true;
}

void TimeSeriesConstraintsDataElements::cleanEarliestTimeSeriesStartTime() {
  m_earliestTimeSeriesStartTimeIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getEarliestTimeSeriesStartTimeIsSet()
    const {
  return m_earliestTimeSeriesStartTimeIsSet;
}

void TimeSeriesConstraintsDataElements::setLatestTimeSeriesEndTime() {
  m_latestTimeSeriesEndTimeIsSet = true;
}

void TimeSeriesConstraintsDataElements::cleanLatestTimeSeriesEndTime() {
  m_latestTimeSeriesEndTimeIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getLatestTimeSeriesEndTimeIsSet()
    const {
  return m_latestTimeSeriesEndTimeIsSet;
}

void TimeSeriesConstraintsDataElements::setSlotValueMin(
    const ScaledNumberElements &slotValueMin) {
  m_slotValueMin = slotValueMin;
  m_slotValueMinIsSet = true;
}

const ScaledNumberElements &
TimeSeriesConstraintsDataElements::getSlotValueMin() const {
  return m_slotValueMin;
}

void TimeSeriesConstraintsDataElements::cleanSlotValueMin() {
  m_slotValueMin = ScaledNumberElements();
  m_slotValueMinIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getSlotValueMinIsSet() const {
  return m_slotValueMinIsSet;
}

void TimeSeriesConstraintsDataElements::setSlotValueMax(
    const ScaledNumberElements &slotValueMax) {
  m_slotValueMax = slotValueMax;
  m_slotValueMaxIsSet = true;
}

const ScaledNumberElements &
TimeSeriesConstraintsDataElements::getSlotValueMax() const {
  return m_slotValueMax;
}

void TimeSeriesConstraintsDataElements::cleanSlotValueMax() {
  m_slotValueMax = ScaledNumberElements();
  m_slotValueMaxIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getSlotValueMaxIsSet() const {
  return m_slotValueMaxIsSet;
}

void TimeSeriesConstraintsDataElements::setSlotValueStepSize(
    const ScaledNumberElements &slotValueStepSize) {
  m_slotValueStepSize = slotValueStepSize;
  m_slotValueStepSizeIsSet = true;
}

const ScaledNumberElements &
TimeSeriesConstraintsDataElements::getSlotValueStepSize() const {
  return m_slotValueStepSize;
}

void TimeSeriesConstraintsDataElements::cleanSlotValueStepSize() {
  m_slotValueStepSize = ScaledNumberElements();
  m_slotValueStepSizeIsSet = false;
}

bool TimeSeriesConstraintsDataElements::getSlotValueStepSizeIsSet() const {
  return m_slotValueStepSizeIsSet;
}

bool TimeSeriesConstraintsDataElements::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSeriesId")) {
      m_timeSeriesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "slotCountMin")) {
      m_slotCountMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "slotCountMax")) {
      m_slotCountMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "slotDurationMin")) {
      m_slotDurationMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "slotDurationMax")) {
      m_slotDurationMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "slotDurationStepSize")) {
      m_slotDurationStepSizeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "earliestTimeSeriesStartTime")) {
      m_earliestTimeSeriesStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "latestTimeSeriesEndTime")) {
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

std::string TimeSeriesConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSeriesId");
  }
  if (m_slotCountMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotCountMin");
  }
  if (m_slotCountMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotCountMax");
  }
  if (m_slotDurationMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotDurationMin");
  }
  if (m_slotDurationMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotDurationMax");
  }
  if (m_slotDurationStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotDurationStepSize");
  }
  if (m_earliestTimeSeriesStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("earliestTimeSeriesStartTime");
  }
  if (m_latestTimeSeriesEndTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("latestTimeSeriesEndTime");
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