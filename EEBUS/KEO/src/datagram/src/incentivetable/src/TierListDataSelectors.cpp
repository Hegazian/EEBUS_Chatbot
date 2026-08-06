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

#include <keo_datagram/incentivetable/TierListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierListDataSelectors::TierListDataSelectors()
    : DataSelectors(), m_tierIdIsSet(false), m_tierId(0),
      m_activeIncentiveIdIsSet(false), m_activeIncentiveId(0)

{}

TierListDataSelectors::TierListDataSelectors(
    const xs_unsignedInt &c_tierId, const xs_unsignedInt &c_activeIncentiveId)
    : DataSelectors(), m_tierIdIsSet(true), m_tierId(c_tierId),
      m_activeIncentiveIdIsSet(true), m_activeIncentiveId(c_activeIncentiveId)

{}

bool TierListDataSelectors::
operator==(const TierListDataSelectors &c_classObject) const {
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet ||
      (m_tierIdIsSet && (m_tierId != c_classObject.m_tierId))) {
    return false;
  }
  if (m_activeIncentiveIdIsSet != c_classObject.m_activeIncentiveIdIsSet ||
      (m_activeIncentiveIdIsSet &&
       (m_activeIncentiveId != c_classObject.m_activeIncentiveId))) {
    return false;
  }

  return true;
}

bool TierListDataSelectors::
operator!=(const TierListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierListDataSelectors::isEmpty() const {
  return !m_tierIdIsSet && !m_activeIncentiveIdIsSet;
}

DataSelectors::Type TierListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIER_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TierListDataSelectors::clone() const {
  return std::make_shared<TierListDataSelectors>(*this);
}

void TierListDataSelectors::setTierId(const xs_unsignedInt &tierId) {
  m_tierId = tierId;
  m_tierIdIsSet = true;
}

const xs_unsignedInt &TierListDataSelectors::getTierId() const {
  return m_tierId;
}

void TierListDataSelectors::cleanTierId() {
  m_tierId = 0;
  m_tierIdIsSet = false;
}

bool TierListDataSelectors::getTierIdIsSet() const { return m_tierIdIsSet; }

void TierListDataSelectors::setActiveIncentiveId(
    const xs_unsignedInt &activeIncentiveId) {
  m_activeIncentiveId = activeIncentiveId;
  m_activeIncentiveIdIsSet = true;
}

const xs_unsignedInt &TierListDataSelectors::getActiveIncentiveId() const {
  return m_activeIncentiveId;
}

void TierListDataSelectors::cleanActiveIncentiveId() {
  m_activeIncentiveId = 0;
  m_activeIncentiveIdIsSet = false;
}

bool TierListDataSelectors::getActiveIncentiveIdIsSet() const {
  return m_activeIncentiveIdIsSet;
}

bool TierListDataSelectors::selects(const TierData &data) const {
  if (getTierIdIsSet() &&
      (!data.getTierIdIsSet() || getTierId() != data.getTierId())) {
    return false;
  }
  if (getActiveIncentiveIdIsSet() &&
      (!data.getActiveIncentiveIdIsSet() ||
       std::find(std::begin(data.getActiveIncentiveId()),
                 std::end(data.getActiveIncentiveId()),
                 getActiveIncentiveId()) ==
           std::end(data.getActiveIncentiveId()))) {
    return false;
  }
  return true;
}

bool TierListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tierId", "activeIncentiveId"})) {
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
                                   "activeIncentiveId", &m_activeIncentiveId)) {
      m_activeIncentiveIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tierId", m_tierId);
  }
  if (m_activeIncentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("activeIncentiveId", m_activeIncentiveId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram