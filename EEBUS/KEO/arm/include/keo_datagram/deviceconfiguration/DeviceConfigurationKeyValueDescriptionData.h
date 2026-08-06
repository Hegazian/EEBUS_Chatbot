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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyName.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionDataElements.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueDescriptionData
 */
class DeviceConfigurationKeyValueDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueDescriptionData();

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
      const DeviceConfigurationKeyValueDescriptionData &c_classObject) const;

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
      const DeviceConfigurationKeyValueDescriptionData &c_classObject) const;

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
   * Set member KeyName.
   * @param c_keyName Value to set
   */
  void setKeyName(const DeviceConfigurationKeyName &c_keyName);

  /**
   * Returns const reference to member KeyName.
   * @return const reference to member keyName
   */
  const DeviceConfigurationKeyName &getKeyName() const;

  /**
   * Returns if member KeyName is set.
   * @retval true member KeyName is set
   * @retval false member KeyName is not set
   */
  bool getKeyNameIsSet() const;

  /**
   * Unsets member KeyName
   */
  void cleanKeyName();

  /**
   * Set member ValueType.
   * @param c_valueType Value to set
   */
  void setValueType(const DeviceConfigurationKeyValueType &c_valueType);

  /**
   * Returns const reference to member ValueType.
   * @return const reference to member valueType
   */
  const DeviceConfigurationKeyValueType &getValueType() const;

  /**
   * Returns if member ValueType is set.
   * @retval true member ValueType is set
   * @retval false member ValueType is not set
   */
  bool getValueTypeIsSet() const;

  /**
   * Unsets member ValueType
   */
  void cleanValueType();

  /**
   * Set member Unit.
   * @param c_unit Value to set
   */
  void setUnit(const UnitOfMeasurement &c_unit);

  /**
   * Returns const reference to member Unit.
   * @return const reference to member unit
   */
  const UnitOfMeasurement &getUnit() const;

  /**
   * Returns if member Unit is set.
   * @retval true member Unit is set
   * @retval false member Unit is not set
   */
  bool getUnitIsSet() const;

  /**
   * Unsets member Unit
   */
  void cleanUnit();

  /**
   * Set member Label.
   * @param c_label Value to set
   */
  void setLabel(const xs_string &c_label);

  /**
   * Returns const reference to member Label.
   * @return const reference to member label
   */
  const xs_string &getLabel() const;

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

  /**
   * @copydoc CmdData::reduce()
   */
  DeviceConfigurationKeyValueDescriptionData reduce(
      const DeviceConfigurationKeyValueDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_keyIdIsSet;
  xs_unsignedInt m_keyId;

  bool m_keyNameIsSet;
  DeviceConfigurationKeyName m_keyName;

  bool m_valueTypeIsSet;
  DeviceConfigurationKeyValueType m_valueType;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type
//! DeviceConfigurationKeyValueDescriptionData
using DeviceConfigurationKeyValueDescriptionDataPtr =
    std::shared_ptr<DeviceConfigurationKeyValueDescriptionData>;

//! typedef for const type DeviceConfigurationKeyValueDescriptionData
using DeviceConfigurationKeyValueDescriptionDataConst =
    const DeviceConfigurationKeyValueDescriptionData;

//! typedef for const type DeviceConfigurationKeyValueDescriptionData
using DeviceConfigurationKeyValueDescriptionDataConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONDATA_H_