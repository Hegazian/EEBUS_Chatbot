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

#include <keo_datagram/setpoint/SetpointListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointListDataSelectors::SetpointListDataSelectors()
    : DataSelectors(), m_setpointIdIsSet(false), m_setpointId(0)

{}

SetpointListDataSelectors::SetpointListDataSelectors(
    const xs_unsignedInt &c_setpointId) {
  setSetpointId(c_setpointId);
}

bool SetpointListDataSelectors::
operator==(const SetpointListDataSelectors &c_classObject) const {
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet ||
      (m_setpointIdIsSet && (m_setpointId != c_classObject.m_setpointId))) {
    return false;
  }

  return true;
}

bool SetpointListDataSelectors::
operator!=(const SetpointListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointListDataSelectors::isEmpty() const { return !m_setpointIdIsSet; }

DataSelectors::Type SetpointListDataSelectors::getDataType() const {
  return DataSelectors::Type::SETPOINT_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SetpointListDataSelectors::clone() const {
  return std::make_shared<SetpointListDataSelectors>(*this);
}

void SetpointListDataSelectors::setSetpointId(
    const xs_unsignedInt &setpointId) {
  m_setpointId = setpointId;
  m_setpointIdIsSet = true;
}

const xs_unsignedInt &SetpointListDataSelectors::getSetpointId() const {
  return m_setpointId;
}

void SetpointListDataSelectors::cleanSetpointId() {
  m_setpointId = 0;
  m_setpointIdIsSet = false;
}

bool SetpointListDataSelectors::getSetpointIdIsSet() const {
  return m_setpointIdIsSet;
}

bool SetpointListDataSelectors::selects(const SetpointData &data) const {
  if (getSetpointIdIsSet() &&
      (!data.getSetpointIdIsSet() || getSetpointId() != data.getSetpointId())) {
    return false;
  }
  return true;
}

bool SetpointListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"setpointId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "setpointId", &m_setpointId)) {
      m_setpointIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SetpointListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("setpointId", m_setpointId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram