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

#include <keo_datagram/incentivetable/IncentiveTableConstraints.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableConstraints::IncentiveTableConstraints()
    : m_tariffIsSet(false), m_tariff(TariffData()),
      m_tariffConstraintsIsSet(false),
      m_tariffConstraints(TariffOverallConstraintsData()),
      m_incentiveSlotConstraintsIsSet(false),
      m_incentiveSlotConstraints(TimeTableConstraintsData())

{}

IncentiveTableConstraints::IncentiveTableConstraints(
    const TariffData &c_tariff,
    const TariffOverallConstraintsData &c_tariffConstraints,
    const TimeTableConstraintsData &c_incentiveSlotConstraints)
    : m_tariffIsSet(true), m_tariff(c_tariff), m_tariffConstraintsIsSet(true),
      m_tariffConstraints(c_tariffConstraints),
      m_incentiveSlotConstraintsIsSet(true),
      m_incentiveSlotConstraints(c_incentiveSlotConstraints)

{}

bool IncentiveTableConstraints::
operator==(const IncentiveTableConstraints &c_classObject) const {
  if (m_tariffIsSet != c_classObject.m_tariffIsSet ||
      (m_tariffIsSet && (m_tariff != c_classObject.m_tariff))) {
    return false;
  }
  if (m_tariffConstraintsIsSet != c_classObject.m_tariffConstraintsIsSet ||
      (m_tariffConstraintsIsSet &&
       (m_tariffConstraints != c_classObject.m_tariffConstraints))) {
    return false;
  }
  if (m_incentiveSlotConstraintsIsSet !=
          c_classObject.m_incentiveSlotConstraintsIsSet ||
      (m_incentiveSlotConstraintsIsSet &&
       (m_incentiveSlotConstraints !=
        c_classObject.m_incentiveSlotConstraints))) {
    return false;
  }

  return true;
}

bool IncentiveTableConstraints::
operator!=(const IncentiveTableConstraints &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableConstraints::isEmpty() const {
  return !m_tariffIsSet && !m_tariffConstraintsIsSet &&
         !m_incentiveSlotConstraintsIsSet;
}

void IncentiveTableConstraints::setTariff(const TariffData &tariff) {
  m_tariff = tariff;
  m_tariffIsSet = true;
}

const TariffData &IncentiveTableConstraints::getTariff() const {
  return m_tariff;
}

void IncentiveTableConstraints::cleanTariff() {
  m_tariff = TariffData();
  m_tariffIsSet = false;
}

bool IncentiveTableConstraints::getTariffIsSet() const { return m_tariffIsSet; }

void IncentiveTableConstraints::setTariffConstraints(
    const TariffOverallConstraintsData &tariffConstraints) {
  m_tariffConstraints = tariffConstraints;
  m_tariffConstraintsIsSet = true;
}

const TariffOverallConstraintsData &
IncentiveTableConstraints::getTariffConstraints() const {
  return m_tariffConstraints;
}

void IncentiveTableConstraints::cleanTariffConstraints() {
  m_tariffConstraints = TariffOverallConstraintsData();
  m_tariffConstraintsIsSet = false;
}

bool IncentiveTableConstraints::getTariffConstraintsIsSet() const {
  return m_tariffConstraintsIsSet;
}

void IncentiveTableConstraints::setIncentiveSlotConstraints(
    const TimeTableConstraintsData &incentiveSlotConstraints) {
  m_incentiveSlotConstraints = incentiveSlotConstraints;
  m_incentiveSlotConstraintsIsSet = true;
}

const TimeTableConstraintsData &
IncentiveTableConstraints::getIncentiveSlotConstraints() const {
  return m_incentiveSlotConstraints;
}

void IncentiveTableConstraints::cleanIncentiveSlotConstraints() {
  m_incentiveSlotConstraints = TimeTableConstraintsData();
  m_incentiveSlotConstraintsIsSet = false;
}

bool IncentiveTableConstraints::getIncentiveSlotConstraintsIsSet() const {
  return m_incentiveSlotConstraintsIsSet;
}

bool IncentiveTableConstraints::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"tariff", "tariffConstraints", "incentiveSlotConstraints"})) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariffConstraints", &m_tariffConstraints)) {
      m_tariffConstraintsIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveSlotConstraints",
                                   &m_incentiveSlotConstraints)) {
      m_incentiveSlotConstraintsIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableConstraints::toJson() const {
  std::string result = "[";
  if (m_tariffIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariff", m_tariff);
  }
  if (m_tariffConstraintsIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("tariffConstraints", m_tariffConstraints);
  }
  if (m_incentiveSlotConstraintsIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveSlotConstraints",
                                           m_incentiveSlotConstraints);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram