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

#include <keo_datagram/directcontrol/DirectControlDescriptionData.h>

#include <keo_datagram/directcontrol/DirectControlDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DirectControlDescriptionData::DirectControlDescriptionData()
    : CmdData(), m_positiveEnergyDirectionIsSet(false),
      m_positiveEnergyDirection(EnergyDirection()), m_powerUnitIsSet(false),
      m_powerUnit(UnitOfMeasurement()), m_energyUnitIsSet(false),
      m_energyUnit(UnitOfMeasurement())

{}

DirectControlDescriptionData::DirectControlDescriptionData(
    const EnergyDirection &c_positiveEnergyDirection,
    const UnitOfMeasurement &c_powerUnit, const UnitOfMeasurement &c_energyUnit)
    : CmdData(), m_positiveEnergyDirectionIsSet(true),
      m_positiveEnergyDirection(c_positiveEnergyDirection),
      m_powerUnitIsSet(true), m_powerUnit(c_powerUnit), m_energyUnitIsSet(true),
      m_energyUnit(c_energyUnit)

{}

bool DirectControlDescriptionData::
operator==(const DirectControlDescriptionData &c_classObject) const {
  if (m_positiveEnergyDirectionIsSet !=
          c_classObject.m_positiveEnergyDirectionIsSet ||
      (m_positiveEnergyDirectionIsSet &&
       (m_positiveEnergyDirection !=
        c_classObject.m_positiveEnergyDirection))) {
    return false;
  }
  if (m_powerUnitIsSet != c_classObject.m_powerUnitIsSet ||
      (m_powerUnitIsSet && (m_powerUnit != c_classObject.m_powerUnit))) {
    return false;
  }
  if (m_energyUnitIsSet != c_classObject.m_energyUnitIsSet ||
      (m_energyUnitIsSet && (m_energyUnit != c_classObject.m_energyUnit))) {
    return false;
  }

  return true;
}

bool DirectControlDescriptionData::
operator!=(const DirectControlDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DirectControlDescriptionData::isEmpty() const {
  return !m_positiveEnergyDirectionIsSet && !m_powerUnitIsSet &&
         !m_energyUnitIsSet;
}

CmdData::Type DirectControlDescriptionData::getDataType() const {
  return CmdData::Type::DIRECT_CONTROL_DESCRIPTION_DATA_TYPE;
}

CmdDataPtr DirectControlDescriptionData::clone() const {
  return std::make_shared<DirectControlDescriptionData>(*this);
}

void DirectControlDescriptionData::setPositiveEnergyDirection(
    const EnergyDirection &positiveEnergyDirection) {
  m_positiveEnergyDirection = positiveEnergyDirection;
  m_positiveEnergyDirectionIsSet = true;
}

const EnergyDirection &
DirectControlDescriptionData::getPositiveEnergyDirection() const {
  return m_positiveEnergyDirection;
}

void DirectControlDescriptionData::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirection = EnergyDirection();
  m_positiveEnergyDirectionIsSet = false;
}

bool DirectControlDescriptionData::getPositiveEnergyDirectionIsSet() const {
  return m_positiveEnergyDirectionIsSet;
}

void DirectControlDescriptionData::setPowerUnit(
    const UnitOfMeasurement &powerUnit) {
  m_powerUnit = powerUnit;
  m_powerUnitIsSet = true;
}

const UnitOfMeasurement &DirectControlDescriptionData::getPowerUnit() const {
  return m_powerUnit;
}

void DirectControlDescriptionData::cleanPowerUnit() {
  m_powerUnit = UnitOfMeasurement();
  m_powerUnitIsSet = false;
}

bool DirectControlDescriptionData::getPowerUnitIsSet() const {
  return m_powerUnitIsSet;
}

void DirectControlDescriptionData::setEnergyUnit(
    const UnitOfMeasurement &energyUnit) {
  m_energyUnit = energyUnit;
  m_energyUnitIsSet = true;
}

const UnitOfMeasurement &DirectControlDescriptionData::getEnergyUnit() const {
  return m_energyUnit;
}

void DirectControlDescriptionData::cleanEnergyUnit() {
  m_energyUnit = UnitOfMeasurement();
  m_energyUnitIsSet = false;
}

bool DirectControlDescriptionData::getEnergyUnitIsSet() const {
  return m_energyUnitIsSet;
}

CmdDataPtr
DirectControlDescriptionData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      DirectControlDescriptionDataElementsPtr elements =
          std::dynamic_pointer_cast<DirectControlDescriptionDataElements>(
              filter.getDataElements());
      if (elements) {
        DirectControlDescriptionDataPtr dataOut =
            std::make_shared<DirectControlDescriptionData>();
        // TODO make sure to always set identifier

        if (getPositiveEnergyDirectionIsSet() &&
            elements->getPositiveEnergyDirectionIsSet()) {
          dataOut->setPositiveEnergyDirection(getPositiveEnergyDirection());
        }

        if (getPowerUnitIsSet() && elements->getPowerUnitIsSet()) {
          dataOut->setPowerUnit(getPowerUnit());
        }

        if (getEnergyUnitIsSet() && elements->getEnergyUnitIsSet()) {
          dataOut->setEnergyUnit(getEnergyUnit());
        }

        return dataOut;
      } else {
        return std::make_shared<DirectControlDescriptionData>(*this);
      }
    } else {
      return std::make_shared<DirectControlDescriptionData>(*this);
    }
  } else {
    return std::make_shared<DirectControlDescriptionData>(*this);
  }
}

bool DirectControlDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"positiveEnergyDirection", "powerUnit", "energyUnit"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "positiveEnergyDirection",
                                   &m_positiveEnergyDirection)) {
      m_positiveEnergyDirectionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerUnit", &m_powerUnit)) {
      m_powerUnitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "energyUnit", &m_energyUnit)) {
      m_energyUnitIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DirectControlDescriptionData::toJson() const {
  std::string result = "[";
  if (m_positiveEnergyDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("positiveEnergyDirection",
                                           m_positiveEnergyDirection);
  }
  if (m_powerUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerUnit", m_powerUnit);
  }
  if (m_energyUnitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("energyUnit", m_energyUnit);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram