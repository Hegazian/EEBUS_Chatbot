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

#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionPowerSequenceRelationDataElements::
    HvacSystemFunctionPowerSequenceRelationDataElements()
    : DataElements(), m_systemFunctionIdIsSet(false), m_sequenceIdIsSet(false)

{}

HvacSystemFunctionPowerSequenceRelationDataElements::
    HvacSystemFunctionPowerSequenceRelationDataElements(
        xs_boolean c_systemFunctionIdIsSet, xs_boolean c_sequenceIdIsSet)
    : DataElements(), m_systemFunctionIdIsSet(c_systemFunctionIdIsSet),
      m_sequenceIdIsSet(c_sequenceIdIsSet)

{}

bool HvacSystemFunctionPowerSequenceRelationDataElements::operator==(
    const HvacSystemFunctionPowerSequenceRelationDataElements &c_classObject)
    const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionPowerSequenceRelationDataElements::operator!=(
    const HvacSystemFunctionPowerSequenceRelationDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionPowerSequenceRelationDataElements::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_sequenceIdIsSet;
}

DataElements::Type
HvacSystemFunctionPowerSequenceRelationDataElements::getDataType() const {
  return DataElements::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
HvacSystemFunctionPowerSequenceRelationDataElements::clone() const {
  return std::make_shared<HvacSystemFunctionPowerSequenceRelationDataElements>(
      *this);
}

void HvacSystemFunctionPowerSequenceRelationDataElements::
    setSystemFunctionId() {
  m_systemFunctionIdIsSet = true;
}

void HvacSystemFunctionPowerSequenceRelationDataElements::
    cleanSystemFunctionId() {
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionPowerSequenceRelationDataElements::
    getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionPowerSequenceRelationDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void HvacSystemFunctionPowerSequenceRelationDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool HvacSystemFunctionPowerSequenceRelationDataElements::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

bool HvacSystemFunctionPowerSequenceRelationDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "systemFunctionId")) {
      m_systemFunctionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
HvacSystemFunctionPowerSequenceRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("systemFunctionId");
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram