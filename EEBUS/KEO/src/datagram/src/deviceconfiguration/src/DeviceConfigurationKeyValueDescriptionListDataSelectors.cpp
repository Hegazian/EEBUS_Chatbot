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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueDescriptionListDataSelectors::
    DeviceConfigurationKeyValueDescriptionListDataSelectors()
    : DataSelectors(), m_keyIdIsSet(false), m_keyId(0), m_keyNameIsSet(false),
      m_keyName(DeviceConfigurationKeyName())

{}

DeviceConfigurationKeyValueDescriptionListDataSelectors::
    DeviceConfigurationKeyValueDescriptionListDataSelectors(
        const xs_unsignedInt &c_keyId,
        const DeviceConfigurationKeyName &c_keyName)
    : DataSelectors(), m_keyIdIsSet(true), m_keyId(c_keyId),
      m_keyNameIsSet(true), m_keyName(c_keyName)

{}

bool DeviceConfigurationKeyValueDescriptionListDataSelectors::
operator==(const DeviceConfigurationKeyValueDescriptionListDataSelectors
               &c_classObject) const {
  if (m_keyIdIsSet != c_classObject.m_keyIdIsSet ||
      (m_keyIdIsSet && (m_keyId != c_classObject.m_keyId))) {
    return false;
  }
  if (m_keyNameIsSet != c_classObject.m_keyNameIsSet ||
      (m_keyNameIsSet && (m_keyName != c_classObject.m_keyName))) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueDescriptionListDataSelectors::
operator!=(const DeviceConfigurationKeyValueDescriptionListDataSelectors
               &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueDescriptionListDataSelectors::isEmpty() const {
  return !m_keyIdIsSet && !m_keyNameIsSet;
}

DataSelectors::Type
DeviceConfigurationKeyValueDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
DeviceConfigurationKeyValueDescriptionListDataSelectors::clone() const {
  return std::make_shared<
      DeviceConfigurationKeyValueDescriptionListDataSelectors>(*this);
}

void DeviceConfigurationKeyValueDescriptionListDataSelectors::setKeyId(
    const xs_unsignedInt &keyId) {
  m_keyId = keyId;
  m_keyIdIsSet = true;
}

const xs_unsignedInt &
DeviceConfigurationKeyValueDescriptionListDataSelectors::getKeyId() const {
  return m_keyId;
}

void DeviceConfigurationKeyValueDescriptionListDataSelectors::cleanKeyId() {
  m_keyId = 0;
  m_keyIdIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionListDataSelectors::getKeyIdIsSet()
    const {
  return m_keyIdIsSet;
}

void DeviceConfigurationKeyValueDescriptionListDataSelectors::setKeyName(
    const DeviceConfigurationKeyName &keyName) {
  m_keyName = keyName;
  m_keyNameIsSet = true;
}

const DeviceConfigurationKeyName &
DeviceConfigurationKeyValueDescriptionListDataSelectors::getKeyName() const {
  return m_keyName;
}

void DeviceConfigurationKeyValueDescriptionListDataSelectors::cleanKeyName() {
  m_keyName = DeviceConfigurationKeyName();
  m_keyNameIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionListDataSelectors::getKeyNameIsSet()
    const {
  return m_keyNameIsSet;
}

bool DeviceConfigurationKeyValueDescriptionListDataSelectors::selects(
    const DeviceConfigurationKeyValueDescriptionData &data) const {
  if (getKeyIdIsSet() &&
      (!data.getKeyIdIsSet() || getKeyId() != data.getKeyId())) {
    return false;
  }
  if (getKeyNameIsSet() &&
      (!data.getKeyNameIsSet() || getKeyName() != data.getKeyName())) {
    return false;
  }
  return true;
}

bool DeviceConfigurationKeyValueDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"keyId", "keyName"})) {
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
  }
  return true;
}

std::string
DeviceConfigurationKeyValueDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_keyIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("keyId", m_keyId);
  }
  if (m_keyNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("keyName", m_keyName);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram