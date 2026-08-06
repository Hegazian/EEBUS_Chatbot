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

#include <keo_datagram/timeinformation/TimePrecisionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimePrecisionDataElements::TimePrecisionDataElements()
    : DataElements(), m_isSynchronisedIsSet(false), m_lastSyncAtIsSet(false),
      m_clockDriftIsSet(false)

{}

TimePrecisionDataElements::TimePrecisionDataElements(
    xs_boolean c_isSynchronisedIsSet, xs_boolean c_lastSyncAtIsSet,
    xs_boolean c_clockDriftIsSet)
    : DataElements(), m_isSynchronisedIsSet(c_isSynchronisedIsSet),
      m_lastSyncAtIsSet(c_lastSyncAtIsSet), m_clockDriftIsSet(c_clockDriftIsSet)

{}

bool TimePrecisionDataElements::
operator==(const TimePrecisionDataElements &c_classObject) const {
  if (m_isSynchronisedIsSet != c_classObject.m_isSynchronisedIsSet) {
    return false;
  }
  if (m_lastSyncAtIsSet != c_classObject.m_lastSyncAtIsSet) {
    return false;
  }
  if (m_clockDriftIsSet != c_classObject.m_clockDriftIsSet) {
    return false;
  }

  return true;
}

bool TimePrecisionDataElements::
operator!=(const TimePrecisionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimePrecisionDataElements::isEmpty() const {
  return !m_isSynchronisedIsSet && !m_lastSyncAtIsSet && !m_clockDriftIsSet;
}

DataElements::Type TimePrecisionDataElements::getDataType() const {
  return DataElements::Type::TIME_PRECISION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimePrecisionDataElements::clone() const {
  return std::make_shared<TimePrecisionDataElements>(*this);
}

void TimePrecisionDataElements::setIsSynchronised() {
  m_isSynchronisedIsSet = true;
}

void TimePrecisionDataElements::cleanIsSynchronised() {
  m_isSynchronisedIsSet = false;
}

bool TimePrecisionDataElements::getIsSynchronisedIsSet() const {
  return m_isSynchronisedIsSet;
}

void TimePrecisionDataElements::setLastSyncAt() { m_lastSyncAtIsSet = true; }

void TimePrecisionDataElements::cleanLastSyncAt() { m_lastSyncAtIsSet = false; }

bool TimePrecisionDataElements::getLastSyncAtIsSet() const {
  return m_lastSyncAtIsSet;
}

void TimePrecisionDataElements::setClockDrift() { m_clockDriftIsSet = true; }

void TimePrecisionDataElements::cleanClockDrift() { m_clockDriftIsSet = false; }

bool TimePrecisionDataElements::getClockDriftIsSet() const {
  return m_clockDriftIsSet;
}

bool TimePrecisionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"isSynchronised", "lastSyncAt", "clockDrift"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isSynchronised")) {
      m_isSynchronisedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "lastSyncAt")) {
      m_lastSyncAtIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "clockDrift")) {
      m_clockDriftIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimePrecisionDataElements::toJson() const {
  std::string result = "[";
  if (m_isSynchronisedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isSynchronised");
  }
  if (m_lastSyncAtIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("lastSyncAt");
  }
  if (m_clockDriftIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("clockDrift");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram