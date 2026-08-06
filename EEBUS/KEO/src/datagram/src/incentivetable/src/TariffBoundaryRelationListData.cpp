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
#include <keo_datagram/incentivetable/TariffBoundaryRelationListData.h>
#include <keo_datagram/incentivetable/TariffBoundaryRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffBoundaryRelationListData::TariffBoundaryRelationListData()
    : CmdData(), m_tariffBoundaryRelationDataIsSet(false),
      m_tariffBoundaryRelationData(std::vector<TariffBoundaryRelationData>())

{}

TariffBoundaryRelationListData::TariffBoundaryRelationListData(
    const std::vector<TariffBoundaryRelationData>
        &c_tariffBoundaryRelationData) {
  setTariffBoundaryRelationData(c_tariffBoundaryRelationData);
}

bool TariffBoundaryRelationListData::
operator==(const TariffBoundaryRelationListData &c_classObject) const {
  if (m_tariffBoundaryRelationDataIsSet !=
          c_classObject.m_tariffBoundaryRelationDataIsSet ||
      (m_tariffBoundaryRelationDataIsSet &&
       (m_tariffBoundaryRelationData !=
        c_classObject.m_tariffBoundaryRelationData))) {
    return false;
  }

  return true;
}

bool TariffBoundaryRelationListData::
operator!=(const TariffBoundaryRelationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffBoundaryRelationListData::isEmpty() const {
  return !m_tariffBoundaryRelationDataIsSet;
}

CmdData::Type TariffBoundaryRelationListData::getDataType() const {
  return CmdData::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr TariffBoundaryRelationListData::clone() const {
  return std::make_shared<TariffBoundaryRelationListData>(*this);
}

void TariffBoundaryRelationListData::setTariffBoundaryRelationData(
    const std::vector<TariffBoundaryRelationData> &tariffBoundaryRelationData) {
  m_tariffBoundaryRelationData = tariffBoundaryRelationData;
  m_tariffBoundaryRelationDataIsSet = true;
}

const std::vector<TariffBoundaryRelationData> &
TariffBoundaryRelationListData::getTariffBoundaryRelationData() const {
  return m_tariffBoundaryRelationData;
}

void TariffBoundaryRelationListData::cleanTariffBoundaryRelationData() {
  m_tariffBoundaryRelationData.clear();
  m_tariffBoundaryRelationDataIsSet = false;
}

bool TariffBoundaryRelationListData::getTariffBoundaryRelationDataIsSet()
    const {
  return m_tariffBoundaryRelationDataIsSet;
}

CmdDataPtr TariffBoundaryRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<TariffBoundaryRelationData> dataOut;
  for (const auto &data : getTariffBoundaryRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TariffBoundaryRelationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  TariffBoundaryRelationListDataSelectors>(baseSelectorsClass);
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
          const TariffBoundaryRelationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TariffBoundaryRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TariffBoundaryRelationData(data));
          }
        }
      } else {
        return std::make_shared<TariffBoundaryRelationListData>(*this);
      }
    } else {
      return std::make_shared<TariffBoundaryRelationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TariffBoundaryRelationListData>(dataOut);
  } else {
    return std::make_shared<TariffBoundaryRelationListData>();
  }
}

bool TariffBoundaryRelationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tariffBoundaryRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TariffBoundaryRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)), "tariffBoundaryRelationData",
            &m_tariffBoundaryRelationData)) {
      m_tariffBoundaryRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffBoundaryRelationListData::toJson() const {
  std::string result = "[";
  if (m_tariffBoundaryRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TariffBoundaryRelationData>(
        "tariffBoundaryRelationData", m_tariffBoundaryRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram