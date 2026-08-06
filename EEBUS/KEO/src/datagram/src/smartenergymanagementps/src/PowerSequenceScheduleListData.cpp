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
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceScheduleListData::PowerSequenceScheduleListData()
    : CmdData(), m_powerSequenceScheduleDataIsSet(false),
      m_powerSequenceScheduleData(std::vector<PowerSequenceScheduleData>())

{}

PowerSequenceScheduleListData::PowerSequenceScheduleListData(
    const std::vector<PowerSequenceScheduleData> &c_powerSequenceScheduleData) {
  setPowerSequenceScheduleData(c_powerSequenceScheduleData);
}

bool PowerSequenceScheduleListData::
operator==(const PowerSequenceScheduleListData &c_classObject) const {
  if (m_powerSequenceScheduleDataIsSet !=
          c_classObject.m_powerSequenceScheduleDataIsSet ||
      (m_powerSequenceScheduleDataIsSet &&
       (m_powerSequenceScheduleData !=
        c_classObject.m_powerSequenceScheduleData))) {
    return false;
  }

  return true;
}

bool PowerSequenceScheduleListData::
operator!=(const PowerSequenceScheduleListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceScheduleListData::isEmpty() const {
  return !m_powerSequenceScheduleDataIsSet;
}

CmdData::Type PowerSequenceScheduleListData::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_TYPE;
}

CmdDataPtr PowerSequenceScheduleListData::clone() const {
  return std::make_shared<PowerSequenceScheduleListData>(*this);
}

void PowerSequenceScheduleListData::setPowerSequenceScheduleData(
    const std::vector<PowerSequenceScheduleData> &powerSequenceScheduleData) {
  m_powerSequenceScheduleData = powerSequenceScheduleData;
  m_powerSequenceScheduleDataIsSet = true;
}

const std::vector<PowerSequenceScheduleData> &
PowerSequenceScheduleListData::getPowerSequenceScheduleData() const {
  return m_powerSequenceScheduleData;
}

void PowerSequenceScheduleListData::cleanPowerSequenceScheduleData() {
  m_powerSequenceScheduleData.clear();
  m_powerSequenceScheduleDataIsSet = false;
}

bool PowerSequenceScheduleListData::getPowerSequenceScheduleDataIsSet() const {
  return m_powerSequenceScheduleDataIsSet;
}

CmdDataPtr PowerSequenceScheduleListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<PowerSequenceScheduleData> dataOut;
  for (const auto &data : getPowerSequenceScheduleData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerSequenceScheduleListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<PowerSequenceScheduleListDataSelectors>(
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
          const PowerSequenceScheduleDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<PowerSequenceScheduleDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerSequenceScheduleData(data));
          }
        }
      } else {
        return std::make_shared<PowerSequenceScheduleListData>(*this);
      }
    } else {
      return std::make_shared<PowerSequenceScheduleListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerSequenceScheduleListData>(dataOut);
  } else {
    return std::make_shared<PowerSequenceScheduleListData>();
  }
}

bool PowerSequenceScheduleListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"powerSequenceScheduleData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerSequenceScheduleData>(
            static_cast<KeoJsonValue *>(&(*iter)), "powerSequenceScheduleData",
            &m_powerSequenceScheduleData)) {
      m_powerSequenceScheduleDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceScheduleListData::toJson() const {
  std::string result = "[";
  if (m_powerSequenceScheduleDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<PowerSequenceScheduleData>(
        "powerSequenceScheduleData", m_powerSequenceScheduleData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram