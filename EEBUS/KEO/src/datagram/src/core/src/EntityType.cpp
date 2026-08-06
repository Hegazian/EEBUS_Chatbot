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

#include <keo_datagram/core/EntityType.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string EntityType::enumToString[MAX_ENUM] = {
    "Battery",
    "Compressor",
    "DeviceInformation",
    "DHWCircuit",
    "DHWStorage",
    "Dishwasher",
    "Dryer",
    "ElectricalImmersionHeater",
    "Fan",
    "GasHeatingAppliance",
    "Generic",
    "HeatingBufferStorage",
    "HeatingCircuit",
    "HeatingObject",
    "HeatingZone",
    "HeatPumpAppliance",
    "HeatSinkCircuit",
    "HeatSourceCircuit",
    "HeatSourceUnit",
    "HVACController",
    "HVACRoom",
    "InstantDHWHeater",
    "Inverter",
    "OilHeatingAppliance",
    "Pump",
    "RefrigerantCircuit",
    "SmartEnergyAppliance",
    "SolarDHWStorage",
    "SolarThermalCircuit",
    "SubMeterElectricity",
    "TemperatureSensor",
    "Washer",
    "BatterySystem",
    "ElectricityGenerationSystem",
    "ElectricityStorageSystem",
    "GridConnectionPointOfPremises",
    "Household",
    "PVSystem",
    "EV",
    "EVSE",
    "ChargingOutlet",
    "CEM"};

EntityType::EntityType()
    : ExtendableSpineEnum(), m_data(EntityType::Value::UNDEFINED__) {}

EntityType::EntityType(EntityType::Value c_data)
    : ExtendableSpineEnum(), m_data(EntityType::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

EntityType::EntityType(const std::string &value) : ExtendableSpineEnum() {
  setFromString(value);
}

EntityType EntityType::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == EntityType::enumToString[i]) {
      return EntityType(static_cast<EntityType::EntityType::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = EntityType();
  result.enumExtend = c_text;
  return result;
}

std::string EntityType::toString() const {
  if (m_data != EntityType::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<EntityType::Value>(MAX_ENUM))) {
      return EntityType::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

EntityType::Value EntityType::getValue() const { return m_data; }

EntityType::Value EntityType::getData() const { return getValue(); }

bool EntityType::setFromString(const std::string &c_text) {
  m_data = EntityType::fromString(c_text).getValue();
  if (m_data == EntityType::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool EntityType::operator==(const EntityType &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool EntityType::operator!=(const EntityType &c_struct) const {
  return !(*this == c_struct);
}

std::size_t EntityType::toNumber() const { return static_cast<size_t>(m_data); }

bool EntityType::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<EntityType::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = EntityType::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram