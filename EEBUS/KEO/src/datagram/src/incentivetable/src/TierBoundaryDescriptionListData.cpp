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
#include <keo_datagram/incentivetable/TierBoundaryDescriptionListData.h>
#include <keo_datagram/incentivetable/TierBoundaryDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierBoundaryDescriptionListData::TierBoundaryDescriptionListData()
    : CmdData(), m_tierBoundaryDescriptionDataIsSet(false),
      m_tierBoundaryDescriptionData(std::vector<TierBoundaryDescriptionData>())

{}

TierBoundaryDescriptionListData::TierBoundaryDescriptionListData(
    const std::vector<TierBoundaryDescriptionData>
        &c_tierBoundaryDescriptionData) {
  setTierBoundaryDescriptionData(c_tierBoundaryDescriptionData);
}

bool TierBoundaryDescriptionListData::
operator==(const TierBoundaryDescriptionListData &c_classObject) const {
  if (m_tierBoundaryDescriptionDataIsSet !=
          c_classObject.m_tierBoundaryDescriptionDataIsSet ||
      (m_tierBoundaryDescriptionDataIsSet &&
       (m_tierBoundaryDescriptionData !=
        c_classObject.m_tierBoundaryDescriptionData))) {
    return false;
  }

  return true;
}

bool TierBoundaryDescriptionListData::
operator!=(const TierBoundaryDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierBoundaryDescriptionListData::isEmpty() const {
  return !m_tierBoundaryDescriptionDataIsSet;
}

CmdData::Type TierBoundaryDescriptionListData::getDataType() const {
  return CmdData::Type::TIER_BOUNDARY_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr TierBoundaryDescriptionListData::clone() const {
  return std::make_shared<TierBoundaryDescriptionListData>(*this);
}

void TierBoundaryDescriptionListData::setTierBoundaryDescriptionData(
    const std::vector<TierBoundaryDescriptionData>
        &tierBoundaryDescriptionData) {
  m_tierBoundaryDescriptionData = tierBoundaryDescriptionData;
  m_tierBoundaryDescriptionDataIsSet = true;
}

const std::vector<TierBoundaryDescriptionData> &
TierBoundaryDescriptionListData::getTierBoundaryDescriptionData() const {
  return m_tierBoundaryDescriptionData;
}

void TierBoundaryDescriptionListData::cleanTierBoundaryDescriptionData() {
  m_tierBoundaryDescriptionData.clear();
  m_tierBoundaryDescriptionDataIsSet = false;
}

bool TierBoundaryDescriptionListData::getTierBoundaryDescriptionDataIsSet()
    const {
  return m_tierBoundaryDescriptionDataIsSet;
}

CmdDataPtr TierBoundaryDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<TierBoundaryDescriptionData> dataOut;
  for (const auto &data : getTierBoundaryDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TierBoundaryDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  TierBoundaryDescriptionListDataSelectors>(baseSelectorsClass);
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
          const TierBoundaryDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TierBoundaryDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TierBoundaryDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<TierBoundaryDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<TierBoundaryDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TierBoundaryDescriptionListData>(dataOut);
  } else {
    return std::make_shared<TierBoundaryDescriptionListData>();
  }
}

bool TierBoundaryDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tierBoundaryDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TierBoundaryDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "tierBoundaryDescriptionData", &m_tierBoundaryDescriptionData)) {
      m_tierBoundaryDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierBoundaryDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_tierBoundaryDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TierBoundaryDescriptionData>(
        "tierBoundaryDescriptionData", m_tierBoundaryDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram