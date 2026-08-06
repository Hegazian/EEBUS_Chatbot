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

#include <keo_datagram/incentivetable/TariffDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffDescriptionDataElements::TariffDescriptionDataElements()
    : DataElements(), m_tariffIdIsSet(false), m_commodityIdIsSet(false),
      m_measurementIdIsSet(false), m_tariffWriteableIsSet(false),
      m_updateRequiredIsSet(false), m_scopeTypeIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false),
      m_slotIdSupportIsSet(false)

{}

bool TariffDescriptionDataElements::
operator==(const TariffDescriptionDataElements &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet) {
    return false;
  }
  if (m_commodityIdIsSet != c_classObject.m_commodityIdIsSet) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_tariffWriteableIsSet != c_classObject.m_tariffWriteableIsSet) {
    return false;
  }
  if (m_updateRequiredIsSet != c_classObject.m_updateRequiredIsSet) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }
  if (m_slotIdSupportIsSet != c_classObject.m_slotIdSupportIsSet) {
    return false;
  }

  return true;
}

bool TariffDescriptionDataElements::
operator!=(const TariffDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffDescriptionDataElements::isEmpty() const {
  return !m_tariffIdIsSet && !m_commodityIdIsSet && !m_measurementIdIsSet &&
         !m_tariffWriteableIsSet && !m_updateRequiredIsSet &&
         !m_scopeTypeIsSet && !m_labelIsSet && !m_descriptionIsSet &&
         !m_slotIdSupportIsSet;
}

DataElements::Type TariffDescriptionDataElements::getDataType() const {
  return DataElements::Type::TARIFF_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TariffDescriptionDataElements::clone() const {
  return std::make_shared<TariffDescriptionDataElements>(*this);
}

void TariffDescriptionDataElements::setTariffId() { m_tariffIdIsSet = true; }

void TariffDescriptionDataElements::cleanTariffId() { m_tariffIdIsSet = false; }

bool TariffDescriptionDataElements::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffDescriptionDataElements::setCommodityId() {
  m_commodityIdIsSet = true;
}

void TariffDescriptionDataElements::cleanCommodityId() {
  m_commodityIdIsSet = false;
}

bool TariffDescriptionDataElements::getCommodityIdIsSet() const {
  return m_commodityIdIsSet;
}

void TariffDescriptionDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void TariffDescriptionDataElements::cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool TariffDescriptionDataElements::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void TariffDescriptionDataElements::setTariffWriteable() {
  m_tariffWriteableIsSet = true;
}

void TariffDescriptionDataElements::cleanTariffWriteable() {
  m_tariffWriteableIsSet = false;
}

bool TariffDescriptionDataElements::getTariffWriteableIsSet() const {
  return m_tariffWriteableIsSet;
}

void TariffDescriptionDataElements::setUpdateRequired() {
  m_updateRequiredIsSet = true;
}

void TariffDescriptionDataElements::cleanUpdateRequired() {
  m_updateRequiredIsSet = false;
}

bool TariffDescriptionDataElements::getUpdateRequiredIsSet() const {
  return m_updateRequiredIsSet;
}

void TariffDescriptionDataElements::setScopeType() { m_scopeTypeIsSet = true; }

void TariffDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool TariffDescriptionDataElements::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void TariffDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void TariffDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool TariffDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void TariffDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void TariffDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool TariffDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void TariffDescriptionDataElements::setSlotIdSupport() {
  m_slotIdSupportIsSet = true;
}

void TariffDescriptionDataElements::cleanSlotIdSupport() {
  m_slotIdSupportIsSet = false;
}

bool TariffDescriptionDataElements::getSlotIdSupportIsSet() const {
  return m_slotIdSupportIsSet;
}

bool TariffDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tariffId", "commodityId", "measurementId",
                   "tariffWriteable", "updateRequired", "scopeType", "label",
                   "description", "slotIdSupport"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tariffId")) {
      m_tariffIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "commodityId")) {
      m_commodityIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "measurementId")) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tariffWriteable")) {
      m_tariffWriteableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "updateRequired")) {
      m_updateRequiredIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scopeType")) {
      m_scopeTypeIsSet = true;
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
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "slotIdSupport")) {
      m_slotIdSupportIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tariffId");
  }
  if (m_commodityIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("commodityId");
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_tariffWriteableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tariffWriteable");
  }
  if (m_updateRequiredIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("updateRequired");
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scopeType");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  if (m_slotIdSupportIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("slotIdSupport");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram