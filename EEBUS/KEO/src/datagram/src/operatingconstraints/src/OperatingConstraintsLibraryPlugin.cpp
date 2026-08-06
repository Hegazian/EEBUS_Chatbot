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

#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationDataElements.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationListDataSelectors.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptDataElements.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptListDataSelectors.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionDataElements.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionListDataSelectors.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelDataElements.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelListDataSelectors.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeDataElements.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeListDataSelectors.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationDataElements.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationListData.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class OperatingConstraintsDatagramPlugin : public KeoDatagramPlugin {
public:
  OperatingConstraintsDatagramPlugin();
  virtual ~OperatingConstraintsDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(OperatingConstraintsDatagramPlugin,
                    "OperatingConstraints Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

OperatingConstraintsDatagramPlugin::OperatingConstraintsDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

OperatingConstraintsDatagramPlugin::~OperatingConstraintsDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new OperatingConstraintsDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr OperatingConstraintsDatagramPlugin::createCmdData(
    const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::OPERATING_CONSTRAINTS_DURATION_LIST_DATA_TYPE:
    return std::make_shared<OperatingConstraintsDurationListData>();
  case CmdData::Type::OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_TYPE:
    return std::make_shared<OperatingConstraintsInterruptListData>();
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<OperatingConstraintsPowerDescriptionListData>();
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_TYPE:
    return std::make_shared<OperatingConstraintsPowerLevelListData>();
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_TYPE:
    return std::make_shared<OperatingConstraintsPowerRangeListData>();
  case CmdData::Type::OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_TYPE:
    return std::make_shared<OperatingConstraintsResumeImplicationListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr OperatingConstraintsDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_DURATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<OperatingConstraintsDurationListDataSelectors>();
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<OperatingConstraintsInterruptListDataSelectors>();
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        OperatingConstraintsPowerDescriptionListDataSelectors>();
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<OperatingConstraintsPowerLevelListDataSelectors>();
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<OperatingConstraintsPowerRangeListDataSelectors>();
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        OperatingConstraintsResumeImplicationListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr OperatingConstraintsDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::OPERATING_CONSTRAINTS_DURATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<OperatingConstraintsDurationDataElements>();
  case DataElements::Type::OPERATING_CONSTRAINTS_INTERRUPT_DATA_ELEMENTS_TYPE:
    return std::make_shared<OperatingConstraintsInterruptDataElements>();
  case DataElements::Type::
      OPERATING_CONSTRAINTS_POWER_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<OperatingConstraintsPowerDescriptionDataElements>();
  case DataElements::Type::OPERATING_CONSTRAINTS_POWER_LEVEL_DATA_ELEMENTS_TYPE:
    return std::make_shared<OperatingConstraintsPowerLevelDataElements>();
  case DataElements::Type::OPERATING_CONSTRAINTS_POWER_RANGE_DATA_ELEMENTS_TYPE:
    return std::make_shared<OperatingConstraintsPowerRangeDataElements>();
  case DataElements::Type::
      OPERATING_CONSTRAINTS_RESUME_IMPLICATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<
        OperatingConstraintsResumeImplicationDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
