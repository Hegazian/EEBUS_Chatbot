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

#include <keo_datagram/measurement/MeasurementThresholdRelationData.h>

#include <keo_datagram/measurement/MeasurementThresholdRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementThresholdRelationData::MeasurementThresholdRelationData()
    : m_measurementIdIsSet(false), m_measurementId(0),
      m_thresholdIdIsSet(false), m_thresholdId(std::vector<xs_unsignedInt>())

{}

MeasurementThresholdRelationData::MeasurementThresholdRelationData(
    const xs_unsignedInt &c_measurementId,
    const std::vector<xs_unsignedInt> &c_thresholdId)
    : m_measurementIdIsSet(true), m_measurementId(c_measurementId),
      m_thresholdIdIsSet(true), m_thresholdId(c_thresholdId)

{}

bool MeasurementThresholdRelationData::
operator==(const MeasurementThresholdRelationData &c_classObject) const {
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

bool MeasurementThresholdRelationData::
operator!=(const MeasurementThresholdRelationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementThresholdRelationData::isEmpty() const {
  return !m_measurementIdIsSet && !m_thresholdIdIsSet;
}

void MeasurementThresholdRelationData::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
MeasurementThresholdRelationData::getMeasurementId() const {
  return m_measurementId;
}

void MeasurementThresholdRelationData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool MeasurementThresholdRelationData::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementThresholdRelationData::setThresholdId(
    const std::vector<xs_unsignedInt> &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const std::vector<xs_unsignedInt> &
MeasurementThresholdRelationData::getThresholdId() const {
  return m_thresholdId;
}

void MeasurementThresholdRelationData::cleanThresholdId() {
  m_thresholdId.clear();
  m_thresholdIdIsSet = false;
}

bool MeasurementThresholdRelationData::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

MeasurementThresholdRelationData MeasurementThresholdRelationData::reduce(
    const MeasurementThresholdRelationDataElements &elements) const {
  MeasurementThresholdRelationData dataOut;
  if (getMeasurementIdIsSet() && elements.getMeasurementIdIsSet()) {
    dataOut.setMeasurementId(getMeasurementId());
  }
  if (getThresholdIdIsSet() && elements.getThresholdIdIsSet()) {
    dataOut.setThresholdId(getThresholdId());
  }
  return dataOut;
}

bool MeasurementThresholdRelationData::fromJson(KeoJsonValue *json) {
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
    if (iter != json->end() && KeoJsonTransformation::getList<xs_unsignedInt>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdId", &m_thresholdId)) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementThresholdRelationData::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>("thresholdId",
                                                               m_thresholdId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram