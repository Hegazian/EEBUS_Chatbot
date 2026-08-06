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

#include <keo_datagram/alarm/AlarmDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

AlarmDataElements::AlarmDataElements()
    : DataElements(), m_alarmIdIsSet(false), m_thresholdIdIsSet(false),
      m_timestampIsSet(false), m_alarmTypeIsSet(false),
      m_measuredValueIsSet(false), m_measuredValue(ScaledNumberElements()),
      m_evaluationPeriodIsSet(false), m_evaluationPeriod(TimePeriodElements()),
      m_scopeTypeIsSet(false), m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool AlarmDataElements::
operator==(const AlarmDataElements &c_classObject) const {
  if (m_alarmIdIsSet != c_classObject.m_alarmIdIsSet) {
    return false;
  }
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_alarmTypeIsSet != c_classObject.m_alarmTypeIsSet) {
    return false;
  }
  if (m_measuredValueIsSet != c_classObject.m_measuredValueIsSet ||
      (m_measuredValueIsSet &&
       (m_measuredValue != c_classObject.m_measuredValue))) {
    return false;
  }
  if (m_evaluationPeriodIsSet != c_classObject.m_evaluationPeriodIsSet ||
      (m_evaluationPeriodIsSet &&
       (m_evaluationPeriod != c_classObject.m_evaluationPeriod))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool AlarmDataElements::
operator!=(const AlarmDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool AlarmDataElements::isEmpty() const {
  return !m_alarmIdIsSet && !m_thresholdIdIsSet && !m_timestampIsSet &&
         !m_alarmTypeIsSet && !m_measuredValueIsSet &&
         !m_evaluationPeriodIsSet && !m_scopeTypeIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

DataElements::Type AlarmDataElements::getDataType() const {
  return DataElements::Type::ALARM_DATA_ELEMENTS_TYPE;
}

DataElementsPtr AlarmDataElements::clone() const {
  return std::make_shared<AlarmDataElements>(*this);
}

void AlarmDataElements::setAlarmId() { m_alarmIdIsSet = true; }

void AlarmDataElements::cleanAlarmId() { m_alarmIdIsSet = false; }

bool AlarmDataElements::getAlarmIdIsSet() const { return m_alarmIdIsSet; }

void AlarmDataElements::setThresholdId() { m_thresholdIdIsSet = true; }

void AlarmDataElements::cleanThresholdId() { m_thresholdIdIsSet = false; }

bool AlarmDataElements::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void AlarmDataElements::setTimestamp() { m_timestampIsSet = true; }

void AlarmDataElements::cleanTimestamp() { m_timestampIsSet = false; }

bool AlarmDataElements::getTimestampIsSet() const { return m_timestampIsSet; }

void AlarmDataElements::setAlarmType() { m_alarmTypeIsSet = true; }

void AlarmDataElements::cleanAlarmType() { m_alarmTypeIsSet = false; }

bool AlarmDataElements::getAlarmTypeIsSet() const { return m_alarmTypeIsSet; }

void AlarmDataElements::setMeasuredValue(
    const ScaledNumberElements &measuredValue) {
  m_measuredValue = measuredValue;
  m_measuredValueIsSet = true;
}

const ScaledNumberElements &AlarmDataElements::getMeasuredValue() const {
  return m_measuredValue;
}

void AlarmDataElements::cleanMeasuredValue() {
  m_measuredValue = ScaledNumberElements();
  m_measuredValueIsSet = false;
}

bool AlarmDataElements::getMeasuredValueIsSet() const {
  return m_measuredValueIsSet;
}

void AlarmDataElements::setEvaluationPeriod(
    const TimePeriodElements &evaluationPeriod) {
  m_evaluationPeriod = evaluationPeriod;
  m_evaluationPeriodIsSet = true;
}

const TimePeriodElements &AlarmDataElements::getEvaluationPeriod() const {
  return m_evaluationPeriod;
}

void AlarmDataElements::cleanEvaluationPeriod() {
  m_evaluationPeriod = TimePeriodElements();
  m_evaluationPeriodIsSet = false;
}

bool AlarmDataElements::getEvaluationPeriodIsSet() const {
  return m_evaluationPeriodIsSet;
}

void AlarmDataElements::setScopeType() { m_scopeTypeIsSet = true; }

void AlarmDataElements::cleanScopeType() { m_scopeTypeIsSet = false; }

bool AlarmDataElements::getScopeTypeIsSet() const { return m_scopeTypeIsSet; }

void AlarmDataElements::setLabel() { m_labelIsSet = true; }

void AlarmDataElements::cleanLabel() { m_labelIsSet = false; }

bool AlarmDataElements::getLabelIsSet() const { return m_labelIsSet; }

void AlarmDataElements::setDescription() { m_descriptionIsSet = true; }

void AlarmDataElements::cleanDescription() { m_descriptionIsSet = false; }

bool AlarmDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool AlarmDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"alarmId", "thresholdId", "timestamp", "alarmType",
                   "measuredValue", "evaluationPeriod", "scopeType", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "alarmId")) {
      m_alarmIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "thresholdId")) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timestamp")) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "alarmType")) {
      m_alarmTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measuredValue", &m_measuredValue)) {
      m_measuredValueIsSet = true;
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
                                     "scopeType")) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string AlarmDataElements::toJson() const {
  std::string result = "[";
  if (m_alarmIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("alarmId");
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thresholdId");
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_alarmTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("alarmType");
  }
  if (m_measuredValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measuredValue", m_measuredValue);
  }
  if (m_evaluationPeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("evaluationPeriod", m_evaluationPeriod);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scopeType");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram