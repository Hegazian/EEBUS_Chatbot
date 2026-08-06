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

#include <keo_datagram/incentivetable/IncentiveData.h>

#include <keo_datagram/incentivetable/IncentiveDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveData::IncentiveData()
    : m_incentiveIdIsSet(false), m_incentiveId(0), m_valueTypeIsSet(false),
      m_valueType(IncentiveValueType()), m_timestampIsSet(false),
      m_timestamp(AbsoluteOrRelativeTime()), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriod()), m_timeTableIdIsSet(false), m_timeTableId(0),
      m_valueIsSet(false), m_value(ScaledNumber())

{}

bool IncentiveData::operator==(const IncentiveData &c_classObject) const {
  if (m_incentiveIdIsSet != c_classObject.m_incentiveIdIsSet ||
      (m_incentiveIdIsSet && (m_incentiveId != c_classObject.m_incentiveId))) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet ||
      (m_valueTypeIsSet && (m_valueType != c_classObject.m_valueType))) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
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
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }

  return true;
}

bool IncentiveData::operator!=(const IncentiveData &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveData::isEmpty() const {
  return !m_incentiveIdIsSet && !m_valueTypeIsSet && !m_timestampIsSet &&
         !m_timePeriodIsSet && !m_timeTableIdIsSet && !m_valueIsSet;
}

void IncentiveData::setIncentiveId(const xs_unsignedInt &incentiveId) {
  m_incentiveId = incentiveId;
  m_incentiveIdIsSet = true;
}

const xs_unsignedInt &IncentiveData::getIncentiveId() const {
  return m_incentiveId;
}

void IncentiveData::cleanIncentiveId() {
  m_incentiveId = 0;
  m_incentiveIdIsSet = false;
}

bool IncentiveData::getIncentiveIdIsSet() const { return m_incentiveIdIsSet; }

void IncentiveData::setValueType(const IncentiveValueType &valueType) {
  m_valueType = valueType;
  m_valueTypeIsSet = true;
}

const IncentiveValueType &IncentiveData::getValueType() const {
  return m_valueType;
}

void IncentiveData::cleanValueType() {
  m_valueType = IncentiveValueType();
  m_valueTypeIsSet = false;
}

bool IncentiveData::getValueTypeIsSet() const { return m_valueTypeIsSet; }

void IncentiveData::setTimestamp(const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &IncentiveData::getTimestamp() const {
  return m_timestamp;
}

void IncentiveData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool IncentiveData::getTimestampIsSet() const { return m_timestampIsSet; }

void IncentiveData::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &IncentiveData::getTimePeriod() const { return m_timePeriod; }

void IncentiveData::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool IncentiveData::getTimePeriodIsSet() const { return m_timePeriodIsSet; }

void IncentiveData::setTimeTableId(const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &IncentiveData::getTimeTableId() const {
  return m_timeTableId;
}

void IncentiveData::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool IncentiveData::getTimeTableIdIsSet() const { return m_timeTableIdIsSet; }

void IncentiveData::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &IncentiveData::getValue() const { return m_value; }

void IncentiveData::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool IncentiveData::getValueIsSet() const { return m_valueIsSet; }

IncentiveData
IncentiveData::reduce(const IncentiveDataElements &elements) const {
  IncentiveData dataOut;
  if (getIncentiveIdIsSet() && elements.getIncentiveIdIsSet()) {
    dataOut.setIncentiveId(getIncentiveId());
  }
  if (getValueTypeIsSet() && elements.getValueTypeIsSet()) {
    dataOut.setValueType(getValueType());
  }
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getTimePeriodIsSet() && elements.getTimePeriodIsSet()) {
    dataOut.setTimePeriod(getTimePeriod().reduce(elements.getTimePeriod()));
  }
  if (getTimeTableIdIsSet() && elements.getTimeTableIdIsSet()) {
    dataOut.setTimeTableId(getTimeTableId());
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    dataOut.setValue(getValue());
  }
  return dataOut;
}

bool IncentiveData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveId", "valueType", "timestamp", "timePeriod",
                   "timeTableId", "value"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveId", &m_incentiveId)) {
      m_incentiveIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueType", &m_valueType)) {
      m_valueTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestamp", &m_timestamp)) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeTableId", &m_timeTableId)) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveData::toJson() const {
  std::string result = "[";
  if (m_incentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveId", m_incentiveId);
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueType", m_valueType);
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram