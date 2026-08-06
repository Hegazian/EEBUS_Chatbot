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

#include <keo_datagram/incentivetable/IncentiveDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveDescriptionDataElements::IncentiveDescriptionDataElements()
    : DataElements(), m_incentiveIdIsSet(false), m_incentiveTypeIsSet(false),
      m_incentivePriorityIsSet(false), m_currencyIsSet(false),
      m_unitIsSet(false), m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool IncentiveDescriptionDataElements::
operator==(const IncentiveDescriptionDataElements &c_classObject) const {
  if (m_incentiveIdIsSet != c_classObject.m_incentiveIdIsSet) {
    return false;
  }
  if (m_incentiveTypeIsSet != c_classObject.m_incentiveTypeIsSet) {
    return false;
  }
  if (m_incentivePriorityIsSet != c_classObject.m_incentivePriorityIsSet) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool IncentiveDescriptionDataElements::
operator!=(const IncentiveDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveDescriptionDataElements::isEmpty() const {
  return !m_incentiveIdIsSet && !m_incentiveTypeIsSet &&
         !m_incentivePriorityIsSet && !m_currencyIsSet && !m_unitIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type IncentiveDescriptionDataElements::getDataType() const {
  return DataElements::Type::INCENTIVE_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr IncentiveDescriptionDataElements::clone() const {
  return std::make_shared<IncentiveDescriptionDataElements>(*this);
}

void IncentiveDescriptionDataElements::setIncentiveId() {
  m_incentiveIdIsSet = true;
}

void IncentiveDescriptionDataElements::cleanIncentiveId() {
  m_incentiveIdIsSet = false;
}

bool IncentiveDescriptionDataElements::getIncentiveIdIsSet() const {
  return m_incentiveIdIsSet;
}

void IncentiveDescriptionDataElements::setIncentiveType() {
  m_incentiveTypeIsSet = true;
}

void IncentiveDescriptionDataElements::cleanIncentiveType() {
  m_incentiveTypeIsSet = false;
}

bool IncentiveDescriptionDataElements::getIncentiveTypeIsSet() const {
  return m_incentiveTypeIsSet;
}

void IncentiveDescriptionDataElements::setIncentivePriority() {
  m_incentivePriorityIsSet = true;
}

void IncentiveDescriptionDataElements::cleanIncentivePriority() {
  m_incentivePriorityIsSet = false;
}

bool IncentiveDescriptionDataElements::getIncentivePriorityIsSet() const {
  return m_incentivePriorityIsSet;
}

void IncentiveDescriptionDataElements::setCurrency() { m_currencyIsSet = true; }

void IncentiveDescriptionDataElements::cleanCurrency() {
  m_currencyIsSet = false;
}

bool IncentiveDescriptionDataElements::getCurrencyIsSet() const {
  return m_currencyIsSet;
}

void IncentiveDescriptionDataElements::setUnit() { m_unitIsSet = true; }

void IncentiveDescriptionDataElements::cleanUnit() { m_unitIsSet = false; }

bool IncentiveDescriptionDataElements::getUnitIsSet() const {
  return m_unitIsSet;
}

void IncentiveDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void IncentiveDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool IncentiveDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void IncentiveDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void IncentiveDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool IncentiveDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool IncentiveDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveId", "incentiveType", "incentivePriority",
                   "currency", "unit", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "incentiveId")) {
      m_incentiveIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "incentiveType")) {
      m_incentiveTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "incentivePriority")) {
      m_incentivePriorityIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "currency")) {
      m_currencyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "unit")) {
      m_unitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_incentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("incentiveId");
  }
  if (m_incentiveTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("incentiveType");
  }
  if (m_incentivePriorityIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("incentivePriority");
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("currency");
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("unit");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram