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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionData.h>

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueDescriptionData::
    DeviceConfigurationKeyValueDescriptionData()
    : m_keyIdIsSet(false), m_keyId(0), m_keyNameIsSet(false),
      m_keyName(DeviceConfigurationKeyName()), m_valueTypeIsSet(false),
      m_valueType(DeviceConfigurationKeyValueType()), m_unitIsSet(false),
      m_unit(UnitOfMeasurement()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool DeviceConfigurationKeyValueDescriptionData::operator==(
    const DeviceConfigurationKeyValueDescriptionData &c_classObject) const {
  if (m_keyIdIsSet != c_classObject.m_keyIdIsSet ||
      (m_keyIdIsSet && (m_keyId != c_classObject.m_keyId))) {
    return false;
  }
  if (m_keyNameIsSet != c_classObject.m_keyNameIsSet ||
      (m_keyNameIsSet && (m_keyName != c_classObject.m_keyName))) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet ||
      (m_valueTypeIsSet && (m_valueType != c_classObject.m_valueType))) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
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

bool DeviceConfigurationKeyValueDescriptionData::operator!=(
    const DeviceConfigurationKeyValueDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueDescriptionData::isEmpty() const {
  return !m_keyIdIsSet && !m_keyNameIsSet && !m_valueTypeIsSet &&
         !m_unitIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

void DeviceConfigurationKeyValueDescriptionData::setKeyId(
    const xs_unsignedInt &keyId) {
  m_keyId = keyId;
  m_keyIdIsSet = true;
}

const xs_unsignedInt &
DeviceConfigurationKeyValueDescriptionData::getKeyId() const {
  return m_keyId;
}

void DeviceConfigurationKeyValueDescriptionData::cleanKeyId() {
  m_keyId = 0;
  m_keyIdIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionData::getKeyIdIsSet() const {
  return m_keyIdIsSet;
}

void DeviceConfigurationKeyValueDescriptionData::setKeyName(
    const DeviceConfigurationKeyName &keyName) {
  m_keyName = keyName;
  m_keyNameIsSet = true;
}

const DeviceConfigurationKeyName &
DeviceConfigurationKeyValueDescriptionData::getKeyName() const {
  return m_keyName;
}

void DeviceConfigurationKeyValueDescriptionData::cleanKeyName() {
  m_keyName = DeviceConfigurationKeyName();
  m_keyNameIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionData::getKeyNameIsSet() const {
  return m_keyNameIsSet;
}

void DeviceConfigurationKeyValueDescriptionData::setValueType(
    const DeviceConfigurationKeyValueType &valueType) {
  m_valueType = valueType;
  m_valueTypeIsSet = true;
}

const DeviceConfigurationKeyValueType &
DeviceConfigurationKeyValueDescriptionData::getValueType() const {
  return m_valueType;
}

void DeviceConfigurationKeyValueDescriptionData::cleanValueType() {
  m_valueType = DeviceConfigurationKeyValueType();
  m_valueTypeIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionData::getValueTypeIsSet() const {
  return m_valueTypeIsSet;
}

void DeviceConfigurationKeyValueDescriptionData::setUnit(
    const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &
DeviceConfigurationKeyValueDescriptionData::getUnit() const {
  return m_unit;
}

void DeviceConfigurationKeyValueDescriptionData::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionData::getUnitIsSet() const {
  return m_unitIsSet;
}

void DeviceConfigurationKeyValueDescriptionData::setLabel(
    const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &DeviceConfigurationKeyValueDescriptionData::getLabel() const {
  return m_label;
}

void DeviceConfigurationKeyValueDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void DeviceConfigurationKeyValueDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &
DeviceConfigurationKeyValueDescriptionData::getDescription() const {
  return m_description;
}

void DeviceConfigurationKeyValueDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

DeviceConfigurationKeyValueDescriptionData
DeviceConfigurationKeyValueDescriptionData::reduce(
    const DeviceConfigurationKeyValueDescriptionDataElements &elements) const {
  DeviceConfigurationKeyValueDescriptionData dataOut;
  if (getKeyIdIsSet() && elements.getKeyIdIsSet()) {
    dataOut.setKeyId(getKeyId());
  }
  if (getKeyNameIsSet() && elements.getKeyNameIsSet()) {
    dataOut.setKeyName(getKeyName());
  }
  if (getValueTypeIsSet() && elements.getValueTypeIsSet()) {
    dataOut.setValueType(getValueType());
  }
  if (getUnitIsSet() && elements.getUnitIsSet()) {
    dataOut.setUnit(getUnit());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool DeviceConfigurationKeyValueDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"keyId", "keyName", "valueType", "unit", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "keyId", &m_keyId)) {
      m_keyIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "keyName", &m_keyName)) {
      m_keyNameIsSet = true;
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
                                   "unit", &m_unit)) {
      m_unitIsSet = true;
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

std::string DeviceConfigurationKeyValueDescriptionData::toJson() const {
  std::string result = "[";
  if (m_keyIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("keyId", m_keyId);
  }
  if (m_keyNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("keyName", m_keyName);
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueType", m_valueType);
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
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