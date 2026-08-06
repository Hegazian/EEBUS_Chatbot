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

#include <keo_datagram/core/TimePeriodElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimePeriodElements::TimePeriodElements()
    : m_startTimeIsSet(false), m_endTimeIsSet(false)

{}

TimePeriodElements::TimePeriodElements(xs_boolean c_startTimeIsSet,
                                       xs_boolean c_endTimeIsSet)
    : m_startTimeIsSet(c_startTimeIsSet), m_endTimeIsSet(c_endTimeIsSet)

{}

bool TimePeriodElements::
operator==(const TimePeriodElements &c_classObject) const {
  if (m_startTimeIsSet != c_classObject.m_startTimeIsSet) {
    return false;
  }
  if (m_endTimeIsSet != c_classObject.m_endTimeIsSet) {
    return false;
  }

  return true;
}

bool TimePeriodElements::
operator!=(const TimePeriodElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimePeriodElements::isEmpty() const {
  return !m_startTimeIsSet && !m_endTimeIsSet;
}

void TimePeriodElements::setStartTime() { m_startTimeIsSet = true; }

void TimePeriodElements::cleanStartTime() { m_startTimeIsSet = false; }

bool TimePeriodElements::getStartTimeIsSet() const { return m_startTimeIsSet; }

void TimePeriodElements::setEndTime() { m_endTimeIsSet = true; }

void TimePeriodElements::cleanEndTime() { m_endTimeIsSet = false; }

bool TimePeriodElements::getEndTimeIsSet() const { return m_endTimeIsSet; }

bool TimePeriodElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"startTime", "endTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "startTime")) {
      m_startTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "endTime")) {
      m_endTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimePeriodElements::toJson() const {
  std::string result = "[";
  if (m_startTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("startTime");
  }
  if (m_endTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("endTime");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram