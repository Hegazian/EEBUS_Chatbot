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

#ifndef KEO_DATAGRAM_CORE_SPINEDTATAGRAMJSON_H_
#define KEO_DATAGRAM_CORE_SPINEDTATAGRAMJSON_H_

#include <keo_datagram/core/Datagram.h>
#include <vector>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * \deprecated Use Datagram methods (Datagram.h) instead.
 */
class SpineDatagramJson {
public:
  SpineDatagramJson() = delete;

  /**
   * Create a Datagram from a JSON string.
   * \deprecated Use Datagram::fromJson(std::string) instead.
   * @code Datagram::fromJson(std::string(c_jsonArray.begin(),
   * c_jsonArray.end()));
   */
  static DatagramPtr getDatagramFromJson(const std::vector<char> &c_jsonArray);

  /**
   * Generate a JSON representation of a datagram.
   * \deprecated Use Datagram::toJson() instead.
   * \code{.cpp}
   *  std::string jsonString = c_datagram->toJson();
   *  std::vector<char> jsonString = std::vector<char>(jsonString.begin(),
   * jsonString.end());
   * \endcode
   */
  static std::vector<char> getJsonFromDatagram(const DatagramPtr &c_datagram);

  /**
   * Create a payload from JSON.
   * \deprecated
   * @param r_payload payload, to be filled
   * @param c_jsonArray JSON object
   * @return true, if successful
   */
  static bool getPayloadFromJson(Payload &r_payload,
                                 const std::vector<char> &c_jsonArray);

  /**
   * Create a JSON string from a cmd.
   * \deprecated
   * @param c_pCmd a command
   * @return a JSON representation of the datagram
   */
  static std::vector<char> generateCmdToJson(const CmdPtr &c_pCmd);
};

inline DatagramPtr
SpineDatagramJson::getDatagramFromJson(const std::vector<char> &c_jsonArray) {
  return std::make_shared<Datagram>(
      Datagram::fromJson(std::string(c_jsonArray.begin(), c_jsonArray.end())));
}

inline std::vector<char>
SpineDatagramJson::getJsonFromDatagram(const DatagramPtr &c_datagram) {
  std::string jsonString = c_datagram->toJson();
  return std::vector<char>(jsonString.begin(), jsonString.end());
}

/** @}
 */
} // end namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_SPINEDTATAGRAMJSON_H_