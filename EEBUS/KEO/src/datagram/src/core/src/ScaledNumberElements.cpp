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

#include <keo_datagram/core/ScaledNumberElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ScaledNumberElements::ScaledNumberElements()
    : m_numberIsSet(false), m_scaleIsSet(false)

{}

ScaledNumberElements::ScaledNumberElements(xs_boolean c_numberIsSet,
                                           xs_boolean c_scaleIsSet)
    : m_numberIsSet(c_numberIsSet), m_scaleIsSet(c_scaleIsSet)

{}

bool ScaledNumberElements::
operator==(const ScaledNumberElements &c_classObject) const {
  if (m_numberIsSet != c_classObject.m_numberIsSet) {
    return false;
  }
  if (m_scaleIsSet != c_classObject.m_scaleIsSet) {
    return false;
  }

  return true;
}

bool ScaledNumberElements::
operator!=(const ScaledNumberElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ScaledNumberElements::isEmpty() const {
  return !m_numberIsSet && !m_scaleIsSet;
}

void ScaledNumberElements::setNumber() { m_numberIsSet = true; }

void ScaledNumberElements::cleanNumber() { m_numberIsSet = false; }

bool ScaledNumberElements::getNumberIsSet() const { return m_numberIsSet; }

void ScaledNumberElements::setScale() { m_scaleIsSet = true; }

void ScaledNumberElements::cleanScale() { m_scaleIsSet = false; }

bool ScaledNumberElements::getScaleIsSet() const { return m_scaleIsSet; }

bool ScaledNumberElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"number", "scale"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "number")) {
      m_numberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scale")) {
      m_scaleIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ScaledNumberElements::toJson() const {
  std::string result = "[";
  if (m_numberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("number");
  }
  if (m_scaleIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scale");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram