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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTJOININGMODEDATA_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTJOININGMODEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementJoiningModeData
 */
class NetworkManagementJoiningModeData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementJoiningModeData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_setup the member to set
   */
  explicit NetworkManagementJoiningModeData(const xs_string &c_setup);

  /**
   * Equality operator
   *
   * Two objects a and b are considered equal if and only if
   *     - all members that are set in a are also set in b
   *     - all members that are set in b are also set in a
   *     - all members that are set in a and b are equal
   *
   * @param c_classObject the object to compare to
   * @return true if the objects are equal
   */
  bool operator==(const NetworkManagementJoiningModeData &c_classObject) const;

  /**
   * Inequality operator
   *
   * Two objects a and b are considered not equal if and only if
   *     - at least one member that is set in a is not set in b
   *     - at least one member that is set in b is not set in a
   *     - at least one member that is set in a and b differs
   *
   * @param c_classObject the object to compare to
   * @return true, if the objects are not equal
   */
  bool operator!=(const NetworkManagementJoiningModeData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member Setup.
   * @param c_setup Value to set
   */
  void setSetup(const xs_string &c_setup);

  /**
   * Returns const reference to member Setup.
   * @return const reference to member setup
   */
  const xs_string &getSetup() const;

  /**
   * Returns if member Setup is set.
   * @retval true member Setup is set
   * @retval false member Setup is not set
   */
  bool getSetupIsSet() const;

  /**
   * Unsets member Setup
   */
  void cleanSetup();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_setupIsSet;
  xs_string m_setup;
};

//! typedef for non-const smart pointer type NetworkManagementJoiningModeData
using NetworkManagementJoiningModeDataPtr =
    std::shared_ptr<NetworkManagementJoiningModeData>;

//! typedef for const type NetworkManagementJoiningModeData
using NetworkManagementJoiningModeDataConst =
    const NetworkManagementJoiningModeData;

//! typedef for const type NetworkManagementJoiningModeData
using NetworkManagementJoiningModeDataConstPtr =
    std::shared_ptr<NetworkManagementJoiningModeDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTJOININGMODEDATA_H_