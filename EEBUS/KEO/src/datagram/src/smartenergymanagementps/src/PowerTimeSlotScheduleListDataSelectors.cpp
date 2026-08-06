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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotScheduleListDataSelectors::PowerTimeSlotScheduleListDataSelectors()
    : DataSelectors(), m_sequenceIdIsSet(false), m_sequenceId(0),
      m_slotNumberIsSet(false), m_slotNumber(0)

{}

PowerTimeSlotScheduleListDataSelectors::PowerTimeSlotScheduleListDataSelectors(
    const xs_unsignedInt &c_sequenceId, const xs_unsignedInt &c_slotNumber)
    : DataSelectors(), m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId),
      m_slotNumberIsSet(true), m_slotNumber(c_slotNumber)

{}

bool PowerTimeSlotScheduleListDataSelectors::
operator==(const PowerTimeSlotScheduleListDataSelectors &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_slotNumberIsSet != c_classObject.m_slotNumberIsSet ||
      (m_slotNumberIsSet && (m_slotNumber != c_classObject.m_slotNumber))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotScheduleListDataSelectors::
operator!=(const PowerTimeSlotScheduleListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotScheduleListDataSelectors::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet;
}

DataSelectors::Type
PowerTimeSlotScheduleListDataSelectors::getDataType() const {
  return DataSelectors::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr PowerTimeSlotScheduleListDataSelectors::clone() const {
  return std::make_shared<PowerTimeSlotScheduleListDataSelectors>(*this);
}

void PowerTimeSlotScheduleListDataSelectors::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerTimeSlotScheduleListDataSelectors::getSequenceId() const {
  return m_sequenceId;
}

void PowerTimeSlotScheduleListDataSelectors::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotScheduleListDataSelectors::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotScheduleListDataSelectors::setSlotNumber(
    const xs_unsignedInt &slotNumber) {
  m_slotNumber = slotNumber;
  m_slotNumberIsSet = true;
}

const xs_unsignedInt &
PowerTimeSlotScheduleListDataSelectors::getSlotNumber() const {
  return m_slotNumber;
}

void PowerTimeSlotScheduleListDataSelectors::cleanSlotNumber() {
  m_slotNumber = 0;
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotScheduleListDataSelectors::getSlotNumberIsSet() const {
  return m_slotNumberIsSet;
}

bool PowerTimeSlotScheduleListDataSelectors::selects(
    const PowerTimeSlotScheduleData &data) const {
  if (getSequenceIdIsSet() &&
      (!data.getSequenceIdIsSet() || getSequenceId() != data.getSequenceId())) {
    return false;
  }
  if (getSlotNumberIsSet() &&
      (!data.getSlotNumberIsSet() || getSlotNumber() != data.getSlotNumber())) {
    return false;
  }
  return true;
}

bool PowerTimeSlotScheduleListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"sequenceId", "slotNumber"})) {
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
  }
  return true;
}

std::string PowerTimeSlotScheduleListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_slotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotNumber", m_slotNumber);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram