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

#include <keo_datagram/measurement/MeasurementData.h>

#include <keo_datagram/measurement/MeasurementDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementData::MeasurementData()
    : m_measurementIdIsSet(false), m_measurementId(0), m_valueTypeIsSet(false),
      m_valueType(MeasurementValueType()), m_timestampIsSet(false),
      m_timestamp(AbsoluteOrRelativeTime()), m_valueIsSet(false),
      m_value(ScaledNumber()), m_evaluationPeriodIsSet(false),
      m_evaluationPeriod(TimePeriod()), m_valueSourceIsSet(false),
      m_valueSource(MeasurementValueSource()), m_valueTendencyIsSet(false),
      m_valueTendency(MeasurementValueTendency()), m_valueStateIsSet(false),
      m_valueState(MeasurementValueState())

{}

bool MeasurementData::operator==(const MeasurementData &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
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
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }
  if (m_evaluationPeriodIsSet != c_classObject.m_evaluationPeriodIsSet ||
      (m_evaluationPeriodIsSet &&
       (m_evaluationPeriod != c_classObject.m_evaluationPeriod))) {
    return false;
  }
  if (m_valueSourceIsSet != c_classObject.m_valueSourceIsSet ||
      (m_valueSourceIsSet && (m_valueSource != c_classObject.m_valueSource))) {
    return false;
  }
  if (m_valueTendencyIsSet != c_classObject.m_valueTendencyIsSet ||
      (m_valueTendencyIsSet &&
       (m_valueTendency != c_classObject.m_valueTendency))) {
    return false;
  }
  if (m_valueStateIsSet != c_classObject.m_valueStateIsSet ||
      (m_valueStateIsSet && (m_valueState != c_classObject.m_valueState))) {
    return false;
  }

  return true;
}

bool MeasurementData::operator!=(const MeasurementData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementData::isEmpty() const {
  return !m_measurementIdIsSet && !m_valueTypeIsSet && !m_timestampIsSet &&
         !m_valueIsSet && !m_evaluationPeriodIsSet && !m_valueSourceIsSet &&
         !m_valueTendencyIsSet && !m_valueStateIsSet;
}

void MeasurementData::setMeasurementId(const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &MeasurementData::getMeasurementId() const {
  return m_measurementId;
}

void MeasurementData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool MeasurementData::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementData::setValueType(const MeasurementValueType &valueType) {
  m_valueType = valueType;
  m_valueTypeIsSet = true;
}

const MeasurementValueType &MeasurementData::getValueType() const {
  return m_valueType;
}

void MeasurementData::cleanValueType() {
  m_valueType = MeasurementValueType();
  m_valueTypeIsSet = false;
}

bool MeasurementData::getValueTypeIsSet() const { return m_valueTypeIsSet; }

void MeasurementData::setTimestamp(const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &MeasurementData::getTimestamp() const {
  return m_timestamp;
}

void MeasurementData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool MeasurementData::getTimestampIsSet() const { return m_timestampIsSet; }

void MeasurementData::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &MeasurementData::getValue() const { return m_value; }

void MeasurementData::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool MeasurementData::getValueIsSet() const { return m_valueIsSet; }

void MeasurementData::setEvaluationPeriod(const TimePeriod &evaluationPeriod) {
  m_evaluationPeriod = evaluationPeriod;
  m_evaluationPeriodIsSet = true;
}

const TimePeriod &MeasurementData::getEvaluationPeriod() const {
  return m_evaluationPeriod;
}

void MeasurementData::cleanEvaluationPeriod() {
  m_evaluationPeriod = TimePeriod();
  m_evaluationPeriodIsSet = false;
}

bool MeasurementData::getEvaluationPeriodIsSet() const {
  return m_evaluationPeriodIsSet;
}

void MeasurementData::setValueSource(
    const MeasurementValueSource &valueSource) {
  m_valueSource = valueSource;
  m_valueSourceIsSet = true;
}

const MeasurementValueSource &MeasurementData::getValueSource() const {
  return m_valueSource;
}

void MeasurementData::cleanValueSource() {
  m_valueSource = MeasurementValueSource();
  m_valueSourceIsSet = false;
}

bool MeasurementData::getValueSourceIsSet() const { return m_valueSourceIsSet; }

void MeasurementData::setValueTendency(
    const MeasurementValueTendency &valueTendency) {
  m_valueTendency = valueTendency;
  m_valueTendencyIsSet = true;
}

const MeasurementValueTendency &MeasurementData::getValueTendency() const {
  return m_valueTendency;
}

void MeasurementData::cleanValueTendency() {
  m_valueTendency = MeasurementValueTendency();
  m_valueTendencyIsSet = false;
}

bool MeasurementData::getValueTendencyIsSet() const {
  return m_valueTendencyIsSet;
}

void MeasurementData::setValueState(const MeasurementValueState &valueState) {
  m_valueState = valueState;
  m_valueStateIsSet = true;
}

const MeasurementValueState &MeasurementData::getValueState() const {
  return m_valueState;
}

void MeasurementData::cleanValueState() {
  m_valueState = MeasurementValueState();
  m_valueStateIsSet = false;
}

bool MeasurementData::getValueStateIsSet() const { return m_valueStateIsSet; }

MeasurementData
MeasurementData::reduce(const MeasurementDataElements &elements) const {
  MeasurementData dataOut;
  if (getMeasurementIdIsSet() && elements.getMeasurementIdIsSet()) {
    dataOut.setMeasurementId(getMeasurementId());
  }
  if (getValueTypeIsSet() && elements.getValueTypeIsSet()) {
    dataOut.setValueType(getValueType());
  }
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    dataOut.setValue(getValue().reduce(elements.getValue()));
  }
  if (getEvaluationPeriodIsSet() && elements.getEvaluationPeriodIsSet()) {
    dataOut.setEvaluationPeriod(
        getEvaluationPeriod().reduce(elements.getEvaluationPeriod()));
  }
  if (getValueSourceIsSet() && elements.getValueSourceIsSet()) {
    dataOut.setValueSource(getValueSource());
  }
  if (getValueTendencyIsSet() && elements.getValueTendencyIsSet()) {
    dataOut.setValueTendency(getValueTendency());
  }
  if (getValueStateIsSet() && elements.getValueStateIsSet()) {
    dataOut.setValueState(getValueState());
  }
  return dataOut;
}

bool MeasurementData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "valueType", "timestamp", "value",
                   "evaluationPeriod", "valueSource", "valueTendency",
                   "valueState"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
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
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "evaluationPeriod", &m_evaluationPeriod)) {
      m_evaluationPeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueSource", &m_valueSource)) {
      m_valueSourceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueTendency", &m_valueTendency)) {
      m_valueTendencyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueState", &m_valueState)) {
      m_valueStateIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementData::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueType", m_valueType);
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  if (m_evaluationPeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("evaluationPeriod", m_evaluationPeriod);
  }
  if (m_valueSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueSource", m_valueSource);
  }
  if (m_valueTendencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueTendency", m_valueTendency);
  }
  if (m_valueStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueState", m_valueState);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram