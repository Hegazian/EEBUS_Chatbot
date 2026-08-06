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

#include <keo_datagram/identification/IdentificationDataElements.h>
#include <keo_datagram/identification/IdentificationListData.h>
#include <keo_datagram/identification/IdentificationListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class IdentificationDatagramPlugin : public KeoDatagramPlugin {
public:
  IdentificationDatagramPlugin();
  virtual ~IdentificationDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(IdentificationDatagramPlugin,
                    "Identification Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

IdentificationDatagramPlugin::IdentificationDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

IdentificationDatagramPlugin::~IdentificationDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new IdentificationDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
IdentificationDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::IDENTIFICATION_LIST_DATA_TYPE:
    return std::make_shared<IdentificationListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr IdentificationDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::IDENTIFICATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<IdentificationListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr IdentificationDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::IDENTIFICATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<IdentificationDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
