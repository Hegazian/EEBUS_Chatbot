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

#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationData.h>

#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsResumeImplicationData::
    OperatingConstraintsResumeImplicationData()
    : m_sequenceIdIsSet(false), m_sequenceId(0),
      m_resumeEnergyEstimatedIsSet(false),
      m_resumeEnergyEstimated(ScaledNumber()), m_energyUnitIsSet(false),
      m_energyUnit(UnitOfMeasurement()), m_resumeCostEstimatedIsSet(false),
      m_resumeCostEstimated(ScaledNumber()), m_currencyIsSet(false),
      m_currency(Currency())

{}

bool OperatingConstraintsResumeImplicationData::operator==(
    const OperatingConstraintsResumeImplicationData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_resumeEnergyEstimatedIsSet !=
          c_classObject.m_resumeEnergyEstimatedIsSet ||
      (m_resumeEnergyEstimatedIsSet &&
       (m_resumeEnergyEstimated != c_classObject.m_resumeEnergyEstimated))) {
    return false;
  }
  if (m_energyUnitIsSet != c_classObject.m_energyUnitIsSet ||
      (m_energyUnitIsSet && (m_energyUnit != c_classObject.m_energyUnit))) {
    return false;
  }
  if (m_resumeCostEstimatedIsSet != c_classObject.m_resumeCostEstimatedIsSet ||
      (m_resumeCostEstimatedIsSet &&
       (m_resumeCostEstimated != c_classObject.m_resumeCostEstimated))) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet ||
      (m_currencyIsSet && (m_currency != c_classObject.m_currency))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsResumeImplicationData::operator!=(
    const OperatingConstraintsResumeImplicationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsResumeImplicationData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_resumeEnergyEstimatedIsSet &&
         !m_energyUnitIsSet && !m_resumeCostEstimatedIsSet && !m_currencyIsSet;
}

void OperatingConstraintsResumeImplicationData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
OperatingConstraintsResumeImplicationData::getSequenceId() const {
  return m_sequenceId;
}

void OperatingConstraintsResumeImplicationData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsResumeImplicationData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsResumeImplicationData::setResumeEnergyEstimated(
    const ScaledNumber &resumeEnergyEstimated) {
  m_resumeEnergyEstimated = resumeEnergyEstimated;
  m_resumeEnergyEstimatedIsSet = true;
}

const ScaledNumber &
OperatingConstraintsResumeImplicationData::getResumeEnergyEstimated() const {
  return m_resumeEnergyEstimated;
}

void OperatingConstraintsResumeImplicationData::cleanResumeEnergyEstimated() {
  m_resumeEnergyEstimated = ScaledNumber();
  m_resumeEnergyEstimatedIsSet = false;
}

bool OperatingConstraintsResumeImplicationData::getResumeEnergyEstimatedIsSet()
    const {
  return m_resumeEnergyEstimatedIsSet;
}

void OperatingConstraintsResumeImplicationData::setEnergyUnit(
    const UnitOfMeasurement &energyUnit) {
  m_energyUnit = energyUnit;
  m_energyUnitIsSet = true;
}

const UnitOfMeasurement &
OperatingConstraintsResumeImplicationData::getEnergyUnit() const {
  return m_energyUnit;
}

void OperatingConstraintsResumeImplicationData::cleanEnergyUnit() {
  m_energyUnit = UnitOfMeasurement();
  m_energyUnitIsSet = false;
}

bool OperatingConstraintsResumeImplicationData::getEnergyUnitIsSet() const {
  return m_energyUnitIsSet;
}

void OperatingConstraintsResumeImplicationData::setResumeCostEstimated(
    const ScaledNumber &resumeCostEstimated) {
  m_resumeCostEstimated = resumeCostEstimated;
  m_resumeCostEstimatedIsSet = true;
}

const ScaledNumber &
OperatingConstraintsResumeImplicationData::getResumeCostEstimated() const {
  return m_resumeCostEstimated;
}

void OperatingConstraintsResumeImplicationData::cleanResumeCostEstimated() {
  m_resumeCostEstimated = ScaledNumber();
  m_resumeCostEstimatedIsSet = false;
}

bool OperatingConstraintsResumeImplicationData::getResumeCostEstimatedIsSet()
    const {
  return m_resumeCostEstimatedIsSet;
}

void OperatingConstraintsResumeImplicationData::setCurrency(
    const Currency &currency) {
  m_currency = currency;
  m_currencyIsSet = true;
}

const Currency &OperatingConstraintsResumeImplicationData::getCurrency() const {
  return m_currency;
}

void OperatingConstraintsResumeImplicationData::cleanCurrency() {
  m_currency = Currency();
  m_currencyIsSet = false;
}

bool OperatingConstraintsResumeImplicationData::getCurrencyIsSet() const {
  return m_currencyIsSet;
}

OperatingConstraintsResumeImplicationData
OperatingConstraintsResumeImplicationData::reduce(
    const OperatingConstraintsResumeImplicationDataElements &elements) const {
  OperatingConstraintsResumeImplicationData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getResumeEnergyEstimatedIsSet() &&
      elements.getResumeEnergyEstimatedIsSet()) {
    dataOut.setResumeEnergyEstimated(
        getResumeEnergyEstimated().reduce(elements.getResumeEnergyEstimated()));
  }
  if (getEnergyUnitIsSet() && elements.getEnergyUnitIsSet()) {
    dataOut.setEnergyUnit(getEnergyUnit());
  }
  if (getResumeCostEstimatedIsSet() && elements.getResumeCostEstimatedIsSet()) {
    dataOut.setResumeCostEstimated(
        getResumeCostEstimated().reduce(elements.getResumeCostEstimated()));
  }
  if (getCurrencyIsSet() && elements.getCurrencyIsSet()) {
    dataOut.setCurrency(getCurrency());
  }
  return dataOut;
}

bool OperatingConstraintsResumeImplicationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "resumeEnergyEstimated", "energyUnit",
                   "resumeCostEstimated", "currency"})) {
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
                                   "resumeEnergyEstimated",
                                   &m_resumeEnergyEstimated)) {
      m_resumeEnergyEstimatedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "energyUnit", &m_energyUnit)) {
      m_energyUnitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "resumeCostEstimated",
                                   &m_resumeCostEstimated)) {
      m_resumeCostEstimatedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "currency", &m_currency)) {
      m_currencyIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsResumeImplicationData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_resumeEnergyEstimatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("resumeEnergyEstimated",
                                           m_resumeEnergyEstimated);
  }
  if (m_energyUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("energyUnit", m_energyUnit);
  }
  if (m_resumeCostEstimatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("resumeCostEstimated",
                                           m_resumeCostEstimated);
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("currency", m_currency);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram