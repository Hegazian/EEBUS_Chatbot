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
#include <keo_datagram/incentivetable/TariffDescriptionListData.h>
#include <keo_datagram/incentivetable/TariffDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffDescriptionListData::TariffDescriptionListData()
    : CmdData(), m_tariffDescriptionDataIsSet(false),
      m_tariffDescriptionData(std::vector<TariffDescriptionData>())

{}

TariffDescriptionListData::TariffDescriptionListData(
    const std::vector<TariffDescriptionData> &c_tariffDescriptionData) {
  setTariffDescriptionData(c_tariffDescriptionData);
}

bool TariffDescriptionListData::
operator==(const TariffDescriptionListData &c_classObject) const {
  if (m_tariffDescriptionDataIsSet !=
          c_classObject.m_tariffDescriptionDataIsSet ||
      (m_tariffDescriptionDataIsSet &&
       (m_tariffDescriptionData != c_classObject.m_tariffDescriptionData))) {
    return false;
  }

  return true;
}

bool TariffDescriptionListData::
operator!=(const TariffDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffDescriptionListData::isEmpty() const {
  return !m_tariffDescriptionDataIsSet;
}

CmdData::Type TariffDescriptionListData::getDataType() const {
  return CmdData::Type::TARIFF_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr TariffDescriptionListData::clone() const {
  return std::make_shared<TariffDescriptionListData>(*this);
}

void TariffDescriptionListData::setTariffDescriptionData(
    const std::vector<TariffDescriptionData> &tariffDescriptionData) {
  m_tariffDescriptionData = tariffDescriptionData;
  m_tariffDescriptionDataIsSet = true;
}

const std::vector<TariffDescriptionData> &
TariffDescriptionListData::getTariffDescriptionData() const {
  return m_tariffDescriptionData;
}

void TariffDescriptionListData::cleanTariffDescriptionData() {
  m_tariffDescriptionData.clear();
  m_tariffDescriptionDataIsSet = false;
}

bool TariffDescriptionListData::getTariffDescriptionDataIsSet() const {
  return m_tariffDescriptionDataIsSet;
}

CmdDataPtr
TariffDescriptionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TariffDescriptionData> dataOut;
  for (const auto &data : getTariffDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TariffDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TariffDescriptionListDataSelectors>(
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
          const TariffDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TariffDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TariffDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<TariffDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<TariffDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TariffDescriptionListData>(dataOut);
  } else {
    return std::make_shared<TariffDescriptionListData>();
  }
}

bool TariffDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tariffDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TariffDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "tariffDescriptionData",
            &m_tariffDescriptionData)) {
      m_tariffDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_tariffDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TariffDescriptionData>(
        "tariffDescriptionData", m_tariffDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram