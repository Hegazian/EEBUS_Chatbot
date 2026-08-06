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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotValueListDataSelectors::PowerTimeSlotValueListDataSelectors()
    : DataSelectors(), m_sequenceIdIsSet(false), m_sequenceId(0),
      m_slotNumberIsSet(false), m_slotNumber(0), m_valueTypeIsSet(false),
      m_valueType(PowerTimeSlotValueType())

{}

PowerTimeSlotValueListDataSelectors::PowerTimeSlotValueListDataSelectors(
    const xs_unsignedInt &c_sequenceId, const xs_unsignedInt &c_slotNumber,
    const PowerTimeSlotValueType &c_valueType)
    : DataSelectors(), m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId),
      m_slotNumberIsSet(true), m_slotNumber(c_slotNumber),
      m_valueTypeIsSet(true), m_valueType(c_valueType)

{}

bool PowerTimeSlotValueListDataSelectors::
operator==(const PowerTimeSlotValueListDataSelectors &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_slotNumberIsSet != c_classObject.m_slotNumberIsSet ||
      (m_slotNumberIsSet && (m_slotNumber != c_classObject.m_slotNumber))) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet ||
      (m_valueTypeIsSet && (m_valueType != c_classObject.m_valueType))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotValueListDataSelectors::
operator!=(const PowerTimeSlotValueListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotValueListDataSelectors::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet && !m_valueTypeIsSet;
}

DataSelectors::Type PowerTimeSlotValueListDataSelectors::getDataType() const {
  return DataSelectors::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr PowerTimeSlotValueListDataSelectors::clone() const {
  return std::make_shared<PowerTimeSlotValueListDataSelectors>(*this);
}

void PowerTimeSlotValueListDataSelectors::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerTimeSlotValueListDataSelectors::getSequenceId() const {
  return m_sequenceId;
}

void PowerTimeSlotValueListDataSelectors::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotValueListDataSelectors::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotValueListDataSelectors::setSlotNumber(
    const xs_unsignedInt &slotNumber) {
  m_slotNumber = slotNumber;
  m_slotNumberIsSet = true;
}

const xs_unsignedInt &
PowerTimeSlotValueListDataSelectors::getSlotNumber() const {
  return m_slotNumber;
}

void PowerTimeSlotValueListDataSelectors::cleanSlotNumber() {
  m_slotNumber = 0;
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotValueListDataSelectors::getSlotNumberIsSet() const {
  return m_slotNumberIsSet;
}

void PowerTimeSlotValueListDataSelectors::setValueType(
    const PowerTimeSlotValueType &valueType) {
  m_valueType = valueType;
  m_valueTypeIsSet = true;
}

const PowerTimeSlotValueType &
PowerTimeSlotValueListDataSelectors::getValueType() const {
  return m_valueType;
}

void PowerTimeSlotValueListDataSelectors::cleanValueType() {
  m_valueType = PowerTimeSlotValueType();
  m_valueTypeIsSet = false;
}

bool PowerTimeSlotValueListDataSelectors::getValueTypeIsSet() const {
  return m_valueTypeIsSet;
}

bool PowerTimeSlotValueListDataSelectors::selects(
    const PowerTimeSlotValueData &data) const {
  if (getSequenceIdIsSet() &&
      (!data.getSequenceIdIsSet() || getSequenceId() != data.getSequenceId())) {
    return false;
  }
  if (getSlotNumberIsSet() &&
      (!data.getSlotNumberIsSet() || getSlotNumber() != data.getSlotNumber())) {
    return false;
  }
  if (getValueTypeIsSet() &&
      (!data.getValueTypeIsSet() || getValueType() != data.getValueType())) {
    return false;
  }
  return true;
}

bool PowerTimeSlotValueListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "slotNumber", "valueType"})) {
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
                                   "valueType", &m_valueType)) {
      m_valueTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerTimeSlotValueListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_slotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotNumber", m_slotNumber);
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueType", m_valueType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram