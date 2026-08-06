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

#include <keo_datagram/alarm/AlarmData.h>

#include <keo_datagram/alarm/AlarmDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

AlarmData::AlarmData()
    : m_alarmIdIsSet(false), m_alarmId(0), m_thresholdIdIsSet(false),
      m_thresholdId(0), m_timestampIsSet(false),
      m_timestamp(AbsoluteOrRelativeTime()), m_alarmTypeIsSet(false),
      m_alarmType(AlarmType()), m_measuredValueIsSet(false),
      m_measuredValue(ScaledNumber()), m_evaluationPeriodIsSet(false),
      m_evaluationPeriod(TimePeriod()), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool AlarmData::operator==(const AlarmData &c_classObject) const {
  if (m_alarmIdIsSet != c_classObject.m_alarmIdIsSet ||
      (m_alarmIdIsSet && (m_alarmId != c_classObject.m_alarmId))) {
    return false;
  }
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_alarmTypeIsSet != c_classObject.m_alarmTypeIsSet ||
      (m_alarmTypeIsSet && (m_alarmType != c_classObject.m_alarmType))) {
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
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool AlarmData::operator!=(const AlarmData &c_classObject) const {
  return !(*this == c_classObject);
}

bool AlarmData::isEmpty() const {
  return !m_alarmIdIsSet && !m_thresholdIdIsSet && !m_timestampIsSet &&
         !m_alarmTypeIsSet && !m_measuredValueIsSet &&
         !m_evaluationPeriodIsSet && !m_scopeTypeIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

void AlarmData::setAlarmId(const xs_unsignedInt &alarmId) {
  m_alarmId = alarmId;
  m_alarmIdIsSet = true;
}

const xs_unsignedInt &AlarmData::getAlarmId() const { return m_alarmId; }

void AlarmData::cleanAlarmId() {
  m_alarmId = 0;
  m_alarmIdIsSet = false;
}

bool AlarmData::getAlarmIdIsSet() const { return m_alarmIdIsSet; }

void AlarmData::setThresholdId(const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &AlarmData::getThresholdId() const {
  return m_thresholdId;
}

void AlarmData::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool AlarmData::getThresholdIdIsSet() const { return m_thresholdIdIsSet; }

void AlarmData::setTimestamp(const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &AlarmData::getTimestamp() const {
  return m_timestamp;
}

void AlarmData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool AlarmData::getTimestampIsSet() const { return m_timestampIsSet; }

void AlarmData::setAlarmType(const AlarmType &alarmType) {
  m_alarmType = alarmType;
  m_alarmTypeIsSet = true;
}

const AlarmType &AlarmData::getAlarmType() const { return m_alarmType; }

void AlarmData::cleanAlarmType() {
  m_alarmType = AlarmType();
  m_alarmTypeIsSet = false;
}

bool AlarmData::getAlarmTypeIsSet() const { return m_alarmTypeIsSet; }

void AlarmData::setMeasuredValue(const ScaledNumber &measuredValue) {
  m_measuredValue = measuredValue;
  m_measuredValueIsSet = true;
}

const ScaledNumber &AlarmData::getMeasuredValue() const {
  return m_measuredValue;
}

void AlarmData::cleanMeasuredValue() {
  m_measuredValue = ScaledNumber();
  m_measuredValueIsSet = false;
}

bool AlarmData::getMeasuredValueIsSet() const { return m_measuredValueIsSet; }

void AlarmData::setEvaluationPeriod(const TimePeriod &evaluationPeriod) {
  m_evaluationPeriod = evaluationPeriod;
  m_evaluationPeriodIsSet = true;
}

const TimePeriod &AlarmData::getEvaluationPeriod() const {
  return m_evaluationPeriod;
}

void AlarmData::cleanEvaluationPeriod() {
  m_evaluationPeriod = TimePeriod();
  m_evaluationPeriodIsSet = false;
}

bool AlarmData::getEvaluationPeriodIsSet() const {
  return m_evaluationPeriodIsSet;
}

void AlarmData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &AlarmData::getScopeType() const { return m_scopeType; }

void AlarmData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool AlarmData::getScopeTypeIsSet() const { return m_scopeTypeIsSet; }

void AlarmData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &AlarmData::getLabel() const { return m_label; }

void AlarmData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool AlarmData::getLabelIsSet() const { return m_labelIsSet; }

void AlarmData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &AlarmData::getDescription() const { return m_description; }

void AlarmData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool AlarmData::getDescriptionIsSet() const { return m_descriptionIsSet; }

AlarmData AlarmData::reduce(const AlarmDataElements &elements) const {
  AlarmData dataOut;
  if (getAlarmIdIsSet() && elements.getAlarmIdIsSet()) {
    dataOut.setAlarmId(getAlarmId());
  }
  if (getThresholdIdIsSet() && elements.getThresholdIdIsSet()) {
    dataOut.setThresholdId(getThresholdId());
  }
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getAlarmTypeIsSet() && elements.getAlarmTypeIsSet()) {
    dataOut.setAlarmType(getAlarmType());
  }
  if (getMeasuredValueIsSet() && elements.getMeasuredValueIsSet()) {
    dataOut.setMeasuredValue(
        getMeasuredValue().reduce(elements.getMeasuredValue()));
  }
  if (getEvaluationPeriodIsSet() && elements.getEvaluationPeriodIsSet()) {
    dataOut.setEvaluationPeriod(
        getEvaluationPeriod().reduce(elements.getEvaluationPeriod()));
  }
  if (getScopeTypeIsSet() && elements.getScopeTypeIsSet()) {
    dataOut.setScopeType(getScopeType());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool AlarmData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"alarmId", "thresholdId", "timestamp", "alarmType",
                   "measuredValue", "evaluationPeriod", "scopeType", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "alarmId", &m_alarmId)) {
      m_alarmIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdId", &m_thresholdId)) {
      m_thresholdIdIsSet = true;
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
                                   "alarmType", &m_alarmType)) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string AlarmData::toJson() const {
  std::string result = "[";
  if (m_alarmIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("alarmId", m_alarmId);
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_alarmTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("alarmType", m_alarmType);
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
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram