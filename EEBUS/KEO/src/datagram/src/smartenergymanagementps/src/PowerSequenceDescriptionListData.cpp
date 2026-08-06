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
#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceDescriptionListData::PowerSequenceDescriptionListData()
    : CmdData(), m_powerSequenceDescriptionDataIsSet(false),
      m_powerSequenceDescriptionData(
          std::vector<PowerSequenceDescriptionData>())

{}

PowerSequenceDescriptionListData::PowerSequenceDescriptionListData(
    const std::vector<PowerSequenceDescriptionData>
        &c_powerSequenceDescriptionData) {
  setPowerSequenceDescriptionData(c_powerSequenceDescriptionData);
}

bool PowerSequenceDescriptionListData::
operator==(const PowerSequenceDescriptionListData &c_classObject) const {
  if (m_powerSequenceDescriptionDataIsSet !=
          c_classObject.m_powerSequenceDescriptionDataIsSet ||
      (m_powerSequenceDescriptionDataIsSet &&
       (m_powerSequenceDescriptionData !=
        c_classObject.m_powerSequenceDescriptionData))) {
    return false;
  }

  return true;
}

bool PowerSequenceDescriptionListData::
operator!=(const PowerSequenceDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceDescriptionListData::isEmpty() const {
  return !m_powerSequenceDescriptionDataIsSet;
}

CmdData::Type PowerSequenceDescriptionListData::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr PowerSequenceDescriptionListData::clone() const {
  return std::make_shared<PowerSequenceDescriptionListData>(*this);
}

void PowerSequenceDescriptionListData::setPowerSequenceDescriptionData(
    const std::vector<PowerSequenceDescriptionData>
        &powerSequenceDescriptionData) {
  m_powerSequenceDescriptionData = powerSequenceDescriptionData;
  m_powerSequenceDescriptionDataIsSet = true;
}

const std::vector<PowerSequenceDescriptionData> &
PowerSequenceDescriptionListData::getPowerSequenceDescriptionData() const {
  return m_powerSequenceDescriptionData;
}

void PowerSequenceDescriptionListData::cleanPowerSequenceDescriptionData() {
  m_powerSequenceDescriptionData.clear();
  m_powerSequenceDescriptionDataIsSet = false;
}

bool PowerSequenceDescriptionListData::getPowerSequenceDescriptionDataIsSet()
    const {
  return m_powerSequenceDescriptionDataIsSet;
}

CmdDataPtr PowerSequenceDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<PowerSequenceDescriptionData> dataOut;
  for (const auto &data : getPowerSequenceDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          PowerSequenceDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  PowerSequenceDescriptionListDataSelectors>(
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
          const PowerSequenceDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<PowerSequenceDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(PowerSequenceDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<PowerSequenceDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<PowerSequenceDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<PowerSequenceDescriptionListData>(dataOut);
  } else {
    return std::make_shared<PowerSequenceDescriptionListData>();
  }
}

bool PowerSequenceDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"powerSequenceDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<PowerSequenceDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "powerSequenceDescriptionData", &m_powerSequenceDescriptionData)) {
      m_powerSequenceDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_powerSequenceDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<PowerSequenceDescriptionData>(
        "powerSequenceDescriptionData", m_powerSequenceDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram