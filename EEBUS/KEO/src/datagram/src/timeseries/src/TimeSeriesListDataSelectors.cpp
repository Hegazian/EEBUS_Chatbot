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

#include <keo_datagram/timeseries/TimeSeriesListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesListDataSelectors::TimeSeriesListDataSelectors()
    : DataSelectors(), m_timeSeriesIdIsSet(false), m_timeSeriesId(0),
      m_timeSeriesSlotIdIsSet(false), m_timeSeriesSlotId(0)

{}

TimeSeriesListDataSelectors::TimeSeriesListDataSelectors(
    const xs_unsignedInt &c_timeSeriesId,
    const xs_unsignedInt &c_timeSeriesSlotId)
    : DataSelectors(), m_timeSeriesIdIsSet(true),
      m_timeSeriesId(c_timeSeriesId), m_timeSeriesSlotIdIsSet(true),
      m_timeSeriesSlotId(c_timeSeriesSlotId)

{}

bool TimeSeriesListDataSelectors::
operator==(const TimeSeriesListDataSelectors &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet ||
      (m_timeSeriesIdIsSet &&
       (m_timeSeriesId != c_classObject.m_timeSeriesId))) {
    return false;
  }
  if (m_timeSeriesSlotIdIsSet != c_classObject.m_timeSeriesSlotIdIsSet ||
      (m_timeSeriesSlotIdIsSet &&
       (m_timeSeriesSlotId != c_classObject.m_timeSeriesSlotId))) {
    return false;
  }

  return true;
}

bool TimeSeriesListDataSelectors::
operator!=(const TimeSeriesListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesListDataSelectors::isEmpty() const {
  return !m_timeSeriesIdIsSet && !m_timeSeriesSlotIdIsSet;
}

DataSelectors::Type TimeSeriesListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIME_SERIES_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TimeSeriesListDataSelectors::clone() const {
  return std::make_shared<TimeSeriesListDataSelectors>(*this);
}

void TimeSeriesListDataSelectors::setTimeSeriesId(
    const xs_unsignedInt &timeSeriesId) {
  m_timeSeriesId = timeSeriesId;
  m_timeSeriesIdIsSet = true;
}

const xs_unsignedInt &TimeSeriesListDataSelectors::getTimeSeriesId() const {
  return m_timeSeriesId;
}

void TimeSeriesListDataSelectors::cleanTimeSeriesId() {
  m_timeSeriesId = 0;
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesListDataSelectors::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

void TimeSeriesListDataSelectors::setTimeSeriesSlotId(
    const xs_unsignedInt &timeSeriesSlotId) {
  m_timeSeriesSlotId = timeSeriesSlotId;
  m_timeSeriesSlotIdIsSet = true;
}

const xs_unsignedInt &TimeSeriesListDataSelectors::getTimeSeriesSlotId() const {
  return m_timeSeriesSlotId;
}

void TimeSeriesListDataSelectors::cleanTimeSeriesSlotId() {
  m_timeSeriesSlotId = 0;
  m_timeSeriesSlotIdIsSet = false;
}

bool TimeSeriesListDataSelectors::getTimeSeriesSlotIdIsSet() const {
  return m_timeSeriesSlotIdIsSet;
}

bool TimeSeriesListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesId", "timeSeriesSlotId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesId", &m_timeSeriesId)) {
      m_timeSeriesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesSlotId", &m_timeSeriesSlotId)) {
      m_timeSeriesSlotIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesId", m_timeSeriesId);
  }
  if (m_timeSeriesSlotIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timeSeriesSlotId", m_timeSeriesSlotId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram