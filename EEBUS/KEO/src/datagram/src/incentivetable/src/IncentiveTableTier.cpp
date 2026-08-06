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

#include <keo_datagram/incentivetable/IncentiveTableTier.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableTier::IncentiveTableTier()
    : m_tierIsSet(false), m_tier(TierData()), m_boundaryIsSet(false),
      m_boundary(std::vector<TierBoundaryData>()), m_incentiveIsSet(false),
      m_incentive(std::vector<IncentiveData>())

{}

IncentiveTableTier::IncentiveTableTier(
    const TierData &c_tier, const std::vector<TierBoundaryData> &c_boundary,
    const std::vector<IncentiveData> &c_incentive)
    : m_tierIsSet(true), m_tier(c_tier), m_boundaryIsSet(true),
      m_boundary(c_boundary), m_incentiveIsSet(true), m_incentive(c_incentive)

{}

bool IncentiveTableTier::
operator==(const IncentiveTableTier &c_classObject) const {
  if (m_tierIsSet != c_classObject.m_tierIsSet ||
      (m_tierIsSet && (m_tier != c_classObject.m_tier))) {
    return false;
  }
  if (m_boundaryIsSet != c_classObject.m_boundaryIsSet ||
      (m_boundaryIsSet && (m_boundary != c_classObject.m_boundary))) {
    return false;
  }
  if (m_incentiveIsSet != c_classObject.m_incentiveIsSet ||
      (m_incentiveIsSet && (m_incentive != c_classObject.m_incentive))) {
    return false;
  }

  return true;
}

bool IncentiveTableTier::
operator!=(const IncentiveTableTier &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableTier::isEmpty() const {
  return !m_tierIsSet && !m_boundaryIsSet && !m_incentiveIsSet;
}

void IncentiveTableTier::setTier(const TierData &tier) {
  m_tier = tier;
  m_tierIsSet = true;
}

const TierData &IncentiveTableTier::getTier() const { return m_tier; }

void IncentiveTableTier::cleanTier() {
  m_tier = TierData();
  m_tierIsSet = false;
}

bool IncentiveTableTier::getTierIsSet() const { return m_tierIsSet; }

void IncentiveTableTier::setBoundary(
    const std::vector<TierBoundaryData> &boundary) {
  m_boundary = boundary;
  m_boundaryIsSet = true;
}

const std::vector<TierBoundaryData> &IncentiveTableTier::getBoundary() const {
  return m_boundary;
}

void IncentiveTableTier::cleanBoundary() {
  m_boundary.clear();
  m_boundaryIsSet = false;
}

bool IncentiveTableTier::getBoundaryIsSet() const { return m_boundaryIsSet; }

void IncentiveTableTier::setIncentive(
    const std::vector<IncentiveData> &incentive) {
  m_incentive = incentive;
  m_incentiveIsSet = true;
}

const std::vector<IncentiveData> &IncentiveTableTier::getIncentive() const {
  return m_incentive;
}

void IncentiveTableTier::cleanIncentive() {
  m_incentive.clear();
  m_incentiveIsSet = false;
}

bool IncentiveTableTier::getIncentiveIsSet() const { return m_incentiveIsSet; }

bool IncentiveTableTier::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tier", "boundary", "incentive"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tier", &m_tier)) {
      m_tierIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TierBoundaryData>(
            static_cast<KeoJsonValue *>(&(*iter)), "boundary", &m_boundary)) {
      m_boundaryIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<IncentiveData>(
            static_cast<KeoJsonValue *>(&(*iter)), "incentive", &m_incentive)) {
      m_incentiveIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableTier::toJson() const {
  std::string result = "[";
  if (m_tierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tier", m_tier);
  }
  if (m_boundaryIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TierBoundaryData>("boundary",
                                                                 m_boundary);
  }
  if (m_incentiveIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<IncentiveData>("incentive",
                                                              m_incentive);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram