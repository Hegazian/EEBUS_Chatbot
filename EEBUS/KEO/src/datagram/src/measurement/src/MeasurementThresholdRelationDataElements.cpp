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

#include <keo_datagram/measurement/MeasurementThresholdRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementThresholdRelationDataElements::
    MeasurementThresholdRelationDataElements()
    : DataElements(), m_measurementIdIsSet(false), m_thresholdIdIsSet(false)

{}

MeasurementThresholdRelationDataElements::
    MeasurementThresholdRelationDataElements(xs_boolean c_measurementIdIsSet,
                                             xs_boolean c_thresholdIdIsSet)
    : DataElements(), m_measurementIdIsSet(c_measurementIdIsSet),
      m_thresholdIdIsSet(c_thresholdIdIsSet)

{}

bool MeasurementThresholdRelationDataElements::operator==(
    const MeasurementThresholdRelationDataElements &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet) {
    return false;
  }

  return true;
}

bool MeasurementThresholdRelationDataElements::operator!=(
    const MeasurementThresholdRelationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementThresholdRelationDataElements::isEmpty() const {
  return !m_measurementIdIsSet && !m_thresholdIdIsSet;
}

DataElements::Type
MeasurementThresholdRelationDataElements::getDataType() const {
  return DataElements::Type::MEASUREMENT_THRESHOLD_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr MeasurementThresholdRelationDataElements::clone() const {
  return std::make_shared<MeasurementThresholdRelationDataElements>(*this);
}

void MeasurementThresholdRelationDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void MeasurementThresholdRelationDataElements::cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool MeasurementThresholdRelationDataElements::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementThresholdRelationDataElements::setThresholdId() {
  m_thresholdIdIsSet = true;
}

void MeasurementThresholdRelationDataElements::cleanThresholdId() {
  m_thresholdIdIsSet = false;
}

bool MeasurementThresholdRelationDataElements::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

bool MeasurementThresholdRelationDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "thresholdId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "measurementId")) {
      m_measurementIdIsSet = true;
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

std::string MeasurementThresholdRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thresholdId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram