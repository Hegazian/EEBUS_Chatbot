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

#include <keo_datagram/core/RecurrenceInformation.h>

#include <keo_datagram/core/RecurrenceInformationElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

RecurrenceInformation::RecurrenceInformation()
    : m_recurringIntervalIsSet(false), m_recurringInterval(RecurringInterval()),
      m_recurringIntervalStepIsSet(false), m_recurringIntervalStep(0),
      m_firstExecutionIsSet(false), m_firstExecution(xs_dateTime()),
      m_executionCountIsSet(false), m_executionCount(0),
      m_lastExecutionIsSet(false), m_lastExecution(xs_dateTime())

{}

bool RecurrenceInformation::
operator==(const RecurrenceInformation &c_classObject) const {
  if (m_recurringIntervalIsSet != c_classObject.m_recurringIntervalIsSet ||
      (m_recurringIntervalIsSet &&
       (m_recurringInterval != c_classObject.m_recurringInterval))) {
    return false;
  }
  if (m_recurringIntervalStepIsSet !=
          c_classObject.m_recurringIntervalStepIsSet ||
      (m_recurringIntervalStepIsSet &&
       (m_recurringIntervalStep != c_classObject.m_recurringIntervalStep))) {
    return false;
  }
  if (m_firstExecutionIsSet != c_classObject.m_firstExecutionIsSet ||
      (m_firstExecutionIsSet &&
       (m_firstExecution != c_classObject.m_firstExecution))) {
    return false;
  }
  if (m_executionCountIsSet != c_classObject.m_executionCountIsSet ||
      (m_executionCountIsSet &&
       (m_executionCount != c_classObject.m_executionCount))) {
    return false;
  }
  if (m_lastExecutionIsSet != c_classObject.m_lastExecutionIsSet ||
      (m_lastExecutionIsSet &&
       (m_lastExecution != c_classObject.m_lastExecution))) {
    return false;
  }

  return true;
}

bool RecurrenceInformation::
operator!=(const RecurrenceInformation &c_classObject) const {
  return !(*this == c_classObject);
}

bool RecurrenceInformation::isEmpty() const {
  return !m_recurringIntervalIsSet && !m_recurringIntervalStepIsSet &&
         !m_firstExecutionIsSet && !m_executionCountIsSet &&
         !m_lastExecutionIsSet;
}

void RecurrenceInformation::setRecurringInterval(
    const RecurringInterval &recurringInterval) {
  m_recurringInterval = recurringInterval;
  m_recurringIntervalIsSet = true;
}

const RecurringInterval &RecurrenceInformation::getRecurringInterval() const {
  return m_recurringInterval;
}

void RecurrenceInformation::cleanRecurringInterval() {
  m_recurringInterval = RecurringInterval();
  m_recurringIntervalIsSet = false;
}

bool RecurrenceInformation::getRecurringIntervalIsSet() const {
  return m_recurringIntervalIsSet;
}

void RecurrenceInformation::setRecurringIntervalStep(
    const xs_unsignedInt &recurringIntervalStep) {
  m_recurringIntervalStep = recurringIntervalStep;
  m_recurringIntervalStepIsSet = true;
}

const xs_unsignedInt &RecurrenceInformation::getRecurringIntervalStep() const {
  return m_recurringIntervalStep;
}

void RecurrenceInformation::cleanRecurringIntervalStep() {
  m_recurringIntervalStep = 0;
  m_recurringIntervalStepIsSet = false;
}

bool RecurrenceInformation::getRecurringIntervalStepIsSet() const {
  return m_recurringIntervalStepIsSet;
}

void RecurrenceInformation::setFirstExecution(
    const xs_dateTime &firstExecution) {
  m_firstExecution = firstExecution;
  m_firstExecutionIsSet = true;
}

const xs_dateTime &RecurrenceInformation::getFirstExecution() const {
  return m_firstExecution;
}

void RecurrenceInformation::cleanFirstExecution() {
  m_firstExecution = xs_dateTime();
  m_firstExecutionIsSet = false;
}

bool RecurrenceInformation::getFirstExecutionIsSet() const {
  return m_firstExecutionIsSet;
}

void RecurrenceInformation::setExecutionCount(
    const xs_unsignedInt &executionCount) {
  m_executionCount = executionCount;
  m_executionCountIsSet = true;
}

const xs_unsignedInt &RecurrenceInformation::getExecutionCount() const {
  return m_executionCount;
}

void RecurrenceInformation::cleanExecutionCount() {
  m_executionCount = 0;
  m_executionCountIsSet = false;
}

bool RecurrenceInformation::getExecutionCountIsSet() const {
  return m_executionCountIsSet;
}

void RecurrenceInformation::setLastExecution(const xs_dateTime &lastExecution) {
  m_lastExecution = lastExecution;
  m_lastExecutionIsSet = true;
}

const xs_dateTime &RecurrenceInformation::getLastExecution() const {
  return m_lastExecution;
}

void RecurrenceInformation::cleanLastExecution() {
  m_lastExecution = xs_dateTime();
  m_lastExecutionIsSet = false;
}

bool RecurrenceInformation::getLastExecutionIsSet() const {
  return m_lastExecutionIsSet;
}

RecurrenceInformation RecurrenceInformation::reduce(
    const RecurrenceInformationElements &elements) const {
  RecurrenceInformation dataOut;
  if (getRecurringIntervalIsSet() && elements.getRecurringIntervalIsSet()) {
    dataOut.setRecurringInterval(getRecurringInterval());
  }
  if (getRecurringIntervalStepIsSet() &&
      elements.getRecurringIntervalStepIsSet()) {
    dataOut.setRecurringIntervalStep(getRecurringIntervalStep());
  }
  if (getFirstExecutionIsSet() && elements.getFirstExecutionIsSet()) {
    dataOut.setFirstExecution(getFirstExecution());
  }
  if (getExecutionCountIsSet() && elements.getExecutionCountIsSet()) {
    dataOut.setExecutionCount(getExecutionCount());
  }
  if (getLastExecutionIsSet() && elements.getLastExecutionIsSet()) {
    dataOut.setLastExecution(getLastExecution());
  }
  return dataOut;
}

bool RecurrenceInformation::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"recurringInterval", "recurringIntervalStep",
                   "firstExecution", "executionCount", "lastExecution"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "recurringInterval", &m_recurringInterval)) {
      m_recurringIntervalIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "recurringIntervalStep",
                                   &m_recurringIntervalStep)) {
      m_recurringIntervalStepIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "firstExecution", &m_firstExecution)) {
      m_firstExecutionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "executionCount", &m_executionCount)) {
      m_executionCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "lastExecution", &m_lastExecution)) {
      m_lastExecutionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string RecurrenceInformation::toJson() const {
  std::string result = "[";
  if (m_recurringIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("recurringInterval", m_recurringInterval);
  }
  if (m_recurringIntervalStepIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("recurringIntervalStep",
                                           m_recurringIntervalStep);
  }
  if (m_firstExecutionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("firstExecution", m_firstExecution);
  }
  if (m_executionCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("executionCount", m_executionCount);
  }
  if (m_lastExecutionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("lastExecution", m_lastExecution);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram