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
#include <keo_datagram/core/SpecificationVersionListData.h>
#include <keo_datagram/core/SpecificationVersionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SpecificationVersionListData::SpecificationVersionListData()
    : CmdData(), m_specificationVersionDataIsSet(false),
      m_specificationVersionData(std::vector<xs_string>())

{}

SpecificationVersionListData::SpecificationVersionListData(
    const std::vector<xs_string> &c_specificationVersionData) {
  setSpecificationVersionData(c_specificationVersionData);
}

bool SpecificationVersionListData::
operator==(const SpecificationVersionListData &c_classObject) const {
  if (m_specificationVersionDataIsSet !=
          c_classObject.m_specificationVersionDataIsSet ||
      (m_specificationVersionDataIsSet &&
       (m_specificationVersionData !=
        c_classObject.m_specificationVersionData))) {
    return false;
  }

  return true;
}

bool SpecificationVersionListData::
operator!=(const SpecificationVersionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SpecificationVersionListData::isEmpty() const {
  return !m_specificationVersionDataIsSet;
}

CmdData::Type SpecificationVersionListData::getDataType() const {
  return CmdData::Type::SPECIFICATION_VERSION_LIST_DATA_TYPE;
}

CmdDataPtr SpecificationVersionListData::clone() const {
  return std::make_shared<SpecificationVersionListData>(*this);
}

void SpecificationVersionListData::setSpecificationVersionData(
    const std::vector<xs_string> &specificationVersionData) {
  m_specificationVersionData = specificationVersionData;
  m_specificationVersionDataIsSet = true;
}

const std::vector<xs_string> &
SpecificationVersionListData::getSpecificationVersionData() const {
  return m_specificationVersionData;
}

void SpecificationVersionListData::cleanSpecificationVersionData() {
  m_specificationVersionData.clear();
  m_specificationVersionDataIsSet = false;
}

bool SpecificationVersionListData::getSpecificationVersionDataIsSet() const {
  return m_specificationVersionDataIsSet;
}

CmdDataPtr
SpecificationVersionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<xs_string> dataOut;
  for (const auto &data : getSpecificationVersionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          SpecificationVersionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<SpecificationVersionListDataSelectors>(
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
          dataOut.push_back(xs_string(data));
        }
      } else {
        return std::make_shared<SpecificationVersionListData>(*this);
      }
    } else {
      return std::make_shared<SpecificationVersionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<SpecificationVersionListData>(dataOut);
  } else {
    return std::make_shared<SpecificationVersionListData>();
  }
}

bool SpecificationVersionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"specificationVersionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<xs_string>(
            static_cast<KeoJsonValue *>(&(*iter)), "specificationVersionData",
            &m_specificationVersionData)) {
      m_specificationVersionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SpecificationVersionListData::toJson() const {
  std::string result = "[";
  if (m_specificationVersionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_string>(
        "specificationVersionData", m_specificationVersionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram