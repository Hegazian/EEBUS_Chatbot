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

#ifndef KEO_DATAGRAM_ALARM_ALARMDATAELEMENTS_H_
#define KEO_DATAGRAM_ALARM_ALARMDATAELEMENTS_H_

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

/** @addtogroup SpineDatagramAlarm
 * @{
 */

/**
 * Declaration AlarmDataElements
 */
class AlarmDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  AlarmDataElements();

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
  bool operator==(const AlarmDataElements &c_classObject) const;

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
  bool operator!=(const AlarmDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member AlarmId.
   */
  void setAlarmId();

  /**
   * Returns if member AlarmId is set.
   * @retval true member AlarmId is set
   * @retval false member AlarmId is not set
   */
  bool getAlarmIdIsSet() const;

  /**
   * Unsets member AlarmId
   */
  void cleanAlarmId();

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
   * Set member AlarmType.
   */
  void setAlarmType();

  /**
   * Returns if member AlarmType is set.
   * @retval true member AlarmType is set
   * @retval false member AlarmType is not set
   */
  bool getAlarmTypeIsSet() const;

  /**
   * Unsets member AlarmType
   */
  void cleanAlarmType();

  /**
   * Set member MeasuredValue.
   * @param c_measuredValue Value to set
   */
  void setMeasuredValue(const ScaledNumberElements &c_measuredValue);

  /**
   * Returns const reference to member MeasuredValue.
   * @return const reference to member measuredValue
   */
  const ScaledNumberElements &getMeasuredValue() const;

  /**
   * Returns if member MeasuredValue is set.
   * @retval true member MeasuredValue is set
   * @retval false member MeasuredValue is not set
   */
  bool getMeasuredValueIsSet() const;

  /**
   * Unsets member MeasuredValue
   */
  void cleanMeasuredValue();

  /**
   * Set member EvaluationPeriod.
   * @param c_evaluationPeriod Value to set
   */
  void setEvaluationPeriod(const TimePeriodElements &c_evaluationPeriod);

  /**
   * Returns const reference to member EvaluationPeriod.
   * @return const reference to member evaluationPeriod
   */
  const TimePeriodElements &getEvaluationPeriod() const;

  /**
   * Returns if member EvaluationPeriod is set.
   * @retval true member EvaluationPeriod is set
   * @retval false member EvaluationPeriod is not set
   */
  bool getEvaluationPeriodIsSet() const;

  /**
   * Unsets member EvaluationPeriod
   */
  void cleanEvaluationPeriod();

  /**
   * Set member ScopeType.
   */
  void setScopeType();

  /**
   * Returns if member ScopeType is set.
   * @retval true member ScopeType is set
   * @retval false member ScopeType is not set
   */
  bool getScopeTypeIsSet() const;

  /**
   * Unsets member ScopeType
   */
  void cleanScopeType();

  /**
   * Set member Label.
   */
  void setLabel();

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_alarmIdIsSet;

  // ElementTag
  bool m_thresholdIdIsSet;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_alarmTypeIsSet;

  bool m_measuredValueIsSet;
  ScaledNumberElements m_measuredValue;

  bool m_evaluationPeriodIsSet;
  TimePeriodElements m_evaluationPeriod;

  // ElementTag
  bool m_scopeTypeIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type AlarmDataElements
using AlarmDataElementsPtr = std::shared_ptr<AlarmDataElements>;

//! typedef for const type AlarmDataElements
using AlarmDataElementsConst = const AlarmDataElements;

//! typedef for const type AlarmDataElements
using AlarmDataElementsConstPtr = std::shared_ptr<AlarmDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ALARM_ALARMDATAELEMENTS_H_