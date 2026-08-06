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

#include <keo_datagram/incentivetable/TierDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierDescriptionListDataSelectors::TierDescriptionListDataSelectors()
    : DataSelectors(), m_tierIdIsSet(false), m_tierId(0),
      m_tierTypeIsSet(false), m_tierType(TierType())

{}

TierDescriptionListDataSelectors::TierDescriptionListDataSelectors(
    const xs_unsignedInt &c_tierId, const TierType &c_tierType)
    : DataSelectors(), m_tierIdIsSet(true), m_tierId(c_tierId),
      m_tierTypeIsSet(true), m_tierType(c_tierType)

{}

bool TierDescriptionListDataSelectors::
operator==(const TierDescriptionListDataSelectors &c_classObject) const {
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet ||
      (m_tierIdIsSet && (m_tierId != c_classObject.m_tierId))) {
    return false;
  }
  if (m_tierTypeIsSet != c_classObject.m_tierTypeIsSet ||
      (m_tierTypeIsSet && (m_tierType != c_classObject.m_tierType))) {
    return false;
  }

  return true;
}

bool TierDescriptionListDataSelectors::
operator!=(const TierDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierDescriptionListDataSelectors::isEmpty() const {
  return !m_tierIdIsSet && !m_tierTypeIsSet;
}

DataSelectors::Type TierDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TierDescriptionListDataSelectors::clone() const {
  return std::make_shared<TierDescriptionListDataSelectors>(*this);
}

void TierDescriptionListDataSelectors::setTierId(const xs_unsignedInt &tierId) {
  m_tierId = tierId;
  m_tierIdIsSet = true;
}

const xs_unsignedInt &TierDescriptionListDataSelectors::getTierId() const {
  return m_tierId;
}

void TierDescriptionListDataSelectors::cleanTierId() {
  m_tierId = 0;
  m_tierIdIsSet = false;
}

bool TierDescriptionListDataSelectors::getTierIdIsSet() const {
  return m_tierIdIsSet;
}

void TierDescriptionListDataSelectors::setTierType(const TierType &tierType) {
  m_tierType = tierType;
  m_tierTypeIsSet = true;
}

const TierType &TierDescriptionListDataSelectors::getTierType() const {
  return m_tierType;
}

void TierDescriptionListDataSelectors::cleanTierType() {
  m_tierType = TierType();
  m_tierTypeIsSet = false;
}

bool TierDescriptionListDataSelectors::getTierTypeIsSet() const {
  return m_tierTypeIsSet;
}

bool TierDescriptionListDataSelectors::selects(
    const TierDescriptionData &data) const {
  if (getTierIdIsSet() &&
      (!data.getTierIdIsSet() || getTierId() != data.getTierId())) {
    return false;
  }
  if (getTierTypeIsSet() &&
      (!data.getTierTypeIsSet() || getTierType() != data.getTierType())) {
    return false;
  }
  return true;
}

bool TierDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tierId", "tierType"})) {
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
                                   "tierType", &m_tierType)) {
      m_tierTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tierId", m_tierId);
  }
  if (m_tierTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tierType", m_tierType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram