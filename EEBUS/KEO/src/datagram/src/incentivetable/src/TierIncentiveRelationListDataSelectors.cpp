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

#include <keo_datagram/incentivetable/TierIncentiveRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierIncentiveRelationListDataSelectors::TierIncentiveRelationListDataSelectors()
    : DataSelectors(), m_tierIdIsSet(false), m_tierId(0),
      m_incentiveIdIsSet(false), m_incentiveId(0)

{}

TierIncentiveRelationListDataSelectors::TierIncentiveRelationListDataSelectors(
    const xs_unsignedInt &c_tierId, const xs_unsignedInt &c_incentiveId)
    : DataSelectors(), m_tierIdIsSet(true), m_tierId(c_tierId),
      m_incentiveIdIsSet(true), m_incentiveId(c_incentiveId)

{}

bool TierIncentiveRelationListDataSelectors::
operator==(const TierIncentiveRelationListDataSelectors &c_classObject) const {
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet ||
      (m_tierIdIsSet && (m_tierId != c_classObject.m_tierId))) {
    return false;
  }
  if (m_incentiveIdIsSet != c_classObject.m_incentiveIdIsSet ||
      (m_incentiveIdIsSet && (m_incentiveId != c_classObject.m_incentiveId))) {
    return false;
  }

  return true;
}

bool TierIncentiveRelationListDataSelectors::
operator!=(const TierIncentiveRelationListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierIncentiveRelationListDataSelectors::isEmpty() const {
  return !m_tierIdIsSet && !m_incentiveIdIsSet;
}

DataSelectors::Type
TierIncentiveRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIER_INCENTIVE_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TierIncentiveRelationListDataSelectors::clone() const {
  return std::make_shared<TierIncentiveRelationListDataSelectors>(*this);
}

void TierIncentiveRelationListDataSelectors::setTierId(
    const xs_unsignedInt &tierId) {
  m_tierId = tierId;
  m_tierIdIsSet = true;
}

const xs_unsignedInt &
TierIncentiveRelationListDataSelectors::getTierId() const {
  return m_tierId;
}

void TierIncentiveRelationListDataSelectors::cleanTierId() {
  m_tierId = 0;
  m_tierIdIsSet = false;
}

bool TierIncentiveRelationListDataSelectors::getTierIdIsSet() const {
  return m_tierIdIsSet;
}

void TierIncentiveRelationListDataSelectors::setIncentiveId(
    const xs_unsignedInt &incentiveId) {
  m_incentiveId = incentiveId;
  m_incentiveIdIsSet = true;
}

const xs_unsignedInt &
TierIncentiveRelationListDataSelectors::getIncentiveId() const {
  return m_incentiveId;
}

void TierIncentiveRelationListDataSelectors::cleanIncentiveId() {
  m_incentiveId = 0;
  m_incentiveIdIsSet = false;
}

bool TierIncentiveRelationListDataSelectors::getIncentiveIdIsSet() const {
  return m_incentiveIdIsSet;
}

bool TierIncentiveRelationListDataSelectors::selects(
    const TierIncentiveRelationData &data) const {
  if (getTierIdIsSet() &&
      (!data.getTierIdIsSet() || getTierId() != data.getTierId())) {
    return false;
  }
  if (getIncentiveIdIsSet() &&
      (!data.getIncentiveIdIsSet() ||
       std::find(std::begin(data.getIncentiveId()),
                 std::end(data.getIncentiveId()),
                 getIncentiveId()) == std::end(data.getIncentiveId()))) {
    return false;
  }
  return true;
}

bool TierIncentiveRelationListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tierId", "incentiveId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tierId", &m_tierId)) {
      m_tierIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveId", &m_incentiveId)) {
      m_incentiveIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierIncentiveRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tierId", m_tierId);
  }
  if (m_incentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveId", m_incentiveId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram