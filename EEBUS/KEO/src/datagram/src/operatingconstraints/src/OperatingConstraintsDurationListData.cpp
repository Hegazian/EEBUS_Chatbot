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
#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsDurationListData::OperatingConstraintsDurationListData()
    : CmdData(), m_operatingConstraintsDurationDataIsSet(false),
      m_operatingConstraintsDurationData(
          std::vector<OperatingConstraintsDurationData>())

{}

OperatingConstraintsDurationListData::OperatingConstraintsDurationListData(
    const std::vector<OperatingConstraintsDurationData>
        &c_operatingConstraintsDurationData) {
  setOperatingConstraintsDurationData(c_operatingConstraintsDurationData);
}

bool OperatingConstraintsDurationListData::
operator==(const OperatingConstraintsDurationListData &c_classObject) const {
  if (m_operatingConstraintsDurationDataIsSet !=
          c_classObject.m_operatingConstraintsDurationDataIsSet ||
      (m_operatingConstraintsDurationDataIsSet &&
       (m_operatingConstraintsDurationData !=
        c_classObject.m_operatingConstraintsDurationData))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsDurationListData::
operator!=(const OperatingConstraintsDurationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsDurationListData::isEmpty() const {
  return !m_operatingConstraintsDurationDataIsSet;
}

CmdData::Type OperatingConstraintsDurationListData::getDataType() const {
  return CmdData::Type::OPERATING_CONSTRAINTS_DURATION_LIST_DATA_TYPE;
}

CmdDataPtr OperatingConstraintsDurationListData::clone() const {
  return std::make_shared<OperatingConstraintsDurationListData>(*this);
}

void OperatingConstraintsDurationListData::setOperatingConstraintsDurationData(
    const std::vector<OperatingConstraintsDurationData>
        &operatingConstraintsDurationData) {
  m_operatingConstraintsDurationData = operatingConstraintsDurationData;
  m_operatingConstraintsDurationDataIsSet = true;
}

const std::vector<OperatingConstraintsDurationData> &
OperatingConstraintsDurationListData::getOperatingConstraintsDurationData()
    const {
  return m_operatingConstraintsDurationData;
}

void OperatingConstraintsDurationListData::
    cleanOperatingConstraintsDurationData() {
  m_operatingConstraintsDurationData.clear();
  m_operatingConstraintsDurationDataIsSet = false;
}

bool OperatingConstraintsDurationListData::
    getOperatingConstraintsDurationDataIsSet() const {
  return m_operatingConstraintsDurationDataIsSet;
}

CmdDataPtr OperatingConstraintsDurationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<OperatingConstraintsDurationData> dataOut;
  for (const auto &data : getOperatingConstraintsDurationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          OperatingConstraintsDurationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  OperatingConstraintsDurationListDataSelectors>(
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
          const OperatingConstraintsDurationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  OperatingConstraintsDurationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(OperatingConstraintsDurationData(data));
          }
        }
      } else {
        return std::make_shared<OperatingConstraintsDurationListData>(*this);
      }
    } else {
      return std::make_shared<OperatingConstraintsDurationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<OperatingConstraintsDurationListData>(dataOut);
  } else {
    return std::make_shared<OperatingConstraintsDurationListData>();
  }
}

bool OperatingConstraintsDurationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"operatingConstraintsDurationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<OperatingConstraintsDurationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "operatingConstraintsDurationData",
            &m_operatingConstraintsDurationData)) {
      m_operatingConstraintsDurationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsDurationListData::toJson() const {
  std::string result = "[";
  if (m_operatingConstraintsDurationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<OperatingConstraintsDurationData>(
            "operatingConstraintsDurationData",
            m_operatingConstraintsDurationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram