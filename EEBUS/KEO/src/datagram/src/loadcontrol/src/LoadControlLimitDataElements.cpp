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

#include <keo_datagram/loadcontrol/LoadControlLimitDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitDataElements::LoadControlLimitDataElements()
    : DataElements(), m_limitIdIsSet(false), m_isLimitChangeableIsSet(false),
      m_isLimitActiveIsSet(false), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriodElements()), m_valueIsSet(false),
      m_value(ScaledNumberElements())

{}

bool LoadControlLimitDataElements::
operator==(const LoadControlLimitDataElements &c_classObject) const {
  if (m_limitIdIsSet != c_classObject.m_limitIdIsSet) {
    return false;
  }
  if (m_isLimitChangeableIsSet != c_classObject.m_isLimitChangeableIsSet) {
    return false;
  }
  if (m_isLimitActiveIsSet != c_classObject.m_isLimitActiveIsSet) {
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

bool LoadControlLimitDataElements::
operator!=(const LoadControlLimitDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitDataElements::isEmpty() const {
  return !m_limitIdIsSet && !m_isLimitChangeableIsSet &&
         !m_isLimitActiveIsSet && !m_timePeriodIsSet && !m_valueIsSet;
}

DataElements::Type LoadControlLimitDataElements::getDataType() const {
  return DataElements::Type::LOAD_CONTROL_LIMIT_DATA_ELEMENTS_TYPE;
}

DataElementsPtr LoadControlLimitDataElements::clone() const {
  return std::make_shared<LoadControlLimitDataElements>(*this);
}

void LoadControlLimitDataElements::setLimitId() { m_limitIdIsSet = true; }

void LoadControlLimitDataElements::cleanLimitId() { m_limitIdIsSet = false; }

bool LoadControlLimitDataElements::getLimitIdIsSet() const {
  return m_limitIdIsSet;
}

void LoadControlLimitDataElements::setIsLimitChangeable() {
  m_isLimitChangeableIsSet = true;
}

void LoadControlLimitDataElements::cleanIsLimitChangeable() {
  m_isLimitChangeableIsSet = false;
}

bool LoadControlLimitDataElements::getIsLimitChangeableIsSet() const {
  return m_isLimitChangeableIsSet;
}

void LoadControlLimitDataElements::setIsLimitActive() {
  m_isLimitActiveIsSet = true;
}

void LoadControlLimitDataElements::cleanIsLimitActive() {
  m_isLimitActiveIsSet = false;
}

bool LoadControlLimitDataElements::getIsLimitActiveIsSet() const {
  return m_isLimitActiveIsSet;
}

void LoadControlLimitDataElements::setTimePeriod(
    const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &LoadControlLimitDataElements::getTimePeriod() const {
  return m_timePeriod;
}

void LoadControlLimitDataElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool LoadControlLimitDataElements::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void LoadControlLimitDataElements::setValue(const ScaledNumberElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumberElements &LoadControlLimitDataElements::getValue() const {
  return m_value;
}

void LoadControlLimitDataElements::cleanValue() {
  m_value = ScaledNumberElements();
  m_valueIsSet = false;
}

bool LoadControlLimitDataElements::getValueIsSet() const {
  return m_valueIsSet;
}

bool LoadControlLimitDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"limitId", "isLimitChangeable", "isLimitActive",
                   "timePeriod", "value"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "limitId")) {
      m_limitIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isLimitChangeable")) {
      m_isLimitChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isLimitActive")) {
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

std::string LoadControlLimitDataElements::toJson() const {
  std::string result = "[";
  if (m_limitIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("limitId");
  }
  if (m_isLimitChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isLimitChangeable");
  }
  if (m_isLimitActiveIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isLimitActive");
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