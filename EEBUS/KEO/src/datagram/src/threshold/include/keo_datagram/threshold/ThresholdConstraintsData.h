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

#ifndef KEO_DATAGRAM_THRESHOLD_THRESHOLDCONSTRAINTSDATA_H_
#define KEO_DATAGRAM_THRESHOLD_THRESHOLDCONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/threshold/ThresholdConstraintsDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramThreshold
 * @{
 */

/**
 * Declaration ThresholdConstraintsData
 */
class ThresholdConstraintsData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  ThresholdConstraintsData();

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
  bool operator==(const ThresholdConstraintsData &c_classObject) const;

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
  bool operator!=(const ThresholdConstraintsData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member ThresholdRangeMin.
   * @param c_thresholdRangeMin Value to set
   */
  void setThresholdRangeMin(const ScaledNumber &c_thresholdRangeMin);

  /**
   * Returns const reference to member ThresholdRangeMin.
   * @return const reference to member thresholdRangeMin
   */
  const ScaledNumber &getThresholdRangeMin() const;

  /**
   * Returns if member ThresholdRangeMin is set.
   * @retval true member ThresholdRangeMin is set
   * @retval false member ThresholdRangeMin is not set
   */
  bool getThresholdRangeMinIsSet() const;

  /**
   * Unsets member ThresholdRangeMin
   */
  void cleanThresholdRangeMin();

  /**
   * Set member ThresholdRangeMax.
   * @param c_thresholdRangeMax Value to set
   */
  void setThresholdRangeMax(const ScaledNumber &c_thresholdRangeMax);

  /**
   * Returns const reference to member ThresholdRangeMax.
   * @return const reference to member thresholdRangeMax
   */
  const ScaledNumber &getThresholdRangeMax() const;

  /**
   * Returns if member ThresholdRangeMax is set.
   * @retval true member ThresholdRangeMax is set
   * @retval false member ThresholdRangeMax is not set
   */
  bool getThresholdRangeMaxIsSet() const;

  /**
   * Unsets member ThresholdRangeMax
   */
  void cleanThresholdRangeMax();

  /**
   * Set member ThresholdStepSize.
   * @param c_thresholdStepSize Value to set
   */
  void setThresholdStepSize(const ScaledNumber &c_thresholdStepSize);

  /**
   * Returns const reference to member ThresholdStepSize.
   * @return const reference to member thresholdStepSize
   */
  const ScaledNumber &getThresholdStepSize() const;

  /**
   * Returns if member ThresholdStepSize is set.
   * @retval true member ThresholdStepSize is set
   * @retval false member ThresholdStepSize is not set
   */
  bool getThresholdStepSizeIsSet() const;

  /**
   * Unsets member ThresholdStepSize
   */
  void cleanThresholdStepSize();

  /**
   * @copydoc CmdData::reduce()
   */
  ThresholdConstraintsData
  reduce(const ThresholdConstraintsDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_thresholdIdIsSet;
  xs_unsignedInt m_thresholdId;

  bool m_thresholdRangeMinIsSet;
  ScaledNumber m_thresholdRangeMin;

  bool m_thresholdRangeMaxIsSet;
  ScaledNumber m_thresholdRangeMax;

  bool m_thresholdStepSizeIsSet;
  ScaledNumber m_thresholdStepSize;
};

//! typedef for non-const smart pointer type ThresholdConstraintsData
using ThresholdConstraintsDataPtr = std::shared_ptr<ThresholdConstraintsData>;

//! typedef for const type ThresholdConstraintsData
using ThresholdConstraintsDataConst = const ThresholdConstraintsData;

//! typedef for const type ThresholdConstraintsData
using ThresholdConstraintsDataConstPtr =
    std::shared_ptr<ThresholdConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_THRESHOLD_THRESHOLDCONSTRAINTSDATA_H_