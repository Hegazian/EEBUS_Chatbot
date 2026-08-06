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
#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceSchedulePreferenceListData::
    PowerSequenceSchedulePreferenceListData()
    : CmdData(), m_powerSequenceSchedulePreferenceDataIsSet(false),
      m_powerSequenceSchedulePreferenceData(
          std::vector<PowerSequenceSchedulePreferenceData>())

{}

PowerSequenceSchedulePreferenceListData::
    PowerSequenceSchedulePreferenceListData(
        const std::vector<PowerSequenceSchedulePreferenceData>
            &c_powerSequenceSchedulePreferenceData) {
  setPowerSequenceSchedulePreferenceData(c_powerSequenceSchedulePreferenceData);
}

bool PowerSequenceSchedulePreferenceListData::
operator==(const PowerSequenceSchedulePreferenceListData &c_classObject) const {
  if (m_powerSequenceSchedulePreferenceDataIsSet !=
          c_classObject.m_powerSequenceSchedulePreferenceDataIsSet ||
      (m_powerSequenceSchedulePreferenceDataIsSet &&
       (m_powerSequenceSchedulePreferenceData !=
        c_classObject.m_powerSequenceSchedulePreferenceData))) {
    return false;
  }

  return true;
}

bool PowerSequenceSchedulePreferenceListData::
operator!=(const PowerSequenceSchedulePreferenceListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceSchedulePreferenceListData::isEmpty() const {
  return !m_powerSequenceSchedulePreferenceDataIsSet;
}

CmdData::Type PowerSequenceSchedulePreferenceListData::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_TYPE;
}

CmdDataPtr PowerSequenceSchedulePreferenceListData::clone() const {
  return std::make_shared<PowerSequenceSchedulePreferenceListData>(*this);
}

void PowerSequenceSchedulePreferenceListData::
    setPowerSequenceSchedulePreferenceData(
        const std::vector<PowerSequenceSchedulePreferenceData>
            &powerSequenceSchedulePreferenceData) {
  m_powerSequenceSchedulePreferenceData = powerSequenceSchedulePreferenceData;
  m_powerSequenceSchedulePreferenceDataIsSet = true;
}

const std::vector<PowerSequenceSchedulePreferenceData> &
PowerSequenceSchedulePreferenceListData::
    getPowerSequenceSchedulePreferenceData() const {
  return m_powerSequenceSchedulePreferenceData;
}

void PowerSequenceSchedulePreferenceListData::
    cleanPowerSequenceSchedulePreferenceData() {
  m_powerSequenceSchedulePreferenceData.clear();
  m_powerSequenceSchedulePreferenceDataIsSet = false;
}

bool PowerSequenceSchedulePreferenceListData::
    getPowerSequenceSchedulePreferenceDataIsSet() const {
  return m_powerSequenceSchedulePreferenceDataIsSet;
}

CmdDataPtr PowerSequenceSchedulePreferenceListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<PowerSequenceSchedulePreferenceData> dataOut;
  for (const auto &data : getPowerSequenceSchedulePreferenceData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerSequenceSchedulePreferenceListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  PowerSequenceSchedulePreferenceListDataSelectors>(
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
          const PowerSequenceSchedulePreferenceDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  PowerSequenceSchedulePreferenceDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerSequenceSchedulePreferenceData(data));
          }
        }
      } else {
        return std::make_shared<PowerSequenceSchedulePreferenceListData>(*this);
      }
    } else {
      return std::make_shared<PowerSequenceSchedulePreferenceListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerSequenceSchedulePreferenceListData>(dataOut);
  } else {
    return std::make_shared<PowerSequenceSchedulePreferenceListData>();
  }
}

bool PowerSequenceSchedulePreferenceListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"powerSequenceSchedulePreferenceData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerSequenceSchedulePreferenceData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "powerSequenceSchedulePreferenceData",
            &m_powerSequenceSchedulePreferenceData)) {
      m_powerSequenceSchedulePreferenceDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceSchedulePreferenceListData::toJson() const {
  std::string result = "[";
  if (m_powerSequenceSchedulePreferenceDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<PowerSequenceSchedulePreferenceData>(
            "powerSequenceSchedulePreferenceData",
            m_powerSequenceSchedulePreferenceData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram