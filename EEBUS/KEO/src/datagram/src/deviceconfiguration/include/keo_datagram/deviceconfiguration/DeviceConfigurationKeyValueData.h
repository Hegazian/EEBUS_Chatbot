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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDATA_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDataElements.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueValue.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueData
 */
class DeviceConfigurationKeyValueData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_keyId the member to set
   * @param c_value the member to set
   * @param c_isValueChangeable the member to set
   */
  DeviceConfigurationKeyValueData(
      const xs_unsignedInt &c_keyId,
      const DeviceConfigurationKeyValueValue &c_value,
      const xs_boolean &c_isValueChangeable);

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
  bool operator==(const DeviceConfigurationKeyValueData &c_classObject) const;

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
  bool operator!=(const DeviceConfigurationKeyValueData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member KeyId.
   * @param c_keyId Value to set
   */
  void setKeyId(const xs_unsignedInt &c_keyId);

  /**
   * Returns const reference to member KeyId.
   * @return const reference to member keyId
   */
  const xs_unsignedInt &getKeyId() const;

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
  void setValue(const DeviceConfigurationKeyValueValue &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const DeviceConfigurationKeyValueValue &getValue() const;

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
   * @param c_isValueChangeable Value to set
   */
  void setIsValueChangeable(const xs_boolean &c_isValueChangeable);

  /**
   * Returns const reference to member IsValueChangeable.
   * @return const reference to member isValueChangeable
   */
  const xs_boolean &getIsValueChangeable() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  DeviceConfigurationKeyValueData
  reduce(const DeviceConfigurationKeyValueDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_keyIdIsSet;
  xs_unsignedInt m_keyId;

  bool m_valueIsSet;
  DeviceConfigurationKeyValueValue m_value;

  bool m_isValueChangeableIsSet;
  xs_boolean m_isValueChangeable;
};

//! typedef for non-const smart pointer type DeviceConfigurationKeyValueData
using DeviceConfigurationKeyValueDataPtr =
    std::shared_ptr<DeviceConfigurationKeyValueData>;

//! typedef for const type DeviceConfigurationKeyValueData
using DeviceConfigurationKeyValueDataConst =
    const DeviceConfigurationKeyValueData;

//! typedef for const type DeviceConfigurationKeyValueData
using DeviceConfigurationKeyValueDataConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDATA_H_