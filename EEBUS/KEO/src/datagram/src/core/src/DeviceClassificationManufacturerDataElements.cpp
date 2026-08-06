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

#include <keo_datagram/core/DeviceClassificationManufacturerDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceClassificationManufacturerDataElements::
    DeviceClassificationManufacturerDataElements()
    : DataElements(), m_deviceNameIsSet(false), m_deviceCodeIsSet(false),
      m_serialNumberIsSet(false), m_softwareRevisionIsSet(false),
      m_hardwareRevisionIsSet(false), m_vendorNameIsSet(false),
      m_vendorCodeIsSet(false), m_brandNameIsSet(false),
      m_powerSourceIsSet(false), m_manufacturerNodeIdentificationIsSet(false),
      m_manufacturerLabelIsSet(false), m_manufacturerDescriptionIsSet(false)

{}

bool DeviceClassificationManufacturerDataElements::operator==(
    const DeviceClassificationManufacturerDataElements &c_classObject) const {
  if (m_deviceNameIsSet != c_classObject.m_deviceNameIsSet) {
    return false;
  }
  if (m_deviceCodeIsSet != c_classObject.m_deviceCodeIsSet) {
    return false;
  }
  if (m_serialNumberIsSet != c_classObject.m_serialNumberIsSet) {
    return false;
  }
  if (m_softwareRevisionIsSet != c_classObject.m_softwareRevisionIsSet) {
    return false;
  }
  if (m_hardwareRevisionIsSet != c_classObject.m_hardwareRevisionIsSet) {
    return false;
  }
  if (m_vendorNameIsSet != c_classObject.m_vendorNameIsSet) {
    return false;
  }
  if (m_vendorCodeIsSet != c_classObject.m_vendorCodeIsSet) {
    return false;
  }
  if (m_brandNameIsSet != c_classObject.m_brandNameIsSet) {
    return false;
  }
  if (m_powerSourceIsSet != c_classObject.m_powerSourceIsSet) {
    return false;
  }
  if (m_manufacturerNodeIdentificationIsSet !=
      c_classObject.m_manufacturerNodeIdentificationIsSet) {
    return false;
  }
  if (m_manufacturerLabelIsSet != c_classObject.m_manufacturerLabelIsSet) {
    return false;
  }
  if (m_manufacturerDescriptionIsSet !=
      c_classObject.m_manufacturerDescriptionIsSet) {
    return false;
  }

  return true;
}

bool DeviceClassificationManufacturerDataElements::operator!=(
    const DeviceClassificationManufacturerDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceClassificationManufacturerDataElements::isEmpty() const {
  return !m_deviceNameIsSet && !m_deviceCodeIsSet && !m_serialNumberIsSet &&
         !m_softwareRevisionIsSet && !m_hardwareRevisionIsSet &&
         !m_vendorNameIsSet && !m_vendorCodeIsSet && !m_brandNameIsSet &&
         !m_powerSourceIsSet && !m_manufacturerNodeIdentificationIsSet &&
         !m_manufacturerLabelIsSet && !m_manufacturerDescriptionIsSet;
}

DataElements::Type
DeviceClassificationManufacturerDataElements::getDataType() const {
  return DataElements::Type::
      DEVICE_CLASSIFICATION_MANUFACTURER_DATA_ELEMENTS_TYPE;
}

DataElementsPtr DeviceClassificationManufacturerDataElements::clone() const {
  return std::make_shared<DeviceClassificationManufacturerDataElements>(*this);
}

void DeviceClassificationManufacturerDataElements::setDeviceName() {
  m_deviceNameIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanDeviceName() {
  m_deviceNameIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getDeviceNameIsSet() const {
  return m_deviceNameIsSet;
}

void DeviceClassificationManufacturerDataElements::setDeviceCode() {
  m_deviceCodeIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanDeviceCode() {
  m_deviceCodeIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getDeviceCodeIsSet() const {
  return m_deviceCodeIsSet;
}

void DeviceClassificationManufacturerDataElements::setSerialNumber() {
  m_serialNumberIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanSerialNumber() {
  m_serialNumberIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getSerialNumberIsSet()
    const {
  return m_serialNumberIsSet;
}

void DeviceClassificationManufacturerDataElements::setSoftwareRevision() {
  m_softwareRevisionIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanSoftwareRevision() {
  m_softwareRevisionIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getSoftwareRevisionIsSet()
    const {
  return m_softwareRevisionIsSet;
}

void DeviceClassificationManufacturerDataElements::setHardwareRevision() {
  m_hardwareRevisionIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanHardwareRevision() {
  m_hardwareRevisionIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getHardwareRevisionIsSet()
    const {
  return m_hardwareRevisionIsSet;
}

void DeviceClassificationManufacturerDataElements::setVendorName() {
  m_vendorNameIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanVendorName() {
  m_vendorNameIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getVendorNameIsSet() const {
  return m_vendorNameIsSet;
}

void DeviceClassificationManufacturerDataElements::setVendorCode() {
  m_vendorCodeIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanVendorCode() {
  m_vendorCodeIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getVendorCodeIsSet() const {
  return m_vendorCodeIsSet;
}

void DeviceClassificationManufacturerDataElements::setBrandName() {
  m_brandNameIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanBrandName() {
  m_brandNameIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getBrandNameIsSet() const {
  return m_brandNameIsSet;
}

void DeviceClassificationManufacturerDataElements::setPowerSource() {
  m_powerSourceIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanPowerSource() {
  m_powerSourceIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getPowerSourceIsSet() const {
  return m_powerSourceIsSet;
}

void DeviceClassificationManufacturerDataElements::
    setManufacturerNodeIdentification() {
  m_manufacturerNodeIdentificationIsSet = true;
}

void DeviceClassificationManufacturerDataElements::
    cleanManufacturerNodeIdentification() {
  m_manufacturerNodeIdentificationIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::
    getManufacturerNodeIdentificationIsSet() const {
  return m_manufacturerNodeIdentificationIsSet;
}

void DeviceClassificationManufacturerDataElements::setManufacturerLabel() {
  m_manufacturerLabelIsSet = true;
}

void DeviceClassificationManufacturerDataElements::cleanManufacturerLabel() {
  m_manufacturerLabelIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::getManufacturerLabelIsSet()
    const {
  return m_manufacturerLabelIsSet;
}

void DeviceClassificationManufacturerDataElements::
    setManufacturerDescription() {
  m_manufacturerDescriptionIsSet = true;
}

void DeviceClassificationManufacturerDataElements::
    cleanManufacturerDescription() {
  m_manufacturerDescriptionIsSet = false;
}

bool DeviceClassificationManufacturerDataElements::
    getManufacturerDescriptionIsSet() const {
  return m_manufacturerDescriptionIsSet;
}

bool DeviceClassificationManufacturerDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"deviceName", "deviceCode", "serialNumber", "softwareRevision",
             "hardwareRevision", "vendorName", "vendorCode", "brandName",
             "powerSource", "manufacturerNodeIdentification",
             "manufacturerLabel", "manufacturerDescription"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "deviceName")) {
      m_deviceNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "deviceCode")) {
      m_deviceCodeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "serialNumber")) {
      m_serialNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "softwareRevision")) {
      m_softwareRevisionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "hardwareRevision")) {
      m_hardwareRevisionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "vendorName")) {
      m_vendorNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "vendorCode")) {
      m_vendorCodeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "brandName")) {
      m_brandNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "powerSource")) {
      m_powerSourceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "manufacturerNodeIdentification")) {
      m_manufacturerNodeIdentificationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "manufacturerLabel")) {
      m_manufacturerLabelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "manufacturerDescription")) {
      m_manufacturerDescriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceClassificationManufacturerDataElements::toJson() const {
  std::string result = "[";
  if (m_deviceNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("deviceName");
  }
  if (m_deviceCodeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("deviceCode");
  }
  if (m_serialNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("serialNumber");
  }
  if (m_softwareRevisionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("softwareRevision");
  }
  if (m_hardwareRevisionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("hardwareRevision");
  }
  if (m_vendorNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("vendorName");
  }
  if (m_vendorCodeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("vendorCode");
  }
  if (m_brandNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("brandName");
  }
  if (m_powerSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("powerSource");
  }
  if (m_manufacturerNodeIdentificationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("manufacturerNodeIdentification");
  }
  if (m_manufacturerLabelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("manufacturerLabel");
  }
  if (m_manufacturerDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("manufacturerDescription");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram