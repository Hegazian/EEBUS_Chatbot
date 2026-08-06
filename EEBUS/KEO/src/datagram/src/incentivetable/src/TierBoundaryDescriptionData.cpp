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

#include <keo_datagram/incentivetable/TierBoundaryDescriptionData.h>

#include <keo_datagram/incentivetable/TierBoundaryDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierBoundaryDescriptionData::TierBoundaryDescriptionData()
    : m_boundaryIdIsSet(false), m_boundaryId(0), m_boundaryTypeIsSet(false),
      m_boundaryType(TierBoundaryType()), m_validForTierIdIsSet(false),
      m_validForTierId(0), m_switchToTierIdWhenLowerIsSet(false),
      m_switchToTierIdWhenLower(0), m_switchToTierIdWhenHigherIsSet(false),
      m_switchToTierIdWhenHigher(0), m_boundaryUnitIsSet(false),
      m_boundaryUnit(UnitOfMeasurement()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool TierBoundaryDescriptionData::
operator==(const TierBoundaryDescriptionData &c_classObject) const {
  if (m_boundaryIdIsSet != c_classObject.m_boundaryIdIsSet ||
      (m_boundaryIdIsSet && (m_boundaryId != c_classObject.m_boundaryId))) {
    return false;
  }
  if (m_boundaryTypeIsSet != c_classObject.m_boundaryTypeIsSet ||
      (m_boundaryTypeIsSet &&
       (m_boundaryType != c_classObject.m_boundaryType))) {
    return false;
  }
  if (m_validForTierIdIsSet != c_classObject.m_validForTierIdIsSet ||
      (m_validForTierIdIsSet &&
       (m_validForTierId != c_classObject.m_validForTierId))) {
    return false;
  }
  if (m_switchToTierIdWhenLowerIsSet !=
          c_classObject.m_switchToTierIdWhenLowerIsSet ||
      (m_switchToTierIdWhenLowerIsSet &&
       (m_switchToTierIdWhenLower !=
        c_classObject.m_switchToTierIdWhenLower))) {
    return false;
  }
  if (m_switchToTierIdWhenHigherIsSet !=
          c_classObject.m_switchToTierIdWhenHigherIsSet ||
      (m_switchToTierIdWhenHigherIsSet &&
       (m_switchToTierIdWhenHigher !=
        c_classObject.m_switchToTierIdWhenHigher))) {
    return false;
  }
  if (m_boundaryUnitIsSet != c_classObject.m_boundaryUnitIsSet ||
      (m_boundaryUnitIsSet &&
       (m_boundaryUnit != c_classObject.m_boundaryUnit))) {
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

bool TierBoundaryDescriptionData::
operator!=(const TierBoundaryDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierBoundaryDescriptionData::isEmpty() const {
  return !m_boundaryIdIsSet && !m_boundaryTypeIsSet && !m_validForTierIdIsSet &&
         !m_switchToTierIdWhenLowerIsSet && !m_switchToTierIdWhenHigherIsSet &&
         !m_boundaryUnitIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

void TierBoundaryDescriptionData::setBoundaryId(
    const xs_unsignedInt &boundaryId) {
  m_boundaryId = boundaryId;
  m_boundaryIdIsSet = true;
}

const xs_unsignedInt &TierBoundaryDescriptionData::getBoundaryId() const {
  return m_boundaryId;
}

void TierBoundaryDescriptionData::cleanBoundaryId() {
  m_boundaryId = 0;
  m_boundaryIdIsSet = false;
}

bool TierBoundaryDescriptionData::getBoundaryIdIsSet() const {
  return m_boundaryIdIsSet;
}

void TierBoundaryDescriptionData::setBoundaryType(
    const TierBoundaryType &boundaryType) {
  m_boundaryType = boundaryType;
  m_boundaryTypeIsSet = true;
}

const TierBoundaryType &TierBoundaryDescriptionData::getBoundaryType() const {
  return m_boundaryType;
}

void TierBoundaryDescriptionData::cleanBoundaryType() {
  m_boundaryType = TierBoundaryType();
  m_boundaryTypeIsSet = false;
}

bool TierBoundaryDescriptionData::getBoundaryTypeIsSet() const {
  return m_boundaryTypeIsSet;
}

void TierBoundaryDescriptionData::setValidForTierId(
    const xs_unsignedInt &validForTierId) {
  m_validForTierId = validForTierId;
  m_validForTierIdIsSet = true;
}

const xs_unsignedInt &TierBoundaryDescriptionData::getValidForTierId() const {
  return m_validForTierId;
}

void TierBoundaryDescriptionData::cleanValidForTierId() {
  m_validForTierId = 0;
  m_validForTierIdIsSet = false;
}

bool TierBoundaryDescriptionData::getValidForTierIdIsSet() const {
  return m_validForTierIdIsSet;
}

void TierBoundaryDescriptionData::setSwitchToTierIdWhenLower(
    const xs_unsignedInt &switchToTierIdWhenLower) {
  m_switchToTierIdWhenLower = switchToTierIdWhenLower;
  m_switchToTierIdWhenLowerIsSet = true;
}

const xs_unsignedInt &
TierBoundaryDescriptionData::getSwitchToTierIdWhenLower() const {
  return m_switchToTierIdWhenLower;
}

void TierBoundaryDescriptionData::cleanSwitchToTierIdWhenLower() {
  m_switchToTierIdWhenLower = 0;
  m_switchToTierIdWhenLowerIsSet = false;
}

bool TierBoundaryDescriptionData::getSwitchToTierIdWhenLowerIsSet() const {
  return m_switchToTierIdWhenLowerIsSet;
}

void TierBoundaryDescriptionData::setSwitchToTierIdWhenHigher(
    const xs_unsignedInt &switchToTierIdWhenHigher) {
  m_switchToTierIdWhenHigher = switchToTierIdWhenHigher;
  m_switchToTierIdWhenHigherIsSet = true;
}

const xs_unsignedInt &
TierBoundaryDescriptionData::getSwitchToTierIdWhenHigher() const {
  return m_switchToTierIdWhenHigher;
}

void TierBoundaryDescriptionData::cleanSwitchToTierIdWhenHigher() {
  m_switchToTierIdWhenHigher = 0;
  m_switchToTierIdWhenHigherIsSet = false;
}

bool TierBoundaryDescriptionData::getSwitchToTierIdWhenHigherIsSet() const {
  return m_switchToTierIdWhenHigherIsSet;
}

void TierBoundaryDescriptionData::setBoundaryUnit(
    const UnitOfMeasurement &boundaryUnit) {
  m_boundaryUnit = boundaryUnit;
  m_boundaryUnitIsSet = true;
}

const UnitOfMeasurement &TierBoundaryDescriptionData::getBoundaryUnit() const {
  return m_boundaryUnit;
}

void TierBoundaryDescriptionData::cleanBoundaryUnit() {
  m_boundaryUnit = UnitOfMeasurement();
  m_boundaryUnitIsSet = false;
}

bool TierBoundaryDescriptionData::getBoundaryUnitIsSet() const {
  return m_boundaryUnitIsSet;
}

void TierBoundaryDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &TierBoundaryDescriptionData::getLabel() const {
  return m_label;
}

void TierBoundaryDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool TierBoundaryDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void TierBoundaryDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &TierBoundaryDescriptionData::getDescription() const {
  return m_description;
}

void TierBoundaryDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool TierBoundaryDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

TierBoundaryDescriptionData TierBoundaryDescriptionData::reduce(
    const TierBoundaryDescriptionDataElements &elements) const {
  TierBoundaryDescriptionData dataOut;
  if (getBoundaryIdIsSet() && elements.getBoundaryIdIsSet()) {
    dataOut.setBoundaryId(getBoundaryId());
  }
  if (getBoundaryTypeIsSet() && elements.getBoundaryTypeIsSet()) {
    dataOut.setBoundaryType(getBoundaryType());
  }
  if (getValidForTierIdIsSet() && elements.getValidForTierIdIsSet()) {
    dataOut.setValidForTierId(getValidForTierId());
  }
  if (getSwitchToTierIdWhenLowerIsSet() &&
      elements.getSwitchToTierIdWhenLowerIsSet()) {
    dataOut.setSwitchToTierIdWhenLower(getSwitchToTierIdWhenLower());
  }
  if (getSwitchToTierIdWhenHigherIsSet() &&
      elements.getSwitchToTierIdWhenHigherIsSet()) {
    dataOut.setSwitchToTierIdWhenHigher(getSwitchToTierIdWhenHigher());
  }
  if (getBoundaryUnitIsSet() && elements.getBoundaryUnitIsSet()) {
    dataOut.setBoundaryUnit(getBoundaryUnit());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool TierBoundaryDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"boundaryId", "boundaryType", "validForTierId",
                   "switchToTierIdWhenLower", "switchToTierIdWhenHigher",
                   "boundaryUnit", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryId", &m_boundaryId)) {
      m_boundaryIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryType", &m_boundaryType)) {
      m_boundaryTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "validForTierId", &m_validForTierId)) {
      m_validForTierIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "switchToTierIdWhenLower",
                                   &m_switchToTierIdWhenLower)) {
      m_switchToTierIdWhenLowerIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "switchToTierIdWhenHigher",
                                   &m_switchToTierIdWhenHigher)) {
      m_switchToTierIdWhenHigherIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryUnit", &m_boundaryUnit)) {
      m_boundaryUnitIsSet = true;
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

std::string TierBoundaryDescriptionData::toJson() const {
  std::string result = "[";
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryId", m_boundaryId);
  }
  if (m_boundaryTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryType", m_boundaryType);
  }
  if (m_validForTierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("validForTierId", m_validForTierId);
  }
  if (m_switchToTierIdWhenLowerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("switchToTierIdWhenLower",
                                           m_switchToTierIdWhenLower);
  }
  if (m_switchToTierIdWhenHigherIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("switchToTierIdWhenHigher",
                                           m_switchToTierIdWhenHigher);
  }
  if (m_boundaryUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryUnit", m_boundaryUnit);
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