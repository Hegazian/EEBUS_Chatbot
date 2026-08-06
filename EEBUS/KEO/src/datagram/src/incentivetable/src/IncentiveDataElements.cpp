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

#include <keo_datagram/incentivetable/IncentiveDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveDataElements::IncentiveDataElements()
    : DataElements(), m_incentiveIdIsSet(false), m_valueTypeIsSet(false),
      m_timestampIsSet(false), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriodElements()), m_timeTableIdIsSet(false),
      m_valueIsSet(false)

{}

bool IncentiveDataElements::
operator==(const IncentiveDataElements &c_classObject) const {
  if (m_incentiveIdIsSet != c_classObject.m_incentiveIdIsSet) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet) {
    return false;
  }

  return true;
}

bool IncentiveDataElements::
operator!=(const IncentiveDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveDataElements::isEmpty() const {
  return !m_incentiveIdIsSet && !m_valueTypeIsSet && !m_timestampIsSet &&
         !m_timePeriodIsSet && !m_timeTableIdIsSet && !m_valueIsSet;
}

DataElements::Type IncentiveDataElements::getDataType() const {
  return DataElements::Type::INCENTIVE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr IncentiveDataElements::clone() const {
  return std::make_shared<IncentiveDataElements>(*this);
}

void IncentiveDataElements::setIncentiveId() { m_incentiveIdIsSet = true; }

void IncentiveDataElements::cleanIncentiveId() { m_incentiveIdIsSet = false; }

bool IncentiveDataElements::getIncentiveIdIsSet() const {
  return m_incentiveIdIsSet;
}

void IncentiveDataElements::setValueType() { m_valueTypeIsSet = true; }

void IncentiveDataElements::cleanValueType() { m_valueTypeIsSet = false; }

bool IncentiveDataElements::getValueTypeIsSet() const {
  return m_valueTypeIsSet;
}

void IncentiveDataElements::setTimestamp() { m_timestampIsSet = true; }

void IncentiveDataElements::cleanTimestamp() { m_timestampIsSet = false; }

bool IncentiveDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void IncentiveDataElements::setTimePeriod(
    const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &IncentiveDataElements::getTimePeriod() const {
  return m_timePeriod;
}

void IncentiveDataElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool IncentiveDataElements::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void IncentiveDataElements::setTimeTableId() { m_timeTableIdIsSet = true; }

void IncentiveDataElements::cleanTimeTableId() { m_timeTableIdIsSet = false; }

bool IncentiveDataElements::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void IncentiveDataElements::setValue() { m_valueIsSet = true; }

void IncentiveDataElements::cleanValue() { m_valueIsSet = false; }

bool IncentiveDataElements::getValueIsSet() const { return m_valueIsSet; }

bool IncentiveDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveId", "valueType", "timestamp", "timePeriod",
                   "timeTableId", "value"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "incentiveId")) {
      m_incentiveIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "valueType")) {
      m_valueTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timestamp")) {
      m_timestampIsSet = true;
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "value")) {
      m_valueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveDataElements::toJson() const {
  std::string result = "[";
  if (m_incentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("incentiveId");
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueType");
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeTableId");
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("value");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram