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

#include <keo_datagram/timetable/TimeTableConstraintsData.h>

#include <keo_datagram/timetable/TimeTableConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableConstraintsData::TimeTableConstraintsData()
    : m_timeTableIdIsSet(false), m_timeTableId(0), m_slotCountMinIsSet(false),
      m_slotCountMin(0), m_slotCountMaxIsSet(false), m_slotCountMax(0),
      m_slotDurationMinIsSet(false), m_slotDurationMin(xs_duration()),
      m_slotDurationMaxIsSet(false), m_slotDurationMax(xs_duration()),
      m_slotDurationStepSizeIsSet(false), m_slotDurationStepSize(xs_duration()),
      m_slotShiftStepSizeIsSet(false), m_slotShiftStepSize(xs_duration()),
      m_firstSlotBeginsAtIsSet(false), m_firstSlotBeginsAt(xs_time())

{}

bool TimeTableConstraintsData::
operator==(const TimeTableConstraintsData &c_classObject) const {
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
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
  if (m_slotShiftStepSizeIsSet != c_classObject.m_slotShiftStepSizeIsSet ||
      (m_slotShiftStepSizeIsSet &&
       (m_slotShiftStepSize != c_classObject.m_slotShiftStepSize))) {
    return false;
  }
  if (m_firstSlotBeginsAtIsSet != c_classObject.m_firstSlotBeginsAtIsSet ||
      (m_firstSlotBeginsAtIsSet &&
       (m_firstSlotBeginsAt != c_classObject.m_firstSlotBeginsAt))) {
    return false;
  }

  return true;
}

bool TimeTableConstraintsData::
operator!=(const TimeTableConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableConstraintsData::isEmpty() const {
  return !m_timeTableIdIsSet && !m_slotCountMinIsSet && !m_slotCountMaxIsSet &&
         !m_slotDurationMinIsSet && !m_slotDurationMaxIsSet &&
         !m_slotDurationStepSizeIsSet && !m_slotShiftStepSizeIsSet &&
         !m_firstSlotBeginsAtIsSet;
}

void TimeTableConstraintsData::setTimeTableId(
    const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &TimeTableConstraintsData::getTimeTableId() const {
  return m_timeTableId;
}

void TimeTableConstraintsData::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool TimeTableConstraintsData::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TimeTableConstraintsData::setSlotCountMin(
    const xs_unsignedInt &slotCountMin) {
  m_slotCountMin = slotCountMin;
  m_slotCountMinIsSet = true;
}

const xs_unsignedInt &TimeTableConstraintsData::getSlotCountMin() const {
  return m_slotCountMin;
}

void TimeTableConstraintsData::cleanSlotCountMin() {
  m_slotCountMin = 0;
  m_slotCountMinIsSet = false;
}

bool TimeTableConstraintsData::getSlotCountMinIsSet() const {
  return m_slotCountMinIsSet;
}

void TimeTableConstraintsData::setSlotCountMax(
    const xs_unsignedInt &slotCountMax) {
  m_slotCountMax = slotCountMax;
  m_slotCountMaxIsSet = true;
}

const xs_unsignedInt &TimeTableConstraintsData::getSlotCountMax() const {
  return m_slotCountMax;
}

void TimeTableConstraintsData::cleanSlotCountMax() {
  m_slotCountMax = 0;
  m_slotCountMaxIsSet = false;
}

bool TimeTableConstraintsData::getSlotCountMaxIsSet() const {
  return m_slotCountMaxIsSet;
}

void TimeTableConstraintsData::setSlotDurationMin(
    const xs_duration &slotDurationMin) {
  m_slotDurationMin = slotDurationMin;
  m_slotDurationMinIsSet = true;
}

const xs_duration &TimeTableConstraintsData::getSlotDurationMin() const {
  return m_slotDurationMin;
}

void TimeTableConstraintsData::cleanSlotDurationMin() {
  m_slotDurationMin = xs_duration();
  m_slotDurationMinIsSet = false;
}

bool TimeTableConstraintsData::getSlotDurationMinIsSet() const {
  return m_slotDurationMinIsSet;
}

void TimeTableConstraintsData::setSlotDurationMax(
    const xs_duration &slotDurationMax) {
  m_slotDurationMax = slotDurationMax;
  m_slotDurationMaxIsSet = true;
}

const xs_duration &TimeTableConstraintsData::getSlotDurationMax() const {
  return m_slotDurationMax;
}

void TimeTableConstraintsData::cleanSlotDurationMax() {
  m_slotDurationMax = xs_duration();
  m_slotDurationMaxIsSet = false;
}

bool TimeTableConstraintsData::getSlotDurationMaxIsSet() const {
  return m_slotDurationMaxIsSet;
}

void TimeTableConstraintsData::setSlotDurationStepSize(
    const xs_duration &slotDurationStepSize) {
  m_slotDurationStepSize = slotDurationStepSize;
  m_slotDurationStepSizeIsSet = true;
}

const xs_duration &TimeTableConstraintsData::getSlotDurationStepSize() const {
  return m_slotDurationStepSize;
}

void TimeTableConstraintsData::cleanSlotDurationStepSize() {
  m_slotDurationStepSize = xs_duration();
  m_slotDurationStepSizeIsSet = false;
}

bool TimeTableConstraintsData::getSlotDurationStepSizeIsSet() const {
  return m_slotDurationStepSizeIsSet;
}

void TimeTableConstraintsData::setSlotShiftStepSize(
    const xs_duration &slotShiftStepSize) {
  m_slotShiftStepSize = slotShiftStepSize;
  m_slotShiftStepSizeIsSet = true;
}

const xs_duration &TimeTableConstraintsData::getSlotShiftStepSize() const {
  return m_slotShiftStepSize;
}

void TimeTableConstraintsData::cleanSlotShiftStepSize() {
  m_slotShiftStepSize = xs_duration();
  m_slotShiftStepSizeIsSet = false;
}

bool TimeTableConstraintsData::getSlotShiftStepSizeIsSet() const {
  return m_slotShiftStepSizeIsSet;
}

void TimeTableConstraintsData::setFirstSlotBeginsAt(
    const xs_time &firstSlotBeginsAt) {
  m_firstSlotBeginsAt = firstSlotBeginsAt;
  m_firstSlotBeginsAtIsSet = true;
}

const xs_time &TimeTableConstraintsData::getFirstSlotBeginsAt() const {
  return m_firstSlotBeginsAt;
}

void TimeTableConstraintsData::cleanFirstSlotBeginsAt() {
  m_firstSlotBeginsAt = xs_time();
  m_firstSlotBeginsAtIsSet = false;
}

bool TimeTableConstraintsData::getFirstSlotBeginsAtIsSet() const {
  return m_firstSlotBeginsAtIsSet;
}

TimeTableConstraintsData TimeTableConstraintsData::reduce(
    const TimeTableConstraintsDataElements &elements) const {
  TimeTableConstraintsData dataOut;
  if (getTimeTableIdIsSet() && elements.getTimeTableIdIsSet()) {
    dataOut.setTimeTableId(getTimeTableId());
  }
  if (getSlotCountMinIsSet() && elements.getSlotCountMinIsSet()) {
    dataOut.setSlotCountMin(getSlotCountMin());
  }
  if (getSlotCountMaxIsSet() && elements.getSlotCountMaxIsSet()) {
    dataOut.setSlotCountMax(getSlotCountMax());
  }
  if (getSlotDurationMinIsSet() && elements.getSlotDurationMinIsSet()) {
    dataOut.setSlotDurationMin(getSlotDurationMin());
  }
  if (getSlotDurationMaxIsSet() && elements.getSlotDurationMaxIsSet()) {
    dataOut.setSlotDurationMax(getSlotDurationMax());
  }
  if (getSlotDurationStepSizeIsSet() &&
      elements.getSlotDurationStepSizeIsSet()) {
    dataOut.setSlotDurationStepSize(getSlotDurationStepSize());
  }
  if (getSlotShiftStepSizeIsSet() && elements.getSlotShiftStepSizeIsSet()) {
    dataOut.setSlotShiftStepSize(getSlotShiftStepSize());
  }
  if (getFirstSlotBeginsAtIsSet() && elements.getFirstSlotBeginsAtIsSet()) {
    dataOut.setFirstSlotBeginsAt(getFirstSlotBeginsAt());
  }
  return dataOut;
}

bool TimeTableConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeTableId", "slotCountMin", "slotCountMax",
                   "slotDurationMin", "slotDurationMax", "slotDurationStepSize",
                   "slotShiftStepSize", "firstSlotBeginsAt"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeTableId", &m_timeTableId)) {
      m_timeTableIdIsSet = true;
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
                                   "slotShiftStepSize", &m_slotShiftStepSize)) {
      m_slotShiftStepSizeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "firstSlotBeginsAt", &m_firstSlotBeginsAt)) {
      m_firstSlotBeginsAtIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableConstraintsData::toJson() const {
  std::string result = "[";
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
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
  if (m_slotShiftStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("slotShiftStepSize", m_slotShiftStepSize);
  }
  if (m_firstSlotBeginsAtIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("firstSlotBeginsAt", m_firstSlotBeginsAt);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram