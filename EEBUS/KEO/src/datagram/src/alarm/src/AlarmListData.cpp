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
#include <keo_datagram/alarm/AlarmListData.h>
#include <keo_datagram/alarm/AlarmListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

AlarmListData::AlarmListData()
    : CmdData(), m_alarmDataIsSet(false), m_alarmData(std::vector<AlarmData>())

{}

AlarmListData::AlarmListData(const std::vector<AlarmData> &c_alarmData) {
  setAlarmData(c_alarmData);
}

bool AlarmListData::operator==(const AlarmListData &c_classObject) const {
  if (m_alarmDataIsSet != c_classObject.m_alarmDataIsSet ||
      (m_alarmDataIsSet && (m_alarmData != c_classObject.m_alarmData))) {
    return false;
  }

  return true;
}

bool AlarmListData::operator!=(const AlarmListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool AlarmListData::isEmpty() const { return !m_alarmDataIsSet; }

CmdData::Type AlarmListData::getDataType() const {
  return CmdData::Type::ALARM_LIST_DATA_TYPE;
}

CmdDataPtr AlarmListData::clone() const {
  return std::make_shared<AlarmListData>(*this);
}

void AlarmListData::setAlarmData(const std::vector<AlarmData> &alarmData) {
  m_alarmData = alarmData;
  m_alarmDataIsSet = true;
}

const std::vector<AlarmData> &AlarmListData::getAlarmData() const {
  return m_alarmData;
}

void AlarmListData::cleanAlarmData() {
  m_alarmData.clear();
  m_alarmDataIsSet = false;
}

bool AlarmListData::getAlarmDataIsSet() const { return m_alarmDataIsSet; }

CmdDataPtr AlarmListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<AlarmData> dataOut;
  for (const auto &data : getAlarmData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          AlarmListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<AlarmListDataSelectors>(
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
          const AlarmDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<AlarmDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(AlarmData(data));
          }
        }
      } else {
        return std::make_shared<AlarmListData>(*this);
      }
    } else {
      return std::make_shared<AlarmListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<AlarmListData>(dataOut);
  } else {
    return std::make_shared<AlarmListData>();
  }
}

bool AlarmListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"alarmData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<AlarmData>(
            static_cast<KeoJsonValue *>(&(*iter)), "alarmData", &m_alarmData)) {
      m_alarmDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string AlarmListData::toJson() const {
  std::string result = "[";
  if (m_alarmDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<AlarmData>("alarmData", m_alarmData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram