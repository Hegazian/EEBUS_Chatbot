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

#include <keo_datagram/supplycondition/SupplyConditionDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionDescriptionDataElements::SupplyConditionDescriptionDataElements()
    : DataElements(), m_conditionIdIsSet(false), m_commodityTypeIsSet(false),
      m_positiveEnergyDirectionIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool SupplyConditionDescriptionDataElements::
operator==(const SupplyConditionDescriptionDataElements &c_classObject) const {
  if (m_conditionIdIsSet != c_classObject.m_conditionIdIsSet) {
    return false;
  }
  if (m_commodityTypeIsSet != c_classObject.m_commodityTypeIsSet) {
    return false;
  }
  if (m_positiveEnergyDirectionIsSet !=
      c_classObject.m_positiveEnergyDirectionIsSet) {
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

bool SupplyConditionDescriptionDataElements::
operator!=(const SupplyConditionDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionDescriptionDataElements::isEmpty() const {
  return !m_conditionIdIsSet && !m_commodityTypeIsSet &&
         !m_positiveEnergyDirectionIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

DataElements::Type SupplyConditionDescriptionDataElements::getDataType() const {
  return DataElements::Type::SUPPLY_CONDITION_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SupplyConditionDescriptionDataElements::clone() const {
  return std::make_shared<SupplyConditionDescriptionDataElements>(*this);
}

void SupplyConditionDescriptionDataElements::setConditionId() {
  m_conditionIdIsSet = true;
}

void SupplyConditionDescriptionDataElements::cleanConditionId() {
  m_conditionIdIsSet = false;
}

bool SupplyConditionDescriptionDataElements::getConditionIdIsSet() const {
  return m_conditionIdIsSet;
}

void SupplyConditionDescriptionDataElements::setCommodityType() {
  m_commodityTypeIsSet = true;
}

void SupplyConditionDescriptionDataElements::cleanCommodityType() {
  m_commodityTypeIsSet = false;
}

bool SupplyConditionDescriptionDataElements::getCommodityTypeIsSet() const {
  return m_commodityTypeIsSet;
}

void SupplyConditionDescriptionDataElements::setPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = true;
}

void SupplyConditionDescriptionDataElements::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = false;
}

bool SupplyConditionDescriptionDataElements::getPositiveEnergyDirectionIsSet()
    const {
  return m_positiveEnergyDirectionIsSet;
}

void SupplyConditionDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void SupplyConditionDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool SupplyConditionDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void SupplyConditionDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void SupplyConditionDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool SupplyConditionDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool SupplyConditionDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"conditionId", "commodityType", "positiveEnergyDirection",
                   "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "conditionId")) {
      m_conditionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "commodityType")) {
      m_commodityTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "positiveEnergyDirection")) {
      m_positiveEnergyDirectionIsSet = true;
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

std::string SupplyConditionDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("conditionId");
  }
  if (m_commodityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("commodityType");
  }
  if (m_positiveEnergyDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("positiveEnergyDirection");
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