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

#include <keo_datagram/incentivetable/IncentiveTable.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTable::IncentiveTable()
    : m_tariffIsSet(false), m_tariff(TariffData()), m_incentiveSlotIsSet(false),
      m_incentiveSlot(std::vector<IncentiveTableIncentiveSlot>())

{}

IncentiveTable::IncentiveTable(
    const TariffData &c_tariff,
    const std::vector<IncentiveTableIncentiveSlot> &c_incentiveSlot)
    : m_tariffIsSet(true), m_tariff(c_tariff), m_incentiveSlotIsSet(true),
      m_incentiveSlot(c_incentiveSlot)

{}

bool IncentiveTable::operator==(const IncentiveTable &c_classObject) const {
  if (m_tariffIsSet != c_classObject.m_tariffIsSet ||
      (m_tariffIsSet && (m_tariff != c_classObject.m_tariff))) {
    return false;
  }
  if (m_incentiveSlotIsSet != c_classObject.m_incentiveSlotIsSet ||
      (m_incentiveSlotIsSet &&
       (m_incentiveSlot != c_classObject.m_incentiveSlot))) {
    return false;
  }

  return true;
}

bool IncentiveTable::operator!=(const IncentiveTable &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTable::isEmpty() const {
  return !m_tariffIsSet && !m_incentiveSlotIsSet;
}

void IncentiveTable::setTariff(const TariffData &tariff) {
  m_tariff = tariff;
  m_tariffIsSet = true;
}

const TariffData &IncentiveTable::getTariff() const { return m_tariff; }

void IncentiveTable::cleanTariff() {
  m_tariff = TariffData();
  m_tariffIsSet = false;
}

bool IncentiveTable::getTariffIsSet() const { return m_tariffIsSet; }

void IncentiveTable::setIncentiveSlot(
    const std::vector<IncentiveTableIncentiveSlot> &incentiveSlot) {
  m_incentiveSlot = incentiveSlot;
  m_incentiveSlotIsSet = true;
}

const std::vector<IncentiveTableIncentiveSlot> &
IncentiveTable::getIncentiveSlot() const {
  return m_incentiveSlot;
}

void IncentiveTable::cleanIncentiveSlot() {
  m_incentiveSlot.clear();
  m_incentiveSlotIsSet = false;
}

bool IncentiveTable::getIncentiveSlotIsSet() const {
  return m_incentiveSlotIsSet;
}

bool IncentiveTable::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tariff", "incentiveSlot"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariff", &m_tariff)) {
      m_tariffIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<IncentiveTableIncentiveSlot>(
            static_cast<KeoJsonValue *>(&(*iter)), "incentiveSlot",
            &m_incentiveSlot)) {
      m_incentiveSlotIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTable::toJson() const {
  std::string result = "[";
  if (m_tariffIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariff", m_tariff);
  }
  if (m_incentiveSlotIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<IncentiveTableIncentiveSlot>(
        "incentiveSlot", m_incentiveSlot);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram