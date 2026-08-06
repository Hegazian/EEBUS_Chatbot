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

#ifndef KEO_DATAGRAM_SETPOINT_SETPOINTLISTDATASELECTORS_H_
#define KEO_DATAGRAM_SETPOINT_SETPOINTLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/setpoint/SetpointData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSetpoint
 * @{
 */

/**
 * Declaration SetpointListDataSelectors
 */
class SetpointListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  SetpointListDataSelectors();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_setpointId the member to set
   */
  explicit SetpointListDataSelectors(const xs_unsignedInt &c_setpointId);

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
  bool operator==(const SetpointListDataSelectors &c_classObject) const;

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
  bool operator!=(const SetpointListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member SetpointId.
   * @param c_setpointId Value to set
   */
  void setSetpointId(const xs_unsignedInt &c_setpointId);

  /**
   * Returns const reference to member SetpointId.
   * @return const reference to member setpointId
   */
  const xs_unsignedInt &getSetpointId() const;

  /**
   * Returns if member SetpointId is set.
   * @retval true member SetpointId is set
   * @retval false member SetpointId is not set
   */
  bool getSetpointIdIsSet() const;

  /**
   * Unsets member SetpointId
   */
  void cleanSetpointId();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const SetpointData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_setpointIdIsSet;
  xs_unsignedInt m_setpointId;
};

//! typedef for non-const smart pointer type SetpointListDataSelectors
using SetpointListDataSelectorsPtr = std::shared_ptr<SetpointListDataSelectors>;

//! typedef for const type SetpointListDataSelectors
using SetpointListDataSelectorsConst = const SetpointListDataSelectors;

//! typedef for const type SetpointListDataSelectors
using SetpointListDataSelectorsConstPtr =
    std::shared_ptr<SetpointListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SETPOINT_SETPOINTLISTDATASELECTORS_H_