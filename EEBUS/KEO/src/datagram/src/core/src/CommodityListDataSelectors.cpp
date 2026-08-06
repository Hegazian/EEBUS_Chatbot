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

#include <keo_datagram/core/CommodityListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

CommodityListDataSelectors::CommodityListDataSelectors()
    : DataSelectors(), m_commodityIdIsSet(false), m_commodityId(0),
      m_commodityTypeIsSet(false), m_commodityType(CommodityType())

{}

CommodityListDataSelectors::CommodityListDataSelectors(
    const xs_unsignedInt &c_commodityId, const CommodityType &c_commodityType)
    : DataSelectors(), m_commodityIdIsSet(true), m_commodityId(c_commodityId),
      m_commodityTypeIsSet(true), m_commodityType(c_commodityType)

{}

bool CommodityListDataSelectors::
operator==(const CommodityListDataSelectors &c_classObject) const {
  if (m_commodityIdIsSet != c_classObject.m_commodityIdIsSet ||
      (m_commodityIdIsSet && (m_commodityId != c_classObject.m_commodityId))) {
    return false;
  }
  if (m_commodityTypeIsSet != c_classObject.m_commodityTypeIsSet ||
      (m_commodityTypeIsSet &&
       (m_commodityType != c_classObject.m_commodityType))) {
    return false;
  }

  return true;
}

bool CommodityListDataSelectors::
operator!=(const CommodityListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool CommodityListDataSelectors::isEmpty() const {
  return !m_commodityIdIsSet && !m_commodityTypeIsSet;
}

DataSelectors::Type CommodityListDataSelectors::getDataType() const {
  return DataSelectors::Type::COMMODITY_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr CommodityListDataSelectors::clone() const {
  return std::make_shared<CommodityListDataSelectors>(*this);
}

void CommodityListDataSelectors::setCommodityId(
    const xs_unsignedInt &commodityId) {
  m_commodityId = commodityId;
  m_commodityIdIsSet = true;
}

const xs_unsignedInt &CommodityListDataSelectors::getCommodityId() const {
  return m_commodityId;
}

void CommodityListDataSelectors::cleanCommodityId() {
  m_commodityId = 0;
  m_commodityIdIsSet = false;
}

bool CommodityListDataSelectors::getCommodityIdIsSet() const {
  return m_commodityIdIsSet;
}

void CommodityListDataSelectors::setCommodityType(
    const CommodityType &commodityType) {
  m_commodityType = commodityType;
  m_commodityTypeIsSet = true;
}

const CommodityType &CommodityListDataSelectors::getCommodityType() const {
  return m_commodityType;
}

void CommodityListDataSelectors::cleanCommodityType() {
  m_commodityType = CommodityType();
  m_commodityTypeIsSet = false;
}

bool CommodityListDataSelectors::getCommodityTypeIsSet() const {
  return m_commodityTypeIsSet;
}

bool CommodityListDataSelectors::selects(const CommodityData &data) const {
  if (getCommodityIdIsSet() && (!data.getCommodityIdIsSet() ||
                                getCommodityId() != data.getCommodityId())) {
    return false;
  }
  if (getCommodityTypeIsSet() &&
      (!data.getCommodityTypeIsSet() ||
       getCommodityType() != data.getCommodityType())) {
    return false;
  }
  return true;
}

bool CommodityListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"commodityId", "commodityType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "commodityId", &m_commodityId)) {
      m_commodityIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "commodityType", &m_commodityType)) {
      m_commodityTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string CommodityListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_commodityIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("commodityId", m_commodityId);
  }
  if (m_commodityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("commodityType", m_commodityType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram