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

#include <keo_datagram/timeseries/TimeSeriesConstraintsListData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesConstraintsListData::TimeSeriesConstraintsListData()
    : CmdData(), m_timeSeriesConstraintsDataIsSet(false),
      m_timeSeriesConstraintsData(std::vector<TimeSeriesConstraintsData>())

{}

TimeSeriesConstraintsListData::TimeSeriesConstraintsListData(
    const std::vector<TimeSeriesConstraintsData> &c_timeSeriesConstraintsData) {
  setTimeSeriesConstraintsData(c_timeSeriesConstraintsData);
}

bool TimeSeriesConstraintsListData::
operator==(const TimeSeriesConstraintsListData &c_classObject) const {
  if (m_timeSeriesConstraintsDataIsSet !=
          c_classObject.m_timeSeriesConstraintsDataIsSet ||
      (m_timeSeriesConstraintsDataIsSet &&
       (m_timeSeriesConstraintsData !=
        c_classObject.m_timeSeriesConstraintsData))) {
    return false;
  }

  return true;
}

bool TimeSeriesConstraintsListData::
operator!=(const TimeSeriesConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesConstraintsListData::isEmpty() const {
  return !m_timeSeriesConstraintsDataIsSet;
}

CmdData::Type TimeSeriesConstraintsListData::getDataType() const {
  return CmdData::Type::TIME_SERIES_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr TimeSeriesConstraintsListData::clone() const {
  return std::make_shared<TimeSeriesConstraintsListData>(*this);
}

void TimeSeriesConstraintsListData::setTimeSeriesConstraintsData(
    const std::vector<TimeSeriesConstraintsData> &timeSeriesConstraintsData) {
  m_timeSeriesConstraintsData = timeSeriesConstraintsData;
  m_timeSeriesConstraintsDataIsSet = true;
}

const std::vector<TimeSeriesConstraintsData> &
TimeSeriesConstraintsListData::getTimeSeriesConstraintsData() const {
  return m_timeSeriesConstraintsData;
}

void TimeSeriesConstraintsListData::cleanTimeSeriesConstraintsData() {
  m_timeSeriesConstraintsData.clear();
  m_timeSeriesConstraintsDataIsSet = false;
}

bool TimeSeriesConstraintsListData::getTimeSeriesConstraintsDataIsSet() const {
  return m_timeSeriesConstraintsDataIsSet;
}

CmdDataPtr TimeSeriesConstraintsListData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<TimeSeriesConstraintsListData>(*this);
}

bool TimeSeriesConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TimeSeriesConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)), "timeSeriesConstraintsData",
            &m_timeSeriesConstraintsData)) {
      m_timeSeriesConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_timeSeriesConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TimeSeriesConstraintsData>(
        "timeSeriesConstraintsData", m_timeSeriesConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram