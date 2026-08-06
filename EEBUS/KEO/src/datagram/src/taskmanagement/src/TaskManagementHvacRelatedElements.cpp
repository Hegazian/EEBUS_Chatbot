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

#include <keo_datagram/taskmanagement/TaskManagementHvacRelatedElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementHvacRelatedElements::TaskManagementHvacRelatedElements()
    : m_overrunIdIsSet(false)

{}

TaskManagementHvacRelatedElements::TaskManagementHvacRelatedElements(
    const xs_boolean &c_overrunIdIsSet) {
  if (c_overrunIdIsSet) {
    setOverrunId();
  }
}

bool TaskManagementHvacRelatedElements::
operator==(const TaskManagementHvacRelatedElements &c_classObject) const {
  if (m_overrunIdIsSet != c_classObject.m_overrunIdIsSet) {
    return false;
  }

  return true;
}

bool TaskManagementHvacRelatedElements::
operator!=(const TaskManagementHvacRelatedElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementHvacRelatedElements::isEmpty() const {
  return !m_overrunIdIsSet;
}

void TaskManagementHvacRelatedElements::setOverrunId() {
  m_overrunIdIsSet = true;
}

void TaskManagementHvacRelatedElements::cleanOverrunId() {
  m_overrunIdIsSet = false;
}

bool TaskManagementHvacRelatedElements::getOverrunIdIsSet() const {
  return m_overrunIdIsSet;
}

bool TaskManagementHvacRelatedElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"overrunId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "overrunId")) {
      m_overrunIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementHvacRelatedElements::toJson() const {
  std::string result = "[";
  if (m_overrunIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("overrunId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram