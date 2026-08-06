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
#include <keo_datagram/incentivetable/TierIncentiveRelationListData.h>
#include <keo_datagram/incentivetable/TierIncentiveRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierIncentiveRelationListData::TierIncentiveRelationListData()
    : CmdData(), m_tierIncentiveRelationDataIsSet(false),
      m_tierIncentiveRelationData(std::vector<TierIncentiveRelationData>())

{}

TierIncentiveRelationListData::TierIncentiveRelationListData(
    const std::vector<TierIncentiveRelationData> &c_tierIncentiveRelationData) {
  setTierIncentiveRelationData(c_tierIncentiveRelationData);
}

bool TierIncentiveRelationListData::
operator==(const TierIncentiveRelationListData &c_classObject) const {
  if (m_tierIncentiveRelationDataIsSet !=
          c_classObject.m_tierIncentiveRelationDataIsSet ||
      (m_tierIncentiveRelationDataIsSet &&
       (m_tierIncentiveRelationData !=
        c_classObject.m_tierIncentiveRelationData))) {
    return false;
  }

  return true;
}

bool TierIncentiveRelationListData::
operator!=(const TierIncentiveRelationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierIncentiveRelationListData::isEmpty() const {
  return !m_tierIncentiveRelationDataIsSet;
}

CmdData::Type TierIncentiveRelationListData::getDataType() const {
  return CmdData::Type::TIER_INCENTIVE_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr TierIncentiveRelationListData::clone() const {
  return std::make_shared<TierIncentiveRelationListData>(*this);
}

void TierIncentiveRelationListData::setTierIncentiveRelationData(
    const std::vector<TierIncentiveRelationData> &tierIncentiveRelationData) {
  m_tierIncentiveRelationData = tierIncentiveRelationData;
  m_tierIncentiveRelationDataIsSet = true;
}

const std::vector<TierIncentiveRelationData> &
TierIncentiveRelationListData::getTierIncentiveRelationData() const {
  return m_tierIncentiveRelationData;
}

void TierIncentiveRelationListData::cleanTierIncentiveRelationData() {
  m_tierIncentiveRelationData.clear();
  m_tierIncentiveRelationDataIsSet = false;
}

bool TierIncentiveRelationListData::getTierIncentiveRelationDataIsSet() const {
  return m_tierIncentiveRelationDataIsSet;
}

CmdDataPtr TierIncentiveRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<TierIncentiveRelationData> dataOut;
  for (const auto &data : getTierIncentiveRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TierIncentiveRelationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TierIncentiveRelationListDataSelectors>(
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
          const TierIncentiveRelationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TierIncentiveRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TierIncentiveRelationData(data));
          }
        }
      } else {
        return std::make_shared<TierIncentiveRelationListData>(*this);
      }
    } else {
      return std::make_shared<TierIncentiveRelationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TierIncentiveRelationListData>(dataOut);
  } else {
    return std::make_shared<TierIncentiveRelationListData>();
  }
}

bool TierIncentiveRelationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tierIncentiveRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TierIncentiveRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)), "tierIncentiveRelationData",
            &m_tierIncentiveRelationData)) {
      m_tierIncentiveRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierIncentiveRelationListData::toJson() const {
  std::string result = "[";
  if (m_tierIncentiveRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TierIncentiveRelationData>(
        "tierIncentiveRelationData", m_tierIncentiveRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram