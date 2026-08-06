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

#include <keo_datagram/measurement/MeasurementConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementConstraintsDataElements::MeasurementConstraintsDataElements()
    : DataElements(), m_measurementIdIsSet(false), m_valueRangeMinIsSet(false),
      m_valueRangeMin(ScaledNumberElements()), m_valueRangeMaxIsSet(false),
      m_valueRangeMax(ScaledNumberElements()), m_valueStepSizeIsSet(false),
      m_valueStepSize(ScaledNumberElements())

{}

bool MeasurementConstraintsDataElements::
operator==(const MeasurementConstraintsDataElements &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_valueRangeMinIsSet != c_classObject.m_valueRangeMinIsSet ||
      (m_valueRangeMinIsSet &&
       (m_valueRangeMin != c_classObject.m_valueRangeMin))) {
    return false;
  }
  if (m_valueRangeMaxIsSet != c_classObject.m_valueRangeMaxIsSet ||
      (m_valueRangeMaxIsSet &&
       (m_valueRangeMax != c_classObject.m_valueRangeMax))) {
    return false;
  }
  if (m_valueStepSizeIsSet != c_classObject.m_valueStepSizeIsSet ||
      (m_valueStepSizeIsSet &&
       (m_valueStepSize != c_classObject.m_valueStepSize))) {
    return false;
  }

  return true;
}

bool MeasurementConstraintsDataElements::
operator!=(const MeasurementConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementConstraintsDataElements::isEmpty() const {
  return !m_measurementIdIsSet && !m_valueRangeMinIsSet &&
         !m_valueRangeMaxIsSet && !m_valueStepSizeIsSet;
}

DataElements::Type MeasurementConstraintsDataElements::getDataType() const {
  return DataElements::Type::MEASUREMENT_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr MeasurementConstraintsDataElements::clone() const {
  return std::make_shared<MeasurementConstraintsDataElements>(*this);
}

void MeasurementConstraintsDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void MeasurementConstraintsDataElements::cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool MeasurementConstraintsDataElements::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementConstraintsDataElements::setValueRangeMin(
    const ScaledNumberElements &valueRangeMin) {
  m_valueRangeMin = valueRangeMin;
  m_valueRangeMinIsSet = true;
}

const ScaledNumberElements &
MeasurementConstraintsDataElements::getValueRangeMin() const {
  return m_valueRangeMin;
}

void MeasurementConstraintsDataElements::cleanValueRangeMin() {
  m_valueRangeMin = ScaledNumberElements();
  m_valueRangeMinIsSet = false;
}

bool MeasurementConstraintsDataElements::getValueRangeMinIsSet() const {
  return m_valueRangeMinIsSet;
}

void MeasurementConstraintsDataElements::setValueRangeMax(
    const ScaledNumberElements &valueRangeMax) {
  m_valueRangeMax = valueRangeMax;
  m_valueRangeMaxIsSet = true;
}

const ScaledNumberElements &
MeasurementConstraintsDataElements::getValueRangeMax() const {
  return m_valueRangeMax;
}

void MeasurementConstraintsDataElements::cleanValueRangeMax() {
  m_valueRangeMax = ScaledNumberElements();
  m_valueRangeMaxIsSet = false;
}

bool MeasurementConstraintsDataElements::getValueRangeMaxIsSet() const {
  return m_valueRangeMaxIsSet;
}

void MeasurementConstraintsDataElements::setValueStepSize(
    const ScaledNumberElements &valueStepSize) {
  m_valueStepSize = valueStepSize;
  m_valueStepSizeIsSet = true;
}

const ScaledNumberElements &
MeasurementConstraintsDataElements::getValueStepSize() const {
  return m_valueStepSize;
}

void MeasurementConstraintsDataElements::cleanValueStepSize() {
  m_valueStepSize = ScaledNumberElements();
  m_valueStepSizeIsSet = false;
}

bool MeasurementConstraintsDataElements::getValueStepSizeIsSet() const {
  return m_valueStepSizeIsSet;
}

bool MeasurementConstraintsDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "valueRangeMin", "valueRangeMax",
                   "valueStepSize"})) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueRangeMin", &m_valueRangeMin)) {
      m_valueRangeMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueRangeMax", &m_valueRangeMax)) {
      m_valueRangeMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueStepSize", &m_valueStepSize)) {
      m_valueStepSizeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_valueRangeMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueRangeMin", m_valueRangeMin);
  }
  if (m_valueRangeMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueRangeMax", m_valueRangeMax);
  }
  if (m_valueStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueStepSize", m_valueStepSize);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram