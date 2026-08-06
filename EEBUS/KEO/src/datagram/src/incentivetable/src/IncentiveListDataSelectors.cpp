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

#include <keo_datagram/incentivetable/IncentiveListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveListDataSelectors::IncentiveListDataSelectors()
    : DataSelectors(), m_incentiveIdIsSet(false), m_incentiveId(0),
      m_valueTypeIsSet(false), m_valueType(IncentiveValueType()),
      m_timestampIntervalIsSet(false), m_timestampInterval(TimestampInterval())

{}

IncentiveListDataSelectors::IncentiveListDataSelectors(
    const xs_unsignedInt &c_incentiveId, const IncentiveValueType &c_valueType,
    const TimestampInterval &c_timestampInterval)
    : DataSelectors(), m_incentiveIdIsSet(true), m_incentiveId(c_incentiveId),
      m_valueTypeIsSet(true), m_valueType(c_valueType),
      m_timestampIntervalIsSet(true), m_timestampInterval(c_timestampInterval)

{}

bool IncentiveListDataSelectors::
operator==(const IncentiveListDataSelectors &c_classObject) const {
  if (m_incentiveIdIsSet != c_classObject.m_incentiveIdIsSet ||
      (m_incentiveIdIsSet && (m_incentiveId != c_classObject.m_incentiveId))) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet ||
      (m_valueTypeIsSet && (m_valueType != c_classObject.m_valueType))) {
    return false;
  }
  if (m_timestampIntervalIsSet != c_classObject.m_timestampIntervalIsSet ||
      (m_timestampIntervalIsSet &&
       (m_timestampInterval != c_classObject.m_timestampInterval))) {
    return false;
  }

  return true;
}

bool IncentiveListDataSelectors::
operator!=(const IncentiveListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveListDataSelectors::isEmpty() const {
  return !m_incentiveIdIsSet && !m_valueTypeIsSet && !m_timestampIntervalIsSet;
}

DataSelectors::Type IncentiveListDataSelectors::getDataType() const {
  return DataSelectors::Type::INCENTIVE_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr IncentiveListDataSelectors::clone() const {
  return std::make_shared<IncentiveListDataSelectors>(*this);
}

void IncentiveListDataSelectors::setIncentiveId(
    const xs_unsignedInt &incentiveId) {
  m_incentiveId = incentiveId;
  m_incentiveIdIsSet = true;
}

const xs_unsignedInt &IncentiveListDataSelectors::getIncentiveId() const {
  return m_incentiveId;
}

void IncentiveListDataSelectors::cleanIncentiveId() {
  m_incentiveId = 0;
  m_incentiveIdIsSet = false;
}

bool IncentiveListDataSelectors::getIncentiveIdIsSet() const {
  return m_incentiveIdIsSet;
}

void IncentiveListDataSelectors::setValueType(
    const IncentiveValueType &valueType) {
  m_valueType = valueType;
  m_valueTypeIsSet = true;
}

const IncentiveValueType &IncentiveListDataSelectors::getValueType() const {
  return m_valueType;
}

void IncentiveListDataSelectors::cleanValueType() {
  m_valueType = IncentiveValueType();
  m_valueTypeIsSet = false;
}

bool IncentiveListDataSelectors::getValueTypeIsSet() const {
  return m_valueTypeIsSet;
}

void IncentiveListDataSelectors::setTimestampInterval(
    const TimestampInterval &timestampInterval) {
  m_timestampInterval = timestampInterval;
  m_timestampIntervalIsSet = true;
}

const TimestampInterval &
IncentiveListDataSelectors::getTimestampInterval() const {
  return m_timestampInterval;
}

void IncentiveListDataSelectors::cleanTimestampInterval() {
  m_timestampInterval = TimestampInterval();
  m_timestampIntervalIsSet = false;
}

bool IncentiveListDataSelectors::getTimestampIntervalIsSet() const {
  return m_timestampIntervalIsSet;
}

bool IncentiveListDataSelectors::selects(const IncentiveData &data) const {
  if (getIncentiveIdIsSet() && (!data.getIncentiveIdIsSet() ||
                                getIncentiveId() != data.getIncentiveId())) {
    return false;
  }
  if (getValueTypeIsSet() &&
      (!data.getValueTypeIsSet() || getValueType() != data.getValueType())) {
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
  return true;
}

bool IncentiveListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveId", "valueType", "timestampInterval"})) {
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
                                   "timestampInterval", &m_timestampInterval)) {
      m_timestampIntervalIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_incentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveId", m_incentiveId);
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueType", m_valueType);
  }
  if (m_timestampIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timestampInterval", m_timestampInterval);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram