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

#include <keo_datagram/incentivetable/IncentiveDescriptionData.h>

#include <keo_datagram/incentivetable/IncentiveDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveDescriptionData::IncentiveDescriptionData()
    : m_incentiveIdIsSet(false), m_incentiveId(0), m_incentiveTypeIsSet(false),
      m_incentiveType(IncentiveType()), m_incentivePriorityIsSet(false),
      m_incentivePriority(0), m_currencyIsSet(false), m_currency(Currency()),
      m_unitIsSet(false), m_unit(UnitOfMeasurement()), m_labelIsSet(false),
      m_label(""), m_descriptionIsSet(false), m_description("")

{}

bool IncentiveDescriptionData::
operator==(const IncentiveDescriptionData &c_classObject) const {
  if (m_incentiveIdIsSet != c_classObject.m_incentiveIdIsSet ||
      (m_incentiveIdIsSet && (m_incentiveId != c_classObject.m_incentiveId))) {
    return false;
  }
  if (m_incentiveTypeIsSet != c_classObject.m_incentiveTypeIsSet ||
      (m_incentiveTypeIsSet &&
       (m_incentiveType != c_classObject.m_incentiveType))) {
    return false;
  }
  if (m_incentivePriorityIsSet != c_classObject.m_incentivePriorityIsSet ||
      (m_incentivePriorityIsSet &&
       (m_incentivePriority != c_classObject.m_incentivePriority))) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet ||
      (m_currencyIsSet && (m_currency != c_classObject.m_currency))) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool IncentiveDescriptionData::
operator!=(const IncentiveDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveDescriptionData::isEmpty() const {
  return !m_incentiveIdIsSet && !m_incentiveTypeIsSet &&
         !m_incentivePriorityIsSet && !m_currencyIsSet && !m_unitIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

void IncentiveDescriptionData::setIncentiveId(
    const xs_unsignedInt &incentiveId) {
  m_incentiveId = incentiveId;
  m_incentiveIdIsSet = true;
}

const xs_unsignedInt &IncentiveDescriptionData::getIncentiveId() const {
  return m_incentiveId;
}

void IncentiveDescriptionData::cleanIncentiveId() {
  m_incentiveId = 0;
  m_incentiveIdIsSet = false;
}

bool IncentiveDescriptionData::getIncentiveIdIsSet() const {
  return m_incentiveIdIsSet;
}

void IncentiveDescriptionData::setIncentiveType(
    const IncentiveType &incentiveType) {
  m_incentiveType = incentiveType;
  m_incentiveTypeIsSet = true;
}

const IncentiveType &IncentiveDescriptionData::getIncentiveType() const {
  return m_incentiveType;
}

void IncentiveDescriptionData::cleanIncentiveType() {
  m_incentiveType = IncentiveType();
  m_incentiveTypeIsSet = false;
}

bool IncentiveDescriptionData::getIncentiveTypeIsSet() const {
  return m_incentiveTypeIsSet;
}

void IncentiveDescriptionData::setIncentivePriority(
    const xs_unsignedInt &incentivePriority) {
  m_incentivePriority = incentivePriority;
  m_incentivePriorityIsSet = true;
}

const xs_unsignedInt &IncentiveDescriptionData::getIncentivePriority() const {
  return m_incentivePriority;
}

void IncentiveDescriptionData::cleanIncentivePriority() {
  m_incentivePriority = 0;
  m_incentivePriorityIsSet = false;
}

bool IncentiveDescriptionData::getIncentivePriorityIsSet() const {
  return m_incentivePriorityIsSet;
}

void IncentiveDescriptionData::setCurrency(const Currency &currency) {
  m_currency = currency;
  m_currencyIsSet = true;
}

const Currency &IncentiveDescriptionData::getCurrency() const {
  return m_currency;
}

void IncentiveDescriptionData::cleanCurrency() {
  m_currency = Currency();
  m_currencyIsSet = false;
}

bool IncentiveDescriptionData::getCurrencyIsSet() const {
  return m_currencyIsSet;
}

void IncentiveDescriptionData::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &IncentiveDescriptionData::getUnit() const {
  return m_unit;
}

void IncentiveDescriptionData::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool IncentiveDescriptionData::getUnitIsSet() const { return m_unitIsSet; }

void IncentiveDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &IncentiveDescriptionData::getLabel() const { return m_label; }

void IncentiveDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool IncentiveDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void IncentiveDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &IncentiveDescriptionData::getDescription() const {
  return m_description;
}

void IncentiveDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool IncentiveDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

IncentiveDescriptionData IncentiveDescriptionData::reduce(
    const IncentiveDescriptionDataElements &elements) const {
  IncentiveDescriptionData dataOut;
  if (getIncentiveIdIsSet() && elements.getIncentiveIdIsSet()) {
    dataOut.setIncentiveId(getIncentiveId());
  }
  if (getIncentiveTypeIsSet() && elements.getIncentiveTypeIsSet()) {
    dataOut.setIncentiveType(getIncentiveType());
  }
  if (getIncentivePriorityIsSet() && elements.getIncentivePriorityIsSet()) {
    dataOut.setIncentivePriority(getIncentivePriority());
  }
  if (getCurrencyIsSet() && elements.getCurrencyIsSet()) {
    dataOut.setCurrency(getCurrency());
  }
  if (getUnitIsSet() && elements.getUnitIsSet()) {
    dataOut.setUnit(getUnit());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool IncentiveDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveId", "incentiveType", "incentivePriority",
                   "currency", "unit", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveId", &m_incentiveId)) {
      m_incentiveIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveType", &m_incentiveType)) {
      m_incentiveTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentivePriority", &m_incentivePriority)) {
      m_incentivePriorityIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "currency", &m_currency)) {
      m_currencyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "unit", &m_unit)) {
      m_unitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveDescriptionData::toJson() const {
  std::string result = "[";
  if (m_incentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveId", m_incentiveId);
  }
  if (m_incentiveTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveType", m_incentiveType);
  }
  if (m_incentivePriorityIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("incentivePriority", m_incentivePriority);
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("currency", m_currency);
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram