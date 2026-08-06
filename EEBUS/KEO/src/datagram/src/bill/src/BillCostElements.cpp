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

#include <keo_datagram/bill/BillCostElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillCostElements::BillCostElements()
    : m_costIdIsSet(false), m_costTypeIsSet(false), m_valueIdIsSet(false),
      m_unitIsSet(false), m_currencyIsSet(false), m_costIsSet(false),
      m_cost(ScaledNumberElements()), m_costPercentageIsSet(false),
      m_costPercentage(ScaledNumberElements())

{}

bool BillCostElements::operator==(const BillCostElements &c_classObject) const {
  if (m_costIdIsSet != c_classObject.m_costIdIsSet) {
    return false;
  }
  if (m_costTypeIsSet != c_classObject.m_costTypeIsSet) {
    return false;
  }
  if (m_valueIdIsSet != c_classObject.m_valueIdIsSet) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet) {
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

bool BillCostElements::operator!=(const BillCostElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillCostElements::isEmpty() const {
  return !m_costIdIsSet && !m_costTypeIsSet && !m_valueIdIsSet &&
         !m_unitIsSet && !m_currencyIsSet && !m_costIsSet &&
         !m_costPercentageIsSet;
}

void BillCostElements::setCostId() { m_costIdIsSet = true; }

void BillCostElements::cleanCostId() { m_costIdIsSet = false; }

bool BillCostElements::getCostIdIsSet() const { return m_costIdIsSet; }

void BillCostElements::setCostType() { m_costTypeIsSet = true; }

void BillCostElements::cleanCostType() { m_costTypeIsSet = false; }

bool BillCostElements::getCostTypeIsSet() const { return m_costTypeIsSet; }

void BillCostElements::setValueId() { m_valueIdIsSet = true; }

void BillCostElements::cleanValueId() { m_valueIdIsSet = false; }

bool BillCostElements::getValueIdIsSet() const { return m_valueIdIsSet; }

void BillCostElements::setUnit() { m_unitIsSet = true; }

void BillCostElements::cleanUnit() { m_unitIsSet = false; }

bool BillCostElements::getUnitIsSet() const { return m_unitIsSet; }

void BillCostElements::setCurrency() { m_currencyIsSet = true; }

void BillCostElements::cleanCurrency() { m_currencyIsSet = false; }

bool BillCostElements::getCurrencyIsSet() const { return m_currencyIsSet; }

void BillCostElements::setCost(const ScaledNumberElements &cost) {
  m_cost = cost;
  m_costIsSet = true;
}

const ScaledNumberElements &BillCostElements::getCost() const { return m_cost; }

void BillCostElements::cleanCost() {
  m_cost = ScaledNumberElements();
  m_costIsSet = false;
}

bool BillCostElements::getCostIsSet() const { return m_costIsSet; }

void BillCostElements::setCostPercentage(
    const ScaledNumberElements &costPercentage) {
  m_costPercentage = costPercentage;
  m_costPercentageIsSet = true;
}

const ScaledNumberElements &BillCostElements::getCostPercentage() const {
  return m_costPercentage;
}

void BillCostElements::cleanCostPercentage() {
  m_costPercentage = ScaledNumberElements();
  m_costPercentageIsSet = false;
}

bool BillCostElements::getCostPercentageIsSet() const {
  return m_costPercentageIsSet;
}

bool BillCostElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"costId", "costType", "valueId", "unit", "currency", "cost",
                   "costPercentage"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "costId")) {
      m_costIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "costType")) {
      m_costTypeIsSet = true;
      ++iter;
    }
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "currency")) {
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

std::string BillCostElements::toJson() const {
  std::string result = "[";
  if (m_costIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("costId");
  }
  if (m_costTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("costType");
  }
  if (m_valueIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueId");
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("unit");
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("currency");
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