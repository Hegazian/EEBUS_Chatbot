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

#include <keo_datagram/actuator/ActuatorSwitchData.h>

#include <keo_datagram/actuator/ActuatorSwitchDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ActuatorSwitchData::ActuatorSwitchData()
    : CmdData(), m_functionIsSet(false), m_function(ActuatorSwitchFct())

{}

ActuatorSwitchData::ActuatorSwitchData(const ActuatorSwitchFct &c_function) {
  setFunction(c_function);
}

bool ActuatorSwitchData::
operator==(const ActuatorSwitchData &c_classObject) const {
  if (m_functionIsSet != c_classObject.m_functionIsSet ||
      (m_functionIsSet && (m_function != c_classObject.m_function))) {
    return false;
  }

  return true;
}

bool ActuatorSwitchData::
operator!=(const ActuatorSwitchData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ActuatorSwitchData::isEmpty() const { return !m_functionIsSet; }

CmdData::Type ActuatorSwitchData::getDataType() const {
  return CmdData::Type::ACTUATOR_SWITCH_DATA_TYPE;
}

CmdDataPtr ActuatorSwitchData::clone() const {
  return std::make_shared<ActuatorSwitchData>(*this);
}

void ActuatorSwitchData::setFunction(const ActuatorSwitchFct &function) {
  m_function = function;
  m_functionIsSet = true;
}

const ActuatorSwitchFct &ActuatorSwitchData::getFunction() const {
  return m_function;
}

void ActuatorSwitchData::cleanFunction() {
  m_function = ActuatorSwitchFct();
  m_functionIsSet = false;
}

bool ActuatorSwitchData::getFunctionIsSet() const { return m_functionIsSet; }

CmdDataPtr
ActuatorSwitchData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      ActuatorSwitchDataElementsPtr elements =
          std::dynamic_pointer_cast<ActuatorSwitchDataElements>(
              filter.getDataElements());
      if (elements) {
        ActuatorSwitchDataPtr dataOut = std::make_shared<ActuatorSwitchData>();
        // TODO make sure to always set identifier

        if (getFunctionIsSet() && elements->getFunctionIsSet()) {
          dataOut->setFunction(getFunction());
        }

        return dataOut;
      } else {
        return std::make_shared<ActuatorSwitchData>(*this);
      }
    } else {
      return std::make_shared<ActuatorSwitchData>(*this);
    }
  } else {
    return std::make_shared<ActuatorSwitchData>(*this);
  }
}

bool ActuatorSwitchData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"function"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "function", &m_function)) {
      m_functionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ActuatorSwitchData::toJson() const {
  std::string result = "[";
  if (m_functionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("function", m_function);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram