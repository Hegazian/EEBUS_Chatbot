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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERTIMESLOTVALUELIST_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERTIMESLOTVALUELIST_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration SmartEnergyManagementPsPowerTimeSlotValueList
 */
class SmartEnergyManagementPsPowerTimeSlotValueList
    : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SmartEnergyManagementPsPowerTimeSlotValueList();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_value the member to set
   */
  explicit SmartEnergyManagementPsPowerTimeSlotValueList(
      const std::vector<PowerTimeSlotValueData> &c_value);

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
  bool operator==(
      const SmartEnergyManagementPsPowerTimeSlotValueList &c_classObject) const;

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
  bool operator!=(
      const SmartEnergyManagementPsPowerTimeSlotValueList &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const std::vector<PowerTimeSlotValueData> &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const std::vector<PowerTimeSlotValueData> &getValue() const;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_valueIsSet;
  std::vector<PowerTimeSlotValueData> m_value;
};

//! typedef for non-const smart pointer type
//! SmartEnergyManagementPsPowerTimeSlotValueList
using SmartEnergyManagementPsPowerTimeSlotValueListPtr =
    std::shared_ptr<SmartEnergyManagementPsPowerTimeSlotValueList>;

//! typedef for const type SmartEnergyManagementPsPowerTimeSlotValueList
using SmartEnergyManagementPsPowerTimeSlotValueListConst =
    const SmartEnergyManagementPsPowerTimeSlotValueList;

//! typedef for const type SmartEnergyManagementPsPowerTimeSlotValueList
using SmartEnergyManagementPsPowerTimeSlotValueListConstPtr =
    std::shared_ptr<SmartEnergyManagementPsPowerTimeSlotValueListConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSPOWERTIMESLOTVALUELIST_H_