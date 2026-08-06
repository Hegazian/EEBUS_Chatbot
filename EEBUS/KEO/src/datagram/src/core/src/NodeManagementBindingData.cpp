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

#include <keo_datagram/core/NodeManagementBindingData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementBindingData::NodeManagementBindingData()
    : CmdData(), m_bindingEntryIsSet(false),
      m_bindingEntry(std::vector<BindingManagementEntryData>())

{}

NodeManagementBindingData::NodeManagementBindingData(
    const std::vector<BindingManagementEntryData> &c_bindingEntry) {
  setBindingEntry(c_bindingEntry);
}

bool NodeManagementBindingData::
operator==(const NodeManagementBindingData &c_classObject) const {
  if (m_bindingEntryIsSet != c_classObject.m_bindingEntryIsSet ||
      (m_bindingEntryIsSet &&
       (m_bindingEntry != c_classObject.m_bindingEntry))) {
    return false;
  }

  return true;
}

bool NodeManagementBindingData::
operator!=(const NodeManagementBindingData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementBindingData::isEmpty() const { return !m_bindingEntryIsSet; }

CmdData::Type NodeManagementBindingData::getDataType() const {
  return CmdData::Type::NODE_MANAGEMENT_BINDING_DATA_TYPE;
}

CmdDataPtr NodeManagementBindingData::clone() const {
  return std::make_shared<NodeManagementBindingData>(*this);
}

void NodeManagementBindingData::setBindingEntry(
    const std::vector<BindingManagementEntryData> &bindingEntry) {
  m_bindingEntry = bindingEntry;
  m_bindingEntryIsSet = true;
}

const std::vector<BindingManagementEntryData> &
NodeManagementBindingData::getBindingEntry() const {
  return m_bindingEntry;
}

void NodeManagementBindingData::cleanBindingEntry() {
  m_bindingEntry.clear();
  m_bindingEntryIsSet = false;
}

bool NodeManagementBindingData::getBindingEntryIsSet() const {
  return m_bindingEntryIsSet;
}

CmdDataPtr
NodeManagementBindingData::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NodeManagementBindingData>(*this);
}

bool NodeManagementBindingData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"bindingEntry"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<BindingManagementEntryData>(
            static_cast<KeoJsonValue *>(&(*iter)), "bindingEntry",
            &m_bindingEntry)) {
      m_bindingEntryIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementBindingData::toJson() const {
  std::string result = "[";
  if (m_bindingEntryIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<BindingManagementEntryData>(
        "bindingEntry", m_bindingEntry);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram