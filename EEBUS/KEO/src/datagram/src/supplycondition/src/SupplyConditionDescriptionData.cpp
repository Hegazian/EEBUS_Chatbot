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

#include <keo_datagram/supplycondition/SupplyConditionDescriptionData.h>

#include <keo_datagram/supplycondition/SupplyConditionDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionDescriptionData::SupplyConditionDescriptionData()
    : m_conditionIdIsSet(false), m_conditionId(0), m_commodityTypeIsSet(false),
      m_commodityType(CommodityType()), m_positiveEnergyDirectionIsSet(false),
      m_positiveEnergyDirection(EnergyDirection()), m_labelIsSet(false),
      m_label(""), m_descriptionIsSet(false), m_description("")

{}

bool SupplyConditionDescriptionData::
operator==(const SupplyConditionDescriptionData &c_classObject) const {
  if (m_conditionIdIsSet != c_classObject.m_conditionIdIsSet ||
      (m_conditionIdIsSet && (m_conditionId != c_classObject.m_conditionId))) {
    return false;
  }
  if (m_commodityTypeIsSet != c_classObject.m_commodityTypeIsSet ||
      (m_commodityTypeIsSet &&
       (m_commodityType != c_classObject.m_commodityType))) {
    return false;
  }
  if (m_positiveEnergyDirectionIsSet !=
          c_classObject.m_positiveEnergyDirectionIsSet ||
      (m_positiveEnergyDirectionIsSet &&
       (m_positiveEnergyDirection !=
        c_classObject.m_positiveEnergyDirection))) {
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

bool SupplyConditionDescriptionData::
operator!=(const SupplyConditionDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionDescriptionData::isEmpty() const {
  return !m_conditionIdIsSet && !m_commodityTypeIsSet &&
         !m_positiveEnergyDirectionIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

void SupplyConditionDescriptionData::setConditionId(
    const xs_unsignedInt &conditionId) {
  m_conditionId = conditionId;
  m_conditionIdIsSet = true;
}

const xs_unsignedInt &SupplyConditionDescriptionData::getConditionId() const {
  return m_conditionId;
}

void SupplyConditionDescriptionData::cleanConditionId() {
  m_conditionId = 0;
  m_conditionIdIsSet = false;
}

bool SupplyConditionDescriptionData::getConditionIdIsSet() const {
  return m_conditionIdIsSet;
}

void SupplyConditionDescriptionData::setCommodityType(
    const CommodityType &commodityType) {
  m_commodityType = commodityType;
  m_commodityTypeIsSet = true;
}

const CommodityType &SupplyConditionDescriptionData::getCommodityType() const {
  return m_commodityType;
}

void SupplyConditionDescriptionData::cleanCommodityType() {
  m_commodityType = CommodityType();
  m_commodityTypeIsSet = false;
}

bool SupplyConditionDescriptionData::getCommodityTypeIsSet() const {
  return m_commodityTypeIsSet;
}

void SupplyConditionDescriptionData::setPositiveEnergyDirection(
    const EnergyDirection &positiveEnergyDirection) {
  m_positiveEnergyDirection = positiveEnergyDirection;
  m_positiveEnergyDirectionIsSet = true;
}

const EnergyDirection &
SupplyConditionDescriptionData::getPositiveEnergyDirection() const {
  return m_positiveEnergyDirection;
}

void SupplyConditionDescriptionData::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirection = EnergyDirection();
  m_positiveEnergyDirectionIsSet = false;
}

bool SupplyConditionDescriptionData::getPositiveEnergyDirectionIsSet() const {
  return m_positiveEnergyDirectionIsSet;
}

void SupplyConditionDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &SupplyConditionDescriptionData::getLabel() const {
  return m_label;
}

void SupplyConditionDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool SupplyConditionDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void SupplyConditionDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &SupplyConditionDescriptionData::getDescription() const {
  return m_description;
}

void SupplyConditionDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool SupplyConditionDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

SupplyConditionDescriptionData SupplyConditionDescriptionData::reduce(
    const SupplyConditionDescriptionDataElements &elements) const {
  SupplyConditionDescriptionData dataOut;
  if (getConditionIdIsSet() && elements.getConditionIdIsSet()) {
    dataOut.setConditionId(getConditionId());
  }
  if (getCommodityTypeIsSet() && elements.getCommodityTypeIsSet()) {
    dataOut.setCommodityType(getCommodityType());
  }
  if (getPositiveEnergyDirectionIsSet() &&
      elements.getPositiveEnergyDirectionIsSet()) {
    dataOut.setPositiveEnergyDirection(getPositiveEnergyDirection());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool SupplyConditionDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"conditionId", "commodityType", "positiveEnergyDirection",
                   "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "conditionId", &m_conditionId)) {
      m_conditionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "commodityType", &m_commodityType)) {
      m_commodityTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "positiveEnergyDirection",
                                   &m_positiveEnergyDirection)) {
      m_positiveEnergyDirectionIsSet = true;
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

std::string SupplyConditionDescriptionData::toJson() const {
  std::string result = "[";
  if (m_conditionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("conditionId", m_conditionId);
  }
  if (m_commodityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("commodityType", m_commodityType);
  }
  if (m_positiveEnergyDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("positiveEnergyDirection",
                                           m_positiveEnergyDirection);
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