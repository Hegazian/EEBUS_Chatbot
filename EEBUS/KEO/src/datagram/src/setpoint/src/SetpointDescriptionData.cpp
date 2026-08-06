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

#include <keo_datagram/setpoint/SetpointDescriptionData.h>

#include <keo_datagram/setpoint/SetpointDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointDescriptionData::SetpointDescriptionData()
    : m_setpointIdIsSet(false), m_setpointId(0), m_measurementIdIsSet(false),
      m_measurementId(0), m_timeTableIdIsSet(false), m_timeTableId(0),
      m_setpointTypeIsSet(false), m_setpointType(SetpointType()),
      m_unitIsSet(false), m_unit(UnitOfMeasurement()), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool SetpointDescriptionData::
operator==(const SetpointDescriptionData &c_classObject) const {
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
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
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

bool SetpointDescriptionData::
operator!=(const SetpointDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointDescriptionData::isEmpty() const {
  return !m_setpointIdIsSet && !m_measurementIdIsSet && !m_timeTableIdIsSet &&
         !m_setpointTypeIsSet && !m_unitIsSet && !m_scopeTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

void SetpointDescriptionData::setSetpointId(const xs_unsignedInt &setpointId) {
  m_setpointId = setpointId;
  m_setpointIdIsSet = true;
}

const xs_unsignedInt &SetpointDescriptionData::getSetpointId() const {
  return m_setpointId;
}

void SetpointDescriptionData::cleanSetpointId() {
  m_setpointId = 0;
  m_setpointIdIsSet = false;
}

bool SetpointDescriptionData::getSetpointIdIsSet() const {
  return m_setpointIdIsSet;
}

void SetpointDescriptionData::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &SetpointDescriptionData::getMeasurementId() const {
  return m_measurementId;
}

void SetpointDescriptionData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool SetpointDescriptionData::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void SetpointDescriptionData::setTimeTableId(
    const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &SetpointDescriptionData::getTimeTableId() const {
  return m_timeTableId;
}

void SetpointDescriptionData::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool SetpointDescriptionData::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void SetpointDescriptionData::setSetpointType(
    const SetpointType &setpointType) {
  m_setpointType = setpointType;
  m_setpointTypeIsSet = true;
}

const SetpointType &SetpointDescriptionData::getSetpointType() const {
  return m_setpointType;
}

void SetpointDescriptionData::cleanSetpointType() {
  m_setpointType = SetpointType();
  m_setpointTypeIsSet = false;
}

bool SetpointDescriptionData::getSetpointTypeIsSet() const {
  return m_setpointTypeIsSet;
}

void SetpointDescriptionData::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &SetpointDescriptionData::getUnit() const {
  return m_unit;
}

void SetpointDescriptionData::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool SetpointDescriptionData::getUnitIsSet() const { return m_unitIsSet; }

void SetpointDescriptionData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &SetpointDescriptionData::getScopeType() const {
  return m_scopeType;
}

void SetpointDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool SetpointDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void SetpointDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &SetpointDescriptionData::getLabel() const { return m_label; }

void SetpointDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool SetpointDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void SetpointDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &SetpointDescriptionData::getDescription() const {
  return m_description;
}

void SetpointDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool SetpointDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

SetpointDescriptionData SetpointDescriptionData::reduce(
    const SetpointDescriptionDataElements &elements) const {
  SetpointDescriptionData dataOut;
  if (getSetpointIdIsSet() && elements.getSetpointIdIsSet()) {
    dataOut.setSetpointId(getSetpointId());
  }
  if (getMeasurementIdIsSet() && elements.getMeasurementIdIsSet()) {
    dataOut.setMeasurementId(getMeasurementId());
  }
  if (getTimeTableIdIsSet() && elements.getTimeTableIdIsSet()) {
    dataOut.setTimeTableId(getTimeTableId());
  }
  if (getSetpointTypeIsSet() && elements.getSetpointTypeIsSet()) {
    dataOut.setSetpointType(getSetpointType());
  }
  if (getUnitIsSet() && elements.getUnitIsSet()) {
    dataOut.setUnit(getUnit());
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

bool SetpointDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"setpointId", "measurementId", "timeTableId", "setpointType",
                   "unit", "scopeType", "label", "description"})) {
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
                                   "unit", &m_unit)) {
      m_unitIsSet = true;
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

std::string SetpointDescriptionData::toJson() const {
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
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
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