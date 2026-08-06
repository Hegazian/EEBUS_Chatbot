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

#include <keo_datagram/core/NodeManagementUseCaseDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementUseCaseDataSelectors::NodeManagementUseCaseDataSelectors()
    : DataSelectors(), m_useCaseInformationIsSet(false),
      m_useCaseInformation(UseCaseInformationListDataSelectors())

{}

NodeManagementUseCaseDataSelectors::NodeManagementUseCaseDataSelectors(
    const UseCaseInformationListDataSelectors &c_useCaseInformation) {
  setUseCaseInformation(c_useCaseInformation);
}

bool NodeManagementUseCaseDataSelectors::
operator==(const NodeManagementUseCaseDataSelectors &c_classObject) const {
  if (m_useCaseInformationIsSet != c_classObject.m_useCaseInformationIsSet ||
      (m_useCaseInformationIsSet &&
       (m_useCaseInformation != c_classObject.m_useCaseInformation))) {
    return false;
  }

  return true;
}

bool NodeManagementUseCaseDataSelectors::
operator!=(const NodeManagementUseCaseDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementUseCaseDataSelectors::isEmpty() const {
  return !m_useCaseInformationIsSet;
}

DataSelectors::Type NodeManagementUseCaseDataSelectors::getDataType() const {
  return DataSelectors::Type::NODE_MANAGEMENT_USE_CASE_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr NodeManagementUseCaseDataSelectors::clone() const {
  return std::make_shared<NodeManagementUseCaseDataSelectors>(*this);
}

void NodeManagementUseCaseDataSelectors::setUseCaseInformation(
    const UseCaseInformationListDataSelectors &useCaseInformation) {
  m_useCaseInformation = useCaseInformation;
  m_useCaseInformationIsSet = true;
}

const UseCaseInformationListDataSelectors &
NodeManagementUseCaseDataSelectors::getUseCaseInformation() const {
  return m_useCaseInformation;
}

void NodeManagementUseCaseDataSelectors::cleanUseCaseInformation() {
  m_useCaseInformation = UseCaseInformationListDataSelectors();
  m_useCaseInformationIsSet = false;
}

bool NodeManagementUseCaseDataSelectors::getUseCaseInformationIsSet() const {
  return m_useCaseInformationIsSet;
}

bool NodeManagementUseCaseDataSelectors::fromJson(KeoJsonValue *json) {
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

std::string NodeManagementUseCaseDataSelectors::toJson() const {
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