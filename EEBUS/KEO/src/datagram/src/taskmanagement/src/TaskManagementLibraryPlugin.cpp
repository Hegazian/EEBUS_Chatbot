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

#include <KeoDatagramPlugin.h>
#include <keo_spine_datagramVersion.h>

#include <keo_datagram/taskmanagement/TaskManagementJobDataElements.h>
#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionDataElements.h>
#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionListData.h>
#include <keo_datagram/taskmanagement/TaskManagementJobDescriptionListDataSelectors.h>
#include <keo_datagram/taskmanagement/TaskManagementJobListData.h>
#include <keo_datagram/taskmanagement/TaskManagementJobListDataSelectors.h>
#include <keo_datagram/taskmanagement/TaskManagementJobRelationDataElements.h>
#include <keo_datagram/taskmanagement/TaskManagementJobRelationListData.h>
#include <keo_datagram/taskmanagement/TaskManagementJobRelationListDataSelectors.h>
#include <keo_datagram/taskmanagement/TaskManagementOverviewData.h>
#include <keo_datagram/taskmanagement/TaskManagementOverviewDataElements.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class TaskManagementDatagramPlugin : public KeoDatagramPlugin {
public:
  TaskManagementDatagramPlugin();
  virtual ~TaskManagementDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(TaskManagementDatagramPlugin,
                    "TaskManagement Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

TaskManagementDatagramPlugin::TaskManagementDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

TaskManagementDatagramPlugin::~TaskManagementDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new TaskManagementDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
TaskManagementDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<TaskManagementJobDescriptionListData>();
  case CmdData::Type::TASK_MANAGEMENT_JOB_LIST_DATA_TYPE:
    return std::make_shared<TaskManagementJobListData>();
  case CmdData::Type::TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_TYPE:
    return std::make_shared<TaskManagementJobRelationListData>();
  case CmdData::Type::TASK_MANAGEMENT_OVERVIEW_DATA_TYPE:
    return std::make_shared<TaskManagementOverviewData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr TaskManagementDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::
      TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TaskManagementJobDescriptionListDataSelectors>();
  case DataSelectors::Type::TASK_MANAGEMENT_JOB_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TaskManagementJobListDataSelectors>();
  case DataSelectors::Type::
      TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TaskManagementJobRelationListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr TaskManagementDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::TASK_MANAGEMENT_JOB_DATA_ELEMENTS_TYPE:
    return std::make_shared<TaskManagementJobDataElements>();
  case DataElements::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TaskManagementJobDescriptionDataElements>();
  case DataElements::Type::TASK_MANAGEMENT_JOB_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TaskManagementJobRelationDataElements>();
  case DataElements::Type::TASK_MANAGEMENT_OVERVIEW_DATA_ELEMENTS_TYPE:
    return std::make_shared<TaskManagementOverviewDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
