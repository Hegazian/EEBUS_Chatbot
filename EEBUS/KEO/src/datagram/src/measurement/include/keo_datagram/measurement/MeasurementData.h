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

#ifndef KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDATA_H_
#define KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDATA_H_

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
#include <keo_datagram/measurement/MeasurementDataElements.h>
#include <keo_datagram/measurement/MeasurementValueSource.h>
#include <keo_datagram/measurement/MeasurementValueState.h>
#include <keo_datagram/measurement/MeasurementValueTendency.h>
#include <keo_datagram/measurement/MeasurementValueType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramMeasurement
 * @{
 */

/**
 * Declaration MeasurementData
 */
class MeasurementData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  MeasurementData();

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
  bool operator==(const MeasurementData &c_classObject) const;

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
  bool operator!=(const MeasurementData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member MeasurementId.
   * @param c_measurementId Value to set
   */
  void setMeasurementId(const xs_unsignedInt &c_measurementId);

  /**
   * Returns const reference to member MeasurementId.
   * @return const reference to member measurementId
   */
  const xs_unsignedInt &getMeasurementId() const;

  /**
   * Returns if member MeasurementId is set.
   * @retval true member MeasurementId is set
   * @retval false member MeasurementId is not set
   */
  bool getMeasurementIdIsSet() const;

  /**
   * Unsets member MeasurementId
   */
  void cleanMeasurementId();

  /**
   * Set member ValueType.
   * @param c_valueType Value to set
   */
  void setValueType(const MeasurementValueType &c_valueType);

  /**
   * Returns const reference to member ValueType.
   * @return const reference to member valueType
   */
  const MeasurementValueType &getValueType() const;

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
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const ScaledNumber &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const ScaledNumber &getValue() const;

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
   * Set member ValueSource.
   * @param c_valueSource Value to set
   */
  void setValueSource(const MeasurementValueSource &c_valueSource);

  /**
   * Returns const reference to member ValueSource.
   * @return const reference to member valueSource
   */
  const MeasurementValueSource &getValueSource() const;

  /**
   * Returns if member ValueSource is set.
   * @retval true member ValueSource is set
   * @retval false member ValueSource is not set
   */
  bool getValueSourceIsSet() const;

  /**
   * Unsets member ValueSource
   */
  void cleanValueSource();

  /**
   * Set member ValueTendency.
   * @param c_valueTendency Value to set
   */
  void setValueTendency(const MeasurementValueTendency &c_valueTendency);

  /**
   * Returns const reference to member ValueTendency.
   * @return const reference to member valueTendency
   */
  const MeasurementValueTendency &getValueTendency() const;

  /**
   * Returns if member ValueTendency is set.
   * @retval true member ValueTendency is set
   * @retval false member ValueTendency is not set
   */
  bool getValueTendencyIsSet() const;

  /**
   * Unsets member ValueTendency
   */
  void cleanValueTendency();

  /**
   * Set member ValueState.
   * @param c_valueState Value to set
   */
  void setValueState(const MeasurementValueState &c_valueState);

  /**
   * Returns const reference to member ValueState.
   * @return const reference to member valueState
   */
  const MeasurementValueState &getValueState() const;

  /**
   * Returns if member ValueState is set.
   * @retval true member ValueState is set
   * @retval false member ValueState is not set
   */
  bool getValueStateIsSet() const;

  /**
   * Unsets member ValueState
   */
  void cleanValueState();

  /**
   * @copydoc CmdData::reduce()
   */
  MeasurementData reduce(const MeasurementDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_valueTypeIsSet;
  MeasurementValueType m_valueType;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_valueIsSet;
  ScaledNumber m_value;

  bool m_evaluationPeriodIsSet;
  TimePeriod m_evaluationPeriod;

  bool m_valueSourceIsSet;
  MeasurementValueSource m_valueSource;

  bool m_valueTendencyIsSet;
  MeasurementValueTendency m_valueTendency;

  bool m_valueStateIsSet;
  MeasurementValueState m_valueState;
};

//! typedef for non-const smart pointer type MeasurementData
using MeasurementDataPtr = std::shared_ptr<MeasurementData>;

//! typedef for const type MeasurementData
using MeasurementDataConst = const MeasurementData;

//! typedef for const type MeasurementData
using MeasurementDataConstPtr = std::shared_ptr<MeasurementDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDATA_H_