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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUELISTDATASELECTORS_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUELISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueListDataSelectors
 */
class DeviceConfigurationKeyValueListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueListDataSelectors();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_keyId the member to set
   */
  explicit DeviceConfigurationKeyValueListDataSelectors(
      const xs_unsignedInt &c_keyId);

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
      const DeviceConfigurationKeyValueListDataSelectors &c_classObject) const;

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
      const DeviceConfigurationKeyValueListDataSelectors &c_classObject) const;

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
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const DeviceConfigurationKeyValueData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_keyIdIsSet;
  xs_unsignedInt m_keyId;
};

//! typedef for non-const smart pointer type
//! DeviceConfigurationKeyValueListDataSelectors
using DeviceConfigurationKeyValueListDataSelectorsPtr =
    std::shared_ptr<DeviceConfigurationKeyValueListDataSelectors>;

//! typedef for const type DeviceConfigurationKeyValueListDataSelectors
using DeviceConfigurationKeyValueListDataSelectorsConst =
    const DeviceConfigurationKeyValueListDataSelectors;

//! typedef for const type DeviceConfigurationKeyValueListDataSelectors
using DeviceConfigurationKeyValueListDataSelectorsConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUELISTDATASELECTORS_H_