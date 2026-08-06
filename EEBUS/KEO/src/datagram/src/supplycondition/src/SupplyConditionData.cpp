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

#include <keo_datagram/supplycondition/SupplyConditionData.h>

#include <keo_datagram/supplycondition/SupplyConditionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionData::SupplyConditionData()
    : m_conditionIdIsSet(false), m_conditionId(0), m_timestampIsSet(false),
      m_timestamp(AbsoluteOrRelativeTime()), m_eventTypeIsSet(false),
      m_eventType(SupplyConditionEventType()), m_originatorIsSet(false),
      m_originator(SupplyConditionOriginator()), m_thresholdIdIsSet(false),
      m_thresholdId(0), m_thresholdPercentageIsSet(false),
      m_thresholdPercentage(ScaledNumber()), m_relevantPeriodIsSet(false),
      m_relevantPeriod(TimePeriod()), m_descriptionIsSet(false),
      m_description(""), m_gridConditionIsSet(false),
      m_gridCondition(GridCondition())

{}

bool SupplyConditionData::
operator==(const SupplyConditionData &c_classObject) const {
  if (m_conditionIdIsSet != c_classObject.m_conditionIdIsSet ||
      (m_conditionIdIsSet && (m_conditionId != c_classObject.m_conditionId))) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_eventTypeIsSet != c_classObject.m_eventTypeIsSet ||
      (m_eventTypeIsSet && (m_eventType != c_classObject.m_eventType))) {
    return false;
  }
  if (m_originatorIsSet != c_classObject.m_originatorIsSet ||
      (m_originatorIsSet && (m_originator != c_classObject.m_originator))) {
    return false;
  }
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }
  if (m_thresholdPercentageIsSet != c_classObject.m_thresholdPercentageIsSet ||
      (m_thresholdPercentageIsSet &&
       (m_thresholdPercentage != c_classObject.m_thresholdPercentage))) {
    return false;
  }
  if (m_relevantPeriodIsSet != c_classObject.m_relevantPeriodIsSet ||
      (m_relevantPeriodIsSet &&
       (m_relevantPeriod != c_classObject.m_relevantPeriod))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }
  if (m_gridConditionIsSet != c_classObject.m_gridConditionIsSet ||
      (m_gridConditionIsSet &&
       (m_gridCondition != c_classObject.m_gridCondition))) {
    return false;
  }

  return true;
}

bool SupplyConditionData::
operator!=(const SupplyConditionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionData::isEmpty() const {
  return !m_conditionIdIsSet && !m_timestampIsSet && !m_eventTypeIsSet &&
         !m_originatorIsSet && !m_thresholdIdIsSet &&
         !m_thresholdPercentageIsSet && !m_relevantPeriodIsSet &&
         !m_descriptionIsSet && !m_gridConditionIsSet;
}

void SupplyConditionData::setConditionId(const xs_unsignedInt &conditionId) {
  m_conditionId = conditionId;
  m_conditionIdIsSet = true;
}

const xs_unsignedInt &SupplyConditionData::getConditionId() const {
  return m_conditionId;
}

void SupplyConditionData::cleanConditionId() {
  m_conditionId = 0;
  m_conditionIdIsSet = false;
}

bool SupplyConditionData::getConditionIdIsSet() const {
  return m_conditionIdIsSet;
}

void SupplyConditionData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &SupplyConditionData::getTimestamp() const {
  return m_timestamp;
}

void SupplyConditionData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool SupplyConditionData::getTimestampIsSet() const { return m_timestampIsSet; }

void SupplyConditionData::setEventType(
    const SupplyConditionEventType &eventType) {
  m_eventType = eventType;
  m_eventTypeIsSet = true;
}

const SupplyConditionEventType &SupplyConditionData::getEventType() const {
  return m_eventType;
}

void SupplyConditionData::cleanEventType() {
  m_eventType = SupplyConditionEventType();
  m_eventTypeIsSet = false;
}

bool SupplyConditionData::getEventTypeIsSet() const { return m_eventTypeIsSet; }

void SupplyConditionData::setOriginator(
    const SupplyConditionOriginator &originator) {
  m_originator = originator;
  m_originatorIsSet = true;
}

const SupplyConditionOriginator &SupplyConditionData::getOriginator() const {
  return m_originator;
}

void SupplyConditionData::cleanOriginator() {
  m_originator = SupplyConditionOriginator();
  m_originatorIsSet = false;
}

bool SupplyConditionData::getOriginatorIsSet() const {
  return m_originatorIsSet;
}

void SupplyConditionData::setThresholdId(const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &SupplyConditionData::getThresholdId() const {
  return m_thresholdId;
}

void SupplyConditionData::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool SupplyConditionData::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void SupplyConditionData::setThresholdPercentage(
    const ScaledNumber &thresholdPercentage) {
  m_thresholdPercentage = thresholdPercentage;
  m_thresholdPercentageIsSet = true;
}

const ScaledNumber &SupplyConditionData::getThresholdPercentage() const {
  return m_thresholdPercentage;
}

void SupplyConditionData::cleanThresholdPercentage() {
  m_thresholdPercentage = ScaledNumber();
  m_thresholdPercentageIsSet = false;
}

bool SupplyConditionData::getThresholdPercentageIsSet() const {
  return m_thresholdPercentageIsSet;
}

void SupplyConditionData::setRelevantPeriod(const TimePeriod &relevantPeriod) {
  m_relevantPeriod = relevantPeriod;
  m_relevantPeriodIsSet = true;
}

const TimePeriod &SupplyConditionData::getRelevantPeriod() const {
  return m_relevantPeriod;
}

void SupplyConditionData::cleanRelevantPeriod() {
  m_relevantPeriod = TimePeriod();
  m_relevantPeriodIsSet = false;
}

bool SupplyConditionData::getRelevantPeriodIsSet() const {
  return m_relevantPeriodIsSet;
}

void SupplyConditionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &SupplyConditionData::getDescription() const {
  return m_description;
}

void SupplyConditionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool SupplyConditionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void SupplyConditionData::setGridCondition(const GridCondition &gridCondition) {
  m_gridCondition = gridCondition;
  m_gridConditionIsSet = true;
}

const GridCondition &SupplyConditionData::getGridCondition() const {
  return m_gridCondition;
}

void SupplyConditionData::cleanGridCondition() {
  m_gridCondition = GridCondition();
  m_gridConditionIsSet = false;
}

bool SupplyConditionData::getGridConditionIsSet() const {
  return m_gridConditionIsSet;
}

SupplyConditionData
SupplyConditionData::reduce(const SupplyConditionDataElements &elements) const {
  SupplyConditionData dataOut;
  if (getConditionIdIsSet() && elements.getConditionIdIsSet()) {
    dataOut.setConditionId(getConditionId());
  }
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getEventTypeIsSet() && elements.getEventTypeIsSet()) {
    dataOut.setEventType(getEventType());
  }
  if (getOriginatorIsSet() && elements.getOriginatorIsSet()) {
    dataOut.setOriginator(getOriginator());
  }
  if (getThresholdIdIsSet() && elements.getThresholdIdIsSet()) {
    dataOut.setThresholdId(getThresholdId());
  }
  if (getThresholdPercentageIsSet() && elements.getThresholdPercentageIsSet()) {
    dataOut.setThresholdPercentage(
        getThresholdPercentage().reduce(elements.getThresholdPercentage()));
  }
  if (getRelevantPeriodIsSet() && elements.getRelevantPeriodIsSet()) {
    dataOut.setRelevantPeriod(
        getRelevantPeriod().reduce(elements.getRelevantPeriod()));
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  if (getGridConditionIsSet() && elements.getGridConditionIsSet()) {
    dataOut.setGridCondition(getGridCondition());
  }
  return dataOut;
}

bool SupplyConditionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"conditionId", "timestamp", "eventType", "originator",
                   "thresholdId", "thresholdPercentage", "relevantPeriod",
                   "description", "gridCondition"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "conditionId", &m_conditionId)) {
      m_conditionIdIsSet = true;
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
                                   "eventType", &m_eventType)) {
      m_eventTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "originator", &m_originator)) {
      m_originatorIsSet = true;
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
                                   "thresholdPercentage",
                                   &m_thresholdPercentage)) {
      m_thresholdPercentageIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "relevantPeriod", &m_relevantPeriod)) {
      m_relevantPeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "gridCondition", &m_gridCondition)) {
      m_gridConditionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SupplyConditionData::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("conditionId", m_conditionId);
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_eventTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("eventType", m_eventType);
  }
  if (m_originatorIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("originator", m_originator);
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  if (m_thresholdPercentageIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdPercentage",
                                           m_thresholdPercentage);
  }
  if (m_relevantPeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("relevantPeriod", m_relevantPeriod);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  if (m_gridConditionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("gridCondition", m_gridCondition);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram