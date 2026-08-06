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
#include <keo_datagram/smartenergymanagementps/PowerSequenceStateListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceStateListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceStateListData::PowerSequenceStateListData()
    : CmdData(), m_powerSequenceStateDataIsSet(false),
      m_powerSequenceStateData(std::vector<PowerSequenceStateData>())

{}

PowerSequenceStateListData::PowerSequenceStateListData(
    const std::vector<PowerSequenceStateData> &c_powerSequenceStateData) {
  setPowerSequenceStateData(c_powerSequenceStateData);
}

bool PowerSequenceStateListData::
operator==(const PowerSequenceStateListData &c_classObject) const {
  if (m_powerSequenceStateDataIsSet !=
          c_classObject.m_powerSequenceStateDataIsSet ||
      (m_powerSequenceStateDataIsSet &&
       (m_powerSequenceStateData != c_classObject.m_powerSequenceStateData))) {
    return false;
  }

  return true;
}

bool PowerSequenceStateListData::
operator!=(const PowerSequenceStateListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceStateListData::isEmpty() const {
  return !m_powerSequenceStateDataIsSet;
}

CmdData::Type PowerSequenceStateListData::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_STATE_LIST_DATA_TYPE;
}

CmdDataPtr PowerSequenceStateListData::clone() const {
  return std::make_shared<PowerSequenceStateListData>(*this);
}

void PowerSequenceStateListData::setPowerSequenceStateData(
    const std::vector<PowerSequenceStateData> &powerSequenceStateData) {
  m_powerSequenceStateData = powerSequenceStateData;
  m_powerSequenceStateDataIsSet = true;
}

const std::vector<PowerSequenceStateData> &
PowerSequenceStateListData::getPowerSequenceStateData() const {
  return m_powerSequenceStateData;
}

void PowerSequenceStateListData::cleanPowerSequenceStateData() {
  m_powerSequenceStateData.clear();
  m_powerSequenceStateDataIsSet = false;
}

bool PowerSequenceStateListData::getPowerSequenceStateDataIsSet() const {
  return m_powerSequenceStateDataIsSet;
}

CmdDataPtr
PowerSequenceStateListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<PowerSequenceStateData> dataOut;
  for (const auto &data : getPowerSequenceStateData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerSequenceStateListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<PowerSequenceStateListDataSelectors>(
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
          const PowerSequenceStateDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<PowerSequenceStateDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerSequenceStateData(data));
          }
        }
      } else {
        return std::make_shared<PowerSequenceStateListData>(*this);
      }
    } else {
      return std::make_shared<PowerSequenceStateListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerSequenceStateListData>(dataOut);
  } else {
    return std::make_shared<PowerSequenceStateListData>();
  }
}

bool PowerSequenceStateListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"powerSequenceStateData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerSequenceStateData>(
            static_cast<KeoJsonValue *>(&(*iter)), "powerSequenceStateData",
            &m_powerSequenceStateData)) {
      m_powerSequenceStateDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceStateListData::toJson() const {
  std::string result = "[";
  if (m_powerSequenceStateDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<PowerSequenceStateData>(
        "powerSequenceStateData", m_powerSequenceStateData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram