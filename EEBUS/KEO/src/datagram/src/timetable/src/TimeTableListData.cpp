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
#include <keo_datagram/timetable/TimeTableListData.h>
#include <keo_datagram/timetable/TimeTableListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableListData::TimeTableListData()
    : CmdData(), m_timeTableDataIsSet(false),
      m_timeTableData(std::vector<TimeTableData>())

{}

TimeTableListData::TimeTableListData(
    const std::vector<TimeTableData> &c_timeTableData) {
  setTimeTableData(c_timeTableData);
}

bool TimeTableListData::
operator==(const TimeTableListData &c_classObject) const {
  if (m_timeTableDataIsSet != c_classObject.m_timeTableDataIsSet ||
      (m_timeTableDataIsSet &&
       (m_timeTableData != c_classObject.m_timeTableData))) {
    return false;
  }

  return true;
}

bool TimeTableListData::
operator!=(const TimeTableListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableListData::isEmpty() const { return !m_timeTableDataIsSet; }

CmdData::Type TimeTableListData::getDataType() const {
  return CmdData::Type::TIME_TABLE_LIST_DATA_TYPE;
}

CmdDataPtr TimeTableListData::clone() const {
  return std::make_shared<TimeTableListData>(*this);
}

void TimeTableListData::setTimeTableData(
    const std::vector<TimeTableData> &timeTableData) {
  m_timeTableData = timeTableData;
  m_timeTableDataIsSet = true;
}

const std::vector<TimeTableData> &TimeTableListData::getTimeTableData() const {
  return m_timeTableData;
}

void TimeTableListData::cleanTimeTableData() {
  m_timeTableData.clear();
  m_timeTableDataIsSet = false;
}

bool TimeTableListData::getTimeTableDataIsSet() const {
  return m_timeTableDataIsSet;
}

CmdDataPtr TimeTableListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TimeTableData> dataOut;
  for (const auto &data : getTimeTableData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TimeTableListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TimeTableListDataSelectors>(
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
          const TimeTableDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TimeTableDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TimeTableData(data));
          }
        }
      } else {
        return std::make_shared<TimeTableListData>(*this);
      }
    } else {
      return std::make_shared<TimeTableListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TimeTableListData>(dataOut);
  } else {
    return std::make_shared<TimeTableListData>();
  }
}

bool TimeTableListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"timeTableData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<TimeTableData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeTableData", &m_timeTableData)) {
      m_timeTableDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableListData::toJson() const {
  std::string result = "[";
  if (m_timeTableDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TimeTableData>("timeTableData",
                                                              m_timeTableData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram