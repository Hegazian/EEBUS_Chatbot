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

#ifndef KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLACTIVITYDATAELEMENTS_H_
#define KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLACTIVITYDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDirectControl
 * @{
 */

/**
 * Declaration DirectControlActivityDataElements
 */
class DirectControlActivityDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  DirectControlActivityDataElements();

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
  bool operator==(const DirectControlActivityDataElements &c_classObject) const;

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
  bool operator!=(const DirectControlActivityDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member Timestamp.
   */
  void setTimestamp();

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
   */
  void setActivityState();

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
   */
  void setIsActivityStateChangeable();

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
   */
  void setEnergyMode();

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
   */
  void setIsEnergyModeChangeable();

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
  void setPower(const ScaledNumberElements &c_power);

  /**
   * Returns const reference to member Power.
   * @return const reference to member power
   */
  const ScaledNumberElements &getPower() const;

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
   */
  void setIsPowerChangeable();

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
  void setEnergy(const ScaledNumberElements &c_energy);

  /**
   * Returns const reference to member Energy.
   * @return const reference to member energy
   */
  const ScaledNumberElements &getEnergy() const;

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
   */
  void setIsEnergyChangeable();

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
   */
  void setSequenceId();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_activityStateIsSet;

  // ElementTag
  bool m_isActivityStateChangeableIsSet;

  // ElementTag
  bool m_energyModeIsSet;

  // ElementTag
  bool m_isEnergyModeChangeableIsSet;

  bool m_powerIsSet;
  ScaledNumberElements m_power;

  // ElementTag
  bool m_isPowerChangeableIsSet;

  bool m_energyIsSet;
  ScaledNumberElements m_energy;

  // ElementTag
  bool m_isEnergyChangeableIsSet;

  // ElementTag
  bool m_sequenceIdIsSet;
};

//! typedef for non-const smart pointer type DirectControlActivityDataElements
using DirectControlActivityDataElementsPtr =
    std::shared_ptr<DirectControlActivityDataElements>;

//! typedef for const type DirectControlActivityDataElements
using DirectControlActivityDataElementsConst =
    const DirectControlActivityDataElements;

//! typedef for const type DirectControlActivityDataElements
using DirectControlActivityDataElementsConstPtr =
    std::shared_ptr<DirectControlActivityDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLACTIVITYDATAELEMENTS_H_