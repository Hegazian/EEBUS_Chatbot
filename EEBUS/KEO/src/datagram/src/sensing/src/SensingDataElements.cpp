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

#include <keo_datagram/sensing/SensingDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SensingDataElements::SensingDataElements()
    : DataElements(), m_timestampIsSet(false), m_stateIsSet(false),
      m_valueIsSet(false), m_value(ScaledNumberElements())

{}

SensingDataElements::SensingDataElements(xs_boolean c_timestampIsSet,
                                         xs_boolean c_stateIsSet,
                                         const ScaledNumberElements &c_value)
    : DataElements(), m_timestampIsSet(c_timestampIsSet),
      m_stateIsSet(c_stateIsSet), m_valueIsSet(true), m_value(c_value)

{}

bool SensingDataElements::
operator==(const SensingDataElements &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_stateIsSet != c_classObject.m_stateIsSet) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }

  return true;
}

bool SensingDataElements::
operator!=(const SensingDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SensingDataElements::isEmpty() const {
  return !m_timestampIsSet && !m_stateIsSet && !m_valueIsSet;
}

DataElements::Type SensingDataElements::getDataType() const {
  return DataElements::Type::SENSING_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SensingDataElements::clone() const {
  return std::make_shared<SensingDataElements>(*this);
}

void SensingDataElements::setTimestamp() { m_timestampIsSet = true; }

void SensingDataElements::cleanTimestamp() { m_timestampIsSet = false; }

bool SensingDataElements::getTimestampIsSet() const { return m_timestampIsSet; }

void SensingDataElements::setState() { m_stateIsSet = true; }

void SensingDataElements::cleanState() { m_stateIsSet = false; }

bool SensingDataElements::getStateIsSet() const { return m_stateIsSet; }

void SensingDataElements::setValue(const ScaledNumberElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumberElements &SensingDataElements::getValue() const {
  return m_value;
}

void SensingDataElements::cleanValue() {
  m_value = ScaledNumberElements();
  m_valueIsSet = false;
}

bool SensingDataElements::getValueIsSet() const { return m_valueIsSet; }

bool SensingDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "state", "value"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timestamp")) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "state")) {
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

std::string SensingDataElements::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_stateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("state");
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram