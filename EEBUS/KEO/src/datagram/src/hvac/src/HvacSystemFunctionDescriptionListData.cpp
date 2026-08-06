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
#include <keo_datagram/hvac/HvacSystemFunctionDescriptionListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionDescriptionListData::HvacSystemFunctionDescriptionListData()
    : CmdData(), m_hvacSystemFunctionDescriptionDataIsSet(false),
      m_hvacSystemFunctionDescriptionData(
          std::vector<HvacSystemFunctionDescriptionData>())

{}

HvacSystemFunctionDescriptionListData::HvacSystemFunctionDescriptionListData(
    const std::vector<HvacSystemFunctionDescriptionData>
        &c_hvacSystemFunctionDescriptionData) {
  setHvacSystemFunctionDescriptionData(c_hvacSystemFunctionDescriptionData);
}

bool HvacSystemFunctionDescriptionListData::
operator==(const HvacSystemFunctionDescriptionListData &c_classObject) const {
  if (m_hvacSystemFunctionDescriptionDataIsSet !=
          c_classObject.m_hvacSystemFunctionDescriptionDataIsSet ||
      (m_hvacSystemFunctionDescriptionDataIsSet &&
       (m_hvacSystemFunctionDescriptionData !=
        c_classObject.m_hvacSystemFunctionDescriptionData))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionDescriptionListData::
operator!=(const HvacSystemFunctionDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionDescriptionListData::isEmpty() const {
  return !m_hvacSystemFunctionDescriptionDataIsSet;
}

CmdData::Type HvacSystemFunctionDescriptionListData::getDataType() const {
  return CmdData::Type::HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr HvacSystemFunctionDescriptionListData::clone() const {
  return std::make_shared<HvacSystemFunctionDescriptionListData>(*this);
}

void HvacSystemFunctionDescriptionListData::
    setHvacSystemFunctionDescriptionData(
        const std::vector<HvacSystemFunctionDescriptionData>
            &hvacSystemFunctionDescriptionData) {
  m_hvacSystemFunctionDescriptionData = hvacSystemFunctionDescriptionData;
  m_hvacSystemFunctionDescriptionDataIsSet = true;
}

const std::vector<HvacSystemFunctionDescriptionData> &
HvacSystemFunctionDescriptionListData::getHvacSystemFunctionDescriptionData()
    const {
  return m_hvacSystemFunctionDescriptionData;
}

void HvacSystemFunctionDescriptionListData::
    cleanHvacSystemFunctionDescriptionData() {
  m_hvacSystemFunctionDescriptionData.clear();
  m_hvacSystemFunctionDescriptionDataIsSet = false;
}

bool HvacSystemFunctionDescriptionListData::
    getHvacSystemFunctionDescriptionDataIsSet() const {
  return m_hvacSystemFunctionDescriptionDataIsSet;
}

CmdDataPtr HvacSystemFunctionDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<HvacSystemFunctionDescriptionData> dataOut;
  for (const auto &data : getHvacSystemFunctionDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          HvacSystemFunctionDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  HvacSystemFunctionDescriptionListDataSelectors>(
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
          const HvacSystemFunctionDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  HvacSystemFunctionDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(HvacSystemFunctionDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<HvacSystemFunctionDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<HvacSystemFunctionDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<HvacSystemFunctionDescriptionListData>(dataOut);
  } else {
    return std::make_shared<HvacSystemFunctionDescriptionListData>();
  }
}

bool HvacSystemFunctionDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"hvacSystemFunctionDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<HvacSystemFunctionDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "hvacSystemFunctionDescriptionData",
            &m_hvacSystemFunctionDescriptionData)) {
      m_hvacSystemFunctionDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_hvacSystemFunctionDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<HvacSystemFunctionDescriptionData>(
            "hvacSystemFunctionDescriptionData",
            m_hvacSystemFunctionDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram