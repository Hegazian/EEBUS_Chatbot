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

#include <keo_datagram/smartenergymanagementps/PowerSequencePriceCalculationRequestCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequencePriceCalculationRequestCall::
    PowerSequencePriceCalculationRequestCall()
    : CmdData(), m_sequenceIdIsSet(false), m_sequenceId(0),
      m_potentialStartTimeIsSet(false),
      m_potentialStartTime(AbsoluteOrRelativeTime())

{}

PowerSequencePriceCalculationRequestCall::
    PowerSequencePriceCalculationRequestCall(
        const xs_unsignedInt &c_sequenceId,
        const AbsoluteOrRelativeTime &c_potentialStartTime)
    : CmdData(), m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId),
      m_potentialStartTimeIsSet(true),
      m_potentialStartTime(c_potentialStartTime)

{}

bool PowerSequencePriceCalculationRequestCall::operator==(
    const PowerSequencePriceCalculationRequestCall &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_potentialStartTimeIsSet != c_classObject.m_potentialStartTimeIsSet ||
      (m_potentialStartTimeIsSet &&
       (m_potentialStartTime != c_classObject.m_potentialStartTime))) {
    return false;
  }

  return true;
}

bool PowerSequencePriceCalculationRequestCall::operator!=(
    const PowerSequencePriceCalculationRequestCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequencePriceCalculationRequestCall::isEmpty() const {
  return !m_sequenceIdIsSet && !m_potentialStartTimeIsSet;
}

CmdData::Type PowerSequencePriceCalculationRequestCall::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_TYPE;
}

CmdDataPtr PowerSequencePriceCalculationRequestCall::clone() const {
  return std::make_shared<PowerSequencePriceCalculationRequestCall>(*this);
}

void PowerSequencePriceCalculationRequestCall::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerSequencePriceCalculationRequestCall::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequencePriceCalculationRequestCall::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequencePriceCalculationRequestCall::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequencePriceCalculationRequestCall::setPotentialStartTime(
    const AbsoluteOrRelativeTime &potentialStartTime) {
  m_potentialStartTime = potentialStartTime;
  m_potentialStartTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
PowerSequencePriceCalculationRequestCall::getPotentialStartTime() const {
  return m_potentialStartTime;
}

void PowerSequencePriceCalculationRequestCall::cleanPotentialStartTime() {
  m_potentialStartTime = AbsoluteOrRelativeTime();
  m_potentialStartTimeIsSet = false;
}

bool PowerSequencePriceCalculationRequestCall::getPotentialStartTimeIsSet()
    const {
  return m_potentialStartTimeIsSet;
}

CmdDataPtr PowerSequencePriceCalculationRequestCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<PowerSequencePriceCalculationRequestCall>(*this);
}

bool PowerSequencePriceCalculationRequestCall::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "potentialStartTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "potentialStartTime",
                                   &m_potentialStartTime)) {
      m_potentialStartTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequencePriceCalculationRequestCall::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_potentialStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("potentialStartTime",
                                           m_potentialStartTime);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram