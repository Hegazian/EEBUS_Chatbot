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

#include <keo_datagram/core/NodeManagementBindingRequestCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementBindingRequestCall::NodeManagementBindingRequestCall()
    : CmdData(), m_bindingRequestIsSet(false),
      m_bindingRequest(BindingManagementRequestCall())

{}

NodeManagementBindingRequestCall::NodeManagementBindingRequestCall(
    const BindingManagementRequestCall &c_bindingRequest) {
  setBindingRequest(c_bindingRequest);
}

bool NodeManagementBindingRequestCall::
operator==(const NodeManagementBindingRequestCall &c_classObject) const {
  if (m_bindingRequestIsSet != c_classObject.m_bindingRequestIsSet ||
      (m_bindingRequestIsSet &&
       (m_bindingRequest != c_classObject.m_bindingRequest))) {
    return false;
  }

  return true;
}

bool NodeManagementBindingRequestCall::
operator!=(const NodeManagementBindingRequestCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementBindingRequestCall::isEmpty() const {
  return !m_bindingRequestIsSet;
}

CmdData::Type NodeManagementBindingRequestCall::getDataType() const {
  return CmdData::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE;
}

CmdDataPtr NodeManagementBindingRequestCall::clone() const {
  return std::make_shared<NodeManagementBindingRequestCall>(*this);
}

void NodeManagementBindingRequestCall::setBindingRequest(
    const BindingManagementRequestCall &bindingRequest) {
  m_bindingRequest = bindingRequest;
  m_bindingRequestIsSet = true;
}

const BindingManagementRequestCall &
NodeManagementBindingRequestCall::getBindingRequest() const {
  return m_bindingRequest;
}

void NodeManagementBindingRequestCall::cleanBindingRequest() {
  m_bindingRequest = BindingManagementRequestCall();
  m_bindingRequestIsSet = false;
}

bool NodeManagementBindingRequestCall::getBindingRequestIsSet() const {
  return m_bindingRequestIsSet;
}

CmdDataPtr NodeManagementBindingRequestCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NodeManagementBindingRequestCall>(*this);
}

bool NodeManagementBindingRequestCall::fromJson(KeoJsonValue *json) {
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

std::string NodeManagementBindingRequestCall::toJson() const {
  std::string result = "[";
  if (m_bindingRequestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("bindingRequest", m_bindingRequest);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram