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

#include <keo_datagram/incentivetable/TierBoundaryDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierBoundaryDescriptionDataElements::TierBoundaryDescriptionDataElements()
    : DataElements(), m_boundaryIdIsSet(false), m_boundaryTypeIsSet(false),
      m_validForTierIdIsSet(false), m_switchToTierIdWhenLowerIsSet(false),
      m_switchToTierIdWhenHigherIsSet(false), m_boundaryUnitIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool TierBoundaryDescriptionDataElements::
operator==(const TierBoundaryDescriptionDataElements &c_classObject) const {
  if (m_boundaryIdIsSet != c_classObject.m_boundaryIdIsSet) {
    return false;
  }
  if (m_boundaryTypeIsSet != c_classObject.m_boundaryTypeIsSet) {
    return false;
  }
  if (m_validForTierIdIsSet != c_classObject.m_validForTierIdIsSet) {
    return false;
  }
  if (m_switchToTierIdWhenLowerIsSet !=
      c_classObject.m_switchToTierIdWhenLowerIsSet) {
    return false;
  }
  if (m_switchToTierIdWhenHigherIsSet !=
      c_classObject.m_switchToTierIdWhenHigherIsSet) {
    return false;
  }
  if (m_boundaryUnitIsSet != c_classObject.m_boundaryUnitIsSet) {
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

bool TierBoundaryDescriptionDataElements::
operator!=(const TierBoundaryDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierBoundaryDescriptionDataElements::isEmpty() const {
  return !m_boundaryIdIsSet && !m_boundaryTypeIsSet && !m_validForTierIdIsSet &&
         !m_switchToTierIdWhenLowerIsSet && !m_switchToTierIdWhenHigherIsSet &&
         !m_boundaryUnitIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type TierBoundaryDescriptionDataElements::getDataType() const {
  return DataElements::Type::TIER_BOUNDARY_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TierBoundaryDescriptionDataElements::clone() const {
  return std::make_shared<TierBoundaryDescriptionDataElements>(*this);
}

void TierBoundaryDescriptionDataElements::setBoundaryId() {
  m_boundaryIdIsSet = true;
}

void TierBoundaryDescriptionDataElements::cleanBoundaryId() {
  m_boundaryIdIsSet = false;
}

bool TierBoundaryDescriptionDataElements::getBoundaryIdIsSet() const {
  return m_boundaryIdIsSet;
}

void TierBoundaryDescriptionDataElements::setBoundaryType() {
  m_boundaryTypeIsSet = true;
}

void TierBoundaryDescriptionDataElements::cleanBoundaryType() {
  m_boundaryTypeIsSet = false;
}

bool TierBoundaryDescriptionDataElements::getBoundaryTypeIsSet() const {
  return m_boundaryTypeIsSet;
}

void TierBoundaryDescriptionDataElements::setValidForTierId() {
  m_validForTierIdIsSet = true;
}

void TierBoundaryDescriptionDataElements::cleanValidForTierId() {
  m_validForTierIdIsSet = false;
}

bool TierBoundaryDescriptionDataElements::getValidForTierIdIsSet() const {
  return m_validForTierIdIsSet;
}

void TierBoundaryDescriptionDataElements::setSwitchToTierIdWhenLower() {
  m_switchToTierIdWhenLowerIsSet = true;
}

void TierBoundaryDescriptionDataElements::cleanSwitchToTierIdWhenLower() {
  m_switchToTierIdWhenLowerIsSet = false;
}

bool TierBoundaryDescriptionDataElements::getSwitchToTierIdWhenLowerIsSet()
    const {
  return m_switchToTierIdWhenLowerIsSet;
}

void TierBoundaryDescriptionDataElements::setSwitchToTierIdWhenHigher() {
  m_switchToTierIdWhenHigherIsSet = true;
}

void TierBoundaryDescriptionDataElements::cleanSwitchToTierIdWhenHigher() {
  m_switchToTierIdWhenHigherIsSet = false;
}

bool TierBoundaryDescriptionDataElements::getSwitchToTierIdWhenHigherIsSet()
    const {
  return m_switchToTierIdWhenHigherIsSet;
}

void TierBoundaryDescriptionDataElements::setBoundaryUnit() {
  m_boundaryUnitIsSet = true;
}

void TierBoundaryDescriptionDataElements::cleanBoundaryUnit() {
  m_boundaryUnitIsSet = false;
}

bool TierBoundaryDescriptionDataElements::getBoundaryUnitIsSet() const {
  return m_boundaryUnitIsSet;
}

void TierBoundaryDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void TierBoundaryDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool TierBoundaryDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void TierBoundaryDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void TierBoundaryDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool TierBoundaryDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool TierBoundaryDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"boundaryId", "boundaryType", "validForTierId",
                   "switchToTierIdWhenLower", "switchToTierIdWhenHigher",
                   "boundaryUnit", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "boundaryId")) {
      m_boundaryIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "boundaryType")) {
      m_boundaryTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "validForTierId")) {
      m_validForTierIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "switchToTierIdWhenLower")) {
      m_switchToTierIdWhenLowerIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "switchToTierIdWhenHigher")) {
      m_switchToTierIdWhenHigherIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "boundaryUnit")) {
      m_boundaryUnitIsSet = true;
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

std::string TierBoundaryDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("boundaryId");
  }
  if (m_boundaryTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("boundaryType");
  }
  if (m_validForTierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("validForTierId");
  }
  if (m_switchToTierIdWhenLowerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("switchToTierIdWhenLower");
  }
  if (m_switchToTierIdWhenHigherIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("switchToTierIdWhenHigher");
  }
  if (m_boundaryUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("boundaryUnit");
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