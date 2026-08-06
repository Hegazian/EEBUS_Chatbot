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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueListDataSelectors::
    DeviceConfigurationKeyValueListDataSelectors()
    : DataSelectors(), m_keyIdIsSet(false), m_keyId(0)

{}

DeviceConfigurationKeyValueListDataSelectors::
    DeviceConfigurationKeyValueListDataSelectors(
        const xs_unsignedInt &c_keyId) {
  setKeyId(c_keyId);
}

bool DeviceConfigurationKeyValueListDataSelectors::operator==(
    const DeviceConfigurationKeyValueListDataSelectors &c_classObject) const {
  if (m_keyIdIsSet != c_classObject.m_keyIdIsSet ||
      (m_keyIdIsSet && (m_keyId != c_classObject.m_keyId))) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueListDataSelectors::operator!=(
    const DeviceConfigurationKeyValueListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueListDataSelectors::isEmpty() const {
  return !m_keyIdIsSet;
}

DataSelectors::Type
DeviceConfigurationKeyValueListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr DeviceConfigurationKeyValueListDataSelectors::clone() const {
  return std::make_shared<DeviceConfigurationKeyValueListDataSelectors>(*this);
}

void DeviceConfigurationKeyValueListDataSelectors::setKeyId(
    const xs_unsignedInt &keyId) {
  m_keyId = keyId;
  m_keyIdIsSet = true;
}

const xs_unsignedInt &
DeviceConfigurationKeyValueListDataSelectors::getKeyId() const {
  return m_keyId;
}

void DeviceConfigurationKeyValueListDataSelectors::cleanKeyId() {
  m_keyId = 0;
  m_keyIdIsSet = false;
}

bool DeviceConfigurationKeyValueListDataSelectors::getKeyIdIsSet() const {
  return m_keyIdIsSet;
}

bool DeviceConfigurationKeyValueListDataSelectors::selects(
    const DeviceConfigurationKeyValueData &data) const {
  if (getKeyIdIsSet() &&
      (!data.getKeyIdIsSet() || getKeyId() != data.getKeyId())) {
    return false;
  }
  return true;
}

bool DeviceConfigurationKeyValueListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"keyId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "keyId", &m_keyId)) {
      m_keyIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceConfigurationKeyValueListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_keyIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("keyId", m_keyId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram