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
#include <keo_datagram/incentivetable/IncentiveDescriptionListData.h>
#include <keo_datagram/incentivetable/IncentiveDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveDescriptionListData::IncentiveDescriptionListData()
    : CmdData(), m_incentiveDescriptionDataIsSet(false),
      m_incentiveDescriptionData(std::vector<IncentiveDescriptionData>())

{}

IncentiveDescriptionListData::IncentiveDescriptionListData(
    const std::vector<IncentiveDescriptionData> &c_incentiveDescriptionData) {
  setIncentiveDescriptionData(c_incentiveDescriptionData);
}

bool IncentiveDescriptionListData::
operator==(const IncentiveDescriptionListData &c_classObject) const {
  if (m_incentiveDescriptionDataIsSet !=
          c_classObject.m_incentiveDescriptionDataIsSet ||
      (m_incentiveDescriptionDataIsSet &&
       (m_incentiveDescriptionData !=
        c_classObject.m_incentiveDescriptionData))) {
    return false;
  }

  return true;
}

bool IncentiveDescriptionListData::
operator!=(const IncentiveDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveDescriptionListData::isEmpty() const {
  return !m_incentiveDescriptionDataIsSet;
}

CmdData::Type IncentiveDescriptionListData::getDataType() const {
  return CmdData::Type::INCENTIVE_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr IncentiveDescriptionListData::clone() const {
  return std::make_shared<IncentiveDescriptionListData>(*this);
}

void IncentiveDescriptionListData::setIncentiveDescriptionData(
    const std::vector<IncentiveDescriptionData> &incentiveDescriptionData) {
  m_incentiveDescriptionData = incentiveDescriptionData;
  m_incentiveDescriptionDataIsSet = true;
}

const std::vector<IncentiveDescriptionData> &
IncentiveDescriptionListData::getIncentiveDescriptionData() const {
  return m_incentiveDescriptionData;
}

void IncentiveDescriptionListData::cleanIncentiveDescriptionData() {
  m_incentiveDescriptionData.clear();
  m_incentiveDescriptionDataIsSet = false;
}

bool IncentiveDescriptionListData::getIncentiveDescriptionDataIsSet() const {
  return m_incentiveDescriptionDataIsSet;
}

CmdDataPtr
IncentiveDescriptionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<IncentiveDescriptionData> dataOut;
  for (const auto &data : getIncentiveDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          IncentiveDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<IncentiveDescriptionListDataSelectors>(
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
          const IncentiveDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<IncentiveDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(IncentiveDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<IncentiveDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<IncentiveDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<IncentiveDescriptionListData>(dataOut);
  } else {
    return std::make_shared<IncentiveDescriptionListData>();
  }
}

bool IncentiveDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"incentiveDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<IncentiveDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "incentiveDescriptionData",
            &m_incentiveDescriptionData)) {
      m_incentiveDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_incentiveDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<IncentiveDescriptionData>(
        "incentiveDescriptionData", m_incentiveDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram