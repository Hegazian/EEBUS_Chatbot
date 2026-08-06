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

#include <keo_datagram/incentivetable/IncentiveDataElements.h>
#include <keo_datagram/incentivetable/IncentiveDescriptionDataElements.h>
#include <keo_datagram/incentivetable/IncentiveDescriptionListData.h>
#include <keo_datagram/incentivetable/IncentiveDescriptionListDataSelectors.h>
#include <keo_datagram/incentivetable/IncentiveListData.h>
#include <keo_datagram/incentivetable/IncentiveListDataSelectors.h>
#include <keo_datagram/incentivetable/IncentiveTableConstraintsData.h>
#include <keo_datagram/incentivetable/IncentiveTableConstraintsDataElements.h>
#include <keo_datagram/incentivetable/IncentiveTableConstraintsDataSelectors.h>
#include <keo_datagram/incentivetable/IncentiveTableData.h>
#include <keo_datagram/incentivetable/IncentiveTableDataElements.h>
#include <keo_datagram/incentivetable/IncentiveTableDataSelectors.h>
#include <keo_datagram/incentivetable/IncentiveTableDescriptionData.h>
#include <keo_datagram/incentivetable/IncentiveTableDescriptionDataElements.h>
#include <keo_datagram/incentivetable/IncentiveTableDescriptionDataSelectors.h>
#include <keo_datagram/incentivetable/TariffBoundaryRelationDataElements.h>
#include <keo_datagram/incentivetable/TariffBoundaryRelationListData.h>
#include <keo_datagram/incentivetable/TariffBoundaryRelationListDataSelectors.h>
#include <keo_datagram/incentivetable/TariffDataElements.h>
#include <keo_datagram/incentivetable/TariffDescriptionDataElements.h>
#include <keo_datagram/incentivetable/TariffDescriptionListData.h>
#include <keo_datagram/incentivetable/TariffDescriptionListDataSelectors.h>
#include <keo_datagram/incentivetable/TariffListData.h>
#include <keo_datagram/incentivetable/TariffListDataSelectors.h>
#include <keo_datagram/incentivetable/TariffOverallConstraintsData.h>
#include <keo_datagram/incentivetable/TariffOverallConstraintsDataElements.h>
#include <keo_datagram/incentivetable/TariffTierRelationDataElements.h>
#include <keo_datagram/incentivetable/TariffTierRelationListData.h>
#include <keo_datagram/incentivetable/TariffTierRelationListDataSelectors.h>
#include <keo_datagram/incentivetable/TierBoundaryDataElements.h>
#include <keo_datagram/incentivetable/TierBoundaryDescriptionDataElements.h>
#include <keo_datagram/incentivetable/TierBoundaryDescriptionListData.h>
#include <keo_datagram/incentivetable/TierBoundaryDescriptionListDataSelectors.h>
#include <keo_datagram/incentivetable/TierBoundaryListData.h>
#include <keo_datagram/incentivetable/TierBoundaryListDataSelectors.h>
#include <keo_datagram/incentivetable/TierDataElements.h>
#include <keo_datagram/incentivetable/TierDescriptionDataElements.h>
#include <keo_datagram/incentivetable/TierDescriptionListData.h>
#include <keo_datagram/incentivetable/TierDescriptionListDataSelectors.h>
#include <keo_datagram/incentivetable/TierIncentiveRelationDataElements.h>
#include <keo_datagram/incentivetable/TierIncentiveRelationListData.h>
#include <keo_datagram/incentivetable/TierIncentiveRelationListDataSelectors.h>
#include <keo_datagram/incentivetable/TierListData.h>
#include <keo_datagram/incentivetable/TierListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class IncentiveTableDatagramPlugin : public KeoDatagramPlugin {
public:
  IncentiveTableDatagramPlugin();
  virtual ~IncentiveTableDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(IncentiveTableDatagramPlugin,
                    "IncentiveTable Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

IncentiveTableDatagramPlugin::IncentiveTableDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

IncentiveTableDatagramPlugin::~IncentiveTableDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new IncentiveTableDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
IncentiveTableDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::INCENTIVE_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<IncentiveDescriptionListData>();
  case CmdData::Type::INCENTIVE_LIST_DATA_TYPE:
    return std::make_shared<IncentiveListData>();
  case CmdData::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_TYPE:
    return std::make_shared<TariffOverallConstraintsData>();
  case CmdData::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_TYPE:
    return std::make_shared<IncentiveTableConstraintsData>();
  case CmdData::Type::INCENTIVE_TABLE_DATA_TYPE:
    return std::make_shared<IncentiveTableData>();
  case CmdData::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_TYPE:
    return std::make_shared<IncentiveTableDescriptionData>();
  case CmdData::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_TYPE:
    return std::make_shared<TariffBoundaryRelationListData>();
  case CmdData::Type::TARIFF_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<TariffDescriptionListData>();
  case CmdData::Type::TARIFF_LIST_DATA_TYPE:
    return std::make_shared<TariffListData>();
  case CmdData::Type::TARIFF_TIER_RELATION_LIST_DATA_TYPE:
    return std::make_shared<TariffTierRelationListData>();
  case CmdData::Type::TIER_BOUNDARY_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<TierBoundaryDescriptionListData>();
  case CmdData::Type::TIER_BOUNDARY_LIST_DATA_TYPE:
    return std::make_shared<TierBoundaryListData>();
  case CmdData::Type::TIER_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<TierDescriptionListData>();
  case CmdData::Type::TIER_INCENTIVE_RELATION_LIST_DATA_TYPE:
    return std::make_shared<TierIncentiveRelationListData>();
  case CmdData::Type::TIER_LIST_DATA_TYPE:
    return std::make_shared<TierListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr IncentiveTableDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::INCENTIVE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<IncentiveDescriptionListDataSelectors>();
  case DataSelectors::Type::INCENTIVE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<IncentiveListDataSelectors>();
  case DataSelectors::Type::TARIFF_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TariffListDataSelectors>();
  case DataSelectors::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_SELECTORS_TYPE:
    return std::make_shared<IncentiveTableConstraintsDataSelectors>();
  case DataSelectors::Type::INCENTIVE_TABLE_DATA_SELECTORS_TYPE:
    return std::make_shared<IncentiveTableDataSelectors>();
  case DataSelectors::Type::TARIFF_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TariffDescriptionListDataSelectors>();
  case DataSelectors::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_SELECTORS_TYPE:
    return std::make_shared<IncentiveTableDescriptionDataSelectors>();
  case DataSelectors::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TariffBoundaryRelationListDataSelectors>();
  case DataSelectors::Type::TARIFF_TIER_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TariffTierRelationListDataSelectors>();
  case DataSelectors::Type::TIER_BOUNDARY_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TierBoundaryDescriptionListDataSelectors>();
  case DataSelectors::Type::TIER_BOUNDARY_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TierBoundaryListDataSelectors>();
  case DataSelectors::Type::TIER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TierDescriptionListDataSelectors>();
  case DataSelectors::Type::TIER_INCENTIVE_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TierIncentiveRelationListDataSelectors>();
  case DataSelectors::Type::TIER_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TierListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr IncentiveTableDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::INCENTIVE_DATA_ELEMENTS_TYPE:
    return std::make_shared<IncentiveDataElements>();
  case DataElements::Type::INCENTIVE_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<IncentiveDescriptionDataElements>();
  case DataElements::Type::TARIFF_DATA_ELEMENTS_TYPE:
    return std::make_shared<TariffDataElements>();
  case DataElements::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<TariffOverallConstraintsDataElements>();
  case DataElements::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<IncentiveTableConstraintsDataElements>();
  case DataElements::Type::TIER_DATA_ELEMENTS_TYPE:
    return std::make_shared<TierDataElements>();
  case DataElements::Type::TIER_BOUNDARY_DATA_ELEMENTS_TYPE:
    return std::make_shared<TierBoundaryDataElements>();
  case DataElements::Type::INCENTIVE_TABLE_DATA_ELEMENTS_TYPE:
    return std::make_shared<IncentiveTableDataElements>();
  case DataElements::Type::TARIFF_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TariffDescriptionDataElements>();
  case DataElements::Type::TIER_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TierDescriptionDataElements>();
  case DataElements::Type::TIER_BOUNDARY_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TierBoundaryDescriptionDataElements>();
  case DataElements::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<IncentiveTableDescriptionDataElements>();
  case DataElements::Type::TARIFF_BOUNDARY_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TariffBoundaryRelationDataElements>();
  case DataElements::Type::TARIFF_TIER_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TariffTierRelationDataElements>();
  case DataElements::Type::TIER_INCENTIVE_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TierIncentiveRelationDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
