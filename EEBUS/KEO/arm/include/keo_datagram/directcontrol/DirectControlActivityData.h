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

#ifndef KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLACTIVITYDATA_H_
#define KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLACTIVITYDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/EnergyMode.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/directcontrol/DirectControlActivityDataElements.h>
#include <keo_datagram/directcontrol/DirectControlActivityState.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDirectControl
 * @{
 */

/**
 * Declaration DirectControlActivityData
 */
class DirectControlActivityData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  DirectControlActivityData();

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
  bool operator==(const DirectControlActivityData &c_classObject) const;

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
  bool operator!=(const DirectControlActivityData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Timestamp.
   * @param c_timestamp Value to set
   */
  void setTimestamp(const AbsoluteOrRelativeTime &c_timestamp);

  /**
   * Returns const reference to member Timestamp.
   * @return const reference to member timestamp
   */
  const AbsoluteOrRelativeTime &getTimestamp() const;

  /**
   * Returns if member Timestamp is set.
   * @retval true member Timestamp is set
   * @retval false member Timestamp is not set
   */
  bool getTimestampIsSet() const;

  /**
   * Unsets member Timestamp
   */
  void cleanTimestamp();

  /**
   * Set member ActivityState.
   * @param c_activityState Value to set
   */
  void setActivityState(const DirectControlActivityState &c_activityState);

  /**
   * Returns const reference to member ActivityState.
   * @return const reference to member activityState
   */
  const DirectControlActivityState &getActivityState() const;

  /**
   * Returns if member ActivityState is set.
   * @retval true member ActivityState is set
   * @retval false member ActivityState is not set
   */
  bool getActivityStateIsSet() const;

  /**
   * Unsets member ActivityState
   */
  void cleanActivityState();

  /**
   * Set member IsActivityStateChangeable.
   * @param c_isActivityStateChangeable Value to set
   */
  void
  setIsActivityStateChangeable(const xs_boolean &c_isActivityStateChangeable);

  /**
   * Returns const reference to member IsActivityStateChangeable.
   * @return const reference to member isActivityStateChangeable
   */
  const xs_boolean &getIsActivityStateChangeable() const;

  /**
   * Returns if member IsActivityStateChangeable is set.
   * @retval true member IsActivityStateChangeable is set
   * @retval false member IsActivityStateChangeable is not set
   */
  bool getIsActivityStateChangeableIsSet() const;

  /**
   * Unsets member IsActivityStateChangeable
   */
  void cleanIsActivityStateChangeable();

  /**
   * Set member EnergyMode.
   * @param c_energyMode Value to set
   */
  void setEnergyMode(const EnergyMode &c_energyMode);

  /**
   * Returns const reference to member EnergyMode.
   * @return const reference to member energyMode
   */
  const EnergyMode &getEnergyMode() const;

  /**
   * Returns if member EnergyMode is set.
   * @retval true member EnergyMode is set
   * @retval false member EnergyMode is not set
   */
  bool getEnergyModeIsSet() const;

  /**
   * Unsets member EnergyMode
   */
  void cleanEnergyMode();

  /**
   * Set member IsEnergyModeChangeable.
   * @param c_isEnergyModeChangeable Value to set
   */
  void setIsEnergyModeChangeable(const xs_boolean &c_isEnergyModeChangeable);

  /**
   * Returns const reference to member IsEnergyModeChangeable.
   * @return const reference to member isEnergyModeChangeable
   */
  const xs_boolean &getIsEnergyModeChangeable() const;

  /**
   * Returns if member IsEnergyModeChangeable is set.
   * @retval true member IsEnergyModeChangeable is set
   * @retval false member IsEnergyModeChangeable is not set
   */
  bool getIsEnergyModeChangeableIsSet() const;

  /**
   * Unsets member IsEnergyModeChangeable
   */
  void cleanIsEnergyModeChangeable();

  /**
   * Set member Power.
   * @param c_power Value to set
   */
  void setPower(const ScaledNumber &c_power);

  /**
   * Returns const reference to member Power.
   * @return const reference to member power
   */
  const ScaledNumber &getPower() const;

  /**
   * Returns if member Power is set.
   * @retval true member Power is set
   * @retval false member Power is not set
   */
  bool getPowerIsSet() const;

  /**
   * Unsets member Power
   */
  void cleanPower();

  /**
   * Set member IsPowerChangeable.
   * @param c_isPowerChangeable Value to set
   */
  void setIsPowerChangeable(const xs_boolean &c_isPowerChangeable);

  /**
   * Returns const reference to member IsPowerChangeable.
   * @return const reference to member isPowerChangeable
   */
  const xs_boolean &getIsPowerChangeable() const;

  /**
   * Returns if member IsPowerChangeable is set.
   * @retval true member IsPowerChangeable is set
   * @retval false member IsPowerChangeable is not set
   */
  bool getIsPowerChangeableIsSet() const;

  /**
   * Unsets member IsPowerChangeable
   */
  void cleanIsPowerChangeable();

  /**
   * Set member Energy.
   * @param c_energy Value to set
   */
  void setEnergy(const ScaledNumber &c_energy);

  /**
   * Returns const reference to member Energy.
   * @return const reference to member energy
   */
  const ScaledNumber &getEnergy() const;

  /**
   * Returns if member Energy is set.
   * @retval true member Energy is set
   * @retval false member Energy is not set
   */
  bool getEnergyIsSet() const;

  /**
   * Unsets member Energy
   */
  void cleanEnergy();

  /**
   * Set member IsEnergyChangeable.
   * @param c_isEnergyChangeable Value to set
   */
  void setIsEnergyChangeable(const xs_boolean &c_isEnergyChangeable);

  /**
   * Returns const reference to member IsEnergyChangeable.
   * @return const reference to member isEnergyChangeable
   */
  const xs_boolean &getIsEnergyChangeable() const;

  /**
   * Returns if member IsEnergyChangeable is set.
   * @retval true member IsEnergyChangeable is set
   * @retval false member IsEnergyChangeable is not set
   */
  bool getIsEnergyChangeableIsSet() const;

  /**
   * Unsets member IsEnergyChangeable
   */
  void cleanIsEnergyChangeable();

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
   * @copydoc CmdData::reduce()
   */
  DirectControlActivityData
  reduce(const DirectControlActivityDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_activityStateIsSet;
  DirectControlActivityState m_activityState;

  bool m_isActivityStateChangeableIsSet;
  xs_boolean m_isActivityStateChangeable;

  bool m_energyModeIsSet;
  EnergyMode m_energyMode;

  bool m_isEnergyModeChangeableIsSet;
  xs_boolean m_isEnergyModeChangeable;

  bool m_powerIsSet;
  ScaledNumber m_power;

  bool m_isPowerChangeableIsSet;
  xs_boolean m_isPowerChangeable;

  bool m_energyIsSet;
  ScaledNumber m_energy;

  bool m_isEnergyChangeableIsSet;
  xs_boolean m_isEnergyChangeable;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;
};

//! typedef for non-const smart pointer type DirectControlActivityData
using DirectControlActivityDataPtr = std::shared_ptr<DirectControlActivityData>;

//! typedef for const type DirectControlActivityData
using DirectControlActivityDataConst = const DirectControlActivityData;

//! typedef for const type DirectControlActivityData
using DirectControlActivityDataConstPtr =
    std::shared_ptr<DirectControlActivityDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLACTIVITYDATA_H_