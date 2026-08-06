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

#include <keo_datagram/bill/BillCost.h>

#include <keo_datagram/bill/BillCostElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillCost::BillCost()
    : m_costIdIsSet(false), m_costId(0), m_costTypeIsSet(false),
      m_costType(BillCostType()), m_valueIdIsSet(false), m_valueId(0),
      m_unitIsSet(false), m_unit(UnitOfMeasurement()), m_currencyIsSet(false),
      m_currency(Currency()), m_costIsSet(false), m_cost(ScaledNumber()),
      m_costPercentageIsSet(false), m_costPercentage(ScaledNumber())

{}

bool BillCost::operator==(const BillCost &c_classObject) const {
  if (m_costIdIsSet != c_classObject.m_costIdIsSet ||
      (m_costIdIsSet && (m_costId != c_classObject.m_costId))) {
    return false;
  }
  if (m_costTypeIsSet != c_classObject.m_costTypeIsSet ||
      (m_costTypeIsSet && (m_costType != c_classObject.m_costType))) {
    return false;
  }
  if (m_valueIdIsSet != c_classObject.m_valueIdIsSet ||
      (m_valueIdIsSet && (m_valueId != c_classObject.m_valueId))) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet ||
      (m_currencyIsSet && (m_currency != c_classObject.m_currency))) {
    return false;
  }
  if (m_costIsSet != c_classObject.m_costIsSet ||
      (m_costIsSet && (m_cost != c_classObject.m_cost))) {
    return false;
  }
  if (m_costPercentageIsSet != c_classObject.m_costPercentageIsSet ||
      (m_costPercentageIsSet &&
       (m_costPercentage != c_classObject.m_costPercentage))) {
    return false;
  }

  return true;
}

bool BillCost::operator!=(const BillCost &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillCost::isEmpty() const {
  return !m_costIdIsSet && !m_costTypeIsSet && !m_valueIdIsSet &&
         !m_unitIsSet && !m_currencyIsSet && !m_costIsSet &&
         !m_costPercentageIsSet;
}

void BillCost::setCostId(const xs_unsignedInt &costId) {
  m_costId = costId;
  m_costIdIsSet = true;
}

const xs_unsignedInt &BillCost::getCostId() const { return m_costId; }

void BillCost::cleanCostId() {
  m_costId = 0;
  m_costIdIsSet = false;
}

bool BillCost::getCostIdIsSet() const { return m_costIdIsSet; }

void BillCost::setCostType(const BillCostType &costType) {
  m_costType = costType;
  m_costTypeIsSet = true;
}

const BillCostType &BillCost::getCostType() const { return m_costType; }

void BillCost::cleanCostType() {
  m_costType = BillCostType();
  m_costTypeIsSet = false;
}

bool BillCost::getCostTypeIsSet() const { return m_costTypeIsSet; }

void BillCost::setValueId(const xs_unsignedInt &valueId) {
  m_valueId = valueId;
  m_valueIdIsSet = true;
}

const xs_unsignedInt &BillCost::getValueId() const { return m_valueId; }

void BillCost::cleanValueId() {
  m_valueId = 0;
  m_valueIdIsSet = false;
}

bool BillCost::getValueIdIsSet() const { return m_valueIdIsSet; }

void BillCost::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &BillCost::getUnit() const { return m_unit; }

void BillCost::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool BillCost::getUnitIsSet() const { return m_unitIsSet; }

void BillCost::setCurrency(const Currency &currency) {
  m_currency = currency;
  m_currencyIsSet = true;
}

const Currency &BillCost::getCurrency() const { return m_currency; }

void BillCost::cleanCurrency() {
  m_currency = Currency();
  m_currencyIsSet = false;
}

bool BillCost::getCurrencyIsSet() const { return m_currencyIsSet; }

void BillCost::setCost(const ScaledNumber &cost) {
  m_cost = cost;
  m_costIsSet = true;
}

const ScaledNumber &BillCost::getCost() const { return m_cost; }

void BillCost::cleanCost() {
  m_cost = ScaledNumber();
  m_costIsSet = false;
}

bool BillCost::getCostIsSet() const { return m_costIsSet; }

void BillCost::setCostPercentage(const ScaledNumber &costPercentage) {
  m_costPercentage = costPercentage;
  m_costPercentageIsSet = true;
}

const ScaledNumber &BillCost::getCostPercentage() const {
  return m_costPercentage;
}

void BillCost::cleanCostPercentage() {
  m_costPercentage = ScaledNumber();
  m_costPercentageIsSet = false;
}

bool BillCost::getCostPercentageIsSet() const { return m_costPercentageIsSet; }

BillCost BillCost::reduce(const BillCostElements &elements) const {
  BillCost dataOut;
  if (getCostIdIsSet() && elements.getCostIdIsSet()) {
    dataOut.setCostId(getCostId());
  }
  if (getCostTypeIsSet() && elements.getCostTypeIsSet()) {
    dataOut.setCostType(getCostType());
  }
  if (getValueIdIsSet() && elements.getValueIdIsSet()) {
    dataOut.setValueId(getValueId());
  }
  if (getUnitIsSet() && elements.getUnitIsSet()) {
    dataOut.setUnit(getUnit());
  }
  if (getCurrencyIsSet() && elements.getCurrencyIsSet()) {
    dataOut.setCurrency(getCurrency());
  }
  if (getCostIsSet() && elements.getCostIsSet()) {
    dataOut.setCost(getCost().reduce(elements.getCost()));
  }
  if (getCostPercentageIsSet() && elements.getCostPercentageIsSet()) {
    dataOut.setCostPercentage(
        getCostPercentage().reduce(elements.getCostPercentage()));
  }
  return dataOut;
}

bool BillCost::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"costId", "costType", "valueId", "unit", "currency", "cost",
                   "costPercentage"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "costId", &m_costId)) {
      m_costIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "costType", &m_costType)) {
      m_costTypeIsSet = true;
      ++iter;
    }
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
                                   "currency", &m_currency)) {
      m_currencyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "cost", &m_cost)) {
      m_costIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "costPercentage", &m_costPercentage)) {
      m_costPercentageIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillCost::toJson() const {
  std::string result = "[";
  if (m_costIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("costId", m_costId);
  }
  if (m_costTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("costType", m_costType);
  }
  if (m_valueIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueId", m_valueId);
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("currency", m_currency);
  }
  if (m_costIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("cost", m_cost);
  }
  if (m_costPercentageIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("costPercentage", m_costPercentage);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram