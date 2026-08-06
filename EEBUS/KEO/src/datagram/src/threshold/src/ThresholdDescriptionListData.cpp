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
#include <keo_datagram/threshold/ThresholdDescriptionListData.h>
#include <keo_datagram/threshold/ThresholdDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdDescriptionListData::ThresholdDescriptionListData()
    : CmdData(), m_thresholdDescriptionDataIsSet(false),
      m_thresholdDescriptionData(std::vector<ThresholdDescriptionData>())

{}

ThresholdDescriptionListData::ThresholdDescriptionListData(
    const std::vector<ThresholdDescriptionData> &c_thresholdDescriptionData) {
  setThresholdDescriptionData(c_thresholdDescriptionData);
}

bool ThresholdDescriptionListData::
operator==(const ThresholdDescriptionListData &c_classObject) const {
  if (m_thresholdDescriptionDataIsSet !=
          c_classObject.m_thresholdDescriptionDataIsSet ||
      (m_thresholdDescriptionDataIsSet &&
       (m_thresholdDescriptionData !=
        c_classObject.m_thresholdDescriptionData))) {
    return false;
  }

  return true;
}

bool ThresholdDescriptionListData::
operator!=(const ThresholdDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdDescriptionListData::isEmpty() const {
  return !m_thresholdDescriptionDataIsSet;
}

CmdData::Type ThresholdDescriptionListData::getDataType() const {
  return CmdData::Type::THRESHOLD_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr ThresholdDescriptionListData::clone() const {
  return std::make_shared<ThresholdDescriptionListData>(*this);
}

void ThresholdDescriptionListData::setThresholdDescriptionData(
    const std::vector<ThresholdDescriptionData> &thresholdDescriptionData) {
  m_thresholdDescriptionData = thresholdDescriptionData;
  m_thresholdDescriptionDataIsSet = true;
}

const std::vector<ThresholdDescriptionData> &
ThresholdDescriptionListData::getThresholdDescriptionData() const {
  return m_thresholdDescriptionData;
}

void ThresholdDescriptionListData::cleanThresholdDescriptionData() {
  m_thresholdDescriptionData.clear();
  m_thresholdDescriptionDataIsSet = false;
}

bool ThresholdDescriptionListData::getThresholdDescriptionDataIsSet() const {
  return m_thresholdDescriptionDataIsSet;
}

CmdDataPtr
ThresholdDescriptionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<ThresholdDescriptionData> dataOut;
  for (const auto &data : getThresholdDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          ThresholdDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<ThresholdDescriptionListDataSelectors>(
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
          const ThresholdDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<ThresholdDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(ThresholdDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<ThresholdDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<ThresholdDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<ThresholdDescriptionListData>(dataOut);
  } else {
    return std::make_shared<ThresholdDescriptionListData>();
  }
}

bool ThresholdDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"thresholdDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<ThresholdDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "thresholdDescriptionData",
            &m_thresholdDescriptionData)) {
      m_thresholdDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ThresholdDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_thresholdDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<ThresholdDescriptionData>(
        "thresholdDescriptionData", m_thresholdDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram