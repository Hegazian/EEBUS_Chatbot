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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSINTERRUPTDATA_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSINTERRUPTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsInterruptDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsInterruptData
 */
class OperatingConstraintsInterruptData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsInterruptData();

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
  bool operator==(const OperatingConstraintsInterruptData &c_classObject) const;

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
  bool operator!=(const OperatingConstraintsInterruptData &c_classObject) const;

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
   * Set member IsPausable.
   * @param c_isPausable Value to set
   */
  void setIsPausable(const xs_boolean &c_isPausable);

  /**
   * Returns const reference to member IsPausable.
   * @return const reference to member isPausable
   */
  const xs_boolean &getIsPausable() const;

  /**
   * Returns if member IsPausable is set.
   * @retval true member IsPausable is set
   * @retval false member IsPausable is not set
   */
  bool getIsPausableIsSet() const;

  /**
   * Unsets member IsPausable
   */
  void cleanIsPausable();

  /**
   * Set member IsStoppable.
   * @param c_isStoppable Value to set
   */
  void setIsStoppable(const xs_boolean &c_isStoppable);

  /**
   * Returns const reference to member IsStoppable.
   * @return const reference to member isStoppable
   */
  const xs_boolean &getIsStoppable() const;

  /**
   * Returns if member IsStoppable is set.
   * @retval true member IsStoppable is set
   * @retval false member IsStoppable is not set
   */
  bool getIsStoppableIsSet() const;

  /**
   * Unsets member IsStoppable
   */
  void cleanIsStoppable();

  /**
   * Set member NotInterruptibleAtHighPower.
   * @param c_notInterruptibleAtHighPower Value to set
   */
  void setNotInterruptibleAtHighPower(
      const xs_boolean &c_notInterruptibleAtHighPower);

  /**
   * Returns const reference to member NotInterruptibleAtHighPower.
   * @return const reference to member notInterruptibleAtHighPower
   */
  const xs_boolean &getNotInterruptibleAtHighPower() const;

  /**
   * Returns if member NotInterruptibleAtHighPower is set.
   * @retval true member NotInterruptibleAtHighPower is set
   * @retval false member NotInterruptibleAtHighPower is not set
   */
  bool getNotInterruptibleAtHighPowerIsSet() const;

  /**
   * Unsets member NotInterruptibleAtHighPower
   */
  void cleanNotInterruptibleAtHighPower();

  /**
   * Set member MaxCyclesPerDay.
   * @param c_maxCyclesPerDay Value to set
   */
  void setMaxCyclesPerDay(const xs_unsignedInt &c_maxCyclesPerDay);

  /**
   * Returns const reference to member MaxCyclesPerDay.
   * @return const reference to member maxCyclesPerDay
   */
  const xs_unsignedInt &getMaxCyclesPerDay() const;

  /**
   * Returns if member MaxCyclesPerDay is set.
   * @retval true member MaxCyclesPerDay is set
   * @retval false member MaxCyclesPerDay is not set
   */
  bool getMaxCyclesPerDayIsSet() const;

  /**
   * Unsets member MaxCyclesPerDay
   */
  void cleanMaxCyclesPerDay();

  /**
   * @copydoc CmdData::reduce()
   */
  OperatingConstraintsInterruptData
  reduce(const OperatingConstraintsInterruptDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_isPausableIsSet;
  xs_boolean m_isPausable;

  bool m_isStoppableIsSet;
  xs_boolean m_isStoppable;

  bool m_notInterruptibleAtHighPowerIsSet;
  xs_boolean m_notInterruptibleAtHighPower;

  bool m_maxCyclesPerDayIsSet;
  xs_unsignedInt m_maxCyclesPerDay;
};

//! typedef for non-const smart pointer type OperatingConstraintsInterruptData
using OperatingConstraintsInterruptDataPtr =
    std::shared_ptr<OperatingConstraintsInterruptData>;

//! typedef for const type OperatingConstraintsInterruptData
using OperatingConstraintsInterruptDataConst =
    const OperatingConstraintsInterruptData;

//! typedef for const type OperatingConstraintsInterruptData
using OperatingConstraintsInterruptDataConstPtr =
    std::shared_ptr<OperatingConstraintsInterruptDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSINTERRUPTDATA_H_