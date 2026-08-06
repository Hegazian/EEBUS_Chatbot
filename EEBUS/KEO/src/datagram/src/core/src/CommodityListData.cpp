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

#include <algorithm>
#include <keo_datagram/core/CommodityListData.h>
#include <keo_datagram/core/CommodityListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

CommodityListData::CommodityListData()
    : CmdData(), m_commodityDataIsSet(false),
      m_commodityData(std::vector<CommodityData>())

{}

CommodityListData::CommodityListData(
    const std::vector<CommodityData> &c_commodityData) {
  setCommodityData(c_commodityData);
}

bool CommodityListData::
operator==(const CommodityListData &c_classObject) const {
  if (m_commodityDataIsSet != c_classObject.m_commodityDataIsSet ||
      (m_commodityDataIsSet &&
       (m_commodityData != c_classObject.m_commodityData))) {
    return false;
  }

  return true;
}

bool CommodityListData::
operator!=(const CommodityListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool CommodityListData::isEmpty() const { return !m_commodityDataIsSet; }

CmdData::Type CommodityListData::getDataType() const {
  return CmdData::Type::COMMODITY_LIST_DATA_TYPE;
}

CmdDataPtr CommodityListData::clone() const {
  return std::make_shared<CommodityListData>(*this);
}

void CommodityListData::setCommodityData(
    const std::vector<CommodityData> &commodityData) {
  m_commodityData = commodityData;
  m_commodityDataIsSet = true;
}

const std::vector<CommodityData> &CommodityListData::getCommodityData() const {
  return m_commodityData;
}

void CommodityListData::cleanCommodityData() {
  m_commodityData.clear();
  m_commodityDataIsSet = false;
}

bool CommodityListData::getCommodityDataIsSet() const {
  return m_commodityDataIsSet;
}

CmdDataPtr CommodityListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<CommodityData> dataOut;
  for (const auto &data : getCommodityData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          CommodityListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<CommodityListDataSelectors>(
                  baseSelectorsClass);
          if (selectors) {
            if (selectors->selects(data)) {
              // The first selecting selector selects
              isSelected = true;
              break;
            }
          } else {
            // Selectors of wrong type are ignored and don't select anything.
          }
        }
        if (isSelected) {
          const CommodityDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<CommodityDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(CommodityData(data));
          }
        }
      } else {
        return std::make_shared<CommodityListData>(*this);
      }
    } else {
      return std::make_shared<CommodityListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<CommodityListData>(dataOut);
  } else {
    return std::make_shared<CommodityListData>();
  }
}

bool CommodityListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"commodityData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<CommodityData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "commodityData", &m_commodityData)) {
      m_commodityDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string CommodityListData::toJson() const {
  std::string result = "[";
  if (m_commodityDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<CommodityData>("commodityData",
                                                              m_commodityData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram