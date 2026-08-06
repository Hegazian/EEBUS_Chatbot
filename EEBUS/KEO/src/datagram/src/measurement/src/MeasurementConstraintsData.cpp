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

#include <keo_datagram/measurement/MeasurementConstraintsData.h>

#include <keo_datagram/measurement/MeasurementConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementConstraintsData::MeasurementConstraintsData()
    : m_measurementIdIsSet(false), m_measurementId(0),
      m_valueRangeMinIsSet(false), m_valueRangeMin(ScaledNumber()),
      m_valueRangeMaxIsSet(false), m_valueRangeMax(ScaledNumber()),
      m_valueStepSizeIsSet(false), m_valueStepSize(ScaledNumber())

{}

bool MeasurementConstraintsData::
operator==(const MeasurementConstraintsData &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
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

bool MeasurementConstraintsData::
operator!=(const MeasurementConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementConstraintsData::isEmpty() const {
  return !m_measurementIdIsSet && !m_valueRangeMinIsSet &&
         !m_valueRangeMaxIsSet && !m_valueStepSizeIsSet;
}

void MeasurementConstraintsData::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &MeasurementConstraintsData::getMeasurementId() const {
  return m_measurementId;
}

void MeasurementConstraintsData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool MeasurementConstraintsData::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementConstraintsData::setValueRangeMin(
    const ScaledNumber &valueRangeMin) {
  m_valueRangeMin = valueRangeMin;
  m_valueRangeMinIsSet = true;
}

const ScaledNumber &MeasurementConstraintsData::getValueRangeMin() const {
  return m_valueRangeMin;
}

void MeasurementConstraintsData::cleanValueRangeMin() {
  m_valueRangeMin = ScaledNumber();
  m_valueRangeMinIsSet = false;
}

bool MeasurementConstraintsData::getValueRangeMinIsSet() const {
  return m_valueRangeMinIsSet;
}

void MeasurementConstraintsData::setValueRangeMax(
    const ScaledNumber &valueRangeMax) {
  m_valueRangeMax = valueRangeMax;
  m_valueRangeMaxIsSet = true;
}

const ScaledNumber &MeasurementConstraintsData::getValueRangeMax() const {
  return m_valueRangeMax;
}

void MeasurementConstraintsData::cleanValueRangeMax() {
  m_valueRangeMax = ScaledNumber();
  m_valueRangeMaxIsSet = false;
}

bool MeasurementConstraintsData::getValueRangeMaxIsSet() const {
  return m_valueRangeMaxIsSet;
}

void MeasurementConstraintsData::setValueStepSize(
    const ScaledNumber &valueStepSize) {
  m_valueStepSize = valueStepSize;
  m_valueStepSizeIsSet = true;
}

const ScaledNumber &MeasurementConstraintsData::getValueStepSize() const {
  return m_valueStepSize;
}

void MeasurementConstraintsData::cleanValueStepSize() {
  m_valueStepSize = ScaledNumber();
  m_valueStepSizeIsSet = false;
}

bool MeasurementConstraintsData::getValueStepSizeIsSet() const {
  return m_valueStepSizeIsSet;
}

MeasurementConstraintsData MeasurementConstraintsData::reduce(
    const MeasurementConstraintsDataElements &elements) const {
  MeasurementConstraintsData dataOut;
  if (getMeasurementIdIsSet() && elements.getMeasurementIdIsSet()) {
    dataOut.setMeasurementId(getMeasurementId());
  }
  if (getValueRangeMinIsSet() && elements.getValueRangeMinIsSet()) {
    dataOut.setValueRangeMin(
        getValueRangeMin().reduce(elements.getValueRangeMin()));
  }
  if (getValueRangeMaxIsSet() && elements.getValueRangeMaxIsSet()) {
    dataOut.setValueRangeMax(
        getValueRangeMax().reduce(elements.getValueRangeMax()));
  }
  if (getValueStepSizeIsSet() && elements.getValueStepSizeIsSet()) {
    dataOut.setValueStepSize(
        getValueStepSize().reduce(elements.getValueStepSize()));
  }
  return dataOut;
}

bool MeasurementConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "valueRangeMin", "valueRangeMax",
                   "valueStepSize"})) {
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

std::string MeasurementConstraintsData::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
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