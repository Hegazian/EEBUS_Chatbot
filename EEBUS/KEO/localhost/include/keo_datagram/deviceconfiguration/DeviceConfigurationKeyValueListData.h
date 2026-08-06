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

#ifndef KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUELISTDATA_H_
#define KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUELISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceConfiguration
 * @{
 */

/**
 * Declaration DeviceConfigurationKeyValueListData
 */
class DeviceConfigurationKeyValueListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  DeviceConfigurationKeyValueListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_deviceConfigurationKeyValueData the member to set
   */
  explicit DeviceConfigurationKeyValueListData(
      const std::vector<DeviceConfigurationKeyValueData>
          &c_deviceConfigurationKeyValueData);

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
  bool
  operator==(const DeviceConfigurationKeyValueListData &c_classObject) const;

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
  bool
  operator!=(const DeviceConfigurationKeyValueListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member DeviceConfigurationKeyValueData.
   * @param c_deviceConfigurationKeyValueData Value to set
   */
  void setDeviceConfigurationKeyValueData(
      const std::vector<DeviceConfigurationKeyValueData>
          &c_deviceConfigurationKeyValueData);

  /**
   * Returns const reference to member DeviceConfigurationKeyValueData.
   * @return const reference to member deviceConfigurationKeyValueData
   */
  const std::vector<DeviceConfigurationKeyValueData> &
  getDeviceConfigurationKeyValueData() const;

  /**
   * Returns if member DeviceConfigurationKeyValueData is set.
   * @retval true member DeviceConfigurationKeyValueData is set
   * @retval false member DeviceConfigurationKeyValueData is not set
   */
  bool getDeviceConfigurationKeyValueDataIsSet() const;

  /**
   * Unsets member DeviceConfigurationKeyValueData
   */
  void cleanDeviceConfigurationKeyValueData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_deviceConfigurationKeyValueDataIsSet;
  std::vector<DeviceConfigurationKeyValueData>
      m_deviceConfigurationKeyValueData;
};

//! typedef for non-const smart pointer type DeviceConfigurationKeyValueListData
using DeviceConfigurationKeyValueListDataPtr =
    std::shared_ptr<DeviceConfigurationKeyValueListData>;

//! typedef for const type DeviceConfigurationKeyValueListData
using DeviceConfigurationKeyValueListDataConst =
    const DeviceConfigurationKeyValueListData;

//! typedef for const type DeviceConfigurationKeyValueListData
using DeviceConfigurationKeyValueListDataConstPtr =
    std::shared_ptr<DeviceConfigurationKeyValueListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICECONFIGURATION_DEVICECONFIGURATIONKEYVALUELISTDATA_H_