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

#include <keo_datagram/timetable/TimeTableConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableConstraintsDataElements::TimeTableConstraintsDataElements()
    : DataElements(), m_timeTableIdIsSet(false), m_slotCountMinIsSet(false),
      m_slotCountMaxIsSet(false), m_slotDurationMinIsSet(false),
      m_slotDurationMaxIsSet(false), m_slotDurationStepSizeIsSet(false),
      m_slotShiftStepSizeIsSet(false), m_firstSlotBeginsAtIsSet(false)

{}

bool TimeTableConstraintsDataElements::
operator==(const TimeTableConstraintsDataElements &c_classObject) const {
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet) {
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
  if (m_slotShiftStepSizeIsSet != c_classObject.m_slotShiftStepSizeIsSet) {
    return false;
  }
  if (m_firstSlotBeginsAtIsSet != c_classObject.m_firstSlotBeginsAtIsSet) {
    return false;
  }

  return true;
}

bool TimeTableConstraintsDataElements::
operator!=(const TimeTableConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableConstraintsDataElements::isEmpty() const {
  return !m_timeTableIdIsSet && !m_slotCountMinIsSet && !m_slotCountMaxIsSet &&
         !m_slotDurationMinIsSet && !m_slotDurationMaxIsSet &&
         !m_slotDurationStepSizeIsSet && !m_slotShiftStepSizeIsSet &&
         !m_firstSlotBeginsAtIsSet;
}

DataElements::Type TimeTableConstraintsDataElements::getDataType() const {
  return DataElements::Type::TIME_TABLE_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimeTableConstraintsDataElements::clone() const {
  return std::make_shared<TimeTableConstraintsDataElements>(*this);
}

void TimeTableConstraintsDataElements::setTimeTableId() {
  m_timeTableIdIsSet = true;
}

void TimeTableConstraintsDataElements::cleanTimeTableId() {
  m_timeTableIdIsSet = false;
}

bool TimeTableConstraintsDataElements::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TimeTableConstraintsDataElements::setSlotCountMin() {
  m_slotCountMinIsSet = true;
}

void TimeTableConstraintsDataElements::cleanSlotCountMin() {
  m_slotCountMinIsSet = false;
}

bool TimeTableConstraintsDataElements::getSlotCountMinIsSet() const {
  return m_slotCountMinIsSet;
}

void TimeTableConstraintsDataElements::setSlotCountMax() {
  m_slotCountMaxIsSet = true;
}

void TimeTableConstraintsDataElements::cleanSlotCountMax() {
  m_slotCountMaxIsSet = false;
}

bool TimeTableConstraintsDataElements::getSlotCountMaxIsSet() const {
  return m_slotCountMaxIsSet;
}

void TimeTableConstraintsDataElements::setSlotDurationMin() {
  m_slotDurationMinIsSet = true;
}

void TimeTableConstraintsDataElements::cleanSlotDurationMin() {
  m_slotDurationMinIsSet = false;
}

bool TimeTableConstraintsDataElements::getSlotDurationMinIsSet() const {
  return m_slotDurationMinIsSet;
}

void TimeTableConstraintsDataElements::setSlotDurationMax() {
  m_slotDurationMaxIsSet = true;
}

void TimeTableConstraintsDataElements::cleanSlotDurationMax() {
  m_slotDurationMaxIsSet = false;
}

bool TimeTableConstraintsDataElements::getSlotDurationMaxIsSet() const {
  return m_slotDurationMaxIsSet;
}

void TimeTableConstraintsDataElements::setSlotDurationStepSize() {
  m_slotDurationStepSizeIsSet = true;
}

void TimeTableConstraintsDataElements::cleanSlotDurationStepSize() {
  m_slotDurationStepSizeIsSet = false;
}

bool TimeTableConstraintsDataElements::getSlotDurationStepSizeIsSet() const {
  return m_slotDurationStepSizeIsSet;
}

void TimeTableConstraintsDataElements::setSlotShiftStepSize() {
  m_slotShiftStepSizeIsSet = true;
}

void TimeTableConstraintsDataElements::cleanSlotShiftStepSize() {
  m_slotShiftStepSizeIsSet = false;
}

bool TimeTableConstraintsDataElements::getSlotShiftStepSizeIsSet() const {
  return m_slotShiftStepSizeIsSet;
}

void TimeTableConstraintsDataElements::setFirstSlotBeginsAt() {
  m_firstSlotBeginsAtIsSet = true;
}

void TimeTableConstraintsDataElements::cleanFirstSlotBeginsAt() {
  m_firstSlotBeginsAtIsSet = false;
}

bool TimeTableConstraintsDataElements::getFirstSlotBeginsAtIsSet() const {
  return m_firstSlotBeginsAtIsSet;
}

bool TimeTableConstraintsDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeTableId", "slotCountMin", "slotCountMax",
                   "slotDurationMin", "slotDurationMax", "slotDurationStepSize",
                   "slotShiftStepSize", "firstSlotBeginsAt"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeTableId")) {
      m_timeTableIdIsSet = true;
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
                                     "slotShiftStepSize")) {
      m_slotShiftStepSizeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "firstSlotBeginsAt")) {
      m_firstSlotBeginsAtIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeTableId");
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
  if (m_slotShiftStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotShiftStepSize");
  }
  if (m_firstSlotBeginsAtIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("firstSlotBeginsAt");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram