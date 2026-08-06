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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULECONSTRAINTSLISTDATASELECTORS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULECONSTRAINTSLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerTimeSlotScheduleConstraintsListDataSelectors
 */
class PowerTimeSlotScheduleConstraintsListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  PowerTimeSlotScheduleConstraintsListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_sequenceId the member to set
   * @param c_slotNumber the member to set
   */
  PowerTimeSlotScheduleConstraintsListDataSelectors(
      const xs_unsignedInt &c_sequenceId, const xs_unsignedInt &c_slotNumber);

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
  bool operator==(const PowerTimeSlotScheduleConstraintsListDataSelectors
                      &c_classObject) const;

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
  bool operator!=(const PowerTimeSlotScheduleConstraintsListDataSelectors
                      &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member SequenceId.
   * @param c_sequenceId Value to set
   */
  void setSequenceId(const xs_unsignedInt &c_sequenceId);

  /**
   * Returns const reference to member SequenceId.
   * @return const reference to member sequenceId
   */
  const xs_unsignedInt &getSequenceId() const;

  /**
   * Returns if member SequenceId is set.
   * @retval true member SequenceId is set
   * @retval false member SequenceId is not set
   */
  bool getSequenceIdIsSet() const;

  /**
   * Unsets member SequenceId
   */
  void cleanSequenceId();

  /**
   * Set member SlotNumber.
   * @param c_slotNumber Value to set
   */
  void setSlotNumber(const xs_unsignedInt &c_slotNumber);

  /**
   * Returns const reference to member SlotNumber.
   * @return const reference to member slotNumber
   */
  const xs_unsignedInt &getSlotNumber() const;

  /**
   * Returns if member SlotNumber is set.
   * @retval true member SlotNumber is set
   * @retval false member SlotNumber is not set
   */
  bool getSlotNumberIsSet() const;

  /**
   * Unsets member SlotNumber
   */
  void cleanSlotNumber();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const PowerTimeSlotScheduleConstraintsData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_slotNumberIsSet;
  xs_unsignedInt m_slotNumber;
};

//! typedef for non-const smart pointer type
//! PowerTimeSlotScheduleConstraintsListDataSelectors
using PowerTimeSlotScheduleConstraintsListDataSelectorsPtr =
    std::shared_ptr<PowerTimeSlotScheduleConstraintsListDataSelectors>;

//! typedef for const type PowerTimeSlotScheduleConstraintsListDataSelectors
using PowerTimeSlotScheduleConstraintsListDataSelectorsConst =
    const PowerTimeSlotScheduleConstraintsListDataSelectors;

//! typedef for const type PowerTimeSlotScheduleConstraintsListDataSelectors
using PowerTimeSlotScheduleConstraintsListDataSelectorsConstPtr =
    std::shared_ptr<PowerTimeSlotScheduleConstraintsListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTSCHEDULECONSTRAINTSLISTDATASELECTORS_H_