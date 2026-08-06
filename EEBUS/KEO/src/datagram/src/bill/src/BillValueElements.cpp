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

#include <keo_datagram/bill/BillValueElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillValueElements::BillValueElements()
    : m_valueIdIsSet(false), m_unitIsSet(false), m_valueIsSet(false),
      m_value(ScaledNumberElements()), m_valuePercentageIsSet(false),
      m_valuePercentage(ScaledNumberElements())

{}

bool BillValueElements::
operator==(const BillValueElements &c_classObject) const {
  if (m_valueIdIsSet != c_classObject.m_valueIdIsSet) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet) {
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

bool BillValueElements::
operator!=(const BillValueElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillValueElements::isEmpty() const {
  return !m_valueIdIsSet && !m_unitIsSet && !m_valueIsSet &&
         !m_valuePercentageIsSet;
}

void BillValueElements::setValueId() { m_valueIdIsSet = true; }

void BillValueElements::cleanValueId() { m_valueIdIsSet = false; }

bool BillValueElements::getValueIdIsSet() const { return m_valueIdIsSet; }

void BillValueElements::setUnit() { m_unitIsSet = true; }

void BillValueElements::cleanUnit() { m_unitIsSet = false; }

bool BillValueElements::getUnitIsSet() const { return m_unitIsSet; }

void BillValueElements::setValue(const ScaledNumberElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumberElements &BillValueElements::getValue() const {
  return m_value;
}

void BillValueElements::cleanValue() {
  m_value = ScaledNumberElements();
  m_valueIsSet = false;
}

bool BillValueElements::getValueIsSet() const { return m_valueIsSet; }

void BillValueElements::setValuePercentage(
    const ScaledNumberElements &valuePercentage) {
  m_valuePercentage = valuePercentage;
  m_valuePercentageIsSet = true;
}

const ScaledNumberElements &BillValueElements::getValuePercentage() const {
  return m_valuePercentage;
}

void BillValueElements::cleanValuePercentage() {
  m_valuePercentage = ScaledNumberElements();
  m_valuePercentageIsSet = false;
}

bool BillValueElements::getValuePercentageIsSet() const {
  return m_valuePercentageIsSet;
}

bool BillValueElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"valueId", "unit", "value", "valuePercentage"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "valueId")) {
      m_valueIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "unit")) {
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

std::string BillValueElements::toJson() const {
  std::string result = "[";
  if (m_valueIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueId");
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("unit");
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