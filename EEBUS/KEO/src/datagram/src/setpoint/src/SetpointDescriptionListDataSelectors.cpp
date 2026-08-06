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

#include <keo_datagram/setpoint/SetpointDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointDescriptionListDataSelectors::SetpointDescriptionListDataSelectors()
    : DataSelectors(), m_setpointIdIsSet(false), m_setpointId(0),
      m_measurementIdIsSet(false), m_measurementId(0),
      m_timeTableIdIsSet(false), m_timeTableId(0), m_setpointTypeIsSet(false),
      m_setpointType(SetpointType()), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType())

{}

bool SetpointDescriptionListDataSelectors::
operator==(const SetpointDescriptionListDataSelectors &c_classObject) const {
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet ||
      (m_setpointIdIsSet && (m_setpointId != c_classObject.m_setpointId))) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
    return false;
  }
  if (m_setpointTypeIsSet != c_classObject.m_setpointTypeIsSet ||
      (m_setpointTypeIsSet &&
       (m_setpointType != c_classObject.m_setpointType))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool SetpointDescriptionListDataSelectors::
operator!=(const SetpointDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointDescriptionListDataSelectors::isEmpty() const {
  return !m_setpointIdIsSet && !m_measurementIdIsSet && !m_timeTableIdIsSet &&
         !m_setpointTypeIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type SetpointDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::SETPOINT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SetpointDescriptionListDataSelectors::clone() const {
  return std::make_shared<SetpointDescriptionListDataSelectors>(*this);
}

void SetpointDescriptionListDataSelectors::setSetpointId(
    const xs_unsignedInt &setpointId) {
  m_setpointId = setpointId;
  m_setpointIdIsSet = true;
}

const xs_unsignedInt &
SetpointDescriptionListDataSelectors::getSetpointId() const {
  return m_setpointId;
}

void SetpointDescriptionListDataSelectors::cleanSetpointId() {
  m_setpointId = 0;
  m_setpointIdIsSet = false;
}

bool SetpointDescriptionListDataSelectors::getSetpointIdIsSet() const {
  return m_setpointIdIsSet;
}

void SetpointDescriptionListDataSelectors::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
SetpointDescriptionListDataSelectors::getMeasurementId() const {
  return m_measurementId;
}

void SetpointDescriptionListDataSelectors::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool SetpointDescriptionListDataSelectors::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void SetpointDescriptionListDataSelectors::setTimeTableId(
    const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &
SetpointDescriptionListDataSelectors::getTimeTableId() const {
  return m_timeTableId;
}

void SetpointDescriptionListDataSelectors::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool SetpointDescriptionListDataSelectors::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void SetpointDescriptionListDataSelectors::setSetpointType(
    const SetpointType &setpointType) {
  m_setpointType = setpointType;
  m_setpointTypeIsSet = true;
}

const SetpointType &
SetpointDescriptionListDataSelectors::getSetpointType() const {
  return m_setpointType;
}

void SetpointDescriptionListDataSelectors::cleanSetpointType() {
  m_setpointType = SetpointType();
  m_setpointTypeIsSet = false;
}

bool SetpointDescriptionListDataSelectors::getSetpointTypeIsSet() const {
  return m_setpointTypeIsSet;
}

void SetpointDescriptionListDataSelectors::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &SetpointDescriptionListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void SetpointDescriptionListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool SetpointDescriptionListDataSelectors::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool SetpointDescriptionListDataSelectors::selects(
    const SetpointDescriptionData &data) const {
  if (getSetpointIdIsSet() &&
      (!data.getSetpointIdIsSet() || getSetpointId() != data.getSetpointId())) {
    return false;
  }
  if (getMeasurementIdIsSet() &&
      (!data.getMeasurementIdIsSet() ||
       getMeasurementId() != data.getMeasurementId())) {
    return false;
  }
  if (getTimeTableIdIsSet() && (!data.getTimeTableIdIsSet() ||
                                getTimeTableId() != data.getTimeTableId())) {
    return false;
  }
  if (getSetpointTypeIsSet() && (!data.getSetpointTypeIsSet() ||
                                 getSetpointType() != data.getSetpointType())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool SetpointDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"setpointId", "measurementId", "timeTableId", "setpointType",
                   "scopeType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "setpointId", &m_setpointId)) {
      m_setpointIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
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
                                   "setpointType", &m_setpointType)) {
      m_setpointTypeIsSet = true;
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

std::string SetpointDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("setpointId", m_setpointId);
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  if (m_setpointTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("setpointType", m_setpointType);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram