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

#include <keo_datagram/core/NodeManagementBindingDeleteCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementBindingDeleteCallElements::
    NodeManagementBindingDeleteCallElements()
    : DataElements(), m_bindingDeleteIsSet(false),
      m_bindingDelete(BindingManagementDeleteCallElements())

{}

NodeManagementBindingDeleteCallElements::
    NodeManagementBindingDeleteCallElements(
        const BindingManagementDeleteCallElements &c_bindingDelete) {
  setBindingDelete(c_bindingDelete);
}

bool NodeManagementBindingDeleteCallElements::
operator==(const NodeManagementBindingDeleteCallElements &c_classObject) const {
  if (m_bindingDeleteIsSet != c_classObject.m_bindingDeleteIsSet ||
      (m_bindingDeleteIsSet &&
       (m_bindingDelete != c_classObject.m_bindingDelete))) {
    return false;
  }

  return true;
}

bool NodeManagementBindingDeleteCallElements::
operator!=(const NodeManagementBindingDeleteCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementBindingDeleteCallElements::isEmpty() const {
  return !m_bindingDeleteIsSet;
}

DataElements::Type
NodeManagementBindingDeleteCallElements::getDataType() const {
  return DataElements::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_ELEMENTS_TYPE;
}

DataElementsPtr NodeManagementBindingDeleteCallElements::clone() const {
  return std::make_shared<NodeManagementBindingDeleteCallElements>(*this);
}

void NodeManagementBindingDeleteCallElements::setBindingDelete(
    const BindingManagementDeleteCallElements &bindingDelete) {
  m_bindingDelete = bindingDelete;
  m_bindingDeleteIsSet = true;
}

const BindingManagementDeleteCallElements &
NodeManagementBindingDeleteCallElements::getBindingDelete() const {
  return m_bindingDelete;
}

void NodeManagementBindingDeleteCallElements::cleanBindingDelete() {
  m_bindingDelete = BindingManagementDeleteCallElements();
  m_bindingDeleteIsSet = false;
}

bool NodeManagementBindingDeleteCallElements::getBindingDeleteIsSet() const {
  return m_bindingDeleteIsSet;
}

bool NodeManagementBindingDeleteCallElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"bindingDelete"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "bindingDelete", &m_bindingDelete)) {
      m_bindingDeleteIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementBindingDeleteCallElements::toJson() const {
  std::string result = "[";
  if (m_bindingDeleteIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("bindingDelete", m_bindingDelete);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram