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

#include <keo_datagram/devicediagnosis/DeviceDiagnosisHeartbeatDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceDiagnosisHeartbeatDataElements::DeviceDiagnosisHeartbeatDataElements()
    : DataElements(), m_timestampIsSet(false), m_heartbeatCounterIsSet(false),
      m_heartbeatTimeoutIsSet(false)

{}

DeviceDiagnosisHeartbeatDataElements::DeviceDiagnosisHeartbeatDataElements(
    xs_boolean c_timestampIsSet, xs_boolean c_heartbeatCounterIsSet,
    xs_boolean c_heartbeatTimeoutIsSet)
    : DataElements(), m_timestampIsSet(c_timestampIsSet),
      m_heartbeatCounterIsSet(c_heartbeatCounterIsSet),
      m_heartbeatTimeoutIsSet(c_heartbeatTimeoutIsSet)

{}

bool DeviceDiagnosisHeartbeatDataElements::
operator==(const DeviceDiagnosisHeartbeatDataElements &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_heartbeatCounterIsSet != c_classObject.m_heartbeatCounterIsSet) {
    return false;
  }
  if (m_heartbeatTimeoutIsSet != c_classObject.m_heartbeatTimeoutIsSet) {
    return false;
  }

  return true;
}

bool DeviceDiagnosisHeartbeatDataElements::
operator!=(const DeviceDiagnosisHeartbeatDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceDiagnosisHeartbeatDataElements::isEmpty() const {
  return !m_timestampIsSet && !m_heartbeatCounterIsSet &&
         !m_heartbeatTimeoutIsSet;
}

DataElements::Type DeviceDiagnosisHeartbeatDataElements::getDataType() const {
  return DataElements::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_ELEMENTS_TYPE;
}

DataElementsPtr DeviceDiagnosisHeartbeatDataElements::clone() const {
  return std::make_shared<DeviceDiagnosisHeartbeatDataElements>(*this);
}

void DeviceDiagnosisHeartbeatDataElements::setTimestamp() {
  m_timestampIsSet = true;
}

void DeviceDiagnosisHeartbeatDataElements::cleanTimestamp() {
  m_timestampIsSet = false;
}

bool DeviceDiagnosisHeartbeatDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void DeviceDiagnosisHeartbeatDataElements::setHeartbeatCounter() {
  m_heartbeatCounterIsSet = true;
}

void DeviceDiagnosisHeartbeatDataElements::cleanHeartbeatCounter() {
  m_heartbeatCounterIsSet = false;
}

bool DeviceDiagnosisHeartbeatDataElements::getHeartbeatCounterIsSet() const {
  return m_heartbeatCounterIsSet;
}

void DeviceDiagnosisHeartbeatDataElements::setHeartbeatTimeout() {
  m_heartbeatTimeoutIsSet = true;
}

void DeviceDiagnosisHeartbeatDataElements::cleanHeartbeatTimeout() {
  m_heartbeatTimeoutIsSet = false;
}

bool DeviceDiagnosisHeartbeatDataElements::getHeartbeatTimeoutIsSet() const {
  return m_heartbeatTimeoutIsSet;
}

bool DeviceDiagnosisHeartbeatDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "heartbeatCounter", "heartbeatTimeout"})) {
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
                                     "heartbeatCounter")) {
      m_heartbeatCounterIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "heartbeatTimeout")) {
      m_heartbeatTimeoutIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceDiagnosisHeartbeatDataElements::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_heartbeatCounterIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("heartbeatCounter");
  }
  if (m_heartbeatTimeoutIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("heartbeatTimeout");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram