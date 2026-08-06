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

#include <keo_datagram/actuator/ActuatorLevelDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ActuatorLevelDescriptionDataElements::ActuatorLevelDescriptionDataElements()
    : DataElements(), m_labelIsSet(false), m_descriptionIsSet(false),
      m_levelDefaultUnitIsSet(false)

{}

ActuatorLevelDescriptionDataElements::ActuatorLevelDescriptionDataElements(
    xs_boolean c_labelIsSet, xs_boolean c_descriptionIsSet,
    xs_boolean c_levelDefaultUnitIsSet)
    : DataElements(), m_labelIsSet(c_labelIsSet),
      m_descriptionIsSet(c_descriptionIsSet),
      m_levelDefaultUnitIsSet(c_levelDefaultUnitIsSet)

{}

bool ActuatorLevelDescriptionDataElements::
operator==(const ActuatorLevelDescriptionDataElements &c_classObject) const {
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }
  if (m_levelDefaultUnitIsSet != c_classObject.m_levelDefaultUnitIsSet) {
    return false;
  }

  return true;
}

bool ActuatorLevelDescriptionDataElements::
operator!=(const ActuatorLevelDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ActuatorLevelDescriptionDataElements::isEmpty() const {
  return !m_labelIsSet && !m_descriptionIsSet && !m_levelDefaultUnitIsSet;
}

DataElements::Type ActuatorLevelDescriptionDataElements::getDataType() const {
  return DataElements::Type::ACTUATOR_LEVEL_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ActuatorLevelDescriptionDataElements::clone() const {
  return std::make_shared<ActuatorLevelDescriptionDataElements>(*this);
}

void ActuatorLevelDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void ActuatorLevelDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool ActuatorLevelDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void ActuatorLevelDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void ActuatorLevelDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool ActuatorLevelDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void ActuatorLevelDescriptionDataElements::setLevelDefaultUnit() {
  m_levelDefaultUnitIsSet = true;
}

void ActuatorLevelDescriptionDataElements::cleanLevelDefaultUnit() {
  m_levelDefaultUnitIsSet = false;
}

bool ActuatorLevelDescriptionDataElements::getLevelDefaultUnitIsSet() const {
  return m_levelDefaultUnitIsSet;
}

bool ActuatorLevelDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"label", "description", "levelDefaultUnit"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
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
                                     "levelDefaultUnit")) {
      m_levelDefaultUnitIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ActuatorLevelDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  if (m_levelDefaultUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("levelDefaultUnit");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram