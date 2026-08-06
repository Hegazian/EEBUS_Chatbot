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

#include <keo_datagram/core/UseCaseInformationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

UseCaseInformationDataElements::UseCaseInformationDataElements()
    : DataElements(), m_addressIsSet(false),
      m_address(FeatureAddressElements()), m_actorIsSet(false),
      m_useCaseSupportIsSet(false), m_useCaseSupport(UseCaseSupportElements())

{}

UseCaseInformationDataElements::UseCaseInformationDataElements(
    const FeatureAddressElements &c_address, xs_boolean c_actorIsSet,
    const UseCaseSupportElements &c_useCaseSupport)
    : DataElements(), m_addressIsSet(true), m_address(c_address),
      m_actorIsSet(c_actorIsSet), m_useCaseSupportIsSet(true),
      m_useCaseSupport(c_useCaseSupport)

{}

bool UseCaseInformationDataElements::
operator==(const UseCaseInformationDataElements &c_classObject) const {
  if (m_addressIsSet != c_classObject.m_addressIsSet ||
      (m_addressIsSet && (m_address != c_classObject.m_address))) {
    return false;
  }
  if (m_actorIsSet != c_classObject.m_actorIsSet) {
    return false;
  }
  if (m_useCaseSupportIsSet != c_classObject.m_useCaseSupportIsSet ||
      (m_useCaseSupportIsSet &&
       (m_useCaseSupport != c_classObject.m_useCaseSupport))) {
    return false;
  }

  return true;
}

bool UseCaseInformationDataElements::
operator!=(const UseCaseInformationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool UseCaseInformationDataElements::isEmpty() const {
  return !m_addressIsSet && !m_actorIsSet && !m_useCaseSupportIsSet;
}

DataElements::Type UseCaseInformationDataElements::getDataType() const {
  return DataElements::Type::USE_CASE_INFORMATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr UseCaseInformationDataElements::clone() const {
  return std::make_shared<UseCaseInformationDataElements>(*this);
}

void UseCaseInformationDataElements::setAddress(
    const FeatureAddressElements &address) {
  m_address = address;
  m_addressIsSet = true;
}

const FeatureAddressElements &
UseCaseInformationDataElements::getAddress() const {
  return m_address;
}

void UseCaseInformationDataElements::cleanAddress() {
  m_address = FeatureAddressElements();
  m_addressIsSet = false;
}

bool UseCaseInformationDataElements::getAddressIsSet() const {
  return m_addressIsSet;
}

void UseCaseInformationDataElements::setActor() { m_actorIsSet = true; }

void UseCaseInformationDataElements::cleanActor() { m_actorIsSet = false; }

bool UseCaseInformationDataElements::getActorIsSet() const {
  return m_actorIsSet;
}

void UseCaseInformationDataElements::setUseCaseSupport(
    const UseCaseSupportElements &useCaseSupport) {
  m_useCaseSupport = useCaseSupport;
  m_useCaseSupportIsSet = true;
}

const UseCaseSupportElements &
UseCaseInformationDataElements::getUseCaseSupport() const {
  return m_useCaseSupport;
}

void UseCaseInformationDataElements::cleanUseCaseSupport() {
  m_useCaseSupport = UseCaseSupportElements();
  m_useCaseSupportIsSet = false;
}

bool UseCaseInformationDataElements::getUseCaseSupportIsSet() const {
  return m_useCaseSupportIsSet;
}

bool UseCaseInformationDataElements::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "actor")) {
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

std::string UseCaseInformationDataElements::toJson() const {
  std::string result = "[";
  if (m_addressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("address", m_address);
  }
  if (m_actorIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("actor");
  }
  if (m_useCaseSupportIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("useCaseSupport", m_useCaseSupport);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram