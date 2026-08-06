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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEINCENTIVESLOT_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEINCENTIVESLOT_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveTableTier.h>
#include <keo_datagram/timetable/TimeTableData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveTableIncentiveSlot
 */
class IncentiveTableIncentiveSlot : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveTableIncentiveSlot();

  /**
   * Construct an instance of this class and set its member.
   * @param c_timeInterval the member to set
   * @param c_tier the member to set
   */
  IncentiveTableIncentiveSlot(const TimeTableData &c_timeInterval,
                              const std::vector<IncentiveTableTier> &c_tier);

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
  bool operator==(const IncentiveTableIncentiveSlot &c_classObject) const;

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
  bool operator!=(const IncentiveTableIncentiveSlot &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member TimeInterval.
   * @param c_timeInterval Value to set
   */
  void setTimeInterval(const TimeTableData &c_timeInterval);

  /**
   * Returns const reference to member TimeInterval.
   * @return const reference to member timeInterval
   */
  const TimeTableData &getTimeInterval() const;

  /**
   * Returns if member TimeInterval is set.
   * @retval true member TimeInterval is set
   * @retval false member TimeInterval is not set
   */
  bool getTimeIntervalIsSet() const;

  /**
   * Unsets member TimeInterval
   */
  void cleanTimeInterval();

  /**
   * Set member Tier.
   * @param c_tier Value to set
   */
  void setTier(const std::vector<IncentiveTableTier> &c_tier);

  /**
   * Returns const reference to member Tier.
   * @return const reference to member tier
   */
  const std::vector<IncentiveTableTier> &getTier() const;

  /**
   * Returns if member Tier is set.
   * @retval true member Tier is set
   * @retval false member Tier is not set
   */
  bool getTierIsSet() const;

  /**
   * Unsets member Tier
   */
  void cleanTier();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeIntervalIsSet;
  TimeTableData m_timeInterval;

  bool m_tierIsSet;
  std::vector<IncentiveTableTier> m_tier;
};

//! typedef for non-const smart pointer type IncentiveTableIncentiveSlot
using IncentiveTableIncentiveSlotPtr =
    std::shared_ptr<IncentiveTableIncentiveSlot>;

//! typedef for const type IncentiveTableIncentiveSlot
using IncentiveTableIncentiveSlotConst = const IncentiveTableIncentiveSlot;

//! typedef for const type IncentiveTableIncentiveSlot
using IncentiveTableIncentiveSlotConstPtr =
    std::shared_ptr<IncentiveTableIncentiveSlotConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEINCENTIVESLOT_H_