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
#include <keo_datagram/core/SubscriptionManagementEntryListData.h>
#include <keo_datagram/core/SubscriptionManagementEntryListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SubscriptionManagementEntryListData::SubscriptionManagementEntryListData()
    : CmdData(), m_subscriptionManagementEntryDataIsSet(false),
      m_subscriptionManagementEntryData(
          std::vector<SubscriptionManagementEntryData>())

{}

SubscriptionManagementEntryListData::SubscriptionManagementEntryListData(
    const std::vector<SubscriptionManagementEntryData>
        &c_subscriptionManagementEntryData) {
  setSubscriptionManagementEntryData(c_subscriptionManagementEntryData);
}

bool SubscriptionManagementEntryListData::
operator==(const SubscriptionManagementEntryListData &c_classObject) const {
  if (m_subscriptionManagementEntryDataIsSet !=
          c_classObject.m_subscriptionManagementEntryDataIsSet ||
      (m_subscriptionManagementEntryDataIsSet &&
       (m_subscriptionManagementEntryData !=
        c_classObject.m_subscriptionManagementEntryData))) {
    return false;
  }

  return true;
}

bool SubscriptionManagementEntryListData::
operator!=(const SubscriptionManagementEntryListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SubscriptionManagementEntryListData::isEmpty() const {
  return !m_subscriptionManagementEntryDataIsSet;
}

CmdData::Type SubscriptionManagementEntryListData::getDataType() const {
  return CmdData::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_TYPE;
}

CmdDataPtr SubscriptionManagementEntryListData::clone() const {
  return std::make_shared<SubscriptionManagementEntryListData>(*this);
}

void SubscriptionManagementEntryListData::setSubscriptionManagementEntryData(
    const std::vector<SubscriptionManagementEntryData>
        &subscriptionManagementEntryData) {
  m_subscriptionManagementEntryData = subscriptionManagementEntryData;
  m_subscriptionManagementEntryDataIsSet = true;
}

const std::vector<SubscriptionManagementEntryData> &
SubscriptionManagementEntryListData::getSubscriptionManagementEntryData()
    const {
  return m_subscriptionManagementEntryData;
}

void SubscriptionManagementEntryListData::
    cleanSubscriptionManagementEntryData() {
  m_subscriptionManagementEntryData.clear();
  m_subscriptionManagementEntryDataIsSet = false;
}

bool SubscriptionManagementEntryListData::
    getSubscriptionManagementEntryDataIsSet() const {
  return m_subscriptionManagementEntryDataIsSet;
}

CmdDataPtr SubscriptionManagementEntryListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<SubscriptionManagementEntryData> dataOut;
  for (const auto &data : getSubscriptionManagementEntryData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          SubscriptionManagementEntryListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  SubscriptionManagementEntryListDataSelectors>(
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
          const SubscriptionManagementEntryDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  SubscriptionManagementEntryDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(SubscriptionManagementEntryData(data));
          }
        }
      } else {
        return std::make_shared<SubscriptionManagementEntryListData>(*this);
      }
    } else {
      return std::make_shared<SubscriptionManagementEntryListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<SubscriptionManagementEntryListData>(dataOut);
  } else {
    return std::make_shared<SubscriptionManagementEntryListData>();
  }
}

bool SubscriptionManagementEntryListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"subscriptionManagementEntryData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<SubscriptionManagementEntryData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "subscriptionManagementEntryData",
            &m_subscriptionManagementEntryData)) {
      m_subscriptionManagementEntryDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SubscriptionManagementEntryListData::toJson() const {
  std::string result = "[";
  if (m_subscriptionManagementEntryDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<SubscriptionManagementEntryData>(
        "subscriptionManagementEntryData", m_subscriptionManagementEntryData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram