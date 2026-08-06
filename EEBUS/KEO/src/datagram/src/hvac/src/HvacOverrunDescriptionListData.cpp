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
#include <keo_datagram/hvac/HvacOverrunDescriptionListData.h>
#include <keo_datagram/hvac/HvacOverrunDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOverrunDescriptionListData::HvacOverrunDescriptionListData()
    : CmdData(), m_hvacOverrunDescriptionDataIsSet(false),
      m_hvacOverrunDescriptionData(std::vector<HvacOverrunDescriptionData>())

{}

HvacOverrunDescriptionListData::HvacOverrunDescriptionListData(
    const std::vector<HvacOverrunDescriptionData>
        &c_hvacOverrunDescriptionData) {
  setHvacOverrunDescriptionData(c_hvacOverrunDescriptionData);
}

bool HvacOverrunDescriptionListData::
operator==(const HvacOverrunDescriptionListData &c_classObject) const {
  if (m_hvacOverrunDescriptionDataIsSet !=
          c_classObject.m_hvacOverrunDescriptionDataIsSet ||
      (m_hvacOverrunDescriptionDataIsSet &&
       (m_hvacOverrunDescriptionData !=
        c_classObject.m_hvacOverrunDescriptionData))) {
    return false;
  }

  return true;
}

bool HvacOverrunDescriptionListData::
operator!=(const HvacOverrunDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOverrunDescriptionListData::isEmpty() const {
  return !m_hvacOverrunDescriptionDataIsSet;
}

CmdData::Type HvacOverrunDescriptionListData::getDataType() const {
  return CmdData::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr HvacOverrunDescriptionListData::clone() const {
  return std::make_shared<HvacOverrunDescriptionListData>(*this);
}

void HvacOverrunDescriptionListData::setHvacOverrunDescriptionData(
    const std::vector<HvacOverrunDescriptionData> &hvacOverrunDescriptionData) {
  m_hvacOverrunDescriptionData = hvacOverrunDescriptionData;
  m_hvacOverrunDescriptionDataIsSet = true;
}

const std::vector<HvacOverrunDescriptionData> &
HvacOverrunDescriptionListData::getHvacOverrunDescriptionData() const {
  return m_hvacOverrunDescriptionData;
}

void HvacOverrunDescriptionListData::cleanHvacOverrunDescriptionData() {
  m_hvacOverrunDescriptionData.clear();
  m_hvacOverrunDescriptionDataIsSet = false;
}

bool HvacOverrunDescriptionListData::getHvacOverrunDescriptionDataIsSet()
    const {
  return m_hvacOverrunDescriptionDataIsSet;
}

CmdDataPtr HvacOverrunDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<HvacOverrunDescriptionData> dataOut;
  for (const auto &data : getHvacOverrunDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          HvacOverrunDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  HvacOverrunDescriptionListDataSelectors>(baseSelectorsClass);
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
          const HvacOverrunDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<HvacOverrunDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(HvacOverrunDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<HvacOverrunDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<HvacOverrunDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<HvacOverrunDescriptionListData>(dataOut);
  } else {
    return std::make_shared<HvacOverrunDescriptionListData>();
  }
}

bool HvacOverrunDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"hvacOverrunDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<HvacOverrunDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "hvacOverrunDescriptionData",
            &m_hvacOverrunDescriptionData)) {
      m_hvacOverrunDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacOverrunDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_hvacOverrunDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<HvacOverrunDescriptionData>(
        "hvacOverrunDescriptionData", m_hvacOverrunDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram