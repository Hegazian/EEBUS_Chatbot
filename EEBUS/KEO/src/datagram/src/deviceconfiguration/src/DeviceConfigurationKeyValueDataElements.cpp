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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueDataElements::
    DeviceConfigurationKeyValueDataElements()
    : DataElements(), m_keyIdIsSet(false), m_valueIsSet(false),
      m_value(DeviceConfigurationKeyValueValueElements()),
      m_isValueChangeableIsSet(false)

{}

DeviceConfigurationKeyValueDataElements::
    DeviceConfigurationKeyValueDataElements(
        xs_boolean c_keyIdIsSet,
        const DeviceConfigurationKeyValueValueElements &c_value,
        xs_boolean c_isValueChangeableIsSet)
    : DataElements(), m_keyIdIsSet(c_keyIdIsSet), m_valueIsSet(true),
      m_value(c_value), m_isValueChangeableIsSet(c_isValueChangeableIsSet)

{}

bool DeviceConfigurationKeyValueDataElements::
operator==(const DeviceConfigurationKeyValueDataElements &c_classObject) const {
  if (m_keyIdIsSet != c_classObject.m_keyIdIsSet) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }
  if (m_isValueChangeableIsSet != c_classObject.m_isValueChangeableIsSet) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueDataElements::
operator!=(const DeviceConfigurationKeyValueDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueDataElements::isEmpty() const {
  return !m_keyIdIsSet && !m_valueIsSet && !m_isValueChangeableIsSet;
}

DataElements::Type
DeviceConfigurationKeyValueDataElements::getDataType() const {
  return DataElements::Type::DEVICE_CONFIGURATION_KEY_VALUE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr DeviceConfigurationKeyValueDataElements::clone() const {
  return std::make_shared<DeviceConfigurationKeyValueDataElements>(*this);
}

void DeviceConfigurationKeyValueDataElements::setKeyId() {
  m_keyIdIsSet = true;
}

void DeviceConfigurationKeyValueDataElements::cleanKeyId() {
  m_keyIdIsSet = false;
}

bool DeviceConfigurationKeyValueDataElements::getKeyIdIsSet() const {
  return m_keyIdIsSet;
}

void DeviceConfigurationKeyValueDataElements::setValue(
    const DeviceConfigurationKeyValueValueElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const DeviceConfigurationKeyValueValueElements &
DeviceConfigurationKeyValueDataElements::getValue() const {
  return m_value;
}

void DeviceConfigurationKeyValueDataElements::cleanValue() {
  m_value = DeviceConfigurationKeyValueValueElements();
  m_valueIsSet = false;
}

bool DeviceConfigurationKeyValueDataElements::getValueIsSet() const {
  return m_valueIsSet;
}

void DeviceConfigurationKeyValueDataElements::setIsValueChangeable() {
  m_isValueChangeableIsSet = true;
}

void DeviceConfigurationKeyValueDataElements::cleanIsValueChangeable() {
  m_isValueChangeableIsSet = false;
}

bool DeviceConfigurationKeyValueDataElements::getIsValueChangeableIsSet()
    const {
  return m_isValueChangeableIsSet;
}

bool DeviceConfigurationKeyValueDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"keyId", "value", "isValueChangeable"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "keyId")) {
      m_keyIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isValueChangeable")) {
      m_isValueChangeableIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceConfigurationKeyValueDataElements::toJson() const {
  std::string result = "[";
  if (m_keyIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("keyId");
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  if (m_isValueChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isValueChangeable");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram