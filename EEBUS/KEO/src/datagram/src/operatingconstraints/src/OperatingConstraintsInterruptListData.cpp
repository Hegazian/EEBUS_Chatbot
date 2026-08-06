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
#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsInterruptListData::OperatingConstraintsInterruptListData()
    : CmdData(), m_operatingConstraintsInterruptDataIsSet(false),
      m_operatingConstraintsInterruptData(
          std::vector<OperatingConstraintsInterruptData>())

{}

OperatingConstraintsInterruptListData::OperatingConstraintsInterruptListData(
    const std::vector<OperatingConstraintsInterruptData>
        &c_operatingConstraintsInterruptData) {
  setOperatingConstraintsInterruptData(c_operatingConstraintsInterruptData);
}

bool OperatingConstraintsInterruptListData::
operator==(const OperatingConstraintsInterruptListData &c_classObject) const {
  if (m_operatingConstraintsInterruptDataIsSet !=
          c_classObject.m_operatingConstraintsInterruptDataIsSet ||
      (m_operatingConstraintsInterruptDataIsSet &&
       (m_operatingConstraintsInterruptData !=
        c_classObject.m_operatingConstraintsInterruptData))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsInterruptListData::
operator!=(const OperatingConstraintsInterruptListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsInterruptListData::isEmpty() const {
  return !m_operatingConstraintsInterruptDataIsSet;
}

CmdData::Type OperatingConstraintsInterruptListData::getDataType() const {
  return CmdData::Type::OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_TYPE;
}

CmdDataPtr OperatingConstraintsInterruptListData::clone() const {
  return std::make_shared<OperatingConstraintsInterruptListData>(*this);
}

void OperatingConstraintsInterruptListData::
    setOperatingConstraintsInterruptData(
        const std::vector<OperatingConstraintsInterruptData>
            &operatingConstraintsInterruptData) {
  m_operatingConstraintsInterruptData = operatingConstraintsInterruptData;
  m_operatingConstraintsInterruptDataIsSet = true;
}

const std::vector<OperatingConstraintsInterruptData> &
OperatingConstraintsInterruptListData::getOperatingConstraintsInterruptData()
    const {
  return m_operatingConstraintsInterruptData;
}

void OperatingConstraintsInterruptListData::
    cleanOperatingConstraintsInterruptData() {
  m_operatingConstraintsInterruptData.clear();
  m_operatingConstraintsInterruptDataIsSet = false;
}

bool OperatingConstraintsInterruptListData::
    getOperatingConstraintsInterruptDataIsSet() const {
  return m_operatingConstraintsInterruptDataIsSet;
}

CmdDataPtr OperatingConstraintsInterruptListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<OperatingConstraintsInterruptData> dataOut;
  for (const auto &data : getOperatingConstraintsInterruptData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          OperatingConstraintsInterruptListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  OperatingConstraintsInterruptListDataSelectors>(
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
          const OperatingConstraintsInterruptDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  OperatingConstraintsInterruptDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(OperatingConstraintsInterruptData(data));
          }
        }
      } else {
        return std::make_shared<OperatingConstraintsInterruptListData>(*this);
      }
    } else {
      return std::make_shared<OperatingConstraintsInterruptListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<OperatingConstraintsInterruptListData>(dataOut);
  } else {
    return std::make_shared<OperatingConstraintsInterruptListData>();
  }
}

bool OperatingConstraintsInterruptListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"operatingConstraintsInterruptData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<OperatingConstraintsInterruptData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "operatingConstraintsInterruptData",
            &m_operatingConstraintsInterruptData)) {
      m_operatingConstraintsInterruptDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsInterruptListData::toJson() const {
  std::string result = "[";
  if (m_operatingConstraintsInterruptDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<OperatingConstraintsInterruptData>(
            "operatingConstraintsInterruptData",
            m_operatingConstraintsInterruptData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram