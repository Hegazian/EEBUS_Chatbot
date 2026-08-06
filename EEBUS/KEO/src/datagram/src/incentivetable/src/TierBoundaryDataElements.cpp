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

#include <keo_datagram/incentivetable/TierBoundaryDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierBoundaryDataElements::TierBoundaryDataElements()
    : DataElements(), m_boundaryIdIsSet(false), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriodElements()), m_timeTableIdIsSet(false),
      m_lowerBoundaryValueIsSet(false),
      m_lowerBoundaryValue(ScaledNumberElements()),
      m_upperBoundaryValueIsSet(false),
      m_upperBoundaryValue(ScaledNumberElements())

{}

bool TierBoundaryDataElements::
operator==(const TierBoundaryDataElements &c_classObject) const {
  if (m_boundaryIdIsSet != c_classObject.m_boundaryIdIsSet) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet) {
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

bool TierBoundaryDataElements::
operator!=(const TierBoundaryDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierBoundaryDataElements::isEmpty() const {
  return !m_boundaryIdIsSet && !m_timePeriodIsSet && !m_timeTableIdIsSet &&
         !m_lowerBoundaryValueIsSet && !m_upperBoundaryValueIsSet;
}

DataElements::Type TierBoundaryDataElements::getDataType() const {
  return DataElements::Type::TIER_BOUNDARY_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TierBoundaryDataElements::clone() const {
  return std::make_shared<TierBoundaryDataElements>(*this);
}

void TierBoundaryDataElements::setBoundaryId() { m_boundaryIdIsSet = true; }

void TierBoundaryDataElements::cleanBoundaryId() { m_boundaryIdIsSet = false; }

bool TierBoundaryDataElements::getBoundaryIdIsSet() const {
  return m_boundaryIdIsSet;
}

void TierBoundaryDataElements::setTimePeriod(
    const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &TierBoundaryDataElements::getTimePeriod() const {
  return m_timePeriod;
}

void TierBoundaryDataElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool TierBoundaryDataElements::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void TierBoundaryDataElements::setTimeTableId() { m_timeTableIdIsSet = true; }

void TierBoundaryDataElements::cleanTimeTableId() {
  m_timeTableIdIsSet = false;
}

bool TierBoundaryDataElements::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TierBoundaryDataElements::setLowerBoundaryValue(
    const ScaledNumberElements &lowerBoundaryValue) {
  m_lowerBoundaryValue = lowerBoundaryValue;
  m_lowerBoundaryValueIsSet = true;
}

const ScaledNumberElements &
TierBoundaryDataElements::getLowerBoundaryValue() const {
  return m_lowerBoundaryValue;
}

void TierBoundaryDataElements::cleanLowerBoundaryValue() {
  m_lowerBoundaryValue = ScaledNumberElements();
  m_lowerBoundaryValueIsSet = false;
}

bool TierBoundaryDataElements::getLowerBoundaryValueIsSet() const {
  return m_lowerBoundaryValueIsSet;
}

void TierBoundaryDataElements::setUpperBoundaryValue(
    const ScaledNumberElements &upperBoundaryValue) {
  m_upperBoundaryValue = upperBoundaryValue;
  m_upperBoundaryValueIsSet = true;
}

const ScaledNumberElements &
TierBoundaryDataElements::getUpperBoundaryValue() const {
  return m_upperBoundaryValue;
}

void TierBoundaryDataElements::cleanUpperBoundaryValue() {
  m_upperBoundaryValue = ScaledNumberElements();
  m_upperBoundaryValueIsSet = false;
}

bool TierBoundaryDataElements::getUpperBoundaryValueIsSet() const {
  return m_upperBoundaryValueIsSet;
}

bool TierBoundaryDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"boundaryId", "timePeriod", "timeTableId",
                   "lowerBoundaryValue", "upperBoundaryValue"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "boundaryId")) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeTableId")) {
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

std::string TierBoundaryDataElements::toJson() const {
  std::string result = "[";
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("boundaryId");
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeTableId");
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