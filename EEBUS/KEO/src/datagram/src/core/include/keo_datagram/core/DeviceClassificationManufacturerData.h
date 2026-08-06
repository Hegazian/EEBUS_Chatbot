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

#ifndef KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONMANUFACTURERDATA_H_
#define KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONMANUFACTURERDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/PowerSource.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration DeviceClassificationManufacturerData
 */
class DeviceClassificationManufacturerData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  DeviceClassificationManufacturerData();

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
  operator==(const DeviceClassificationManufacturerData &c_classObject) const;

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
  operator!=(const DeviceClassificationManufacturerData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member DeviceName.
   * @param c_deviceName Value to set
   */
  void setDeviceName(const xs_string &c_deviceName);

  /**
   * Returns const reference to member DeviceName.
   * @return const reference to member deviceName
   */
  const xs_string &getDeviceName() const;

  /**
   * Returns if member DeviceName is set.
   * @retval true member DeviceName is set
   * @retval false member DeviceName is not set
   */
  bool getDeviceNameIsSet() const;

  /**
   * Unsets member DeviceName
   */
  void cleanDeviceName();

  /**
   * Set member DeviceCode.
   * @param c_deviceCode Value to set
   */
  void setDeviceCode(const xs_string &c_deviceCode);

  /**
   * Returns const reference to member DeviceCode.
   * @return const reference to member deviceCode
   */
  const xs_string &getDeviceCode() const;

  /**
   * Returns if member DeviceCode is set.
   * @retval true member DeviceCode is set
   * @retval false member DeviceCode is not set
   */
  bool getDeviceCodeIsSet() const;

  /**
   * Unsets member DeviceCode
   */
  void cleanDeviceCode();

  /**
   * Set member SerialNumber.
   * @param c_serialNumber Value to set
   */
  void setSerialNumber(const xs_string &c_serialNumber);

  /**
   * Returns const reference to member SerialNumber.
   * @return const reference to member serialNumber
   */
  const xs_string &getSerialNumber() const;

  /**
   * Returns if member SerialNumber is set.
   * @retval true member SerialNumber is set
   * @retval false member SerialNumber is not set
   */
  bool getSerialNumberIsSet() const;

  /**
   * Unsets member SerialNumber
   */
  void cleanSerialNumber();

  /**
   * Set member SoftwareRevision.
   * @param c_softwareRevision Value to set
   */
  void setSoftwareRevision(const xs_string &c_softwareRevision);

  /**
   * Returns const reference to member SoftwareRevision.
   * @return const reference to member softwareRevision
   */
  const xs_string &getSoftwareRevision() const;

  /**
   * Returns if member SoftwareRevision is set.
   * @retval true member SoftwareRevision is set
   * @retval false member SoftwareRevision is not set
   */
  bool getSoftwareRevisionIsSet() const;

  /**
   * Unsets member SoftwareRevision
   */
  void cleanSoftwareRevision();

  /**
   * Set member HardwareRevision.
   * @param c_hardwareRevision Value to set
   */
  void setHardwareRevision(const xs_string &c_hardwareRevision);

  /**
   * Returns const reference to member HardwareRevision.
   * @return const reference to member hardwareRevision
   */
  const xs_string &getHardwareRevision() const;

  /**
   * Returns if member HardwareRevision is set.
   * @retval true member HardwareRevision is set
   * @retval false member HardwareRevision is not set
   */
  bool getHardwareRevisionIsSet() const;

  /**
   * Unsets member HardwareRevision
   */
  void cleanHardwareRevision();

  /**
   * Set member VendorName.
   * @param c_vendorName Value to set
   */
  void setVendorName(const xs_string &c_vendorName);

  /**
   * Returns const reference to member VendorName.
   * @return const reference to member vendorName
   */
  const xs_string &getVendorName() const;

  /**
   * Returns if member VendorName is set.
   * @retval true member VendorName is set
   * @retval false member VendorName is not set
   */
  bool getVendorNameIsSet() const;

  /**
   * Unsets member VendorName
   */
  void cleanVendorName();

  /**
   * Set member VendorCode.
   * @param c_vendorCode Value to set
   */
  void setVendorCode(const xs_string &c_vendorCode);

  /**
   * Returns const reference to member VendorCode.
   * @return const reference to member vendorCode
   */
  const xs_string &getVendorCode() const;

  /**
   * Returns if member VendorCode is set.
   * @retval true member VendorCode is set
   * @retval false member VendorCode is not set
   */
  bool getVendorCodeIsSet() const;

  /**
   * Unsets member VendorCode
   */
  void cleanVendorCode();

  /**
   * Set member BrandName.
   * @param c_brandName Value to set
   */
  void setBrandName(const xs_string &c_brandName);

  /**
   * Returns const reference to member BrandName.
   * @return const reference to member brandName
   */
  const xs_string &getBrandName() const;

  /**
   * Returns if member BrandName is set.
   * @retval true member BrandName is set
   * @retval false member BrandName is not set
   */
  bool getBrandNameIsSet() const;

  /**
   * Unsets member BrandName
   */
  void cleanBrandName();

  /**
   * Set member PowerSource.
   * @param c_powerSource Value to set
   */
  void setPowerSource(const PowerSource &c_powerSource);

  /**
   * Returns const reference to member PowerSource.
   * @return const reference to member powerSource
   */
  const PowerSource &getPowerSource() const;

  /**
   * Returns if member PowerSource is set.
   * @retval true member PowerSource is set
   * @retval false member PowerSource is not set
   */
  bool getPowerSourceIsSet() const;

  /**
   * Unsets member PowerSource
   */
  void cleanPowerSource();

  /**
   * Set member ManufacturerNodeIdentification.
   * @param c_manufacturerNodeIdentification Value to set
   */
  void setManufacturerNodeIdentification(
      const xs_string &c_manufacturerNodeIdentification);

  /**
   * Returns const reference to member ManufacturerNodeIdentification.
   * @return const reference to member manufacturerNodeIdentification
   */
  const xs_string &getManufacturerNodeIdentification() const;

  /**
   * Returns if member ManufacturerNodeIdentification is set.
   * @retval true member ManufacturerNodeIdentification is set
   * @retval false member ManufacturerNodeIdentification is not set
   */
  bool getManufacturerNodeIdentificationIsSet() const;

  /**
   * Unsets member ManufacturerNodeIdentification
   */
  void cleanManufacturerNodeIdentification();

  /**
   * Set member ManufacturerLabel.
   * @param c_manufacturerLabel Value to set
   */
  void setManufacturerLabel(const xs_string &c_manufacturerLabel);

  /**
   * Returns const reference to member ManufacturerLabel.
   * @return const reference to member manufacturerLabel
   */
  const xs_string &getManufacturerLabel() const;

  /**
   * Returns if member ManufacturerLabel is set.
   * @retval true member ManufacturerLabel is set
   * @retval false member ManufacturerLabel is not set
   */
  bool getManufacturerLabelIsSet() const;

  /**
   * Unsets member ManufacturerLabel
   */
  void cleanManufacturerLabel();

  /**
   * Set member ManufacturerDescription.
   * @param c_manufacturerDescription Value to set
   */
  void setManufacturerDescription(const xs_string &c_manufacturerDescription);

  /**
   * Returns const reference to member ManufacturerDescription.
   * @return const reference to member manufacturerDescription
   */
  const xs_string &getManufacturerDescription() const;

  /**
   * Returns if member ManufacturerDescription is set.
   * @retval true member ManufacturerDescription is set
   * @retval false member ManufacturerDescription is not set
   */
  bool getManufacturerDescriptionIsSet() const;

  /**
   * Unsets member ManufacturerDescription
   */
  void cleanManufacturerDescription();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_deviceNameIsSet;
  xs_string m_deviceName;

  bool m_deviceCodeIsSet;
  xs_string m_deviceCode;

  bool m_serialNumberIsSet;
  xs_string m_serialNumber;

  bool m_softwareRevisionIsSet;
  xs_string m_softwareRevision;

  bool m_hardwareRevisionIsSet;
  xs_string m_hardwareRevision;

  bool m_vendorNameIsSet;
  xs_string m_vendorName;

  bool m_vendorCodeIsSet;
  xs_string m_vendorCode;

  bool m_brandNameIsSet;
  xs_string m_brandName;

  bool m_powerSourceIsSet;
  PowerSource m_powerSource;

  bool m_manufacturerNodeIdentificationIsSet;
  xs_string m_manufacturerNodeIdentification;

  bool m_manufacturerLabelIsSet;
  xs_string m_manufacturerLabel;

  bool m_manufacturerDescriptionIsSet;
  xs_string m_manufacturerDescription;
};

//! typedef for non-const smart pointer type
//! DeviceClassificationManufacturerData
using DeviceClassificationManufacturerDataPtr =
    std::shared_ptr<DeviceClassificationManufacturerData>;

//! typedef for const type DeviceClassificationManufacturerData
using DeviceClassificationManufacturerDataConst =
    const DeviceClassificationManufacturerData;

//! typedef for const type DeviceClassificationManufacturerData
using DeviceClassificationManufacturerDataConstPtr =
    std::shared_ptr<DeviceClassificationManufacturerDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONMANUFACTURERDATA_H_