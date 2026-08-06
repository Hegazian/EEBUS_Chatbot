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

#include <keo_datagram/supplycondition/SupplyConditionDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionDescriptionListDataSelectors::
    SupplyConditionDescriptionListDataSelectors()
    : DataSelectors(), m_conditionIdIsSet(false), m_conditionId(0)

{}

SupplyConditionDescriptionListDataSelectors::
    SupplyConditionDescriptionListDataSelectors(
        const xs_unsignedInt &c_conditionId) {
  setConditionId(c_conditionId);
}

bool SupplyConditionDescriptionListDataSelectors::operator==(
    const SupplyConditionDescriptionListDataSelectors &c_classObject) const {
  if (m_conditionIdIsSet != c_classObject.m_conditionIdIsSet ||
      (m_conditionIdIsSet && (m_conditionId != c_classObject.m_conditionId))) {
    return false;
  }

  return true;
}

bool SupplyConditionDescriptionListDataSelectors::operator!=(
    const SupplyConditionDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionDescriptionListDataSelectors::isEmpty() const {
  return !m_conditionIdIsSet;
}

DataSelectors::Type
SupplyConditionDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SupplyConditionDescriptionListDataSelectors::clone() const {
  return std::make_shared<SupplyConditionDescriptionListDataSelectors>(*this);
}

void SupplyConditionDescriptionListDataSelectors::setConditionId(
    const xs_unsignedInt &conditionId) {
  m_conditionId = conditionId;
  m_conditionIdIsSet = true;
}

const xs_unsignedInt &
SupplyConditionDescriptionListDataSelectors::getConditionId() const {
  return m_conditionId;
}

void SupplyConditionDescriptionListDataSelectors::cleanConditionId() {
  m_conditionId = 0;
  m_conditionIdIsSet = false;
}

bool SupplyConditionDescriptionListDataSelectors::getConditionIdIsSet() const {
  return m_conditionIdIsSet;
}

bool SupplyConditionDescriptionListDataSelectors::selects(
    const SupplyConditionDescriptionData &data) const {
  if (getConditionIdIsSet() && (!data.getConditionIdIsSet() ||
                                getConditionId() != data.getConditionId())) {
    return false;
  }
  return true;
}

bool SupplyConditionDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"conditionId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "conditionId", &m_conditionId)) {
      m_conditionIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SupplyConditionDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("conditionId", m_conditionId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram