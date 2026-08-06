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

#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceSchedulePreferenceDataElements::
    PowerSequenceSchedulePreferenceDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_greenestIsSet(false),
      m_cheapestIsSet(false)

{}

PowerSequenceSchedulePreferenceDataElements::
    PowerSequenceSchedulePreferenceDataElements(xs_boolean c_sequenceIdIsSet,
                                                xs_boolean c_greenestIsSet,
                                                xs_boolean c_cheapestIsSet)
    : DataElements(), m_sequenceIdIsSet(c_sequenceIdIsSet),
      m_greenestIsSet(c_greenestIsSet), m_cheapestIsSet(c_cheapestIsSet)

{}

bool PowerSequenceSchedulePreferenceDataElements::operator==(
    const PowerSequenceSchedulePreferenceDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_greenestIsSet != c_classObject.m_greenestIsSet) {
    return false;
  }
  if (m_cheapestIsSet != c_classObject.m_cheapestIsSet) {
    return false;
  }

  return true;
}

bool PowerSequenceSchedulePreferenceDataElements::operator!=(
    const PowerSequenceSchedulePreferenceDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceSchedulePreferenceDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_greenestIsSet && !m_cheapestIsSet;
}

DataElements::Type
PowerSequenceSchedulePreferenceDataElements::getDataType() const {
  return DataElements::Type::
      POWER_SEQUENCE_SCHEDULE_PREFERENCE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerSequenceSchedulePreferenceDataElements::clone() const {
  return std::make_shared<PowerSequenceSchedulePreferenceDataElements>(*this);
}

void PowerSequenceSchedulePreferenceDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerSequenceSchedulePreferenceDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerSequenceSchedulePreferenceDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceSchedulePreferenceDataElements::setGreenest() {
  m_greenestIsSet = true;
}

void PowerSequenceSchedulePreferenceDataElements::cleanGreenest() {
  m_greenestIsSet = false;
}

bool PowerSequenceSchedulePreferenceDataElements::getGreenestIsSet() const {
  return m_greenestIsSet;
}

void PowerSequenceSchedulePreferenceDataElements::setCheapest() {
  m_cheapestIsSet = true;
}

void PowerSequenceSchedulePreferenceDataElements::cleanCheapest() {
  m_cheapestIsSet = false;
}

bool PowerSequenceSchedulePreferenceDataElements::getCheapestIsSet() const {
  return m_cheapestIsSet;
}

bool PowerSequenceSchedulePreferenceDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "greenest", "cheapest"})) {
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
                                     "greenest")) {
      m_greenestIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "cheapest")) {
      m_cheapestIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceSchedulePreferenceDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_greenestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("greenest");
  }
  if (m_cheapestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("cheapest");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram