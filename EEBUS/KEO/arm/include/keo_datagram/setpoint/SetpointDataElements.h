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

#ifndef KEO_DATAGRAM_SETPOINT_SETPOINTDATAELEMENTS_H_
#define KEO_DATAGRAM_SETPOINT_SETPOINTDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSetpoint
 * @{
 */

/**
 * Declaration SetpointDataElements
 */
class SetpointDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  SetpointDataElements();

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
  bool operator==(const SetpointDataElements &c_classObject) const;

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
  bool operator!=(const SetpointDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member SetpointId.
   */
  void setSetpointId();

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
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const ScaledNumberElements &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const ScaledNumberElements &getValue() const;

  /**
   * Returns if member Value is set.
   * @retval true member Value is set
   * @retval false member Value is not set
   */
  bool getValueIsSet() const;

  /**
   * Unsets member Value
   */
  void cleanValue();

  /**
   * Set member ValueMin.
   * @param c_valueMin Value to set
   */
  void setValueMin(const ScaledNumberElements &c_valueMin);

  /**
   * Returns const reference to member ValueMin.
   * @return const reference to member valueMin
   */
  const ScaledNumberElements &getValueMin() const;

  /**
   * Returns if member ValueMin is set.
   * @retval true member ValueMin is set
   * @retval false member ValueMin is not set
   */
  bool getValueMinIsSet() const;

  /**
   * Unsets member ValueMin
   */
  void cleanValueMin();

  /**
   * Set member ValueMax.
   * @param c_valueMax Value to set
   */
  void setValueMax(const ScaledNumberElements &c_valueMax);

  /**
   * Returns const reference to member ValueMax.
   * @return const reference to member valueMax
   */
  const ScaledNumberElements &getValueMax() const;

  /**
   * Returns if member ValueMax is set.
   * @retval true member ValueMax is set
   * @retval false member ValueMax is not set
   */
  bool getValueMaxIsSet() const;

  /**
   * Unsets member ValueMax
   */
  void cleanValueMax();

  /**
   * Set member ValueToleranceAbsolute.
   * @param c_valueToleranceAbsolute Value to set
   */
  void setValueToleranceAbsolute(
      const ScaledNumberElements &c_valueToleranceAbsolute);

  /**
   * Returns const reference to member ValueToleranceAbsolute.
   * @return const reference to member valueToleranceAbsolute
   */
  const ScaledNumberElements &getValueToleranceAbsolute() const;

  /**
   * Returns if member ValueToleranceAbsolute is set.
   * @retval true member ValueToleranceAbsolute is set
   * @retval false member ValueToleranceAbsolute is not set
   */
  bool getValueToleranceAbsoluteIsSet() const;

  /**
   * Unsets member ValueToleranceAbsolute
   */
  void cleanValueToleranceAbsolute();

  /**
   * Set member ValueTolerancePercentage.
   * @param c_valueTolerancePercentage Value to set
   */
  void setValueTolerancePercentage(
      const ScaledNumberElements &c_valueTolerancePercentage);

  /**
   * Returns const reference to member ValueTolerancePercentage.
   * @return const reference to member valueTolerancePercentage
   */
  const ScaledNumberElements &getValueTolerancePercentage() const;

  /**
   * Returns if member ValueTolerancePercentage is set.
   * @retval true member ValueTolerancePercentage is set
   * @retval false member ValueTolerancePercentage is not set
   */
  bool getValueTolerancePercentageIsSet() const;

  /**
   * Unsets member ValueTolerancePercentage
   */
  void cleanValueTolerancePercentage();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_setpointIdIsSet;

  bool m_valueIsSet;
  ScaledNumberElements m_value;

  bool m_valueMinIsSet;
  ScaledNumberElements m_valueMin;

  bool m_valueMaxIsSet;
  ScaledNumberElements m_valueMax;

  bool m_valueToleranceAbsoluteIsSet;
  ScaledNumberElements m_valueToleranceAbsolute;

  bool m_valueTolerancePercentageIsSet;
  ScaledNumberElements m_valueTolerancePercentage;
};

//! typedef for non-const smart pointer type SetpointDataElements
using SetpointDataElementsPtr = std::shared_ptr<SetpointDataElements>;

//! typedef for const type SetpointDataElements
using SetpointDataElementsConst = const SetpointDataElements;

//! typedef for const type SetpointDataElements
using SetpointDataElementsConstPtr = std::shared_ptr<SetpointDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SETPOINT_SETPOINTDATAELEMENTS_H_