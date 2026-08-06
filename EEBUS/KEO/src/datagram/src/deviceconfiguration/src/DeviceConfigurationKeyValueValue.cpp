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

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueValue.h>

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueValueElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueValue::DeviceConfigurationKeyValueValue()
    : m_booleanIsSet(false), m_boolean(false), m_dateIsSet(false),
      m_date(xs_date()), m_dateTimeIsSet(false), m_dateTime(xs_dateTime()),
      m_durationIsSet(false), m_duration(xs_duration()), m_stringIsSet(false),
      m_string(""), m_timeIsSet(false), m_time(xs_time()),
      m_scaledNumberIsSet(false), m_scaledNumber(ScaledNumber())

{}

bool DeviceConfigurationKeyValueValue::
operator==(const DeviceConfigurationKeyValueValue &c_classObject) const {
  if (m_booleanIsSet != c_classObject.m_booleanIsSet ||
      (m_booleanIsSet && (m_boolean != c_classObject.m_boolean))) {
    return false;
  }
  if (m_dateIsSet != c_classObject.m_dateIsSet ||
      (m_dateIsSet && (m_date != c_classObject.m_date))) {
    return false;
  }
  if (m_dateTimeIsSet != c_classObject.m_dateTimeIsSet ||
      (m_dateTimeIsSet && (m_dateTime != c_classObject.m_dateTime))) {
    return false;
  }
  if (m_durationIsSet != c_classObject.m_durationIsSet ||
      (m_durationIsSet && (m_duration != c_classObject.m_duration))) {
    return false;
  }
  if (m_stringIsSet != c_classObject.m_stringIsSet ||
      (m_stringIsSet && (m_string != c_classObject.m_string))) {
    return false;
  }
  if (m_timeIsSet != c_classObject.m_timeIsSet ||
      (m_timeIsSet && (m_time != c_classObject.m_time))) {
    return false;
  }
  if (m_scaledNumberIsSet != c_classObject.m_scaledNumberIsSet ||
      (m_scaledNumberIsSet &&
       (m_scaledNumber != c_classObject.m_scaledNumber))) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueValue::
operator!=(const DeviceConfigurationKeyValueValue &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueValue::isEmpty() const {
  return !m_booleanIsSet && !m_dateIsSet && !m_dateTimeIsSet &&
         !m_durationIsSet && !m_stringIsSet && !m_timeIsSet &&
         !m_scaledNumberIsSet;
}

void DeviceConfigurationKeyValueValue::setBoolean(const xs_boolean &boolean) {
  m_boolean = boolean;
  m_booleanIsSet = true;
}

const xs_boolean &DeviceConfigurationKeyValueValue::getBoolean() const {
  return m_boolean;
}

void DeviceConfigurationKeyValueValue::cleanBoolean() {
  m_boolean = false;
  m_booleanIsSet = false;
}

bool DeviceConfigurationKeyValueValue::getBooleanIsSet() const {
  return m_booleanIsSet;
}

void DeviceConfigurationKeyValueValue::setDate(const xs_date &date) {
  m_date = date;
  m_dateIsSet = true;
}

const xs_date &DeviceConfigurationKeyValueValue::getDate() const {
  return m_date;
}

void DeviceConfigurationKeyValueValue::cleanDate() {
  m_date = xs_date();
  m_dateIsSet = false;
}

bool DeviceConfigurationKeyValueValue::getDateIsSet() const {
  return m_dateIsSet;
}

void DeviceConfigurationKeyValueValue::setDateTime(
    const xs_dateTime &dateTime) {
  m_dateTime = dateTime;
  m_dateTimeIsSet = true;
}

const xs_dateTime &DeviceConfigurationKeyValueValue::getDateTime() const {
  return m_dateTime;
}

void DeviceConfigurationKeyValueValue::cleanDateTime() {
  m_dateTime = xs_dateTime();
  m_dateTimeIsSet = false;
}

bool DeviceConfigurationKeyValueValue::getDateTimeIsSet() const {
  return m_dateTimeIsSet;
}

void DeviceConfigurationKeyValueValue::setDuration(
    const xs_duration &duration) {
  m_duration = duration;
  m_durationIsSet = true;
}

const xs_duration &DeviceConfigurationKeyValueValue::getDuration() const {
  return m_duration;
}

void DeviceConfigurationKeyValueValue::cleanDuration() {
  m_duration = xs_duration();
  m_durationIsSet = false;
}

bool DeviceConfigurationKeyValueValue::getDurationIsSet() const {
  return m_durationIsSet;
}

void DeviceConfigurationKeyValueValue::setString(const xs_string &string) {
  m_string = string;
  m_stringIsSet = true;
}

const xs_string &DeviceConfigurationKeyValueValue::getString() const {
  return m_string;
}

void DeviceConfigurationKeyValueValue::cleanString() {
  m_string = "";
  m_stringIsSet = false;
}

bool DeviceConfigurationKeyValueValue::getStringIsSet() const {
  return m_stringIsSet;
}

void DeviceConfigurationKeyValueValue::setTime(const xs_time &time) {
  m_time = time;
  m_timeIsSet = true;
}

const xs_time &DeviceConfigurationKeyValueValue::getTime() const {
  return m_time;
}

void DeviceConfigurationKeyValueValue::cleanTime() {
  m_time = xs_time();
  m_timeIsSet = false;
}

bool DeviceConfigurationKeyValueValue::getTimeIsSet() const {
  return m_timeIsSet;
}

void DeviceConfigurationKeyValueValue::setScaledNumber(
    const ScaledNumber &scaledNumber) {
  m_scaledNumber = scaledNumber;
  m_scaledNumberIsSet = true;
}

const ScaledNumber &DeviceConfigurationKeyValueValue::getScaledNumber() const {
  return m_scaledNumber;
}

void DeviceConfigurationKeyValueValue::cleanScaledNumber() {
  m_scaledNumber = ScaledNumber();
  m_scaledNumberIsSet = false;
}

bool DeviceConfigurationKeyValueValue::getScaledNumberIsSet() const {
  return m_scaledNumberIsSet;
}

DeviceConfigurationKeyValueValue DeviceConfigurationKeyValueValue::reduce(
    const DeviceConfigurationKeyValueValueElements &elements) const {
  DeviceConfigurationKeyValueValue dataOut;
  if (getBooleanIsSet() && elements.getBooleanIsSet()) {
    dataOut.setBoolean(getBoolean());
  }
  if (getDateIsSet() && elements.getDateIsSet()) {
    dataOut.setDate(getDate());
  }
  if (getDateTimeIsSet() && elements.getDateTimeIsSet()) {
    dataOut.setDateTime(getDateTime());
  }
  if (getDurationIsSet() && elements.getDurationIsSet()) {
    dataOut.setDuration(getDuration());
  }
  if (getStringIsSet() && elements.getStringIsSet()) {
    dataOut.setString(getString());
  }
  if (getTimeIsSet() && elements.getTimeIsSet()) {
    dataOut.setTime(getTime());
  }
  if (getScaledNumberIsSet() && elements.getScaledNumberIsSet()) {
    dataOut.setScaledNumber(
        getScaledNumber().reduce(elements.getScaledNumber()));
  }
  return dataOut;
}

bool DeviceConfigurationKeyValueValue::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"boolean", "date", "dateTime", "duration", "string", "time",
                   "scaledNumber"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boolean", &m_boolean)) {
      m_booleanIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "date", &m_date)) {
      m_dateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "dateTime", &m_dateTime)) {
      m_dateTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "duration", &m_duration)) {
      m_durationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "string", &m_string)) {
      m_stringIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "time", &m_time)) {
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

std::string DeviceConfigurationKeyValueValue::toJson() const {
  std::string result = "[";
  if (m_booleanIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boolean", m_boolean);
  }
  if (m_dateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("date", m_date);
  }
  if (m_dateTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("dateTime", m_dateTime);
  }
  if (m_durationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("duration", m_duration);
  }
  if (m_stringIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("string", m_string);
  }
  if (m_timeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("time", m_time);
  }
  if (m_scaledNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scaledNumber", m_scaledNumber);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram