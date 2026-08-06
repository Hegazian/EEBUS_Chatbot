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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESTATEDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESTATEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceState.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceStateDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceStateData
 */
class PowerSequenceStateData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceStateData();

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
  bool operator==(const PowerSequenceStateData &c_classObject) const;

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
  bool operator!=(const PowerSequenceStateData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member State.
   * @param c_state Value to set
   */
  void setState(const PowerSequenceState &c_state);

  /**
   * Returns const reference to member State.
   * @return const reference to member state
   */
  const PowerSequenceState &getState() const;

  /**
   * Returns if member State is set.
   * @retval true member State is set
   * @retval false member State is not set
   */
  bool getStateIsSet() const;

  /**
   * Unsets member State
   */
  void cleanState();

  /**
   * Set member ActiveSlotNumber.
   * @param c_activeSlotNumber Value to set
   */
  void setActiveSlotNumber(const xs_unsignedInt &c_activeSlotNumber);

  /**
   * Returns const reference to member ActiveSlotNumber.
   * @return const reference to member activeSlotNumber
   */
  const xs_unsignedInt &getActiveSlotNumber() const;

  /**
   * Returns if member ActiveSlotNumber is set.
   * @retval true member ActiveSlotNumber is set
   * @retval false member ActiveSlotNumber is not set
   */
  bool getActiveSlotNumberIsSet() const;

  /**
   * Unsets member ActiveSlotNumber
   */
  void cleanActiveSlotNumber();

  /**
   * Set member ElapsedSlotTime.
   * @param c_elapsedSlotTime Value to set
   */
  void setElapsedSlotTime(const xs_duration &c_elapsedSlotTime);

  /**
   * Returns const reference to member ElapsedSlotTime.
   * @return const reference to member elapsedSlotTime
   */
  const xs_duration &getElapsedSlotTime() const;

  /**
   * Returns if member ElapsedSlotTime is set.
   * @retval true member ElapsedSlotTime is set
   * @retval false member ElapsedSlotTime is not set
   */
  bool getElapsedSlotTimeIsSet() const;

  /**
   * Unsets member ElapsedSlotTime
   */
  void cleanElapsedSlotTime();

  /**
   * Set member RemainingSlotTime.
   * @param c_remainingSlotTime Value to set
   */
  void setRemainingSlotTime(const xs_duration &c_remainingSlotTime);

  /**
   * Returns const reference to member RemainingSlotTime.
   * @return const reference to member remainingSlotTime
   */
  const xs_duration &getRemainingSlotTime() const;

  /**
   * Returns if member RemainingSlotTime is set.
   * @retval true member RemainingSlotTime is set
   * @retval false member RemainingSlotTime is not set
   */
  bool getRemainingSlotTimeIsSet() const;

  /**
   * Unsets member RemainingSlotTime
   */
  void cleanRemainingSlotTime();

  /**
   * Set member SequenceRemoteControllable.
   * @param c_sequenceRemoteControllable Value to set
   */
  void
  setSequenceRemoteControllable(const xs_boolean &c_sequenceRemoteControllable);

  /**
   * Returns const reference to member SequenceRemoteControllable.
   * @return const reference to member sequenceRemoteControllable
   */
  const xs_boolean &getSequenceRemoteControllable() const;

  /**
   * Returns if member SequenceRemoteControllable is set.
   * @retval true member SequenceRemoteControllable is set
   * @retval false member SequenceRemoteControllable is not set
   */
  bool getSequenceRemoteControllableIsSet() const;

  /**
   * Unsets member SequenceRemoteControllable
   */
  void cleanSequenceRemoteControllable();

  /**
   * Set member ActiveRepetitionNumber.
   * @param c_activeRepetitionNumber Value to set
   */
  void
  setActiveRepetitionNumber(const xs_unsignedInt &c_activeRepetitionNumber);

  /**
   * Returns const reference to member ActiveRepetitionNumber.
   * @return const reference to member activeRepetitionNumber
   */
  const xs_unsignedInt &getActiveRepetitionNumber() const;

  /**
   * Returns if member ActiveRepetitionNumber is set.
   * @retval true member ActiveRepetitionNumber is set
   * @retval false member ActiveRepetitionNumber is not set
   */
  bool getActiveRepetitionNumberIsSet() const;

  /**
   * Unsets member ActiveRepetitionNumber
   */
  void cleanActiveRepetitionNumber();

  /**
   * Set member RemainingPauseTime.
   * @param c_remainingPauseTime Value to set
   */
  void setRemainingPauseTime(const xs_duration &c_remainingPauseTime);

  /**
   * Returns const reference to member RemainingPauseTime.
   * @return const reference to member remainingPauseTime
   */
  const xs_duration &getRemainingPauseTime() const;

  /**
   * Returns if member RemainingPauseTime is set.
   * @retval true member RemainingPauseTime is set
   * @retval false member RemainingPauseTime is not set
   */
  bool getRemainingPauseTimeIsSet() const;

  /**
   * Unsets member RemainingPauseTime
   */
  void cleanRemainingPauseTime();

  /**
   * @copydoc CmdData::reduce()
   */
  PowerSequenceStateData
  reduce(const PowerSequenceStateDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_stateIsSet;
  PowerSequenceState m_state;

  bool m_activeSlotNumberIsSet;
  xs_unsignedInt m_activeSlotNumber;

  bool m_elapsedSlotTimeIsSet;
  xs_duration m_elapsedSlotTime;

  bool m_remainingSlotTimeIsSet;
  xs_duration m_remainingSlotTime;

  bool m_sequenceRemoteControllableIsSet;
  xs_boolean m_sequenceRemoteControllable;

  bool m_activeRepetitionNumberIsSet;
  xs_unsignedInt m_activeRepetitionNumber;

  bool m_remainingPauseTimeIsSet;
  xs_duration m_remainingPauseTime;
};

//! typedef for non-const smart pointer type PowerSequenceStateData
using PowerSequenceStateDataPtr = std::shared_ptr<PowerSequenceStateData>;

//! typedef for const type PowerSequenceStateData
using PowerSequenceStateDataConst = const PowerSequenceStateData;

//! typedef for const type PowerSequenceStateData
using PowerSequenceStateDataConstPtr =
    std::shared_ptr<PowerSequenceStateDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESTATEDATA_H_