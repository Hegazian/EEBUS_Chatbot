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

#include <keo_datagram/incentivetable/TariffListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffListDataSelectors::TariffListDataSelectors()
    : DataSelectors(), m_tariffIdIsSet(false), m_tariffId(0),
      m_activeTierIdIsSet(false), m_activeTierId(0)

{}

TariffListDataSelectors::TariffListDataSelectors(
    const xs_unsignedInt &c_tariffId, const xs_unsignedInt &c_activeTierId)
    : DataSelectors(), m_tariffIdIsSet(true), m_tariffId(c_tariffId),
      m_activeTierIdIsSet(true), m_activeTierId(c_activeTierId)

{}

bool TariffListDataSelectors::
operator==(const TariffListDataSelectors &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet ||
      (m_tariffIdIsSet && (m_tariffId != c_classObject.m_tariffId))) {
    return false;
  }
  if (m_activeTierIdIsSet != c_classObject.m_activeTierIdIsSet ||
      (m_activeTierIdIsSet &&
       (m_activeTierId != c_classObject.m_activeTierId))) {
    return false;
  }

  return true;
}

bool TariffListDataSelectors::
operator!=(const TariffListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffListDataSelectors::isEmpty() const {
  return !m_tariffIdIsSet && !m_activeTierIdIsSet;
}

DataSelectors::Type TariffListDataSelectors::getDataType() const {
  return DataSelectors::Type::TARIFF_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TariffListDataSelectors::clone() const {
  return std::make_shared<TariffListDataSelectors>(*this);
}

void TariffListDataSelectors::setTariffId(const xs_unsignedInt &tariffId) {
  m_tariffId = tariffId;
  m_tariffIdIsSet = true;
}

const xs_unsignedInt &TariffListDataSelectors::getTariffId() const {
  return m_tariffId;
}

void TariffListDataSelectors::cleanTariffId() {
  m_tariffId = 0;
  m_tariffIdIsSet = false;
}

bool TariffListDataSelectors::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffListDataSelectors::setActiveTierId(
    const xs_unsignedInt &activeTierId) {
  m_activeTierId = activeTierId;
  m_activeTierIdIsSet = true;
}

const xs_unsignedInt &TariffListDataSelectors::getActiveTierId() const {
  return m_activeTierId;
}

void TariffListDataSelectors::cleanActiveTierId() {
  m_activeTierId = 0;
  m_activeTierIdIsSet = false;
}

bool TariffListDataSelectors::getActiveTierIdIsSet() const {
  return m_activeTierIdIsSet;
}

bool TariffListDataSelectors::selects(const TariffData &data) const {
  if (getTariffIdIsSet() &&
      (!data.getTariffIdIsSet() || getTariffId() != data.getTariffId())) {
    return false;
  }
  if (getActiveTierIdIsSet() &&
      (!data.getActiveTierIdIsSet() ||
       std::find(std::begin(data.getActiveTierId()),
                 std::end(data.getActiveTierId()),
                 getActiveTierId()) == std::end(data.getActiveTierId()))) {
    return false;
  }
  return true;
}

bool TariffListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tariffId", "activeTierId"})) {
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
                                   "activeTierId", &m_activeTierId)) {
      m_activeTierIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariffId", m_tariffId);
  }
  if (m_activeTierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("activeTierId", m_activeTierId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram