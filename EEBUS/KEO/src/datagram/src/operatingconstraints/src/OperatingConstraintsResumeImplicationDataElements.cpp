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

#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsResumeImplicationDataElements::
    OperatingConstraintsResumeImplicationDataElements()
    : DataElements(), m_sequenceIdIsSet(false),
      m_resumeEnergyEstimatedIsSet(false),
      m_resumeEnergyEstimated(ScaledNumberElements()), m_energyUnitIsSet(false),
      m_resumeCostEstimatedIsSet(false),
      m_resumeCostEstimated(ScaledNumberElements()), m_currencyIsSet(false)

{}

bool OperatingConstraintsResumeImplicationDataElements::operator==(
    const OperatingConstraintsResumeImplicationDataElements &c_classObject)
    const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_resumeEnergyEstimatedIsSet !=
          c_classObject.m_resumeEnergyEstimatedIsSet ||
      (m_resumeEnergyEstimatedIsSet &&
       (m_resumeEnergyEstimated != c_classObject.m_resumeEnergyEstimated))) {
    return false;
  }
  if (m_energyUnitIsSet != c_classObject.m_energyUnitIsSet) {
    return false;
  }
  if (m_resumeCostEstimatedIsSet != c_classObject.m_resumeCostEstimatedIsSet ||
      (m_resumeCostEstimatedIsSet &&
       (m_resumeCostEstimated != c_classObject.m_resumeCostEstimated))) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet) {
    return false;
  }

  return true;
}

bool OperatingConstraintsResumeImplicationDataElements::operator!=(
    const OperatingConstraintsResumeImplicationDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsResumeImplicationDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_resumeEnergyEstimatedIsSet &&
         !m_energyUnitIsSet && !m_resumeCostEstimatedIsSet && !m_currencyIsSet;
}

DataElements::Type
OperatingConstraintsResumeImplicationDataElements::getDataType() const {
  return DataElements::Type::
      OPERATING_CONSTRAINTS_RESUME_IMPLICATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
OperatingConstraintsResumeImplicationDataElements::clone() const {
  return std::make_shared<OperatingConstraintsResumeImplicationDataElements>(
      *this);
}

void OperatingConstraintsResumeImplicationDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void OperatingConstraintsResumeImplicationDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsResumeImplicationDataElements::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

void OperatingConstraintsResumeImplicationDataElements::
    setResumeEnergyEstimated(
        const ScaledNumberElements &resumeEnergyEstimated) {
  m_resumeEnergyEstimated = resumeEnergyEstimated;
  m_resumeEnergyEstimatedIsSet = true;
}

const ScaledNumberElements &
OperatingConstraintsResumeImplicationDataElements::getResumeEnergyEstimated()
    const {
  return m_resumeEnergyEstimated;
}

void OperatingConstraintsResumeImplicationDataElements::
    cleanResumeEnergyEstimated() {
  m_resumeEnergyEstimated = ScaledNumberElements();
  m_resumeEnergyEstimatedIsSet = false;
}

bool OperatingConstraintsResumeImplicationDataElements::
    getResumeEnergyEstimatedIsSet() const {
  return m_resumeEnergyEstimatedIsSet;
}

void OperatingConstraintsResumeImplicationDataElements::setEnergyUnit() {
  m_energyUnitIsSet = true;
}

void OperatingConstraintsResumeImplicationDataElements::cleanEnergyUnit() {
  m_energyUnitIsSet = false;
}

bool OperatingConstraintsResumeImplicationDataElements::getEnergyUnitIsSet()
    const {
  return m_energyUnitIsSet;
}

void OperatingConstraintsResumeImplicationDataElements::setResumeCostEstimated(
    const ScaledNumberElements &resumeCostEstimated) {
  m_resumeCostEstimated = resumeCostEstimated;
  m_resumeCostEstimatedIsSet = true;
}

const ScaledNumberElements &
OperatingConstraintsResumeImplicationDataElements::getResumeCostEstimated()
    const {
  return m_resumeCostEstimated;
}

void OperatingConstraintsResumeImplicationDataElements::
    cleanResumeCostEstimated() {
  m_resumeCostEstimated = ScaledNumberElements();
  m_resumeCostEstimatedIsSet = false;
}

bool OperatingConstraintsResumeImplicationDataElements::
    getResumeCostEstimatedIsSet() const {
  return m_resumeCostEstimatedIsSet;
}

void OperatingConstraintsResumeImplicationDataElements::setCurrency() {
  m_currencyIsSet = true;
}

void OperatingConstraintsResumeImplicationDataElements::cleanCurrency() {
  m_currencyIsSet = false;
}

bool OperatingConstraintsResumeImplicationDataElements::getCurrencyIsSet()
    const {
  return m_currencyIsSet;
}

bool OperatingConstraintsResumeImplicationDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "resumeEnergyEstimated", "energyUnit",
                   "resumeCostEstimated", "currency"})) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "resumeEnergyEstimated",
                                   &m_resumeEnergyEstimated)) {
      m_resumeEnergyEstimatedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "energyUnit")) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "currency")) {
      m_currencyIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsResumeImplicationDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_resumeEnergyEstimatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("resumeEnergyEstimated",
                                           m_resumeEnergyEstimated);
  }
  if (m_energyUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("energyUnit");
  }
  if (m_resumeCostEstimatedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("resumeCostEstimated",
                                           m_resumeCostEstimated);
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("currency");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram