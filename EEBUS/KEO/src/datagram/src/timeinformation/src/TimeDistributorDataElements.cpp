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

#include <keo_datagram/timeinformation/TimeDistributorDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeDistributorDataElements::TimeDistributorDataElements()
    : DataElements(), m_isTimeDistributorIsSet(false),
      m_distributorPriorityIsSet(false)

{}

TimeDistributorDataElements::TimeDistributorDataElements(
    xs_boolean c_isTimeDistributorIsSet, xs_boolean c_distributorPriorityIsSet)
    : DataElements(), m_isTimeDistributorIsSet(c_isTimeDistributorIsSet),
      m_distributorPriorityIsSet(c_distributorPriorityIsSet)

{}

bool TimeDistributorDataElements::
operator==(const TimeDistributorDataElements &c_classObject) const {
  if (m_isTimeDistributorIsSet != c_classObject.m_isTimeDistributorIsSet) {
    return false;
  }
  if (m_distributorPriorityIsSet != c_classObject.m_distributorPriorityIsSet) {
    return false;
  }

  return true;
}

bool TimeDistributorDataElements::
operator!=(const TimeDistributorDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeDistributorDataElements::isEmpty() const {
  return !m_isTimeDistributorIsSet && !m_distributorPriorityIsSet;
}

DataElements::Type TimeDistributorDataElements::getDataType() const {
  return DataElements::Type::TIME_DISTRIBUTOR_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimeDistributorDataElements::clone() const {
  return std::make_shared<TimeDistributorDataElements>(*this);
}

void TimeDistributorDataElements::setIsTimeDistributor() {
  m_isTimeDistributorIsSet = true;
}

void TimeDistributorDataElements::cleanIsTimeDistributor() {
  m_isTimeDistributorIsSet = false;
}

bool TimeDistributorDataElements::getIsTimeDistributorIsSet() const {
  return m_isTimeDistributorIsSet;
}

void TimeDistributorDataElements::setDistributorPriority() {
  m_distributorPriorityIsSet = true;
}

void TimeDistributorDataElements::cleanDistributorPriority() {
  m_distributorPriorityIsSet = false;
}

bool TimeDistributorDataElements::getDistributorPriorityIsSet() const {
  return m_distributorPriorityIsSet;
}

bool TimeDistributorDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"isTimeDistributor", "distributorPriority"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isTimeDistributor")) {
      m_isTimeDistributorIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "distributorPriority")) {
      m_distributorPriorityIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeDistributorDataElements::toJson() const {
  std::string result = "[";
  if (m_isTimeDistributorIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isTimeDistributor");
  }
  if (m_distributorPriorityIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("distributorPriority");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram