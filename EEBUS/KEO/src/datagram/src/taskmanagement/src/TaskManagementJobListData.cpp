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
#include <keo_datagram/taskmanagement/TaskManagementJobListData.h>
#include <keo_datagram/taskmanagement/TaskManagementJobListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobListData::TaskManagementJobListData()
    : CmdData(), m_taskManagementJobDataIsSet(false),
      m_taskManagementJobData(std::vector<TaskManagementJobData>())

{}

TaskManagementJobListData::TaskManagementJobListData(
    const std::vector<TaskManagementJobData> &c_taskManagementJobData) {
  setTaskManagementJobData(c_taskManagementJobData);
}

bool TaskManagementJobListData::
operator==(const TaskManagementJobListData &c_classObject) const {
  if (m_taskManagementJobDataIsSet !=
          c_classObject.m_taskManagementJobDataIsSet ||
      (m_taskManagementJobDataIsSet &&
       (m_taskManagementJobData != c_classObject.m_taskManagementJobData))) {
    return false;
  }

  return true;
}

bool TaskManagementJobListData::
operator!=(const TaskManagementJobListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobListData::isEmpty() const {
  return !m_taskManagementJobDataIsSet;
}

CmdData::Type TaskManagementJobListData::getDataType() const {
  return CmdData::Type::TASK_MANAGEMENT_JOB_LIST_DATA_TYPE;
}

CmdDataPtr TaskManagementJobListData::clone() const {
  return std::make_shared<TaskManagementJobListData>(*this);
}

void TaskManagementJobListData::setTaskManagementJobData(
    const std::vector<TaskManagementJobData> &taskManagementJobData) {
  m_taskManagementJobData = taskManagementJobData;
  m_taskManagementJobDataIsSet = true;
}

const std::vector<TaskManagementJobData> &
TaskManagementJobListData::getTaskManagementJobData() const {
  return m_taskManagementJobData;
}

void TaskManagementJobListData::cleanTaskManagementJobData() {
  m_taskManagementJobData.clear();
  m_taskManagementJobDataIsSet = false;
}

bool TaskManagementJobListData::getTaskManagementJobDataIsSet() const {
  return m_taskManagementJobDataIsSet;
}

CmdDataPtr
TaskManagementJobListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<TaskManagementJobData> dataOut;
  for (const auto &data : getTaskManagementJobData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TaskManagementJobListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<TaskManagementJobListDataSelectors>(
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
          const TaskManagementJobDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TaskManagementJobDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TaskManagementJobData(data));
          }
        }
      } else {
        return std::make_shared<TaskManagementJobListData>(*this);
      }
    } else {
      return std::make_shared<TaskManagementJobListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TaskManagementJobListData>(dataOut);
  } else {
    return std::make_shared<TaskManagementJobListData>();
  }
}

bool TaskManagementJobListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"taskManagementJobData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TaskManagementJobData>(
            static_cast<KeoJsonValue *>(&(*iter)), "taskManagementJobData",
            &m_taskManagementJobData)) {
      m_taskManagementJobDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobListData::toJson() const {
  std::string result = "[";
  if (m_taskManagementJobDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TaskManagementJobData>(
        "taskManagementJobData", m_taskManagementJobData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram