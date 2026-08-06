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
#include <keo_datagram/threshold/ThresholdConstraintsListData.h>
#include <keo_datagram/threshold/ThresholdConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdConstraintsListData::ThresholdConstraintsListData()
    : CmdData(), m_thresholdConstraintsDataIsSet(false),
      m_thresholdConstraintsData(std::vector<ThresholdConstraintsData>())

{}

ThresholdConstraintsListData::ThresholdConstraintsListData(
    const std::vector<ThresholdConstraintsData> &c_thresholdConstraintsData) {
  setThresholdConstraintsData(c_thresholdConstraintsData);
}

bool ThresholdConstraintsListData::
operator==(const ThresholdConstraintsListData &c_classObject) const {
  if (m_thresholdConstraintsDataIsSet !=
          c_classObject.m_thresholdConstraintsDataIsSet ||
      (m_thresholdConstraintsDataIsSet &&
       (m_thresholdConstraintsData !=
        c_classObject.m_thresholdConstraintsData))) {
    return false;
  }

  return true;
}

bool ThresholdConstraintsListData::
operator!=(const ThresholdConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdConstraintsListData::isEmpty() const {
  return !m_thresholdConstraintsDataIsSet;
}

CmdData::Type ThresholdConstraintsListData::getDataType() const {
  return CmdData::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr ThresholdConstraintsListData::clone() const {
  return std::make_shared<ThresholdConstraintsListData>(*this);
}

void ThresholdConstraintsListData::setThresholdConstraintsData(
    const std::vector<ThresholdConstraintsData> &thresholdConstraintsData) {
  m_thresholdConstraintsData = thresholdConstraintsData;
  m_thresholdConstraintsDataIsSet = true;
}

const std::vector<ThresholdConstraintsData> &
ThresholdConstraintsListData::getThresholdConstraintsData() const {
  return m_thresholdConstraintsData;
}

void ThresholdConstraintsListData::cleanThresholdConstraintsData() {
  m_thresholdConstraintsData.clear();
  m_thresholdConstraintsDataIsSet = false;
}

bool ThresholdConstraintsListData::getThresholdConstraintsDataIsSet() const {
  return m_thresholdConstraintsDataIsSet;
}

CmdDataPtr
ThresholdConstraintsListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<ThresholdConstraintsData> dataOut;
  for (const auto &data : getThresholdConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          ThresholdConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<ThresholdConstraintsListDataSelectors>(
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
          const ThresholdConstraintsDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<ThresholdConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(ThresholdConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<ThresholdConstraintsListData>(*this);
      }
    } else {
      return std::make_shared<ThresholdConstraintsListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<ThresholdConstraintsListData>(dataOut);
  } else {
    return std::make_shared<ThresholdConstraintsListData>();
  }
}

bool ThresholdConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"thresholdConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<ThresholdConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)), "thresholdConstraintsData",
            &m_thresholdConstraintsData)) {
      m_thresholdConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ThresholdConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_thresholdConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<ThresholdConstraintsData>(
        "thresholdConstraintsData", m_thresholdConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram