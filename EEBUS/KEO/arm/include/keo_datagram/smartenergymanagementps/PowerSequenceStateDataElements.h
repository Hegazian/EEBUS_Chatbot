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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESTATEDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESTATEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceStateDataElements
 */
class PowerSequenceStateDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceStateDataElements();

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
  bool operator==(const PowerSequenceStateDataElements &c_classObject) const;

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
  bool operator!=(const PowerSequenceStateDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

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

  /**
   * Set member State.
   */
  void setState();

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
   */
  void setActiveSlotNumber();

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
   */
  void setElapsedSlotTime();

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
   */
  void setRemainingSlotTime();

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
   */
  void setSequenceRemoteControllable();

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
   */
  void setActiveRepetitionNumber();

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
   */
  void setRemainingPauseTime();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_stateIsSet;

  // ElementTag
  bool m_activeSlotNumberIsSet;

  // ElementTag
  bool m_elapsedSlotTimeIsSet;

  // ElementTag
  bool m_remainingSlotTimeIsSet;

  // ElementTag
  bool m_sequenceRemoteControllableIsSet;

  // ElementTag
  bool m_activeRepetitionNumberIsSet;

  // ElementTag
  bool m_remainingPauseTimeIsSet;
};

//! typedef for non-const smart pointer type PowerSequenceStateDataElements
using PowerSequenceStateDataElementsPtr =
    std::shared_ptr<PowerSequenceStateDataElements>;

//! typedef for const type PowerSequenceStateDataElements
using PowerSequenceStateDataElementsConst =
    const PowerSequenceStateDataElements;

//! typedef for const type PowerSequenceStateDataElements
using PowerSequenceStateDataElementsConstPtr =
    std::shared_ptr<PowerSequenceStateDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESTATEDATAELEMENTS_H_