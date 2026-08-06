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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERLEVELDATAELEMENTS_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERLEVELDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsPowerLevelDataElements
 */
class OperatingConstraintsPowerLevelDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsPowerLevelDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_sequenceIdIsSet the member to set
   * @param c_power the member to set
   */
  OperatingConstraintsPowerLevelDataElements(
      xs_boolean c_sequenceIdIsSet, const ScaledNumberElements &c_power);

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
      const OperatingConstraintsPowerLevelDataElements &c_classObject) const;

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
      const OperatingConstraintsPowerLevelDataElements &c_classObject) const;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  bool m_powerIsSet;
  ScaledNumberElements m_power;
};

//! typedef for non-const smart pointer type
//! OperatingConstraintsPowerLevelDataElements
using OperatingConstraintsPowerLevelDataElementsPtr =
    std::shared_ptr<OperatingConstraintsPowerLevelDataElements>;

//! typedef for const type OperatingConstraintsPowerLevelDataElements
using OperatingConstraintsPowerLevelDataElementsConst =
    const OperatingConstraintsPowerLevelDataElements;

//! typedef for const type OperatingConstraintsPowerLevelDataElements
using OperatingConstraintsPowerLevelDataElementsConstPtr =
    std::shared_ptr<OperatingConstraintsPowerLevelDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERLEVELDATAELEMENTS_H_