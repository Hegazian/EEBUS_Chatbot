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

#ifndef KEO_DATAGRAM_SETPOINT_SETPOINTCONSTRAINTSDATA_H_
#define KEO_DATAGRAM_SETPOINT_SETPOINTCONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/setpoint/SetpointConstraintsDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSetpoint
 * @{
 */

/**
 * Declaration SetpointConstraintsData
 */
class SetpointConstraintsData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SetpointConstraintsData();

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
  bool operator==(const SetpointConstraintsData &c_classObject) const;

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
  bool operator!=(const SetpointConstraintsData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member SetpointId.
   * @param c_setpointId Value to set
   */
  void setSetpointId(const xs_unsignedInt &c_setpointId);

  /**
   * Returns const reference to member SetpointId.
   * @return const reference to member setpointId
   */
  const xs_unsignedInt &getSetpointId() const;

  /**
   * Returns if member SetpointId is set.
   * @retval true member SetpointId is set
   * @retval false member SetpointId is not set
   */
  bool getSetpointIdIsSet() const;

  /**
   * Unsets member SetpointId
   */
  void cleanSetpointId();

  /**
   * Set member SetpointRangeMin.
   * @param c_setpointRangeMin Value to set
   */
  void setSetpointRangeMin(const ScaledNumber &c_setpointRangeMin);

  /**
   * Returns const reference to member SetpointRangeMin.
   * @return const reference to member setpointRangeMin
   */
  const ScaledNumber &getSetpointRangeMin() const;

  /**
   * Returns if member SetpointRangeMin is set.
   * @retval true member SetpointRangeMin is set
   * @retval false member SetpointRangeMin is not set
   */
  bool getSetpointRangeMinIsSet() const;

  /**
   * Unsets member SetpointRangeMin
   */
  void cleanSetpointRangeMin();

  /**
   * Set member SetpointRangeMax.
   * @param c_setpointRangeMax Value to set
   */
  void setSetpointRangeMax(const ScaledNumber &c_setpointRangeMax);

  /**
   * Returns const reference to member SetpointRangeMax.
   * @return const reference to member setpointRangeMax
   */
  const ScaledNumber &getSetpointRangeMax() const;

  /**
   * Returns if member SetpointRangeMax is set.
   * @retval true member SetpointRangeMax is set
   * @retval false member SetpointRangeMax is not set
   */
  bool getSetpointRangeMaxIsSet() const;

  /**
   * Unsets member SetpointRangeMax
   */
  void cleanSetpointRangeMax();

  /**
   * Set member SetpointStepSize.
   * @param c_setpointStepSize Value to set
   */
  void setSetpointStepSize(const ScaledNumber &c_setpointStepSize);

  /**
   * Returns const reference to member SetpointStepSize.
   * @return const reference to member setpointStepSize
   */
  const ScaledNumber &getSetpointStepSize() const;

  /**
   * Returns if member SetpointStepSize is set.
   * @retval true member SetpointStepSize is set
   * @retval false member SetpointStepSize is not set
   */
  bool getSetpointStepSizeIsSet() const;

  /**
   * Unsets member SetpointStepSize
   */
  void cleanSetpointStepSize();

  /**
   * @copydoc CmdData::reduce()
   */
  SetpointConstraintsData
  reduce(const SetpointConstraintsDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_setpointIdIsSet;
  xs_unsignedInt m_setpointId;

  bool m_setpointRangeMinIsSet;
  ScaledNumber m_setpointRangeMin;

  bool m_setpointRangeMaxIsSet;
  ScaledNumber m_setpointRangeMax;

  bool m_setpointStepSizeIsSet;
  ScaledNumber m_setpointStepSize;
};

//! typedef for non-const smart pointer type SetpointConstraintsData
using SetpointConstraintsDataPtr = std::shared_ptr<SetpointConstraintsData>;

//! typedef for const type SetpointConstraintsData
using SetpointConstraintsDataConst = const SetpointConstraintsData;

//! typedef for const type SetpointConstraintsData
using SetpointConstraintsDataConstPtr =
    std::shared_ptr<SetpointConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SETPOINT_SETPOINTCONSTRAINTSDATA_H_