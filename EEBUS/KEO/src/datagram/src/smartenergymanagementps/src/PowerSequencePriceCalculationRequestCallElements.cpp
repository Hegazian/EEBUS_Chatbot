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

#include <keo_datagram/smartenergymanagementps/PowerSequencePriceCalculationRequestCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequencePriceCalculationRequestCallElements::
    PowerSequencePriceCalculationRequestCallElements()
    : DataElements(), m_sequenceIdIsSet(false), m_potentialStartTimeIsSet(false)

{}

PowerSequencePriceCalculationRequestCallElements::
    PowerSequencePriceCalculationRequestCallElements(
        xs_boolean c_sequenceIdIsSet, xs_boolean c_potentialStartTimeIsSet)
    : DataElements(), m_sequenceIdIsSet(c_sequenceIdIsSet),
      m_potentialStartTimeIsSet(c_potentialStartTimeIsSet)

{}

bool PowerSequencePriceCalculationRequestCallElements::operator==(
    const PowerSequencePriceCalculationRequestCallElements &c_classObject)
    const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_potentialStartTimeIsSet != c_classObject.m_potentialStartTimeIsSet) {
    return false;
  }

  return true;
}

bool PowerSequencePriceCalculationRequestCallElements::operator!=(
    const PowerSequencePriceCalculationRequestCallElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool PowerSequencePriceCalculationRequestCallElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_potentialStartTimeIsSet;
}

DataElements::Type
PowerSequencePriceCalculationRequestCallElements::getDataType() const {
  return DataElements::Type::
      POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_ELEMENTS_TYPE;
}

DataElementsPtr
PowerSequencePriceCalculationRequestCallElements::clone() const {
  return std::make_shared<PowerSequencePriceCalculationRequestCallElements>(
      *this);
}

void PowerSequencePriceCalculationRequestCallElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerSequencePriceCalculationRequestCallElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerSequencePriceCalculationRequestCallElements::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

void PowerSequencePriceCalculationRequestCallElements::setPotentialStartTime() {
  m_potentialStartTimeIsSet = true;
}

void PowerSequencePriceCalculationRequestCallElements::
    cleanPotentialStartTime() {
  m_potentialStartTimeIsSet = false;
}

bool PowerSequencePriceCalculationRequestCallElements::
    getPotentialStartTimeIsSet() const {
  return m_potentialStartTimeIsSet;
}

bool PowerSequencePriceCalculationRequestCallElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "potentialStartTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "potentialStartTime")) {
      m_potentialStartTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequencePriceCalculationRequestCallElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_potentialStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("potentialStartTime");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram