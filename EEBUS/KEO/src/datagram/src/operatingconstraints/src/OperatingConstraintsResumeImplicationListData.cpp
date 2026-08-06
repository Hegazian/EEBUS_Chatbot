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
#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsResumeImplicationListData::
    OperatingConstraintsResumeImplicationListData()
    : CmdData(), m_operatingConstraintsResumeImplicationDataIsSet(false),
      m_operatingConstraintsResumeImplicationData(
          std::vector<OperatingConstraintsResumeImplicationData>())

{}

OperatingConstraintsResumeImplicationListData::
    OperatingConstraintsResumeImplicationListData(
        const std::vector<OperatingConstraintsResumeImplicationData>
            &c_operatingConstraintsResumeImplicationData) {
  setOperatingConstraintsResumeImplicationData(
      c_operatingConstraintsResumeImplicationData);
}

bool OperatingConstraintsResumeImplicationListData::operator==(
    const OperatingConstraintsResumeImplicationListData &c_classObject) const {
  if (m_operatingConstraintsResumeImplicationDataIsSet !=
          c_classObject.m_operatingConstraintsResumeImplicationDataIsSet ||
      (m_operatingConstraintsResumeImplicationDataIsSet &&
       (m_operatingConstraintsResumeImplicationData !=
        c_classObject.m_operatingConstraintsResumeImplicationData))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsResumeImplicationListData::operator!=(
    const OperatingConstraintsResumeImplicationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsResumeImplicationListData::isEmpty() const {
  return !m_operatingConstraintsResumeImplicationDataIsSet;
}

CmdData::Type
OperatingConstraintsResumeImplicationListData::getDataType() const {
  return CmdData::Type::OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_TYPE;
}

CmdDataPtr OperatingConstraintsResumeImplicationListData::clone() const {
  return std::make_shared<OperatingConstraintsResumeImplicationListData>(*this);
}

void OperatingConstraintsResumeImplicationListData::
    setOperatingConstraintsResumeImplicationData(
        const std::vector<OperatingConstraintsResumeImplicationData>
            &operatingConstraintsResumeImplicationData) {
  m_operatingConstraintsResumeImplicationData =
      operatingConstraintsResumeImplicationData;
  m_operatingConstraintsResumeImplicationDataIsSet = true;
}

const std::vector<OperatingConstraintsResumeImplicationData> &
OperatingConstraintsResumeImplicationListData::
    getOperatingConstraintsResumeImplicationData() const {
  return m_operatingConstraintsResumeImplicationData;
}

void OperatingConstraintsResumeImplicationListData::
    cleanOperatingConstraintsResumeImplicationData() {
  m_operatingConstraintsResumeImplicationData.clear();
  m_operatingConstraintsResumeImplicationDataIsSet = false;
}

bool OperatingConstraintsResumeImplicationListData::
    getOperatingConstraintsResumeImplicationDataIsSet() const {
  return m_operatingConstraintsResumeImplicationDataIsSet;
}

CmdDataPtr OperatingConstraintsResumeImplicationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<OperatingConstraintsResumeImplicationData> dataOut;
  for (const auto &data : getOperatingConstraintsResumeImplicationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          OperatingConstraintsResumeImplicationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  OperatingConstraintsResumeImplicationListDataSelectors>(
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
          const OperatingConstraintsResumeImplicationDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  OperatingConstraintsResumeImplicationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(OperatingConstraintsResumeImplicationData(data));
          }
        }
      } else {
        return std::make_shared<OperatingConstraintsResumeImplicationListData>(
            *this);
      }
    } else {
      return std::make_shared<OperatingConstraintsResumeImplicationListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<OperatingConstraintsResumeImplicationListData>(
        dataOut);
  } else {
    return std::make_shared<OperatingConstraintsResumeImplicationListData>();
  }
}

bool OperatingConstraintsResumeImplicationListData::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"operatingConstraintsResumeImplicationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            OperatingConstraintsResumeImplicationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "operatingConstraintsResumeImplicationData",
            &m_operatingConstraintsResumeImplicationData)) {
      m_operatingConstraintsResumeImplicationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string OperatingConstraintsResumeImplicationListData::toJson() const {
  std::string result = "[";
  if (m_operatingConstraintsResumeImplicationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        OperatingConstraintsResumeImplicationData>(
        "operatingConstraintsResumeImplicationData",
        m_operatingConstraintsResumeImplicationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram