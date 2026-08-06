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

#ifndef KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONLISTDATA_H_
#define KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/setpoint/SetpointDescriptionData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSetpoint
 * @{
 */

/**
 * Declaration SetpointDescriptionListData
 */
class SetpointDescriptionListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  SetpointDescriptionListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_setpointDescriptionData the member to set
   */
  explicit SetpointDescriptionListData(
      const std::vector<SetpointDescriptionData> &c_setpointDescriptionData);

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
  bool operator==(const SetpointDescriptionListData &c_classObject) const;

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
  bool operator!=(const SetpointDescriptionListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member SetpointDescriptionData.
   * @param c_setpointDescriptionData Value to set
   */
  void setSetpointDescriptionData(
      const std::vector<SetpointDescriptionData> &c_setpointDescriptionData);

  /**
   * Returns const reference to member SetpointDescriptionData.
   * @return const reference to member setpointDescriptionData
   */
  const std::vector<SetpointDescriptionData> &
  getSetpointDescriptionData() const;

  /**
   * Returns if member SetpointDescriptionData is set.
   * @retval true member SetpointDescriptionData is set
   * @retval false member SetpointDescriptionData is not set
   */
  bool getSetpointDescriptionDataIsSet() const;

  /**
   * Unsets member SetpointDescriptionData
   */
  void cleanSetpointDescriptionData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_setpointDescriptionDataIsSet;
  std::vector<SetpointDescriptionData> m_setpointDescriptionData;
};

//! typedef for non-const smart pointer type SetpointDescriptionListData
using SetpointDescriptionListDataPtr =
    std::shared_ptr<SetpointDescriptionListData>;

//! typedef for const type SetpointDescriptionListData
using SetpointDescriptionListDataConst = const SetpointDescriptionListData;

//! typedef for const type SetpointDescriptionListData
using SetpointDescriptionListDataConstPtr =
    std::shared_ptr<SetpointDescriptionListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONLISTDATA_H_