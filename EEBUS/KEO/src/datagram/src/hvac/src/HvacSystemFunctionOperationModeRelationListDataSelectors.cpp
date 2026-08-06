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

#include <keo_datagram/hvac/HvacSystemFunctionOperationModeRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionOperationModeRelationListDataSelectors::
    HvacSystemFunctionOperationModeRelationListDataSelectors()
    : DataSelectors(), m_systemFunctionIdIsSet(false), m_systemFunctionId(0)

{}

HvacSystemFunctionOperationModeRelationListDataSelectors::
    HvacSystemFunctionOperationModeRelationListDataSelectors(
        const xs_unsignedInt &c_systemFunctionId) {
  setSystemFunctionId(c_systemFunctionId);
}

bool HvacSystemFunctionOperationModeRelationListDataSelectors::
operator==(const HvacSystemFunctionOperationModeRelationListDataSelectors
               &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet ||
      (m_systemFunctionIdIsSet &&
       (m_systemFunctionId != c_classObject.m_systemFunctionId))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionOperationModeRelationListDataSelectors::
operator!=(const HvacSystemFunctionOperationModeRelationListDataSelectors
               &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionOperationModeRelationListDataSelectors::isEmpty() const {
  return !m_systemFunctionIdIsSet;
}

DataSelectors::Type
HvacSystemFunctionOperationModeRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
HvacSystemFunctionOperationModeRelationListDataSelectors::clone() const {
  return std::make_shared<
      HvacSystemFunctionOperationModeRelationListDataSelectors>(*this);
}

void HvacSystemFunctionOperationModeRelationListDataSelectors::
    setSystemFunctionId(const xs_unsignedInt &systemFunctionId) {
  m_systemFunctionId = systemFunctionId;
  m_systemFunctionIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionOperationModeRelationListDataSelectors::getSystemFunctionId()
    const {
  return m_systemFunctionId;
}

void HvacSystemFunctionOperationModeRelationListDataSelectors::
    cleanSystemFunctionId() {
  m_systemFunctionId = 0;
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionOperationModeRelationListDataSelectors::
    getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

bool HvacSystemFunctionOperationModeRelationListDataSelectors::selects(
    const HvacSystemFunctionOperationModeRelationData &data) const {
  if (getSystemFunctionIdIsSet() &&
      (!data.getSystemFunctionIdIsSet() ||
       getSystemFunctionId() != data.getSystemFunctionId())) {
    return false;
  }
  return true;
}

bool HvacSystemFunctionOperationModeRelationListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"systemFunctionId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "systemFunctionId", &m_systemFunctionId)) {
      m_systemFunctionIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
HvacSystemFunctionOperationModeRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("systemFunctionId", m_systemFunctionId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram