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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotScheduleConstraintsListDataSelectors::
    PowerTimeSlotScheduleConstraintsListDataSelectors()
    : DataSelectors(), m_sequenceIdIsSet(false), m_sequenceId(0),
      m_slotNumberIsSet(false), m_slotNumber(0)

{}

PowerTimeSlotScheduleConstraintsListDataSelectors::
    PowerTimeSlotScheduleConstraintsListDataSelectors(
        const xs_unsignedInt &c_sequenceId, const xs_unsignedInt &c_slotNumber)
    : DataSelectors(), m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId),
      m_slotNumberIsSet(true), m_slotNumber(c_slotNumber)

{}

bool PowerTimeSlotScheduleConstraintsListDataSelectors::operator==(
    const PowerTimeSlotScheduleConstraintsListDataSelectors &c_classObject)
    const {
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

bool PowerTimeSlotScheduleConstraintsListDataSelectors::operator!=(
    const PowerTimeSlotScheduleConstraintsListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotScheduleConstraintsListDataSelectors::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet;
}

DataSelectors::Type
PowerTimeSlotScheduleConstraintsListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
PowerTimeSlotScheduleConstraintsListDataSelectors::clone() const {
  return std::make_shared<PowerTimeSlotScheduleConstraintsListDataSelectors>(
      *this);
}

void PowerTimeSlotScheduleConstraintsListDataSelectors::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerTimeSlotScheduleConstraintsListDataSelectors::getSequenceId() const {
  return m_sequenceId;
}

void PowerTimeSlotScheduleConstraintsListDataSelectors::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsListDataSelectors::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotScheduleConstraintsListDataSelectors::setSlotNumber(
    const xs_unsignedInt &slotNumber) {
  m_slotNumber = slotNumber;
  m_slotNumberIsSet = true;
}

const xs_unsignedInt &
PowerTimeSlotScheduleConstraintsListDataSelectors::getSlotNumber() const {
  return m_slotNumber;
}

void PowerTimeSlotScheduleConstraintsListDataSelectors::cleanSlotNumber() {
  m_slotNumber = 0;
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsListDataSelectors::getSlotNumberIsSet()
    const {
  return m_slotNumberIsSet;
}

bool PowerTimeSlotScheduleConstraintsListDataSelectors::selects(
    const PowerTimeSlotScheduleConstraintsData &data) const {
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

bool PowerTimeSlotScheduleConstraintsListDataSelectors::fromJson(
    KeoJsonValue *json) {
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

std::string PowerTimeSlotScheduleConstraintsListDataSelectors::toJson() const {
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