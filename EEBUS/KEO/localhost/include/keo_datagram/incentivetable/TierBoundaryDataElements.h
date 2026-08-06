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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDATAELEMENTS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDATAELEMENTS_H_

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

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TierBoundaryDataElements
 */
class TierBoundaryDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TierBoundaryDataElements();

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
  bool operator==(const TierBoundaryDataElements &c_classObject) const;

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
  bool operator!=(const TierBoundaryDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member BoundaryId.
   */
  void setBoundaryId();

  /**
   * Returns if member BoundaryId is set.
   * @retval true member BoundaryId is set
   * @retval false member BoundaryId is not set
   */
  bool getBoundaryIdIsSet() const;

  /**
   * Unsets member BoundaryId
   */
  void cleanBoundaryId();

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
   * Set member TimeTableId.
   */
  void setTimeTableId();

  /**
   * Returns if member TimeTableId is set.
   * @retval true member TimeTableId is set
   * @retval false member TimeTableId is not set
   */
  bool getTimeTableIdIsSet() const;

  /**
   * Unsets member TimeTableId
   */
  void cleanTimeTableId();

  /**
   * Set member LowerBoundaryValue.
   * @param c_lowerBoundaryValue Value to set
   */
  void setLowerBoundaryValue(const ScaledNumberElements &c_lowerBoundaryValue);

  /**
   * Returns const reference to member LowerBoundaryValue.
   * @return const reference to member lowerBoundaryValue
   */
  const ScaledNumberElements &getLowerBoundaryValue() const;

  /**
   * Returns if member LowerBoundaryValue is set.
   * @retval true member LowerBoundaryValue is set
   * @retval false member LowerBoundaryValue is not set
   */
  bool getLowerBoundaryValueIsSet() const;

  /**
   * Unsets member LowerBoundaryValue
   */
  void cleanLowerBoundaryValue();

  /**
   * Set member UpperBoundaryValue.
   * @param c_upperBoundaryValue Value to set
   */
  void setUpperBoundaryValue(const ScaledNumberElements &c_upperBoundaryValue);

  /**
   * Returns const reference to member UpperBoundaryValue.
   * @return const reference to member upperBoundaryValue
   */
  const ScaledNumberElements &getUpperBoundaryValue() const;

  /**
   * Returns if member UpperBoundaryValue is set.
   * @retval true member UpperBoundaryValue is set
   * @retval false member UpperBoundaryValue is not set
   */
  bool getUpperBoundaryValueIsSet() const;

  /**
   * Unsets member UpperBoundaryValue
   */
  void cleanUpperBoundaryValue();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_boundaryIdIsSet;

  bool m_timePeriodIsSet;
  TimePeriodElements m_timePeriod;

  // ElementTag
  bool m_timeTableIdIsSet;

  bool m_lowerBoundaryValueIsSet;
  ScaledNumberElements m_lowerBoundaryValue;

  bool m_upperBoundaryValueIsSet;
  ScaledNumberElements m_upperBoundaryValue;
};

//! typedef for non-const smart pointer type TierBoundaryDataElements
using TierBoundaryDataElementsPtr = std::shared_ptr<TierBoundaryDataElements>;

//! typedef for const type TierBoundaryDataElements
using TierBoundaryDataElementsConst = const TierBoundaryDataElements;

//! typedef for const type TierBoundaryDataElements
using TierBoundaryDataElementsConstPtr =
    std::shared_ptr<TierBoundaryDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDATAELEMENTS_H_