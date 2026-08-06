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

#include <keo_datagram/hvac/HvacOperationModeDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOperationModeDescriptionListDataSelectors::
    HvacOperationModeDescriptionListDataSelectors()
    : DataSelectors(), m_operationModeIdIsSet(false), m_operationModeId(0)

{}

HvacOperationModeDescriptionListDataSelectors::
    HvacOperationModeDescriptionListDataSelectors(
        const xs_unsignedInt &c_operationModeId) {
  setOperationModeId(c_operationModeId);
}

bool HvacOperationModeDescriptionListDataSelectors::operator==(
    const HvacOperationModeDescriptionListDataSelectors &c_classObject) const {
  if (m_operationModeIdIsSet != c_classObject.m_operationModeIdIsSet ||
      (m_operationModeIdIsSet &&
       (m_operationModeId != c_classObject.m_operationModeId))) {
    return false;
  }

  return true;
}

bool HvacOperationModeDescriptionListDataSelectors::operator!=(
    const HvacOperationModeDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOperationModeDescriptionListDataSelectors::isEmpty() const {
  return !m_operationModeIdIsSet;
}

DataSelectors::Type
HvacOperationModeDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr HvacOperationModeDescriptionListDataSelectors::clone() const {
  return std::make_shared<HvacOperationModeDescriptionListDataSelectors>(*this);
}

void HvacOperationModeDescriptionListDataSelectors::setOperationModeId(
    const xs_unsignedInt &operationModeId) {
  m_operationModeId = operationModeId;
  m_operationModeIdIsSet = true;
}

const xs_unsignedInt &
HvacOperationModeDescriptionListDataSelectors::getOperationModeId() const {
  return m_operationModeId;
}

void HvacOperationModeDescriptionListDataSelectors::cleanOperationModeId() {
  m_operationModeId = 0;
  m_operationModeIdIsSet = false;
}

bool HvacOperationModeDescriptionListDataSelectors::getOperationModeIdIsSet()
    const {
  return m_operationModeIdIsSet;
}

bool HvacOperationModeDescriptionListDataSelectors::selects(
    const HvacOperationModeDescriptionData &data) const {
  if (getOperationModeIdIsSet() &&
      (!data.getOperationModeIdIsSet() ||
       getOperationModeId() != data.getOperationModeId())) {
    return false;
  }
  return true;
}

bool HvacOperationModeDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"operationModeId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "operationModeId", &m_operationModeId)) {
      m_operationModeIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacOperationModeDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_operationModeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("operationModeId", m_operationModeId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram