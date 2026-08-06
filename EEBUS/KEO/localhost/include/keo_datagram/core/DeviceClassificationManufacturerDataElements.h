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

#ifndef KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONMANUFACTURERDATAELEMENTS_H_
#define KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONMANUFACTURERDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration DeviceClassificationManufacturerDataElements
 */
class DeviceClassificationManufacturerDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  DeviceClassificationManufacturerDataElements();

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
      const DeviceClassificationManufacturerDataElements &c_classObject) const;

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
      const DeviceClassificationManufacturerDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member DeviceName.
   */
  void setDeviceName();

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
   */
  void setDeviceCode();

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
   */
  void setSerialNumber();

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
   */
  void setSoftwareRevision();

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
   */
  void setHardwareRevision();

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
   */
  void setVendorName();

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
   */
  void setVendorCode();

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
   */
  void setBrandName();

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
   */
  void setPowerSource();

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
   */
  void setManufacturerNodeIdentification();

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
   */
  void setManufacturerLabel();

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
   */
  void setManufacturerDescription();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_deviceNameIsSet;

  // ElementTag
  bool m_deviceCodeIsSet;

  // ElementTag
  bool m_serialNumberIsSet;

  // ElementTag
  bool m_softwareRevisionIsSet;

  // ElementTag
  bool m_hardwareRevisionIsSet;

  // ElementTag
  bool m_vendorNameIsSet;

  // ElementTag
  bool m_vendorCodeIsSet;

  // ElementTag
  bool m_brandNameIsSet;

  // ElementTag
  bool m_powerSourceIsSet;

  // ElementTag
  bool m_manufacturerNodeIdentificationIsSet;

  // ElementTag
  bool m_manufacturerLabelIsSet;

  // ElementTag
  bool m_manufacturerDescriptionIsSet;
};

//! typedef for non-const smart pointer type
//! DeviceClassificationManufacturerDataElements
using DeviceClassificationManufacturerDataElementsPtr =
    std::shared_ptr<DeviceClassificationManufacturerDataElements>;

//! typedef for const type DeviceClassificationManufacturerDataElements
using DeviceClassificationManufacturerDataElementsConst =
    const DeviceClassificationManufacturerDataElements;

//! typedef for const type DeviceClassificationManufacturerDataElements
using DeviceClassificationManufacturerDataElementsConstPtr =
    std::shared_ptr<DeviceClassificationManufacturerDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONMANUFACTURERDATAELEMENTS_H_