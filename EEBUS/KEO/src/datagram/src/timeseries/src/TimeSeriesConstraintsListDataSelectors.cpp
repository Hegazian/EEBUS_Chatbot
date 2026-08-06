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

#include <keo_datagram/timeseries/TimeSeriesConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesConstraintsListDataSelectors::TimeSeriesConstraintsListDataSelectors()
    : DataSelectors(), m_timeSeriesIdIsSet(false), m_timeSeriesId(0)

{}

TimeSeriesConstraintsListDataSelectors::TimeSeriesConstraintsListDataSelectors(
    const xs_unsignedInt &c_timeSeriesId) {
  setTimeSeriesId(c_timeSeriesId);
}

bool TimeSeriesConstraintsListDataSelectors::
operator==(const TimeSeriesConstraintsListDataSelectors &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet ||
      (m_timeSeriesIdIsSet &&
       (m_timeSeriesId != c_classObject.m_timeSeriesId))) {
    return false;
  }

  return true;
}

bool TimeSeriesConstraintsListDataSelectors::
operator!=(const TimeSeriesConstraintsListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesConstraintsListDataSelectors::isEmpty() const {
  return !m_timeSeriesIdIsSet;
}

DataSelectors::Type
TimeSeriesConstraintsListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIME_SERIES_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TimeSeriesConstraintsListDataSelectors::clone() const {
  return std::make_shared<TimeSeriesConstraintsListDataSelectors>(*this);
}

void TimeSeriesConstraintsListDataSelectors::setTimeSeriesId(
    const xs_unsignedInt &timeSeriesId) {
  m_timeSeriesId = timeSeriesId;
  m_timeSeriesIdIsSet = true;
}

const xs_unsignedInt &
TimeSeriesConstraintsListDataSelectors::getTimeSeriesId() const {
  return m_timeSeriesId;
}

void TimeSeriesConstraintsListDataSelectors::cleanTimeSeriesId() {
  m_timeSeriesId = 0;
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesConstraintsListDataSelectors::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

bool TimeSeriesConstraintsListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"timeSeriesId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesId", &m_timeSeriesId)) {
      m_timeSeriesIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesConstraintsListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesId", m_timeSeriesId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram