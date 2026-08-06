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
#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionListData.h>
#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobDescriptionListData::TaskManagementJobDescriptionListData()
    : CmdData(), m_taskManagementJobDescriptionDataIsSet(false),
      m_taskManagementJobDescriptionData(
          std::vector<TaskManagementJobDescriptionData>())

{}

TaskManagementJobDescriptionListData::TaskManagementJobDescriptionListData(
    const std::vector<TaskManagementJobDescriptionData>
        &c_taskManagementJobDescriptionData) {
  setTaskManagementJobDescriptionData(c_taskManagementJobDescriptionData);
}

bool TaskManagementJobDescriptionListData::
operator==(const TaskManagementJobDescriptionListData &c_classObject) const {
  if (m_taskManagementJobDescriptionDataIsSet !=
          c_classObject.m_taskManagementJobDescriptionDataIsSet ||
      (m_taskManagementJobDescriptionDataIsSet &&
       (m_taskManagementJobDescriptionData !=
        c_classObject.m_taskManagementJobDescriptionData))) {
    return false;
  }

  return true;
}

bool TaskManagementJobDescriptionListData::
operator!=(const TaskManagementJobDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobDescriptionListData::isEmpty() const {
  return !m_taskManagementJobDescriptionDataIsSet;
}

CmdData::Type TaskManagementJobDescriptionListData::getDataType() const {
  return CmdData::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr TaskManagementJobDescriptionListData::clone() const {
  return std::make_shared<TaskManagementJobDescriptionListData>(*this);
}

void TaskManagementJobDescriptionListData::setTaskManagementJobDescriptionData(
    const std::vector<TaskManagementJobDescriptionData>
        &taskManagementJobDescriptionData) {
  m_taskManagementJobDescriptionData = taskManagementJobDescriptionData;
  m_taskManagementJobDescriptionDataIsSet = true;
}

const std::vector<TaskManagementJobDescriptionData> &
TaskManagementJobDescriptionListData::getTaskManagementJobDescriptionData()
    const {
  return m_taskManagementJobDescriptionData;
}

void TaskManagementJobDescriptionListData::
    cleanTaskManagementJobDescriptionData() {
  m_taskManagementJobDescriptionData.clear();
  m_taskManagementJobDescriptionDataIsSet = false;
}

bool TaskManagementJobDescriptionListData::
    getTaskManagementJobDescriptionDataIsSet() const {
  return m_taskManagementJobDescriptionDataIsSet;
}

CmdDataPtr TaskManagementJobDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<TaskManagementJobDescriptionData> dataOut;
  for (const auto &data : getTaskManagementJobDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TaskManagementJobDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  TaskManagementJobDescriptionListDataSelectors>(
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
          const TaskManagementJobDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  TaskManagementJobDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TaskManagementJobDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<TaskManagementJobDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<TaskManagementJobDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TaskManagementJobDescriptionListData>(dataOut);
  } else {
    return std::make_shared<TaskManagementJobDescriptionListData>();
  }
}

bool TaskManagementJobDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"taskManagementJobDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TaskManagementJobDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "taskManagementJobDescriptionData",
            &m_taskManagementJobDescriptionData)) {
      m_taskManagementJobDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_taskManagementJobDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<TaskManagementJobDescriptionData>(
            "taskManagementJobDescriptionData",
            m_taskManagementJobDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram