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

#include <keo_datagram/timeinformation/TimeDistributorData.h>

#include <keo_datagram/timeinformation/TimeDistributorDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeDistributorData::TimeDistributorData()
    : CmdData(), m_isTimeDistributorIsSet(false), m_isTimeDistributor(false),
      m_distributorPriorityIsSet(false), m_distributorPriority(0)

{}

TimeDistributorData::TimeDistributorData(
    const xs_boolean &c_isTimeDistributor,
    const xs_unsignedInt &c_distributorPriority)
    : CmdData(), m_isTimeDistributorIsSet(true),
      m_isTimeDistributor(c_isTimeDistributor),
      m_distributorPriorityIsSet(true),
      m_distributorPriority(c_distributorPriority)

{}

bool TimeDistributorData::
operator==(const TimeDistributorData &c_classObject) const {
  if (m_isTimeDistributorIsSet != c_classObject.m_isTimeDistributorIsSet ||
      (m_isTimeDistributorIsSet &&
       (m_isTimeDistributor != c_classObject.m_isTimeDistributor))) {
    return false;
  }
  if (m_distributorPriorityIsSet != c_classObject.m_distributorPriorityIsSet ||
      (m_distributorPriorityIsSet &&
       (m_distributorPriority != c_classObject.m_distributorPriority))) {
    return false;
  }

  return true;
}

bool TimeDistributorData::
operator!=(const TimeDistributorData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeDistributorData::isEmpty() const {
  return !m_isTimeDistributorIsSet && !m_distributorPriorityIsSet;
}

CmdData::Type TimeDistributorData::getDataType() const {
  return CmdData::Type::TIME_DISTRIBUTOR_DATA_TYPE;
}

CmdDataPtr TimeDistributorData::clone() const {
  return std::make_shared<TimeDistributorData>(*this);
}

void TimeDistributorData::setIsTimeDistributor(
    const xs_boolean &isTimeDistributor) {
  m_isTimeDistributor = isTimeDistributor;
  m_isTimeDistributorIsSet = true;
}

const xs_boolean &TimeDistributorData::getIsTimeDistributor() const {
  return m_isTimeDistributor;
}

void TimeDistributorData::cleanIsTimeDistributor() {
  m_isTimeDistributor = false;
  m_isTimeDistributorIsSet = false;
}

bool TimeDistributorData::getIsTimeDistributorIsSet() const {
  return m_isTimeDistributorIsSet;
}

void TimeDistributorData::setDistributorPriority(
    const xs_unsignedInt &distributorPriority) {
  m_distributorPriority = distributorPriority;
  m_distributorPriorityIsSet = true;
}

const xs_unsignedInt &TimeDistributorData::getDistributorPriority() const {
  return m_distributorPriority;
}

void TimeDistributorData::cleanDistributorPriority() {
  m_distributorPriority = 0;
  m_distributorPriorityIsSet = false;
}

bool TimeDistributorData::getDistributorPriorityIsSet() const {
  return m_distributorPriorityIsSet;
}

CmdDataPtr
TimeDistributorData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      TimeDistributorDataElementsPtr elements =
          std::dynamic_pointer_cast<TimeDistributorDataElements>(
              filter.getDataElements());
      if (elements) {
        TimeDistributorDataPtr dataOut =
            std::make_shared<TimeDistributorData>();
        // TODO make sure to always set identifier

        if (getIsTimeDistributorIsSet() &&
            elements->getIsTimeDistributorIsSet()) {
          dataOut->setIsTimeDistributor(getIsTimeDistributor());
        }

        if (getDistributorPriorityIsSet() &&
            elements->getDistributorPriorityIsSet()) {
          dataOut->setDistributorPriority(getDistributorPriority());
        }

        return dataOut;
      } else {
        return std::make_shared<TimeDistributorData>(*this);
      }
    } else {
      return std::make_shared<TimeDistributorData>(*this);
    }
  } else {
    return std::make_shared<TimeDistributorData>(*this);
  }
}

bool TimeDistributorData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"isTimeDistributor", "distributorPriority"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isTimeDistributor", &m_isTimeDistributor)) {
      m_isTimeDistributorIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "distributorPriority",
                                   &m_distributorPriority)) {
      m_distributorPriorityIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeDistributorData::toJson() const {
  std::string result = "[";
  if (m_isTimeDistributorIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("isTimeDistributor", m_isTimeDistributor);
  }
  if (m_distributorPriorityIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("distributorPriority",
                                           m_distributorPriority);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram