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

#include <keo_datagram/devicediagnosis/DeviceDiagnosisStateData.h>

#include <keo_datagram/devicediagnosis/DeviceDiagnosisStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceDiagnosisStateData::DeviceDiagnosisStateData()
    : CmdData(), m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_operatingStateIsSet(false),
      m_operatingState(DeviceDiagnosisOperatingState()),
      m_vendorStateCodeIsSet(false), m_vendorStateCode(""),
      m_lastErrorCodeIsSet(false), m_lastErrorCode(""), m_upTimeIsSet(false),
      m_upTime(xs_duration()), m_totalUpTimeIsSet(false),
      m_totalUpTime(xs_duration()), m_powerSupplyConditionIsSet(false),
      m_powerSupplyCondition(PowerSupplyCondition())

{}

bool DeviceDiagnosisStateData::
operator==(const DeviceDiagnosisStateData &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_operatingStateIsSet != c_classObject.m_operatingStateIsSet ||
      (m_operatingStateIsSet &&
       (m_operatingState != c_classObject.m_operatingState))) {
    return false;
  }
  if (m_vendorStateCodeIsSet != c_classObject.m_vendorStateCodeIsSet ||
      (m_vendorStateCodeIsSet &&
       (m_vendorStateCode != c_classObject.m_vendorStateCode))) {
    return false;
  }
  if (m_lastErrorCodeIsSet != c_classObject.m_lastErrorCodeIsSet ||
      (m_lastErrorCodeIsSet &&
       (m_lastErrorCode != c_classObject.m_lastErrorCode))) {
    return false;
  }
  if (m_upTimeIsSet != c_classObject.m_upTimeIsSet ||
      (m_upTimeIsSet && (m_upTime != c_classObject.m_upTime))) {
    return false;
  }
  if (m_totalUpTimeIsSet != c_classObject.m_totalUpTimeIsSet ||
      (m_totalUpTimeIsSet && (m_totalUpTime != c_classObject.m_totalUpTime))) {
    return false;
  }
  if (m_powerSupplyConditionIsSet !=
          c_classObject.m_powerSupplyConditionIsSet ||
      (m_powerSupplyConditionIsSet &&
       (m_powerSupplyCondition != c_classObject.m_powerSupplyCondition))) {
    return false;
  }

  return true;
}

bool DeviceDiagnosisStateData::
operator!=(const DeviceDiagnosisStateData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceDiagnosisStateData::isEmpty() const {
  return !m_timestampIsSet && !m_operatingStateIsSet &&
         !m_vendorStateCodeIsSet && !m_lastErrorCodeIsSet && !m_upTimeIsSet &&
         !m_totalUpTimeIsSet && !m_powerSupplyConditionIsSet;
}

CmdData::Type DeviceDiagnosisStateData::getDataType() const {
  return CmdData::Type::DEVICE_DIAGNOSIS_STATE_DATA_TYPE;
}

CmdDataPtr DeviceDiagnosisStateData::clone() const {
  return std::make_shared<DeviceDiagnosisStateData>(*this);
}

void DeviceDiagnosisStateData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &DeviceDiagnosisStateData::getTimestamp() const {
  return m_timestamp;
}

void DeviceDiagnosisStateData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool DeviceDiagnosisStateData::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void DeviceDiagnosisStateData::setOperatingState(
    const DeviceDiagnosisOperatingState &operatingState) {
  m_operatingState = operatingState;
  m_operatingStateIsSet = true;
}

const DeviceDiagnosisOperatingState &
DeviceDiagnosisStateData::getOperatingState() const {
  return m_operatingState;
}

void DeviceDiagnosisStateData::cleanOperatingState() {
  m_operatingState = DeviceDiagnosisOperatingState();
  m_operatingStateIsSet = false;
}

bool DeviceDiagnosisStateData::getOperatingStateIsSet() const {
  return m_operatingStateIsSet;
}

void DeviceDiagnosisStateData::setVendorStateCode(
    const xs_string &vendorStateCode) {
  m_vendorStateCode = vendorStateCode;
  m_vendorStateCodeIsSet = true;
}

const xs_string &DeviceDiagnosisStateData::getVendorStateCode() const {
  return m_vendorStateCode;
}

void DeviceDiagnosisStateData::cleanVendorStateCode() {
  m_vendorStateCode = "";
  m_vendorStateCodeIsSet = false;
}

bool DeviceDiagnosisStateData::getVendorStateCodeIsSet() const {
  return m_vendorStateCodeIsSet;
}

void DeviceDiagnosisStateData::setLastErrorCode(
    const xs_string &lastErrorCode) {
  m_lastErrorCode = lastErrorCode;
  m_lastErrorCodeIsSet = true;
}

const xs_string &DeviceDiagnosisStateData::getLastErrorCode() const {
  return m_lastErrorCode;
}

void DeviceDiagnosisStateData::cleanLastErrorCode() {
  m_lastErrorCode = "";
  m_lastErrorCodeIsSet = false;
}

bool DeviceDiagnosisStateData::getLastErrorCodeIsSet() const {
  return m_lastErrorCodeIsSet;
}

void DeviceDiagnosisStateData::setUpTime(const xs_duration &upTime) {
  m_upTime = upTime;
  m_upTimeIsSet = true;
}

const xs_duration &DeviceDiagnosisStateData::getUpTime() const {
  return m_upTime;
}

void DeviceDiagnosisStateData::cleanUpTime() {
  m_upTime = xs_duration();
  m_upTimeIsSet = false;
}

bool DeviceDiagnosisStateData::getUpTimeIsSet() const { return m_upTimeIsSet; }

void DeviceDiagnosisStateData::setTotalUpTime(const xs_duration &totalUpTime) {
  m_totalUpTime = totalUpTime;
  m_totalUpTimeIsSet = true;
}

const xs_duration &DeviceDiagnosisStateData::getTotalUpTime() const {
  return m_totalUpTime;
}

void DeviceDiagnosisStateData::cleanTotalUpTime() {
  m_totalUpTime = xs_duration();
  m_totalUpTimeIsSet = false;
}

bool DeviceDiagnosisStateData::getTotalUpTimeIsSet() const {
  return m_totalUpTimeIsSet;
}

void DeviceDiagnosisStateData::setPowerSupplyCondition(
    const PowerSupplyCondition &powerSupplyCondition) {
  m_powerSupplyCondition = powerSupplyCondition;
  m_powerSupplyConditionIsSet = true;
}

const PowerSupplyCondition &
DeviceDiagnosisStateData::getPowerSupplyCondition() const {
  return m_powerSupplyCondition;
}

void DeviceDiagnosisStateData::cleanPowerSupplyCondition() {
  m_powerSupplyCondition = PowerSupplyCondition();
  m_powerSupplyConditionIsSet = false;
}

bool DeviceDiagnosisStateData::getPowerSupplyConditionIsSet() const {
  return m_powerSupplyConditionIsSet;
}

CmdDataPtr
DeviceDiagnosisStateData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      DeviceDiagnosisStateDataElementsPtr elements =
          std::dynamic_pointer_cast<DeviceDiagnosisStateDataElements>(
              filter.getDataElements());
      if (elements) {
        DeviceDiagnosisStateDataPtr dataOut =
            std::make_shared<DeviceDiagnosisStateData>();
        // TODO make sure to always set identifier

        if (getTimestampIsSet() && elements->getTimestampIsSet()) {
          dataOut->setTimestamp(getTimestamp());
        }

        if (getOperatingStateIsSet() && elements->getOperatingStateIsSet()) {
          dataOut->setOperatingState(getOperatingState());
        }

        if (getVendorStateCodeIsSet() && elements->getVendorStateCodeIsSet()) {
          dataOut->setVendorStateCode(getVendorStateCode());
        }

        if (getLastErrorCodeIsSet() && elements->getLastErrorCodeIsSet()) {
          dataOut->setLastErrorCode(getLastErrorCode());
        }

        if (getUpTimeIsSet() && elements->getUpTimeIsSet()) {
          dataOut->setUpTime(getUpTime());
        }

        if (getTotalUpTimeIsSet() && elements->getTotalUpTimeIsSet()) {
          dataOut->setTotalUpTime(getTotalUpTime());
        }

        if (getPowerSupplyConditionIsSet() &&
            elements->getPowerSupplyConditionIsSet()) {
          dataOut->setPowerSupplyCondition(getPowerSupplyCondition());
        }

        return dataOut;
      } else {
        return std::make_shared<DeviceDiagnosisStateData>(*this);
      }
    } else {
      return std::make_shared<DeviceDiagnosisStateData>(*this);
    }
  } else {
    return std::make_shared<DeviceDiagnosisStateData>(*this);
  }
}

bool DeviceDiagnosisStateData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"timestamp", "operatingState", "vendorStateCode", "lastErrorCode",
             "upTime", "totalUpTime", "powerSupplyCondition"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestamp", &m_timestamp)) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "operatingState", &m_operatingState)) {
      m_operatingStateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "vendorStateCode", &m_vendorStateCode)) {
      m_vendorStateCodeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "lastErrorCode", &m_lastErrorCode)) {
      m_lastErrorCodeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "upTime", &m_upTime)) {
      m_upTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "totalUpTime", &m_totalUpTime)) {
      m_totalUpTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerSupplyCondition",
                                   &m_powerSupplyCondition)) {
      m_powerSupplyConditionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceDiagnosisStateData::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_operatingStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("operatingState", m_operatingState);
  }
  if (m_vendorStateCodeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("vendorStateCode", m_vendorStateCode);
  }
  if (m_lastErrorCodeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("lastErrorCode", m_lastErrorCode);
  }
  if (m_upTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("upTime", m_upTime);
  }
  if (m_totalUpTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("totalUpTime", m_totalUpTime);
  }
  if (m_powerSupplyConditionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerSupplyCondition",
                                           m_powerSupplyCondition);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram