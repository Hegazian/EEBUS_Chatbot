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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotScheduleConstraintsDataElements::
    PowerTimeSlotScheduleConstraintsDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_slotNumberIsSet(false),
      m_earliestStartTimeIsSet(false), m_latestEndTimeIsSet(false),
      m_minDurationIsSet(false), m_maxDurationIsSet(false),
      m_optionalSlotIsSet(false)

{}

bool PowerTimeSlotScheduleConstraintsDataElements::operator==(
    const PowerTimeSlotScheduleConstraintsDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_slotNumberIsSet != c_classObject.m_slotNumberIsSet) {
    return false;
  }
  if (m_earliestStartTimeIsSet != c_classObject.m_earliestStartTimeIsSet) {
    return false;
  }
  if (m_latestEndTimeIsSet != c_classObject.m_latestEndTimeIsSet) {
    return false;
  }
  if (m_minDurationIsSet != c_classObject.m_minDurationIsSet) {
    return false;
  }
  if (m_maxDurationIsSet != c_classObject.m_maxDurationIsSet) {
    return false;
  }
  if (m_optionalSlotIsSet != c_classObject.m_optionalSlotIsSet) {
    return false;
  }

  return true;
}

bool PowerTimeSlotScheduleConstraintsDataElements::operator!=(
    const PowerTimeSlotScheduleConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotScheduleConstraintsDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet &&
         !m_earliestStartTimeIsSet && !m_latestEndTimeIsSet &&
         !m_minDurationIsSet && !m_maxDurationIsSet && !m_optionalSlotIsSet;
}

DataElements::Type
PowerTimeSlotScheduleConstraintsDataElements::getDataType() const {
  return DataElements::Type::
      POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerTimeSlotScheduleConstraintsDataElements::clone() const {
  return std::make_shared<PowerTimeSlotScheduleConstraintsDataElements>(*this);
}

void PowerTimeSlotScheduleConstraintsDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerTimeSlotScheduleConstraintsDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotScheduleConstraintsDataElements::setSlotNumber() {
  m_slotNumberIsSet = true;
}

void PowerTimeSlotScheduleConstraintsDataElements::cleanSlotNumber() {
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsDataElements::getSlotNumberIsSet() const {
  return m_slotNumberIsSet;
}

void PowerTimeSlotScheduleConstraintsDataElements::setEarliestStartTime() {
  m_earliestStartTimeIsSet = true;
}

void PowerTimeSlotScheduleConstraintsDataElements::cleanEarliestStartTime() {
  m_earliestStartTimeIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsDataElements::getEarliestStartTimeIsSet()
    const {
  return m_earliestStartTimeIsSet;
}

void PowerTimeSlotScheduleConstraintsDataElements::setLatestEndTime() {
  m_latestEndTimeIsSet = true;
}

void PowerTimeSlotScheduleConstraintsDataElements::cleanLatestEndTime() {
  m_latestEndTimeIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsDataElements::getLatestEndTimeIsSet()
    const {
  return m_latestEndTimeIsSet;
}

void PowerTimeSlotScheduleConstraintsDataElements::setMinDuration() {
  m_minDurationIsSet = true;
}

void PowerTimeSlotScheduleConstraintsDataElements::cleanMinDuration() {
  m_minDurationIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsDataElements::getMinDurationIsSet() const {
  return m_minDurationIsSet;
}

void PowerTimeSlotScheduleConstraintsDataElements::setMaxDuration() {
  m_maxDurationIsSet = true;
}

void PowerTimeSlotScheduleConstraintsDataElements::cleanMaxDuration() {
  m_maxDurationIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsDataElements::getMaxDurationIsSet() const {
  return m_maxDurationIsSet;
}

void PowerTimeSlotScheduleConstraintsDataElements::setOptionalSlot() {
  m_optionalSlotIsSet = true;
}

void PowerTimeSlotScheduleConstraintsDataElements::cleanOptionalSlot() {
  m_optionalSlotIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsDataElements::getOptionalSlotIsSet()
    const {
  return m_optionalSlotIsSet;
}

bool PowerTimeSlotScheduleConstraintsDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"sequenceId", "slotNumber", "earliestStartTime", "latestEndTime",
             "minDuration", "maxDuration", "optionalSlot"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "slotNumber")) {
      m_slotNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "earliestStartTime")) {
      m_earliestStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "latestEndTime")) {
      m_latestEndTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "minDuration")) {
      m_minDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxDuration")) {
      m_maxDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "optionalSlot")) {
      m_optionalSlotIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerTimeSlotScheduleConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_slotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotNumber");
  }
  if (m_earliestStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("earliestStartTime");
  }
  if (m_latestEndTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("latestEndTime");
  }
  if (m_minDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("minDuration");
  }
  if (m_maxDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxDuration");
  }
  if (m_optionalSlotIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("optionalSlot");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram