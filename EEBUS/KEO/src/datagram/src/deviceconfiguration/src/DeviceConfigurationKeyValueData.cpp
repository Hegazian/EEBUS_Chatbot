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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueData.h>

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueData::DeviceConfigurationKeyValueData()
    : m_keyIdIsSet(false), m_keyId(0), m_valueIsSet(false),
      m_value(DeviceConfigurationKeyValueValue()),
      m_isValueChangeableIsSet(false), m_isValueChangeable(false)

{}

DeviceConfigurationKeyValueData::DeviceConfigurationKeyValueData(
    const xs_unsignedInt &c_keyId,
    const DeviceConfigurationKeyValueValue &c_value,
    const xs_boolean &c_isValueChangeable)
    : m_keyIdIsSet(true), m_keyId(c_keyId), m_valueIsSet(true),
      m_value(c_value), m_isValueChangeableIsSet(true),
      m_isValueChangeable(c_isValueChangeable)

{}

bool DeviceConfigurationKeyValueData::
operator==(const DeviceConfigurationKeyValueData &c_classObject) const {
  if (m_keyIdIsSet != c_classObject.m_keyIdIsSet ||
      (m_keyIdIsSet && (m_keyId != c_classObject.m_keyId))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }
  if (m_isValueChangeableIsSet != c_classObject.m_isValueChangeableIsSet ||
      (m_isValueChangeableIsSet &&
       (m_isValueChangeable != c_classObject.m_isValueChangeable))) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueData::
operator!=(const DeviceConfigurationKeyValueData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueData::isEmpty() const {
  return !m_keyIdIsSet && !m_valueIsSet && !m_isValueChangeableIsSet;
}

void DeviceConfigurationKeyValueData::setKeyId(const xs_unsignedInt &keyId) {
  m_keyId = keyId;
  m_keyIdIsSet = true;
}

const xs_unsignedInt &DeviceConfigurationKeyValueData::getKeyId() const {
  return m_keyId;
}

void DeviceConfigurationKeyValueData::cleanKeyId() {
  m_keyId = 0;
  m_keyIdIsSet = false;
}

bool DeviceConfigurationKeyValueData::getKeyIdIsSet() const {
  return m_keyIdIsSet;
}

void DeviceConfigurationKeyValueData::setValue(
    const DeviceConfigurationKeyValueValue &value) {
  m_value = value;
  m_valueIsSet = true;
}

const DeviceConfigurationKeyValueValue &
DeviceConfigurationKeyValueData::getValue() const {
  return m_value;
}

void DeviceConfigurationKeyValueData::cleanValue() {
  m_value = DeviceConfigurationKeyValueValue();
  m_valueIsSet = false;
}

bool DeviceConfigurationKeyValueData::getValueIsSet() const {
  return m_valueIsSet;
}

void DeviceConfigurationKeyValueData::setIsValueChangeable(
    const xs_boolean &isValueChangeable) {
  m_isValueChangeable = isValueChangeable;
  m_isValueChangeableIsSet = true;
}

const xs_boolean &
DeviceConfigurationKeyValueData::getIsValueChangeable() const {
  return m_isValueChangeable;
}

void DeviceConfigurationKeyValueData::cleanIsValueChangeable() {
  m_isValueChangeable = false;
  m_isValueChangeableIsSet = false;
}

bool DeviceConfigurationKeyValueData::getIsValueChangeableIsSet() const {
  return m_isValueChangeableIsSet;
}

DeviceConfigurationKeyValueData DeviceConfigurationKeyValueData::reduce(
    const DeviceConfigurationKeyValueDataElements &elements) const {
  DeviceConfigurationKeyValueData dataOut;
  if (getKeyIdIsSet() && elements.getKeyIdIsSet()) {
    dataOut.setKeyId(getKeyId());
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    dataOut.setValue(getValue().reduce(elements.getValue()));
  }
  if (getIsValueChangeableIsSet() && elements.getIsValueChangeableIsSet()) {
    dataOut.setIsValueChangeable(getIsValueChangeable());
  }
  return dataOut;
}

bool DeviceConfigurationKeyValueData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"keyId", "value", "isValueChangeable"})) {
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
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isValueChangeable", &m_isValueChangeable)) {
      m_isValueChangeableIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceConfigurationKeyValueData::toJson() const {
  std::string result = "[";
  if (m_keyIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("keyId", m_keyId);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  if (m_isValueChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("isValueChangeable", m_isValueChangeable);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram