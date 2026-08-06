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
#include <keo_datagram/threshold/ThresholdListData.h>
#include <keo_datagram/threshold/ThresholdListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdListData::ThresholdListData()
    : CmdData(), m_thresholdDataIsSet(false),
      m_thresholdData(std::vector<ThresholdData>())

{}

ThresholdListData::ThresholdListData(
    const std::vector<ThresholdData> &c_thresholdData) {
  setThresholdData(c_thresholdData);
}

bool ThresholdListData::
operator==(const ThresholdListData &c_classObject) const {
  if (m_thresholdDataIsSet != c_classObject.m_thresholdDataIsSet ||
      (m_thresholdDataIsSet &&
       (m_thresholdData != c_classObject.m_thresholdData))) {
    return false;
  }

  return true;
}

bool ThresholdListData::
operator!=(const ThresholdListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdListData::isEmpty() const { return !m_thresholdDataIsSet; }

CmdData::Type ThresholdListData::getDataType() const {
  return CmdData::Type::THRESHOLD_LIST_DATA_TYPE;
}

CmdDataPtr ThresholdListData::clone() const {
  return std::make_shared<ThresholdListData>(*this);
}

void ThresholdListData::setThresholdData(
    const std::vector<ThresholdData> &thresholdData) {
  m_thresholdData = thresholdData;
  m_thresholdDataIsSet = true;
}

const std::vector<ThresholdData> &ThresholdListData::getThresholdData() const {
  return m_thresholdData;
}

void ThresholdListData::cleanThresholdData() {
  m_thresholdData.clear();
  m_thresholdDataIsSet = false;
}

bool ThresholdListData::getThresholdDataIsSet() const {
  return m_thresholdDataIsSet;
}

CmdDataPtr ThresholdListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<ThresholdData> dataOut;
  for (const auto &data : getThresholdData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          ThresholdListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<ThresholdListDataSelectors>(
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
          const ThresholdDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<ThresholdDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(ThresholdData(data));
          }
        }
      } else {
        return std::make_shared<ThresholdListData>(*this);
      }
    } else {
      return std::make_shared<ThresholdListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<ThresholdListData>(dataOut);
  } else {
    return std::make_shared<ThresholdListData>();
  }
}

bool ThresholdListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"thresholdData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<ThresholdData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdData", &m_thresholdData)) {
      m_thresholdDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ThresholdListData::toJson() const {
  std::string result = "[";
  if (m_thresholdDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<ThresholdData>("thresholdData",
                                                              m_thresholdData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram