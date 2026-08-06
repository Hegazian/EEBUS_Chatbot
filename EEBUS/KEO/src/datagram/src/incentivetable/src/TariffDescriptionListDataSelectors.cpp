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

#include <keo_datagram/incentivetable/TariffDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffDescriptionListDataSelectors::TariffDescriptionListDataSelectors()
    : DataSelectors(), m_tariffIdIsSet(false), m_tariffId(0),
      m_commodityIdIsSet(false), m_commodityId(0), m_measurementIdIsSet(false),
      m_measurementId(0), m_scopeTypeIsSet(false), m_scopeType(ScopeType())

{}

bool TariffDescriptionListDataSelectors::
operator==(const TariffDescriptionListDataSelectors &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet ||
      (m_tariffIdIsSet && (m_tariffId != c_classObject.m_tariffId))) {
    return false;
  }
  if (m_commodityIdIsSet != c_classObject.m_commodityIdIsSet ||
      (m_commodityIdIsSet && (m_commodityId != c_classObject.m_commodityId))) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool TariffDescriptionListDataSelectors::
operator!=(const TariffDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffDescriptionListDataSelectors::isEmpty() const {
  return !m_tariffIdIsSet && !m_commodityIdIsSet && !m_measurementIdIsSet &&
         !m_scopeTypeIsSet;
}

DataSelectors::Type TariffDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::TARIFF_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TariffDescriptionListDataSelectors::clone() const {
  return std::make_shared<TariffDescriptionListDataSelectors>(*this);
}

void TariffDescriptionListDataSelectors::setTariffId(
    const xs_unsignedInt &tariffId) {
  m_tariffId = tariffId;
  m_tariffIdIsSet = true;
}

const xs_unsignedInt &TariffDescriptionListDataSelectors::getTariffId() const {
  return m_tariffId;
}

void TariffDescriptionListDataSelectors::cleanTariffId() {
  m_tariffId = 0;
  m_tariffIdIsSet = false;
}

bool TariffDescriptionListDataSelectors::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffDescriptionListDataSelectors::setCommodityId(
    const xs_unsignedInt &commodityId) {
  m_commodityId = commodityId;
  m_commodityIdIsSet = true;
}

const xs_unsignedInt &
TariffDescriptionListDataSelectors::getCommodityId() const {
  return m_commodityId;
}

void TariffDescriptionListDataSelectors::cleanCommodityId() {
  m_commodityId = 0;
  m_commodityIdIsSet = false;
}

bool TariffDescriptionListDataSelectors::getCommodityIdIsSet() const {
  return m_commodityIdIsSet;
}

void TariffDescriptionListDataSelectors::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
TariffDescriptionListDataSelectors::getMeasurementId() const {
  return m_measurementId;
}

void TariffDescriptionListDataSelectors::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool TariffDescriptionListDataSelectors::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void TariffDescriptionListDataSelectors::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &TariffDescriptionListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void TariffDescriptionListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool TariffDescriptionListDataSelectors::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool TariffDescriptionListDataSelectors::selects(
    const TariffDescriptionData &data) const {
  if (getTariffIdIsSet() &&
      (!data.getTariffIdIsSet() || getTariffId() != data.getTariffId())) {
    return false;
  }
  if (getCommodityIdIsSet() && (!data.getCommodityIdIsSet() ||
                                getCommodityId() != data.getCommodityId())) {
    return false;
  }
  if (getMeasurementIdIsSet() &&
      (!data.getMeasurementIdIsSet() ||
       getMeasurementId() != data.getMeasurementId())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool TariffDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tariffId", "commodityId", "measurementId", "scopeType"})) {
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
                                   "commodityId", &m_commodityId)) {
      m_commodityIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariffId", m_tariffId);
  }
  if (m_commodityIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("commodityId", m_commodityId);
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram