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

#include <keo_datagram/core/UseCaseSupport.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

UseCaseSupport::UseCaseSupport()
    : m_useCaseNameIsSet(false), m_useCaseName(""),
      m_useCaseVersionIsSet(false), m_useCaseVersion(""),
      m_useCaseAvailableIsSet(false), m_useCaseAvailable(false),
      m_scenarioSupportIsSet(false),
      m_scenarioSupport(std::vector<xs_unsignedInt>())

{}

bool UseCaseSupport::operator==(const UseCaseSupport &c_classObject) const {
  if (m_useCaseNameIsSet != c_classObject.m_useCaseNameIsSet ||
      (m_useCaseNameIsSet && (m_useCaseName != c_classObject.m_useCaseName))) {
    return false;
  }
  if (m_useCaseVersionIsSet != c_classObject.m_useCaseVersionIsSet ||
      (m_useCaseVersionIsSet &&
       (m_useCaseVersion != c_classObject.m_useCaseVersion))) {
    return false;
  }
  if (m_useCaseAvailableIsSet != c_classObject.m_useCaseAvailableIsSet ||
      (m_useCaseAvailableIsSet &&
       (m_useCaseAvailable != c_classObject.m_useCaseAvailable))) {
    return false;
  }
  if (m_scenarioSupportIsSet != c_classObject.m_scenarioSupportIsSet ||
      (m_scenarioSupportIsSet &&
       (m_scenarioSupport != c_classObject.m_scenarioSupport))) {
    return false;
  }

  return true;
}

bool UseCaseSupport::operator!=(const UseCaseSupport &c_classObject) const {
  return !(*this == c_classObject);
}

bool UseCaseSupport::isEmpty() const {
  return !m_useCaseNameIsSet && !m_useCaseVersionIsSet &&
         !m_useCaseAvailableIsSet && !m_scenarioSupportIsSet;
}

void UseCaseSupport::setUseCaseName(const xs_string &useCaseName) {
  m_useCaseName = useCaseName;
  m_useCaseNameIsSet = true;
}

const xs_string &UseCaseSupport::getUseCaseName() const {
  return m_useCaseName;
}

void UseCaseSupport::cleanUseCaseName() {
  m_useCaseName = "";
  m_useCaseNameIsSet = false;
}

bool UseCaseSupport::getUseCaseNameIsSet() const { return m_useCaseNameIsSet; }

void UseCaseSupport::setUseCaseVersion(const xs_string &useCaseVersion) {
  m_useCaseVersion = useCaseVersion;
  m_useCaseVersionIsSet = true;
}

const xs_string &UseCaseSupport::getUseCaseVersion() const {
  return m_useCaseVersion;
}

void UseCaseSupport::cleanUseCaseVersion() {
  m_useCaseVersion = "";
  m_useCaseVersionIsSet = false;
}

bool UseCaseSupport::getUseCaseVersionIsSet() const {
  return m_useCaseVersionIsSet;
}

void UseCaseSupport::setUseCaseAvailable(const xs_boolean &useCaseAvailable) {
  m_useCaseAvailable = useCaseAvailable;
  m_useCaseAvailableIsSet = true;
}

const xs_boolean &UseCaseSupport::getUseCaseAvailable() const {
  return m_useCaseAvailable;
}

void UseCaseSupport::cleanUseCaseAvailable() {
  m_useCaseAvailable = false;
  m_useCaseAvailableIsSet = false;
}

bool UseCaseSupport::getUseCaseAvailableIsSet() const {
  return m_useCaseAvailableIsSet;
}

void UseCaseSupport::setScenarioSupport(
    const std::vector<xs_unsignedInt> &scenarioSupport) {
  m_scenarioSupport = scenarioSupport;
  m_scenarioSupportIsSet = true;
}

const std::vector<xs_unsignedInt> &UseCaseSupport::getScenarioSupport() const {
  return m_scenarioSupport;
}

void UseCaseSupport::cleanScenarioSupport() {
  m_scenarioSupport.clear();
  m_scenarioSupportIsSet = false;
}

bool UseCaseSupport::getScenarioSupportIsSet() const {
  return m_scenarioSupportIsSet;
}

bool UseCaseSupport::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"useCaseName", "useCaseVersion", "useCaseAvailable",
                   "scenarioSupport"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "useCaseName", &m_useCaseName)) {
      m_useCaseNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "useCaseVersion", &m_useCaseVersion)) {
      m_useCaseVersionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "useCaseAvailable", &m_useCaseAvailable)) {
      m_useCaseAvailableIsSet = true;
      ++iter;
    }
    if (iter != json->end() && KeoJsonTransformation::getList<xs_unsignedInt>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "scenarioSupport", &m_scenarioSupport)) {
      m_scenarioSupportIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string UseCaseSupport::toJson() const {
  std::string result = "[";
  if (m_useCaseNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("useCaseName", m_useCaseName);
  }
  if (m_useCaseVersionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("useCaseVersion", m_useCaseVersion);
  }
  if (m_useCaseAvailableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("useCaseAvailable", m_useCaseAvailable);
  }
  if (m_scenarioSupportIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>(
        "scenarioSupport", m_scenarioSupport);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram