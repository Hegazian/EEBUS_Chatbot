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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueData.h>

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotValueData::PowerTimeSlotValueData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_slotNumberIsSet(false),
      m_slotNumber(0), m_valueTypeIsSet(false),
      m_valueType(PowerTimeSlotValueType()), m_valueIsSet(false),
      m_value(ScaledNumber())

{}

bool PowerTimeSlotValueData::
operator==(const PowerTimeSlotValueData &c_classObject) const {
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
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotValueData::
operator!=(const PowerTimeSlotValueData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotValueData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet && !m_valueTypeIsSet &&
         !m_valueIsSet;
}

void PowerTimeSlotValueData::setSequenceId(const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &PowerTimeSlotValueData::getSequenceId() const {
  return m_sequenceId;
}

void PowerTimeSlotValueData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotValueData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotValueData::setSlotNumber(const xs_unsignedInt &slotNumber) {
  m_slotNumber = slotNumber;
  m_slotNumberIsSet = true;
}

const xs_unsignedInt &PowerTimeSlotValueData::getSlotNumber() const {
  return m_slotNumber;
}

void PowerTimeSlotValueData::cleanSlotNumber() {
  m_slotNumber = 0;
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotValueData::getSlotNumberIsSet() const {
  return m_slotNumberIsSet;
}

void PowerTimeSlotValueData::setValueType(
    const PowerTimeSlotValueType &valueType) {
  m_valueType = valueType;
  m_valueTypeIsSet = true;
}

const PowerTimeSlotValueType &PowerTimeSlotValueData::getValueType() const {
  return m_valueType;
}

void PowerTimeSlotValueData::cleanValueType() {
  m_valueType = PowerTimeSlotValueType();
  m_valueTypeIsSet = false;
}

bool PowerTimeSlotValueData::getValueTypeIsSet() const {
  return m_valueTypeIsSet;
}

void PowerTimeSlotValueData::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &PowerTimeSlotValueData::getValue() const { return m_value; }

void PowerTimeSlotValueData::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool PowerTimeSlotValueData::getValueIsSet() const { return m_valueIsSet; }

PowerTimeSlotValueData PowerTimeSlotValueData::reduce(
    const PowerTimeSlotValueDataElements &elements) const {
  PowerTimeSlotValueData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getSlotNumberIsSet() && elements.getSlotNumberIsSet()) {
    dataOut.setSlotNumber(getSlotNumber());
  }
  if (getValueTypeIsSet() && elements.getValueTypeIsSet()) {
    dataOut.setValueType(getValueType());
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    dataOut.setValue(getValue().reduce(elements.getValue()));
  }
  return dataOut;
}

bool PowerTimeSlotValueData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "slotNumber", "valueType", "value"})) {
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
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerTimeSlotValueData::toJson() const {
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
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram