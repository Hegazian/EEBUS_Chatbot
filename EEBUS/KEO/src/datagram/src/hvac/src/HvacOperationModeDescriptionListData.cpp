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
#include <keo_datagram/hvac/HvacOperationModeDescriptionListData.h>
#include <keo_datagram/hvac/HvacOperationModeDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOperationModeDescriptionListData::HvacOperationModeDescriptionListData()
    : CmdData(), m_hvacOperationModeDescriptionDataIsSet(false),
      m_hvacOperationModeDescriptionData(
          std::vector<HvacOperationModeDescriptionData>())

{}

HvacOperationModeDescriptionListData::HvacOperationModeDescriptionListData(
    const std::vector<HvacOperationModeDescriptionData>
        &c_hvacOperationModeDescriptionData) {
  setHvacOperationModeDescriptionData(c_hvacOperationModeDescriptionData);
}

bool HvacOperationModeDescriptionListData::
operator==(const HvacOperationModeDescriptionListData &c_classObject) const {
  if (m_hvacOperationModeDescriptionDataIsSet !=
          c_classObject.m_hvacOperationModeDescriptionDataIsSet ||
      (m_hvacOperationModeDescriptionDataIsSet &&
       (m_hvacOperationModeDescriptionData !=
        c_classObject.m_hvacOperationModeDescriptionData))) {
    return false;
  }

  return true;
}

bool HvacOperationModeDescriptionListData::
operator!=(const HvacOperationModeDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOperationModeDescriptionListData::isEmpty() const {
  return !m_hvacOperationModeDescriptionDataIsSet;
}

CmdData::Type HvacOperationModeDescriptionListData::getDataType() const {
  return CmdData::Type::HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr HvacOperationModeDescriptionListData::clone() const {
  return std::make_shared<HvacOperationModeDescriptionListData>(*this);
}

void HvacOperationModeDescriptionListData::setHvacOperationModeDescriptionData(
    const std::vector<HvacOperationModeDescriptionData>
        &hvacOperationModeDescriptionData) {
  m_hvacOperationModeDescriptionData = hvacOperationModeDescriptionData;
  m_hvacOperationModeDescriptionDataIsSet = true;
}

const std::vector<HvacOperationModeDescriptionData> &
HvacOperationModeDescriptionListData::getHvacOperationModeDescriptionData()
    const {
  return m_hvacOperationModeDescriptionData;
}

void HvacOperationModeDescriptionListData::
    cleanHvacOperationModeDescriptionData() {
  m_hvacOperationModeDescriptionData.clear();
  m_hvacOperationModeDescriptionDataIsSet = false;
}

bool HvacOperationModeDescriptionListData::
    getHvacOperationModeDescriptionDataIsSet() const {
  return m_hvacOperationModeDescriptionDataIsSet;
}

CmdDataPtr HvacOperationModeDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<HvacOperationModeDescriptionData> dataOut;
  for (const auto &data : getHvacOperationModeDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          HvacOperationModeDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  HvacOperationModeDescriptionListDataSelectors>(
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
          const HvacOperationModeDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  HvacOperationModeDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(HvacOperationModeDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<HvacOperationModeDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<HvacOperationModeDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<HvacOperationModeDescriptionListData>(dataOut);
  } else {
    return std::make_shared<HvacOperationModeDescriptionListData>();
  }
}

bool HvacOperationModeDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"hvacOperationModeDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<HvacOperationModeDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "hvacOperationModeDescriptionData",
            &m_hvacOperationModeDescriptionData)) {
      m_hvacOperationModeDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacOperationModeDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_hvacOperationModeDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<HvacOperationModeDescriptionData>(
            "hvacOperationModeDescriptionData",
            m_hvacOperationModeDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram