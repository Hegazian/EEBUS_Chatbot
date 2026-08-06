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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERLEVELDATA_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERLEVELDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsPowerLevelData
 */
class OperatingConstraintsPowerLevelData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsPowerLevelData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_sequenceId the member to set
   * @param c_power the member to set
   */
  OperatingConstraintsPowerLevelData(const xs_unsignedInt &c_sequenceId,
                                     const std::vector<ScaledNumber> &c_power);

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
  bool
  operator==(const OperatingConstraintsPowerLevelData &c_classObject) const;

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
  bool
  operator!=(const OperatingConstraintsPowerLevelData &c_classObject) const;

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
   * Set member Power.
   * @param c_power Value to set
   */
  void setPower(const std::vector<ScaledNumber> &c_power);

  /**
   * Returns const reference to member Power.
   * @return const reference to member power
   */
  const std::vector<ScaledNumber> &getPower() const;

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
   * @copydoc CmdData::reduce()
   */
  OperatingConstraintsPowerLevelData
  reduce(const OperatingConstraintsPowerLevelDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_powerIsSet;
  std::vector<ScaledNumber> m_power;
};

//! typedef for non-const smart pointer type OperatingConstraintsPowerLevelData
using OperatingConstraintsPowerLevelDataPtr =
    std::shared_ptr<OperatingConstraintsPowerLevelData>;

//! typedef for const type OperatingConstraintsPowerLevelData
using OperatingConstraintsPowerLevelDataConst =
    const OperatingConstraintsPowerLevelData;

//! typedef for const type OperatingConstraintsPowerLevelData
using OperatingConstraintsPowerLevelDataConstPtr =
    std::shared_ptr<OperatingConstraintsPowerLevelDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERLEVELDATA_H_