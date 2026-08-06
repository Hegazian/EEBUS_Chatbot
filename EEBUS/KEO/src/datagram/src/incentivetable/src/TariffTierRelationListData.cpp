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
#include <keo_datagram/incentivetable/TariffTierRelationListData.h>
#include <keo_datagram/incentivetable/TariffTierRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffTierRelationListData::TariffTierRelationListData()
    : CmdData(), m_tariffTierRelationDataIsSet(false),
      m_tariffTierRelationData(std::vector<TariffTierRelationData>())

{}

TariffTierRelationListData::TariffTierRelationListData(
    const std::vector<TariffTierRelationData> &c_tariffTierRelationData) {
  setTariffTierRelationData(c_tariffTierRelationData);
}

bool TariffTierRelationListData::
operator==(const TariffTierRelationListData &c_classObject) const {
  if (m_tariffTierRelationDataIsSet !=
          c_classObject.m_tariffTierRelationDataIsSet ||
      (m_tariffTierRelationDataIsSet &&
       (m_tariffTierRelationData != c_classObject.m_tariffTierRelationData))) {
    return false;
  }

  return true;
}

bool TariffTierRelationListData::
operator!=(const TariffTierRelationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffTierRelationListData::isEmpty() const {
  return !m_tariffTierRelationDataIsSet;
}

CmdData::Type TariffTierRelationListData::getDataType() const {
  return CmdData::Type::TARIFF_TIER_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr TariffTierRelationListData::clone() const {
  return std::make_shared<TariffTierRelationListData>(*this);
}

void TariffTierRelationListData::setTariffTierRelationData(
    const std::vector<TariffTierRelationData> &tariffTierRelationData) {
  m_tariffTierRelationData = tariffTierRelationData;
  m_tariffTierRelationDataIsSet = true;
}

const std::vector<TariffTierRelationData> &
TariffTierRelationListData::getTariffTierRelationData() const {
  return m_tariffTierRelationData;
}

void TariffTierRelationListData::cleanTariffTierRelationData() {
  m_tariffTierRelationData.clear();
  m_tariffTierRelationDataIsSet = false;
}

bool TariffTierRelationListData::getTariffTierRelationDataIsSet() const {
  return m_tariffTierRelationDataIsSet;
}

CmdDataPtr
TariffTierRelationListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TariffTierRelationData> dataOut;
  for (const auto &data : getTariffTierRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TariffTierRelationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TariffTierRelationListDataSelectors>(
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
          const TariffTierRelationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TariffTierRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TariffTierRelationData(data));
          }
        }
      } else {
        return std::make_shared<TariffTierRelationListData>(*this);
      }
    } else {
      return std::make_shared<TariffTierRelationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TariffTierRelationListData>(dataOut);
  } else {
    return std::make_shared<TariffTierRelationListData>();
  }
}

bool TariffTierRelationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tariffTierRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TariffTierRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)), "tariffTierRelationData",
            &m_tariffTierRelationData)) {
      m_tariffTierRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffTierRelationListData::toJson() const {
  std::string result = "[";
  if (m_tariffTierRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TariffTierRelationData>(
        "tariffTierRelationData", m_tariffTierRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram