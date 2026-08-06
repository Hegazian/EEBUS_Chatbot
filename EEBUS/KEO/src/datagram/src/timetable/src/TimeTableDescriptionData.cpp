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

#include <keo_datagram/timetable/TimeTableDescriptionData.h>

#include <keo_datagram/timetable/TimeTableDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableDescriptionData::TimeTableDescriptionData()
    : m_timeTableIdIsSet(false), m_timeTableId(0),
      m_timeSlotCountChangeableIsSet(false), m_timeSlotCountChangeable(false),
      m_timeSlotTimesChangeableIsSet(false), m_timeSlotTimesChangeable(false),
      m_timeSlotTimeModeIsSet(false), m_timeSlotTimeMode(TimeSlotTimeMode()),
      m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description("")

{}

bool TimeTableDescriptionData::
operator==(const TimeTableDescriptionData &c_classObject) const {
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
    return false;
  }
  if (m_timeSlotCountChangeableIsSet !=
          c_classObject.m_timeSlotCountChangeableIsSet ||
      (m_timeSlotCountChangeableIsSet &&
       (m_timeSlotCountChangeable !=
        c_classObject.m_timeSlotCountChangeable))) {
    return false;
  }
  if (m_timeSlotTimesChangeableIsSet !=
          c_classObject.m_timeSlotTimesChangeableIsSet ||
      (m_timeSlotTimesChangeableIsSet &&
       (m_timeSlotTimesChangeable !=
        c_classObject.m_timeSlotTimesChangeable))) {
    return false;
  }
  if (m_timeSlotTimeModeIsSet != c_classObject.m_timeSlotTimeModeIsSet ||
      (m_timeSlotTimeModeIsSet &&
       (m_timeSlotTimeMode != c_classObject.m_timeSlotTimeMode))) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool TimeTableDescriptionData::
operator!=(const TimeTableDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableDescriptionData::isEmpty() const {
  return !m_timeTableIdIsSet && !m_timeSlotCountChangeableIsSet &&
         !m_timeSlotTimesChangeableIsSet && !m_timeSlotTimeModeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

void TimeTableDescriptionData::setTimeTableId(
    const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &TimeTableDescriptionData::getTimeTableId() const {
  return m_timeTableId;
}

void TimeTableDescriptionData::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool TimeTableDescriptionData::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TimeTableDescriptionData::setTimeSlotCountChangeable(
    const xs_boolean &timeSlotCountChangeable) {
  m_timeSlotCountChangeable = timeSlotCountChangeable;
  m_timeSlotCountChangeableIsSet = true;
}

const xs_boolean &TimeTableDescriptionData::getTimeSlotCountChangeable() const {
  return m_timeSlotCountChangeable;
}

void TimeTableDescriptionData::cleanTimeSlotCountChangeable() {
  m_timeSlotCountChangeable = false;
  m_timeSlotCountChangeableIsSet = false;
}

bool TimeTableDescriptionData::getTimeSlotCountChangeableIsSet() const {
  return m_timeSlotCountChangeableIsSet;
}

void TimeTableDescriptionData::setTimeSlotTimesChangeable(
    const xs_boolean &timeSlotTimesChangeable) {
  m_timeSlotTimesChangeable = timeSlotTimesChangeable;
  m_timeSlotTimesChangeableIsSet = true;
}

const xs_boolean &TimeTableDescriptionData::getTimeSlotTimesChangeable() const {
  return m_timeSlotTimesChangeable;
}

void TimeTableDescriptionData::cleanTimeSlotTimesChangeable() {
  m_timeSlotTimesChangeable = false;
  m_timeSlotTimesChangeableIsSet = false;
}

bool TimeTableDescriptionData::getTimeSlotTimesChangeableIsSet() const {
  return m_timeSlotTimesChangeableIsSet;
}

void TimeTableDescriptionData::setTimeSlotTimeMode(
    const TimeSlotTimeMode &timeSlotTimeMode) {
  m_timeSlotTimeMode = timeSlotTimeMode;
  m_timeSlotTimeModeIsSet = true;
}

const TimeSlotTimeMode &TimeTableDescriptionData::getTimeSlotTimeMode() const {
  return m_timeSlotTimeMode;
}

void TimeTableDescriptionData::cleanTimeSlotTimeMode() {
  m_timeSlotTimeMode = TimeSlotTimeMode();
  m_timeSlotTimeModeIsSet = false;
}

bool TimeTableDescriptionData::getTimeSlotTimeModeIsSet() const {
  return m_timeSlotTimeModeIsSet;
}

void TimeTableDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &TimeTableDescriptionData::getLabel() const { return m_label; }

void TimeTableDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool TimeTableDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void TimeTableDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &TimeTableDescriptionData::getDescription() const {
  return m_description;
}

void TimeTableDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool TimeTableDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

TimeTableDescriptionData TimeTableDescriptionData::reduce(
    const TimeTableDescriptionDataElements &elements) const {
  TimeTableDescriptionData dataOut;
  if (getTimeTableIdIsSet() && elements.getTimeTableIdIsSet()) {
    dataOut.setTimeTableId(getTimeTableId());
  }
  if (getTimeSlotCountChangeableIsSet() &&
      elements.getTimeSlotCountChangeableIsSet()) {
    dataOut.setTimeSlotCountChangeable(getTimeSlotCountChangeable());
  }
  if (getTimeSlotTimesChangeableIsSet() &&
      elements.getTimeSlotTimesChangeableIsSet()) {
    dataOut.setTimeSlotTimesChangeable(getTimeSlotTimesChangeable());
  }
  if (getTimeSlotTimeModeIsSet() && elements.getTimeSlotTimeModeIsSet()) {
    dataOut.setTimeSlotTimeMode(getTimeSlotTimeMode());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool TimeTableDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeTableId", "timeSlotCountChangeable",
                   "timeSlotTimesChangeable", "timeSlotTimeMode", "label",
                   "description"})) {
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
                                   "timeSlotCountChangeable",
                                   &m_timeSlotCountChangeable)) {
      m_timeSlotCountChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSlotTimesChangeable",
                                   &m_timeSlotTimesChangeable)) {
      m_timeSlotTimesChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSlotTimeMode", &m_timeSlotTimeMode)) {
      m_timeSlotTimeModeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableDescriptionData::toJson() const {
  std::string result = "[";
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  if (m_timeSlotCountChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSlotCountChangeable",
                                           m_timeSlotCountChangeable);
  }
  if (m_timeSlotTimesChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSlotTimesChangeable",
                                           m_timeSlotTimesChangeable);
  }
  if (m_timeSlotTimeModeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timeSlotTimeMode", m_timeSlotTimeMode);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram