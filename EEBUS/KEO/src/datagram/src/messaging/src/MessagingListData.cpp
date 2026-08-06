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
#include <keo_datagram/messaging/MessagingListData.h>
#include <keo_datagram/messaging/MessagingListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MessagingListData::MessagingListData()
    : CmdData(), m_messagingDataIsSet(false),
      m_messagingData(std::vector<MessagingData>())

{}

MessagingListData::MessagingListData(
    const std::vector<MessagingData> &c_messagingData) {
  setMessagingData(c_messagingData);
}

bool MessagingListData::
operator==(const MessagingListData &c_classObject) const {
  if (m_messagingDataIsSet != c_classObject.m_messagingDataIsSet ||
      (m_messagingDataIsSet &&
       (m_messagingData != c_classObject.m_messagingData))) {
    return false;
  }

  return true;
}

bool MessagingListData::
operator!=(const MessagingListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MessagingListData::isEmpty() const { return !m_messagingDataIsSet; }

CmdData::Type MessagingListData::getDataType() const {
  return CmdData::Type::MESSAGING_LIST_DATA_TYPE;
}

CmdDataPtr MessagingListData::clone() const {
  return std::make_shared<MessagingListData>(*this);
}

void MessagingListData::setMessagingData(
    const std::vector<MessagingData> &messagingData) {
  m_messagingData = messagingData;
  m_messagingDataIsSet = true;
}

const std::vector<MessagingData> &MessagingListData::getMessagingData() const {
  return m_messagingData;
}

void MessagingListData::cleanMessagingData() {
  m_messagingData.clear();
  m_messagingDataIsSet = false;
}

bool MessagingListData::getMessagingDataIsSet() const {
  return m_messagingDataIsSet;
}

CmdDataPtr MessagingListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<MessagingData> dataOut;
  for (const auto &data : getMessagingData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          MessagingListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<MessagingListDataSelectors>(
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
          const MessagingDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<MessagingDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(MessagingData(data));
          }
        }
      } else {
        return std::make_shared<MessagingListData>(*this);
      }
    } else {
      return std::make_shared<MessagingListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<MessagingListData>(dataOut);
  } else {
    return std::make_shared<MessagingListData>();
  }
}

bool MessagingListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"messagingData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<MessagingData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "messagingData", &m_messagingData)) {
      m_messagingDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MessagingListData::toJson() const {
  std::string result = "[";
  if (m_messagingDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<MessagingData>("messagingData",
                                                              m_messagingData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram