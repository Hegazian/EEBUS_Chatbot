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

#ifndef KEO_DATAGRAM_THRESHOLD_THRESHOLDCONSTRAINTSDATAELEMENTS_H_
#define KEO_DATAGRAM_THRESHOLD_THRESHOLDCONSTRAINTSDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramThreshold
 * @{
 */

/**
 * Declaration ThresholdConstraintsDataElements
 */
class ThresholdConstraintsDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  ThresholdConstraintsDataElements();

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
  bool operator==(const ThresholdConstraintsDataElements &c_classObject) const;

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
  bool operator!=(const ThresholdConstraintsDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

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
   * Set member ThresholdRangeMin.
   * @param c_thresholdRangeMin Value to set
   */
  void setThresholdRangeMin(const ScaledNumberElements &c_thresholdRangeMin);

  /**
   * Returns const reference to member ThresholdRangeMin.
   * @return const reference to member thresholdRangeMin
   */
  const ScaledNumberElements &getThresholdRangeMin() const;

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
  void setThresholdRangeMax(const ScaledNumberElements &c_thresholdRangeMax);

  /**
   * Returns const reference to member ThresholdRangeMax.
   * @return const reference to member thresholdRangeMax
   */
  const ScaledNumberElements &getThresholdRangeMax() const;

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
  void setThresholdStepSize(const ScaledNumberElements &c_thresholdStepSize);

  /**
   * Returns const reference to member ThresholdStepSize.
   * @return const reference to member thresholdStepSize
   */
  const ScaledNumberElements &getThresholdStepSize() const;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_thresholdIdIsSet;

  bool m_thresholdRangeMinIsSet;
  ScaledNumberElements m_thresholdRangeMin;

  bool m_thresholdRangeMaxIsSet;
  ScaledNumberElements m_thresholdRangeMax;

  bool m_thresholdStepSizeIsSet;
  ScaledNumberElements m_thresholdStepSize;
};

//! typedef for non-const smart pointer type ThresholdConstraintsDataElements
using ThresholdConstraintsDataElementsPtr =
    std::shared_ptr<ThresholdConstraintsDataElements>;

//! typedef for const type ThresholdConstraintsDataElements
using ThresholdConstraintsDataElementsConst =
    const ThresholdConstraintsDataElements;

//! typedef for const type ThresholdConstraintsDataElements
using ThresholdConstraintsDataElementsConstPtr =
    std::shared_ptr<ThresholdConstraintsDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_THRESHOLD_THRESHOLDCONSTRAINTSDATAELEMENTS_H_