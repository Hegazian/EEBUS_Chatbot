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

#include <keo_datagram/incentivetable/IncentiveTableDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableDataSelectors::IncentiveTableDataSelectors()
    : DataSelectors(), m_tariffIsSet(false), m_tariff(TariffListDataSelectors())

{}

IncentiveTableDataSelectors::IncentiveTableDataSelectors(
    const TariffListDataSelectors &c_tariff) {
  setTariff(c_tariff);
}

bool IncentiveTableDataSelectors::
operator==(const IncentiveTableDataSelectors &c_classObject) const {
  if (m_tariffIsSet != c_classObject.m_tariffIsSet ||
      (m_tariffIsSet && (m_tariff != c_classObject.m_tariff))) {
    return false;
  }

  return true;
}

bool IncentiveTableDataSelectors::
operator!=(const IncentiveTableDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableDataSelectors::isEmpty() const { return !m_tariffIsSet; }

DataSelectors::Type IncentiveTableDataSelectors::getDataType() const {
  return DataSelectors::Type::INCENTIVE_TABLE_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr IncentiveTableDataSelectors::clone() const {
  return std::make_shared<IncentiveTableDataSelectors>(*this);
}

void IncentiveTableDataSelectors::setTariff(
    const TariffListDataSelectors &tariff) {
  m_tariff = tariff;
  m_tariffIsSet = true;
}

const TariffListDataSelectors &IncentiveTableDataSelectors::getTariff() const {
  return m_tariff;
}

void IncentiveTableDataSelectors::cleanTariff() {
  m_tariff = TariffListDataSelectors();
  m_tariffIsSet = false;
}

bool IncentiveTableDataSelectors::getTariffIsSet() const {
  return m_tariffIsSet;
}

bool IncentiveTableDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tariff"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariff", &m_tariff)) {
      m_tariffIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tariffIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariff", m_tariff);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram