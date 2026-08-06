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
#include <keo_datagram/incentivetable/TierDescriptionListData.h>
#include <keo_datagram/incentivetable/TierDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierDescriptionListData::TierDescriptionListData()
    : CmdData(), m_tierDescriptionDataIsSet(false),
      m_tierDescriptionData(std::vector<TierDescriptionData>())

{}

TierDescriptionListData::TierDescriptionListData(
    const std::vector<TierDescriptionData> &c_tierDescriptionData) {
  setTierDescriptionData(c_tierDescriptionData);
}

bool TierDescriptionListData::
operator==(const TierDescriptionListData &c_classObject) const {
  if (m_tierDescriptionDataIsSet != c_classObject.m_tierDescriptionDataIsSet ||
      (m_tierDescriptionDataIsSet &&
       (m_tierDescriptionData != c_classObject.m_tierDescriptionData))) {
    return false;
  }

  return true;
}

bool TierDescriptionListData::
operator!=(const TierDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierDescriptionListData::isEmpty() const {
  return !m_tierDescriptionDataIsSet;
}

CmdData::Type TierDescriptionListData::getDataType() const {
  return CmdData::Type::TIER_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr TierDescriptionListData::clone() const {
  return std::make_shared<TierDescriptionListData>(*this);
}

void TierDescriptionListData::setTierDescriptionData(
    const std::vector<TierDescriptionData> &tierDescriptionData) {
  m_tierDescriptionData = tierDescriptionData;
  m_tierDescriptionDataIsSet = true;
}

const std::vector<TierDescriptionData> &
TierDescriptionListData::getTierDescriptionData() const {
  return m_tierDescriptionData;
}

void TierDescriptionListData::cleanTierDescriptionData() {
  m_tierDescriptionData.clear();
  m_tierDescriptionDataIsSet = false;
}

bool TierDescriptionListData::getTierDescriptionDataIsSet() const {
  return m_tierDescriptionDataIsSet;
}

CmdDataPtr
TierDescriptionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TierDescriptionData> dataOut;
  for (const auto &data : getTierDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TierDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TierDescriptionListDataSelectors>(
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
          const TierDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TierDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TierDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<TierDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<TierDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TierDescriptionListData>(dataOut);
  } else {
    return std::make_shared<TierDescriptionListData>();
  }
}

bool TierDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tierDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TierDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "tierDescriptionData",
            &m_tierDescriptionData)) {
      m_tierDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_tierDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TierDescriptionData>(
        "tierDescriptionData", m_tierDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram