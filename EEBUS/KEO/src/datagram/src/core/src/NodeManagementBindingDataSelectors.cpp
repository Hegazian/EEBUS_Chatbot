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

#include <keo_datagram/core/NodeManagementBindingDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementBindingDataSelectors::NodeManagementBindingDataSelectors()
    : DataSelectors(), m_bindingEntryIsSet(false),
      m_bindingEntry(BindingManagementEntryListDataSelectors())

{}

NodeManagementBindingDataSelectors::NodeManagementBindingDataSelectors(
    const BindingManagementEntryListDataSelectors &c_bindingEntry) {
  setBindingEntry(c_bindingEntry);
}

bool NodeManagementBindingDataSelectors::
operator==(const NodeManagementBindingDataSelectors &c_classObject) const {
  if (m_bindingEntryIsSet != c_classObject.m_bindingEntryIsSet ||
      (m_bindingEntryIsSet &&
       (m_bindingEntry != c_classObject.m_bindingEntry))) {
    return false;
  }

  return true;
}

bool NodeManagementBindingDataSelectors::
operator!=(const NodeManagementBindingDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementBindingDataSelectors::isEmpty() const {
  return !m_bindingEntryIsSet;
}

DataSelectors::Type NodeManagementBindingDataSelectors::getDataType() const {
  return DataSelectors::Type::NODE_MANAGEMENT_BINDING_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr NodeManagementBindingDataSelectors::clone() const {
  return std::make_shared<NodeManagementBindingDataSelectors>(*this);
}

void NodeManagementBindingDataSelectors::setBindingEntry(
    const BindingManagementEntryListDataSelectors &bindingEntry) {
  m_bindingEntry = bindingEntry;
  m_bindingEntryIsSet = true;
}

const BindingManagementEntryListDataSelectors &
NodeManagementBindingDataSelectors::getBindingEntry() const {
  return m_bindingEntry;
}

void NodeManagementBindingDataSelectors::cleanBindingEntry() {
  m_bindingEntry = BindingManagementEntryListDataSelectors();
  m_bindingEntryIsSet = false;
}

bool NodeManagementBindingDataSelectors::getBindingEntryIsSet() const {
  return m_bindingEntryIsSet;
}

bool NodeManagementBindingDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"bindingEntry"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "bindingEntry", &m_bindingEntry)) {
      m_bindingEntryIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementBindingDataSelectors::toJson() const {
  std::string result = "[";
  if (m_bindingEntryIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("bindingEntry", m_bindingEntry);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram