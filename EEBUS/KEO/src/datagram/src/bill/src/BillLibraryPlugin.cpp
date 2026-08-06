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

#include <keo_datagram/bill/BillConstraintsDataElements.h>
#include <keo_datagram/bill/BillConstraintsListData.h>
#include <keo_datagram/bill/BillConstraintsListDataSelectors.h>
#include <keo_datagram/bill/BillDataElements.h>
#include <keo_datagram/bill/BillDescriptionDataElements.h>
#include <keo_datagram/bill/BillDescriptionListData.h>
#include <keo_datagram/bill/BillDescriptionListDataSelectors.h>
#include <keo_datagram/bill/BillListData.h>
#include <keo_datagram/bill/BillListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class BillDatagramPlugin : public KeoDatagramPlugin {
public:
  BillDatagramPlugin();
  virtual ~BillDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(BillDatagramPlugin, "Bill Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

BillDatagramPlugin::BillDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

BillDatagramPlugin::~BillDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() { return new BillDatagramPlugin; }

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr BillDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::BILL_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<BillConstraintsListData>();
  case CmdData::Type::BILL_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<BillDescriptionListData>();
  case CmdData::Type::BILL_LIST_DATA_TYPE:
    return std::make_shared<BillListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr
BillDatagramPlugin::createDataSelectors(const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::BILL_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<BillConstraintsListDataSelectors>();
  case DataSelectors::Type::BILL_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<BillDescriptionListDataSelectors>();
  case DataSelectors::Type::BILL_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<BillListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr
BillDatagramPlugin::createDataElements(const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::BILL_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<BillConstraintsDataElements>();
  case DataElements::Type::BILL_DATA_ELEMENTS_TYPE:
    return std::make_shared<BillDataElements>();
  case DataElements::Type::BILL_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<BillDescriptionDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
