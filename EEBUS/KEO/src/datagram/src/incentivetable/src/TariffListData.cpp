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
#include <keo_datagram/incentivetable/TariffListData.h>
#include <keo_datagram/incentivetable/TariffListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffListData::TariffListData()
    : CmdData(), m_tariffDataIsSet(false),
      m_tariffData(std::vector<TariffData>())

{}

TariffListData::TariffListData(const std::vector<TariffData> &c_tariffData) {
  setTariffData(c_tariffData);
}

bool TariffListData::operator==(const TariffListData &c_classObject) const {
  if (m_tariffDataIsSet != c_classObject.m_tariffDataIsSet ||
      (m_tariffDataIsSet && (m_tariffData != c_classObject.m_tariffData))) {
    return false;
  }

  return true;
}

bool TariffListData::operator!=(const TariffListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffListData::isEmpty() const { return !m_tariffDataIsSet; }

CmdData::Type TariffListData::getDataType() const {
  return CmdData::Type::TARIFF_LIST_DATA_TYPE;
}

CmdDataPtr TariffListData::clone() const {
  return std::make_shared<TariffListData>(*this);
}

void TariffListData::setTariffData(const std::vector<TariffData> &tariffData) {
  m_tariffData = tariffData;
  m_tariffDataIsSet = true;
}

const std::vector<TariffData> &TariffListData::getTariffData() const {
  return m_tariffData;
}

void TariffListData::cleanTariffData() {
  m_tariffData.clear();
  m_tariffDataIsSet = false;
}

bool TariffListData::getTariffDataIsSet() const { return m_tariffDataIsSet; }

CmdDataPtr TariffListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TariffData> dataOut;
  for (const auto &data : getTariffData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TariffListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TariffListDataSelectors>(
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
          const TariffDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TariffDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TariffData(data));
          }
        }
      } else {
        return std::make_shared<TariffListData>(*this);
      }
    } else {
      return std::make_shared<TariffListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TariffListData>(dataOut);
  } else {
    return std::make_shared<TariffListData>();
  }
}

bool TariffListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tariffData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<TariffData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariffData", &m_tariffData)) {
      m_tariffDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffListData::toJson() const {
  std::string result = "[";
  if (m_tariffDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TariffData>("tariffData",
                                                           m_tariffData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram