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

#include <keo_datagram/timeseries/TimeSeriesDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesDescriptionListDataSelectors::TimeSeriesDescriptionListDataSelectors()
    : DataSelectors(), m_timeSeriesIdIsSet(false), m_timeSeriesId(0),
      m_timeSeriesTypeIsSet(false), m_timeSeriesType(TimeSeriesType()),
      m_measurementIdIsSet(false), m_measurementId(0), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType())

{}

bool TimeSeriesDescriptionListDataSelectors::
operator==(const TimeSeriesDescriptionListDataSelectors &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet ||
      (m_timeSeriesIdIsSet &&
       (m_timeSeriesId != c_classObject.m_timeSeriesId))) {
    return false;
  }
  if (m_timeSeriesTypeIsSet != c_classObject.m_timeSeriesTypeIsSet ||
      (m_timeSeriesTypeIsSet &&
       (m_timeSeriesType != c_classObject.m_timeSeriesType))) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool TimeSeriesDescriptionListDataSelectors::
operator!=(const TimeSeriesDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesDescriptionListDataSelectors::isEmpty() const {
  return !m_timeSeriesIdIsSet && !m_timeSeriesTypeIsSet &&
         !m_measurementIdIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type
TimeSeriesDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIME_SERIES_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TimeSeriesDescriptionListDataSelectors::clone() const {
  return std::make_shared<TimeSeriesDescriptionListDataSelectors>(*this);
}

void TimeSeriesDescriptionListDataSelectors::setTimeSeriesId(
    const xs_unsignedInt &timeSeriesId) {
  m_timeSeriesId = timeSeriesId;
  m_timeSeriesIdIsSet = true;
}

const xs_unsignedInt &
TimeSeriesDescriptionListDataSelectors::getTimeSeriesId() const {
  return m_timeSeriesId;
}

void TimeSeriesDescriptionListDataSelectors::cleanTimeSeriesId() {
  m_timeSeriesId = 0;
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesDescriptionListDataSelectors::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

void TimeSeriesDescriptionListDataSelectors::setTimeSeriesType(
    const TimeSeriesType &timeSeriesType) {
  m_timeSeriesType = timeSeriesType;
  m_timeSeriesTypeIsSet = true;
}

const TimeSeriesType &
TimeSeriesDescriptionListDataSelectors::getTimeSeriesType() const {
  return m_timeSeriesType;
}

void TimeSeriesDescriptionListDataSelectors::cleanTimeSeriesType() {
  m_timeSeriesType = TimeSeriesType();
  m_timeSeriesTypeIsSet = false;
}

bool TimeSeriesDescriptionListDataSelectors::getTimeSeriesTypeIsSet() const {
  return m_timeSeriesTypeIsSet;
}

void TimeSeriesDescriptionListDataSelectors::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
TimeSeriesDescriptionListDataSelectors::getMeasurementId() const {
  return m_measurementId;
}

void TimeSeriesDescriptionListDataSelectors::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool TimeSeriesDescriptionListDataSelectors::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void TimeSeriesDescriptionListDataSelectors::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &TimeSeriesDescriptionListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void TimeSeriesDescriptionListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool TimeSeriesDescriptionListDataSelectors::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool TimeSeriesDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"timeSeriesId", "timeSeriesType", "measurementId", "scopeType"})) {
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
                                   "timeSeriesType", &m_timeSeriesType)) {
      m_timeSeriesTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesId", m_timeSeriesId);
  }
  if (m_timeSeriesTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesType", m_timeSeriesType);
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram