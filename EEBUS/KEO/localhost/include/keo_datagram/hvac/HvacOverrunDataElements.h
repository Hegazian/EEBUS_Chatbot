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

#ifndef KEO_DATAGRAM_HVAC_HVACOVERRUNDATAELEMENTS_H_
#define KEO_DATAGRAM_HVAC_HVACOVERRUNDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacOverrunDataElements
 */
class HvacOverrunDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  HvacOverrunDataElements();

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
  bool operator==(const HvacOverrunDataElements &c_classObject) const;

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
  bool operator!=(const HvacOverrunDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member OverrunId.
   */
  void setOverrunId();

  /**
   * Returns if member OverrunId is set.
   * @retval true member OverrunId is set
   * @retval false member OverrunId is not set
   */
  bool getOverrunIdIsSet() const;

  /**
   * Unsets member OverrunId
   */
  void cleanOverrunId();

  /**
   * Set member OverrunStatus.
   */
  void setOverrunStatus();

  /**
   * Returns if member OverrunStatus is set.
   * @retval true member OverrunStatus is set
   * @retval false member OverrunStatus is not set
   */
  bool getOverrunStatusIsSet() const;

  /**
   * Unsets member OverrunStatus
   */
  void cleanOverrunStatus();

  /**
   * Set member TimeTableId.
   */
  void setTimeTableId();

  /**
   * Returns if member TimeTableId is set.
   * @retval true member TimeTableId is set
   * @retval false member TimeTableId is not set
   */
  bool getTimeTableIdIsSet() const;

  /**
   * Unsets member TimeTableId
   */
  void cleanTimeTableId();

  /**
   * Set member IsOverrunStatusChangeable.
   */
  void setIsOverrunStatusChangeable();

  /**
   * Returns if member IsOverrunStatusChangeable is set.
   * @retval true member IsOverrunStatusChangeable is set
   * @retval false member IsOverrunStatusChangeable is not set
   */
  bool getIsOverrunStatusChangeableIsSet() const;

  /**
   * Unsets member IsOverrunStatusChangeable
   */
  void cleanIsOverrunStatusChangeable();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_overrunIdIsSet;

  // ElementTag
  bool m_overrunStatusIsSet;

  // ElementTag
  bool m_timeTableIdIsSet;

  // ElementTag
  bool m_isOverrunStatusChangeableIsSet;
};

//! typedef for non-const smart pointer type HvacOverrunDataElements
using HvacOverrunDataElementsPtr = std::shared_ptr<HvacOverrunDataElements>;

//! typedef for const type HvacOverrunDataElements
using HvacOverrunDataElementsConst = const HvacOverrunDataElements;

//! typedef for const type HvacOverrunDataElements
using HvacOverrunDataElementsConstPtr =
    std::shared_ptr<HvacOverrunDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACOVERRUNDATAELEMENTS_H_