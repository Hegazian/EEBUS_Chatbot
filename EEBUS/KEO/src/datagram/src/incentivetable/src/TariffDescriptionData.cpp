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

#include <keo_datagram/incentivetable/TariffDescriptionData.h>

#include <keo_datagram/incentivetable/TariffDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffDescriptionData::TariffDescriptionData()
    : m_tariffIdIsSet(false), m_tariffId(0), m_commodityIdIsSet(false),
      m_commodityId(0), m_measurementIdIsSet(false), m_measurementId(0),
      m_tariffWriteableIsSet(false), m_tariffWriteable(false),
      m_updateRequiredIsSet(false), m_updateRequired(false),
      m_scopeTypeIsSet(false), m_scopeType(ScopeType()), m_labelIsSet(false),
      m_label(""), m_descriptionIsSet(false), m_description(""),
      m_slotIdSupportIsSet(false), m_slotIdSupport(false)

{}

bool TariffDescriptionData::
operator==(const TariffDescriptionData &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet ||
      (m_tariffIdIsSet && (m_tariffId != c_classObject.m_tariffId))) {
    return false;
  }
  if (m_commodityIdIsSet != c_classObject.m_commodityIdIsSet ||
      (m_commodityIdIsSet && (m_commodityId != c_classObject.m_commodityId))) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_tariffWriteableIsSet != c_classObject.m_tariffWriteableIsSet ||
      (m_tariffWriteableIsSet &&
       (m_tariffWriteable != c_classObject.m_tariffWriteable))) {
    return false;
  }
  if (m_updateRequiredIsSet != c_classObject.m_updateRequiredIsSet ||
      (m_updateRequiredIsSet &&
       (m_updateRequired != c_classObject.m_updateRequired))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
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
  if (m_slotIdSupportIsSet != c_classObject.m_slotIdSupportIsSet ||
      (m_slotIdSupportIsSet &&
       (m_slotIdSupport != c_classObject.m_slotIdSupport))) {
    return false;
  }

  return true;
}

bool TariffDescriptionData::
operator!=(const TariffDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffDescriptionData::isEmpty() const {
  return !m_tariffIdIsSet && !m_commodityIdIsSet && !m_measurementIdIsSet &&
         !m_tariffWriteableIsSet && !m_updateRequiredIsSet &&
         !m_scopeTypeIsSet && !m_labelIsSet && !m_descriptionIsSet &&
         !m_slotIdSupportIsSet;
}

void TariffDescriptionData::setTariffId(const xs_unsignedInt &tariffId) {
  m_tariffId = tariffId;
  m_tariffIdIsSet = true;
}

const xs_unsignedInt &TariffDescriptionData::getTariffId() const {
  return m_tariffId;
}

void TariffDescriptionData::cleanTariffId() {
  m_tariffId = 0;
  m_tariffIdIsSet = false;
}

bool TariffDescriptionData::getTariffIdIsSet() const { return m_tariffIdIsSet; }

void TariffDescriptionData::setCommodityId(const xs_unsignedInt &commodityId) {
  m_commodityId = commodityId;
  m_commodityIdIsSet = true;
}

const xs_unsignedInt &TariffDescriptionData::getCommodityId() const {
  return m_commodityId;
}

void TariffDescriptionData::cleanCommodityId() {
  m_commodityId = 0;
  m_commodityIdIsSet = false;
}

bool TariffDescriptionData::getCommodityIdIsSet() const {
  return m_commodityIdIsSet;
}

void TariffDescriptionData::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &TariffDescriptionData::getMeasurementId() const {
  return m_measurementId;
}

void TariffDescriptionData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool TariffDescriptionData::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void TariffDescriptionData::setTariffWriteable(
    const xs_boolean &tariffWriteable) {
  m_tariffWriteable = tariffWriteable;
  m_tariffWriteableIsSet = true;
}

const xs_boolean &TariffDescriptionData::getTariffWriteable() const {
  return m_tariffWriteable;
}

void TariffDescriptionData::cleanTariffWriteable() {
  m_tariffWriteable = false;
  m_tariffWriteableIsSet = false;
}

bool TariffDescriptionData::getTariffWriteableIsSet() const {
  return m_tariffWriteableIsSet;
}

void TariffDescriptionData::setUpdateRequired(
    const xs_boolean &updateRequired) {
  m_updateRequired = updateRequired;
  m_updateRequiredIsSet = true;
}

const xs_boolean &TariffDescriptionData::getUpdateRequired() const {
  return m_updateRequired;
}

void TariffDescriptionData::cleanUpdateRequired() {
  m_updateRequired = false;
  m_updateRequiredIsSet = false;
}

bool TariffDescriptionData::getUpdateRequiredIsSet() const {
  return m_updateRequiredIsSet;
}

void TariffDescriptionData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &TariffDescriptionData::getScopeType() const {
  return m_scopeType;
}

void TariffDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool TariffDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void TariffDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &TariffDescriptionData::getLabel() const { return m_label; }

void TariffDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool TariffDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void TariffDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &TariffDescriptionData::getDescription() const {
  return m_description;
}

void TariffDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool TariffDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void TariffDescriptionData::setSlotIdSupport(const xs_boolean &slotIdSupport) {
  m_slotIdSupport = slotIdSupport;
  m_slotIdSupportIsSet = true;
}

const xs_boolean &TariffDescriptionData::getSlotIdSupport() const {
  return m_slotIdSupport;
}

void TariffDescriptionData::cleanSlotIdSupport() {
  m_slotIdSupport = false;
  m_slotIdSupportIsSet = false;
}

bool TariffDescriptionData::getSlotIdSupportIsSet() const {
  return m_slotIdSupportIsSet;
}

TariffDescriptionData TariffDescriptionData::reduce(
    const TariffDescriptionDataElements &elements) const {
  TariffDescriptionData dataOut;
  if (getTariffIdIsSet() && elements.getTariffIdIsSet()) {
    dataOut.setTariffId(getTariffId());
  }
  if (getCommodityIdIsSet() && elements.getCommodityIdIsSet()) {
    dataOut.setCommodityId(getCommodityId());
  }
  if (getMeasurementIdIsSet() && elements.getMeasurementIdIsSet()) {
    dataOut.setMeasurementId(getMeasurementId());
  }
  if (getTariffWriteableIsSet() && elements.getTariffWriteableIsSet()) {
    dataOut.setTariffWriteable(getTariffWriteable());
  }
  if (getUpdateRequiredIsSet() && elements.getUpdateRequiredIsSet()) {
    dataOut.setUpdateRequired(getUpdateRequired());
  }
  if (getScopeTypeIsSet() && elements.getScopeTypeIsSet()) {
    dataOut.setScopeType(getScopeType());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  if (getSlotIdSupportIsSet() && elements.getSlotIdSupportIsSet()) {
    dataOut.setSlotIdSupport(getSlotIdSupport());
  }
  return dataOut;
}

bool TariffDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tariffId", "commodityId", "measurementId",
                   "tariffWriteable", "updateRequired", "scopeType", "label",
                   "description", "slotIdSupport"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariffId", &m_tariffId)) {
      m_tariffIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "commodityId", &m_commodityId)) {
      m_commodityIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariffWriteable", &m_tariffWriteable)) {
      m_tariffWriteableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "updateRequired", &m_updateRequired)) {
      m_updateRequiredIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
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
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "slotIdSupport", &m_slotIdSupport)) {
      m_slotIdSupportIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffDescriptionData::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariffId", m_tariffId);
  }
  if (m_commodityIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("commodityId", m_commodityId);
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_tariffWriteableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("tariffWriteable", m_tariffWriteable);
  }
  if (m_updateRequiredIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("updateRequired", m_updateRequired);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  if (m_slotIdSupportIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("slotIdSupport", m_slotIdSupport);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram