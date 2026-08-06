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

#include <keo_datagram/timeseries/TimeSeriesDescriptionListData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesDescriptionListData::TimeSeriesDescriptionListData()
    : CmdData(), m_timeSeriesDescriptionDataIsSet(false),
      m_timeSeriesDescriptionData(std::vector<TimeSeriesDescriptionData>())

{}

TimeSeriesDescriptionListData::TimeSeriesDescriptionListData(
    const std::vector<TimeSeriesDescriptionData> &c_timeSeriesDescriptionData) {
  setTimeSeriesDescriptionData(c_timeSeriesDescriptionData);
}

bool TimeSeriesDescriptionListData::
operator==(const TimeSeriesDescriptionListData &c_classObject) const {
  if (m_timeSeriesDescriptionDataIsSet !=
          c_classObject.m_timeSeriesDescriptionDataIsSet ||
      (m_timeSeriesDescriptionDataIsSet &&
       (m_timeSeriesDescriptionData !=
        c_classObject.m_timeSeriesDescriptionData))) {
    return false;
  }

  return true;
}

bool TimeSeriesDescriptionListData::
operator!=(const TimeSeriesDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesDescriptionListData::isEmpty() const {
  return !m_timeSeriesDescriptionDataIsSet;
}

CmdData::Type TimeSeriesDescriptionListData::getDataType() const {
  return CmdData::Type::TIME_SERIES_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr TimeSeriesDescriptionListData::clone() const {
  return std::make_shared<TimeSeriesDescriptionListData>(*this);
}

void TimeSeriesDescriptionListData::setTimeSeriesDescriptionData(
    const std::vector<TimeSeriesDescriptionData> &timeSeriesDescriptionData) {
  m_timeSeriesDescriptionData = timeSeriesDescriptionData;
  m_timeSeriesDescriptionDataIsSet = true;
}

const std::vector<TimeSeriesDescriptionData> &
TimeSeriesDescriptionListData::getTimeSeriesDescriptionData() const {
  return m_timeSeriesDescriptionData;
}

void TimeSeriesDescriptionListData::cleanTimeSeriesDescriptionData() {
  m_timeSeriesDescriptionData.clear();
  m_timeSeriesDescriptionDataIsSet = false;
}

bool TimeSeriesDescriptionListData::getTimeSeriesDescriptionDataIsSet() const {
  return m_timeSeriesDescriptionDataIsSet;
}

CmdDataPtr TimeSeriesDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<TimeSeriesDescriptionListData>(*this);
}

bool TimeSeriesDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TimeSeriesDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "timeSeriesDescriptionData",
            &m_timeSeriesDescriptionData)) {
      m_timeSeriesDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_timeSeriesDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TimeSeriesDescriptionData>(
        "timeSeriesDescriptionData", m_timeSeriesDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram