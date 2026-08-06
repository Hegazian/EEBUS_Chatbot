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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TierBoundaryDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TierBoundaryData
 */
class TierBoundaryData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TierBoundaryData();

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
  bool operator==(const TierBoundaryData &c_classObject) const;

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
  bool operator!=(const TierBoundaryData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member BoundaryId.
   * @param c_boundaryId Value to set
   */
  void setBoundaryId(const xs_unsignedInt &c_boundaryId);

  /**
   * Returns const reference to member BoundaryId.
   * @return const reference to member boundaryId
   */
  const xs_unsignedInt &getBoundaryId() const;

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
  void setTimePeriod(const TimePeriod &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriod &getTimePeriod() const;

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
   * @param c_timeTableId Value to set
   */
  void setTimeTableId(const xs_unsignedInt &c_timeTableId);

  /**
   * Returns const reference to member TimeTableId.
   * @return const reference to member timeTableId
   */
  const xs_unsignedInt &getTimeTableId() const;

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
  void setLowerBoundaryValue(const ScaledNumber &c_lowerBoundaryValue);

  /**
   * Returns const reference to member LowerBoundaryValue.
   * @return const reference to member lowerBoundaryValue
   */
  const ScaledNumber &getLowerBoundaryValue() const;

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
  void setUpperBoundaryValue(const ScaledNumber &c_upperBoundaryValue);

  /**
   * Returns const reference to member UpperBoundaryValue.
   * @return const reference to member upperBoundaryValue
   */
  const ScaledNumber &getUpperBoundaryValue() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  TierBoundaryData reduce(const TierBoundaryDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_boundaryIdIsSet;
  xs_unsignedInt m_boundaryId;

  bool m_timePeriodIsSet;
  TimePeriod m_timePeriod;

  bool m_timeTableIdIsSet;
  xs_unsignedInt m_timeTableId;

  bool m_lowerBoundaryValueIsSet;
  ScaledNumber m_lowerBoundaryValue;

  bool m_upperBoundaryValueIsSet;
  ScaledNumber m_upperBoundaryValue;
};

//! typedef for non-const smart pointer type TierBoundaryData
using TierBoundaryDataPtr = std::shared_ptr<TierBoundaryData>;

//! typedef for const type TierBoundaryData
using TierBoundaryDataConst = const TierBoundaryData;

//! typedef for const type TierBoundaryData
using TierBoundaryDataConstPtr = std::shared_ptr<TierBoundaryDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDATA_H_