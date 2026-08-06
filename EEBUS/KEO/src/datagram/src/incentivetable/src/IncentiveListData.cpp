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

#include <algorithm>
#include <keo_datagram/incentivetable/IncentiveListData.h>
#include <keo_datagram/incentivetable/IncentiveListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveListData::IncentiveListData()
    : CmdData(), m_incentiveDataIsSet(false),
      m_incentiveData(std::vector<IncentiveData>())

{}

IncentiveListData::IncentiveListData(
    const std::vector<IncentiveData> &c_incentiveData) {
  setIncentiveData(c_incentiveData);
}

bool IncentiveListData::
operator==(const IncentiveListData &c_classObject) const {
  if (m_incentiveDataIsSet != c_classObject.m_incentiveDataIsSet ||
      (m_incentiveDataIsSet &&
       (m_incentiveData != c_classObject.m_incentiveData))) {
    return false;
  }

  return true;
}

bool IncentiveListData::
operator!=(const IncentiveListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveListData::isEmpty() const { return !m_incentiveDataIsSet; }

CmdData::Type IncentiveListData::getDataType() const {
  return CmdData::Type::INCENTIVE_LIST_DATA_TYPE;
}

CmdDataPtr IncentiveListData::clone() const {
  return std::make_shared<IncentiveListData>(*this);
}

void IncentiveListData::setIncentiveData(
    const std::vector<IncentiveData> &incentiveData) {
  m_incentiveData = incentiveData;
  m_incentiveDataIsSet = true;
}

const std::vector<IncentiveData> &IncentiveListData::getIncentiveData() const {
  return m_incentiveData;
}

void IncentiveListData::cleanIncentiveData() {
  m_incentiveData.clear();
  m_incentiveDataIsSet = false;
}

bool IncentiveListData::getIncentiveDataIsSet() const {
  return m_incentiveDataIsSet;
}

CmdDataPtr IncentiveListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<IncentiveData> dataOut;
  for (const auto &data : getIncentiveData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          IncentiveListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<IncentiveListDataSelectors>(
                  baseSelectorsClass);
          if (selectors) {
            if (selectors->selects(data)) {
              // The first selecting selector selects
              isSelected = true;
              break;
            }
          } else {
            // Selectors of wrong type are ignored and don't select anything.
          }
        }
        if (isSelected) {
          const IncentiveDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<IncentiveDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(IncentiveData(data));
          }
        }
      } else {
        return std::make_shared<IncentiveListData>(*this);
      }
    } else {
      return std::make_shared<IncentiveListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<IncentiveListData>(dataOut);
  } else {
    return std::make_shared<IncentiveListData>();
  }
}

bool IncentiveListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"incentiveData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<IncentiveData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveData", &m_incentiveData)) {
      m_incentiveDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveListData::toJson() const {
  std::string result = "[";
  if (m_incentiveDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<IncentiveData>("incentiveData",
                                                              m_incentiveData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram