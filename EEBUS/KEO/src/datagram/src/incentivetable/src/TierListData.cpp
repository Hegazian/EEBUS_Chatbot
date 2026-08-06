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
#include <keo_datagram/incentivetable/TierListData.h>
#include <keo_datagram/incentivetable/TierListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierListData::TierListData()
    : CmdData(), m_tierDataIsSet(false), m_tierData(std::vector<TierData>())

{}

TierListData::TierListData(const std::vector<TierData> &c_tierData) {
  setTierData(c_tierData);
}

bool TierListData::operator==(const TierListData &c_classObject) const {
  if (m_tierDataIsSet != c_classObject.m_tierDataIsSet ||
      (m_tierDataIsSet && (m_tierData != c_classObject.m_tierData))) {
    return false;
  }

  return true;
}

bool TierListData::operator!=(const TierListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierListData::isEmpty() const { return !m_tierDataIsSet; }

CmdData::Type TierListData::getDataType() const {
  return CmdData::Type::TIER_LIST_DATA_TYPE;
}

CmdDataPtr TierListData::clone() const {
  return std::make_shared<TierListData>(*this);
}

void TierListData::setTierData(const std::vector<TierData> &tierData) {
  m_tierData = tierData;
  m_tierDataIsSet = true;
}

const std::vector<TierData> &TierListData::getTierData() const {
  return m_tierData;
}

void TierListData::cleanTierData() {
  m_tierData.clear();
  m_tierDataIsSet = false;
}

bool TierListData::getTierDataIsSet() const { return m_tierDataIsSet; }

CmdDataPtr TierListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TierData> dataOut;
  for (const auto &data : getTierData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TierListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TierListDataSelectors>(
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
          const TierDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TierDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TierData(data));
          }
        }
      } else {
        return std::make_shared<TierListData>(*this);
      }
    } else {
      return std::make_shared<TierListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TierListData>(dataOut);
  } else {
    return std::make_shared<TierListData>();
  }
}

bool TierListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tierData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TierData>(
            static_cast<KeoJsonValue *>(&(*iter)), "tierData", &m_tierData)) {
      m_tierDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierListData::toJson() const {
  std::string result = "[";
  if (m_tierDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<TierData>("tierData", m_tierData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram