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

#include <keo_datagram/incentivetable/TariffOverallConstraintsData.h>

#include <keo_datagram/incentivetable/TariffOverallConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffOverallConstraintsData::TariffOverallConstraintsData()
    : CmdData(), m_maxTariffCountIsSet(false), m_maxTariffCount(0),
      m_maxBoundaryCountIsSet(false), m_maxBoundaryCount(0),
      m_maxTierCountIsSet(false), m_maxTierCount(0),
      m_maxIncentiveCountIsSet(false), m_maxIncentiveCount(0),
      m_maxBoundariesPerTariffIsSet(false), m_maxBoundariesPerTariff(0),
      m_maxTiersPerTariffIsSet(false), m_maxTiersPerTariff(0),
      m_maxBoundariesPerTierIsSet(false), m_maxBoundariesPerTier(0),
      m_maxIncentivesPerTierIsSet(false), m_maxIncentivesPerTier(0)

{}

bool TariffOverallConstraintsData::
operator==(const TariffOverallConstraintsData &c_classObject) const {
  if (m_maxTariffCountIsSet != c_classObject.m_maxTariffCountIsSet ||
      (m_maxTariffCountIsSet &&
       (m_maxTariffCount != c_classObject.m_maxTariffCount))) {
    return false;
  }
  if (m_maxBoundaryCountIsSet != c_classObject.m_maxBoundaryCountIsSet ||
      (m_maxBoundaryCountIsSet &&
       (m_maxBoundaryCount != c_classObject.m_maxBoundaryCount))) {
    return false;
  }
  if (m_maxTierCountIsSet != c_classObject.m_maxTierCountIsSet ||
      (m_maxTierCountIsSet &&
       (m_maxTierCount != c_classObject.m_maxTierCount))) {
    return false;
  }
  if (m_maxIncentiveCountIsSet != c_classObject.m_maxIncentiveCountIsSet ||
      (m_maxIncentiveCountIsSet &&
       (m_maxIncentiveCount != c_classObject.m_maxIncentiveCount))) {
    return false;
  }
  if (m_maxBoundariesPerTariffIsSet !=
          c_classObject.m_maxBoundariesPerTariffIsSet ||
      (m_maxBoundariesPerTariffIsSet &&
       (m_maxBoundariesPerTariff != c_classObject.m_maxBoundariesPerTariff))) {
    return false;
  }
  if (m_maxTiersPerTariffIsSet != c_classObject.m_maxTiersPerTariffIsSet ||
      (m_maxTiersPerTariffIsSet &&
       (m_maxTiersPerTariff != c_classObject.m_maxTiersPerTariff))) {
    return false;
  }
  if (m_maxBoundariesPerTierIsSet !=
          c_classObject.m_maxBoundariesPerTierIsSet ||
      (m_maxBoundariesPerTierIsSet &&
       (m_maxBoundariesPerTier != c_classObject.m_maxBoundariesPerTier))) {
    return false;
  }
  if (m_maxIncentivesPerTierIsSet !=
          c_classObject.m_maxIncentivesPerTierIsSet ||
      (m_maxIncentivesPerTierIsSet &&
       (m_maxIncentivesPerTier != c_classObject.m_maxIncentivesPerTier))) {
    return false;
  }

  return true;
}

bool TariffOverallConstraintsData::
operator!=(const TariffOverallConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffOverallConstraintsData::isEmpty() const {
  return !m_maxTariffCountIsSet && !m_maxBoundaryCountIsSet &&
         !m_maxTierCountIsSet && !m_maxIncentiveCountIsSet &&
         !m_maxBoundariesPerTariffIsSet && !m_maxTiersPerTariffIsSet &&
         !m_maxBoundariesPerTierIsSet && !m_maxIncentivesPerTierIsSet;
}

CmdData::Type TariffOverallConstraintsData::getDataType() const {
  return CmdData::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_TYPE;
}

CmdDataPtr TariffOverallConstraintsData::clone() const {
  return std::make_shared<TariffOverallConstraintsData>(*this);
}

void TariffOverallConstraintsData::setMaxTariffCount(
    const xs_unsignedInt &maxTariffCount) {
  m_maxTariffCount = maxTariffCount;
  m_maxTariffCountIsSet = true;
}

const xs_unsignedInt &TariffOverallConstraintsData::getMaxTariffCount() const {
  return m_maxTariffCount;
}

void TariffOverallConstraintsData::cleanMaxTariffCount() {
  m_maxTariffCount = 0;
  m_maxTariffCountIsSet = false;
}

bool TariffOverallConstraintsData::getMaxTariffCountIsSet() const {
  return m_maxTariffCountIsSet;
}

void TariffOverallConstraintsData::setMaxBoundaryCount(
    const xs_unsignedInt &maxBoundaryCount) {
  m_maxBoundaryCount = maxBoundaryCount;
  m_maxBoundaryCountIsSet = true;
}

const xs_unsignedInt &
TariffOverallConstraintsData::getMaxBoundaryCount() const {
  return m_maxBoundaryCount;
}

void TariffOverallConstraintsData::cleanMaxBoundaryCount() {
  m_maxBoundaryCount = 0;
  m_maxBoundaryCountIsSet = false;
}

bool TariffOverallConstraintsData::getMaxBoundaryCountIsSet() const {
  return m_maxBoundaryCountIsSet;
}

void TariffOverallConstraintsData::setMaxTierCount(
    const xs_unsignedInt &maxTierCount) {
  m_maxTierCount = maxTierCount;
  m_maxTierCountIsSet = true;
}

const xs_unsignedInt &TariffOverallConstraintsData::getMaxTierCount() const {
  return m_maxTierCount;
}

void TariffOverallConstraintsData::cleanMaxTierCount() {
  m_maxTierCount = 0;
  m_maxTierCountIsSet = false;
}

bool TariffOverallConstraintsData::getMaxTierCountIsSet() const {
  return m_maxTierCountIsSet;
}

void TariffOverallConstraintsData::setMaxIncentiveCount(
    const xs_unsignedInt &maxIncentiveCount) {
  m_maxIncentiveCount = maxIncentiveCount;
  m_maxIncentiveCountIsSet = true;
}

const xs_unsignedInt &
TariffOverallConstraintsData::getMaxIncentiveCount() const {
  return m_maxIncentiveCount;
}

void TariffOverallConstraintsData::cleanMaxIncentiveCount() {
  m_maxIncentiveCount = 0;
  m_maxIncentiveCountIsSet = false;
}

bool TariffOverallConstraintsData::getMaxIncentiveCountIsSet() const {
  return m_maxIncentiveCountIsSet;
}

void TariffOverallConstraintsData::setMaxBoundariesPerTariff(
    const xs_unsignedInt &maxBoundariesPerTariff) {
  m_maxBoundariesPerTariff = maxBoundariesPerTariff;
  m_maxBoundariesPerTariffIsSet = true;
}

const xs_unsignedInt &
TariffOverallConstraintsData::getMaxBoundariesPerTariff() const {
  return m_maxBoundariesPerTariff;
}

void TariffOverallConstraintsData::cleanMaxBoundariesPerTariff() {
  m_maxBoundariesPerTariff = 0;
  m_maxBoundariesPerTariffIsSet = false;
}

bool TariffOverallConstraintsData::getMaxBoundariesPerTariffIsSet() const {
  return m_maxBoundariesPerTariffIsSet;
}

void TariffOverallConstraintsData::setMaxTiersPerTariff(
    const xs_unsignedInt &maxTiersPerTariff) {
  m_maxTiersPerTariff = maxTiersPerTariff;
  m_maxTiersPerTariffIsSet = true;
}

const xs_unsignedInt &
TariffOverallConstraintsData::getMaxTiersPerTariff() const {
  return m_maxTiersPerTariff;
}

void TariffOverallConstraintsData::cleanMaxTiersPerTariff() {
  m_maxTiersPerTariff = 0;
  m_maxTiersPerTariffIsSet = false;
}

bool TariffOverallConstraintsData::getMaxTiersPerTariffIsSet() const {
  return m_maxTiersPerTariffIsSet;
}

void TariffOverallConstraintsData::setMaxBoundariesPerTier(
    const xs_unsignedInt &maxBoundariesPerTier) {
  m_maxBoundariesPerTier = maxBoundariesPerTier;
  m_maxBoundariesPerTierIsSet = true;
}

const xs_unsignedInt &
TariffOverallConstraintsData::getMaxBoundariesPerTier() const {
  return m_maxBoundariesPerTier;
}

void TariffOverallConstraintsData::cleanMaxBoundariesPerTier() {
  m_maxBoundariesPerTier = 0;
  m_maxBoundariesPerTierIsSet = false;
}

bool TariffOverallConstraintsData::getMaxBoundariesPerTierIsSet() const {
  return m_maxBoundariesPerTierIsSet;
}

void TariffOverallConstraintsData::setMaxIncentivesPerTier(
    const xs_unsignedInt &maxIncentivesPerTier) {
  m_maxIncentivesPerTier = maxIncentivesPerTier;
  m_maxIncentivesPerTierIsSet = true;
}

const xs_unsignedInt &
TariffOverallConstraintsData::getMaxIncentivesPerTier() const {
  return m_maxIncentivesPerTier;
}

void TariffOverallConstraintsData::cleanMaxIncentivesPerTier() {
  m_maxIncentivesPerTier = 0;
  m_maxIncentivesPerTierIsSet = false;
}

bool TariffOverallConstraintsData::getMaxIncentivesPerTierIsSet() const {
  return m_maxIncentivesPerTierIsSet;
}

CmdDataPtr
TariffOverallConstraintsData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      TariffOverallConstraintsDataElementsPtr elements =
          std::dynamic_pointer_cast<TariffOverallConstraintsDataElements>(
              filter.getDataElements());
      if (elements) {
        TariffOverallConstraintsDataPtr dataOut =
            std::make_shared<TariffOverallConstraintsData>();
        // TODO make sure to always set identifier

        if (getMaxTariffCountIsSet() && elements->getMaxTariffCountIsSet()) {
          dataOut->setMaxTariffCount(getMaxTariffCount());
        }

        if (getMaxBoundaryCountIsSet() &&
            elements->getMaxBoundaryCountIsSet()) {
          dataOut->setMaxBoundaryCount(getMaxBoundaryCount());
        }

        if (getMaxTierCountIsSet() && elements->getMaxTierCountIsSet()) {
          dataOut->setMaxTierCount(getMaxTierCount());
        }

        if (getMaxIncentiveCountIsSet() &&
            elements->getMaxIncentiveCountIsSet()) {
          dataOut->setMaxIncentiveCount(getMaxIncentiveCount());
        }

        if (getMaxBoundariesPerTariffIsSet() &&
            elements->getMaxBoundariesPerTariffIsSet()) {
          dataOut->setMaxBoundariesPerTariff(getMaxBoundariesPerTariff());
        }

        if (getMaxTiersPerTariffIsSet() &&
            elements->getMaxTiersPerTariffIsSet()) {
          dataOut->setMaxTiersPerTariff(getMaxTiersPerTariff());
        }

        if (getMaxBoundariesPerTierIsSet() &&
            elements->getMaxBoundariesPerTierIsSet()) {
          dataOut->setMaxBoundariesPerTier(getMaxBoundariesPerTier());
        }

        if (getMaxIncentivesPerTierIsSet() &&
            elements->getMaxIncentivesPerTierIsSet()) {
          dataOut->setMaxIncentivesPerTier(getMaxIncentivesPerTier());
        }

        return dataOut;
      } else {
        return std::make_shared<TariffOverallConstraintsData>(*this);
      }
    } else {
      return std::make_shared<TariffOverallConstraintsData>(*this);
    }
  } else {
    return std::make_shared<TariffOverallConstraintsData>(*this);
  }
}

bool TariffOverallConstraintsData::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxTariffCount", &m_maxTariffCount)) {
      m_maxTariffCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxBoundaryCount", &m_maxBoundaryCount)) {
      m_maxBoundaryCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxTierCount", &m_maxTierCount)) {
      m_maxTierCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxIncentiveCount", &m_maxIncentiveCount)) {
      m_maxIncentiveCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxBoundariesPerTariff",
                                   &m_maxBoundariesPerTariff)) {
      m_maxBoundariesPerTariffIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxTiersPerTariff", &m_maxTiersPerTariff)) {
      m_maxTiersPerTariffIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxBoundariesPerTier",
                                   &m_maxBoundariesPerTier)) {
      m_maxBoundariesPerTierIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "maxIncentivesPerTier",
                                   &m_maxIncentivesPerTier)) {
      m_maxIncentivesPerTierIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffOverallConstraintsData::toJson() const {
  std::string result = "[";
  if (m_maxTariffCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("maxTariffCount", m_maxTariffCount);
  }
  if (m_maxBoundaryCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("maxBoundaryCount", m_maxBoundaryCount);
  }
  if (m_maxTierCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("maxTierCount", m_maxTierCount);
  }
  if (m_maxIncentiveCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("maxIncentiveCount", m_maxIncentiveCount);
  }
  if (m_maxBoundariesPerTariffIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("maxBoundariesPerTariff",
                                           m_maxBoundariesPerTariff);
  }
  if (m_maxTiersPerTariffIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("maxTiersPerTariff", m_maxTiersPerTariff);
  }
  if (m_maxBoundariesPerTierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("maxBoundariesPerTier",
                                           m_maxBoundariesPerTier);
  }
  if (m_maxIncentivesPerTierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("maxIncentivesPerTier",
                                           m_maxIncentivesPerTier);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram