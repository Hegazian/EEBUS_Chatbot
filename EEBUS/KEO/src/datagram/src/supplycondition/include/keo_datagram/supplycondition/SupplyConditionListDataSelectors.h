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

#ifndef KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/TimestampInterval.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/supplycondition/SupplyConditionEventType.h>
#include <keo_datagram/supplycondition/SupplyConditionOriginator.h>

#include <keo_datagram/supplycondition/SupplyConditionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSupplyCondition
 * @{
 */

/**
 * Declaration SupplyConditionListDataSelectors
 */
class SupplyConditionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  SupplyConditionListDataSelectors();

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
  bool operator==(const SupplyConditionListDataSelectors &c_classObject) const;

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
  bool operator!=(const SupplyConditionListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member ConditionId.
   * @param c_conditionId Value to set
   */
  void setConditionId(const xs_unsignedInt &c_conditionId);

  /**
   * Returns const reference to member ConditionId.
   * @return const reference to member conditionId
   */
  const xs_unsignedInt &getConditionId() const;

  /**
   * Returns if member ConditionId is set.
   * @retval true member ConditionId is set
   * @retval false member ConditionId is not set
   */
  bool getConditionIdIsSet() const;

  /**
   * Unsets member ConditionId
   */
  void cleanConditionId();

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
   * Set member EventType.
   * @param c_eventType Value to set
   */
  void setEventType(const SupplyConditionEventType &c_eventType);

  /**
   * Returns const reference to member EventType.
   * @return const reference to member eventType
   */
  const SupplyConditionEventType &getEventType() const;

  /**
   * Returns if member EventType is set.
   * @retval true member EventType is set
   * @retval false member EventType is not set
   */
  bool getEventTypeIsSet() const;

  /**
   * Unsets member EventType
   */
  void cleanEventType();

  /**
   * Set member Originator.
   * @param c_originator Value to set
   */
  void setOriginator(const SupplyConditionOriginator &c_originator);

  /**
   * Returns const reference to member Originator.
   * @return const reference to member originator
   */
  const SupplyConditionOriginator &getOriginator() const;

  /**
   * Returns if member Originator is set.
   * @retval true member Originator is set
   * @retval false member Originator is not set
   */
  bool getOriginatorIsSet() const;

  /**
   * Unsets member Originator
   */
  void cleanOriginator();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const SupplyConditionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_conditionIdIsSet;
  xs_unsignedInt m_conditionId;

  bool m_timestampIntervalIsSet;
  TimestampInterval m_timestampInterval;

  bool m_eventTypeIsSet;
  SupplyConditionEventType m_eventType;

  bool m_originatorIsSet;
  SupplyConditionOriginator m_originator;
};

//! typedef for non-const smart pointer type SupplyConditionListDataSelectors
using SupplyConditionListDataSelectorsPtr =
    std::shared_ptr<SupplyConditionListDataSelectors>;

//! typedef for const type SupplyConditionListDataSelectors
using SupplyConditionListDataSelectorsConst =
    const SupplyConditionListDataSelectors;

//! typedef for const type SupplyConditionListDataSelectors
using SupplyConditionListDataSelectorsConstPtr =
    std::shared_ptr<SupplyConditionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONLISTDATASELECTORS_H_