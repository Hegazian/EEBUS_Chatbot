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

#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionPowerSequenceRelationListDataSelectors::
    HvacSystemFunctionPowerSequenceRelationListDataSelectors()
    : DataSelectors(), m_systemFunctionIdIsSet(false), m_systemFunctionId(0)

{}

HvacSystemFunctionPowerSequenceRelationListDataSelectors::
    HvacSystemFunctionPowerSequenceRelationListDataSelectors(
        const xs_unsignedInt &c_systemFunctionId) {
  setSystemFunctionId(c_systemFunctionId);
}

bool HvacSystemFunctionPowerSequenceRelationListDataSelectors::
operator==(const HvacSystemFunctionPowerSequenceRelationListDataSelectors
               &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet ||
      (m_systemFunctionIdIsSet &&
       (m_systemFunctionId != c_classObject.m_systemFunctionId))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionPowerSequenceRelationListDataSelectors::
operator!=(const HvacSystemFunctionPowerSequenceRelationListDataSelectors
               &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionPowerSequenceRelationListDataSelectors::isEmpty() const {
  return !m_systemFunctionIdIsSet;
}

DataSelectors::Type
HvacSystemFunctionPowerSequenceRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
HvacSystemFunctionPowerSequenceRelationListDataSelectors::clone() const {
  return std::make_shared<
      HvacSystemFunctionPowerSequenceRelationListDataSelectors>(*this);
}

void HvacSystemFunctionPowerSequenceRelationListDataSelectors::
    setSystemFunctionId(const xs_unsignedInt &systemFunctionId) {
  m_systemFunctionId = systemFunctionId;
  m_systemFunctionIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionPowerSequenceRelationListDataSelectors::getSystemFunctionId()
    const {
  return m_systemFunctionId;
}

void HvacSystemFunctionPowerSequenceRelationListDataSelectors::
    cleanSystemFunctionId() {
  m_systemFunctionId = 0;
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionPowerSequenceRelationListDataSelectors::
    getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

bool HvacSystemFunctionPowerSequenceRelationListDataSelectors::selects(
    const HvacSystemFunctionPowerSequenceRelationData &data) const {
  if (getSystemFunctionIdIsSet() &&
      (!data.getSystemFunctionIdIsSet() ||
       getSystemFunctionId() != data.getSystemFunctionId())) {
    return false;
  }
  return true;
}

bool HvacSystemFunctionPowerSequenceRelationListDataSelectors::fromJson(
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
HvacSystemFunctionPowerSequenceRelationListDataSelectors::toJson() const {
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