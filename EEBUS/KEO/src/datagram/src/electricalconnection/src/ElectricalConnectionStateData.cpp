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

#include <keo_datagram/electricalconnection/ElectricalConnectionStateData.h>

#include <keo_datagram/electricalconnection/ElectricalConnectionStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionStateData::ElectricalConnectionStateData()
    : m_electricalConnectionIdIsSet(false), m_electricalConnectionId(0),
      m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_currentEnergyModeIsSet(false), m_currentEnergyMode(EnergyMode()),
      m_consumptionTimeIsSet(false), m_consumptionTime(xs_duration()),
      m_productionTimeIsSet(false), m_productionTime(xs_duration()),
      m_totalConsumptionTimeIsSet(false), m_totalConsumptionTime(xs_duration()),
      m_totalProductionTimeIsSet(false), m_totalProductionTime(xs_duration())

{}

bool ElectricalConnectionStateData::
operator==(const ElectricalConnectionStateData &c_classObject) const {
  if (m_electricalConnectionIdIsSet !=
          c_classObject.m_electricalConnectionIdIsSet ||
      (m_electricalConnectionIdIsSet &&
       (m_electricalConnectionId != c_classObject.m_electricalConnectionId))) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_currentEnergyModeIsSet != c_classObject.m_currentEnergyModeIsSet ||
      (m_currentEnergyModeIsSet &&
       (m_currentEnergyMode != c_classObject.m_currentEnergyMode))) {
    return false;
  }
  if (m_consumptionTimeIsSet != c_classObject.m_consumptionTimeIsSet ||
      (m_consumptionTimeIsSet &&
       (m_consumptionTime != c_classObject.m_consumptionTime))) {
    return false;
  }
  if (m_productionTimeIsSet != c_classObject.m_productionTimeIsSet ||
      (m_productionTimeIsSet &&
       (m_productionTime != c_classObject.m_productionTime))) {
    return false;
  }
  if (m_totalConsumptionTimeIsSet !=
          c_classObject.m_totalConsumptionTimeIsSet ||
      (m_totalConsumptionTimeIsSet &&
       (m_totalConsumptionTime != c_classObject.m_totalConsumptionTime))) {
    return false;
  }
  if (m_totalProductionTimeIsSet != c_classObject.m_totalProductionTimeIsSet ||
      (m_totalProductionTimeIsSet &&
       (m_totalProductionTime != c_classObject.m_totalProductionTime))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionStateData::
operator!=(const ElectricalConnectionStateData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionStateData::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_timestampIsSet &&
         !m_currentEnergyModeIsSet && !m_consumptionTimeIsSet &&
         !m_productionTimeIsSet && !m_totalConsumptionTimeIsSet &&
         !m_totalProductionTimeIsSet;
}

void ElectricalConnectionStateData::setElectricalConnectionId(
    const xs_unsignedInt &electricalConnectionId) {
  m_electricalConnectionId = electricalConnectionId;
  m_electricalConnectionIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionStateData::getElectricalConnectionId() const {
  return m_electricalConnectionId;
}

void ElectricalConnectionStateData::cleanElectricalConnectionId() {
  m_electricalConnectionId = 0;
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionStateData::getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionStateData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &
ElectricalConnectionStateData::getTimestamp() const {
  return m_timestamp;
}

void ElectricalConnectionStateData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool ElectricalConnectionStateData::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void ElectricalConnectionStateData::setCurrentEnergyMode(
    const EnergyMode &currentEnergyMode) {
  m_currentEnergyMode = currentEnergyMode;
  m_currentEnergyModeIsSet = true;
}

const EnergyMode &ElectricalConnectionStateData::getCurrentEnergyMode() const {
  return m_currentEnergyMode;
}

void ElectricalConnectionStateData::cleanCurrentEnergyMode() {
  m_currentEnergyMode = EnergyMode();
  m_currentEnergyModeIsSet = false;
}

bool ElectricalConnectionStateData::getCurrentEnergyModeIsSet() const {
  return m_currentEnergyModeIsSet;
}

void ElectricalConnectionStateData::setConsumptionTime(
    const xs_duration &consumptionTime) {
  m_consumptionTime = consumptionTime;
  m_consumptionTimeIsSet = true;
}

const xs_duration &ElectricalConnectionStateData::getConsumptionTime() const {
  return m_consumptionTime;
}

void ElectricalConnectionStateData::cleanConsumptionTime() {
  m_consumptionTime = xs_duration();
  m_consumptionTimeIsSet = false;
}

bool ElectricalConnectionStateData::getConsumptionTimeIsSet() const {
  return m_consumptionTimeIsSet;
}

void ElectricalConnectionStateData::setProductionTime(
    const xs_duration &productionTime) {
  m_productionTime = productionTime;
  m_productionTimeIsSet = true;
}

const xs_duration &ElectricalConnectionStateData::getProductionTime() const {
  return m_productionTime;
}

void ElectricalConnectionStateData::cleanProductionTime() {
  m_productionTime = xs_duration();
  m_productionTimeIsSet = false;
}

bool ElectricalConnectionStateData::getProductionTimeIsSet() const {
  return m_productionTimeIsSet;
}

void ElectricalConnectionStateData::setTotalConsumptionTime(
    const xs_duration &totalConsumptionTime) {
  m_totalConsumptionTime = totalConsumptionTime;
  m_totalConsumptionTimeIsSet = true;
}

const xs_duration &
ElectricalConnectionStateData::getTotalConsumptionTime() const {
  return m_totalConsumptionTime;
}

void ElectricalConnectionStateData::cleanTotalConsumptionTime() {
  m_totalConsumptionTime = xs_duration();
  m_totalConsumptionTimeIsSet = false;
}

bool ElectricalConnectionStateData::getTotalConsumptionTimeIsSet() const {
  return m_totalConsumptionTimeIsSet;
}

void ElectricalConnectionStateData::setTotalProductionTime(
    const xs_duration &totalProductionTime) {
  m_totalProductionTime = totalProductionTime;
  m_totalProductionTimeIsSet = true;
}

const xs_duration &
ElectricalConnectionStateData::getTotalProductionTime() const {
  return m_totalProductionTime;
}

void ElectricalConnectionStateData::cleanTotalProductionTime() {
  m_totalProductionTime = xs_duration();
  m_totalProductionTimeIsSet = false;
}

bool ElectricalConnectionStateData::getTotalProductionTimeIsSet() const {
  return m_totalProductionTimeIsSet;
}

ElectricalConnectionStateData ElectricalConnectionStateData::reduce(
    const ElectricalConnectionStateDataElements &elements) const {
  ElectricalConnectionStateData dataOut;
  if (getElectricalConnectionIdIsSet() &&
      elements.getElectricalConnectionIdIsSet()) {
    dataOut.setElectricalConnectionId(getElectricalConnectionId());
  }
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getCurrentEnergyModeIsSet() && elements.getCurrentEnergyModeIsSet()) {
    dataOut.setCurrentEnergyMode(getCurrentEnergyMode());
  }
  if (getConsumptionTimeIsSet() && elements.getConsumptionTimeIsSet()) {
    dataOut.setConsumptionTime(getConsumptionTime());
  }
  if (getProductionTimeIsSet() && elements.getProductionTimeIsSet()) {
    dataOut.setProductionTime(getProductionTime());
  }
  if (getTotalConsumptionTimeIsSet() &&
      elements.getTotalConsumptionTimeIsSet()) {
    dataOut.setTotalConsumptionTime(getTotalConsumptionTime());
  }
  if (getTotalProductionTimeIsSet() && elements.getTotalProductionTimeIsSet()) {
    dataOut.setTotalProductionTime(getTotalProductionTime());
  }
  return dataOut;
}

bool ElectricalConnectionStateData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionId", "timestamp", "currentEnergyMode",
                   "consumptionTime", "productionTime", "totalConsumptionTime",
                   "totalProductionTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "electricalConnectionId",
                                   &m_electricalConnectionId)) {
      m_electricalConnectionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestamp", &m_timestamp)) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "currentEnergyMode", &m_currentEnergyMode)) {
      m_currentEnergyModeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "consumptionTime", &m_consumptionTime)) {
      m_consumptionTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "productionTime", &m_productionTime)) {
      m_productionTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "totalConsumptionTime",
                                   &m_totalConsumptionTime)) {
      m_totalConsumptionTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "totalProductionTime",
                                   &m_totalProductionTime)) {
      m_totalProductionTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionStateData::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("electricalConnectionId",
                                           m_electricalConnectionId);
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_currentEnergyModeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("currentEnergyMode", m_currentEnergyMode);
  }
  if (m_consumptionTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("consumptionTime", m_consumptionTime);
  }
  if (m_productionTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("productionTime", m_productionTime);
  }
  if (m_totalConsumptionTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("totalConsumptionTime",
                                           m_totalConsumptionTime);
  }
  if (m_totalProductionTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("totalProductionTime",
                                           m_totalProductionTime);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram