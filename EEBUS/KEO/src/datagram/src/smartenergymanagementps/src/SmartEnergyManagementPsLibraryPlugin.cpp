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

#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequencePriceCalculationRequestCall.h>
#include <keo_datagram/smartenergymanagementps/PowerSequencePriceCalculationRequestCallElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequencePriceDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequencePriceListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequencePriceListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConfigurationRequestCall.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConfigurationRequestCallElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceStateDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceStateListData.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceStateListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsListData.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleListData.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueListData.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsConfigurationRequestCall.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsConfigurationRequestCallElements.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsData.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsDataElements.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceCalculationRequestCall.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceCalculationRequestCallElements.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceData.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceDataElements.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class SmartEnergyManagementPsDatagramPlugin : public KeoDatagramPlugin {
public:
  SmartEnergyManagementPsDatagramPlugin();
  virtual ~SmartEnergyManagementPsDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(SmartEnergyManagementPsDatagramPlugin,
                    "SmartEnergyManagementPs Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

SmartEnergyManagementPsDatagramPlugin::SmartEnergyManagementPsDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

SmartEnergyManagementPsDatagramPlugin::
    ~SmartEnergyManagementPsDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new SmartEnergyManagementPsDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr SmartEnergyManagementPsDatagramPlugin::createCmdData(
    const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_TYPE:
    return std::make_shared<PowerSequenceAlternativesRelationListData>();
  case CmdData::Type::POWER_SEQUENCE_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<PowerSequenceDescriptionListData>();
  case CmdData::Type::POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_TYPE:
    return std::make_shared<PowerSequenceNodeScheduleInformationData>();
  case CmdData::Type::POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_TYPE:
    return std::make_shared<PowerSequencePriceCalculationRequestCall>();
  case CmdData::Type::POWER_SEQUENCE_PRICE_LIST_DATA_TYPE:
    return std::make_shared<PowerSequencePriceListData>();
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_TYPE:
    return std::make_shared<PowerSequenceScheduleConfigurationRequestCall>();
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<PowerSequenceScheduleConstraintsListData>();
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_TYPE:
    return std::make_shared<PowerSequenceScheduleListData>();
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_TYPE:
    return std::make_shared<PowerSequenceSchedulePreferenceListData>();
  case CmdData::Type::POWER_SEQUENCE_STATE_LIST_DATA_TYPE:
    return std::make_shared<PowerSequenceStateListData>();
  case CmdData::Type::POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<PowerTimeSlotScheduleConstraintsListData>();
  case CmdData::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_TYPE:
    return std::make_shared<PowerTimeSlotScheduleListData>();
  case CmdData::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_TYPE:
    return std::make_shared<PowerTimeSlotValueListData>();
  case CmdData::Type::
      SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_TYPE:
    return std::make_shared<SmartEnergyManagementPsConfigurationRequestCall>();
  case CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_TYPE:
    return std::make_shared<SmartEnergyManagementPsData>();
  case CmdData::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_TYPE:
    return std::make_shared<
        SmartEnergyManagementPsPriceCalculationRequestCall>();
  case CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_TYPE:
    return std::make_shared<SmartEnergyManagementPsPriceData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr SmartEnergyManagementPsDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::
      POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        PowerSequenceAlternativesRelationListDataSelectors>();
  case DataSelectors::Type::POWER_SEQUENCE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<PowerSequenceDescriptionListDataSelectors>();
  case DataSelectors::Type::POWER_SEQUENCE_PRICE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<PowerSequencePriceListDataSelectors>();
  case DataSelectors::Type::
      POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        PowerSequenceScheduleConstraintsListDataSelectors>();
  case DataSelectors::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<PowerSequenceScheduleListDataSelectors>();
  case DataSelectors::Type::
      POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<PowerSequenceSchedulePreferenceListDataSelectors>();
  case DataSelectors::Type::POWER_SEQUENCE_STATE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<PowerSequenceStateListDataSelectors>();
  case DataSelectors::Type::
      POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        PowerTimeSlotScheduleConstraintsListDataSelectors>();
  case DataSelectors::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<PowerTimeSlotScheduleListDataSelectors>();
  case DataSelectors::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<PowerTimeSlotValueListDataSelectors>();
  case DataSelectors::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_SELECTORS_TYPE:
    return std::make_shared<SmartEnergyManagementPsDataSelectors>();
  case DataSelectors::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_SELECTORS_TYPE:
    return std::make_shared<SmartEnergyManagementPsPriceDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr SmartEnergyManagementPsDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::
      POWER_SEQUENCE_ALTERNATIVES_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerSequenceAlternativesRelationDataElements>();
  case DataElements::Type::POWER_SEQUENCE_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerSequenceDescriptionDataElements>();
  case DataElements::Type::
      POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerSequenceNodeScheduleInformationDataElements>();
  case DataElements::Type::
      POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_ELEMENTS_TYPE:
    return std::make_shared<PowerSequencePriceCalculationRequestCallElements>();
  case DataElements::Type::POWER_SEQUENCE_PRICE_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerSequencePriceDataElements>();
  case DataElements::Type::
      POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_ELEMENTS_TYPE:
    return std::make_shared<
        PowerSequenceScheduleConfigurationRequestCallElements>();
  case DataElements::Type::
      POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerSequenceScheduleConstraintsDataElements>();
  case DataElements::Type::POWER_SEQUENCE_SCHEDULE_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerSequenceScheduleDataElements>();
  case DataElements::Type::
      POWER_SEQUENCE_SCHEDULE_PREFERENCE_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerSequenceSchedulePreferenceDataElements>();
  case DataElements::Type::POWER_SEQUENCE_STATE_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerSequenceStateDataElements>();
  case DataElements::Type::
      POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerTimeSlotScheduleConstraintsDataElements>();
  case DataElements::Type::POWER_TIME_SLOT_SCHEDULE_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerTimeSlotScheduleDataElements>();
  case DataElements::Type::POWER_TIME_SLOT_VALUE_DATA_ELEMENTS_TYPE:
    return std::make_shared<PowerTimeSlotValueDataElements>();
  case DataElements::Type::
      SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_ELEMENTS_TYPE:
    return std::make_shared<
        SmartEnergyManagementPsConfigurationRequestCallElements>();
  case DataElements::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_ELEMENTS_TYPE:
    return std::make_shared<SmartEnergyManagementPsDataElements>();
  case DataElements::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_ELEMENTS_TYPE:
    return std::make_shared<
        SmartEnergyManagementPsPriceCalculationRequestCallElements>();
  case DataElements::Type::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_ELEMENTS_TYPE:
    return std::make_shared<SmartEnergyManagementPsPriceDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
