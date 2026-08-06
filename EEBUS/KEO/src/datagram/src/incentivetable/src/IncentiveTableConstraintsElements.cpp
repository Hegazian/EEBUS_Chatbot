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

#include <keo_datagram/incentivetable/IncentiveTableConstraintsElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableConstraintsElements::IncentiveTableConstraintsElements()
    : m_tariffIsSet(false), m_tariff(TariffDataElements()),
      m_tariffConstraintsIsSet(false),
      m_tariffConstraints(TariffOverallConstraintsDataElements()),
      m_incentiveSlotConstraintsIsSet(false),
      m_incentiveSlotConstraints(TimeTableConstraintsDataElements())

{}

IncentiveTableConstraintsElements::IncentiveTableConstraintsElements(
    const TariffDataElements &c_tariff,
    const TariffOverallConstraintsDataElements &c_tariffConstraints,
    const TimeTableConstraintsDataElements &c_incentiveSlotConstraints)
    : m_tariffIsSet(true), m_tariff(c_tariff), m_tariffConstraintsIsSet(true),
      m_tariffConstraints(c_tariffConstraints),
      m_incentiveSlotConstraintsIsSet(true),
      m_incentiveSlotConstraints(c_incentiveSlotConstraints)

{}

bool IncentiveTableConstraintsElements::
operator==(const IncentiveTableConstraintsElements &c_classObject) const {
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

bool IncentiveTableConstraintsElements::
operator!=(const IncentiveTableConstraintsElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableConstraintsElements::isEmpty() const {
  return !m_tariffIsSet && !m_tariffConstraintsIsSet &&
         !m_incentiveSlotConstraintsIsSet;
}

void IncentiveTableConstraintsElements::setTariff(
    const TariffDataElements &tariff) {
  m_tariff = tariff;
  m_tariffIsSet = true;
}

const TariffDataElements &IncentiveTableConstraintsElements::getTariff() const {
  return m_tariff;
}

void IncentiveTableConstraintsElements::cleanTariff() {
  m_tariff = TariffDataElements();
  m_tariffIsSet = false;
}

bool IncentiveTableConstraintsElements::getTariffIsSet() const {
  return m_tariffIsSet;
}

void IncentiveTableConstraintsElements::setTariffConstraints(
    const TariffOverallConstraintsDataElements &tariffConstraints) {
  m_tariffConstraints = tariffConstraints;
  m_tariffConstraintsIsSet = true;
}

const TariffOverallConstraintsDataElements &
IncentiveTableConstraintsElements::getTariffConstraints() const {
  return m_tariffConstraints;
}

void IncentiveTableConstraintsElements::cleanTariffConstraints() {
  m_tariffConstraints = TariffOverallConstraintsDataElements();
  m_tariffConstraintsIsSet = false;
}

bool IncentiveTableConstraintsElements::getTariffConstraintsIsSet() const {
  return m_tariffConstraintsIsSet;
}

void IncentiveTableConstraintsElements::setIncentiveSlotConstraints(
    const TimeTableConstraintsDataElements &incentiveSlotConstraints) {
  m_incentiveSlotConstraints = incentiveSlotConstraints;
  m_incentiveSlotConstraintsIsSet = true;
}

const TimeTableConstraintsDataElements &
IncentiveTableConstraintsElements::getIncentiveSlotConstraints() const {
  return m_incentiveSlotConstraints;
}

void IncentiveTableConstraintsElements::cleanIncentiveSlotConstraints() {
  m_incentiveSlotConstraints = TimeTableConstraintsDataElements();
  m_incentiveSlotConstraintsIsSet = false;
}

bool IncentiveTableConstraintsElements::getIncentiveSlotConstraintsIsSet()
    const {
  return m_incentiveSlotConstraintsIsSet;
}

bool IncentiveTableConstraintsElements::fromJson(KeoJsonValue *json) {
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

std::string IncentiveTableConstraintsElements::toJson() const {
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