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

#ifndef KEO_DATAGRAM_THRESHOLD_THRESHOLDDATAELEMENTS_H_
#define KEO_DATAGRAM_THRESHOLD_THRESHOLDDATAELEMENTS_H_

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
 * Declaration ThresholdDataElements
 */
class ThresholdDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  ThresholdDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_thresholdIdIsSet the member to set
   * @param c_thresholdValue the member to set
   */
  ThresholdDataElements(xs_boolean c_thresholdIdIsSet,
                        const ScaledNumberElements &c_thresholdValue);

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
  bool operator==(const ThresholdDataElements &c_classObject) const;

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
  bool operator!=(const ThresholdDataElements &c_classObject) const;

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
   * Set member ThresholdValue.
   * @param c_thresholdValue Value to set
   */
  void setThresholdValue(const ScaledNumberElements &c_thresholdValue);

  /**
   * Returns const reference to member ThresholdValue.
   * @return const reference to member thresholdValue
   */
  const ScaledNumberElements &getThresholdValue() const;

  /**
   * Returns if member ThresholdValue is set.
   * @retval true member ThresholdValue is set
   * @retval false member ThresholdValue is not set
   */
  bool getThresholdValueIsSet() const;

  /**
   * Unsets member ThresholdValue
   */
  void cleanThresholdValue();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_thresholdIdIsSet;

  bool m_thresholdValueIsSet;
  ScaledNumberElements m_thresholdValue;
};

//! typedef for non-const smart pointer type ThresholdDataElements
using ThresholdDataElementsPtr = std::shared_ptr<ThresholdDataElements>;

//! typedef for const type ThresholdDataElements
using ThresholdDataElementsConst = const ThresholdDataElements;

//! typedef for const type ThresholdDataElements
using ThresholdDataElementsConstPtr =
    std::shared_ptr<ThresholdDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_THRESHOLD_THRESHOLDDATAELEMENTS_H_