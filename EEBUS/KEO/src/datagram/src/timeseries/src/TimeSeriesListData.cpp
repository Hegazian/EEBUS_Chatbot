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

#include <keo_datagram/timeseries/TimeSeriesListData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesListData::TimeSeriesListData()
    : CmdData(), m_timeSeriesDataIsSet(false),
      m_timeSeriesData(std::vector<TimeSeriesData>())

{}

TimeSeriesListData::TimeSeriesListData(
    const std::vector<TimeSeriesData> &c_timeSeriesData) {
  setTimeSeriesData(c_timeSeriesData);
}

bool TimeSeriesListData::
operator==(const TimeSeriesListData &c_classObject) const {
  if (m_timeSeriesDataIsSet != c_classObject.m_timeSeriesDataIsSet ||
      (m_timeSeriesDataIsSet &&
       (m_timeSeriesData != c_classObject.m_timeSeriesData))) {
    return false;
  }

  return true;
}

bool TimeSeriesListData::
operator!=(const TimeSeriesListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesListData::isEmpty() const { return !m_timeSeriesDataIsSet; }

CmdData::Type TimeSeriesListData::getDataType() const {
  return CmdData::Type::TIME_SERIES_LIST_DATA_TYPE;
}

CmdDataPtr TimeSeriesListData::clone() const {
  return std::make_shared<TimeSeriesListData>(*this);
}

void TimeSeriesListData::setTimeSeriesData(
    const std::vector<TimeSeriesData> &timeSeriesData) {
  m_timeSeriesData = timeSeriesData;
  m_timeSeriesDataIsSet = true;
}

const std::vector<TimeSeriesData> &
TimeSeriesListData::getTimeSeriesData() const {
  return m_timeSeriesData;
}

void TimeSeriesListData::cleanTimeSeriesData() {
  m_timeSeriesData.clear();
  m_timeSeriesDataIsSet = false;
}

bool TimeSeriesListData::getTimeSeriesDataIsSet() const {
  return m_timeSeriesDataIsSet;
}

CmdDataPtr
TimeSeriesListData::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<TimeSeriesListData>(*this);
}

bool TimeSeriesListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"timeSeriesData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<TimeSeriesData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesData", &m_timeSeriesData)) {
      m_timeSeriesDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesListData::toJson() const {
  std::string result = "[";
  if (m_timeSeriesDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TimeSeriesData>(
        "timeSeriesData", m_timeSeriesData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram