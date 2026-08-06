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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueDescriptionDataElements::
    DeviceConfigurationKeyValueDescriptionDataElements()
    : DataElements(), m_keyIdIsSet(false), m_keyNameIsSet(false),
      m_valueTypeIsSet(false), m_unitIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool DeviceConfigurationKeyValueDescriptionDataElements::operator==(
    const DeviceConfigurationKeyValueDescriptionDataElements &c_classObject)
    const {
  if (m_keyIdIsSet != c_classObject.m_keyIdIsSet) {
    return false;
  }
  if (m_keyNameIsSet != c_classObject.m_keyNameIsSet) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueDescriptionDataElements::operator!=(
    const DeviceConfigurationKeyValueDescriptionDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueDescriptionDataElements::isEmpty() const {
  return !m_keyIdIsSet && !m_keyNameIsSet && !m_valueTypeIsSet &&
         !m_unitIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type
DeviceConfigurationKeyValueDescriptionDataElements::getDataType() const {
  return DataElements::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
DeviceConfigurationKeyValueDescriptionDataElements::clone() const {
  return std::make_shared<DeviceConfigurationKeyValueDescriptionDataElements>(
      *this);
}

void DeviceConfigurationKeyValueDescriptionDataElements::setKeyId() {
  m_keyIdIsSet = true;
}

void DeviceConfigurationKeyValueDescriptionDataElements::cleanKeyId() {
  m_keyIdIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionDataElements::getKeyIdIsSet() const {
  return m_keyIdIsSet;
}

void DeviceConfigurationKeyValueDescriptionDataElements::setKeyName() {
  m_keyNameIsSet = true;
}

void DeviceConfigurationKeyValueDescriptionDataElements::cleanKeyName() {
  m_keyNameIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionDataElements::getKeyNameIsSet()
    const {
  return m_keyNameIsSet;
}

void DeviceConfigurationKeyValueDescriptionDataElements::setValueType() {
  m_valueTypeIsSet = true;
}

void DeviceConfigurationKeyValueDescriptionDataElements::cleanValueType() {
  m_valueTypeIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionDataElements::getValueTypeIsSet()
    const {
  return m_valueTypeIsSet;
}

void DeviceConfigurationKeyValueDescriptionDataElements::setUnit() {
  m_unitIsSet = true;
}

void DeviceConfigurationKeyValueDescriptionDataElements::cleanUnit() {
  m_unitIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionDataElements::getUnitIsSet() const {
  return m_unitIsSet;
}

void DeviceConfigurationKeyValueDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void DeviceConfigurationKeyValueDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void DeviceConfigurationKeyValueDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void DeviceConfigurationKeyValueDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionDataElements::getDescriptionIsSet()
    const {
  return m_descriptionIsSet;
}

bool DeviceConfigurationKeyValueDescriptionDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"keyId", "keyName", "valueType", "unit", "label",
                   "description"})) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "keyName")) {
      m_keyNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "valueType")) {
      m_valueTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "unit")) {
      m_unitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceConfigurationKeyValueDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_keyIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("keyId");
  }
  if (m_keyNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("keyName");
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("valueType");
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("unit");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram