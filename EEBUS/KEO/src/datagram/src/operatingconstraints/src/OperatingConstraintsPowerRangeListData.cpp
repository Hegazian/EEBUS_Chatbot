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
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerRangeListData::OperatingConstraintsPowerRangeListData()
    : CmdData(), m_operatingConstraintsPowerRangeDataIsSet(false),
      m_operatingConstraintsPowerRangeData(
          std::vector<OperatingConstraintsPowerRangeData>())

{}

OperatingConstraintsPowerRangeListData::OperatingConstraintsPowerRangeListData(
    const std::vector<OperatingConstraintsPowerRangeData>
        &c_operatingConstraintsPowerRangeData) {
  setOperatingConstraintsPowerRangeData(c_operatingConstraintsPowerRangeData);
}

bool OperatingConstraintsPowerRangeListData::
operator==(const OperatingConstraintsPowerRangeListData &c_classObject) const {
  if (m_operatingConstraintsPowerRangeDataIsSet !=
          c_classObject.m_operatingConstraintsPowerRangeDataIsSet ||
      (m_operatingConstraintsPowerRangeDataIsSet &&
       (m_operatingConstraintsPowerRangeData !=
        c_classObject.m_operatingConstraintsPowerRangeData))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerRangeListData::
operator!=(const OperatingConstraintsPowerRangeListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerRangeListData::isEmpty() const {
  return !m_operatingConstraintsPowerRangeDataIsSet;
}

CmdData::Type OperatingConstraintsPowerRangeListData::getDataType() const {
  return CmdData::Type::OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_TYPE;
}

CmdDataPtr OperatingConstraintsPowerRangeListData::clone() const {
  return std::make_shared<OperatingConstraintsPowerRangeListData>(*this);
}

void OperatingConstraintsPowerRangeListData::
    setOperatingConstraintsPowerRangeData(
        const std::vector<OperatingConstraintsPowerRangeData>
            &operatingConstraintsPowerRangeData) {
  m_operatingConstraintsPowerRangeData = operatingConstraintsPowerRangeData;
  m_operatingConstraintsPowerRangeDataIsSet = true;
}

const std::vector<OperatingConstraintsPowerRangeData> &
OperatingConstraintsPowerRangeListData::getOperatingConstraintsPowerRangeData()
    const {
  return m_operatingConstraintsPowerRangeData;
}

void OperatingConstraintsPowerRangeListData::
    cleanOperatingConstraintsPowerRangeData() {
  m_operatingConstraintsPowerRangeData.clear();
  m_operatingConstraintsPowerRangeDataIsSet = false;
}

bool OperatingConstraintsPowerRangeListData::
    getOperatingConstraintsPowerRangeDataIsSet() const {
  return m_operatingConstraintsPowerRangeDataIsSet;
}

CmdDataPtr OperatingConstraintsPowerRangeListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<OperatingConstraintsPowerRangeData> dataOut;
  for (const auto &data : getOperatingConstraintsPowerRangeData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          OperatingConstraintsPowerRangeListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  OperatingConstraintsPowerRangeListDataSelectors>(
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
          const OperatingConstraintsPowerRangeDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  OperatingConstraintsPowerRangeDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(OperatingConstraintsPowerRangeData(data));
          }
        }
      } else {
        return std::make_shared<OperatingConstraintsPowerRangeListData>(*this);
      }
    } else {
      return std::make_shared<OperatingConstraintsPowerRangeListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<OperatingConstraintsPowerRangeListData>(dataOut);
  } else {
    return std::make_shared<OperatingConstraintsPowerRangeListData>();
  }
}

bool OperatingConstraintsPowerRangeListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"operatingConstraintsPowerRangeData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<OperatingConstraintsPowerRangeData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "operatingConstraintsPowerRangeData",
            &m_operatingConstraintsPowerRangeData)) {
      m_operatingConstraintsPowerRangeDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsPowerRangeListData::toJson() const {
  std::string result = "[";
  if (m_operatingConstraintsPowerRangeDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<OperatingConstraintsPowerRangeData>(
            "operatingConstraintsPowerRangeData",
            m_operatingConstraintsPowerRangeData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram