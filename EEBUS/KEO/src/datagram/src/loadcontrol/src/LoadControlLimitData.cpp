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

#include <keo_datagram/loadcontrol/LoadControlLimitData.h>

#include <keo_datagram/loadcontrol/LoadControlLimitDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitData::LoadControlLimitData()
    : m_limitIdIsSet(false), m_limitId(0), m_isLimitChangeableIsSet(false),
      m_isLimitChangeable(false), m_isLimitActiveIsSet(false),
      m_isLimitActive(false), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriod()), m_valueIsSet(false), m_value(ScaledNumber())

{}

bool LoadControlLimitData::
operator==(const LoadControlLimitData &c_classObject) const {
  if (m_limitIdIsSet != c_classObject.m_limitIdIsSet ||
      (m_limitIdIsSet && (m_limitId != c_classObject.m_limitId))) {
    return false;
  }
  if (m_isLimitChangeableIsSet != c_classObject.m_isLimitChangeableIsSet ||
      (m_isLimitChangeableIsSet &&
       (m_isLimitChangeable != c_classObject.m_isLimitChangeable))) {
    return false;
  }
  if (m_isLimitActiveIsSet != c_classObject.m_isLimitActiveIsSet ||
      (m_isLimitActiveIsSet &&
       (m_isLimitActive != c_classObject.m_isLimitActive))) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }

  return true;
}

bool LoadControlLimitData::
operator!=(const LoadControlLimitData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitData::isEmpty() const {
  return !m_limitIdIsSet && !m_isLimitChangeableIsSet &&
         !m_isLimitActiveIsSet && !m_timePeriodIsSet && !m_valueIsSet;
}

void LoadControlLimitData::setLimitId(const xs_unsignedInt &limitId) {
  m_limitId = limitId;
  m_limitIdIsSet = true;
}

const xs_unsignedInt &LoadControlLimitData::getLimitId() const {
  return m_limitId;
}

void LoadControlLimitData::cleanLimitId() {
  m_limitId = 0;
  m_limitIdIsSet = false;
}

bool LoadControlLimitData::getLimitIdIsSet() const { return m_limitIdIsSet; }

void LoadControlLimitData::setIsLimitChangeable(
    const xs_boolean &isLimitChangeable) {
  m_isLimitChangeable = isLimitChangeable;
  m_isLimitChangeableIsSet = true;
}

const xs_boolean &LoadControlLimitData::getIsLimitChangeable() const {
  return m_isLimitChangeable;
}

void LoadControlLimitData::cleanIsLimitChangeable() {
  m_isLimitChangeable = false;
  m_isLimitChangeableIsSet = false;
}

bool LoadControlLimitData::getIsLimitChangeableIsSet() const {
  return m_isLimitChangeableIsSet;
}

void LoadControlLimitData::setIsLimitActive(const xs_boolean &isLimitActive) {
  m_isLimitActive = isLimitActive;
  m_isLimitActiveIsSet = true;
}

const xs_boolean &LoadControlLimitData::getIsLimitActive() const {
  return m_isLimitActive;
}

void LoadControlLimitData::cleanIsLimitActive() {
  m_isLimitActive = false;
  m_isLimitActiveIsSet = false;
}

bool LoadControlLimitData::getIsLimitActiveIsSet() const {
  return m_isLimitActiveIsSet;
}

void LoadControlLimitData::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &LoadControlLimitData::getTimePeriod() const {
  return m_timePeriod;
}

void LoadControlLimitData::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool LoadControlLimitData::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void LoadControlLimitData::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &LoadControlLimitData::getValue() const { return m_value; }

void LoadControlLimitData::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool LoadControlLimitData::getValueIsSet() const { return m_valueIsSet; }

LoadControlLimitData LoadControlLimitData::reduce(
    const LoadControlLimitDataElements &elements) const {
  LoadControlLimitData dataOut;
  if (getLimitIdIsSet() && elements.getLimitIdIsSet()) {
    dataOut.setLimitId(getLimitId());
  }
  if (getIsLimitChangeableIsSet() && elements.getIsLimitChangeableIsSet()) {
    dataOut.setIsLimitChangeable(getIsLimitChangeable());
  }
  if (getIsLimitActiveIsSet() && elements.getIsLimitActiveIsSet()) {
    dataOut.setIsLimitActive(getIsLimitActive());
  }
  if (getTimePeriodIsSet() && elements.getTimePeriodIsSet()) {
    dataOut.setTimePeriod(getTimePeriod().reduce(elements.getTimePeriod()));
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    dataOut.setValue(getValue().reduce(elements.getValue()));
  }
  return dataOut;
}

bool LoadControlLimitData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"limitId", "isLimitChangeable", "isLimitActive",
                   "timePeriod", "value"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitId", &m_limitId)) {
      m_limitIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isLimitChangeable", &m_isLimitChangeable)) {
      m_isLimitChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isLimitActive", &m_isLimitActive)) {
      m_isLimitActiveIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timePeriod", &m_timePeriod)) {
      m_timePeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlLimitData::toJson() const {
  std::string result = "[";
  if (m_limitIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitId", m_limitId);
  }
  if (m_isLimitChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("isLimitChangeable", m_isLimitChangeable);
  }
  if (m_isLimitActiveIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isLimitActive", m_isLimitActive);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram