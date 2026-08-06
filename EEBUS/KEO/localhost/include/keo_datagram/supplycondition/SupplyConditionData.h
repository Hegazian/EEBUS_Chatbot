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

#ifndef KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONDATA_H_
#define KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/supplycondition/GridCondition.h>
#include <keo_datagram/supplycondition/SupplyConditionDataElements.h>
#include <keo_datagram/supplycondition/SupplyConditionEventType.h>
#include <keo_datagram/supplycondition/SupplyConditionOriginator.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSupplyCondition
 * @{
 */

/**
 * Declaration SupplyConditionData
 */
class SupplyConditionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SupplyConditionData();

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
  bool operator==(const SupplyConditionData &c_classObject) const;

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
  bool operator!=(const SupplyConditionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member Timestamp.
   * @param c_timestamp Value to set
   */
  void setTimestamp(const AbsoluteOrRelativeTime &c_timestamp);

  /**
   * Returns const reference to member Timestamp.
   * @return const reference to member timestamp
   */
  const AbsoluteOrRelativeTime &getTimestamp() const;

  /**
   * Returns if member Timestamp is set.
   * @retval true member Timestamp is set
   * @retval false member Timestamp is not set
   */
  bool getTimestampIsSet() const;

  /**
   * Unsets member Timestamp
   */
  void cleanTimestamp();

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
   * Set member ThresholdId.
   * @param c_thresholdId Value to set
   */
  void setThresholdId(const xs_unsignedInt &c_thresholdId);

  /**
   * Returns const reference to member ThresholdId.
   * @return const reference to member thresholdId
   */
  const xs_unsignedInt &getThresholdId() const;

  /**
   * Returns if member ThresholdId is set.
   * @retval true member ThresholdId is set
   * @retval false member ThresholdId is not set
   */
  bool getThresholdIdIsSet() const;

  /**
   * Unsets member ThresholdId
   */
  void cleanThresholdId();

  /**
   * Set member ThresholdPercentage.
   * @param c_thresholdPercentage Value to set
   */
  void setThresholdPercentage(const ScaledNumber &c_thresholdPercentage);

  /**
   * Returns const reference to member ThresholdPercentage.
   * @return const reference to member thresholdPercentage
   */
  const ScaledNumber &getThresholdPercentage() const;

  /**
   * Returns if member ThresholdPercentage is set.
   * @retval true member ThresholdPercentage is set
   * @retval false member ThresholdPercentage is not set
   */
  bool getThresholdPercentageIsSet() const;

  /**
   * Unsets member ThresholdPercentage
   */
  void cleanThresholdPercentage();

  /**
   * Set member RelevantPeriod.
   * @param c_relevantPeriod Value to set
   */
  void setRelevantPeriod(const TimePeriod &c_relevantPeriod);

  /**
   * Returns const reference to member RelevantPeriod.
   * @return const reference to member relevantPeriod
   */
  const TimePeriod &getRelevantPeriod() const;

  /**
   * Returns if member RelevantPeriod is set.
   * @retval true member RelevantPeriod is set
   * @retval false member RelevantPeriod is not set
   */
  bool getRelevantPeriodIsSet() const;

  /**
   * Unsets member RelevantPeriod
   */
  void cleanRelevantPeriod();

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

  /**
   * Set member GridCondition.
   * @param c_gridCondition Value to set
   */
  void setGridCondition(const GridCondition &c_gridCondition);

  /**
   * Returns const reference to member GridCondition.
   * @return const reference to member gridCondition
   */
  const GridCondition &getGridCondition() const;

  /**
   * Returns if member GridCondition is set.
   * @retval true member GridCondition is set
   * @retval false member GridCondition is not set
   */
  bool getGridConditionIsSet() const;

  /**
   * Unsets member GridCondition
   */
  void cleanGridCondition();

  /**
   * @copydoc CmdData::reduce()
   */
  SupplyConditionData reduce(const SupplyConditionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_conditionIdIsSet;
  xs_unsignedInt m_conditionId;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_eventTypeIsSet;
  SupplyConditionEventType m_eventType;

  bool m_originatorIsSet;
  SupplyConditionOriginator m_originator;

  bool m_thresholdIdIsSet;
  xs_unsignedInt m_thresholdId;

  bool m_thresholdPercentageIsSet;
  ScaledNumber m_thresholdPercentage;

  bool m_relevantPeriodIsSet;
  TimePeriod m_relevantPeriod;

  bool m_descriptionIsSet;
  xs_string m_description;

  bool m_gridConditionIsSet;
  GridCondition m_gridCondition;
};

//! typedef for non-const smart pointer type SupplyConditionData
using SupplyConditionDataPtr = std::shared_ptr<SupplyConditionData>;

//! typedef for const type SupplyConditionData
using SupplyConditionDataConst = const SupplyConditionData;

//! typedef for const type SupplyConditionData
using SupplyConditionDataConstPtr = std::shared_ptr<SupplyConditionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONDATA_H_