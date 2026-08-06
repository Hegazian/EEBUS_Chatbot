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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueConstraintsDataElements::
    DeviceConfigurationKeyValueConstraintsDataElements()
    : DataElements(), m_keyIdIsSet(false), m_valueRangeMinIsSet(false),
      m_valueRangeMin(DeviceConfigurationKeyValueValueElements()),
      m_valueRangeMaxIsSet(false),
      m_valueRangeMax(DeviceConfigurationKeyValueValueElements()),
      m_valueStepSizeIsSet(false),
      m_valueStepSize(DeviceConfigurationKeyValueValueElements())

{}

bool DeviceConfigurationKeyValueConstraintsDataElements::operator==(
    const DeviceConfigurationKeyValueConstraintsDataElements &c_classObject)
    const {
  if (m_keyIdIsSet != c_classObject.m_keyIdIsSet) {
    return false;
  }
  if (m_valueRangeMinIsSet != c_classObject.m_valueRangeMinIsSet ||
      (m_valueRangeMinIsSet &&
       (m_valueRangeMin != c_classObject.m_valueRangeMin))) {
    return false;
  }
  if (m_valueRangeMaxIsSet != c_classObject.m_valueRangeMaxIsSet ||
      (m_valueRangeMaxIsSet &&
       (m_valueRangeMax != c_classObject.m_valueRangeMax))) {
    return false;
  }
  if (m_valueStepSizeIsSet != c_classObject.m_valueStepSizeIsSet ||
      (m_valueStepSizeIsSet &&
       (m_valueStepSize != c_classObject.m_valueStepSize))) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueConstraintsDataElements::operator!=(
    const DeviceConfigurationKeyValueConstraintsDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueConstraintsDataElements::isEmpty() const {
  return !m_keyIdIsSet && !m_valueRangeMinIsSet && !m_valueRangeMaxIsSet &&
         !m_valueStepSizeIsSet;
}

DataElements::Type
DeviceConfigurationKeyValueConstraintsDataElements::getDataType() const {
  return DataElements::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
DeviceConfigurationKeyValueConstraintsDataElements::clone() const {
  return std::make_shared<DeviceConfigurationKeyValueConstraintsDataElements>(
      *this);
}

void DeviceConfigurationKeyValueConstraintsDataElements::setKeyId() {
  m_keyIdIsSet = true;
}

void DeviceConfigurationKeyValueConstraintsDataElements::cleanKeyId() {
  m_keyIdIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsDataElements::getKeyIdIsSet() const {
  return m_keyIdIsSet;
}

void DeviceConfigurationKeyValueConstraintsDataElements::setValueRangeMin(
    const DeviceConfigurationKeyValueValueElements &valueRangeMin) {
  m_valueRangeMin = valueRangeMin;
  m_valueRangeMinIsSet = true;
}

const DeviceConfigurationKeyValueValueElements &
DeviceConfigurationKeyValueConstraintsDataElements::getValueRangeMin() const {
  return m_valueRangeMin;
}

void DeviceConfigurationKeyValueConstraintsDataElements::cleanValueRangeMin() {
  m_valueRangeMin = DeviceConfigurationKeyValueValueElements();
  m_valueRangeMinIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsDataElements::getValueRangeMinIsSet()
    const {
  return m_valueRangeMinIsSet;
}

void DeviceConfigurationKeyValueConstraintsDataElements::setValueRangeMax(
    const DeviceConfigurationKeyValueValueElements &valueRangeMax) {
  m_valueRangeMax = valueRangeMax;
  m_valueRangeMaxIsSet = true;
}

const DeviceConfigurationKeyValueValueElements &
DeviceConfigurationKeyValueConstraintsDataElements::getValueRangeMax() const {
  return m_valueRangeMax;
}

void DeviceConfigurationKeyValueConstraintsDataElements::cleanValueRangeMax() {
  m_valueRangeMax = DeviceConfigurationKeyValueValueElements();
  m_valueRangeMaxIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsDataElements::getValueRangeMaxIsSet()
    const {
  return m_valueRangeMaxIsSet;
}

void DeviceConfigurationKeyValueConstraintsDataElements::setValueStepSize(
    const DeviceConfigurationKeyValueValueElements &valueStepSize) {
  m_valueStepSize = valueStepSize;
  m_valueStepSizeIsSet = true;
}

const DeviceConfigurationKeyValueValueElements &
DeviceConfigurationKeyValueConstraintsDataElements::getValueStepSize() const {
  return m_valueStepSize;
}

void DeviceConfigurationKeyValueConstraintsDataElements::cleanValueStepSize() {
  m_valueStepSize = DeviceConfigurationKeyValueValueElements();
  m_valueStepSizeIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsDataElements::getValueStepSizeIsSet()
    const {
  return m_valueStepSizeIsSet;
}

bool DeviceConfigurationKeyValueConstraintsDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"keyId", "valueRangeMin", "valueRangeMax", "valueStepSize"})) {
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
                                   "valueRangeMin", &m_valueRangeMin)) {
      m_valueRangeMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueRangeMax", &m_valueRangeMax)) {
      m_valueRangeMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueStepSize", &m_valueStepSize)) {
      m_valueStepSizeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceConfigurationKeyValueConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_keyIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("keyId");
  }
  if (m_valueRangeMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueRangeMin", m_valueRangeMin);
  }
  if (m_valueRangeMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueRangeMax", m_valueRangeMax);
  }
  if (m_valueStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueStepSize", m_valueStepSize);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram