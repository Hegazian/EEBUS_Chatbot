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

#ifndef KEO_DATAGRAM_HVAC_HVACOVERRUNDATA_H_
#define KEO_DATAGRAM_HVAC_HVACOVERRUNDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/hvac/HvacOverrunDataElements.h>
#include <keo_datagram/hvac/HvacOverrunStatus.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacOverrunData
 */
class HvacOverrunData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  HvacOverrunData();

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
  bool operator==(const HvacOverrunData &c_classObject) const;

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
  bool operator!=(const HvacOverrunData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member OverrunId.
   * @param c_overrunId Value to set
   */
  void setOverrunId(const xs_unsignedInt &c_overrunId);

  /**
   * Returns const reference to member OverrunId.
   * @return const reference to member overrunId
   */
  const xs_unsignedInt &getOverrunId() const;

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
   * @param c_overrunStatus Value to set
   */
  void setOverrunStatus(const HvacOverrunStatus &c_overrunStatus);

  /**
   * Returns const reference to member OverrunStatus.
   * @return const reference to member overrunStatus
   */
  const HvacOverrunStatus &getOverrunStatus() const;

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
   * @param c_timeTableId Value to set
   */
  void setTimeTableId(const xs_unsignedInt &c_timeTableId);

  /**
   * Returns const reference to member TimeTableId.
   * @return const reference to member timeTableId
   */
  const xs_unsignedInt &getTimeTableId() const;

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
   * @param c_isOverrunStatusChangeable Value to set
   */
  void
  setIsOverrunStatusChangeable(const xs_boolean &c_isOverrunStatusChangeable);

  /**
   * Returns const reference to member IsOverrunStatusChangeable.
   * @return const reference to member isOverrunStatusChangeable
   */
  const xs_boolean &getIsOverrunStatusChangeable() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  HvacOverrunData reduce(const HvacOverrunDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_overrunIdIsSet;
  xs_unsignedInt m_overrunId;

  bool m_overrunStatusIsSet;
  HvacOverrunStatus m_overrunStatus;

  bool m_timeTableIdIsSet;
  xs_unsignedInt m_timeTableId;

  bool m_isOverrunStatusChangeableIsSet;
  xs_boolean m_isOverrunStatusChangeable;
};

//! typedef for non-const smart pointer type HvacOverrunData
using HvacOverrunDataPtr = std::shared_ptr<HvacOverrunData>;

//! typedef for const type HvacOverrunData
using HvacOverrunDataConst = const HvacOverrunData;

//! typedef for const type HvacOverrunData
using HvacOverrunDataConstPtr = std::shared_ptr<HvacOverrunDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACOVERRUNDATA_H_