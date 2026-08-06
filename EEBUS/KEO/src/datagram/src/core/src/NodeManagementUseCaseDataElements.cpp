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

#include <keo_datagram/core/NodeManagementUseCaseDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementUseCaseDataElements::NodeManagementUseCaseDataElements()
    : DataElements(), m_useCaseInformationIsSet(false),
      m_useCaseInformation(UseCaseInformationDataElements())

{}

NodeManagementUseCaseDataElements::NodeManagementUseCaseDataElements(
    const UseCaseInformationDataElements &c_useCaseInformation) {
  setUseCaseInformation(c_useCaseInformation);
}

bool NodeManagementUseCaseDataElements::
operator==(const NodeManagementUseCaseDataElements &c_classObject) const {
  if (m_useCaseInformationIsSet != c_classObject.m_useCaseInformationIsSet ||
      (m_useCaseInformationIsSet &&
       (m_useCaseInformation != c_classObject.m_useCaseInformation))) {
    return false;
  }

  return true;
}

bool NodeManagementUseCaseDataElements::
operator!=(const NodeManagementUseCaseDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementUseCaseDataElements::isEmpty() const {
  return !m_useCaseInformationIsSet;
}

DataElements::Type NodeManagementUseCaseDataElements::getDataType() const {
  return DataElements::Type::NODE_MANAGEMENT_USE_CASE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NodeManagementUseCaseDataElements::clone() const {
  return std::make_shared<NodeManagementUseCaseDataElements>(*this);
}

void NodeManagementUseCaseDataElements::setUseCaseInformation(
    const UseCaseInformationDataElements &useCaseInformation) {
  m_useCaseInformation = useCaseInformation;
  m_useCaseInformationIsSet = true;
}

const UseCaseInformationDataElements &
NodeManagementUseCaseDataElements::getUseCaseInformation() const {
  return m_useCaseInformation;
}

void NodeManagementUseCaseDataElements::cleanUseCaseInformation() {
  m_useCaseInformation = UseCaseInformationDataElements();
  m_useCaseInformationIsSet = false;
}

bool NodeManagementUseCaseDataElements::getUseCaseInformationIsSet() const {
  return m_useCaseInformationIsSet;
}

bool NodeManagementUseCaseDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"useCaseInformation"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "useCaseInformation",
                                   &m_useCaseInformation)) {
      m_useCaseInformationIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementUseCaseDataElements::toJson() const {
  std::string result = "[";
  if (m_useCaseInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("useCaseInformation",
                                           m_useCaseInformation);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram