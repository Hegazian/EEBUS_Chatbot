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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsData.h>

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueConstraintsData::
    DeviceConfigurationKeyValueConstraintsData()
    : m_keyIdIsSet(false), m_keyId(0), m_valueRangeMinIsSet(false),
      m_valueRangeMin(DeviceConfigurationKeyValueValue()),
      m_valueRangeMaxIsSet(false),
      m_valueRangeMax(DeviceConfigurationKeyValueValue()),
      m_valueStepSizeIsSet(false),
      m_valueStepSize(DeviceConfigurationKeyValueValue())

{}

bool DeviceConfigurationKeyValueConstraintsData::operator==(
    const DeviceConfigurationKeyValueConstraintsData &c_classObject) const {
  if (m_keyIdIsSet != c_classObject.m_keyIdIsSet ||
      (m_keyIdIsSet && (m_keyId != c_classObject.m_keyId))) {
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

bool DeviceConfigurationKeyValueConstraintsData::operator!=(
    const DeviceConfigurationKeyValueConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueConstraintsData::isEmpty() const {
  return !m_keyIdIsSet && !m_valueRangeMinIsSet && !m_valueRangeMaxIsSet &&
         !m_valueStepSizeIsSet;
}

void DeviceConfigurationKeyValueConstraintsData::setKeyId(
    const xs_unsignedInt &keyId) {
  m_keyId = keyId;
  m_keyIdIsSet = true;
}

const xs_unsignedInt &
DeviceConfigurationKeyValueConstraintsData::getKeyId() const {
  return m_keyId;
}

void DeviceConfigurationKeyValueConstraintsData::cleanKeyId() {
  m_keyId = 0;
  m_keyIdIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsData::getKeyIdIsSet() const {
  return m_keyIdIsSet;
}

void DeviceConfigurationKeyValueConstraintsData::setValueRangeMin(
    const DeviceConfigurationKeyValueValue &valueRangeMin) {
  m_valueRangeMin = valueRangeMin;
  m_valueRangeMinIsSet = true;
}

const DeviceConfigurationKeyValueValue &
DeviceConfigurationKeyValueConstraintsData::getValueRangeMin() const {
  return m_valueRangeMin;
}

void DeviceConfigurationKeyValueConstraintsData::cleanValueRangeMin() {
  m_valueRangeMin = DeviceConfigurationKeyValueValue();
  m_valueRangeMinIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsData::getValueRangeMinIsSet() const {
  return m_valueRangeMinIsSet;
}

void DeviceConfigurationKeyValueConstraintsData::setValueRangeMax(
    const DeviceConfigurationKeyValueValue &valueRangeMax) {
  m_valueRangeMax = valueRangeMax;
  m_valueRangeMaxIsSet = true;
}

const DeviceConfigurationKeyValueValue &
DeviceConfigurationKeyValueConstraintsData::getValueRangeMax() const {
  return m_valueRangeMax;
}

void DeviceConfigurationKeyValueConstraintsData::cleanValueRangeMax() {
  m_valueRangeMax = DeviceConfigurationKeyValueValue();
  m_valueRangeMaxIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsData::getValueRangeMaxIsSet() const {
  return m_valueRangeMaxIsSet;
}

void DeviceConfigurationKeyValueConstraintsData::setValueStepSize(
    const DeviceConfigurationKeyValueValue &valueStepSize) {
  m_valueStepSize = valueStepSize;
  m_valueStepSizeIsSet = true;
}

const DeviceConfigurationKeyValueValue &
DeviceConfigurationKeyValueConstraintsData::getValueStepSize() const {
  return m_valueStepSize;
}

void DeviceConfigurationKeyValueConstraintsData::cleanValueStepSize() {
  m_valueStepSize = DeviceConfigurationKeyValueValue();
  m_valueStepSizeIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsData::getValueStepSizeIsSet() const {
  return m_valueStepSizeIsSet;
}

DeviceConfigurationKeyValueConstraintsData
DeviceConfigurationKeyValueConstraintsData::reduce(
    const DeviceConfigurationKeyValueConstraintsDataElements &elements) const {
  DeviceConfigurationKeyValueConstraintsData dataOut;
  if (getKeyIdIsSet() && elements.getKeyIdIsSet()) {
    dataOut.setKeyId(getKeyId());
  }
  if (getValueRangeMinIsSet() && elements.getValueRangeMinIsSet()) {
    dataOut.setValueRangeMin(
        getValueRangeMin().reduce(elements.getValueRangeMin()));
  }
  if (getValueRangeMaxIsSet() && elements.getValueRangeMaxIsSet()) {
    dataOut.setValueRangeMax(
        getValueRangeMax().reduce(elements.getValueRangeMax()));
  }
  if (getValueStepSizeIsSet() && elements.getValueStepSizeIsSet()) {
    dataOut.setValueStepSize(
        getValueStepSize().reduce(elements.getValueStepSize()));
  }
  return dataOut;
}

bool DeviceConfigurationKeyValueConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"keyId", "valueRangeMin", "valueRangeMax", "valueStepSize"})) {
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

std::string DeviceConfigurationKeyValueConstraintsData::toJson() const {
  std::string result = "[";
  if (m_keyIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("keyId", m_keyId);
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