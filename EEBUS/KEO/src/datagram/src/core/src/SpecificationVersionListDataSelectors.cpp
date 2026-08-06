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

#include <keo_datagram/core/SpecificationVersionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SpecificationVersionListDataSelectors::SpecificationVersionListDataSelectors()
    : DataSelectors()

{}

bool SpecificationVersionListDataSelectors::
operator==(const SpecificationVersionListDataSelectors &c_classObject) const {

  (void)c_classObject;

  return true;
}

bool SpecificationVersionListDataSelectors::
operator!=(const SpecificationVersionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SpecificationVersionListDataSelectors::isEmpty() const { return false; }

DataSelectors::Type SpecificationVersionListDataSelectors::getDataType() const {
  return DataSelectors::Type::SPECIFICATION_VERSION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SpecificationVersionListDataSelectors::clone() const {
  return std::make_shared<SpecificationVersionListDataSelectors>(*this);
}

bool SpecificationVersionListDataSelectors::selects(
    const xs_string &data) const {
  // A selector without members always selects
  (void)data;
  return true;
}

bool SpecificationVersionListDataSelectors::fromJson(KeoJsonValue *json) {
  (void)json;
  return true;
}

std::string SpecificationVersionListDataSelectors::toJson() const {
  std::string result = "[";
  result += "]";
  return result;
}

} // namespace keo_datagram