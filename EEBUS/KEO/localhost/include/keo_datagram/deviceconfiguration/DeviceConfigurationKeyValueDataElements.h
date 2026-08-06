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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDATAELEMENTS_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueValueElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueDataElements
 */
class DeviceConfigurationKeyValueDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_keyIdIsSet the member to set
   * @param c_value the member to set
   * @param c_isValueChangeableIsSet the member to set
   */
  DeviceConfigurationKeyValueDataElements(
      xs_boolean c_keyIdIsSet,
      const DeviceConfigurationKeyValueValueElements &c_value,
      xs_boolean c_isValueChangeableIsSet);

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
      const DeviceConfigurationKeyValueDataElements &c_classObject) const;

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
      const DeviceConfigurationKeyValueDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member KeyId.
   */
  void setKeyId();

  /**
   * Returns if member KeyId is set.
   * @retval true member KeyId is set
   * @retval false member KeyId is not set
   */
  bool getKeyIdIsSet() const;

  /**
   * Unsets member KeyId
   */
  void cleanKeyId();

  /**
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const DeviceConfigurationKeyValueValueElements &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const DeviceConfigurationKeyValueValueElements &getValue() const;

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
   * Set member IsValueChangeable.
   */
  void setIsValueChangeable();

  /**
   * Returns if member IsValueChangeable is set.
   * @retval true member IsValueChangeable is set
   * @retval false member IsValueChangeable is not set
   */
  bool getIsValueChangeableIsSet() const;

  /**
   * Unsets member IsValueChangeable
   */
  void cleanIsValueChangeable();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_keyIdIsSet;

  bool m_valueIsSet;
  DeviceConfigurationKeyValueValueElements m_value;

  // ElementTag
  bool m_isValueChangeableIsSet;
};

//! typedef for non-const smart pointer type
//! DeviceConfigurationKeyValueDataElements
using DeviceConfigurationKeyValueDataElementsPtr =
    std::shared_ptr<DeviceConfigurationKeyValueDataElements>;

//! typedef for const type DeviceConfigurationKeyValueDataElements
using DeviceConfigurationKeyValueDataElementsConst =
    const DeviceConfigurationKeyValueDataElements;

//! typedef for const type DeviceConfigurationKeyValueDataElements
using DeviceConfigurationKeyValueDataElementsConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDATAELEMENTS_H_