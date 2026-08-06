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

#include <keo_datagram/alarm/AlarmListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

AlarmListDataSelectors::AlarmListDataSelectors()
    : DataSelectors(), m_alarmIdIsSet(false), m_alarmId(0),
      m_scopeTypeIsSet(false), m_scopeType(ScopeType())

{}

AlarmListDataSelectors::AlarmListDataSelectors(const xs_unsignedInt &c_alarmId,
                                               const ScopeType &c_scopeType)
    : DataSelectors(), m_alarmIdIsSet(true), m_alarmId(c_alarmId),
      m_scopeTypeIsSet(true), m_scopeType(c_scopeType)

{}

bool AlarmListDataSelectors::
operator==(const AlarmListDataSelectors &c_classObject) const {
  if (m_alarmIdIsSet != c_classObject.m_alarmIdIsSet ||
      (m_alarmIdIsSet && (m_alarmId != c_classObject.m_alarmId))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool AlarmListDataSelectors::
operator!=(const AlarmListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool AlarmListDataSelectors::isEmpty() const {
  return !m_alarmIdIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type AlarmListDataSelectors::getDataType() const {
  return DataSelectors::Type::ALARM_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr AlarmListDataSelectors::clone() const {
  return std::make_shared<AlarmListDataSelectors>(*this);
}

void AlarmListDataSelectors::setAlarmId(const xs_unsignedInt &alarmId) {
  m_alarmId = alarmId;
  m_alarmIdIsSet = true;
}

const xs_unsignedInt &AlarmListDataSelectors::getAlarmId() const {
  return m_alarmId;
}

void AlarmListDataSelectors::cleanAlarmId() {
  m_alarmId = 0;
  m_alarmIdIsSet = false;
}

bool AlarmListDataSelectors::getAlarmIdIsSet() const { return m_alarmIdIsSet; }

void AlarmListDataSelectors::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &AlarmListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void AlarmListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool AlarmListDataSelectors::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool AlarmListDataSelectors::selects(const AlarmData &data) const {
  if (getAlarmIdIsSet() &&
      (!data.getAlarmIdIsSet() || getAlarmId() != data.getAlarmId())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool AlarmListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"alarmId", "scopeType"})) {
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
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string AlarmListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_alarmIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("alarmId", m_alarmId);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram