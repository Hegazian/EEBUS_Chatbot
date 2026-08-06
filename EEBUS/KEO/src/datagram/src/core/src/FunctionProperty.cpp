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

#include <keo_datagram/core/FunctionProperty.h>

#include <keo_datagram/core/FunctionPropertyElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

FunctionProperty::FunctionProperty()
    : m_functionIsSet(false), m_function(Function()),
      m_possibleOperationsIsSet(false),
      m_possibleOperations(PossibleOperations())

{}

FunctionProperty::FunctionProperty(
    const Function &c_function, const PossibleOperations &c_possibleOperations)
    : m_functionIsSet(true), m_function(c_function),
      m_possibleOperationsIsSet(true),
      m_possibleOperations(c_possibleOperations)

{}

bool FunctionProperty::operator==(const FunctionProperty &c_classObject) const {
  if (m_functionIsSet != c_classObject.m_functionIsSet ||
      (m_functionIsSet && (m_function != c_classObject.m_function))) {
    return false;
  }
  if (m_possibleOperationsIsSet != c_classObject.m_possibleOperationsIsSet ||
      (m_possibleOperationsIsSet &&
       (m_possibleOperations != c_classObject.m_possibleOperations))) {
    return false;
  }

  return true;
}

bool FunctionProperty::operator!=(const FunctionProperty &c_classObject) const {
  return !(*this == c_classObject);
}

bool FunctionProperty::isEmpty() const {
  return !m_functionIsSet && !m_possibleOperationsIsSet;
}

void FunctionProperty::setFunction(const Function &function) {
  m_function = function;
  m_functionIsSet = true;
}

const Function &FunctionProperty::getFunction() const { return m_function; }

void FunctionProperty::cleanFunction() {
  m_function = Function();
  m_functionIsSet = false;
}

bool FunctionProperty::getFunctionIsSet() const { return m_functionIsSet; }

void FunctionProperty::setPossibleOperations(
    const PossibleOperations &possibleOperations) {
  m_possibleOperations = possibleOperations;
  m_possibleOperationsIsSet = true;
}

const PossibleOperations &FunctionProperty::getPossibleOperations() const {
  return m_possibleOperations;
}

void FunctionProperty::cleanPossibleOperations() {
  m_possibleOperations = PossibleOperations();
  m_possibleOperationsIsSet = false;
}

bool FunctionProperty::getPossibleOperationsIsSet() const {
  return m_possibleOperationsIsSet;
}

FunctionProperty
FunctionProperty::reduce(const FunctionPropertyElements &elements) const {
  FunctionProperty dataOut;
  if (getFunctionIsSet() && elements.getFunctionIsSet()) {
    dataOut.setFunction(getFunction());
  }
  if (getPossibleOperationsIsSet() && elements.getPossibleOperationsIsSet()) {
    dataOut.setPossibleOperations(
        getPossibleOperations().reduce(elements.getPossibleOperations()));
  }
  return dataOut;
}

bool FunctionProperty::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"function", "possibleOperations"})) {
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
                                   "possibleOperations",
                                   &m_possibleOperations)) {
      m_possibleOperationsIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string FunctionProperty::toJson() const {
  std::string result = "[";
  if (m_functionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("function", m_function);
  }
  if (m_possibleOperationsIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("possibleOperations",
                                           m_possibleOperations);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram