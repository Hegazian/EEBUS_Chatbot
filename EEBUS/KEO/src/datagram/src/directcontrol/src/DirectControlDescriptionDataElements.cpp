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

#include <keo_datagram/directcontrol/DirectControlDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DirectControlDescriptionDataElements::DirectControlDescriptionDataElements()
    : DataElements(), m_positiveEnergyDirectionIsSet(false),
      m_powerUnitIsSet(false), m_energyUnitIsSet(false)

{}

DirectControlDescriptionDataElements::DirectControlDescriptionDataElements(
    xs_boolean c_positiveEnergyDirectionIsSet, xs_boolean c_powerUnitIsSet,
    xs_boolean c_energyUnitIsSet)
    : DataElements(),
      m_positiveEnergyDirectionIsSet(c_positiveEnergyDirectionIsSet),
      m_powerUnitIsSet(c_powerUnitIsSet), m_energyUnitIsSet(c_energyUnitIsSet)

{}

bool DirectControlDescriptionDataElements::
operator==(const DirectControlDescriptionDataElements &c_classObject) const {
  if (m_positiveEnergyDirectionIsSet !=
      c_classObject.m_positiveEnergyDirectionIsSet) {
    return false;
  }
  if (m_powerUnitIsSet != c_classObject.m_powerUnitIsSet) {
    return false;
  }
  if (m_energyUnitIsSet != c_classObject.m_energyUnitIsSet) {
    return false;
  }

  return true;
}

bool DirectControlDescriptionDataElements::
operator!=(const DirectControlDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DirectControlDescriptionDataElements::isEmpty() const {
  return !m_positiveEnergyDirectionIsSet && !m_powerUnitIsSet &&
         !m_energyUnitIsSet;
}

DataElements::Type DirectControlDescriptionDataElements::getDataType() const {
  return DataElements::Type::DIRECT_CONTROL_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr DirectControlDescriptionDataElements::clone() const {
  return std::make_shared<DirectControlDescriptionDataElements>(*this);
}

void DirectControlDescriptionDataElements::setPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = true;
}

void DirectControlDescriptionDataElements::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = false;
}

bool DirectControlDescriptionDataElements::getPositiveEnergyDirectionIsSet()
    const {
  return m_positiveEnergyDirectionIsSet;
}

void DirectControlDescriptionDataElements::setPowerUnit() {
  m_powerUnitIsSet = true;
}

void DirectControlDescriptionDataElements::cleanPowerUnit() {
  m_powerUnitIsSet = false;
}

bool DirectControlDescriptionDataElements::getPowerUnitIsSet() const {
  return m_powerUnitIsSet;
}

void DirectControlDescriptionDataElements::setEnergyUnit() {
  m_energyUnitIsSet = true;
}

void DirectControlDescriptionDataElements::cleanEnergyUnit() {
  m_energyUnitIsSet = false;
}

bool DirectControlDescriptionDataElements::getEnergyUnitIsSet() const {
  return m_energyUnitIsSet;
}

bool DirectControlDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"positiveEnergyDirection", "powerUnit", "energyUnit"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "positiveEnergyDirection")) {
      m_positiveEnergyDirectionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "powerUnit")) {
      m_powerUnitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "energyUnit")) {
      m_energyUnitIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DirectControlDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_positiveEnergyDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("positiveEnergyDirection");
  }
  if (m_powerUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("powerUnit");
  }
  if (m_energyUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("energyUnit");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram