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
#include <keo_datagram/smartenergymanagementps/PowerSequencePriceListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequencePriceListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequencePriceListData::PowerSequencePriceListData()
    : CmdData(), m_powerSequencePriceDataIsSet(false),
      m_powerSequencePriceData(std::vector<PowerSequencePriceData>())

{}

PowerSequencePriceListData::PowerSequencePriceListData(
    const std::vector<PowerSequencePriceData> &c_powerSequencePriceData) {
  setPowerSequencePriceData(c_powerSequencePriceData);
}

bool PowerSequencePriceListData::
operator==(const PowerSequencePriceListData &c_classObject) const {
  if (m_powerSequencePriceDataIsSet !=
          c_classObject.m_powerSequencePriceDataIsSet ||
      (m_powerSequencePriceDataIsSet &&
       (m_powerSequencePriceData != c_classObject.m_powerSequencePriceData))) {
    return false;
  }

  return true;
}

bool PowerSequencePriceListData::
operator!=(const PowerSequencePriceListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequencePriceListData::isEmpty() const {
  return !m_powerSequencePriceDataIsSet;
}

CmdData::Type PowerSequencePriceListData::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_PRICE_LIST_DATA_TYPE;
}

CmdDataPtr PowerSequencePriceListData::clone() const {
  return std::make_shared<PowerSequencePriceListData>(*this);
}

void PowerSequencePriceListData::setPowerSequencePriceData(
    const std::vector<PowerSequencePriceData> &powerSequencePriceData) {
  m_powerSequencePriceData = powerSequencePriceData;
  m_powerSequencePriceDataIsSet = true;
}

const std::vector<PowerSequencePriceData> &
PowerSequencePriceListData::getPowerSequencePriceData() const {
  return m_powerSequencePriceData;
}

void PowerSequencePriceListData::cleanPowerSequencePriceData() {
  m_powerSequencePriceData.clear();
  m_powerSequencePriceDataIsSet = false;
}

bool PowerSequencePriceListData::getPowerSequencePriceDataIsSet() const {
  return m_powerSequencePriceDataIsSet;
}

CmdDataPtr
PowerSequencePriceListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<PowerSequencePriceData> dataOut;
  for (const auto &data : getPowerSequencePriceData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerSequencePriceListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<PowerSequencePriceListDataSelectors>(
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
          const PowerSequencePriceDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<PowerSequencePriceDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerSequencePriceData(data));
          }
        }
      } else {
        return std::make_shared<PowerSequencePriceListData>(*this);
      }
    } else {
      return std::make_shared<PowerSequencePriceListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerSequencePriceListData>(dataOut);
  } else {
    return std::make_shared<PowerSequencePriceListData>();
  }
}

bool PowerSequencePriceListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"powerSequencePriceData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerSequencePriceData>(
            static_cast<KeoJsonValue *>(&(*iter)), "powerSequencePriceData",
            &m_powerSequencePriceData)) {
      m_powerSequencePriceDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequencePriceListData::toJson() const {
  std::string result = "[";
  if (m_powerSequencePriceDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<PowerSequencePriceData>(
        "powerSequencePriceData", m_powerSequencePriceData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram