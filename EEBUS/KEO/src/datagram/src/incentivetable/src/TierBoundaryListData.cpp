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
#include <keo_datagram/incentivetable/TierBoundaryListData.h>
#include <keo_datagram/incentivetable/TierBoundaryListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierBoundaryListData::TierBoundaryListData()
    : CmdData(), m_tierBoundaryDataIsSet(false),
      m_tierBoundaryData(std::vector<TierBoundaryData>())

{}

TierBoundaryListData::TierBoundaryListData(
    const std::vector<TierBoundaryData> &c_tierBoundaryData) {
  setTierBoundaryData(c_tierBoundaryData);
}

bool TierBoundaryListData::
operator==(const TierBoundaryListData &c_classObject) const {
  if (m_tierBoundaryDataIsSet != c_classObject.m_tierBoundaryDataIsSet ||
      (m_tierBoundaryDataIsSet &&
       (m_tierBoundaryData != c_classObject.m_tierBoundaryData))) {
    return false;
  }

  return true;
}

bool TierBoundaryListData::
operator!=(const TierBoundaryListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierBoundaryListData::isEmpty() const { return !m_tierBoundaryDataIsSet; }

CmdData::Type TierBoundaryListData::getDataType() const {
  return CmdData::Type::TIER_BOUNDARY_LIST_DATA_TYPE;
}

CmdDataPtr TierBoundaryListData::clone() const {
  return std::make_shared<TierBoundaryListData>(*this);
}

void TierBoundaryListData::setTierBoundaryData(
    const std::vector<TierBoundaryData> &tierBoundaryData) {
  m_tierBoundaryData = tierBoundaryData;
  m_tierBoundaryDataIsSet = true;
}

const std::vector<TierBoundaryData> &
TierBoundaryListData::getTierBoundaryData() const {
  return m_tierBoundaryData;
}

void TierBoundaryListData::cleanTierBoundaryData() {
  m_tierBoundaryData.clear();
  m_tierBoundaryDataIsSet = false;
}

bool TierBoundaryListData::getTierBoundaryDataIsSet() const {
  return m_tierBoundaryDataIsSet;
}

CmdDataPtr
TierBoundaryListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TierBoundaryData> dataOut;
  for (const auto &data : getTierBoundaryData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TierBoundaryListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TierBoundaryListDataSelectors>(
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
          const TierBoundaryDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TierBoundaryDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TierBoundaryData(data));
          }
        }
      } else {
        return std::make_shared<TierBoundaryListData>(*this);
      }
    } else {
      return std::make_shared<TierBoundaryListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TierBoundaryListData>(dataOut);
  } else {
    return std::make_shared<TierBoundaryListData>();
  }
}

bool TierBoundaryListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tierBoundaryData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<TierBoundaryData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "tierBoundaryData", &m_tierBoundaryData)) {
      m_tierBoundaryDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierBoundaryListData::toJson() const {
  std::string result = "[";
  if (m_tierBoundaryDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TierBoundaryData>(
        "tierBoundaryData", m_tierBoundaryData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram