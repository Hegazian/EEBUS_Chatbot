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
#include <keo_datagram/taskmanagement/TaskManagementJobRelationListData.h>
#include <keo_datagram/taskmanagement/TaskManagementJobRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TaskManagementJobRelationListData::TaskManagementJobRelationListData()
    : CmdData(), m_taskManagementJobRelationDataIsSet(false),
      m_taskManagementJobRelationData(
          std::vector<TaskManagementJobRelationData>())

{}

TaskManagementJobRelationListData::TaskManagementJobRelationListData(
    const std::vector<TaskManagementJobRelationData>
        &c_taskManagementJobRelationData) {
  setTaskManagementJobRelationData(c_taskManagementJobRelationData);
}

bool TaskManagementJobRelationListData::
operator==(const TaskManagementJobRelationListData &c_classObject) const {
  if (m_taskManagementJobRelationDataIsSet !=
          c_classObject.m_taskManagementJobRelationDataIsSet ||
      (m_taskManagementJobRelationDataIsSet &&
       (m_taskManagementJobRelationData !=
        c_classObject.m_taskManagementJobRelationData))) {
    return false;
  }

  return true;
}

bool TaskManagementJobRelationListData::
operator!=(const TaskManagementJobRelationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TaskManagementJobRelationListData::isEmpty() const {
  return !m_taskManagementJobRelationDataIsSet;
}

CmdData::Type TaskManagementJobRelationListData::getDataType() const {
  return CmdData::Type::TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr TaskManagementJobRelationListData::clone() const {
  return std::make_shared<TaskManagementJobRelationListData>(*this);
}

void TaskManagementJobRelationListData::setTaskManagementJobRelationData(
    const std::vector<TaskManagementJobRelationData>
        &taskManagementJobRelationData) {
  m_taskManagementJobRelationData = taskManagementJobRelationData;
  m_taskManagementJobRelationDataIsSet = true;
}

const std::vector<TaskManagementJobRelationData> &
TaskManagementJobRelationListData::getTaskManagementJobRelationData() const {
  return m_taskManagementJobRelationData;
}

void TaskManagementJobRelationListData::cleanTaskManagementJobRelationData() {
  m_taskManagementJobRelationData.clear();
  m_taskManagementJobRelationDataIsSet = false;
}

bool TaskManagementJobRelationListData::getTaskManagementJobRelationDataIsSet()
    const {
  return m_taskManagementJobRelationDataIsSet;
}

CmdDataPtr TaskManagementJobRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<TaskManagementJobRelationData> dataOut;
  for (const auto &data : getTaskManagementJobRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          TaskManagementJobRelationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  TaskManagementJobRelationListDataSelectors>(
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
          const TaskManagementJobRelationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<TaskManagementJobRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(TaskManagementJobRelationData(data));
          }
        }
      } else {
        return std::make_shared<TaskManagementJobRelationListData>(*this);
      }
    } else {
      return std::make_shared<TaskManagementJobRelationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<TaskManagementJobRelationListData>(dataOut);
  } else {
    return std::make_shared<TaskManagementJobRelationListData>();
  }
}

bool TaskManagementJobRelationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"taskManagementJobRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<TaskManagementJobRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "taskManagementJobRelationData",
            &m_taskManagementJobRelationData)) {
      m_taskManagementJobRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TaskManagementJobRelationListData::toJson() const {
  std::string result = "[";
  if (m_taskManagementJobRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<TaskManagementJobRelationData>(
        "taskManagementJobRelationData", m_taskManagementJobRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram