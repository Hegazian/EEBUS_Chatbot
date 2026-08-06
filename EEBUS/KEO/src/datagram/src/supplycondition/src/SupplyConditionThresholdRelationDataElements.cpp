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

#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionThresholdRelationDataElements::
    SupplyConditionThresholdRelationDataElements()
    : DataElements(), m_conditionIdIsSet(false), m_thresholdIdIsSet(false)

{}

SupplyConditionThresholdRelationDataElements::
    SupplyConditionThresholdRelationDataElements(xs_boolean c_conditionIdIsSet,
                                                 xs_boolean c_thresholdIdIsSet)
    : DataElements(), m_conditionIdIsSet(c_conditionIdIsSet),
      m_thresholdIdIsSet(c_thresholdIdIsSet)

{}

bool SupplyConditionThresholdRelationDataElements::operator==(
    const SupplyConditionThresholdRelationDataElements &c_classObject) const {
  if (m_conditionIdIsSet != c_classObject.m_conditionIdIsSet) {
    return false;
  }
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet) {
    return false;
  }

  return true;
}

bool SupplyConditionThresholdRelationDataElements::operator!=(
    const SupplyConditionThresholdRelationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionThresholdRelationDataElements::isEmpty() const {
  return !m_conditionIdIsSet && !m_thresholdIdIsSet;
}

DataElements::Type
SupplyConditionThresholdRelationDataElements::getDataType() const {
  return DataElements::Type::
      SUPPLY_CONDITION_THRESHOLD_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SupplyConditionThresholdRelationDataElements::clone() const {
  return std::make_shared<SupplyConditionThresholdRelationDataElements>(*this);
}

void SupplyConditionThresholdRelationDataElements::setConditionId() {
  m_conditionIdIsSet = true;
}

void SupplyConditionThresholdRelationDataElements::cleanConditionId() {
  m_conditionIdIsSet = false;
}

bool SupplyConditionThresholdRelationDataElements::getConditionIdIsSet() const {
  return m_conditionIdIsSet;
}

void SupplyConditionThresholdRelationDataElements::setThresholdId() {
  m_thresholdIdIsSet = true;
}

void SupplyConditionThresholdRelationDataElements::cleanThresholdId() {
  m_thresholdIdIsSet = false;
}

bool SupplyConditionThresholdRelationDataElements::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

bool SupplyConditionThresholdRelationDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"conditionId", "thresholdId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "conditionId")) {
      m_conditionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "thresholdId")) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SupplyConditionThresholdRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("conditionId");
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thresholdId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram