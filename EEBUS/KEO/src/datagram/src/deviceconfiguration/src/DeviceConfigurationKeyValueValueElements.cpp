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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueValueElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueValueElements::
    DeviceConfigurationKeyValueValueElements()
    : m_booleanIsSet(false), m_dateIsSet(false), m_dateTimeIsSet(false),
      m_durationIsSet(false), m_stringIsSet(false), m_timeIsSet(false),
      m_scaledNumberIsSet(false), m_scaledNumber(ScaledNumberElements())

{}

bool DeviceConfigurationKeyValueValueElements::operator==(
    const DeviceConfigurationKeyValueValueElements &c_classObject) const {
  if (m_booleanIsSet != c_classObject.m_booleanIsSet) {
    return false;
  }
  if (m_dateIsSet != c_classObject.m_dateIsSet) {
    return false;
  }
  if (m_dateTimeIsSet != c_classObject.m_dateTimeIsSet) {
    return false;
  }
  if (m_durationIsSet != c_classObject.m_durationIsSet) {
    return false;
  }
  if (m_stringIsSet != c_classObject.m_stringIsSet) {
    return false;
  }
  if (m_timeIsSet != c_classObject.m_timeIsSet) {
    return false;
  }
  if (m_scaledNumberIsSet != c_classObject.m_scaledNumberIsSet ||
      (m_scaledNumberIsSet &&
       (m_scaledNumber != c_classObject.m_scaledNumber))) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueValueElements::operator!=(
    const DeviceConfigurationKeyValueValueElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueValueElements::isEmpty() const {
  return !m_booleanIsSet && !m_dateIsSet && !m_dateTimeIsSet &&
         !m_durationIsSet && !m_stringIsSet && !m_timeIsSet &&
         !m_scaledNumberIsSet;
}

void DeviceConfigurationKeyValueValueElements::setBoolean() {
  m_booleanIsSet = true;
}

void DeviceConfigurationKeyValueValueElements::cleanBoolean() {
  m_booleanIsSet = false;
}

bool DeviceConfigurationKeyValueValueElements::getBooleanIsSet() const {
  return m_booleanIsSet;
}

void DeviceConfigurationKeyValueValueElements::setDate() { m_dateIsSet = true; }

void DeviceConfigurationKeyValueValueElements::cleanDate() {
  m_dateIsSet = false;
}

bool DeviceConfigurationKeyValueValueElements::getDateIsSet() const {
  return m_dateIsSet;
}

void DeviceConfigurationKeyValueValueElements::setDateTime() {
  m_dateTimeIsSet = true;
}

void DeviceConfigurationKeyValueValueElements::cleanDateTime() {
  m_dateTimeIsSet = false;
}

bool DeviceConfigurationKeyValueValueElements::getDateTimeIsSet() const {
  return m_dateTimeIsSet;
}

void DeviceConfigurationKeyValueValueElements::setDuration() {
  m_durationIsSet = true;
}

void DeviceConfigurationKeyValueValueElements::cleanDuration() {
  m_durationIsSet = false;
}

bool DeviceConfigurationKeyValueValueElements::getDurationIsSet() const {
  return m_durationIsSet;
}

void DeviceConfigurationKeyValueValueElements::setString() {
  m_stringIsSet = true;
}

void DeviceConfigurationKeyValueValueElements::cleanString() {
  m_stringIsSet = false;
}

bool DeviceConfigurationKeyValueValueElements::getStringIsSet() const {
  return m_stringIsSet;
}

void DeviceConfigurationKeyValueValueElements::setTime() { m_timeIsSet = true; }

void DeviceConfigurationKeyValueValueElements::cleanTime() {
  m_timeIsSet = false;
}

bool DeviceConfigurationKeyValueValueElements::getTimeIsSet() const {
  return m_timeIsSet;
}

void DeviceConfigurationKeyValueValueElements::setScaledNumber(
    const ScaledNumberElements &scaledNumber) {
  m_scaledNumber = scaledNumber;
  m_scaledNumberIsSet = true;
}

const ScaledNumberElements &
DeviceConfigurationKeyValueValueElements::getScaledNumber() const {
  return m_scaledNumber;
}

void DeviceConfigurationKeyValueValueElements::cleanScaledNumber() {
  m_scaledNumber = ScaledNumberElements();
  m_scaledNumberIsSet = false;
}

bool DeviceConfigurationKeyValueValueElements::getScaledNumberIsSet() const {
  return m_scaledNumberIsSet;
}

bool DeviceConfigurationKeyValueValueElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"boolean", "date", "dateTime", "duration", "string", "time",
                   "scaledNumber"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "boolean")) {
      m_booleanIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "date")) {
      m_dateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "dateTime")) {
      m_dateTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "duration")) {
      m_durationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "string")) {
      m_stringIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "time")) {
      m_timeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scaledNumber", &m_scaledNumber)) {
      m_scaledNumberIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceConfigurationKeyValueValueElements::toJson() const {
  std::string result = "[";
  if (m_booleanIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("boolean");
  }
  if (m_dateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("date");
  }
  if (m_dateTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("dateTime");
  }
  if (m_durationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("duration");
  }
  if (m_stringIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("string");
  }
  if (m_timeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("time");
  }
  if (m_scaledNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scaledNumber", m_scaledNumber);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram