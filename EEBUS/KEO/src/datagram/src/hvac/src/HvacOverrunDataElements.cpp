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

#include <keo_datagram/hvac/HvacOverrunDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOverrunDataElements::HvacOverrunDataElements()
    : DataElements(), m_overrunIdIsSet(false), m_overrunStatusIsSet(false),
      m_timeTableIdIsSet(false), m_isOverrunStatusChangeableIsSet(false)

{}

bool HvacOverrunDataElements::
operator==(const HvacOverrunDataElements &c_classObject) const {
  if (m_overrunIdIsSet != c_classObject.m_overrunIdIsSet) {
    return false;
  }
  if (m_overrunStatusIsSet != c_classObject.m_overrunStatusIsSet) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet) {
    return false;
  }
  if (m_isOverrunStatusChangeableIsSet !=
      c_classObject.m_isOverrunStatusChangeableIsSet) {
    return false;
  }

  return true;
}

bool HvacOverrunDataElements::
operator!=(const HvacOverrunDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOverrunDataElements::isEmpty() const {
  return !m_overrunIdIsSet && !m_overrunStatusIsSet && !m_timeTableIdIsSet &&
         !m_isOverrunStatusChangeableIsSet;
}

DataElements::Type HvacOverrunDataElements::getDataType() const {
  return DataElements::Type::HVAC_OVERRUN_DATA_ELEMENTS_TYPE;
}

DataElementsPtr HvacOverrunDataElements::clone() const {
  return std::make_shared<HvacOverrunDataElements>(*this);
}

void HvacOverrunDataElements::setOverrunId() { m_overrunIdIsSet = true; }

void HvacOverrunDataElements::cleanOverrunId() { m_overrunIdIsSet = false; }

bool HvacOverrunDataElements::getOverrunIdIsSet() const {
  return m_overrunIdIsSet;
}

void HvacOverrunDataElements::setOverrunStatus() {
  m_overrunStatusIsSet = true;
}

void HvacOverrunDataElements::cleanOverrunStatus() {
  m_overrunStatusIsSet = false;
}

bool HvacOverrunDataElements::getOverrunStatusIsSet() const {
  return m_overrunStatusIsSet;
}

void HvacOverrunDataElements::setTimeTableId() { m_timeTableIdIsSet = true; }

void HvacOverrunDataElements::cleanTimeTableId() { m_timeTableIdIsSet = false; }

bool HvacOverrunDataElements::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void HvacOverrunDataElements::setIsOverrunStatusChangeable() {
  m_isOverrunStatusChangeableIsSet = true;
}

void HvacOverrunDataElements::cleanIsOverrunStatusChangeable() {
  m_isOverrunStatusChangeableIsSet = false;
}

bool HvacOverrunDataElements::getIsOverrunStatusChangeableIsSet() const {
  return m_isOverrunStatusChangeableIsSet;
}

bool HvacOverrunDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"overrunId", "overrunStatus", "timeTableId",
                   "isOverrunStatusChangeable"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "overrunId")) {
      m_overrunIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "overrunStatus")) {
      m_overrunStatusIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeTableId")) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isOverrunStatusChangeable")) {
      m_isOverrunStatusChangeableIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacOverrunDataElements::toJson() const {
  std::string result = "[";
  if (m_overrunIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("overrunId");
  }
  if (m_overrunStatusIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("overrunStatus");
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeTableId");
  }
  if (m_isOverrunStatusChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isOverrunStatusChangeable");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram