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

#include <keo_datagram/core/NodeManagementSpecificationVersionList.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementSpecificationVersionList::NodeManagementSpecificationVersionList()
    : m_specificationVersionIsSet(false),
      m_specificationVersion(std::vector<xs_string>())

{}

NodeManagementSpecificationVersionList::NodeManagementSpecificationVersionList(
    const std::vector<xs_string> &c_specificationVersion) {
  setSpecificationVersion(c_specificationVersion);
}

bool NodeManagementSpecificationVersionList::
operator==(const NodeManagementSpecificationVersionList &c_classObject) const {
  if (m_specificationVersionIsSet !=
          c_classObject.m_specificationVersionIsSet ||
      (m_specificationVersionIsSet &&
       (m_specificationVersion != c_classObject.m_specificationVersion))) {
    return false;
  }

  return true;
}

bool NodeManagementSpecificationVersionList::
operator!=(const NodeManagementSpecificationVersionList &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementSpecificationVersionList::isEmpty() const {
  return !m_specificationVersionIsSet;
}

void NodeManagementSpecificationVersionList::setSpecificationVersion(
    const std::vector<xs_string> &specificationVersion) {
  m_specificationVersion = specificationVersion;
  m_specificationVersionIsSet = true;
}

const std::vector<xs_string> &
NodeManagementSpecificationVersionList::getSpecificationVersion() const {
  return m_specificationVersion;
}

void NodeManagementSpecificationVersionList::cleanSpecificationVersion() {
  m_specificationVersion.clear();
  m_specificationVersionIsSet = false;
}

bool NodeManagementSpecificationVersionList::getSpecificationVersionIsSet()
    const {
  return m_specificationVersionIsSet;
}

bool NodeManagementSpecificationVersionList::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"specificationVersion"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<xs_string>(
            static_cast<KeoJsonValue *>(&(*iter)), "specificationVersion",
            &m_specificationVersion)) {
      m_specificationVersionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementSpecificationVersionList::toJson() const {
  std::string result = "[";
  if (m_specificationVersionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_string>(
        "specificationVersion", m_specificationVersion);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram