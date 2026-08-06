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
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerLevelListData::OperatingConstraintsPowerLevelListData()
    : CmdData(), m_operatingConstraintsPowerLevelDataIsSet(false),
      m_operatingConstraintsPowerLevelData(
          std::vector<OperatingConstraintsPowerLevelData>())

{}

OperatingConstraintsPowerLevelListData::OperatingConstraintsPowerLevelListData(
    const std::vector<OperatingConstraintsPowerLevelData>
        &c_operatingConstraintsPowerLevelData) {
  setOperatingConstraintsPowerLevelData(c_operatingConstraintsPowerLevelData);
}

bool OperatingConstraintsPowerLevelListData::
operator==(const OperatingConstraintsPowerLevelListData &c_classObject) const {
  if (m_operatingConstraintsPowerLevelDataIsSet !=
          c_classObject.m_operatingConstraintsPowerLevelDataIsSet ||
      (m_operatingConstraintsPowerLevelDataIsSet &&
       (m_operatingConstraintsPowerLevelData !=
        c_classObject.m_operatingConstraintsPowerLevelData))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerLevelListData::
operator!=(const OperatingConstraintsPowerLevelListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerLevelListData::isEmpty() const {
  return !m_operatingConstraintsPowerLevelDataIsSet;
}

CmdData::Type OperatingConstraintsPowerLevelListData::getDataType() const {
  return CmdData::Type::OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_TYPE;
}

CmdDataPtr OperatingConstraintsPowerLevelListData::clone() const {
  return std::make_shared<OperatingConstraintsPowerLevelListData>(*this);
}

void OperatingConstraintsPowerLevelListData::
    setOperatingConstraintsPowerLevelData(
        const std::vector<OperatingConstraintsPowerLevelData>
            &operatingConstraintsPowerLevelData) {
  m_operatingConstraintsPowerLevelData = operatingConstraintsPowerLevelData;
  m_operatingConstraintsPowerLevelDataIsSet = true;
}

const std::vector<OperatingConstraintsPowerLevelData> &
OperatingConstraintsPowerLevelListData::getOperatingConstraintsPowerLevelData()
    const {
  return m_operatingConstraintsPowerLevelData;
}

void OperatingConstraintsPowerLevelListData::
    cleanOperatingConstraintsPowerLevelData() {
  m_operatingConstraintsPowerLevelData.clear();
  m_operatingConstraintsPowerLevelDataIsSet = false;
}

bool OperatingConstraintsPowerLevelListData::
    getOperatingConstraintsPowerLevelDataIsSet() const {
  return m_operatingConstraintsPowerLevelDataIsSet;
}

CmdDataPtr OperatingConstraintsPowerLevelListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<OperatingConstraintsPowerLevelData> dataOut;
  for (const auto &data : getOperatingConstraintsPowerLevelData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          OperatingConstraintsPowerLevelListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  OperatingConstraintsPowerLevelListDataSelectors>(
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
          const OperatingConstraintsPowerLevelDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  OperatingConstraintsPowerLevelDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(OperatingConstraintsPowerLevelData(data));
          }
        }
      } else {
        return std::make_shared<OperatingConstraintsPowerLevelListData>(*this);
      }
    } else {
      return std::make_shared<OperatingConstraintsPowerLevelListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<OperatingConstraintsPowerLevelListData>(dataOut);
  } else {
    return std::make_shared<OperatingConstraintsPowerLevelListData>();
  }
}

bool OperatingConstraintsPowerLevelListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"operatingConstraintsPowerLevelData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<OperatingConstraintsPowerLevelData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "operatingConstraintsPowerLevelData",
            &m_operatingConstraintsPowerLevelData)) {
      m_operatingConstraintsPowerLevelDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsPowerLevelListData::toJson() const {
  std::string result = "[";
  if (m_operatingConstraintsPowerLevelDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<OperatingConstraintsPowerLevelData>(
            "operatingConstraintsPowerLevelData",
            m_operatingConstraintsPowerLevelData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram