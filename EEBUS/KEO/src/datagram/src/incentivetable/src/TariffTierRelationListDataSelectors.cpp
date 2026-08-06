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

#include <keo_datagram/incentivetable/TariffTierRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffTierRelationListDataSelectors::TariffTierRelationListDataSelectors()
    : DataSelectors(), m_tariffIdIsSet(false), m_tariffId(0),
      m_tierIdIsSet(false), m_tierId(0)

{}

TariffTierRelationListDataSelectors::TariffTierRelationListDataSelectors(
    const xs_unsignedInt &c_tariffId, const xs_unsignedInt &c_tierId)
    : DataSelectors(), m_tariffIdIsSet(true), m_tariffId(c_tariffId),
      m_tierIdIsSet(true), m_tierId(c_tierId)

{}

bool TariffTierRelationListDataSelectors::
operator==(const TariffTierRelationListDataSelectors &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet ||
      (m_tariffIdIsSet && (m_tariffId != c_classObject.m_tariffId))) {
    return false;
  }
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet ||
      (m_tierIdIsSet && (m_tierId != c_classObject.m_tierId))) {
    return false;
  }

  return true;
}

bool TariffTierRelationListDataSelectors::
operator!=(const TariffTierRelationListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffTierRelationListDataSelectors::isEmpty() const {
  return !m_tariffIdIsSet && !m_tierIdIsSet;
}

DataSelectors::Type TariffTierRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::TARIFF_TIER_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TariffTierRelationListDataSelectors::clone() const {
  return std::make_shared<TariffTierRelationListDataSelectors>(*this);
}

void TariffTierRelationListDataSelectors::setTariffId(
    const xs_unsignedInt &tariffId) {
  m_tariffId = tariffId;
  m_tariffIdIsSet = true;
}

const xs_unsignedInt &TariffTierRelationListDataSelectors::getTariffId() const {
  return m_tariffId;
}

void TariffTierRelationListDataSelectors::cleanTariffId() {
  m_tariffId = 0;
  m_tariffIdIsSet = false;
}

bool TariffTierRelationListDataSelectors::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffTierRelationListDataSelectors::setTierId(
    const xs_unsignedInt &tierId) {
  m_tierId = tierId;
  m_tierIdIsSet = true;
}

const xs_unsignedInt &TariffTierRelationListDataSelectors::getTierId() const {
  return m_tierId;
}

void TariffTierRelationListDataSelectors::cleanTierId() {
  m_tierId = 0;
  m_tierIdIsSet = false;
}

bool TariffTierRelationListDataSelectors::getTierIdIsSet() const {
  return m_tierIdIsSet;
}

bool TariffTierRelationListDataSelectors::selects(
    const TariffTierRelationData &data) const {
  if (getTariffIdIsSet() &&
      (!data.getTariffIdIsSet() || getTariffId() != data.getTariffId())) {
    return false;
  }
  if (getTierIdIsSet() &&
      (!data.getTierIdIsSet() ||
       std::find(std::begin(data.getTierId()), std::end(data.getTierId()),
                 getTierId()) == std::end(data.getTierId()))) {
    return false;
  }
  return true;
}

bool TariffTierRelationListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tariffId", "tierId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariffId", &m_tariffId)) {
      m_tariffIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tierId", &m_tierId)) {
      m_tierIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffTierRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariffId", m_tariffId);
  }
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tierId", m_tierId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram