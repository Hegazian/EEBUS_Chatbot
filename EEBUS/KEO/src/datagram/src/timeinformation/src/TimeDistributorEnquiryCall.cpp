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

#include <keo_datagram/timeinformation/TimeDistributorEnquiryCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeDistributorEnquiryCall::TimeDistributorEnquiryCall()
    : CmdData()

{}

bool TimeDistributorEnquiryCall::
operator==(const TimeDistributorEnquiryCall &c_classObject) const {

  (void)c_classObject;

  return true;
}

bool TimeDistributorEnquiryCall::
operator!=(const TimeDistributorEnquiryCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeDistributorEnquiryCall::isEmpty() const { return false; }

CmdData::Type TimeDistributorEnquiryCall::getDataType() const {
  return CmdData::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_TYPE;
}

CmdDataPtr TimeDistributorEnquiryCall::clone() const {
  return std::make_shared<TimeDistributorEnquiryCall>(*this);
}

CmdDataPtr
TimeDistributorEnquiryCall::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<TimeDistributorEnquiryCall>(*this);
}

bool TimeDistributorEnquiryCall::fromJson(KeoJsonValue *json) {
  (void)json;
  return true;
}

std::string TimeDistributorEnquiryCall::toJson() const {
  std::string result = "[";
  result += "]";
  return result;
}

} // namespace keo_datagram