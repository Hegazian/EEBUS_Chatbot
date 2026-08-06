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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVELISTDATASELECTORS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVELISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/TimestampInterval.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveValueType.h>

#include <keo_datagram/incentivetable/IncentiveData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveListDataSelectors
 */
class IncentiveListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_incentiveId the member to set
   * @param c_valueType the member to set
   * @param c_timestampInterval the member to set
   */
  IncentiveListDataSelectors(const xs_unsignedInt &c_incentiveId,
                             const IncentiveValueType &c_valueType,
                             const TimestampInterval &c_timestampInterval);

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
  bool operator==(const IncentiveListDataSelectors &c_classObject) const;

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
  bool operator!=(const IncentiveListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member IncentiveId.
   * @param c_incentiveId Value to set
   */
  void setIncentiveId(const xs_unsignedInt &c_incentiveId);

  /**
   * Returns const reference to member IncentiveId.
   * @return const reference to member incentiveId
   */
  const xs_unsignedInt &getIncentiveId() const;

  /**
   * Returns if member IncentiveId is set.
   * @retval true member IncentiveId is set
   * @retval false member IncentiveId is not set
   */
  bool getIncentiveIdIsSet() const;

  /**
   * Unsets member IncentiveId
   */
  void cleanIncentiveId();

  /**
   * Set member ValueType.
   * @param c_valueType Value to set
   */
  void setValueType(const IncentiveValueType &c_valueType);

  /**
   * Returns const reference to member ValueType.
   * @return const reference to member valueType
   */
  const IncentiveValueType &getValueType() const;

  /**
   * Returns if member ValueType is set.
   * @retval true member ValueType is set
   * @retval false member ValueType is not set
   */
  bool getValueTypeIsSet() const;

  /**
   * Unsets member ValueType
   */
  void cleanValueType();

  /**
   * Set member TimestampInterval.
   * @param c_timestampInterval Value to set
   */
  void setTimestampInterval(const TimestampInterval &c_timestampInterval);

  /**
   * Returns const reference to member TimestampInterval.
   * @return const reference to member timestampInterval
   */
  const TimestampInterval &getTimestampInterval() const;

  /**
   * Returns if member TimestampInterval is set.
   * @retval true member TimestampInterval is set
   * @retval false member TimestampInterval is not set
   */
  bool getTimestampIntervalIsSet() const;

  /**
   * Unsets member TimestampInterval
   */
  void cleanTimestampInterval();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const IncentiveData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_incentiveIdIsSet;
  xs_unsignedInt m_incentiveId;

  bool m_valueTypeIsSet;
  IncentiveValueType m_valueType;

  bool m_timestampIntervalIsSet;
  TimestampInterval m_timestampInterval;
};

//! typedef for non-const smart pointer type IncentiveListDataSelectors
using IncentiveListDataSelectorsPtr =
    std::shared_ptr<IncentiveListDataSelectors>;

//! typedef for const type IncentiveListDataSelectors
using IncentiveListDataSelectorsConst = const IncentiveListDataSelectors;

//! typedef for const type IncentiveListDataSelectors
using IncentiveListDataSelectorsConstPtr =
    std::shared_ptr<IncentiveListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVELISTDATASELECTORS_H_