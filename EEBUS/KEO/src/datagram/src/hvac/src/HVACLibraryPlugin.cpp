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

#include <keo_datagram/hvac/HvacOperationModeDescriptionDataElements.h>
#include <keo_datagram/hvac/HvacOperationModeDescriptionListData.h>
#include <keo_datagram/hvac/HvacOperationModeDescriptionListDataSelectors.h>
#include <keo_datagram/hvac/HvacOverrunDataElements.h>
#include <keo_datagram/hvac/HvacOverrunDescriptionDataElements.h>
#include <keo_datagram/hvac/HvacOverrunDescriptionListData.h>
#include <keo_datagram/hvac/HvacOverrunDescriptionListDataSelectors.h>
#include <keo_datagram/hvac/HvacOverrunListData.h>
#include <keo_datagram/hvac/HvacOverrunListDataSelectors.h>
#include <keo_datagram/hvac/HvacSystemFunctionDataElements.h>
#include <keo_datagram/hvac/HvacSystemFunctionDescriptionDataElements.h>
#include <keo_datagram/hvac/HvacSystemFunctionDescriptionListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionDescriptionListDataSelectors.h>
#include <keo_datagram/hvac/HvacSystemFunctionListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionListDataSelectors.h>
#include <keo_datagram/hvac/HvacSystemFunctionOperationModeRelationDataElements.h>
#include <keo_datagram/hvac/HvacSystemFunctionOperationModeRelationListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionOperationModeRelationListDataSelectors.h>
#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationDataElements.h>
#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationListDataSelectors.h>
#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationDataElements.h>
#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class HVACDatagramPlugin : public KeoDatagramPlugin {
public:
  HVACDatagramPlugin();
  virtual ~HVACDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(HVACDatagramPlugin, "HVAC Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

HVACDatagramPlugin::HVACDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

HVACDatagramPlugin::~HVACDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() { return new HVACDatagramPlugin; }

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr HVACDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<HvacOperationModeDescriptionListData>();
  case CmdData::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<HvacOverrunDescriptionListData>();
  case CmdData::Type::HVAC_OVERRUN_LIST_DATA_TYPE:
    return std::make_shared<HvacOverrunListData>();
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<HvacSystemFunctionDescriptionListData>();
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_TYPE:
    return std::make_shared<HvacSystemFunctionListData>();
  case CmdData::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_TYPE:
    return std::make_shared<HvacSystemFunctionOperationModeRelationListData>();
  case CmdData::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_TYPE:
    return std::make_shared<HvacSystemFunctionPowerSequenceRelationListData>();
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_TYPE:
    return std::make_shared<HvacSystemFunctionSetpointRelationListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr
HVACDatagramPlugin::createDataSelectors(const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::
      HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<HvacOperationModeDescriptionListDataSelectors>();
  case DataSelectors::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<HvacOverrunDescriptionListDataSelectors>();
  case DataSelectors::Type::HVAC_OVERRUN_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<HvacOverrunListDataSelectors>();
  case DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<HvacSystemFunctionDescriptionListDataSelectors>();
  case DataSelectors::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<HvacSystemFunctionListDataSelectors>();
  case DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        HvacSystemFunctionOperationModeRelationListDataSelectors>();
  case DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        HvacSystemFunctionPowerSequenceRelationListDataSelectors>();
  case DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        HvacSystemFunctionSetpointRelationListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr
HVACDatagramPlugin::createDataElements(const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::HVAC_OPERATION_MODE_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<HvacOperationModeDescriptionDataElements>();
  case DataElements::Type::HVAC_OVERRUN_DATA_ELEMENTS_TYPE:
    return std::make_shared<HvacOverrunDataElements>();
  case DataElements::Type::HVAC_OVERRUN_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<HvacOverrunDescriptionDataElements>();
  case DataElements::Type::HVAC_SYSTEM_FUNCTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<HvacSystemFunctionDataElements>();
  case DataElements::Type::HVAC_SYSTEM_FUNCTION_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<HvacSystemFunctionDescriptionDataElements>();
  case DataElements::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<
        HvacSystemFunctionOperationModeRelationDataElements>();
  case DataElements::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<
        HvacSystemFunctionPowerSequenceRelationDataElements>();
  case DataElements::Type::
      HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<HvacSystemFunctionSetpointRelationDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
