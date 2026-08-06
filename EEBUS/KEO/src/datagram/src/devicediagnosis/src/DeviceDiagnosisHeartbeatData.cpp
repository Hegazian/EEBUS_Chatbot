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

#include <keo_datagram/devicediagnosis/DeviceDiagnosisHeartbeatData.h>

#include <keo_datagram/devicediagnosis/DeviceDiagnosisHeartbeatDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceDiagnosisHeartbeatData::DeviceDiagnosisHeartbeatData()
    : CmdData(), m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_heartbeatCounterIsSet(false), m_heartbeatCounter(0),
      m_heartbeatTimeoutIsSet(false), m_heartbeatTimeout(xs_duration())

{}

DeviceDiagnosisHeartbeatData::DeviceDiagnosisHeartbeatData(
    const AbsoluteOrRelativeTime &c_timestamp,
    const xs_unsignedLong &c_heartbeatCounter,
    const xs_duration &c_heartbeatTimeout)
    : CmdData(), m_timestampIsSet(true), m_timestamp(c_timestamp),
      m_heartbeatCounterIsSet(true), m_heartbeatCounter(c_heartbeatCounter),
      m_heartbeatTimeoutIsSet(true), m_heartbeatTimeout(c_heartbeatTimeout)

{}

bool DeviceDiagnosisHeartbeatData::
operator==(const DeviceDiagnosisHeartbeatData &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_heartbeatCounterIsSet != c_classObject.m_heartbeatCounterIsSet ||
      (m_heartbeatCounterIsSet &&
       (m_heartbeatCounter != c_classObject.m_heartbeatCounter))) {
    return false;
  }
  if (m_heartbeatTimeoutIsSet != c_classObject.m_heartbeatTimeoutIsSet ||
      (m_heartbeatTimeoutIsSet &&
       (m_heartbeatTimeout != c_classObject.m_heartbeatTimeout))) {
    return false;
  }

  return true;
}

bool DeviceDiagnosisHeartbeatData::
operator!=(const DeviceDiagnosisHeartbeatData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceDiagnosisHeartbeatData::isEmpty() const {
  return !m_timestampIsSet && !m_heartbeatCounterIsSet &&
         !m_heartbeatTimeoutIsSet;
}

CmdData::Type DeviceDiagnosisHeartbeatData::getDataType() const {
  return CmdData::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_TYPE;
}

CmdDataPtr DeviceDiagnosisHeartbeatData::clone() const {
  return std::make_shared<DeviceDiagnosisHeartbeatData>(*this);
}

void DeviceDiagnosisHeartbeatData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &
DeviceDiagnosisHeartbeatData::getTimestamp() const {
  return m_timestamp;
}

void DeviceDiagnosisHeartbeatData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool DeviceDiagnosisHeartbeatData::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void DeviceDiagnosisHeartbeatData::setHeartbeatCounter(
    const xs_unsignedLong &heartbeatCounter) {
  m_heartbeatCounter = heartbeatCounter;
  m_heartbeatCounterIsSet = true;
}

const xs_unsignedLong &
DeviceDiagnosisHeartbeatData::getHeartbeatCounter() const {
  return m_heartbeatCounter;
}

void DeviceDiagnosisHeartbeatData::cleanHeartbeatCounter() {
  m_heartbeatCounter = 0;
  m_heartbeatCounterIsSet = false;
}

bool DeviceDiagnosisHeartbeatData::getHeartbeatCounterIsSet() const {
  return m_heartbeatCounterIsSet;
}

void DeviceDiagnosisHeartbeatData::setHeartbeatTimeout(
    const xs_duration &heartbeatTimeout) {
  m_heartbeatTimeout = heartbeatTimeout;
  m_heartbeatTimeoutIsSet = true;
}

const xs_duration &DeviceDiagnosisHeartbeatData::getHeartbeatTimeout() const {
  return m_heartbeatTimeout;
}

void DeviceDiagnosisHeartbeatData::cleanHeartbeatTimeout() {
  m_heartbeatTimeout = xs_duration();
  m_heartbeatTimeoutIsSet = false;
}

bool DeviceDiagnosisHeartbeatData::getHeartbeatTimeoutIsSet() const {
  return m_heartbeatTimeoutIsSet;
}

CmdDataPtr
DeviceDiagnosisHeartbeatData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      DeviceDiagnosisHeartbeatDataElementsPtr elements =
          std::dynamic_pointer_cast<DeviceDiagnosisHeartbeatDataElements>(
              filter.getDataElements());
      if (elements) {
        DeviceDiagnosisHeartbeatDataPtr dataOut =
            std::make_shared<DeviceDiagnosisHeartbeatData>();
        // TODO make sure to always set identifier

        if (getTimestampIsSet() && elements->getTimestampIsSet()) {
          dataOut->setTimestamp(getTimestamp());
        }

        if (getHeartbeatCounterIsSet() &&
            elements->getHeartbeatCounterIsSet()) {
          dataOut->setHeartbeatCounter(getHeartbeatCounter());
        }

        if (getHeartbeatTimeoutIsSet() &&
            elements->getHeartbeatTimeoutIsSet()) {
          dataOut->setHeartbeatTimeout(getHeartbeatTimeout());
        }

        return dataOut;
      } else {
        return std::make_shared<DeviceDiagnosisHeartbeatData>(*this);
      }
    } else {
      return std::make_shared<DeviceDiagnosisHeartbeatData>(*this);
    }
  } else {
    return std::make_shared<DeviceDiagnosisHeartbeatData>(*this);
  }
}

bool DeviceDiagnosisHeartbeatData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "heartbeatCounter", "heartbeatTimeout"})) {
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
                                   "heartbeatCounter", &m_heartbeatCounter)) {
      m_heartbeatCounterIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "heartbeatTimeout", &m_heartbeatTimeout)) {
      m_heartbeatTimeoutIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceDiagnosisHeartbeatData::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_heartbeatCounterIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("heartbeatCounter", m_heartbeatCounter);
  }
  if (m_heartbeatTimeoutIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("heartbeatTimeout", m_heartbeatTimeout);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram