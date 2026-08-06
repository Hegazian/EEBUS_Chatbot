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

#ifndef KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONDATAELEMENTS_H_
#define KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONDATAELEMENTS_H_

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

/** @addtogroup SpineDatagramSupplyCondition
 * @{
 */

/**
 * Declaration SupplyConditionDataElements
 */
class SupplyConditionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  SupplyConditionDataElements();

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
  bool operator==(const SupplyConditionDataElements &c_classObject) const;

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
  bool operator!=(const SupplyConditionDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member ConditionId.
   */
  void setConditionId();

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
   */
  void setTimestamp();

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
   */
  void setEventType();

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
   */
  void setOriginator();

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
   */
  void setThresholdId();

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
  void
  setThresholdPercentage(const ScaledNumberElements &c_thresholdPercentage);

  /**
   * Returns const reference to member ThresholdPercentage.
   * @return const reference to member thresholdPercentage
   */
  const ScaledNumberElements &getThresholdPercentage() const;

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
  void setRelevantPeriod(const TimePeriodElements &c_relevantPeriod);

  /**
   * Returns const reference to member RelevantPeriod.
   * @return const reference to member relevantPeriod
   */
  const TimePeriodElements &getRelevantPeriod() const;

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
   */
  void setDescription();

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
   */
  void setGridCondition();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_conditionIdIsSet;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_eventTypeIsSet;

  // ElementTag
  bool m_originatorIsSet;

  // ElementTag
  bool m_thresholdIdIsSet;

  bool m_thresholdPercentageIsSet;
  ScaledNumberElements m_thresholdPercentage;

  bool m_relevantPeriodIsSet;
  TimePeriodElements m_relevantPeriod;

  // ElementTag
  bool m_descriptionIsSet;

  // ElementTag
  bool m_gridConditionIsSet;
};

//! typedef for non-const smart pointer type SupplyConditionDataElements
using SupplyConditionDataElementsPtr =
    std::shared_ptr<SupplyConditionDataElements>;

//! typedef for const type SupplyConditionDataElements
using SupplyConditionDataElementsConst = const SupplyConditionDataElements;

//! typedef for const type SupplyConditionDataElements
using SupplyConditionDataElementsConstPtr =
    std::shared_ptr<SupplyConditionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONDATAELEMENTS_H_