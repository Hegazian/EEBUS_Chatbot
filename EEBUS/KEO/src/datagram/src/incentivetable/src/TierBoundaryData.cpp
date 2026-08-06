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

#include <keo_datagram/incentivetable/TierBoundaryData.h>

#include <keo_datagram/incentivetable/TierBoundaryDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierBoundaryData::TierBoundaryData()
    : m_boundaryIdIsSet(false), m_boundaryId(0), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriod()), m_timeTableIdIsSet(false), m_timeTableId(0),
      m_lowerBoundaryValueIsSet(false), m_lowerBoundaryValue(ScaledNumber()),
      m_upperBoundaryValueIsSet(false), m_upperBoundaryValue(ScaledNumber())

{}

bool TierBoundaryData::operator==(const TierBoundaryData &c_classObject) const {
  if (m_boundaryIdIsSet != c_classObject.m_boundaryIdIsSet ||
      (m_boundaryIdIsSet && (m_boundaryId != c_classObject.m_boundaryId))) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
    return false;
  }
  if (m_lowerBoundaryValueIsSet != c_classObject.m_lowerBoundaryValueIsSet ||
      (m_lowerBoundaryValueIsSet &&
       (m_lowerBoundaryValue != c_classObject.m_lowerBoundaryValue))) {
    return false;
  }
  if (m_upperBoundaryValueIsSet != c_classObject.m_upperBoundaryValueIsSet ||
      (m_upperBoundaryValueIsSet &&
       (m_upperBoundaryValue != c_classObject.m_upperBoundaryValue))) {
    return false;
  }

  return true;
}

bool TierBoundaryData::operator!=(const TierBoundaryData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierBoundaryData::isEmpty() const {
  return !m_boundaryIdIsSet && !m_timePeriodIsSet && !m_timeTableIdIsSet &&
         !m_lowerBoundaryValueIsSet && !m_upperBoundaryValueIsSet;
}

void TierBoundaryData::setBoundaryId(const xs_unsignedInt &boundaryId) {
  m_boundaryId = boundaryId;
  m_boundaryIdIsSet = true;
}

const xs_unsignedInt &TierBoundaryData::getBoundaryId() const {
  return m_boundaryId;
}

void TierBoundaryData::cleanBoundaryId() {
  m_boundaryId = 0;
  m_boundaryIdIsSet = false;
}

bool TierBoundaryData::getBoundaryIdIsSet() const { return m_boundaryIdIsSet; }

void TierBoundaryData::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &TierBoundaryData::getTimePeriod() const {
  return m_timePeriod;
}

void TierBoundaryData::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool TierBoundaryData::getTimePeriodIsSet() const { return m_timePeriodIsSet; }

void TierBoundaryData::setTimeTableId(const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &TierBoundaryData::getTimeTableId() const {
  return m_timeTableId;
}

void TierBoundaryData::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool TierBoundaryData::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TierBoundaryData::setLowerBoundaryValue(
    const ScaledNumber &lowerBoundaryValue) {
  m_lowerBoundaryValue = lowerBoundaryValue;
  m_lowerBoundaryValueIsSet = true;
}

const ScaledNumber &TierBoundaryData::getLowerBoundaryValue() const {
  return m_lowerBoundaryValue;
}

void TierBoundaryData::cleanLowerBoundaryValue() {
  m_lowerBoundaryValue = ScaledNumber();
  m_lowerBoundaryValueIsSet = false;
}

bool TierBoundaryData::getLowerBoundaryValueIsSet() const {
  return m_lowerBoundaryValueIsSet;
}

void TierBoundaryData::setUpperBoundaryValue(
    const ScaledNumber &upperBoundaryValue) {
  m_upperBoundaryValue = upperBoundaryValue;
  m_upperBoundaryValueIsSet = true;
}

const ScaledNumber &TierBoundaryData::getUpperBoundaryValue() const {
  return m_upperBoundaryValue;
}

void TierBoundaryData::cleanUpperBoundaryValue() {
  m_upperBoundaryValue = ScaledNumber();
  m_upperBoundaryValueIsSet = false;
}

bool TierBoundaryData::getUpperBoundaryValueIsSet() const {
  return m_upperBoundaryValueIsSet;
}

TierBoundaryData
TierBoundaryData::reduce(const TierBoundaryDataElements &elements) const {
  TierBoundaryData dataOut;
  if (getBoundaryIdIsSet() && elements.getBoundaryIdIsSet()) {
    dataOut.setBoundaryId(getBoundaryId());
  }
  if (getTimePeriodIsSet() && elements.getTimePeriodIsSet()) {
    dataOut.setTimePeriod(getTimePeriod().reduce(elements.getTimePeriod()));
  }
  if (getTimeTableIdIsSet() && elements.getTimeTableIdIsSet()) {
    dataOut.setTimeTableId(getTimeTableId());
  }
  if (getLowerBoundaryValueIsSet() && elements.getLowerBoundaryValueIsSet()) {
    dataOut.setLowerBoundaryValue(
        getLowerBoundaryValue().reduce(elements.getLowerBoundaryValue()));
  }
  if (getUpperBoundaryValueIsSet() && elements.getUpperBoundaryValueIsSet()) {
    dataOut.setUpperBoundaryValue(
        getUpperBoundaryValue().reduce(elements.getUpperBoundaryValue()));
  }
  return dataOut;
}

bool TierBoundaryData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"boundaryId", "timePeriod", "timeTableId",
                   "lowerBoundaryValue", "upperBoundaryValue"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryId", &m_boundaryId)) {
      m_boundaryIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timePeriod", &m_timePeriod)) {
      m_timePeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeTableId", &m_timeTableId)) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "lowerBoundaryValue",
                                   &m_lowerBoundaryValue)) {
      m_lowerBoundaryValueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "upperBoundaryValue",
                                   &m_upperBoundaryValue)) {
      m_upperBoundaryValueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierBoundaryData::toJson() const {
  std::string result = "[";
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryId", m_boundaryId);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  if (m_lowerBoundaryValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("lowerBoundaryValue",
                                           m_lowerBoundaryValue);
  }
  if (m_upperBoundaryValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("upperBoundaryValue",
                                           m_upperBoundaryValue);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram