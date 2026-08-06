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

#include <keo_datagram/incentivetable/TariffOverallConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffOverallConstraintsDataElements::TariffOverallConstraintsDataElements()
    : DataElements(), m_maxTariffCountIsSet(false),
      m_maxBoundaryCountIsSet(false), m_maxTierCountIsSet(false),
      m_maxIncentiveCountIsSet(false), m_maxBoundariesPerTariffIsSet(false),
      m_maxTiersPerTariffIsSet(false), m_maxBoundariesPerTierIsSet(false),
      m_maxIncentivesPerTierIsSet(false)

{}

bool TariffOverallConstraintsDataElements::
operator==(const TariffOverallConstraintsDataElements &c_classObject) const {
  if (m_maxTariffCountIsSet != c_classObject.m_maxTariffCountIsSet) {
    return false;
  }
  if (m_maxBoundaryCountIsSet != c_classObject.m_maxBoundaryCountIsSet) {
    return false;
  }
  if (m_maxTierCountIsSet != c_classObject.m_maxTierCountIsSet) {
    return false;
  }
  if (m_maxIncentiveCountIsSet != c_classObject.m_maxIncentiveCountIsSet) {
    return false;
  }
  if (m_maxBoundariesPerTariffIsSet !=
      c_classObject.m_maxBoundariesPerTariffIsSet) {
    return false;
  }
  if (m_maxTiersPerTariffIsSet != c_classObject.m_maxTiersPerTariffIsSet) {
    return false;
  }
  if (m_maxBoundariesPerTierIsSet !=
      c_classObject.m_maxBoundariesPerTierIsSet) {
    return false;
  }
  if (m_maxIncentivesPerTierIsSet !=
      c_classObject.m_maxIncentivesPerTierIsSet) {
    return false;
  }

  return true;
}

bool TariffOverallConstraintsDataElements::
operator!=(const TariffOverallConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffOverallConstraintsDataElements::isEmpty() const {
  return !m_maxTariffCountIsSet && !m_maxBoundaryCountIsSet &&
         !m_maxTierCountIsSet && !m_maxIncentiveCountIsSet &&
         !m_maxBoundariesPerTariffIsSet && !m_maxTiersPerTariffIsSet &&
         !m_maxBoundariesPerTierIsSet && !m_maxIncentivesPerTierIsSet;
}

DataElements::Type TariffOverallConstraintsDataElements::getDataType() const {
  return DataElements::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TariffOverallConstraintsDataElements::clone() const {
  return std::make_shared<TariffOverallConstraintsDataElements>(*this);
}

void TariffOverallConstraintsDataElements::setMaxTariffCount() {
  m_maxTariffCountIsSet = true;
}

void TariffOverallConstraintsDataElements::cleanMaxTariffCount() {
  m_maxTariffCountIsSet = false;
}

bool TariffOverallConstraintsDataElements::getMaxTariffCountIsSet() const {
  return m_maxTariffCountIsSet;
}

void TariffOverallConstraintsDataElements::setMaxBoundaryCount() {
  m_maxBoundaryCountIsSet = true;
}

void TariffOverallConstraintsDataElements::cleanMaxBoundaryCount() {
  m_maxBoundaryCountIsSet = false;
}

bool TariffOverallConstraintsDataElements::getMaxBoundaryCountIsSet() const {
  return m_maxBoundaryCountIsSet;
}

void TariffOverallConstraintsDataElements::setMaxTierCount() {
  m_maxTierCountIsSet = true;
}

void TariffOverallConstraintsDataElements::cleanMaxTierCount() {
  m_maxTierCountIsSet = false;
}

bool TariffOverallConstraintsDataElements::getMaxTierCountIsSet() const {
  return m_maxTierCountIsSet;
}

void TariffOverallConstraintsDataElements::setMaxIncentiveCount() {
  m_maxIncentiveCountIsSet = true;
}

void TariffOverallConstraintsDataElements::cleanMaxIncentiveCount() {
  m_maxIncentiveCountIsSet = false;
}

bool TariffOverallConstraintsDataElements::getMaxIncentiveCountIsSet() const {
  return m_maxIncentiveCountIsSet;
}

void TariffOverallConstraintsDataElements::setMaxBoundariesPerTariff() {
  m_maxBoundariesPerTariffIsSet = true;
}

void TariffOverallConstraintsDataElements::cleanMaxBoundariesPerTariff() {
  m_maxBoundariesPerTariffIsSet = false;
}

bool TariffOverallConstraintsDataElements::getMaxBoundariesPerTariffIsSet()
    const {
  return m_maxBoundariesPerTariffIsSet;
}

void TariffOverallConstraintsDataElements::setMaxTiersPerTariff() {
  m_maxTiersPerTariffIsSet = true;
}

void TariffOverallConstraintsDataElements::cleanMaxTiersPerTariff() {
  m_maxTiersPerTariffIsSet = false;
}

bool TariffOverallConstraintsDataElements::getMaxTiersPerTariffIsSet() const {
  return m_maxTiersPerTariffIsSet;
}

void TariffOverallConstraintsDataElements::setMaxBoundariesPerTier() {
  m_maxBoundariesPerTierIsSet = true;
}

void TariffOverallConstraintsDataElements::cleanMaxBoundariesPerTier() {
  m_maxBoundariesPerTierIsSet = false;
}

bool TariffOverallConstraintsDataElements::getMaxBoundariesPerTierIsSet()
    const {
  return m_maxBoundariesPerTierIsSet;
}

void TariffOverallConstraintsDataElements::setMaxIncentivesPerTier() {
  m_maxIncentivesPerTierIsSet = true;
}

void TariffOverallConstraintsDataElements::cleanMaxIncentivesPerTier() {
  m_maxIncentivesPerTierIsSet = false;
}

bool TariffOverallConstraintsDataElements::getMaxIncentivesPerTierIsSet()
    const {
  return m_maxIncentivesPerTierIsSet;
}

bool TariffOverallConstraintsDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"maxTariffCount", "maxBoundaryCount", "maxTierCount",
             "maxIncentiveCount", "maxBoundariesPerTariff", "maxTiersPerTariff",
             "maxBoundariesPerTier", "maxIncentivesPerTier"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxTariffCount")) {
      m_maxTariffCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxBoundaryCount")) {
      m_maxBoundaryCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxTierCount")) {
      m_maxTierCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxIncentiveCount")) {
      m_maxIncentiveCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxBoundariesPerTariff")) {
      m_maxBoundariesPerTariffIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxTiersPerTariff")) {
      m_maxTiersPerTariffIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxBoundariesPerTier")) {
      m_maxBoundariesPerTierIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "maxIncentivesPerTier")) {
      m_maxIncentivesPerTierIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffOverallConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_maxTariffCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxTariffCount");
  }
  if (m_maxBoundaryCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxBoundaryCount");
  }
  if (m_maxTierCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxTierCount");
  }
  if (m_maxIncentiveCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxIncentiveCount");
  }
  if (m_maxBoundariesPerTariffIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxBoundariesPerTariff");
  }
  if (m_maxTiersPerTariffIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxTiersPerTariff");
  }
  if (m_maxBoundariesPerTierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxBoundariesPerTier");
  }
  if (m_maxIncentivesPerTierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("maxIncentivesPerTier");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram