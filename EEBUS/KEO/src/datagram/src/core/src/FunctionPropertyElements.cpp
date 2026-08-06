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

#include <keo_datagram/core/FunctionPropertyElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

FunctionPropertyElements::FunctionPropertyElements()
    : m_functionIsSet(false), m_possibleOperationsIsSet(false),
      m_possibleOperations(PossibleOperationsElements())

{}

FunctionPropertyElements::FunctionPropertyElements(
    xs_boolean c_functionIsSet,
    const PossibleOperationsElements &c_possibleOperations)
    : m_functionIsSet(c_functionIsSet), m_possibleOperationsIsSet(true),
      m_possibleOperations(c_possibleOperations)

{}

bool FunctionPropertyElements::
operator==(const FunctionPropertyElements &c_classObject) const {
  if (m_functionIsSet != c_classObject.m_functionIsSet) {
    return false;
  }
  if (m_possibleOperationsIsSet != c_classObject.m_possibleOperationsIsSet ||
      (m_possibleOperationsIsSet &&
       (m_possibleOperations != c_classObject.m_possibleOperations))) {
    return false;
  }

  return true;
}

bool FunctionPropertyElements::
operator!=(const FunctionPropertyElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool FunctionPropertyElements::isEmpty() const {
  return !m_functionIsSet && !m_possibleOperationsIsSet;
}

void FunctionPropertyElements::setFunction() { m_functionIsSet = true; }

void FunctionPropertyElements::cleanFunction() { m_functionIsSet = false; }

bool FunctionPropertyElements::getFunctionIsSet() const {
  return m_functionIsSet;
}

void FunctionPropertyElements::setPossibleOperations(
    const PossibleOperationsElements &possibleOperations) {
  m_possibleOperations = possibleOperations;
  m_possibleOperationsIsSet = true;
}

const PossibleOperationsElements &
FunctionPropertyElements::getPossibleOperations() const {
  return m_possibleOperations;
}

void FunctionPropertyElements::cleanPossibleOperations() {
  m_possibleOperations = PossibleOperationsElements();
  m_possibleOperationsIsSet = false;
}

bool FunctionPropertyElements::getPossibleOperationsIsSet() const {
  return m_possibleOperationsIsSet;
}

bool FunctionPropertyElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"function", "possibleOperations"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "function")) {
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

std::string FunctionPropertyElements::toJson() const {
  std::string result = "[";
  if (m_functionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("function");
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