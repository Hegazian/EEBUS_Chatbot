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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEVALUEELEMENTS_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEVALUEELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueValueElements
 */
class DeviceConfigurationKeyValueValueElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueValueElements();

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
      const DeviceConfigurationKeyValueValueElements &c_classObject) const;

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
      const DeviceConfigurationKeyValueValueElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Boolean.
   */
  void setBoolean();

  /**
   * Returns if member Boolean is set.
   * @retval true member Boolean is set
   * @retval false member Boolean is not set
   */
  bool getBooleanIsSet() const;

  /**
   * Unsets member Boolean
   */
  void cleanBoolean();

  /**
   * Set member Date.
   */
  void setDate();

  /**
   * Returns if member Date is set.
   * @retval true member Date is set
   * @retval false member Date is not set
   */
  bool getDateIsSet() const;

  /**
   * Unsets member Date
   */
  void cleanDate();

  /**
   * Set member DateTime.
   */
  void setDateTime();

  /**
   * Returns if member DateTime is set.
   * @retval true member DateTime is set
   * @retval false member DateTime is not set
   */
  bool getDateTimeIsSet() const;

  /**
   * Unsets member DateTime
   */
  void cleanDateTime();

  /**
   * Set member Duration.
   */
  void setDuration();

  /**
   * Returns if member Duration is set.
   * @retval true member Duration is set
   * @retval false member Duration is not set
   */
  bool getDurationIsSet() const;

  /**
   * Unsets member Duration
   */
  void cleanDuration();

  /**
   * Set member String.
   */
  void setString();

  /**
   * Returns if member String is set.
   * @retval true member String is set
   * @retval false member String is not set
   */
  bool getStringIsSet() const;

  /**
   * Unsets member String
   */
  void cleanString();

  /**
   * Set member Time.
   */
  void setTime();

  /**
   * Returns if member Time is set.
   * @retval true member Time is set
   * @retval false member Time is not set
   */
  bool getTimeIsSet() const;

  /**
   * Unsets member Time
   */
  void cleanTime();

  /**
   * Set member ScaledNumber.
   * @param c_scaledNumber Value to set
   */
  void setScaledNumber(const ScaledNumberElements &c_scaledNumber);

  /**
   * Returns const reference to member ScaledNumber.
   * @return const reference to member scaledNumber
   */
  const ScaledNumberElements &getScaledNumber() const;

  /**
   * Returns if member ScaledNumber is set.
   * @retval true member ScaledNumber is set
   * @retval false member ScaledNumber is not set
   */
  bool getScaledNumberIsSet() const;

  /**
   * Unsets member ScaledNumber
   */
  void cleanScaledNumber();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_booleanIsSet;

  // ElementTag
  bool m_dateIsSet;

  // ElementTag
  bool m_dateTimeIsSet;

  // ElementTag
  bool m_durationIsSet;

  // ElementTag
  bool m_stringIsSet;

  // ElementTag
  bool m_timeIsSet;

  bool m_scaledNumberIsSet;
  ScaledNumberElements m_scaledNumber;
};

//! typedef for non-const smart pointer type
//! DeviceConfigurationKeyValueValueElements
using DeviceConfigurationKeyValueValueElementsPtr =
    std::shared_ptr<DeviceConfigurationKeyValueValueElements>;

//! typedef for const type DeviceConfigurationKeyValueValueElements
using DeviceConfigurationKeyValueValueElementsConst =
    const DeviceConfigurationKeyValueValueElements;

//! typedef for const type DeviceConfigurationKeyValueValueElements
using DeviceConfigurationKeyValueValueElementsConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueValueElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEVALUEELEMENTS_H_