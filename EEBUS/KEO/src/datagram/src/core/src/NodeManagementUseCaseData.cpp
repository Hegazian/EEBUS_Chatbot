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

#include <keo_datagram/core/NodeManagementUseCaseData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementUseCaseData::NodeManagementUseCaseData()
    : CmdData(), m_useCaseInformationIsSet(false),
      m_useCaseInformation(std::vector<UseCaseInformationData>())

{}

NodeManagementUseCaseData::NodeManagementUseCaseData(
    const std::vector<UseCaseInformationData> &c_useCaseInformation) {
  setUseCaseInformation(c_useCaseInformation);
}

bool NodeManagementUseCaseData::
operator==(const NodeManagementUseCaseData &c_classObject) const {
  if (m_useCaseInformationIsSet != c_classObject.m_useCaseInformationIsSet ||
      (m_useCaseInformationIsSet &&
       (m_useCaseInformation != c_classObject.m_useCaseInformation))) {
    return false;
  }

  return true;
}

bool NodeManagementUseCaseData::
operator!=(const NodeManagementUseCaseData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementUseCaseData::isEmpty() const {
  return !m_useCaseInformationIsSet;
}

CmdData::Type NodeManagementUseCaseData::getDataType() const {
  return CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE;
}

CmdDataPtr NodeManagementUseCaseData::clone() const {
  return std::make_shared<NodeManagementUseCaseData>(*this);
}

void NodeManagementUseCaseData::setUseCaseInformation(
    const std::vector<UseCaseInformationData> &useCaseInformation) {
  m_useCaseInformation = useCaseInformation;
  m_useCaseInformationIsSet = true;
}

const std::vector<UseCaseInformationData> &
NodeManagementUseCaseData::getUseCaseInformation() const {
  return m_useCaseInformation;
}

void NodeManagementUseCaseData::cleanUseCaseInformation() {
  m_useCaseInformation.clear();
  m_useCaseInformationIsSet = false;
}

bool NodeManagementUseCaseData::getUseCaseInformationIsSet() const {
  return m_useCaseInformationIsSet;
}

CmdDataPtr
NodeManagementUseCaseData::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NodeManagementUseCaseData>(*this);
}

bool NodeManagementUseCaseData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"useCaseInformation"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<UseCaseInformationData>(
            static_cast<KeoJsonValue *>(&(*iter)), "useCaseInformation",
            &m_useCaseInformation)) {
      m_useCaseInformationIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementUseCaseData::toJson() const {
  std::string result = "[";
  if (m_useCaseInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<UseCaseInformationData>(
        "useCaseInformation", m_useCaseInformation);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram