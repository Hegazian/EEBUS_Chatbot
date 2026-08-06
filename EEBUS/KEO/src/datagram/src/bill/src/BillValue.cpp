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

#include <keo_datagram/bill/BillValue.h>

#include <keo_datagram/bill/BillValueElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillValue::BillValue()
    : m_valueIdIsSet(false), m_valueId(0), m_unitIsSet(false),
      m_unit(UnitOfMeasurement()), m_valueIsSet(false), m_value(ScaledNumber()),
      m_valuePercentageIsSet(false), m_valuePercentage(ScaledNumber())

{}

bool BillValue::operator==(const BillValue &c_classObject) const {
  if (m_valueIdIsSet != c_classObject.m_valueIdIsSet ||
      (m_valueIdIsSet && (m_valueId != c_classObject.m_valueId))) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }
  if (m_valuePercentageIsSet != c_classObject.m_valuePercentageIsSet ||
      (m_valuePercentageIsSet &&
       (m_valuePercentage != c_classObject.m_valuePercentage))) {
    return false;
  }

  return true;
}

bool BillValue::operator!=(const BillValue &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillValue::isEmpty() const {
  return !m_valueIdIsSet && !m_unitIsSet && !m_valueIsSet &&
         !m_valuePercentageIsSet;
}

void BillValue::setValueId(const xs_unsignedInt &valueId) {
  m_valueId = valueId;
  m_valueIdIsSet = true;
}

const xs_unsignedInt &BillValue::getValueId() const { return m_valueId; }

void BillValue::cleanValueId() {
  m_valueId = 0;
  m_valueIdIsSet = false;
}

bool BillValue::getValueIdIsSet() const { return m_valueIdIsSet; }

void BillValue::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &BillValue::getUnit() const { return m_unit; }

void BillValue::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool BillValue::getUnitIsSet() const { return m_unitIsSet; }

void BillValue::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &BillValue::getValue() const { return m_value; }

void BillValue::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool BillValue::getValueIsSet() const { return m_valueIsSet; }

void BillValue::setValuePercentage(const ScaledNumber &valuePercentage) {
  m_valuePercentage = valuePercentage;
  m_valuePercentageIsSet = true;
}

const ScaledNumber &BillValue::getValuePercentage() const {
  return m_valuePercentage;
}

void BillValue::cleanValuePercentage() {
  m_valuePercentage = ScaledNumber();
  m_valuePercentageIsSet = false;
}

bool BillValue::getValuePercentageIsSet() const {
  return m_valuePercentageIsSet;
}

BillValue BillValue::reduce(const BillValueElements &elements) const {
  BillValue dataOut;
  if (getValueIdIsSet() && elements.getValueIdIsSet()) {
    dataOut.setValueId(getValueId());
  }
  if (getUnitIsSet() && elements.getUnitIsSet()) {
    dataOut.setUnit(getUnit());
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    dataOut.setValue(getValue().reduce(elements.getValue()));
  }
  if (getValuePercentageIsSet() && elements.getValuePercentageIsSet()) {
    dataOut.setValuePercentage(
        getValuePercentage().reduce(elements.getValuePercentage()));
  }
  return dataOut;
}

bool BillValue::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"valueId", "unit", "value", "valuePercentage"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueId", &m_valueId)) {
      m_valueIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "unit", &m_unit)) {
      m_unitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valuePercentage", &m_valuePercentage)) {
      m_valuePercentageIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillValue::toJson() const {
  std::string result = "[";
  if (m_valueIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueId", m_valueId);
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  if (m_valuePercentageIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("valuePercentage", m_valuePercentage);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram