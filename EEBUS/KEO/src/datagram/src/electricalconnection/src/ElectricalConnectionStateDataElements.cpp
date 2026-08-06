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

#include <keo_datagram/electricalconnection/ElectricalConnectionStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionStateDataElements::ElectricalConnectionStateDataElements()
    : DataElements(), m_electricalConnectionIdIsSet(false),
      m_timestampIsSet(false), m_currentEnergyModeIsSet(false),
      m_consumptionTimeIsSet(false), m_productionTimeIsSet(false),
      m_totalConsumptionTimeIsSet(false), m_totalProductionTimeIsSet(false)

{}

bool ElectricalConnectionStateDataElements::
operator==(const ElectricalConnectionStateDataElements &c_classObject) const {
  if (m_electricalConnectionIdIsSet !=
      c_classObject.m_electricalConnectionIdIsSet) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_currentEnergyModeIsSet != c_classObject.m_currentEnergyModeIsSet) {
    return false;
  }
  if (m_consumptionTimeIsSet != c_classObject.m_consumptionTimeIsSet) {
    return false;
  }
  if (m_productionTimeIsSet != c_classObject.m_productionTimeIsSet) {
    return false;
  }
  if (m_totalConsumptionTimeIsSet !=
      c_classObject.m_totalConsumptionTimeIsSet) {
    return false;
  }
  if (m_totalProductionTimeIsSet != c_classObject.m_totalProductionTimeIsSet) {
    return false;
  }

  return true;
}

bool ElectricalConnectionStateDataElements::
operator!=(const ElectricalConnectionStateDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionStateDataElements::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_timestampIsSet &&
         !m_currentEnergyModeIsSet && !m_consumptionTimeIsSet &&
         !m_productionTimeIsSet && !m_totalConsumptionTimeIsSet &&
         !m_totalProductionTimeIsSet;
}

DataElements::Type ElectricalConnectionStateDataElements::getDataType() const {
  return DataElements::Type::ELECTRICAL_CONNECTION_STATE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ElectricalConnectionStateDataElements::clone() const {
  return std::make_shared<ElectricalConnectionStateDataElements>(*this);
}

void ElectricalConnectionStateDataElements::setElectricalConnectionId() {
  m_electricalConnectionIdIsSet = true;
}

void ElectricalConnectionStateDataElements::cleanElectricalConnectionId() {
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionStateDataElements::getElectricalConnectionIdIsSet()
    const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionStateDataElements::setTimestamp() {
  m_timestampIsSet = true;
}

void ElectricalConnectionStateDataElements::cleanTimestamp() {
  m_timestampIsSet = false;
}

bool ElectricalConnectionStateDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void ElectricalConnectionStateDataElements::setCurrentEnergyMode() {
  m_currentEnergyModeIsSet = true;
}

void ElectricalConnectionStateDataElements::cleanCurrentEnergyMode() {
  m_currentEnergyModeIsSet = false;
}

bool ElectricalConnectionStateDataElements::getCurrentEnergyModeIsSet() const {
  return m_currentEnergyModeIsSet;
}

void ElectricalConnectionStateDataElements::setConsumptionTime() {
  m_consumptionTimeIsSet = true;
}

void ElectricalConnectionStateDataElements::cleanConsumptionTime() {
  m_consumptionTimeIsSet = false;
}

bool ElectricalConnectionStateDataElements::getConsumptionTimeIsSet() const {
  return m_consumptionTimeIsSet;
}

void ElectricalConnectionStateDataElements::setProductionTime() {
  m_productionTimeIsSet = true;
}

void ElectricalConnectionStateDataElements::cleanProductionTime() {
  m_productionTimeIsSet = false;
}

bool ElectricalConnectionStateDataElements::getProductionTimeIsSet() const {
  return m_productionTimeIsSet;
}

void ElectricalConnectionStateDataElements::setTotalConsumptionTime() {
  m_totalConsumptionTimeIsSet = true;
}

void ElectricalConnectionStateDataElements::cleanTotalConsumptionTime() {
  m_totalConsumptionTimeIsSet = false;
}

bool ElectricalConnectionStateDataElements::getTotalConsumptionTimeIsSet()
    const {
  return m_totalConsumptionTimeIsSet;
}

void ElectricalConnectionStateDataElements::setTotalProductionTime() {
  m_totalProductionTimeIsSet = true;
}

void ElectricalConnectionStateDataElements::cleanTotalProductionTime() {
  m_totalProductionTimeIsSet = false;
}

bool ElectricalConnectionStateDataElements::getTotalProductionTimeIsSet()
    const {
  return m_totalProductionTimeIsSet;
}

bool ElectricalConnectionStateDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionId", "timestamp", "currentEnergyMode",
                   "consumptionTime", "productionTime", "totalConsumptionTime",
                   "totalProductionTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "electricalConnectionId")) {
      m_electricalConnectionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timestamp")) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "currentEnergyMode")) {
      m_currentEnergyModeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "consumptionTime")) {
      m_consumptionTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "productionTime")) {
      m_productionTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "totalConsumptionTime")) {
      m_totalConsumptionTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "totalProductionTime")) {
      m_totalProductionTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionStateDataElements::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("electricalConnectionId");
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_currentEnergyModeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("currentEnergyMode");
  }
  if (m_consumptionTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("consumptionTime");
  }
  if (m_productionTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("productionTime");
  }
  if (m_totalConsumptionTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("totalConsumptionTime");
  }
  if (m_totalProductionTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("totalProductionTime");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram