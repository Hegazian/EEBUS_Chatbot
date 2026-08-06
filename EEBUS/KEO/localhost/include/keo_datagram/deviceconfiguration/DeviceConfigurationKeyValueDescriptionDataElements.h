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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueDescriptionDataElements
 */
class DeviceConfigurationKeyValueDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueDescriptionDataElements();

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
  bool operator==(const DeviceConfigurationKeyValueDescriptionDataElements
                      &c_classObject) const;

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
  bool operator!=(const DeviceConfigurationKeyValueDescriptionDataElements
                      &c_classObject) const;

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
   * Set member KeyName.
   */
  void setKeyName();

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
   */
  void setValueType();

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
   */
  void setUnit();

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
   */
  void setLabel();

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
   */
  void setDescription();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_keyIdIsSet;

  // ElementTag
  bool m_keyNameIsSet;

  // ElementTag
  bool m_valueTypeIsSet;

  // ElementTag
  bool m_unitIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type
//! DeviceConfigurationKeyValueDescriptionDataElements
using DeviceConfigurationKeyValueDescriptionDataElementsPtr =
    std::shared_ptr<DeviceConfigurationKeyValueDescriptionDataElements>;

//! typedef for const type DeviceConfigurationKeyValueDescriptionDataElements
using DeviceConfigurationKeyValueDescriptionDataElementsConst =
    const DeviceConfigurationKeyValueDescriptionDataElements;

//! typedef for const type DeviceConfigurationKeyValueDescriptionDataElements
using DeviceConfigurationKeyValueDescriptionDataElementsConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONDATAELEMENTS_H_