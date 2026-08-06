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

#include <keo_datagram/core/CommodityDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

CommodityDataElements::CommodityDataElements()
    : DataElements(), m_commodityIdIsSet(false), m_commodityTypeIsSet(false),
      m_positiveEnergyDirectionIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool CommodityDataElements::
operator==(const CommodityDataElements &c_classObject) const {
  if (m_commodityIdIsSet != c_classObject.m_commodityIdIsSet) {
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

bool CommodityDataElements::
operator!=(const CommodityDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool CommodityDataElements::isEmpty() const {
  return !m_commodityIdIsSet && !m_commodityTypeIsSet &&
         !m_positiveEnergyDirectionIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

DataElements::Type CommodityDataElements::getDataType() const {
  return DataElements::Type::COMMODITY_DATA_ELEMENTS_TYPE;
}

DataElementsPtr CommodityDataElements::clone() const {
  return std::make_shared<CommodityDataElements>(*this);
}

void CommodityDataElements::setCommodityId() { m_commodityIdIsSet = true; }

void CommodityDataElements::cleanCommodityId() { m_commodityIdIsSet = false; }

bool CommodityDataElements::getCommodityIdIsSet() const {
  return m_commodityIdIsSet;
}

void CommodityDataElements::setCommodityType() { m_commodityTypeIsSet = true; }

void CommodityDataElements::cleanCommodityType() {
  m_commodityTypeIsSet = false;
}

bool CommodityDataElements::getCommodityTypeIsSet() const {
  return m_commodityTypeIsSet;
}

void CommodityDataElements::setPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = true;
}

void CommodityDataElements::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = false;
}

bool CommodityDataElements::getPositiveEnergyDirectionIsSet() const {
  return m_positiveEnergyDirectionIsSet;
}

void CommodityDataElements::setLabel() { m_labelIsSet = true; }

void CommodityDataElements::cleanLabel() { m_labelIsSet = false; }

bool CommodityDataElements::getLabelIsSet() const { return m_labelIsSet; }

void CommodityDataElements::setDescription() { m_descriptionIsSet = true; }

void CommodityDataElements::cleanDescription() { m_descriptionIsSet = false; }

bool CommodityDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool CommodityDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"commodityId", "commodityType", "positiveEnergyDirection",
                   "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "commodityId")) {
      m_commodityIdIsSet = true;
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

std::string CommodityDataElements::toJson() const {
  std::string result = "[";
  if (m_commodityIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("commodityId");
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