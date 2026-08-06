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

#ifndef KEO_DATAGRAM_ALARM_ALARMDATA_H_
#define KEO_DATAGRAM_ALARM_ALARMDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/alarm/AlarmDataElements.h>
#include <keo_datagram/alarm/AlarmType.h>
#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramAlarm
 * @{
 */

/**
 * Declaration AlarmData
 */
class AlarmData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  AlarmData();

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
  bool operator==(const AlarmData &c_classObject) const;

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
  bool operator!=(const AlarmData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member AlarmId.
   * @param c_alarmId Value to set
   */
  void setAlarmId(const xs_unsignedInt &c_alarmId);

  /**
   * Returns const reference to member AlarmId.
   * @return const reference to member alarmId
   */
  const xs_unsignedInt &getAlarmId() const;

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
   * Set member AlarmType.
   * @param c_alarmType Value to set
   */
  void setAlarmType(const AlarmType &c_alarmType);

  /**
   * Returns const reference to member AlarmType.
   * @return const reference to member alarmType
   */
  const AlarmType &getAlarmType() const;

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
  void setMeasuredValue(const ScaledNumber &c_measuredValue);

  /**
   * Returns const reference to member MeasuredValue.
   * @return const reference to member measuredValue
   */
  const ScaledNumber &getMeasuredValue() const;

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
  void setEvaluationPeriod(const TimePeriod &c_evaluationPeriod);

  /**
   * Returns const reference to member EvaluationPeriod.
   * @return const reference to member evaluationPeriod
   */
  const TimePeriod &getEvaluationPeriod() const;

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
   * @param c_scopeType Value to set
   */
  void setScopeType(const ScopeType &c_scopeType);

  /**
   * Returns const reference to member ScopeType.
   * @return const reference to member scopeType
   */
  const ScopeType &getScopeType() const;

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
   * @param c_label Value to set
   */
  void setLabel(const xs_string &c_label);

  /**
   * Returns const reference to member Label.
   * @return const reference to member label
   */
  const xs_string &getLabel() const;

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
   * @copydoc CmdData::reduce()
   */
  AlarmData reduce(const AlarmDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_alarmIdIsSet;
  xs_unsignedInt m_alarmId;

  bool m_thresholdIdIsSet;
  xs_unsignedInt m_thresholdId;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_alarmTypeIsSet;
  AlarmType m_alarmType;

  bool m_measuredValueIsSet;
  ScaledNumber m_measuredValue;

  bool m_evaluationPeriodIsSet;
  TimePeriod m_evaluationPeriod;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type AlarmData
using AlarmDataPtr = std::shared_ptr<AlarmData>;

//! typedef for const type AlarmData
using AlarmDataConst = const AlarmData;

//! typedef for const type AlarmData
using AlarmDataConstPtr = std::shared_ptr<AlarmDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ALARM_ALARMDATA_H_