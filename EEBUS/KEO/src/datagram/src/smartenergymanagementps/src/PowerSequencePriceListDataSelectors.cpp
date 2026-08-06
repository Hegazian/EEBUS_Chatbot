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

#include <keo_datagram/smartenergymanagementps/PowerSequencePriceListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequencePriceListDataSelectors::PowerSequencePriceListDataSelectors()
    : DataSelectors(), m_sequenceIdIsSet(false), m_sequenceId(0),
      m_potentialStartTimeIntervalIsSet(false),
      m_potentialStartTimeInterval(TimestampInterval())

{}

PowerSequencePriceListDataSelectors::PowerSequencePriceListDataSelectors(
    const xs_unsignedInt &c_sequenceId,
    const TimestampInterval &c_potentialStartTimeInterval)
    : DataSelectors(), m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId),
      m_potentialStartTimeIntervalIsSet(true),
      m_potentialStartTimeInterval(c_potentialStartTimeInterval)

{}

bool PowerSequencePriceListDataSelectors::
operator==(const PowerSequencePriceListDataSelectors &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_potentialStartTimeIntervalIsSet !=
          c_classObject.m_potentialStartTimeIntervalIsSet ||
      (m_potentialStartTimeIntervalIsSet &&
       (m_potentialStartTimeInterval !=
        c_classObject.m_potentialStartTimeInterval))) {
    return false;
  }

  return true;
}

bool PowerSequencePriceListDataSelectors::
operator!=(const PowerSequencePriceListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequencePriceListDataSelectors::isEmpty() const {
  return !m_sequenceIdIsSet && !m_potentialStartTimeIntervalIsSet;
}

DataSelectors::Type PowerSequencePriceListDataSelectors::getDataType() const {
  return DataSelectors::Type::POWER_SEQUENCE_PRICE_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr PowerSequencePriceListDataSelectors::clone() const {
  return std::make_shared<PowerSequencePriceListDataSelectors>(*this);
}

void PowerSequencePriceListDataSelectors::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerSequencePriceListDataSelectors::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequencePriceListDataSelectors::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequencePriceListDataSelectors::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequencePriceListDataSelectors::setPotentialStartTimeInterval(
    const TimestampInterval &potentialStartTimeInterval) {
  m_potentialStartTimeInterval = potentialStartTimeInterval;
  m_potentialStartTimeIntervalIsSet = true;
}

const TimestampInterval &
PowerSequencePriceListDataSelectors::getPotentialStartTimeInterval() const {
  return m_potentialStartTimeInterval;
}

void PowerSequencePriceListDataSelectors::cleanPotentialStartTimeInterval() {
  m_potentialStartTimeInterval = TimestampInterval();
  m_potentialStartTimeIntervalIsSet = false;
}

bool PowerSequencePriceListDataSelectors::getPotentialStartTimeIntervalIsSet()
    const {
  return m_potentialStartTimeIntervalIsSet;
}

bool PowerSequencePriceListDataSelectors::selects(
    const PowerSequencePriceData &data) const {
  if (getSequenceIdIsSet() &&
      (!data.getSequenceIdIsSet() || getSequenceId() != data.getSequenceId())) {
    return false;
  }
  if (getPotentialStartTimeIntervalIsSet() &&
      (!data.getPotentialStartTimeIsSet() ||
       (data.getPotentialStartTime().getDateTime() <
            getPotentialStartTimeInterval().getStartTime().getDateTime() ||
        data.getPotentialStartTime().getDateTime() >
            getPotentialStartTimeInterval().getEndTime().getDateTime()))) {
    return false;
  }
  return true;
}

bool PowerSequencePriceListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "potentialStartTimeInterval"})) {
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
                                   "potentialStartTimeInterval",
                                   &m_potentialStartTimeInterval)) {
      m_potentialStartTimeIntervalIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequencePriceListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_potentialStartTimeIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("potentialStartTimeInterval",
                                           m_potentialStartTimeInterval);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram