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

#include <keo_datagram/measurement/MeasurementThresholdRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementThresholdRelationListDataSelectors::
    MeasurementThresholdRelationListDataSelectors()
    : DataSelectors(), m_measurementIdIsSet(false), m_measurementId(0),
      m_thresholdIdIsSet(false), m_thresholdId(0)

{}

MeasurementThresholdRelationListDataSelectors::
    MeasurementThresholdRelationListDataSelectors(
        const xs_unsignedInt &c_measurementId,
        const xs_unsignedInt &c_thresholdId)
    : DataSelectors(), m_measurementIdIsSet(true),
      m_measurementId(c_measurementId), m_thresholdIdIsSet(true),
      m_thresholdId(c_thresholdId)

{}

bool MeasurementThresholdRelationListDataSelectors::operator==(
    const MeasurementThresholdRelationListDataSelectors &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }

  return true;
}

bool MeasurementThresholdRelationListDataSelectors::operator!=(
    const MeasurementThresholdRelationListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementThresholdRelationListDataSelectors::isEmpty() const {
  return !m_measurementIdIsSet && !m_thresholdIdIsSet;
}

DataSelectors::Type
MeasurementThresholdRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr MeasurementThresholdRelationListDataSelectors::clone() const {
  return std::make_shared<MeasurementThresholdRelationListDataSelectors>(*this);
}

void MeasurementThresholdRelationListDataSelectors::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
MeasurementThresholdRelationListDataSelectors::getMeasurementId() const {
  return m_measurementId;
}

void MeasurementThresholdRelationListDataSelectors::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool MeasurementThresholdRelationListDataSelectors::getMeasurementIdIsSet()
    const {
  return m_measurementIdIsSet;
}

void MeasurementThresholdRelationListDataSelectors::setThresholdId(
    const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &
MeasurementThresholdRelationListDataSelectors::getThresholdId() const {
  return m_thresholdId;
}

void MeasurementThresholdRelationListDataSelectors::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool MeasurementThresholdRelationListDataSelectors::getThresholdIdIsSet()
    const {
  return m_thresholdIdIsSet;
}

bool MeasurementThresholdRelationListDataSelectors::selects(
    const MeasurementThresholdRelationData &data) const {
  if (getMeasurementIdIsSet() &&
      (!data.getMeasurementIdIsSet() ||
       getMeasurementId() != data.getMeasurementId())) {
    return false;
  }
  if (getThresholdIdIsSet() &&
      (!data.getThresholdIdIsSet() ||
       std::find(std::begin(data.getThresholdId()),
                 std::end(data.getThresholdId()),
                 getThresholdId()) == std::end(data.getThresholdId()))) {
    return false;
  }
  return true;
}

bool MeasurementThresholdRelationListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "thresholdId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdId", &m_thresholdId)) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementThresholdRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram