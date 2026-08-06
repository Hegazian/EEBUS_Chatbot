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

#include <keo_datagram/hvac/HvacOverrunData.h>

#include <keo_datagram/hvac/HvacOverrunDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOverrunData::HvacOverrunData()
    : m_overrunIdIsSet(false), m_overrunId(0), m_overrunStatusIsSet(false),
      m_overrunStatus(HvacOverrunStatus()), m_timeTableIdIsSet(false),
      m_timeTableId(0), m_isOverrunStatusChangeableIsSet(false),
      m_isOverrunStatusChangeable(false)

{}

bool HvacOverrunData::operator==(const HvacOverrunData &c_classObject) const {
  if (m_overrunIdIsSet != c_classObject.m_overrunIdIsSet ||
      (m_overrunIdIsSet && (m_overrunId != c_classObject.m_overrunId))) {
    return false;
  }
  if (m_overrunStatusIsSet != c_classObject.m_overrunStatusIsSet ||
      (m_overrunStatusIsSet &&
       (m_overrunStatus != c_classObject.m_overrunStatus))) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
    return false;
  }
  if (m_isOverrunStatusChangeableIsSet !=
          c_classObject.m_isOverrunStatusChangeableIsSet ||
      (m_isOverrunStatusChangeableIsSet &&
       (m_isOverrunStatusChangeable !=
        c_classObject.m_isOverrunStatusChangeable))) {
    return false;
  }

  return true;
}

bool HvacOverrunData::operator!=(const HvacOverrunData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOverrunData::isEmpty() const {
  return !m_overrunIdIsSet && !m_overrunStatusIsSet && !m_timeTableIdIsSet &&
         !m_isOverrunStatusChangeableIsSet;
}

void HvacOverrunData::setOverrunId(const xs_unsignedInt &overrunId) {
  m_overrunId = overrunId;
  m_overrunIdIsSet = true;
}

const xs_unsignedInt &HvacOverrunData::getOverrunId() const {
  return m_overrunId;
}

void HvacOverrunData::cleanOverrunId() {
  m_overrunId = 0;
  m_overrunIdIsSet = false;
}

bool HvacOverrunData::getOverrunIdIsSet() const { return m_overrunIdIsSet; }

void HvacOverrunData::setOverrunStatus(const HvacOverrunStatus &overrunStatus) {
  m_overrunStatus = overrunStatus;
  m_overrunStatusIsSet = true;
}

const HvacOverrunStatus &HvacOverrunData::getOverrunStatus() const {
  return m_overrunStatus;
}

void HvacOverrunData::cleanOverrunStatus() {
  m_overrunStatus = HvacOverrunStatus();
  m_overrunStatusIsSet = false;
}

bool HvacOverrunData::getOverrunStatusIsSet() const {
  return m_overrunStatusIsSet;
}

void HvacOverrunData::setTimeTableId(const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &HvacOverrunData::getTimeTableId() const {
  return m_timeTableId;
}

void HvacOverrunData::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool HvacOverrunData::getTimeTableIdIsSet() const { return m_timeTableIdIsSet; }

void HvacOverrunData::setIsOverrunStatusChangeable(
    const xs_boolean &isOverrunStatusChangeable) {
  m_isOverrunStatusChangeable = isOverrunStatusChangeable;
  m_isOverrunStatusChangeableIsSet = true;
}

const xs_boolean &HvacOverrunData::getIsOverrunStatusChangeable() const {
  return m_isOverrunStatusChangeable;
}

void HvacOverrunData::cleanIsOverrunStatusChangeable() {
  m_isOverrunStatusChangeable = false;
  m_isOverrunStatusChangeableIsSet = false;
}

bool HvacOverrunData::getIsOverrunStatusChangeableIsSet() const {
  return m_isOverrunStatusChangeableIsSet;
}

HvacOverrunData
HvacOverrunData::reduce(const HvacOverrunDataElements &elements) const {
  HvacOverrunData dataOut;
  if (getOverrunIdIsSet() && elements.getOverrunIdIsSet()) {
    dataOut.setOverrunId(getOverrunId());
  }
  if (getOverrunStatusIsSet() && elements.getOverrunStatusIsSet()) {
    dataOut.setOverrunStatus(getOverrunStatus());
  }
  if (getTimeTableIdIsSet() && elements.getTimeTableIdIsSet()) {
    dataOut.setTimeTableId(getTimeTableId());
  }
  if (getIsOverrunStatusChangeableIsSet() &&
      elements.getIsOverrunStatusChangeableIsSet()) {
    dataOut.setIsOverrunStatusChangeable(getIsOverrunStatusChangeable());
  }
  return dataOut;
}

bool HvacOverrunData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"overrunId", "overrunStatus", "timeTableId",
                   "isOverrunStatusChangeable"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "overrunId", &m_overrunId)) {
      m_overrunIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "overrunStatus", &m_overrunStatus)) {
      m_overrunStatusIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeTableId", &m_timeTableId)) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isOverrunStatusChangeable",
                                   &m_isOverrunStatusChangeable)) {
      m_isOverrunStatusChangeableIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacOverrunData::toJson() const {
  std::string result = "[";
  if (m_overrunIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("overrunId", m_overrunId);
  }
  if (m_overrunStatusIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("overrunStatus", m_overrunStatus);
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  if (m_isOverrunStatusChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isOverrunStatusChangeable",
                                           m_isOverrunStatusChangeable);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram