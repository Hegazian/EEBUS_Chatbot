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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEVALUE_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEVALUE_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoDate.h>
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/KeoTime.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueValueElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueValue
 */
class DeviceConfigurationKeyValueValue : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueValue();

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
  bool operator==(const DeviceConfigurationKeyValueValue &c_classObject) const;

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
  bool operator!=(const DeviceConfigurationKeyValueValue &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Boolean.
   * @param c_boolean Value to set
   */
  void setBoolean(const xs_boolean &c_boolean);

  /**
   * Returns const reference to member Boolean.
   * @return const reference to member boolean
   */
  const xs_boolean &getBoolean() const;

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
   * @param c_date Value to set
   */
  void setDate(const xs_date &c_date);

  /**
   * Returns const reference to member Date.
   * @return const reference to member date
   */
  const xs_date &getDate() const;

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
   * @param c_dateTime Value to set
   */
  void setDateTime(const xs_dateTime &c_dateTime);

  /**
   * Returns const reference to member DateTime.
   * @return const reference to member dateTime
   */
  const xs_dateTime &getDateTime() const;

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
   * @param c_duration Value to set
   */
  void setDuration(const xs_duration &c_duration);

  /**
   * Returns const reference to member Duration.
   * @return const reference to member duration
   */
  const xs_duration &getDuration() const;

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
   * @param c_string Value to set
   */
  void setString(const xs_string &c_string);

  /**
   * Returns const reference to member String.
   * @return const reference to member string
   */
  const xs_string &getString() const;

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
   * @param c_time Value to set
   */
  void setTime(const xs_time &c_time);

  /**
   * Returns const reference to member Time.
   * @return const reference to member time
   */
  const xs_time &getTime() const;

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
  void setScaledNumber(const ScaledNumber &c_scaledNumber);

  /**
   * Returns const reference to member ScaledNumber.
   * @return const reference to member scaledNumber
   */
  const ScaledNumber &getScaledNumber() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  DeviceConfigurationKeyValueValue
  reduce(const DeviceConfigurationKeyValueValueElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_booleanIsSet;
  xs_boolean m_boolean;

  bool m_dateIsSet;
  xs_date m_date;

  bool m_dateTimeIsSet;
  xs_dateTime m_dateTime;

  bool m_durationIsSet;
  xs_duration m_duration;

  bool m_stringIsSet;
  xs_string m_string;

  bool m_timeIsSet;
  xs_time m_time;

  bool m_scaledNumberIsSet;
  ScaledNumber m_scaledNumber;
};

//! typedef for non-const smart pointer type DeviceConfigurationKeyValueValue
using DeviceConfigurationKeyValueValuePtr =
    std::shared_ptr<DeviceConfigurationKeyValueValue>;

//! typedef for const type DeviceConfigurationKeyValueValue
using DeviceConfigurationKeyValueValueConst =
    const DeviceConfigurationKeyValueValue;

//! typedef for const type DeviceConfigurationKeyValueValue
using DeviceConfigurationKeyValueValueConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueValueConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEVALUE_H_