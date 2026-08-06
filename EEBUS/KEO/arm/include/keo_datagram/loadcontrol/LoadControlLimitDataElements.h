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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDATAELEMENTS_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/TimePeriodElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlLimitDataElements
 */
class LoadControlLimitDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlLimitDataElements();

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
  bool operator==(const LoadControlLimitDataElements &c_classObject) const;

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
  bool operator!=(const LoadControlLimitDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member LimitId.
   */
  void setLimitId();

  /**
   * Returns if member LimitId is set.
   * @retval true member LimitId is set
   * @retval false member LimitId is not set
   */
  bool getLimitIdIsSet() const;

  /**
   * Unsets member LimitId
   */
  void cleanLimitId();

  /**
   * Set member IsLimitChangeable.
   */
  void setIsLimitChangeable();

  /**
   * Returns if member IsLimitChangeable is set.
   * @retval true member IsLimitChangeable is set
   * @retval false member IsLimitChangeable is not set
   */
  bool getIsLimitChangeableIsSet() const;

  /**
   * Unsets member IsLimitChangeable
   */
  void cleanIsLimitChangeable();

  /**
   * Set member IsLimitActive.
   */
  void setIsLimitActive();

  /**
   * Returns if member IsLimitActive is set.
   * @retval true member IsLimitActive is set
   * @retval false member IsLimitActive is not set
   */
  bool getIsLimitActiveIsSet() const;

  /**
   * Unsets member IsLimitActive
   */
  void cleanIsLimitActive();

  /**
   * Set member TimePeriod.
   * @param c_timePeriod Value to set
   */
  void setTimePeriod(const TimePeriodElements &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriodElements &getTimePeriod() const;

  /**
   * Returns if member TimePeriod is set.
   * @retval true member TimePeriod is set
   * @retval false member TimePeriod is not set
   */
  bool getTimePeriodIsSet() const;

  /**
   * Unsets member TimePeriod
   */
  void cleanTimePeriod();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_limitIdIsSet;

  // ElementTag
  bool m_isLimitChangeableIsSet;

  // ElementTag
  bool m_isLimitActiveIsSet;

  bool m_timePeriodIsSet;
  TimePeriodElements m_timePeriod;

  bool m_valueIsSet;
  ScaledNumberElements m_value;
};

//! typedef for non-const smart pointer type LoadControlLimitDataElements
using LoadControlLimitDataElementsPtr =
    std::shared_ptr<LoadControlLimitDataElements>;

//! typedef for const type LoadControlLimitDataElements
using LoadControlLimitDataElementsConst = const LoadControlLimitDataElements;

//! typedef for const type LoadControlLimitDataElements
using LoadControlLimitDataElementsConstPtr =
    std::shared_ptr<LoadControlLimitDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDATAELEMENTS_H_