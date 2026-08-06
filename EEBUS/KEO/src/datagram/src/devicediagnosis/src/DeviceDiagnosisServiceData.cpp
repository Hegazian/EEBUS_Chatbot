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

#include <keo_datagram/devicediagnosis/DeviceDiagnosisServiceData.h>

#include <keo_datagram/devicediagnosis/DeviceDiagnosisServiceDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceDiagnosisServiceData::DeviceDiagnosisServiceData()
    : CmdData(), m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_installationTimeIsSet(false),
      m_installationTime(AbsoluteOrRelativeTime()), m_bootCounterIsSet(false),
      m_bootCounter(0), m_nextServiceIsSet(false),
      m_nextService(AbsoluteOrRelativeTime())

{}

bool DeviceDiagnosisServiceData::
operator==(const DeviceDiagnosisServiceData &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_installationTimeIsSet != c_classObject.m_installationTimeIsSet ||
      (m_installationTimeIsSet &&
       (m_installationTime != c_classObject.m_installationTime))) {
    return false;
  }
  if (m_bootCounterIsSet != c_classObject.m_bootCounterIsSet ||
      (m_bootCounterIsSet && (m_bootCounter != c_classObject.m_bootCounter))) {
    return false;
  }
  if (m_nextServiceIsSet != c_classObject.m_nextServiceIsSet ||
      (m_nextServiceIsSet && (m_nextService != c_classObject.m_nextService))) {
    return false;
  }

  return true;
}

bool DeviceDiagnosisServiceData::
operator!=(const DeviceDiagnosisServiceData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceDiagnosisServiceData::isEmpty() const {
  return !m_timestampIsSet && !m_installationTimeIsSet && !m_bootCounterIsSet &&
         !m_nextServiceIsSet;
}

CmdData::Type DeviceDiagnosisServiceData::getDataType() const {
  return CmdData::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_TYPE;
}

CmdDataPtr DeviceDiagnosisServiceData::clone() const {
  return std::make_shared<DeviceDiagnosisServiceData>(*this);
}

void DeviceDiagnosisServiceData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &DeviceDiagnosisServiceData::getTimestamp() const {
  return m_timestamp;
}

void DeviceDiagnosisServiceData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool DeviceDiagnosisServiceData::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void DeviceDiagnosisServiceData::setInstallationTime(
    const AbsoluteOrRelativeTime &installationTime) {
  m_installationTime = installationTime;
  m_installationTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
DeviceDiagnosisServiceData::getInstallationTime() const {
  return m_installationTime;
}

void DeviceDiagnosisServiceData::cleanInstallationTime() {
  m_installationTime = AbsoluteOrRelativeTime();
  m_installationTimeIsSet = false;
}

bool DeviceDiagnosisServiceData::getInstallationTimeIsSet() const {
  return m_installationTimeIsSet;
}

void DeviceDiagnosisServiceData::setBootCounter(
    const xs_unsignedLong &bootCounter) {
  m_bootCounter = bootCounter;
  m_bootCounterIsSet = true;
}

const xs_unsignedLong &DeviceDiagnosisServiceData::getBootCounter() const {
  return m_bootCounter;
}

void DeviceDiagnosisServiceData::cleanBootCounter() {
  m_bootCounter = 0;
  m_bootCounterIsSet = false;
}

bool DeviceDiagnosisServiceData::getBootCounterIsSet() const {
  return m_bootCounterIsSet;
}

void DeviceDiagnosisServiceData::setNextService(
    const AbsoluteOrRelativeTime &nextService) {
  m_nextService = nextService;
  m_nextServiceIsSet = true;
}

const AbsoluteOrRelativeTime &
DeviceDiagnosisServiceData::getNextService() const {
  return m_nextService;
}

void DeviceDiagnosisServiceData::cleanNextService() {
  m_nextService = AbsoluteOrRelativeTime();
  m_nextServiceIsSet = false;
}

bool DeviceDiagnosisServiceData::getNextServiceIsSet() const {
  return m_nextServiceIsSet;
}

CmdDataPtr
DeviceDiagnosisServiceData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      DeviceDiagnosisServiceDataElementsPtr elements =
          std::dynamic_pointer_cast<DeviceDiagnosisServiceDataElements>(
              filter.getDataElements());
      if (elements) {
        DeviceDiagnosisServiceDataPtr dataOut =
            std::make_shared<DeviceDiagnosisServiceData>();
        // TODO make sure to always set identifier

        if (getTimestampIsSet() && elements->getTimestampIsSet()) {
          dataOut->setTimestamp(getTimestamp());
        }

        if (getInstallationTimeIsSet() &&
            elements->getInstallationTimeIsSet()) {
          dataOut->setInstallationTime(getInstallationTime());
        }

        if (getBootCounterIsSet() && elements->getBootCounterIsSet()) {
          dataOut->setBootCounter(getBootCounter());
        }

        if (getNextServiceIsSet() && elements->getNextServiceIsSet()) {
          dataOut->setNextService(getNextService());
        }

        return dataOut;
      } else {
        return std::make_shared<DeviceDiagnosisServiceData>(*this);
      }
    } else {
      return std::make_shared<DeviceDiagnosisServiceData>(*this);
    }
  } else {
    return std::make_shared<DeviceDiagnosisServiceData>(*this);
  }
}

bool DeviceDiagnosisServiceData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"timestamp", "installationTime", "bootCounter", "nextService"})) {
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
                                   "installationTime", &m_installationTime)) {
      m_installationTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "bootCounter", &m_bootCounter)) {
      m_bootCounterIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "nextService", &m_nextService)) {
      m_nextServiceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceDiagnosisServiceData::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_installationTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("installationTime", m_installationTime);
  }
  if (m_bootCounterIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("bootCounter", m_bootCounter);
  }
  if (m_nextServiceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nextService", m_nextService);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram