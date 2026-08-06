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

#include <keo_datagram/core/UseCaseSupportSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

UseCaseSupportSelectors::UseCaseSupportSelectors()
    : m_useCaseNameIsSet(false), m_useCaseName(""),
      m_useCaseVersionIsSet(false), m_useCaseVersion(""),
      m_scenarioSupportIsSet(false), m_scenarioSupport(0)

{}

UseCaseSupportSelectors::UseCaseSupportSelectors(
    const xs_string &c_useCaseName, const xs_string &c_useCaseVersion,
    const xs_unsignedInt &c_scenarioSupport)
    : m_useCaseNameIsSet(true), m_useCaseName(c_useCaseName),
      m_useCaseVersionIsSet(true), m_useCaseVersion(c_useCaseVersion),
      m_scenarioSupportIsSet(true), m_scenarioSupport(c_scenarioSupport)

{}

bool UseCaseSupportSelectors::
operator==(const UseCaseSupportSelectors &c_classObject) const {
  if (m_useCaseNameIsSet != c_classObject.m_useCaseNameIsSet ||
      (m_useCaseNameIsSet && (m_useCaseName != c_classObject.m_useCaseName))) {
    return false;
  }
  if (m_useCaseVersionIsSet != c_classObject.m_useCaseVersionIsSet ||
      (m_useCaseVersionIsSet &&
       (m_useCaseVersion != c_classObject.m_useCaseVersion))) {
    return false;
  }
  if (m_scenarioSupportIsSet != c_classObject.m_scenarioSupportIsSet ||
      (m_scenarioSupportIsSet &&
       (m_scenarioSupport != c_classObject.m_scenarioSupport))) {
    return false;
  }

  return true;
}

bool UseCaseSupportSelectors::
operator!=(const UseCaseSupportSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool UseCaseSupportSelectors::isEmpty() const {
  return !m_useCaseNameIsSet && !m_useCaseVersionIsSet &&
         !m_scenarioSupportIsSet;
}

void UseCaseSupportSelectors::setUseCaseName(const xs_string &useCaseName) {
  m_useCaseName = useCaseName;
  m_useCaseNameIsSet = true;
}

const xs_string &UseCaseSupportSelectors::getUseCaseName() const {
  return m_useCaseName;
}

void UseCaseSupportSelectors::cleanUseCaseName() {
  m_useCaseName = "";
  m_useCaseNameIsSet = false;
}

bool UseCaseSupportSelectors::getUseCaseNameIsSet() const {
  return m_useCaseNameIsSet;
}

void UseCaseSupportSelectors::setUseCaseVersion(
    const xs_string &useCaseVersion) {
  m_useCaseVersion = useCaseVersion;
  m_useCaseVersionIsSet = true;
}

const xs_string &UseCaseSupportSelectors::getUseCaseVersion() const {
  return m_useCaseVersion;
}

void UseCaseSupportSelectors::cleanUseCaseVersion() {
  m_useCaseVersion = "";
  m_useCaseVersionIsSet = false;
}

bool UseCaseSupportSelectors::getUseCaseVersionIsSet() const {
  return m_useCaseVersionIsSet;
}

void UseCaseSupportSelectors::setScenarioSupport(
    const xs_unsignedInt &scenarioSupport) {
  m_scenarioSupport = scenarioSupport;
  m_scenarioSupportIsSet = true;
}

const xs_unsignedInt &UseCaseSupportSelectors::getScenarioSupport() const {
  return m_scenarioSupport;
}

void UseCaseSupportSelectors::cleanScenarioSupport() {
  m_scenarioSupport = 0;
  m_scenarioSupportIsSet = false;
}

bool UseCaseSupportSelectors::getScenarioSupportIsSet() const {
  return m_scenarioSupportIsSet;
}

bool UseCaseSupportSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"useCaseName", "useCaseVersion", "scenarioSupport"})) {
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
                                   "scenarioSupport", &m_scenarioSupport)) {
      m_scenarioSupportIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string UseCaseSupportSelectors::toJson() const {
  std::string result = "[";
  if (m_useCaseNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("useCaseName", m_useCaseName);
  }
  if (m_useCaseVersionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("useCaseVersion", m_useCaseVersion);
  }
  if (m_scenarioSupportIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("scenarioSupport", m_scenarioSupport);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram