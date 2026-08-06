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

#include <keo_datagram/hvac/HvacSystemFunctionDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionDescriptionListDataSelectors::
    HvacSystemFunctionDescriptionListDataSelectors()
    : DataSelectors(), m_systemFunctionIdIsSet(false), m_systemFunctionId(0)

{}

HvacSystemFunctionDescriptionListDataSelectors::
    HvacSystemFunctionDescriptionListDataSelectors(
        const xs_unsignedInt &c_systemFunctionId) {
  setSystemFunctionId(c_systemFunctionId);
}

bool HvacSystemFunctionDescriptionListDataSelectors::operator==(
    const HvacSystemFunctionDescriptionListDataSelectors &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet ||
      (m_systemFunctionIdIsSet &&
       (m_systemFunctionId != c_classObject.m_systemFunctionId))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionDescriptionListDataSelectors::operator!=(
    const HvacSystemFunctionDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionDescriptionListDataSelectors::isEmpty() const {
  return !m_systemFunctionIdIsSet;
}

DataSelectors::Type
HvacSystemFunctionDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr HvacSystemFunctionDescriptionListDataSelectors::clone() const {
  return std::make_shared<HvacSystemFunctionDescriptionListDataSelectors>(
      *this);
}

void HvacSystemFunctionDescriptionListDataSelectors::setSystemFunctionId(
    const xs_unsignedInt &systemFunctionId) {
  m_systemFunctionId = systemFunctionId;
  m_systemFunctionIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionDescriptionListDataSelectors::getSystemFunctionId() const {
  return m_systemFunctionId;
}

void HvacSystemFunctionDescriptionListDataSelectors::cleanSystemFunctionId() {
  m_systemFunctionId = 0;
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionDescriptionListDataSelectors::getSystemFunctionIdIsSet()
    const {
  return m_systemFunctionIdIsSet;
}

bool HvacSystemFunctionDescriptionListDataSelectors::selects(
    const HvacSystemFunctionDescriptionData &data) const {
  if (getSystemFunctionIdIsSet() &&
      (!data.getSystemFunctionIdIsSet() ||
       getSystemFunctionId() != data.getSystemFunctionId())) {
    return false;
  }
  return true;
}

bool HvacSystemFunctionDescriptionListDataSelectors::fromJson(
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

std::string HvacSystemFunctionDescriptionListDataSelectors::toJson() const {
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