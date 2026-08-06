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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleData.h>

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotScheduleData::PowerTimeSlotScheduleData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_slotNumberIsSet(false),
      m_slotNumber(0), m_timePeriodIsSet(false), m_timePeriod(TimePeriod()),
      m_defaultDurationIsSet(false), m_defaultDuration(xs_duration()),
      m_durationUncertaintyIsSet(false), m_durationUncertainty(xs_duration()),
      m_slotActivatedIsSet(false), m_slotActivated(false),
      m_descriptionIsSet(false), m_description("")

{}

bool PowerTimeSlotScheduleData::
operator==(const PowerTimeSlotScheduleData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_slotNumberIsSet != c_classObject.m_slotNumberIsSet ||
      (m_slotNumberIsSet && (m_slotNumber != c_classObject.m_slotNumber))) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_defaultDurationIsSet != c_classObject.m_defaultDurationIsSet ||
      (m_defaultDurationIsSet &&
       (m_defaultDuration != c_classObject.m_defaultDuration))) {
    return false;
  }
  if (m_durationUncertaintyIsSet != c_classObject.m_durationUncertaintyIsSet ||
      (m_durationUncertaintyIsSet &&
       (m_durationUncertainty != c_classObject.m_durationUncertainty))) {
    return false;
  }
  if (m_slotActivatedIsSet != c_classObject.m_slotActivatedIsSet ||
      (m_slotActivatedIsSet &&
       (m_slotActivated != c_classObject.m_slotActivated))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotScheduleData::
operator!=(const PowerTimeSlotScheduleData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotScheduleData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet && !m_timePeriodIsSet &&
         !m_defaultDurationIsSet && !m_durationUncertaintyIsSet &&
         !m_slotActivatedIsSet && !m_descriptionIsSet;
}

void PowerTimeSlotScheduleData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &PowerTimeSlotScheduleData::getSequenceId() const {
  return m_sequenceId;
}

void PowerTimeSlotScheduleData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotScheduleData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotScheduleData::setSlotNumber(
    const xs_unsignedInt &slotNumber) {
  m_slotNumber = slotNumber;
  m_slotNumberIsSet = true;
}

const xs_unsignedInt &PowerTimeSlotScheduleData::getSlotNumber() const {
  return m_slotNumber;
}

void PowerTimeSlotScheduleData::cleanSlotNumber() {
  m_slotNumber = 0;
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotScheduleData::getSlotNumberIsSet() const {
  return m_slotNumberIsSet;
}

void PowerTimeSlotScheduleData::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &PowerTimeSlotScheduleData::getTimePeriod() const {
  return m_timePeriod;
}

void PowerTimeSlotScheduleData::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool PowerTimeSlotScheduleData::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void PowerTimeSlotScheduleData::setDefaultDuration(
    const xs_duration &defaultDuration) {
  m_defaultDuration = defaultDuration;
  m_defaultDurationIsSet = true;
}

const xs_duration &PowerTimeSlotScheduleData::getDefaultDuration() const {
  return m_defaultDuration;
}

void PowerTimeSlotScheduleData::cleanDefaultDuration() {
  m_defaultDuration = xs_duration();
  m_defaultDurationIsSet = false;
}

bool PowerTimeSlotScheduleData::getDefaultDurationIsSet() const {
  return m_defaultDurationIsSet;
}

void PowerTimeSlotScheduleData::setDurationUncertainty(
    const xs_duration &durationUncertainty) {
  m_durationUncertainty = durationUncertainty;
  m_durationUncertaintyIsSet = true;
}

const xs_duration &PowerTimeSlotScheduleData::getDurationUncertainty() const {
  return m_durationUncertainty;
}

void PowerTimeSlotScheduleData::cleanDurationUncertainty() {
  m_durationUncertainty = xs_duration();
  m_durationUncertaintyIsSet = false;
}

bool PowerTimeSlotScheduleData::getDurationUncertaintyIsSet() const {
  return m_durationUncertaintyIsSet;
}

void PowerTimeSlotScheduleData::setSlotActivated(
    const xs_boolean &slotActivated) {
  m_slotActivated = slotActivated;
  m_slotActivatedIsSet = true;
}

const xs_boolean &PowerTimeSlotScheduleData::getSlotActivated() const {
  return m_slotActivated;
}

void PowerTimeSlotScheduleData::cleanSlotActivated() {
  m_slotActivated = false;
  m_slotActivatedIsSet = false;
}

bool PowerTimeSlotScheduleData::getSlotActivatedIsSet() const {
  return m_slotActivatedIsSet;
}

void PowerTimeSlotScheduleData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &PowerTimeSlotScheduleData::getDescription() const {
  return m_description;
}

void PowerTimeSlotScheduleData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool PowerTimeSlotScheduleData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

PowerTimeSlotScheduleData PowerTimeSlotScheduleData::reduce(
    const PowerTimeSlotScheduleDataElements &elements) const {
  PowerTimeSlotScheduleData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getSlotNumberIsSet() && elements.getSlotNumberIsSet()) {
    dataOut.setSlotNumber(getSlotNumber());
  }
  if (getTimePeriodIsSet() && elements.getTimePeriodIsSet()) {
    dataOut.setTimePeriod(getTimePeriod().reduce(elements.getTimePeriod()));
  }
  if (getDefaultDurationIsSet() && elements.getDefaultDurationIsSet()) {
    dataOut.setDefaultDuration(getDefaultDuration());
  }
  if (getDurationUncertaintyIsSet() && elements.getDurationUncertaintyIsSet()) {
    dataOut.setDurationUncertainty(getDurationUncertainty());
  }
  if (getSlotActivatedIsSet() && elements.getSlotActivatedIsSet()) {
    dataOut.setSlotActivated(getSlotActivated());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool PowerTimeSlotScheduleData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "slotNumber", "timePeriod", "defaultDuration",
                   "durationUncertainty", "slotActivated", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotNumber", &m_slotNumber)) {
      m_slotNumberIsSet = true;
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
                                   "defaultDuration", &m_defaultDuration)) {
      m_defaultDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "durationUncertainty",
                                   &m_durationUncertainty)) {
      m_durationUncertaintyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotActivated", &m_slotActivated)) {
      m_slotActivatedIsSet = true;
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

std::string PowerTimeSlotScheduleData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_slotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotNumber", m_slotNumber);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_defaultDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("defaultDuration", m_defaultDuration);
  }
  if (m_durationUncertaintyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("durationUncertainty",
                                           m_durationUncertainty);
  }
  if (m_slotActivatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotActivated", m_slotActivated);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram