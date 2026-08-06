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
#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceAlternativesRelationListData::
    PowerSequenceAlternativesRelationListData()
    : CmdData(), m_powerSequenceAlternativesRelationDataIsSet(false),
      m_powerSequenceAlternativesRelationData(
          std::vector<PowerSequenceAlternativesRelationData>())

{}

PowerSequenceAlternativesRelationListData::
    PowerSequenceAlternativesRelationListData(
        const std::vector<PowerSequenceAlternativesRelationData>
            &c_powerSequenceAlternativesRelationData) {
  setPowerSequenceAlternativesRelationData(
      c_powerSequenceAlternativesRelationData);
}

bool PowerSequenceAlternativesRelationListData::operator==(
    const PowerSequenceAlternativesRelationListData &c_classObject) const {
  if (m_powerSequenceAlternativesRelationDataIsSet !=
          c_classObject.m_powerSequenceAlternativesRelationDataIsSet ||
      (m_powerSequenceAlternativesRelationDataIsSet &&
       (m_powerSequenceAlternativesRelationData !=
        c_classObject.m_powerSequenceAlternativesRelationData))) {
    return false;
  }

  return true;
}

bool PowerSequenceAlternativesRelationListData::operator!=(
    const PowerSequenceAlternativesRelationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceAlternativesRelationListData::isEmpty() const {
  return !m_powerSequenceAlternativesRelationDataIsSet;
}

CmdData::Type PowerSequenceAlternativesRelationListData::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr PowerSequenceAlternativesRelationListData::clone() const {
  return std::make_shared<PowerSequenceAlternativesRelationListData>(*this);
}

void PowerSequenceAlternativesRelationListData::
    setPowerSequenceAlternativesRelationData(
        const std::vector<PowerSequenceAlternativesRelationData>
            &powerSequenceAlternativesRelationData) {
  m_powerSequenceAlternativesRelationData =
      powerSequenceAlternativesRelationData;
  m_powerSequenceAlternativesRelationDataIsSet = true;
}

const std::vector<PowerSequenceAlternativesRelationData> &
PowerSequenceAlternativesRelationListData::
    getPowerSequenceAlternativesRelationData() const {
  return m_powerSequenceAlternativesRelationData;
}

void PowerSequenceAlternativesRelationListData::
    cleanPowerSequenceAlternativesRelationData() {
  m_powerSequenceAlternativesRelationData.clear();
  m_powerSequenceAlternativesRelationDataIsSet = false;
}

bool PowerSequenceAlternativesRelationListData::
    getPowerSequenceAlternativesRelationDataIsSet() const {
  return m_powerSequenceAlternativesRelationDataIsSet;
}

CmdDataPtr PowerSequenceAlternativesRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<PowerSequenceAlternativesRelationData> dataOut;
  for (const auto &data : getPowerSequenceAlternativesRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerSequenceAlternativesRelationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  PowerSequenceAlternativesRelationListDataSelectors>(
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
          const PowerSequenceAlternativesRelationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  PowerSequenceAlternativesRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerSequenceAlternativesRelationData(data));
          }
        }
      } else {
        return std::make_shared<PowerSequenceAlternativesRelationListData>(
            *this);
      }
    } else {
      return std::make_shared<PowerSequenceAlternativesRelationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerSequenceAlternativesRelationListData>(dataOut);
  } else {
    return std::make_shared<PowerSequenceAlternativesRelationListData>();
  }
}

bool PowerSequenceAlternativesRelationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"powerSequenceAlternativesRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerSequenceAlternativesRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "powerSequenceAlternativesRelationData",
            &m_powerSequenceAlternativesRelationData)) {
      m_powerSequenceAlternativesRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceAlternativesRelationListData::toJson() const {
  std::string result = "[";
  if (m_powerSequenceAlternativesRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<PowerSequenceAlternativesRelationData>(
            "powerSequenceAlternativesRelationData",
            m_powerSequenceAlternativesRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram