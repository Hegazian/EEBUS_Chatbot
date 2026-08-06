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

#include <keo_datagram/core/UseCaseInformationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

UseCaseInformationListDataSelectors::UseCaseInformationListDataSelectors()
    : DataSelectors(), m_addressIsSet(false), m_address(FeatureAddress()),
      m_actorIsSet(false), m_actor(""), m_useCaseSupportIsSet(false),
      m_useCaseSupport(UseCaseSupportSelectors())

{}

UseCaseInformationListDataSelectors::UseCaseInformationListDataSelectors(
    const FeatureAddress &c_address, const xs_string &c_actor,
    const UseCaseSupportSelectors &c_useCaseSupport)
    : DataSelectors(), m_addressIsSet(true), m_address(c_address),
      m_actorIsSet(true), m_actor(c_actor), m_useCaseSupportIsSet(true),
      m_useCaseSupport(c_useCaseSupport)

{}

bool UseCaseInformationListDataSelectors::
operator==(const UseCaseInformationListDataSelectors &c_classObject) const {
  if (m_addressIsSet != c_classObject.m_addressIsSet ||
      (m_addressIsSet && (m_address != c_classObject.m_address))) {
    return false;
  }
  if (m_actorIsSet != c_classObject.m_actorIsSet ||
      (m_actorIsSet && (m_actor != c_classObject.m_actor))) {
    return false;
  }
  if (m_useCaseSupportIsSet != c_classObject.m_useCaseSupportIsSet ||
      (m_useCaseSupportIsSet &&
       (m_useCaseSupport != c_classObject.m_useCaseSupport))) {
    return false;
  }

  return true;
}

bool UseCaseInformationListDataSelectors::
operator!=(const UseCaseInformationListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool UseCaseInformationListDataSelectors::isEmpty() const {
  return !m_addressIsSet && !m_actorIsSet && !m_useCaseSupportIsSet;
}

DataSelectors::Type UseCaseInformationListDataSelectors::getDataType() const {
  return DataSelectors::Type::USE_CASE_INFORMATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr UseCaseInformationListDataSelectors::clone() const {
  return std::make_shared<UseCaseInformationListDataSelectors>(*this);
}

void UseCaseInformationListDataSelectors::setAddress(
    const FeatureAddress &address) {
  m_address = address;
  m_addressIsSet = true;
}

const FeatureAddress &UseCaseInformationListDataSelectors::getAddress() const {
  return m_address;
}

void UseCaseInformationListDataSelectors::cleanAddress() {
  m_address = FeatureAddress();
  m_addressIsSet = false;
}

bool UseCaseInformationListDataSelectors::getAddressIsSet() const {
  return m_addressIsSet;
}

void UseCaseInformationListDataSelectors::setActor(const xs_string &actor) {
  m_actor = actor;
  m_actorIsSet = true;
}

const xs_string &UseCaseInformationListDataSelectors::getActor() const {
  return m_actor;
}

void UseCaseInformationListDataSelectors::cleanActor() {
  m_actor = "";
  m_actorIsSet = false;
}

bool UseCaseInformationListDataSelectors::getActorIsSet() const {
  return m_actorIsSet;
}

void UseCaseInformationListDataSelectors::setUseCaseSupport(
    const UseCaseSupportSelectors &useCaseSupport) {
  m_useCaseSupport = useCaseSupport;
  m_useCaseSupportIsSet = true;
}

const UseCaseSupportSelectors &
UseCaseInformationListDataSelectors::getUseCaseSupport() const {
  return m_useCaseSupport;
}

void UseCaseInformationListDataSelectors::cleanUseCaseSupport() {
  m_useCaseSupport = UseCaseSupportSelectors();
  m_useCaseSupportIsSet = false;
}

bool UseCaseInformationListDataSelectors::getUseCaseSupportIsSet() const {
  return m_useCaseSupportIsSet;
}

bool UseCaseInformationListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"address", "actor", "useCaseSupport"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "address", &m_address)) {
      m_addressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "actor", &m_actor)) {
      m_actorIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "useCaseSupport", &m_useCaseSupport)) {
      m_useCaseSupportIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string UseCaseInformationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_addressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("address", m_address);
  }
  if (m_actorIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("actor", m_actor);
  }
  if (m_useCaseSupportIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("useCaseSupport", m_useCaseSupport);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram