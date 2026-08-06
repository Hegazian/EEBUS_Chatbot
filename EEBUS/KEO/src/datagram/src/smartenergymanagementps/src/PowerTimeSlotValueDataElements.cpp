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

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotValueDataElements::PowerTimeSlotValueDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_slotNumberIsSet(false),
      m_valueTypeIsSet(false), m_valueIsSet(false),
      m_value(ScaledNumberElements())

{}

bool PowerTimeSlotValueDataElements::
operator==(const PowerTimeSlotValueDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_slotNumberIsSet != c_classObject.m_slotNumberIsSet) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotValueDataElements::
operator!=(const PowerTimeSlotValueDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotValueDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_slotNumberIsSet && !m_valueTypeIsSet &&
         !m_valueIsSet;
}

DataElements::Type PowerTimeSlotValueDataElements::getDataType() const {
  return DataElements::Type::POWER_TIME_SLOT_VALUE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerTimeSlotValueDataElements::clone() const {
  return std::make_shared<PowerTimeSlotValueDataElements>(*this);
}

void PowerTimeSlotValueDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerTimeSlotValueDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerTimeSlotValueDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerTimeSlotValueDataElements::setSlotNumber() {
  m_slotNumberIsSet = true;
}

void PowerTimeSlotValueDataElements::cleanSlotNumber() {
  m_slotNumberIsSet = false;
}

bool PowerTimeSlotValueDataElements::getSlotNumberIsSet() const {
  return m_slotNumberIsSet;
}

void PowerTimeSlotValueDataElements::setValueType() { m_valueTypeIsSet = true; }

void PowerTimeSlotValueDataElements::cleanValueType() {
  m_valueTypeIsSet = false;
}

bool PowerTimeSlotValueDataElements::getValueTypeIsSet() const {
  return m_valueTypeIsSet;
}

void PowerTimeSlotValueDataElements::setValue(
    const ScaledNumberElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumberElements &PowerTimeSlotValueDataElements::getValue() const {
  return m_value;
}

void PowerTimeSlotValueDataElements::cleanValue() {
  m_value = ScaledNumberElements();
  m_valueIsSet = false;
}

bool PowerTimeSlotValueDataElements::getValueIsSet() const {
  return m_valueIsSet;
}

bool PowerTimeSlotValueDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "slotNumber", "valueType", "value"})) {
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
                                     "valueType")) {
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

std::string PowerTimeSlotValueDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_slotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotNumber");
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueType");
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram