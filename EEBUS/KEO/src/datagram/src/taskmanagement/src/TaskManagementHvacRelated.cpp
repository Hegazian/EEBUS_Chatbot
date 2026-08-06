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

#include <keo_datagram/taskmanagement/TaskManagementHvacRelated.h>

#include <keo_datagram/taskmanagement/TaskManagementHvacRelatedElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementHvacRelated::TaskManagementHvacRelated()
    : m_overrunIdIsSet(false), m_overrunId(0)

{}

TaskManagementHvacRelated::TaskManagementHvacRelated(
    const xs_unsignedInt &c_overrunId) {
  setOverrunId(c_overrunId);
}

bool TaskManagementHvacRelated::
operator==(const TaskManagementHvacRelated &c_classObject) const {
  if (m_overrunIdIsSet != c_classObject.m_overrunIdIsSet ||
      (m_overrunIdIsSet && (m_overrunId != c_classObject.m_overrunId))) {
    return false;
  }

  return true;
}

bool TaskManagementHvacRelated::
operator!=(const TaskManagementHvacRelated &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementHvacRelated::isEmpty() const { return !m_overrunIdIsSet; }

void TaskManagementHvacRelated::setOverrunId(const xs_unsignedInt &overrunId) {
  m_overrunId = overrunId;
  m_overrunIdIsSet = true;
}

const xs_unsignedInt &TaskManagementHvacRelated::getOverrunId() const {
  return m_overrunId;
}

void TaskManagementHvacRelated::cleanOverrunId() {
  m_overrunId = 0;
  m_overrunIdIsSet = false;
}

bool TaskManagementHvacRelated::getOverrunIdIsSet() const {
  return m_overrunIdIsSet;
}

TaskManagementHvacRelated TaskManagementHvacRelated::reduce(
    const TaskManagementHvacRelatedElements &elements) const {
  TaskManagementHvacRelated dataOut;
  if (getOverrunIdIsSet() && elements.getOverrunIdIsSet()) {
    dataOut.setOverrunId(getOverrunId());
  }
  return dataOut;
}

bool TaskManagementHvacRelated::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"overrunId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "overrunId", &m_overrunId)) {
      m_overrunIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementHvacRelated::toJson() const {
  std::string result = "[";
  if (m_overrunIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("overrunId", m_overrunId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram