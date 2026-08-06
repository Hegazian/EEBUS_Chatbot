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

#include <keo_datagram/loadcontrol/LoadControlEventDataElements.h>
#include <keo_datagram/loadcontrol/LoadControlEventListData.h>
#include <keo_datagram/loadcontrol/LoadControlEventListDataSelectors.h>
#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsDataElements.h>
#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsListData.h>
#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsListDataSelectors.h>
#include <keo_datagram/loadcontrol/LoadControlLimitDataElements.h>
#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionDataElements.h>
#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionListData.h>
#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionListDataSelectors.h>
#include <keo_datagram/loadcontrol/LoadControlLimitListData.h>
#include <keo_datagram/loadcontrol/LoadControlLimitListDataSelectors.h>
#include <keo_datagram/loadcontrol/LoadControlNodeData.h>
#include <keo_datagram/loadcontrol/LoadControlNodeDataElements.h>
#include <keo_datagram/loadcontrol/LoadControlStateDataElements.h>
#include <keo_datagram/loadcontrol/LoadControlStateListData.h>
#include <keo_datagram/loadcontrol/LoadControlStateListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class LoadControlDatagramPlugin : public KeoDatagramPlugin {
public:
  LoadControlDatagramPlugin();
  virtual ~LoadControlDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(LoadControlDatagramPlugin, "LoadControl Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

LoadControlDatagramPlugin::LoadControlDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

LoadControlDatagramPlugin::~LoadControlDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new LoadControlDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
LoadControlDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::LOAD_CONTROL_EVENT_LIST_DATA_TYPE:
    return std::make_shared<LoadControlEventListData>();
  case CmdData::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<LoadControlLimitConstraintsListData>();
  case CmdData::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<LoadControlLimitDescriptionListData>();
  case CmdData::Type::LOAD_CONTROL_LIMIT_LIST_DATA_TYPE:
    return std::make_shared<LoadControlLimitListData>();
  case CmdData::Type::LOAD_CONTROL_NODE_DATA_TYPE:
    return std::make_shared<LoadControlNodeData>();
  case CmdData::Type::LOAD_CONTROL_STATE_LIST_DATA_TYPE:
    return std::make_shared<LoadControlStateListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr LoadControlDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::LOAD_CONTROL_EVENT_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<LoadControlEventListDataSelectors>();
  case DataSelectors::Type::
      LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<LoadControlLimitConstraintsListDataSelectors>();
  case DataSelectors::Type::
      LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<LoadControlLimitDescriptionListDataSelectors>();
  case DataSelectors::Type::LOAD_CONTROL_LIMIT_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<LoadControlLimitListDataSelectors>();
  case DataSelectors::Type::LOAD_CONTROL_STATE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<LoadControlStateListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr LoadControlDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::LOAD_CONTROL_EVENT_DATA_ELEMENTS_TYPE:
    return std::make_shared<LoadControlEventDataElements>();
  case DataElements::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<LoadControlLimitConstraintsDataElements>();
  case DataElements::Type::LOAD_CONTROL_LIMIT_DATA_ELEMENTS_TYPE:
    return std::make_shared<LoadControlLimitDataElements>();
  case DataElements::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<LoadControlLimitDescriptionDataElements>();
  case DataElements::Type::LOAD_CONTROL_NODE_DATA_ELEMENTS_TYPE:
    return std::make_shared<LoadControlNodeDataElements>();
  case DataElements::Type::LOAD_CONTROL_STATE_DATA_ELEMENTS_TYPE:
    return std::make_shared<LoadControlStateDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
