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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUECONSTRAINTSDATAELEMENTS_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUECONSTRAINTSDATAELEMENTS_H_

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
 * Declaration DeviceConfigurationKeyValueConstraintsDataElements
 */
class DeviceConfigurationKeyValueConstraintsDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueConstraintsDataElements();

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
  bool operator==(const DeviceConfigurationKeyValueConstraintsDataElements
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
  bool operator!=(const DeviceConfigurationKeyValueConstraintsDataElements
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
   * Set member ValueRangeMin.
   * @param c_valueRangeMin Value to set
   */
  void setValueRangeMin(
      const DeviceConfigurationKeyValueValueElements &c_valueRangeMin);

  /**
   * Returns const reference to member ValueRangeMin.
   * @return const reference to member valueRangeMin
   */
  const DeviceConfigurationKeyValueValueElements &getValueRangeMin() const;

  /**
   * Returns if member ValueRangeMin is set.
   * @retval true member ValueRangeMin is set
   * @retval false member ValueRangeMin is not set
   */
  bool getValueRangeMinIsSet() const;

  /**
   * Unsets member ValueRangeMin
   */
  void cleanValueRangeMin();

  /**
   * Set member ValueRangeMax.
   * @param c_valueRangeMax Value to set
   */
  void setValueRangeMax(
      const DeviceConfigurationKeyValueValueElements &c_valueRangeMax);

  /**
   * Returns const reference to member ValueRangeMax.
   * @return const reference to member valueRangeMax
   */
  const DeviceConfigurationKeyValueValueElements &getValueRangeMax() const;

  /**
   * Returns if member ValueRangeMax is set.
   * @retval true member ValueRangeMax is set
   * @retval false member ValueRangeMax is not set
   */
  bool getValueRangeMaxIsSet() const;

  /**
   * Unsets member ValueRangeMax
   */
  void cleanValueRangeMax();

  /**
   * Set member ValueStepSize.
   * @param c_valueStepSize Value to set
   */
  void setValueStepSize(
      const DeviceConfigurationKeyValueValueElements &c_valueStepSize);

  /**
   * Returns const reference to member ValueStepSize.
   * @return const reference to member valueStepSize
   */
  const DeviceConfigurationKeyValueValueElements &getValueStepSize() const;

  /**
   * Returns if member ValueStepSize is set.
   * @retval true member ValueStepSize is set
   * @retval false member ValueStepSize is not set
   */
  bool getValueStepSizeIsSet() const;

  /**
   * Unsets member ValueStepSize
   */
  void cleanValueStepSize();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_keyIdIsSet;

  bool m_valueRangeMinIsSet;
  DeviceConfigurationKeyValueValueElements m_valueRangeMin;

  bool m_valueRangeMaxIsSet;
  DeviceConfigurationKeyValueValueElements m_valueRangeMax;

  bool m_valueStepSizeIsSet;
  DeviceConfigurationKeyValueValueElements m_valueStepSize;
};

//! typedef for non-const smart pointer type
//! DeviceConfigurationKeyValueConstraintsDataElements
using DeviceConfigurationKeyValueConstraintsDataElementsPtr =
    std::shared_ptr<DeviceConfigurationKeyValueConstraintsDataElements>;

//! typedef for const type DeviceConfigurationKeyValueConstraintsDataElements
using DeviceConfigurationKeyValueConstraintsDataElementsConst =
    const DeviceConfigurationKeyValueConstraintsDataElements;

//! typedef for const type DeviceConfigurationKeyValueConstraintsDataElements
using DeviceConfigurationKeyValueConstraintsDataElementsConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueConstraintsDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUECONSTRAINTSDATAELEMENTS_H_