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
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceScheduleConstraintsListData::
    PowerSequenceScheduleConstraintsListData()
    : CmdData(), m_powerSequenceScheduleConstraintsDataIsSet(false),
      m_powerSequenceScheduleConstraintsData(
          std::vector<PowerSequenceScheduleConstraintsData>())

{}

PowerSequenceScheduleConstraintsListData::
    PowerSequenceScheduleConstraintsListData(
        const std::vector<PowerSequenceScheduleConstraintsData>
            &c_powerSequenceScheduleConstraintsData) {
  setPowerSequenceScheduleConstraintsData(
      c_powerSequenceScheduleConstraintsData);
}

bool PowerSequenceScheduleConstraintsListData::operator==(
    const PowerSequenceScheduleConstraintsListData &c_classObject) const {
  if (m_powerSequenceScheduleConstraintsDataIsSet !=
          c_classObject.m_powerSequenceScheduleConstraintsDataIsSet ||
      (m_powerSequenceScheduleConstraintsDataIsSet &&
       (m_powerSequenceScheduleConstraintsData !=
        c_classObject.m_powerSequenceScheduleConstraintsData))) {
    return false;
  }

  return true;
}

bool PowerSequenceScheduleConstraintsListData::operator!=(
    const PowerSequenceScheduleConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceScheduleConstraintsListData::isEmpty() const {
  return !m_powerSequenceScheduleConstraintsDataIsSet;
}

CmdData::Type PowerSequenceScheduleConstraintsListData::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr PowerSequenceScheduleConstraintsListData::clone() const {
  return std::make_shared<PowerSequenceScheduleConstraintsListData>(*this);
}

void PowerSequenceScheduleConstraintsListData::
    setPowerSequenceScheduleConstraintsData(
        const std::vector<PowerSequenceScheduleConstraintsData>
            &powerSequenceScheduleConstraintsData) {
  m_powerSequenceScheduleConstraintsData = powerSequenceScheduleConstraintsData;
  m_powerSequenceScheduleConstraintsDataIsSet = true;
}

const std::vector<PowerSequenceScheduleConstraintsData> &
PowerSequenceScheduleConstraintsListData::
    getPowerSequenceScheduleConstraintsData() const {
  return m_powerSequenceScheduleConstraintsData;
}

void PowerSequenceScheduleConstraintsListData::
    cleanPowerSequenceScheduleConstraintsData() {
  m_powerSequenceScheduleConstraintsData.clear();
  m_powerSequenceScheduleConstraintsDataIsSet = false;
}

bool PowerSequenceScheduleConstraintsListData::
    getPowerSequenceScheduleConstraintsDataIsSet() const {
  return m_powerSequenceScheduleConstraintsDataIsSet;
}

CmdDataPtr PowerSequenceScheduleConstraintsListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<PowerSequenceScheduleConstraintsData> dataOut;
  for (const auto &data : getPowerSequenceScheduleConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerSequenceScheduleConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  PowerSequenceScheduleConstraintsListDataSelectors>(
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
          const PowerSequenceScheduleConstraintsDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  PowerSequenceScheduleConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerSequenceScheduleConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<PowerSequenceScheduleConstraintsListData>(
            *this);
      }
    } else {
      return std::make_shared<PowerSequenceScheduleConstraintsListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerSequenceScheduleConstraintsListData>(dataOut);
  } else {
    return std::make_shared<PowerSequenceScheduleConstraintsListData>();
  }
}

bool PowerSequenceScheduleConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"powerSequenceScheduleConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerSequenceScheduleConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "powerSequenceScheduleConstraintsData",
            &m_powerSequenceScheduleConstraintsData)) {
      m_powerSequenceScheduleConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceScheduleConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_powerSequenceScheduleConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<PowerSequenceScheduleConstraintsData>(
            "powerSequenceScheduleConstraintsData",
            m_powerSequenceScheduleConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram