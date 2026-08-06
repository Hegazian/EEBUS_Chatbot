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

#include <keo_datagram/actuator/ActuatorLevelDescriptionData.h>

#include <keo_datagram/actuator/ActuatorLevelDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ActuatorLevelDescriptionData::ActuatorLevelDescriptionData()
    : CmdData(), m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description(""), m_levelDefaultUnitIsSet(false),
      m_levelDefaultUnit(UnitOfMeasurement())

{}

ActuatorLevelDescriptionData::ActuatorLevelDescriptionData(
    const xs_string &c_label, const xs_string &c_description,
    const UnitOfMeasurement &c_levelDefaultUnit)
    : CmdData(), m_labelIsSet(true), m_label(c_label), m_descriptionIsSet(true),
      m_description(c_description), m_levelDefaultUnitIsSet(true),
      m_levelDefaultUnit(c_levelDefaultUnit)

{}

bool ActuatorLevelDescriptionData::
operator==(const ActuatorLevelDescriptionData &c_classObject) const {
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }
  if (m_levelDefaultUnitIsSet != c_classObject.m_levelDefaultUnitIsSet ||
      (m_levelDefaultUnitIsSet &&
       (m_levelDefaultUnit != c_classObject.m_levelDefaultUnit))) {
    return false;
  }

  return true;
}

bool ActuatorLevelDescriptionData::
operator!=(const ActuatorLevelDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ActuatorLevelDescriptionData::isEmpty() const {
  return !m_labelIsSet && !m_descriptionIsSet && !m_levelDefaultUnitIsSet;
}

CmdData::Type ActuatorLevelDescriptionData::getDataType() const {
  return CmdData::Type::ACTUATOR_LEVEL_DESCRIPTION_DATA_TYPE;
}

CmdDataPtr ActuatorLevelDescriptionData::clone() const {
  return std::make_shared<ActuatorLevelDescriptionData>(*this);
}

void ActuatorLevelDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &ActuatorLevelDescriptionData::getLabel() const {
  return m_label;
}

void ActuatorLevelDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool ActuatorLevelDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void ActuatorLevelDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &ActuatorLevelDescriptionData::getDescription() const {
  return m_description;
}

void ActuatorLevelDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool ActuatorLevelDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void ActuatorLevelDescriptionData::setLevelDefaultUnit(
    const UnitOfMeasurement &levelDefaultUnit) {
  m_levelDefaultUnit = levelDefaultUnit;
  m_levelDefaultUnitIsSet = true;
}

const UnitOfMeasurement &
ActuatorLevelDescriptionData::getLevelDefaultUnit() const {
  return m_levelDefaultUnit;
}

void ActuatorLevelDescriptionData::cleanLevelDefaultUnit() {
  m_levelDefaultUnit = UnitOfMeasurement();
  m_levelDefaultUnitIsSet = false;
}

bool ActuatorLevelDescriptionData::getLevelDefaultUnitIsSet() const {
  return m_levelDefaultUnitIsSet;
}

CmdDataPtr
ActuatorLevelDescriptionData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      ActuatorLevelDescriptionDataElementsPtr elements =
          std::dynamic_pointer_cast<ActuatorLevelDescriptionDataElements>(
              filter.getDataElements());
      if (elements) {
        ActuatorLevelDescriptionDataPtr dataOut =
            std::make_shared<ActuatorLevelDescriptionData>();
        // TODO make sure to always set identifier

        if (getLabelIsSet() && elements->getLabelIsSet()) {
          dataOut->setLabel(getLabel());
        }

        if (getDescriptionIsSet() && elements->getDescriptionIsSet()) {
          dataOut->setDescription(getDescription());
        }

        if (getLevelDefaultUnitIsSet() &&
            elements->getLevelDefaultUnitIsSet()) {
          dataOut->setLevelDefaultUnit(getLevelDefaultUnit());
        }

        return dataOut;
      } else {
        return std::make_shared<ActuatorLevelDescriptionData>(*this);
      }
    } else {
      return std::make_shared<ActuatorLevelDescriptionData>(*this);
    }
  } else {
    return std::make_shared<ActuatorLevelDescriptionData>(*this);
  }
}

bool ActuatorLevelDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"label", "description", "levelDefaultUnit"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
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
                                   "levelDefaultUnit", &m_levelDefaultUnit)) {
      m_levelDefaultUnitIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ActuatorLevelDescriptionData::toJson() const {
  std::string result = "[";
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  if (m_levelDefaultUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("levelDefaultUnit", m_levelDefaultUnit);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram