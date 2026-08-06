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
#include <keo_datagram/timetable/TimeTableConstraintsListData.h>
#include <keo_datagram/timetable/TimeTableConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableConstraintsListData::TimeTableConstraintsListData()
    : CmdData(), m_timeTableConstraintsDataIsSet(false),
      m_timeTableConstraintsData(std::vector<TimeTableConstraintsData>())

{}

TimeTableConstraintsListData::TimeTableConstraintsListData(
    const std::vector<TimeTableConstraintsData> &c_timeTableConstraintsData) {
  setTimeTableConstraintsData(c_timeTableConstraintsData);
}

bool TimeTableConstraintsListData::
operator==(const TimeTableConstraintsListData &c_classObject) const {
  if (m_timeTableConstraintsDataIsSet !=
          c_classObject.m_timeTableConstraintsDataIsSet ||
      (m_timeTableConstraintsDataIsSet &&
       (m_timeTableConstraintsData !=
        c_classObject.m_timeTableConstraintsData))) {
    return false;
  }

  return true;
}

bool TimeTableConstraintsListData::
operator!=(const TimeTableConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableConstraintsListData::isEmpty() const {
  return !m_timeTableConstraintsDataIsSet;
}

CmdData::Type TimeTableConstraintsListData::getDataType() const {
  return CmdData::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr TimeTableConstraintsListData::clone() const {
  return std::make_shared<TimeTableConstraintsListData>(*this);
}

void TimeTableConstraintsListData::setTimeTableConstraintsData(
    const std::vector<TimeTableConstraintsData> &timeTableConstraintsData) {
  m_timeTableConstraintsData = timeTableConstraintsData;
  m_timeTableConstraintsDataIsSet = true;
}

const std::vector<TimeTableConstraintsData> &
TimeTableConstraintsListData::getTimeTableConstraintsData() const {
  return m_timeTableConstraintsData;
}

void TimeTableConstraintsListData::cleanTimeTableConstraintsData() {
  m_timeTableConstraintsData.clear();
  m_timeTableConstraintsDataIsSet = false;
}

bool TimeTableConstraintsListData::getTimeTableConstraintsDataIsSet() const {
  return m_timeTableConstraintsDataIsSet;
}

CmdDataPtr
TimeTableConstraintsListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TimeTableConstraintsData> dataOut;
  for (const auto &data : getTimeTableConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TimeTableConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TimeTableConstraintsListDataSelectors>(
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
          const TimeTableConstraintsDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TimeTableConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TimeTableConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<TimeTableConstraintsListData>(*this);
      }
    } else {
      return std::make_shared<TimeTableConstraintsListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TimeTableConstraintsListData>(dataOut);
  } else {
    return std::make_shared<TimeTableConstraintsListData>();
  }
}

bool TimeTableConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"timeTableConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TimeTableConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)), "timeTableConstraintsData",
            &m_timeTableConstraintsData)) {
      m_timeTableConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_timeTableConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TimeTableConstraintsData>(
        "timeTableConstraintsData", m_timeTableConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram