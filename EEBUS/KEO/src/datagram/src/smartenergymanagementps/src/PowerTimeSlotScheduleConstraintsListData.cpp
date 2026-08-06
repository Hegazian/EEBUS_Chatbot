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
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsListData.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerTimeSlotScheduleConstraintsListData::
    PowerTimeSlotScheduleConstraintsListData()
    : CmdData(), m_powerTimeSlotScheduleConstraintsDataIsSet(false),
      m_powerTimeSlotScheduleConstraintsData(
          std::vector<PowerTimeSlotScheduleConstraintsData>())

{}

PowerTimeSlotScheduleConstraintsListData::
    PowerTimeSlotScheduleConstraintsListData(
        const std::vector<PowerTimeSlotScheduleConstraintsData>
            &c_powerTimeSlotScheduleConstraintsData) {
  setPowerTimeSlotScheduleConstraintsData(
      c_powerTimeSlotScheduleConstraintsData);
}

bool PowerTimeSlotScheduleConstraintsListData::operator==(
    const PowerTimeSlotScheduleConstraintsListData &c_classObject) const {
  if (m_powerTimeSlotScheduleConstraintsDataIsSet !=
          c_classObject.m_powerTimeSlotScheduleConstraintsDataIsSet ||
      (m_powerTimeSlotScheduleConstraintsDataIsSet &&
       (m_powerTimeSlotScheduleConstraintsData !=
        c_classObject.m_powerTimeSlotScheduleConstraintsData))) {
    return false;
  }

  return true;
}

bool PowerTimeSlotScheduleConstraintsListData::operator!=(
    const PowerTimeSlotScheduleConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerTimeSlotScheduleConstraintsListData::isEmpty() const {
  return !m_powerTimeSlotScheduleConstraintsDataIsSet;
}

CmdData::Type PowerTimeSlotScheduleConstraintsListData::getDataType() const {
  return CmdData::Type::POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr PowerTimeSlotScheduleConstraintsListData::clone() const {
  return std::make_shared<PowerTimeSlotScheduleConstraintsListData>(*this);
}

void PowerTimeSlotScheduleConstraintsListData::
    setPowerTimeSlotScheduleConstraintsData(
        const std::vector<PowerTimeSlotScheduleConstraintsData>
            &powerTimeSlotScheduleConstraintsData) {
  m_powerTimeSlotScheduleConstraintsData = powerTimeSlotScheduleConstraintsData;
  m_powerTimeSlotScheduleConstraintsDataIsSet = true;
}

const std::vector<PowerTimeSlotScheduleConstraintsData> &
PowerTimeSlotScheduleConstraintsListData::
    getPowerTimeSlotScheduleConstraintsData() const {
  return m_powerTimeSlotScheduleConstraintsData;
}

void PowerTimeSlotScheduleConstraintsListData::
    cleanPowerTimeSlotScheduleConstraintsData() {
  m_powerTimeSlotScheduleConstraintsData.clear();
  m_powerTimeSlotScheduleConstraintsDataIsSet = false;
}

bool PowerTimeSlotScheduleConstraintsListData::
    getPowerTimeSlotScheduleConstraintsDataIsSet() const {
  return m_powerTimeSlotScheduleConstraintsDataIsSet;
}

CmdDataPtr PowerTimeSlotScheduleConstraintsListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<PowerTimeSlotScheduleConstraintsData> dataOut;
  for (const auto &data : getPowerTimeSlotScheduleConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerTimeSlotScheduleConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  PowerTimeSlotScheduleConstraintsListDataSelectors>(
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
          const PowerTimeSlotScheduleConstraintsDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  PowerTimeSlotScheduleConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerTimeSlotScheduleConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<PowerTimeSlotScheduleConstraintsListData>(
            *this);
      }
    } else {
      return std::make_shared<PowerTimeSlotScheduleConstraintsListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerTimeSlotScheduleConstraintsListData>(dataOut);
  } else {
    return std::make_shared<PowerTimeSlotScheduleConstraintsListData>();
  }
}

bool PowerTimeSlotScheduleConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"powerTimeSlotScheduleConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerTimeSlotScheduleConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "powerTimeSlotScheduleConstraintsData",
            &m_powerTimeSlotScheduleConstraintsData)) {
      m_powerTimeSlotScheduleConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerTimeSlotScheduleConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_powerTimeSlotScheduleConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<PowerTimeSlotScheduleConstraintsData>(
            "powerTimeSlotScheduleConstraintsData",
            m_powerTimeSlotScheduleConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram