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

#include <keo_datagram/supplycondition/SupplyConditionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionListDataSelectors::SupplyConditionListDataSelectors()
    : DataSelectors(), m_conditionIdIsSet(false), m_conditionId(0),
      m_timestampIntervalIsSet(false), m_timestampInterval(TimestampInterval()),
      m_eventTypeIsSet(false), m_eventType(SupplyConditionEventType()),
      m_originatorIsSet(false), m_originator(SupplyConditionOriginator())

{}

bool SupplyConditionListDataSelectors::
operator==(const SupplyConditionListDataSelectors &c_classObject) const {
  if (m_conditionIdIsSet != c_classObject.m_conditionIdIsSet ||
      (m_conditionIdIsSet && (m_conditionId != c_classObject.m_conditionId))) {
    return false;
  }
  if (m_timestampIntervalIsSet != c_classObject.m_timestampIntervalIsSet ||
      (m_timestampIntervalIsSet &&
       (m_timestampInterval != c_classObject.m_timestampInterval))) {
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

  return true;
}

bool SupplyConditionListDataSelectors::
operator!=(const SupplyConditionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionListDataSelectors::isEmpty() const {
  return !m_conditionIdIsSet && !m_timestampIntervalIsSet &&
         !m_eventTypeIsSet && !m_originatorIsSet;
}

DataSelectors::Type SupplyConditionListDataSelectors::getDataType() const {
  return DataSelectors::Type::SUPPLY_CONDITION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SupplyConditionListDataSelectors::clone() const {
  return std::make_shared<SupplyConditionListDataSelectors>(*this);
}

void SupplyConditionListDataSelectors::setConditionId(
    const xs_unsignedInt &conditionId) {
  m_conditionId = conditionId;
  m_conditionIdIsSet = true;
}

const xs_unsignedInt &SupplyConditionListDataSelectors::getConditionId() const {
  return m_conditionId;
}

void SupplyConditionListDataSelectors::cleanConditionId() {
  m_conditionId = 0;
  m_conditionIdIsSet = false;
}

bool SupplyConditionListDataSelectors::getConditionIdIsSet() const {
  return m_conditionIdIsSet;
}

void SupplyConditionListDataSelectors::setTimestampInterval(
    const TimestampInterval &timestampInterval) {
  m_timestampInterval = timestampInterval;
  m_timestampIntervalIsSet = true;
}

const TimestampInterval &
SupplyConditionListDataSelectors::getTimestampInterval() const {
  return m_timestampInterval;
}

void SupplyConditionListDataSelectors::cleanTimestampInterval() {
  m_timestampInterval = TimestampInterval();
  m_timestampIntervalIsSet = false;
}

bool SupplyConditionListDataSelectors::getTimestampIntervalIsSet() const {
  return m_timestampIntervalIsSet;
}

void SupplyConditionListDataSelectors::setEventType(
    const SupplyConditionEventType &eventType) {
  m_eventType = eventType;
  m_eventTypeIsSet = true;
}

const SupplyConditionEventType &
SupplyConditionListDataSelectors::getEventType() const {
  return m_eventType;
}

void SupplyConditionListDataSelectors::cleanEventType() {
  m_eventType = SupplyConditionEventType();
  m_eventTypeIsSet = false;
}

bool SupplyConditionListDataSelectors::getEventTypeIsSet() const {
  return m_eventTypeIsSet;
}

void SupplyConditionListDataSelectors::setOriginator(
    const SupplyConditionOriginator &originator) {
  m_originator = originator;
  m_originatorIsSet = true;
}

const SupplyConditionOriginator &
SupplyConditionListDataSelectors::getOriginator() const {
  return m_originator;
}

void SupplyConditionListDataSelectors::cleanOriginator() {
  m_originator = SupplyConditionOriginator();
  m_originatorIsSet = false;
}

bool SupplyConditionListDataSelectors::getOriginatorIsSet() const {
  return m_originatorIsSet;
}

bool SupplyConditionListDataSelectors::selects(
    const SupplyConditionData &data) const {
  if (getConditionIdIsSet() && (!data.getConditionIdIsSet() ||
                                getConditionId() != data.getConditionId())) {
    return false;
  }
  if (getTimestampIntervalIsSet() &&
      (!data.getTimestampIsSet() ||
       (data.getTimestamp().getDateTime() <
            getTimestampInterval().getStartTime().getDateTime() ||
        data.getTimestamp().getDateTime() >
            getTimestampInterval().getEndTime().getDateTime()))) {
    return false;
  }
  if (getEventTypeIsSet() &&
      (!data.getEventTypeIsSet() || getEventType() != data.getEventType())) {
    return false;
  }
  if (getOriginatorIsSet() &&
      (!data.getOriginatorIsSet() || getOriginator() != data.getOriginator())) {
    return false;
  }
  return true;
}

bool SupplyConditionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"conditionId", "timestampInterval", "eventType", "originator"})) {
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
                                   "timestampInterval", &m_timestampInterval)) {
      m_timestampIntervalIsSet = true;
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
  }
  return true;
}

std::string SupplyConditionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("conditionId", m_conditionId);
  }
  if (m_timestampIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timestampInterval", m_timestampInterval);
  }
  if (m_eventTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("eventType", m_eventType);
  }
  if (m_originatorIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("originator", m_originator);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram