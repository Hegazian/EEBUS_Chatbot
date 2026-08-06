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

#include <keo_datagram/actuator/ActuatorLevelData.h>

#include <keo_datagram/actuator/ActuatorLevelDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ActuatorLevelData::ActuatorLevelData()
    : CmdData(), m_functionIsSet(false), m_function(ActuatorLevelFct()),
      m_valueIsSet(false), m_value(ScaledNumber())

{}

ActuatorLevelData::ActuatorLevelData(const ActuatorLevelFct &c_function,
                                     const ScaledNumber &c_value)
    : CmdData(), m_functionIsSet(true), m_function(c_function),
      m_valueIsSet(true), m_value(c_value)

{}

bool ActuatorLevelData::
operator==(const ActuatorLevelData &c_classObject) const {
  if (m_functionIsSet != c_classObject.m_functionIsSet ||
      (m_functionIsSet && (m_function != c_classObject.m_function))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }

  return true;
}

bool ActuatorLevelData::
operator!=(const ActuatorLevelData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ActuatorLevelData::isEmpty() const {
  return !m_functionIsSet && !m_valueIsSet;
}

CmdData::Type ActuatorLevelData::getDataType() const {
  return CmdData::Type::ACTUATOR_LEVEL_DATA_TYPE;
}

CmdDataPtr ActuatorLevelData::clone() const {
  return std::make_shared<ActuatorLevelData>(*this);
}

void ActuatorLevelData::setFunction(const ActuatorLevelFct &function) {
  m_function = function;
  m_functionIsSet = true;
}

const ActuatorLevelFct &ActuatorLevelData::getFunction() const {
  return m_function;
}

void ActuatorLevelData::cleanFunction() {
  m_function = ActuatorLevelFct();
  m_functionIsSet = false;
}

bool ActuatorLevelData::getFunctionIsSet() const { return m_functionIsSet; }

void ActuatorLevelData::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &ActuatorLevelData::getValue() const { return m_value; }

void ActuatorLevelData::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool ActuatorLevelData::getValueIsSet() const { return m_valueIsSet; }

CmdDataPtr ActuatorLevelData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      ActuatorLevelDataElementsPtr elements =
          std::dynamic_pointer_cast<ActuatorLevelDataElements>(
              filter.getDataElements());
      if (elements) {
        ActuatorLevelDataPtr dataOut = std::make_shared<ActuatorLevelData>();
        // TODO make sure to always set identifier

        if (getFunctionIsSet() && elements->getFunctionIsSet()) {
          dataOut->setFunction(getFunction());
        }

        if (getValueIsSet() && elements->getValueIsSet()) {
          dataOut->setValue(getValue().reduce(elements->getValue()));
        }

        return dataOut;
      } else {
        return std::make_shared<ActuatorLevelData>(*this);
      }
    } else {
      return std::make_shared<ActuatorLevelData>(*this);
    }
  } else {
    return std::make_shared<ActuatorLevelData>(*this);
  }
}

bool ActuatorLevelData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"function", "value"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "function", &m_function)) {
      m_functionIsSet = true;
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

std::string ActuatorLevelData::toJson() const {
  std::string result = "[";
  if (m_functionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("function", m_function);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram