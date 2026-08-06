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

#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceData.h>

#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceSchedulePreferenceData::PowerSequenceSchedulePreferenceData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_greenestIsSet(false),
      m_greenest(false), m_cheapestIsSet(false), m_cheapest(false)

{}

PowerSequenceSchedulePreferenceData::PowerSequenceSchedulePreferenceData(
    const xs_unsignedInt &c_sequenceId, const xs_boolean &c_greenest,
    const xs_boolean &c_cheapest)
    : m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId),
      m_greenestIsSet(true), m_greenest(c_greenest), m_cheapestIsSet(true),
      m_cheapest(c_cheapest)

{}

bool PowerSequenceSchedulePreferenceData::
operator==(const PowerSequenceSchedulePreferenceData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_greenestIsSet != c_classObject.m_greenestIsSet ||
      (m_greenestIsSet && (m_greenest != c_classObject.m_greenest))) {
    return false;
  }
  if (m_cheapestIsSet != c_classObject.m_cheapestIsSet ||
      (m_cheapestIsSet && (m_cheapest != c_classObject.m_cheapest))) {
    return false;
  }

  return true;
}

bool PowerSequenceSchedulePreferenceData::
operator!=(const PowerSequenceSchedulePreferenceData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceSchedulePreferenceData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_greenestIsSet && !m_cheapestIsSet;
}

void PowerSequenceSchedulePreferenceData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerSequenceSchedulePreferenceData::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceSchedulePreferenceData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequenceSchedulePreferenceData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceSchedulePreferenceData::setGreenest(
    const xs_boolean &greenest) {
  m_greenest = greenest;
  m_greenestIsSet = true;
}

const xs_boolean &PowerSequenceSchedulePreferenceData::getGreenest() const {
  return m_greenest;
}

void PowerSequenceSchedulePreferenceData::cleanGreenest() {
  m_greenest = false;
  m_greenestIsSet = false;
}

bool PowerSequenceSchedulePreferenceData::getGreenestIsSet() const {
  return m_greenestIsSet;
}

void PowerSequenceSchedulePreferenceData::setCheapest(
    const xs_boolean &cheapest) {
  m_cheapest = cheapest;
  m_cheapestIsSet = true;
}

const xs_boolean &PowerSequenceSchedulePreferenceData::getCheapest() const {
  return m_cheapest;
}

void PowerSequenceSchedulePreferenceData::cleanCheapest() {
  m_cheapest = false;
  m_cheapestIsSet = false;
}

bool PowerSequenceSchedulePreferenceData::getCheapestIsSet() const {
  return m_cheapestIsSet;
}

PowerSequenceSchedulePreferenceData PowerSequenceSchedulePreferenceData::reduce(
    const PowerSequenceSchedulePreferenceDataElements &elements) const {
  PowerSequenceSchedulePreferenceData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getGreenestIsSet() && elements.getGreenestIsSet()) {
    dataOut.setGreenest(getGreenest());
  }
  if (getCheapestIsSet() && elements.getCheapestIsSet()) {
    dataOut.setCheapest(getCheapest());
  }
  return dataOut;
}

bool PowerSequenceSchedulePreferenceData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "greenest", "cheapest"})) {
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
                                   "greenest", &m_greenest)) {
      m_greenestIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "cheapest", &m_cheapest)) {
      m_cheapestIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceSchedulePreferenceData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_greenestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("greenest", m_greenest);
  }
  if (m_cheapestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("cheapest", m_cheapest);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram