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

#include <keo_datagram/core/RecurrenceInformationElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

RecurrenceInformationElements::RecurrenceInformationElements()
    : m_recurringIntervalIsSet(false), m_recurringIntervalStepIsSet(false),
      m_firstExecutionIsSet(false), m_executionCountIsSet(false),
      m_lastExecutionIsSet(false)

{}

bool RecurrenceInformationElements::
operator==(const RecurrenceInformationElements &c_classObject) const {
  if (m_recurringIntervalIsSet != c_classObject.m_recurringIntervalIsSet) {
    return false;
  }
  if (m_recurringIntervalStepIsSet !=
      c_classObject.m_recurringIntervalStepIsSet) {
    return false;
  }
  if (m_firstExecutionIsSet != c_classObject.m_firstExecutionIsSet) {
    return false;
  }
  if (m_executionCountIsSet != c_classObject.m_executionCountIsSet) {
    return false;
  }
  if (m_lastExecutionIsSet != c_classObject.m_lastExecutionIsSet) {
    return false;
  }

  return true;
}

bool RecurrenceInformationElements::
operator!=(const RecurrenceInformationElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool RecurrenceInformationElements::isEmpty() const {
  return !m_recurringIntervalIsSet && !m_recurringIntervalStepIsSet &&
         !m_firstExecutionIsSet && !m_executionCountIsSet &&
         !m_lastExecutionIsSet;
}

void RecurrenceInformationElements::setRecurringInterval() {
  m_recurringIntervalIsSet = true;
}

void RecurrenceInformationElements::cleanRecurringInterval() {
  m_recurringIntervalIsSet = false;
}

bool RecurrenceInformationElements::getRecurringIntervalIsSet() const {
  return m_recurringIntervalIsSet;
}

void RecurrenceInformationElements::setRecurringIntervalStep() {
  m_recurringIntervalStepIsSet = true;
}

void RecurrenceInformationElements::cleanRecurringIntervalStep() {
  m_recurringIntervalStepIsSet = false;
}

bool RecurrenceInformationElements::getRecurringIntervalStepIsSet() const {
  return m_recurringIntervalStepIsSet;
}

void RecurrenceInformationElements::setFirstExecution() {
  m_firstExecutionIsSet = true;
}

void RecurrenceInformationElements::cleanFirstExecution() {
  m_firstExecutionIsSet = false;
}

bool RecurrenceInformationElements::getFirstExecutionIsSet() const {
  return m_firstExecutionIsSet;
}

void RecurrenceInformationElements::setExecutionCount() {
  m_executionCountIsSet = true;
}

void RecurrenceInformationElements::cleanExecutionCount() {
  m_executionCountIsSet = false;
}

bool RecurrenceInformationElements::getExecutionCountIsSet() const {
  return m_executionCountIsSet;
}

void RecurrenceInformationElements::setLastExecution() {
  m_lastExecutionIsSet = true;
}

void RecurrenceInformationElements::cleanLastExecution() {
  m_lastExecutionIsSet = false;
}

bool RecurrenceInformationElements::getLastExecutionIsSet() const {
  return m_lastExecutionIsSet;
}

bool RecurrenceInformationElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"recurringInterval", "recurringIntervalStep",
                   "firstExecution", "executionCount", "lastExecution"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "recurringInterval")) {
      m_recurringIntervalIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "recurringIntervalStep")) {
      m_recurringIntervalStepIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "firstExecution")) {
      m_firstExecutionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "executionCount")) {
      m_executionCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "lastExecution")) {
      m_lastExecutionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string RecurrenceInformationElements::toJson() const {
  std::string result = "[";
  if (m_recurringIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("recurringInterval");
  }
  if (m_recurringIntervalStepIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("recurringIntervalStep");
  }
  if (m_firstExecutionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("firstExecution");
  }
  if (m_executionCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("executionCount");
  }
  if (m_lastExecutionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("lastExecution");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram