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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotScheduleDataElements::PowerTimeSlotScheduleDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_slotNumberIsSet(false),
      m_timePeriodIsSet(false), m_timePeriod(TimePeriodElements()),
      m_defaultDurationIsSet(false), m_durationUncertaintyIsSet(false),
      m_slotActivatedIsSet(false), m_descriptionIsSet(false)

{}

bool PowerTimeSlotScheduleDataElements::
operator==(const PowerTimeSlotScheduleDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_slotNumberIsSet != c_classObject.m_slotNumberIsSet) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_defaultDurationIsSet != c_classObject.m_defaultDurationIsSet) {
    return false;
  }
  if (m_durationUncertaintyIsSet != c_classObject.m_durationUncertaintyIsSet) {
    return false;
  }
  if (m_slotActivatedIsSet != c_classObject.m_slotActivatedIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool PowerTimeSlotScheduleDataElements::
operator!=(const PowerTimeSlotScheduleDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotScheduleDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet && !m_timePeriodIsSet &&
         !m_defaultDurationIsSet && !m_durationUncertaintyIsSet &&
         !m_slotActivatedIsSet && !m_descriptionIsSet;
}

DataElements::Type PowerTimeSlotScheduleDataElements::getDataType() const {
  return DataElements::Type::POWER_TIME_SLOT_SCHEDULE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerTimeSlotScheduleDataElements::clone() const {
  return std::make_shared<PowerTimeSlotScheduleDataElements>(*this);
}

void PowerTimeSlotScheduleDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerTimeSlotScheduleDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotScheduleDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotScheduleDataElements::setSlotNumber() {
  m_slotNumberIsSet = true;
}

void PowerTimeSlotScheduleDataElements::cleanSlotNumber() {
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotScheduleDataElements::getSlotNumberIsSet() const {
  return m_slotNumberIsSet;
}

void PowerTimeSlotScheduleDataElements::setTimePeriod(
    const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &
PowerTimeSlotScheduleDataElements::getTimePeriod() const {
  return m_timePeriod;
}

void PowerTimeSlotScheduleDataElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool PowerTimeSlotScheduleDataElements::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void PowerTimeSlotScheduleDataElements::setDefaultDuration() {
  m_defaultDurationIsSet = true;
}

void PowerTimeSlotScheduleDataElements::cleanDefaultDuration() {
  m_defaultDurationIsSet = false;
}

bool PowerTimeSlotScheduleDataElements::getDefaultDurationIsSet() const {
  return m_defaultDurationIsSet;
}

void PowerTimeSlotScheduleDataElements::setDurationUncertainty() {
  m_durationUncertaintyIsSet = true;
}

void PowerTimeSlotScheduleDataElements::cleanDurationUncertainty() {
  m_durationUncertaintyIsSet = false;
}

bool PowerTimeSlotScheduleDataElements::getDurationUncertaintyIsSet() const {
  return m_durationUncertaintyIsSet;
}

void PowerTimeSlotScheduleDataElements::setSlotActivated() {
  m_slotActivatedIsSet = true;
}

void PowerTimeSlotScheduleDataElements::cleanSlotActivated() {
  m_slotActivatedIsSet = false;
}

bool PowerTimeSlotScheduleDataElements::getSlotActivatedIsSet() const {
  return m_slotActivatedIsSet;
}

void PowerTimeSlotScheduleDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void PowerTimeSlotScheduleDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool PowerTimeSlotScheduleDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool PowerTimeSlotScheduleDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "slotNumber", "timePeriod", "defaultDuration",
                   "durationUncertainty", "slotActivated", "description"})) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timePeriod", &m_timePeriod)) {
      m_timePeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "defaultDuration")) {
      m_defaultDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "durationUncertainty")) {
      m_durationUncertaintyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "slotActivated")) {
      m_slotActivatedIsSet = true;
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

std::string PowerTimeSlotScheduleDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_slotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotNumber");
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_defaultDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("defaultDuration");
  }
  if (m_durationUncertaintyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("durationUncertainty");
  }
  if (m_slotActivatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotActivated");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram