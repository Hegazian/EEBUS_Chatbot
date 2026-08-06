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

#include <keo_datagram/supplycondition/SupplyConditionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionDataElements::SupplyConditionDataElements()
    : DataElements(), m_conditionIdIsSet(false), m_timestampIsSet(false),
      m_eventTypeIsSet(false), m_originatorIsSet(false),
      m_thresholdIdIsSet(false), m_thresholdPercentageIsSet(false),
      m_thresholdPercentage(ScaledNumberElements()),
      m_relevantPeriodIsSet(false), m_relevantPeriod(TimePeriodElements()),
      m_descriptionIsSet(false), m_gridConditionIsSet(false)

{}

bool SupplyConditionDataElements::
operator==(const SupplyConditionDataElements &c_classObject) const {
  if (m_conditionIdIsSet != c_classObject.m_conditionIdIsSet) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_eventTypeIsSet != c_classObject.m_eventTypeIsSet) {
    return false;
  }
  if (m_originatorIsSet != c_classObject.m_originatorIsSet) {
    return false;
  }
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet) {
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
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }
  if (m_gridConditionIsSet != c_classObject.m_gridConditionIsSet) {
    return false;
  }

  return true;
}

bool SupplyConditionDataElements::
operator!=(const SupplyConditionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionDataElements::isEmpty() const {
  return !m_conditionIdIsSet && !m_timestampIsSet && !m_eventTypeIsSet &&
         !m_originatorIsSet && !m_thresholdIdIsSet &&
         !m_thresholdPercentageIsSet && !m_relevantPeriodIsSet &&
         !m_descriptionIsSet && !m_gridConditionIsSet;
}

DataElements::Type SupplyConditionDataElements::getDataType() const {
  return DataElements::Type::SUPPLY_CONDITION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SupplyConditionDataElements::clone() const {
  return std::make_shared<SupplyConditionDataElements>(*this);
}

void SupplyConditionDataElements::setConditionId() {
  m_conditionIdIsSet = true;
}

void SupplyConditionDataElements::cleanConditionId() {
  m_conditionIdIsSet = false;
}

bool SupplyConditionDataElements::getConditionIdIsSet() const {
  return m_conditionIdIsSet;
}

void SupplyConditionDataElements::setTimestamp() { m_timestampIsSet = true; }

void SupplyConditionDataElements::cleanTimestamp() { m_timestampIsSet = false; }

bool SupplyConditionDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void SupplyConditionDataElements::setEventType() { m_eventTypeIsSet = true; }

void SupplyConditionDataElements::cleanEventType() { m_eventTypeIsSet = false; }

bool SupplyConditionDataElements::getEventTypeIsSet() const {
  return m_eventTypeIsSet;
}

void SupplyConditionDataElements::setOriginator() { m_originatorIsSet = true; }

void SupplyConditionDataElements::cleanOriginator() {
  m_originatorIsSet = false;
}

bool SupplyConditionDataElements::getOriginatorIsSet() const {
  return m_originatorIsSet;
}

void SupplyConditionDataElements::setThresholdId() {
  m_thresholdIdIsSet = true;
}

void SupplyConditionDataElements::cleanThresholdId() {
  m_thresholdIdIsSet = false;
}

bool SupplyConditionDataElements::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void SupplyConditionDataElements::setThresholdPercentage(
    const ScaledNumberElements &thresholdPercentage) {
  m_thresholdPercentage = thresholdPercentage;
  m_thresholdPercentageIsSet = true;
}

const ScaledNumberElements &
SupplyConditionDataElements::getThresholdPercentage() const {
  return m_thresholdPercentage;
}

void SupplyConditionDataElements::cleanThresholdPercentage() {
  m_thresholdPercentage = ScaledNumberElements();
  m_thresholdPercentageIsSet = false;
}

bool SupplyConditionDataElements::getThresholdPercentageIsSet() const {
  return m_thresholdPercentageIsSet;
}

void SupplyConditionDataElements::setRelevantPeriod(
    const TimePeriodElements &relevantPeriod) {
  m_relevantPeriod = relevantPeriod;
  m_relevantPeriodIsSet = true;
}

const TimePeriodElements &
SupplyConditionDataElements::getRelevantPeriod() const {
  return m_relevantPeriod;
}

void SupplyConditionDataElements::cleanRelevantPeriod() {
  m_relevantPeriod = TimePeriodElements();
  m_relevantPeriodIsSet = false;
}

bool SupplyConditionDataElements::getRelevantPeriodIsSet() const {
  return m_relevantPeriodIsSet;
}

void SupplyConditionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void SupplyConditionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool SupplyConditionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void SupplyConditionDataElements::setGridCondition() {
  m_gridConditionIsSet = true;
}

void SupplyConditionDataElements::cleanGridCondition() {
  m_gridConditionIsSet = false;
}

bool SupplyConditionDataElements::getGridConditionIsSet() const {
  return m_gridConditionIsSet;
}

bool SupplyConditionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"conditionId", "timestamp", "eventType", "originator",
                   "thresholdId", "thresholdPercentage", "relevantPeriod",
                   "description", "gridCondition"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "conditionId")) {
      m_conditionIdIsSet = true;
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
                                     "eventType")) {
      m_eventTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "originator")) {
      m_originatorIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "thresholdId")) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "gridCondition")) {
      m_gridConditionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SupplyConditionDataElements::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("conditionId");
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_eventTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("eventType");
  }
  if (m_originatorIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("originator");
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thresholdId");
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
    result += KeoJsonTransformation::writeTag("description");
  }
  if (m_gridConditionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("gridCondition");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram