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

#include <keo_datagram/devicediagnosis/DeviceDiagnosisStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceDiagnosisStateDataElements::DeviceDiagnosisStateDataElements()
    : DataElements(), m_timestampIsSet(false), m_operatingStateIsSet(false),
      m_vendorStateCodeIsSet(false), m_lastErrorCodeIsSet(false),
      m_upTimeIsSet(false), m_totalUpTimeIsSet(false),
      m_powerSupplyConditionIsSet(false)

{}

bool DeviceDiagnosisStateDataElements::
operator==(const DeviceDiagnosisStateDataElements &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_operatingStateIsSet != c_classObject.m_operatingStateIsSet) {
    return false;
  }
  if (m_vendorStateCodeIsSet != c_classObject.m_vendorStateCodeIsSet) {
    return false;
  }
  if (m_lastErrorCodeIsSet != c_classObject.m_lastErrorCodeIsSet) {
    return false;
  }
  if (m_upTimeIsSet != c_classObject.m_upTimeIsSet) {
    return false;
  }
  if (m_totalUpTimeIsSet != c_classObject.m_totalUpTimeIsSet) {
    return false;
  }
  if (m_powerSupplyConditionIsSet !=
      c_classObject.m_powerSupplyConditionIsSet) {
    return false;
  }

  return true;
}

bool DeviceDiagnosisStateDataElements::
operator!=(const DeviceDiagnosisStateDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceDiagnosisStateDataElements::isEmpty() const {
  return !m_timestampIsSet && !m_operatingStateIsSet &&
         !m_vendorStateCodeIsSet && !m_lastErrorCodeIsSet && !m_upTimeIsSet &&
         !m_totalUpTimeIsSet && !m_powerSupplyConditionIsSet;
}

DataElements::Type DeviceDiagnosisStateDataElements::getDataType() const {
  return DataElements::Type::DEVICE_DIAGNOSIS_STATE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr DeviceDiagnosisStateDataElements::clone() const {
  return std::make_shared<DeviceDiagnosisStateDataElements>(*this);
}

void DeviceDiagnosisStateDataElements::setTimestamp() {
  m_timestampIsSet = true;
}

void DeviceDiagnosisStateDataElements::cleanTimestamp() {
  m_timestampIsSet = false;
}

bool DeviceDiagnosisStateDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void DeviceDiagnosisStateDataElements::setOperatingState() {
  m_operatingStateIsSet = true;
}

void DeviceDiagnosisStateDataElements::cleanOperatingState() {
  m_operatingStateIsSet = false;
}

bool DeviceDiagnosisStateDataElements::getOperatingStateIsSet() const {
  return m_operatingStateIsSet;
}

void DeviceDiagnosisStateDataElements::setVendorStateCode() {
  m_vendorStateCodeIsSet = true;
}

void DeviceDiagnosisStateDataElements::cleanVendorStateCode() {
  m_vendorStateCodeIsSet = false;
}

bool DeviceDiagnosisStateDataElements::getVendorStateCodeIsSet() const {
  return m_vendorStateCodeIsSet;
}

void DeviceDiagnosisStateDataElements::setLastErrorCode() {
  m_lastErrorCodeIsSet = true;
}

void DeviceDiagnosisStateDataElements::cleanLastErrorCode() {
  m_lastErrorCodeIsSet = false;
}

bool DeviceDiagnosisStateDataElements::getLastErrorCodeIsSet() const {
  return m_lastErrorCodeIsSet;
}

void DeviceDiagnosisStateDataElements::setUpTime() { m_upTimeIsSet = true; }

void DeviceDiagnosisStateDataElements::cleanUpTime() { m_upTimeIsSet = false; }

bool DeviceDiagnosisStateDataElements::getUpTimeIsSet() const {
  return m_upTimeIsSet;
}

void DeviceDiagnosisStateDataElements::setTotalUpTime() {
  m_totalUpTimeIsSet = true;
}

void DeviceDiagnosisStateDataElements::cleanTotalUpTime() {
  m_totalUpTimeIsSet = false;
}

bool DeviceDiagnosisStateDataElements::getTotalUpTimeIsSet() const {
  return m_totalUpTimeIsSet;
}

void DeviceDiagnosisStateDataElements::setPowerSupplyCondition() {
  m_powerSupplyConditionIsSet = true;
}

void DeviceDiagnosisStateDataElements::cleanPowerSupplyCondition() {
  m_powerSupplyConditionIsSet = false;
}

bool DeviceDiagnosisStateDataElements::getPowerSupplyConditionIsSet() const {
  return m_powerSupplyConditionIsSet;
}

bool DeviceDiagnosisStateDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"timestamp", "operatingState", "vendorStateCode", "lastErrorCode",
             "upTime", "totalUpTime", "powerSupplyCondition"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timestamp")) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "operatingState")) {
      m_operatingStateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "vendorStateCode")) {
      m_vendorStateCodeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "lastErrorCode")) {
      m_lastErrorCodeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "upTime")) {
      m_upTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "totalUpTime")) {
      m_totalUpTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "powerSupplyCondition")) {
      m_powerSupplyConditionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceDiagnosisStateDataElements::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_operatingStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("operatingState");
  }
  if (m_vendorStateCodeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("vendorStateCode");
  }
  if (m_lastErrorCodeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("lastErrorCode");
  }
  if (m_upTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("upTime");
  }
  if (m_totalUpTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("totalUpTime");
  }
  if (m_powerSupplyConditionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("powerSupplyCondition");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram