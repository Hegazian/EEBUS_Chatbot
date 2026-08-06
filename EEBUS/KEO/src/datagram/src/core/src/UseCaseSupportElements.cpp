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

#include <keo_datagram/core/UseCaseSupportElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

UseCaseSupportElements::UseCaseSupportElements()
    : m_useCaseNameIsSet(false), m_useCaseVersionIsSet(false),
      m_useCaseAvailableIsSet(false), m_scenarioSupportIsSet(false)

{}

bool UseCaseSupportElements::
operator==(const UseCaseSupportElements &c_classObject) const {
  if (m_useCaseNameIsSet != c_classObject.m_useCaseNameIsSet) {
    return false;
  }
  if (m_useCaseVersionIsSet != c_classObject.m_useCaseVersionIsSet) {
    return false;
  }
  if (m_useCaseAvailableIsSet != c_classObject.m_useCaseAvailableIsSet) {
    return false;
  }
  if (m_scenarioSupportIsSet != c_classObject.m_scenarioSupportIsSet) {
    return false;
  }

  return true;
}

bool UseCaseSupportElements::
operator!=(const UseCaseSupportElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool UseCaseSupportElements::isEmpty() const {
  return !m_useCaseNameIsSet && !m_useCaseVersionIsSet &&
         !m_useCaseAvailableIsSet && !m_scenarioSupportIsSet;
}

void UseCaseSupportElements::setUseCaseName() { m_useCaseNameIsSet = true; }

void UseCaseSupportElements::cleanUseCaseName() { m_useCaseNameIsSet = false; }

bool UseCaseSupportElements::getUseCaseNameIsSet() const {
  return m_useCaseNameIsSet;
}

void UseCaseSupportElements::setUseCaseVersion() {
  m_useCaseVersionIsSet = true;
}

void UseCaseSupportElements::cleanUseCaseVersion() {
  m_useCaseVersionIsSet = false;
}

bool UseCaseSupportElements::getUseCaseVersionIsSet() const {
  return m_useCaseVersionIsSet;
}

void UseCaseSupportElements::setUseCaseAvailable() {
  m_useCaseAvailableIsSet = true;
}

void UseCaseSupportElements::cleanUseCaseAvailable() {
  m_useCaseAvailableIsSet = false;
}

bool UseCaseSupportElements::getUseCaseAvailableIsSet() const {
  return m_useCaseAvailableIsSet;
}

void UseCaseSupportElements::setScenarioSupport() {
  m_scenarioSupportIsSet = true;
}

void UseCaseSupportElements::cleanScenarioSupport() {
  m_scenarioSupportIsSet = false;
}

bool UseCaseSupportElements::getScenarioSupportIsSet() const {
  return m_scenarioSupportIsSet;
}

bool UseCaseSupportElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"useCaseName", "useCaseVersion", "useCaseAvailable",
                   "scenarioSupport"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "useCaseName")) {
      m_useCaseNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "useCaseVersion")) {
      m_useCaseVersionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "useCaseAvailable")) {
      m_useCaseAvailableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scenarioSupport")) {
      m_scenarioSupportIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string UseCaseSupportElements::toJson() const {
  std::string result = "[";
  if (m_useCaseNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("useCaseName");
  }
  if (m_useCaseVersionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("useCaseVersion");
  }
  if (m_useCaseAvailableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("useCaseAvailable");
  }
  if (m_scenarioSupportIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scenarioSupport");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram