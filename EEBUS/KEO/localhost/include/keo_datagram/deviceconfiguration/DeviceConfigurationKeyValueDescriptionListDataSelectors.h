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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyName.h>

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueDescriptionListDataSelectors
 */
class DeviceConfigurationKeyValueDescriptionListDataSelectors
    : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_keyId the member to set
   * @param c_keyName the member to set
   */
  DeviceConfigurationKeyValueDescriptionListDataSelectors(
      const xs_unsignedInt &c_keyId,
      const DeviceConfigurationKeyName &c_keyName);

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
  bool operator==(const DeviceConfigurationKeyValueDescriptionListDataSelectors
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
  bool operator!=(const DeviceConfigurationKeyValueDescriptionListDataSelectors
                      &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const DeviceConfigurationKeyValueDescriptionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_keyIdIsSet;
  xs_unsignedInt m_keyId;

  bool m_keyNameIsSet;
  DeviceConfigurationKeyName m_keyName;
};

//! typedef for non-const smart pointer type
//! DeviceConfigurationKeyValueDescriptionListDataSelectors
using DeviceConfigurationKeyValueDescriptionListDataSelectorsPtr =
    std::shared_ptr<DeviceConfigurationKeyValueDescriptionListDataSelectors>;

//! typedef for const type
//! DeviceConfigurationKeyValueDescriptionListDataSelectors
using DeviceConfigurationKeyValueDescriptionListDataSelectorsConst =
    const DeviceConfigurationKeyValueDescriptionListDataSelectors;

//! typedef for const type
//! DeviceConfigurationKeyValueDescriptionListDataSelectors
using DeviceConfigurationKeyValueDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<
        DeviceConfigurationKeyValueDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUEDESCRIPTIONLISTDATASELECTORS_H_