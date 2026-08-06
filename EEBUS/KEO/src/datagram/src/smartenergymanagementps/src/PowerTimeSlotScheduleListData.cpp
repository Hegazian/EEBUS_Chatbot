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
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleListData.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotScheduleListData::PowerTimeSlotScheduleListData()
    : CmdData(), m_powerTimeSlotScheduleDataIsSet(false),
      m_powerTimeSlotScheduleData(std::vector<PowerTimeSlotScheduleData>())

{}

PowerTimeSlotScheduleListData::PowerTimeSlotScheduleListData(
    const std::vector<PowerTimeSlotScheduleData> &c_powerTimeSlotScheduleData) {
  setPowerTimeSlotScheduleData(c_powerTimeSlotScheduleData);
}

bool PowerTimeSlotScheduleListData::
operator==(const PowerTimeSlotScheduleListData &c_classObject) const {
  if (m_powerTimeSlotScheduleDataIsSet !=
          c_classObject.m_powerTimeSlotScheduleDataIsSet ||
      (m_powerTimeSlotScheduleDataIsSet &&
       (m_powerTimeSlotScheduleData !=
        c_classObject.m_powerTimeSlotScheduleData))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotScheduleListData::
operator!=(const PowerTimeSlotScheduleListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotScheduleListData::isEmpty() const {
  return !m_powerTimeSlotScheduleDataIsSet;
}

CmdData::Type PowerTimeSlotScheduleListData::getDataType() const {
  return CmdData::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_TYPE;
}

CmdDataPtr PowerTimeSlotScheduleListData::clone() const {
  return std::make_shared<PowerTimeSlotScheduleListData>(*this);
}

void PowerTimeSlotScheduleListData::setPowerTimeSlotScheduleData(
    const std::vector<PowerTimeSlotScheduleData> &powerTimeSlotScheduleData) {
  m_powerTimeSlotScheduleData = powerTimeSlotScheduleData;
  m_powerTimeSlotScheduleDataIsSet = true;
}

const std::vector<PowerTimeSlotScheduleData> &
PowerTimeSlotScheduleListData::getPowerTimeSlotScheduleData() const {
  return m_powerTimeSlotScheduleData;
}

void PowerTimeSlotScheduleListData::cleanPowerTimeSlotScheduleData() {
  m_powerTimeSlotScheduleData.clear();
  m_powerTimeSlotScheduleDataIsSet = false;
}

bool PowerTimeSlotScheduleListData::getPowerTimeSlotScheduleDataIsSet() const {
  return m_powerTimeSlotScheduleDataIsSet;
}

CmdDataPtr PowerTimeSlotScheduleListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<PowerTimeSlotScheduleData> dataOut;
  for (const auto &data : getPowerTimeSlotScheduleData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerTimeSlotScheduleListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<PowerTimeSlotScheduleListDataSelectors>(
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
          const PowerTimeSlotScheduleDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<PowerTimeSlotScheduleDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerTimeSlotScheduleData(data));
          }
        }
      } else {
        return std::make_shared<PowerTimeSlotScheduleListData>(*this);
      }
    } else {
      return std::make_shared<PowerTimeSlotScheduleListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerTimeSlotScheduleListData>(dataOut);
  } else {
    return std::make_shared<PowerTimeSlotScheduleListData>();
  }
}

bool PowerTimeSlotScheduleListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"powerTimeSlotScheduleData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerTimeSlotScheduleData>(
            static_cast<KeoJsonValue *>(&(*iter)), "powerTimeSlotScheduleData",
            &m_powerTimeSlotScheduleData)) {
      m_powerTimeSlotScheduleDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerTimeSlotScheduleListData::toJson() const {
  std::string result = "[";
  if (m_powerTimeSlotScheduleDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<PowerTimeSlotScheduleData>(
        "powerTimeSlotScheduleData", m_powerTimeSlotScheduleData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram