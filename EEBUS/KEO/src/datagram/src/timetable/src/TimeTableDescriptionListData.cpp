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
#include <keo_datagram/timetable/TimeTableDescriptionListData.h>
#include <keo_datagram/timetable/TimeTableDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeTableDescriptionListData::TimeTableDescriptionListData()
    : CmdData(), m_timeTableDescriptionDataIsSet(false),
      m_timeTableDescriptionData(std::vector<TimeTableDescriptionData>())

{}

TimeTableDescriptionListData::TimeTableDescriptionListData(
    const std::vector<TimeTableDescriptionData> &c_timeTableDescriptionData) {
  setTimeTableDescriptionData(c_timeTableDescriptionData);
}

bool TimeTableDescriptionListData::
operator==(const TimeTableDescriptionListData &c_classObject) const {
  if (m_timeTableDescriptionDataIsSet !=
          c_classObject.m_timeTableDescriptionDataIsSet ||
      (m_timeTableDescriptionDataIsSet &&
       (m_timeTableDescriptionData !=
        c_classObject.m_timeTableDescriptionData))) {
    return false;
  }

  return true;
}

bool TimeTableDescriptionListData::
operator!=(const TimeTableDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeTableDescriptionListData::isEmpty() const {
  return !m_timeTableDescriptionDataIsSet;
}

CmdData::Type TimeTableDescriptionListData::getDataType() const {
  return CmdData::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr TimeTableDescriptionListData::clone() const {
  return std::make_shared<TimeTableDescriptionListData>(*this);
}

void TimeTableDescriptionListData::setTimeTableDescriptionData(
    const std::vector<TimeTableDescriptionData> &timeTableDescriptionData) {
  m_timeTableDescriptionData = timeTableDescriptionData;
  m_timeTableDescriptionDataIsSet = true;
}

const std::vector<TimeTableDescriptionData> &
TimeTableDescriptionListData::getTimeTableDescriptionData() const {
  return m_timeTableDescriptionData;
}

void TimeTableDescriptionListData::cleanTimeTableDescriptionData() {
  m_timeTableDescriptionData.clear();
  m_timeTableDescriptionDataIsSet = false;
}

bool TimeTableDescriptionListData::getTimeTableDescriptionDataIsSet() const {
  return m_timeTableDescriptionDataIsSet;
}

CmdDataPtr
TimeTableDescriptionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TimeTableDescriptionData> dataOut;
  for (const auto &data : getTimeTableDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TimeTableDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TimeTableDescriptionListDataSelectors>(
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
          const TimeTableDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TimeTableDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TimeTableDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<TimeTableDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<TimeTableDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TimeTableDescriptionListData>(dataOut);
  } else {
    return std::make_shared<TimeTableDescriptionListData>();
  }
}

bool TimeTableDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"timeTableDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TimeTableDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "timeTableDescriptionData",
            &m_timeTableDescriptionData)) {
      m_timeTableDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeTableDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_timeTableDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TimeTableDescriptionData>(
        "timeTableDescriptionData", m_timeTableDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram