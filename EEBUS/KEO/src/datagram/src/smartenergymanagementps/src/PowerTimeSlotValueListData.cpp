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
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueListData.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotValueListData::PowerTimeSlotValueListData()
    : CmdData(), m_powerTimeSlotValueDataIsSet(false),
      m_powerTimeSlotValueData(std::vector<PowerTimeSlotValueData>())

{}

PowerTimeSlotValueListData::PowerTimeSlotValueListData(
    const std::vector<PowerTimeSlotValueData> &c_powerTimeSlotValueData) {
  setPowerTimeSlotValueData(c_powerTimeSlotValueData);
}

bool PowerTimeSlotValueListData::
operator==(const PowerTimeSlotValueListData &c_classObject) const {
  if (m_powerTimeSlotValueDataIsSet !=
          c_classObject.m_powerTimeSlotValueDataIsSet ||
      (m_powerTimeSlotValueDataIsSet &&
       (m_powerTimeSlotValueData != c_classObject.m_powerTimeSlotValueData))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotValueListData::
operator!=(const PowerTimeSlotValueListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotValueListData::isEmpty() const {
  return !m_powerTimeSlotValueDataIsSet;
}

CmdData::Type PowerTimeSlotValueListData::getDataType() const {
  return CmdData::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_TYPE;
}

CmdDataPtr PowerTimeSlotValueListData::clone() const {
  return std::make_shared<PowerTimeSlotValueListData>(*this);
}

void PowerTimeSlotValueListData::setPowerTimeSlotValueData(
    const std::vector<PowerTimeSlotValueData> &powerTimeSlotValueData) {
  m_powerTimeSlotValueData = powerTimeSlotValueData;
  m_powerTimeSlotValueDataIsSet = true;
}

const std::vector<PowerTimeSlotValueData> &
PowerTimeSlotValueListData::getPowerTimeSlotValueData() const {
  return m_powerTimeSlotValueData;
}

void PowerTimeSlotValueListData::cleanPowerTimeSlotValueData() {
  m_powerTimeSlotValueData.clear();
  m_powerTimeSlotValueDataIsSet = false;
}

bool PowerTimeSlotValueListData::getPowerTimeSlotValueDataIsSet() const {
  return m_powerTimeSlotValueDataIsSet;
}

CmdDataPtr
PowerTimeSlotValueListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<PowerTimeSlotValueData> dataOut;
  for (const auto &data : getPowerTimeSlotValueData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerTimeSlotValueListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<PowerTimeSlotValueListDataSelectors>(
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
          const PowerTimeSlotValueDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<PowerTimeSlotValueDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerTimeSlotValueData(data));
          }
        }
      } else {
        return std::make_shared<PowerTimeSlotValueListData>(*this);
      }
    } else {
      return std::make_shared<PowerTimeSlotValueListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerTimeSlotValueListData>(dataOut);
  } else {
    return std::make_shared<PowerTimeSlotValueListData>();
  }
}

bool PowerTimeSlotValueListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"powerTimeSlotValueData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerTimeSlotValueData>(
            static_cast<KeoJsonValue *>(&(*iter)), "powerTimeSlotValueData",
            &m_powerTimeSlotValueData)) {
      m_powerTimeSlotValueDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerTimeSlotValueListData::toJson() const {
  std::string result = "[";
  if (m_powerTimeSlotValueDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<PowerTimeSlotValueData>(
        "powerTimeSlotValueData", m_powerTimeSlotValueData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram