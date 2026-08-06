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

#include <keo_datagram/core/NetworkManagementAbortCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementAbortCall::NetworkManagementAbortCall()
    : CmdData()

{}

bool NetworkManagementAbortCall::
operator==(const NetworkManagementAbortCall &c_classObject) const {

  (void)c_classObject;

  return true;
}

bool NetworkManagementAbortCall::
operator!=(const NetworkManagementAbortCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementAbortCall::isEmpty() const { return false; }

CmdData::Type NetworkManagementAbortCall::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_ABORT_CALL_TYPE;
}

CmdDataPtr NetworkManagementAbortCall::clone() const {
  return std::make_shared<NetworkManagementAbortCall>(*this);
}

CmdDataPtr
NetworkManagementAbortCall::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementAbortCall>(*this);
}

bool NetworkManagementAbortCall::fromJson(KeoJsonValue *json) {
  (void)json;
  return true;
}

std::string NetworkManagementAbortCall::toJson() const {
  std::string result = "[";
  result += "]";
  return result;
}

} // namespace keo_datagram