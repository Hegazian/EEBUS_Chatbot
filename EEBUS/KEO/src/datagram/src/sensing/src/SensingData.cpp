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

#include <keo_datagram/sensing/SensingData.h>

#include <keo_datagram/sensing/SensingDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SensingData::SensingData()
    : m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_stateIsSet(false), m_state(SensingState()), m_valueIsSet(false),
      m_value(ScaledNumber())

{}

SensingData::SensingData(const AbsoluteOrRelativeTime &c_timestamp,
                         const SensingState &c_state,
                         const ScaledNumber &c_value)
    : m_timestampIsSet(true), m_timestamp(c_timestamp), m_stateIsSet(true),
      m_state(c_state), m_valueIsSet(true), m_value(c_value)

{}

bool SensingData::operator==(const SensingData &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_stateIsSet != c_classObject.m_stateIsSet ||
      (m_stateIsSet && (m_state != c_classObject.m_state))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }

  return true;
}

bool SensingData::operator!=(const SensingData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SensingData::isEmpty() const {
  return !m_timestampIsSet && !m_stateIsSet && !m_valueIsSet;
}

void SensingData::setTimestamp(const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &SensingData::getTimestamp() const {
  return m_timestamp;
}

void SensingData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool SensingData::getTimestampIsSet() const { return m_timestampIsSet; }

void SensingData::setState(const SensingState &state) {
  m_state = state;
  m_stateIsSet = true;
}

const SensingState &SensingData::getState() const { return m_state; }

void SensingData::cleanState() {
  m_state = SensingState();
  m_stateIsSet = false;
}

bool SensingData::getStateIsSet() const { return m_stateIsSet; }

void SensingData::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &SensingData::getValue() const { return m_value; }

void SensingData::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool SensingData::getValueIsSet() const { return m_valueIsSet; }

SensingData SensingData::reduce(const SensingDataElements &elements) const {
  SensingData dataOut;
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getStateIsSet() && elements.getStateIsSet()) {
    dataOut.setState(getState());
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    dataOut.setValue(getValue().reduce(elements.getValue()));
  }
  return dataOut;
}

bool SensingData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "state", "value"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestamp", &m_timestamp)) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "state", &m_state)) {
      m_stateIsSet = true;
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

std::string SensingData::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_stateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("state", m_state);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram