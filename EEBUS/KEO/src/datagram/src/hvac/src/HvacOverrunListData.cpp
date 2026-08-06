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
#include <keo_datagram/hvac/HvacOverrunListData.h>
#include <keo_datagram/hvac/HvacOverrunListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOverrunListData::HvacOverrunListData()
    : CmdData(), m_hvacOverrunDataIsSet(false),
      m_hvacOverrunData(std::vector<HvacOverrunData>())

{}

HvacOverrunListData::HvacOverrunListData(
    const std::vector<HvacOverrunData> &c_hvacOverrunData) {
  setHvacOverrunData(c_hvacOverrunData);
}

bool HvacOverrunListData::
operator==(const HvacOverrunListData &c_classObject) const {
  if (m_hvacOverrunDataIsSet != c_classObject.m_hvacOverrunDataIsSet ||
      (m_hvacOverrunDataIsSet &&
       (m_hvacOverrunData != c_classObject.m_hvacOverrunData))) {
    return false;
  }

  return true;
}

bool HvacOverrunListData::
operator!=(const HvacOverrunListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOverrunListData::isEmpty() const { return !m_hvacOverrunDataIsSet; }

CmdData::Type HvacOverrunListData::getDataType() const {
  return CmdData::Type::HVAC_OVERRUN_LIST_DATA_TYPE;
}

CmdDataPtr HvacOverrunListData::clone() const {
  return std::make_shared<HvacOverrunListData>(*this);
}

void HvacOverrunListData::setHvacOverrunData(
    const std::vector<HvacOverrunData> &hvacOverrunData) {
  m_hvacOverrunData = hvacOverrunData;
  m_hvacOverrunDataIsSet = true;
}

const std::vector<HvacOverrunData> &
HvacOverrunListData::getHvacOverrunData() const {
  return m_hvacOverrunData;
}

void HvacOverrunListData::cleanHvacOverrunData() {
  m_hvacOverrunData.clear();
  m_hvacOverrunDataIsSet = false;
}

bool HvacOverrunListData::getHvacOverrunDataIsSet() const {
  return m_hvacOverrunDataIsSet;
}

CmdDataPtr
HvacOverrunListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<HvacOverrunData> dataOut;
  for (const auto &data : getHvacOverrunData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          HvacOverrunListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<HvacOverrunListDataSelectors>(
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
          const HvacOverrunDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<HvacOverrunDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(HvacOverrunData(data));
          }
        }
      } else {
        return std::make_shared<HvacOverrunListData>(*this);
      }
    } else {
      return std::make_shared<HvacOverrunListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<HvacOverrunListData>(dataOut);
  } else {
    return std::make_shared<HvacOverrunListData>();
  }
}

bool HvacOverrunListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"hvacOverrunData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<HvacOverrunData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "hvacOverrunData", &m_hvacOverrunData)) {
      m_hvacOverrunDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacOverrunListData::toJson() const {
  std::string result = "[";
  if (m_hvacOverrunDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<HvacOverrunData>(
        "hvacOverrunData", m_hvacOverrunData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram