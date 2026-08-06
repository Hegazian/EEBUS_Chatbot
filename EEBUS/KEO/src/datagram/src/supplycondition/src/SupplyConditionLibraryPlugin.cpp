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

#include <keo_datagram/supplycondition/SupplyConditionDataElements.h>
#include <keo_datagram/supplycondition/SupplyConditionDescriptionDataElements.h>
#include <keo_datagram/supplycondition/SupplyConditionDescriptionListData.h>
#include <keo_datagram/supplycondition/SupplyConditionDescriptionListDataSelectors.h>
#include <keo_datagram/supplycondition/SupplyConditionListData.h>
#include <keo_datagram/supplycondition/SupplyConditionListDataSelectors.h>
#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationDataElements.h>
#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationListData.h>
#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class SupplyConditionDatagramPlugin : public KeoDatagramPlugin {
public:
  SupplyConditionDatagramPlugin();
  virtual ~SupplyConditionDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(SupplyConditionDatagramPlugin,
                    "SupplyCondition Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

SupplyConditionDatagramPlugin::SupplyConditionDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

SupplyConditionDatagramPlugin::~SupplyConditionDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new SupplyConditionDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
SupplyConditionDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<SupplyConditionDescriptionListData>();
  case CmdData::Type::SUPPLY_CONDITION_LIST_DATA_TYPE:
    return std::make_shared<SupplyConditionListData>();
  case CmdData::Type::SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_TYPE:
    return std::make_shared<SupplyConditionThresholdRelationListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr SupplyConditionDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::
      SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<SupplyConditionDescriptionListDataSelectors>();
  case DataSelectors::Type::SUPPLY_CONDITION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<SupplyConditionListDataSelectors>();
  case DataSelectors::Type::
      SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        SupplyConditionThresholdRelationListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr SupplyConditionDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::SUPPLY_CONDITION_DATA_ELEMENTS_TYPE:
    return std::make_shared<SupplyConditionDataElements>();
  case DataElements::Type::SUPPLY_CONDITION_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<SupplyConditionDescriptionDataElements>();
  case DataElements::Type::
      SUPPLY_CONDITION_THRESHOLD_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<SupplyConditionThresholdRelationDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
