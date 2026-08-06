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
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerDescriptionListData::
    OperatingConstraintsPowerDescriptionListData()
    : CmdData(), m_operatingConstraintsPowerDescriptionDataIsSet(false),
      m_operatingConstraintsPowerDescriptionData(
          std::vector<OperatingConstraintsPowerDescriptionData>())

{}

OperatingConstraintsPowerDescriptionListData::
    OperatingConstraintsPowerDescriptionListData(
        const std::vector<OperatingConstraintsPowerDescriptionData>
            &c_operatingConstraintsPowerDescriptionData) {
  setOperatingConstraintsPowerDescriptionData(
      c_operatingConstraintsPowerDescriptionData);
}

bool OperatingConstraintsPowerDescriptionListData::operator==(
    const OperatingConstraintsPowerDescriptionListData &c_classObject) const {
  if (m_operatingConstraintsPowerDescriptionDataIsSet !=
          c_classObject.m_operatingConstraintsPowerDescriptionDataIsSet ||
      (m_operatingConstraintsPowerDescriptionDataIsSet &&
       (m_operatingConstraintsPowerDescriptionData !=
        c_classObject.m_operatingConstraintsPowerDescriptionData))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerDescriptionListData::operator!=(
    const OperatingConstraintsPowerDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerDescriptionListData::isEmpty() const {
  return !m_operatingConstraintsPowerDescriptionDataIsSet;
}

CmdData::Type
OperatingConstraintsPowerDescriptionListData::getDataType() const {
  return CmdData::Type::OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr OperatingConstraintsPowerDescriptionListData::clone() const {
  return std::make_shared<OperatingConstraintsPowerDescriptionListData>(*this);
}

void OperatingConstraintsPowerDescriptionListData::
    setOperatingConstraintsPowerDescriptionData(
        const std::vector<OperatingConstraintsPowerDescriptionData>
            &operatingConstraintsPowerDescriptionData) {
  m_operatingConstraintsPowerDescriptionData =
      operatingConstraintsPowerDescriptionData;
  m_operatingConstraintsPowerDescriptionDataIsSet = true;
}

const std::vector<OperatingConstraintsPowerDescriptionData> &
OperatingConstraintsPowerDescriptionListData::
    getOperatingConstraintsPowerDescriptionData() const {
  return m_operatingConstraintsPowerDescriptionData;
}

void OperatingConstraintsPowerDescriptionListData::
    cleanOperatingConstraintsPowerDescriptionData() {
  m_operatingConstraintsPowerDescriptionData.clear();
  m_operatingConstraintsPowerDescriptionDataIsSet = false;
}

bool OperatingConstraintsPowerDescriptionListData::
    getOperatingConstraintsPowerDescriptionDataIsSet() const {
  return m_operatingConstraintsPowerDescriptionDataIsSet;
}

CmdDataPtr OperatingConstraintsPowerDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<OperatingConstraintsPowerDescriptionData> dataOut;
  for (const auto &data : getOperatingConstraintsPowerDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          OperatingConstraintsPowerDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  OperatingConstraintsPowerDescriptionListDataSelectors>(
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
          const OperatingConstraintsPowerDescriptionDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  OperatingConstraintsPowerDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(OperatingConstraintsPowerDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<OperatingConstraintsPowerDescriptionListData>(
            *this);
      }
    } else {
      return std::make_shared<OperatingConstraintsPowerDescriptionListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<OperatingConstraintsPowerDescriptionListData>(
        dataOut);
  } else {
    return std::make_shared<OperatingConstraintsPowerDescriptionListData>();
  }
}

bool OperatingConstraintsPowerDescriptionListData::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"operatingConstraintsPowerDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            OperatingConstraintsPowerDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "operatingConstraintsPowerDescriptionData",
            &m_operatingConstraintsPowerDescriptionData)) {
      m_operatingConstraintsPowerDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsPowerDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_operatingConstraintsPowerDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        OperatingConstraintsPowerDescriptionData>(
        "operatingConstraintsPowerDescriptionData",
        m_operatingConstraintsPowerDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram