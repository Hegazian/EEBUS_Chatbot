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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsData.h>

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotScheduleConstraintsData::PowerTimeSlotScheduleConstraintsData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_slotNumberIsSet(false),
      m_slotNumber(0), m_earliestStartTimeIsSet(false),
      m_earliestStartTime(AbsoluteOrRelativeTime()),
      m_latestEndTimeIsSet(false), m_latestEndTime(AbsoluteOrRelativeTime()),
      m_minDurationIsSet(false), m_minDuration(xs_duration()),
      m_maxDurationIsSet(false), m_maxDuration(xs_duration()),
      m_optionalSlotIsSet(false), m_optionalSlot(false)

{}

bool PowerTimeSlotScheduleConstraintsData::
operator==(const PowerTimeSlotScheduleConstraintsData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_slotNumberIsSet != c_classObject.m_slotNumberIsSet ||
      (m_slotNumberIsSet && (m_slotNumber != c_classObject.m_slotNumber))) {
    return false;
  }
  if (m_earliestStartTimeIsSet != c_classObject.m_earliestStartTimeIsSet ||
      (m_earliestStartTimeIsSet &&
       (m_earliestStartTime != c_classObject.m_earliestStartTime))) {
    return false;
  }
  if (m_latestEndTimeIsSet != c_classObject.m_latestEndTimeIsSet ||
      (m_latestEndTimeIsSet &&
       (m_latestEndTime != c_classObject.m_latestEndTime))) {
    return false;
  }
  if (m_minDurationIsSet != c_classObject.m_minDurationIsSet ||
      (m_minDurationIsSet && (m_minDuration != c_classObject.m_minDuration))) {
    return false;
  }
  if (m_maxDurationIsSet != c_classObject.m_maxDurationIsSet ||
      (m_maxDurationIsSet && (m_maxDuration != c_classObject.m_maxDuration))) {
    return false;
  }
  if (m_optionalSlotIsSet != c_classObject.m_optionalSlotIsSet ||
      (m_optionalSlotIsSet &&
       (m_optionalSlot != c_classObject.m_optionalSlot))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotScheduleConstraintsData::
operator!=(const PowerTimeSlotScheduleConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotScheduleConstraintsData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet &&
         !m_earliestStartTimeIsSet && !m_latestEndTimeIsSet &&
         !m_minDurationIsSet && !m_maxDurationIsSet && !m_optionalSlotIsSet;
}

void PowerTimeSlotScheduleConstraintsData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerTimeSlotScheduleConstraintsData::getSequenceId() const {
  return m_sequenceId;
}

void PowerTimeSlotScheduleConstraintsData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotScheduleConstraintsData::setSlotNumber(
    const xs_unsignedInt &slotNumber) {
  m_slotNumber = slotNumber;
  m_slotNumberIsSet = true;
}

const xs_unsignedInt &
PowerTimeSlotScheduleConstraintsData::getSlotNumber() const {
  return m_slotNumber;
}

void PowerTimeSlotScheduleConstraintsData::cleanSlotNumber() {
  m_slotNumber = 0;
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsData::getSlotNumberIsSet() const {
  return m_slotNumberIsSet;
}

void PowerTimeSlotScheduleConstraintsData::setEarliestStartTime(
    const AbsoluteOrRelativeTime &earliestStartTime) {
  m_earliestStartTime = earliestStartTime;
  m_earliestStartTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
PowerTimeSlotScheduleConstraintsData::getEarliestStartTime() const {
  return m_earliestStartTime;
}

void PowerTimeSlotScheduleConstraintsData::cleanEarliestStartTime() {
  m_earliestStartTime = AbsoluteOrRelativeTime();
  m_earliestStartTimeIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsData::getEarliestStartTimeIsSet() const {
  return m_earliestStartTimeIsSet;
}

void PowerTimeSlotScheduleConstraintsData::setLatestEndTime(
    const AbsoluteOrRelativeTime &latestEndTime) {
  m_latestEndTime = latestEndTime;
  m_latestEndTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
PowerTimeSlotScheduleConstraintsData::getLatestEndTime() const {
  return m_latestEndTime;
}

void PowerTimeSlotScheduleConstraintsData::cleanLatestEndTime() {
  m_latestEndTime = AbsoluteOrRelativeTime();
  m_latestEndTimeIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsData::getLatestEndTimeIsSet() const {
  return m_latestEndTimeIsSet;
}

void PowerTimeSlotScheduleConstraintsData::setMinDuration(
    const xs_duration &minDuration) {
  m_minDuration = minDuration;
  m_minDurationIsSet = true;
}

const xs_duration &
PowerTimeSlotScheduleConstraintsData::getMinDuration() const {
  return m_minDuration;
}

void PowerTimeSlotScheduleConstraintsData::cleanMinDuration() {
  m_minDuration = xs_duration();
  m_minDurationIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsData::getMinDurationIsSet() const {
  return m_minDurationIsSet;
}

void PowerTimeSlotScheduleConstraintsData::setMaxDuration(
    const xs_duration &maxDuration) {
  m_maxDuration = maxDuration;
  m_maxDurationIsSet = true;
}

const xs_duration &
PowerTimeSlotScheduleConstraintsData::getMaxDuration() const {
  return m_maxDuration;
}

void PowerTimeSlotScheduleConstraintsData::cleanMaxDuration() {
  m_maxDuration = xs_duration();
  m_maxDurationIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsData::getMaxDurationIsSet() const {
  return m_maxDurationIsSet;
}

void PowerTimeSlotScheduleConstraintsData::setOptionalSlot(
    const xs_boolean &optionalSlot) {
  m_optionalSlot = optionalSlot;
  m_optionalSlotIsSet = true;
}

const xs_boolean &
PowerTimeSlotScheduleConstraintsData::getOptionalSlot() const {
  return m_optionalSlot;
}

void PowerTimeSlotScheduleConstraintsData::cleanOptionalSlot() {
  m_optionalSlot = false;
  m_optionalSlotIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsData::getOptionalSlotIsSet() const {
  return m_optionalSlotIsSet;
}

PowerTimeSlotScheduleConstraintsData
PowerTimeSlotScheduleConstraintsData::reduce(
    const PowerTimeSlotScheduleConstraintsDataElements &elements) const {
  PowerTimeSlotScheduleConstraintsData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getSlotNumberIsSet() && elements.getSlotNumberIsSet()) {
    dataOut.setSlotNumber(getSlotNumber());
  }
  if (getEarliestStartTimeIsSet() && elements.getEarliestStartTimeIsSet()) {
    dataOut.setEarliestStartTime(getEarliestStartTime());
  }
  if (getLatestEndTimeIsSet() && elements.getLatestEndTimeIsSet()) {
    dataOut.setLatestEndTime(getLatestEndTime());
  }
  if (getMinDurationIsSet() && elements.getMinDurationIsSet()) {
    dataOut.setMinDuration(getMinDuration());
  }
  if (getMaxDurationIsSet() && elements.getMaxDurationIsSet()) {
    dataOut.setMaxDuration(getMaxDuration());
  }
  if (getOptionalSlotIsSet() && elements.getOptionalSlotIsSet()) {
    dataOut.setOptionalSlot(getOptionalSlot());
  }
  return dataOut;
}

bool PowerTimeSlotScheduleConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"sequenceId", "slotNumber", "earliestStartTime", "latestEndTime",
             "minDuration", "maxDuration", "optionalSlot"})) {
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
                                   "earliestStartTime", &m_earliestStartTime)) {
      m_earliestStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "latestEndTime", &m_latestEndTime)) {
      m_latestEndTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "minDuration", &m_minDuration)) {
      m_minDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxDuration", &m_maxDuration)) {
      m_maxDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "optionalSlot", &m_optionalSlot)) {
      m_optionalSlotIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerTimeSlotScheduleConstraintsData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_slotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotNumber", m_slotNumber);
  }
  if (m_earliestStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("earliestStartTime", m_earliestStartTime);
  }
  if (m_latestEndTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("latestEndTime", m_latestEndTime);
  }
  if (m_minDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("minDuration", m_minDuration);
  }
  if (m_maxDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("maxDuration", m_maxDuration);
  }
  if (m_optionalSlotIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("optionalSlot", m_optionalSlot);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram