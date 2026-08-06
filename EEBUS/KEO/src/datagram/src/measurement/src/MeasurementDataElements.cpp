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

#include <keo_datagram/measurement/MeasurementDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementDataElements::MeasurementDataElements()
    : DataElements(), m_measurementIdIsSet(false), m_valueTypeIsSet(false),
      m_timestampIsSet(false), m_valueIsSet(false),
      m_value(ScaledNumberElements()), m_evaluationPeriodIsSet(false),
      m_evaluationPeriod(TimePeriodElements()), m_valueSourceIsSet(false),
      m_valueTendencyIsSet(false), m_valueStateIsSet(false)

{}

bool MeasurementDataElements::
operator==(const MeasurementDataElements &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
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
  if (m_valueSourceIsSet != c_classObject.m_valueSourceIsSet) {
    return false;
  }
  if (m_valueTendencyIsSet != c_classObject.m_valueTendencyIsSet) {
    return false;
  }
  if (m_valueStateIsSet != c_classObject.m_valueStateIsSet) {
    return false;
  }

  return true;
}

bool MeasurementDataElements::
operator!=(const MeasurementDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementDataElements::isEmpty() const {
  return !m_measurementIdIsSet && !m_valueTypeIsSet && !m_timestampIsSet &&
         !m_valueIsSet && !m_evaluationPeriodIsSet && !m_valueSourceIsSet &&
         !m_valueTendencyIsSet && !m_valueStateIsSet;
}

DataElements::Type MeasurementDataElements::getDataType() const {
  return DataElements::Type::MEASUREMENT_DATA_ELEMENTS_TYPE;
}

DataElementsPtr MeasurementDataElements::clone() const {
  return std::make_shared<MeasurementDataElements>(*this);
}

void MeasurementDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void MeasurementDataElements::cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool MeasurementDataElements::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementDataElements::setValueType() { m_valueTypeIsSet = true; }

void MeasurementDataElements::cleanValueType() { m_valueTypeIsSet = false; }

bool MeasurementDataElements::getValueTypeIsSet() const {
  return m_valueTypeIsSet;
}

void MeasurementDataElements::setTimestamp() { m_timestampIsSet = true; }

void MeasurementDataElements::cleanTimestamp() { m_timestampIsSet = false; }

bool MeasurementDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void MeasurementDataElements::setValue(const ScaledNumberElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumberElements &MeasurementDataElements::getValue() const {
  return m_value;
}

void MeasurementDataElements::cleanValue() {
  m_value = ScaledNumberElements();
  m_valueIsSet = false;
}

bool MeasurementDataElements::getValueIsSet() const { return m_valueIsSet; }

void MeasurementDataElements::setEvaluationPeriod(
    const TimePeriodElements &evaluationPeriod) {
  m_evaluationPeriod = evaluationPeriod;
  m_evaluationPeriodIsSet = true;
}

const TimePeriodElements &MeasurementDataElements::getEvaluationPeriod() const {
  return m_evaluationPeriod;
}

void MeasurementDataElements::cleanEvaluationPeriod() {
  m_evaluationPeriod = TimePeriodElements();
  m_evaluationPeriodIsSet = false;
}

bool MeasurementDataElements::getEvaluationPeriodIsSet() const {
  return m_evaluationPeriodIsSet;
}

void MeasurementDataElements::setValueSource() { m_valueSourceIsSet = true; }

void MeasurementDataElements::cleanValueSource() { m_valueSourceIsSet = false; }

bool MeasurementDataElements::getValueSourceIsSet() const {
  return m_valueSourceIsSet;
}

void MeasurementDataElements::setValueTendency() {
  m_valueTendencyIsSet = true;
}

void MeasurementDataElements::cleanValueTendency() {
  m_valueTendencyIsSet = false;
}

bool MeasurementDataElements::getValueTendencyIsSet() const {
  return m_valueTendencyIsSet;
}

void MeasurementDataElements::setValueState() { m_valueStateIsSet = true; }

void MeasurementDataElements::cleanValueState() { m_valueStateIsSet = false; }

bool MeasurementDataElements::getValueStateIsSet() const {
  return m_valueStateIsSet;
}

bool MeasurementDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "valueType", "timestamp", "value",
                   "evaluationPeriod", "valueSource", "valueTendency",
                   "valueState"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "measurementId")) {
      m_measurementIdIsSet = true;
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "valueSource")) {
      m_valueSourceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "valueTendency")) {
      m_valueTendencyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "valueState")) {
      m_valueStateIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementDataElements::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueType");
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
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
    result += KeoJsonTransformation::writeTag("valueSource");
  }
  if (m_valueTendencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueTendency");
  }
  if (m_valueStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueState");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram