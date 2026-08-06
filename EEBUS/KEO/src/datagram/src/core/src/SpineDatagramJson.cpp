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

#include "KeoJsonValue.h"
#include "json.h"
#include <keo_datagram/core/SpineDatagramJson.h>

namespace keo_datagram {

bool SpineDatagramJson::getPayloadFromJson(
    Payload &r_payload, const std::vector<char> &c_jsonArray) {
  Json::CharReaderBuilder builder;
  Json::Value root;
  std::string parserErrors;
  std::string jsonString(c_jsonArray.begin(), c_jsonArray.end());
  std::istringstream ss(jsonString);
  bool result = Json::parseFromStream(builder, ss, &root, &parserErrors);
  return result &&
         static_cast<KeoJsonTransformable *>(&r_payload)
             ->fromJson(static_cast<KeoJsonValue *>(&root));
}
std::vector<char> SpineDatagramJson::generateCmdToJson(const CmdPtr &c_pCmd) {
  std::string jsonString =
      static_cast<KeoJsonTransformable *>(c_pCmd.get())->toJson();
  return std::vector<char>(jsonString.begin(), jsonString.end());
}
}