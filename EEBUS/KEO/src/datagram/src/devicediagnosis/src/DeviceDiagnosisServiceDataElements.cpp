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

#include <keo_datagram/devicediagnosis/DeviceDiagnosisServiceDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceDiagnosisServiceDataElements::DeviceDiagnosisServiceDataElements()
    : DataElements(), m_timestampIsSet(false), m_installationTimeIsSet(false),
      m_bootCounterIsSet(false), m_nextServiceIsSet(false)

{}

bool DeviceDiagnosisServiceDataElements::
operator==(const DeviceDiagnosisServiceDataElements &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_installationTimeIsSet != c_classObject.m_installationTimeIsSet) {
    return false;
  }
  if (m_bootCounterIsSet != c_classObject.m_bootCounterIsSet) {
    return false;
  }
  if (m_nextServiceIsSet != c_classObject.m_nextServiceIsSet) {
    return false;
  }

  return true;
}

bool DeviceDiagnosisServiceDataElements::
operator!=(const DeviceDiagnosisServiceDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceDiagnosisServiceDataElements::isEmpty() const {
  return !m_timestampIsSet && !m_installationTimeIsSet && !m_bootCounterIsSet &&
         !m_nextServiceIsSet;
}

DataElements::Type DeviceDiagnosisServiceDataElements::getDataType() const {
  return DataElements::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr DeviceDiagnosisServiceDataElements::clone() const {
  return std::make_shared<DeviceDiagnosisServiceDataElements>(*this);
}

void DeviceDiagnosisServiceDataElements::setTimestamp() {
  m_timestampIsSet = true;
}

void DeviceDiagnosisServiceDataElements::cleanTimestamp() {
  m_timestampIsSet = false;
}

bool DeviceDiagnosisServiceDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void DeviceDiagnosisServiceDataElements::setInstallationTime() {
  m_installationTimeIsSet = true;
}

void DeviceDiagnosisServiceDataElements::cleanInstallationTime() {
  m_installationTimeIsSet = false;
}

bool DeviceDiagnosisServiceDataElements::getInstallationTimeIsSet() const {
  return m_installationTimeIsSet;
}

void DeviceDiagnosisServiceDataElements::setBootCounter() {
  m_bootCounterIsSet = true;
}

void DeviceDiagnosisServiceDataElements::cleanBootCounter() {
  m_bootCounterIsSet = false;
}

bool DeviceDiagnosisServiceDataElements::getBootCounterIsSet() const {
  return m_bootCounterIsSet;
}

void DeviceDiagnosisServiceDataElements::setNextService() {
  m_nextServiceIsSet = true;
}

void DeviceDiagnosisServiceDataElements::cleanNextService() {
  m_nextServiceIsSet = false;
}

bool DeviceDiagnosisServiceDataElements::getNextServiceIsSet() const {
  return m_nextServiceIsSet;
}

bool DeviceDiagnosisServiceDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"timestamp", "installationTime", "bootCounter", "nextService"})) {
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
                                     "installationTime")) {
      m_installationTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "bootCounter")) {
      m_bootCounterIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "nextService")) {
      m_nextServiceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceDiagnosisServiceDataElements::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_installationTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("installationTime");
  }
  if (m_bootCounterIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("bootCounter");
  }
  if (m_nextServiceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("nextService");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram