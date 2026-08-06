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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSINTERRUPTDATAELEMENTS_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSINTERRUPTDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsInterruptDataElements
 */
class OperatingConstraintsInterruptDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsInterruptDataElements();

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
      const OperatingConstraintsInterruptDataElements &c_classObject) const;

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
      const OperatingConstraintsInterruptDataElements &c_classObject) const;

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
   * Set member IsPausable.
   */
  void setIsPausable();

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
   */
  void setIsStoppable();

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
   */
  void setNotInterruptibleAtHighPower();

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
   */
  void setMaxCyclesPerDay();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_isPausableIsSet;

  // ElementTag
  bool m_isStoppableIsSet;

  // ElementTag
  bool m_notInterruptibleAtHighPowerIsSet;

  // ElementTag
  bool m_maxCyclesPerDayIsSet;
};

//! typedef for non-const smart pointer type
//! OperatingConstraintsInterruptDataElements
using OperatingConstraintsInterruptDataElementsPtr =
    std::shared_ptr<OperatingConstraintsInterruptDataElements>;

//! typedef for const type OperatingConstraintsInterruptDataElements
using OperatingConstraintsInterruptDataElementsConst =
    const OperatingConstraintsInterruptDataElements;

//! typedef for const type OperatingConstraintsInterruptDataElements
using OperatingConstraintsInterruptDataElementsConstPtr =
    std::shared_ptr<OperatingConstraintsInterruptDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSINTERRUPTDATAELEMENTS_H_