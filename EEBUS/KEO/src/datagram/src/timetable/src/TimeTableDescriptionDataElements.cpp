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

#include <keo_datagram/timetable/TimeTableDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableDescriptionDataElements::TimeTableDescriptionDataElements()
    : DataElements(), m_timeTableIdIsSet(false),
      m_timeSlotCountChangeableIsSet(false),
      m_timeSlotTimesChangeableIsSet(false), m_timeSlotTimeModeIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool TimeTableDescriptionDataElements::
operator==(const TimeTableDescriptionDataElements &c_classObject) const {
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet) {
    return false;
  }
  if (m_timeSlotCountChangeableIsSet !=
      c_classObject.m_timeSlotCountChangeableIsSet) {
    return false;
  }
  if (m_timeSlotTimesChangeableIsSet !=
      c_classObject.m_timeSlotTimesChangeableIsSet) {
    return false;
  }
  if (m_timeSlotTimeModeIsSet != c_classObject.m_timeSlotTimeModeIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool TimeTableDescriptionDataElements::
operator!=(const TimeTableDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableDescriptionDataElements::isEmpty() const {
  return !m_timeTableIdIsSet && !m_timeSlotCountChangeableIsSet &&
         !m_timeSlotTimesChangeableIsSet && !m_timeSlotTimeModeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type TimeTableDescriptionDataElements::getDataType() const {
  return DataElements::Type::TIME_TABLE_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimeTableDescriptionDataElements::clone() const {
  return std::make_shared<TimeTableDescriptionDataElements>(*this);
}

void TimeTableDescriptionDataElements::setTimeTableId() {
  m_timeTableIdIsSet = true;
}

void TimeTableDescriptionDataElements::cleanTimeTableId() {
  m_timeTableIdIsSet = false;
}

bool TimeTableDescriptionDataElements::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TimeTableDescriptionDataElements::setTimeSlotCountChangeable() {
  m_timeSlotCountChangeableIsSet = true;
}

void TimeTableDescriptionDataElements::cleanTimeSlotCountChangeable() {
  m_timeSlotCountChangeableIsSet = false;
}

bool TimeTableDescriptionDataElements::getTimeSlotCountChangeableIsSet() const {
  return m_timeSlotCountChangeableIsSet;
}

void TimeTableDescriptionDataElements::setTimeSlotTimesChangeable() {
  m_timeSlotTimesChangeableIsSet = true;
}

void TimeTableDescriptionDataElements::cleanTimeSlotTimesChangeable() {
  m_timeSlotTimesChangeableIsSet = false;
}

bool TimeTableDescriptionDataElements::getTimeSlotTimesChangeableIsSet() const {
  return m_timeSlotTimesChangeableIsSet;
}

void TimeTableDescriptionDataElements::setTimeSlotTimeMode() {
  m_timeSlotTimeModeIsSet = true;
}

void TimeTableDescriptionDataElements::cleanTimeSlotTimeMode() {
  m_timeSlotTimeModeIsSet = false;
}

bool TimeTableDescriptionDataElements::getTimeSlotTimeModeIsSet() const {
  return m_timeSlotTimeModeIsSet;
}

void TimeTableDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void TimeTableDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool TimeTableDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void TimeTableDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void TimeTableDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool TimeTableDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool TimeTableDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeTableId", "timeSlotCountChangeable",
                   "timeSlotTimesChangeable", "timeSlotTimeMode", "label",
                   "description"})) {
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
                                     "timeSlotCountChangeable")) {
      m_timeSlotCountChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSlotTimesChangeable")) {
      m_timeSlotTimesChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSlotTimeMode")) {
      m_timeSlotTimeModeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeTableId");
  }
  if (m_timeSlotCountChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSlotCountChangeable");
  }
  if (m_timeSlotTimesChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSlotTimesChangeable");
  }
  if (m_timeSlotTimeModeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSlotTimeMode");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram