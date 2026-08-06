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

#ifndef KEO_DATAGRAM_CORE_KEODATAGRAMPLUGIN_H_
#define KEO_DATAGRAM_CORE_KEODATAGRAMPLUGIN_H_

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/DataSelectors.h>

namespace keo_datagram {

class KeoDatagramPlugin;

// Define the API version.
// This value is incremented whenever there are ABI breaking changes.
const int KEO_DATAGRAM_PLUGIN_API_VERSION = 2;

// Plugin details structure that's exposed to the application.
struct KeoDatagramPluginDetails {
  int apiVersion;
  const char *className;
  const char *pluginName;
  const char *spineVersion;
  const char *spineVersionString;
};

#define KEO_DATAGRAM_PLUGIN(classType, pluginName, spineVersion,               \
                            spineVersionString)                                \
  extern "C" {                                                                 \
  KeoDatagramPluginDetails datagramPluginExports = {                           \
      KEO_DATAGRAM_PLUGIN_API_VERSION, #classType, pluginName, spineVersion,   \
      spineVersionString};                                                     \
  }

class KeoDatagramPlugin {
public:
  virtual ~KeoDatagramPlugin() {}

  virtual CmdDataPtr createCmdData(const CmdData::Type type) const = 0;
  virtual DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const = 0;
  virtual DataElementsPtr
  createDataElements(const DataElements::Type type) const = 0;
};

typedef KeoDatagramPlugin *createPlugin_t();
typedef void destroyPlugin_t(KeoDatagramPlugin *);
}

#endif // KEO_DATAGRAM_CORE_KEODATAGRAMPLUGIN_H_