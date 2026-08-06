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

#include <keo_datagram/core/NodeManagementBindingRequestCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementBindingRequestCallElements::
    NodeManagementBindingRequestCallElements()
    : DataElements(), m_bindingRequestIsSet(false),
      m_bindingRequest(BindingManagementRequestCallElements())

{}

NodeManagementBindingRequestCallElements::
    NodeManagementBindingRequestCallElements(
        const BindingManagementRequestCallElements &c_bindingRequest) {
  setBindingRequest(c_bindingRequest);
}

bool NodeManagementBindingRequestCallElements::operator==(
    const NodeManagementBindingRequestCallElements &c_classObject) const {
  if (m_bindingRequestIsSet != c_classObject.m_bindingRequestIsSet ||
      (m_bindingRequestIsSet &&
       (m_bindingRequest != c_classObject.m_bindingRequest))) {
    return false;
  }

  return true;
}

bool NodeManagementBindingRequestCallElements::operator!=(
    const NodeManagementBindingRequestCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementBindingRequestCallElements::isEmpty() const {
  return !m_bindingRequestIsSet;
}

DataElements::Type
NodeManagementBindingRequestCallElements::getDataType() const {
  return DataElements::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_ELEMENTS_TYPE;
}

DataElementsPtr NodeManagementBindingRequestCallElements::clone() const {
  return std::make_shared<NodeManagementBindingRequestCallElements>(*this);
}

void NodeManagementBindingRequestCallElements::setBindingRequest(
    const BindingManagementRequestCallElements &bindingRequest) {
  m_bindingRequest = bindingRequest;
  m_bindingRequestIsSet = true;
}

const BindingManagementRequestCallElements &
NodeManagementBindingRequestCallElements::getBindingRequest() const {
  return m_bindingRequest;
}

void NodeManagementBindingRequestCallElements::cleanBindingRequest() {
  m_bindingRequest = BindingManagementRequestCallElements();
  m_bindingRequestIsSet = false;
}

bool NodeManagementBindingRequestCallElements::getBindingRequestIsSet() const {
  return m_bindingRequestIsSet;
}

bool NodeManagementBindingRequestCallElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"bindingRequest"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "bindingRequest", &m_bindingRequest)) {
      m_bindingRequestIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementBindingRequestCallElements::toJson() const {
  std::string result = "[";
  if (m_bindingRequestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("bindingRequest", m_bindingRequest);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram