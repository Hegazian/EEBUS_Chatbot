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

#include <keo_datagram/core/NodeManagementBindingDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementBindingDataElements::NodeManagementBindingDataElements()
    : DataElements(), m_bindingEntryIsSet(false),
      m_bindingEntry(BindingManagementEntryDataElements())

{}

NodeManagementBindingDataElements::NodeManagementBindingDataElements(
    const BindingManagementEntryDataElements &c_bindingEntry) {
  setBindingEntry(c_bindingEntry);
}

bool NodeManagementBindingDataElements::
operator==(const NodeManagementBindingDataElements &c_classObject) const {
  if (m_bindingEntryIsSet != c_classObject.m_bindingEntryIsSet ||
      (m_bindingEntryIsSet &&
       (m_bindingEntry != c_classObject.m_bindingEntry))) {
    return false;
  }

  return true;
}

bool NodeManagementBindingDataElements::
operator!=(const NodeManagementBindingDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementBindingDataElements::isEmpty() const {
  return !m_bindingEntryIsSet;
}

DataElements::Type NodeManagementBindingDataElements::getDataType() const {
  return DataElements::Type::NODE_MANAGEMENT_BINDING_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NodeManagementBindingDataElements::clone() const {
  return std::make_shared<NodeManagementBindingDataElements>(*this);
}

void NodeManagementBindingDataElements::setBindingEntry(
    const BindingManagementEntryDataElements &bindingEntry) {
  m_bindingEntry = bindingEntry;
  m_bindingEntryIsSet = true;
}

const BindingManagementEntryDataElements &
NodeManagementBindingDataElements::getBindingEntry() const {
  return m_bindingEntry;
}

void NodeManagementBindingDataElements::cleanBindingEntry() {
  m_bindingEntry = BindingManagementEntryDataElements();
  m_bindingEntryIsSet = false;
}

bool NodeManagementBindingDataElements::getBindingEntryIsSet() const {
  return m_bindingEntryIsSet;
}

bool NodeManagementBindingDataElements::fromJson(KeoJsonValue *json) {
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

std::string NodeManagementBindingDataElements::toJson() const {
  std::string result = "[";
  if (m_bindingEntryIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("bindingEntry", m_bindingEntry);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram