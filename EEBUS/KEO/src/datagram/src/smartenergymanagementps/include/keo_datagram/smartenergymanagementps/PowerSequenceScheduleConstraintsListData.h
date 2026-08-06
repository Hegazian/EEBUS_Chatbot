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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSLISTDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceScheduleConstraintsListData
 */
class PowerSequenceScheduleConstraintsListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceScheduleConstraintsListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_powerSequenceScheduleConstraintsData the member to set
   */
  explicit PowerSequenceScheduleConstraintsListData(
      const std::vector<PowerSequenceScheduleConstraintsData>
          &c_powerSequenceScheduleConstraintsData);

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
  bool operator==(
      const PowerSequenceScheduleConstraintsListData &c_classObject) const;

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
  bool operator!=(
      const PowerSequenceScheduleConstraintsListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member PowerSequenceScheduleConstraintsData.
   * @param c_powerSequenceScheduleConstraintsData Value to set
   */
  void setPowerSequenceScheduleConstraintsData(
      const std::vector<PowerSequenceScheduleConstraintsData>
          &c_powerSequenceScheduleConstraintsData);

  /**
   * Returns const reference to member PowerSequenceScheduleConstraintsData.
   * @return const reference to member powerSequenceScheduleConstraintsData
   */
  const std::vector<PowerSequenceScheduleConstraintsData> &
  getPowerSequenceScheduleConstraintsData() const;

  /**
   * Returns if member PowerSequenceScheduleConstraintsData is set.
   * @retval true member PowerSequenceScheduleConstraintsData is set
   * @retval false member PowerSequenceScheduleConstraintsData is not set
   */
  bool getPowerSequenceScheduleConstraintsDataIsSet() const;

  /**
   * Unsets member PowerSequenceScheduleConstraintsData
   */
  void cleanPowerSequenceScheduleConstraintsData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_powerSequenceScheduleConstraintsDataIsSet;
  std::vector<PowerSequenceScheduleConstraintsData>
      m_powerSequenceScheduleConstraintsData;
};

//! typedef for non-const smart pointer type
//! PowerSequenceScheduleConstraintsListData
using PowerSequenceScheduleConstraintsListDataPtr =
    std::shared_ptr<PowerSequenceScheduleConstraintsListData>;

//! typedef for const type PowerSequenceScheduleConstraintsListData
using PowerSequenceScheduleConstraintsListDataConst =
    const PowerSequenceScheduleConstraintsListData;

//! typedef for const type PowerSequenceScheduleConstraintsListData
using PowerSequenceScheduleConstraintsListDataConstPtr =
    std::shared_ptr<PowerSequenceScheduleConstraintsListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONSTRAINTSLISTDATA_H_