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

#include <keo_datagram/taskmanagement/TaskManagementLoadControlReleated.h>

#include <keo_datagram/taskmanagement/TaskManagementLoadControlReleatedElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementLoadControlReleated::TaskManagementLoadControlReleated()
    : m_eventIdIsSet(false), m_eventId(0)

{}

TaskManagementLoadControlReleated::TaskManagementLoadControlReleated(
    const xs_unsignedInt &c_eventId) {
  setEventId(c_eventId);
}

bool TaskManagementLoadControlReleated::
operator==(const TaskManagementLoadControlReleated &c_classObject) const {
  if (m_eventIdIsSet != c_classObject.m_eventIdIsSet ||
      (m_eventIdIsSet && (m_eventId != c_classObject.m_eventId))) {
    return false;
  }

  return true;
}

bool TaskManagementLoadControlReleated::
operator!=(const TaskManagementLoadControlReleated &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementLoadControlReleated::isEmpty() const {
  return !m_eventIdIsSet;
}

void TaskManagementLoadControlReleated::setEventId(
    const xs_unsignedInt &eventId) {
  m_eventId = eventId;
  m_eventIdIsSet = true;
}

const xs_unsignedInt &TaskManagementLoadControlReleated::getEventId() const {
  return m_eventId;
}

void TaskManagementLoadControlReleated::cleanEventId() {
  m_eventId = 0;
  m_eventIdIsSet = false;
}

bool TaskManagementLoadControlReleated::getEventIdIsSet() const {
  return m_eventIdIsSet;
}

TaskManagementLoadControlReleated TaskManagementLoadControlReleated::reduce(
    const TaskManagementLoadControlReleatedElements &elements) const {
  TaskManagementLoadControlReleated dataOut;
  if (getEventIdIsSet() && elements.getEventIdIsSet()) {
    dataOut.setEventId(getEventId());
  }
  return dataOut;
}

bool TaskManagementLoadControlReleated::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"eventId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "eventId", &m_eventId)) {
      m_eventIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementLoadControlReleated::toJson() const {
  std::string result = "[";
  if (m_eventIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("eventId", m_eventId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram