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

#include <keo_datagram/core/DeviceClassificationManufacturerData.h>

#include <keo_datagram/core/DeviceClassificationManufacturerDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceClassificationManufacturerData::DeviceClassificationManufacturerData()
    : CmdData(), m_deviceNameIsSet(false), m_deviceName(""),
      m_deviceCodeIsSet(false), m_deviceCode(""), m_serialNumberIsSet(false),
      m_serialNumber(""), m_softwareRevisionIsSet(false),
      m_softwareRevision(""), m_hardwareRevisionIsSet(false),
      m_hardwareRevision(""), m_vendorNameIsSet(false), m_vendorName(""),
      m_vendorCodeIsSet(false), m_vendorCode(""), m_brandNameIsSet(false),
      m_brandName(""), m_powerSourceIsSet(false), m_powerSource(PowerSource()),
      m_manufacturerNodeIdentificationIsSet(false),
      m_manufacturerNodeIdentification(""), m_manufacturerLabelIsSet(false),
      m_manufacturerLabel(""), m_manufacturerDescriptionIsSet(false),
      m_manufacturerDescription("")

{}

bool DeviceClassificationManufacturerData::
operator==(const DeviceClassificationManufacturerData &c_classObject) const {
  if (m_deviceNameIsSet != c_classObject.m_deviceNameIsSet ||
      (m_deviceNameIsSet && (m_deviceName != c_classObject.m_deviceName))) {
    return false;
  }
  if (m_deviceCodeIsSet != c_classObject.m_deviceCodeIsSet ||
      (m_deviceCodeIsSet && (m_deviceCode != c_classObject.m_deviceCode))) {
    return false;
  }
  if (m_serialNumberIsSet != c_classObject.m_serialNumberIsSet ||
      (m_serialNumberIsSet &&
       (m_serialNumber != c_classObject.m_serialNumber))) {
    return false;
  }
  if (m_softwareRevisionIsSet != c_classObject.m_softwareRevisionIsSet ||
      (m_softwareRevisionIsSet &&
       (m_softwareRevision != c_classObject.m_softwareRevision))) {
    return false;
  }
  if (m_hardwareRevisionIsSet != c_classObject.m_hardwareRevisionIsSet ||
      (m_hardwareRevisionIsSet &&
       (m_hardwareRevision != c_classObject.m_hardwareRevision))) {
    return false;
  }
  if (m_vendorNameIsSet != c_classObject.m_vendorNameIsSet ||
      (m_vendorNameIsSet && (m_vendorName != c_classObject.m_vendorName))) {
    return false;
  }
  if (m_vendorCodeIsSet != c_classObject.m_vendorCodeIsSet ||
      (m_vendorCodeIsSet && (m_vendorCode != c_classObject.m_vendorCode))) {
    return false;
  }
  if (m_brandNameIsSet != c_classObject.m_brandNameIsSet ||
      (m_brandNameIsSet && (m_brandName != c_classObject.m_brandName))) {
    return false;
  }
  if (m_powerSourceIsSet != c_classObject.m_powerSourceIsSet ||
      (m_powerSourceIsSet && (m_powerSource != c_classObject.m_powerSource))) {
    return false;
  }
  if (m_manufacturerNodeIdentificationIsSet !=
          c_classObject.m_manufacturerNodeIdentificationIsSet ||
      (m_manufacturerNodeIdentificationIsSet &&
       (m_manufacturerNodeIdentification !=
        c_classObject.m_manufacturerNodeIdentification))) {
    return false;
  }
  if (m_manufacturerLabelIsSet != c_classObject.m_manufacturerLabelIsSet ||
      (m_manufacturerLabelIsSet &&
       (m_manufacturerLabel != c_classObject.m_manufacturerLabel))) {
    return false;
  }
  if (m_manufacturerDescriptionIsSet !=
          c_classObject.m_manufacturerDescriptionIsSet ||
      (m_manufacturerDescriptionIsSet &&
       (m_manufacturerDescription !=
        c_classObject.m_manufacturerDescription))) {
    return false;
  }

  return true;
}

bool DeviceClassificationManufacturerData::
operator!=(const DeviceClassificationManufacturerData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceClassificationManufacturerData::isEmpty() const {
  return !m_deviceNameIsSet && !m_deviceCodeIsSet && !m_serialNumberIsSet &&
         !m_softwareRevisionIsSet && !m_hardwareRevisionIsSet &&
         !m_vendorNameIsSet && !m_vendorCodeIsSet && !m_brandNameIsSet &&
         !m_powerSourceIsSet && !m_manufacturerNodeIdentificationIsSet &&
         !m_manufacturerLabelIsSet && !m_manufacturerDescriptionIsSet;
}

CmdData::Type DeviceClassificationManufacturerData::getDataType() const {
  return CmdData::Type::DEVICE_CLASSIFICATION_MANUFACTURER_DATA_TYPE;
}

CmdDataPtr DeviceClassificationManufacturerData::clone() const {
  return std::make_shared<DeviceClassificationManufacturerData>(*this);
}

void DeviceClassificationManufacturerData::setDeviceName(
    const xs_string &deviceName) {
  m_deviceName = deviceName;
  m_deviceNameIsSet = true;
}

const xs_string &DeviceClassificationManufacturerData::getDeviceName() const {
  return m_deviceName;
}

void DeviceClassificationManufacturerData::cleanDeviceName() {
  m_deviceName = "";
  m_deviceNameIsSet = false;
}

bool DeviceClassificationManufacturerData::getDeviceNameIsSet() const {
  return m_deviceNameIsSet;
}

void DeviceClassificationManufacturerData::setDeviceCode(
    const xs_string &deviceCode) {
  m_deviceCode = deviceCode;
  m_deviceCodeIsSet = true;
}

const xs_string &DeviceClassificationManufacturerData::getDeviceCode() const {
  return m_deviceCode;
}

void DeviceClassificationManufacturerData::cleanDeviceCode() {
  m_deviceCode = "";
  m_deviceCodeIsSet = false;
}

bool DeviceClassificationManufacturerData::getDeviceCodeIsSet() const {
  return m_deviceCodeIsSet;
}

void DeviceClassificationManufacturerData::setSerialNumber(
    const xs_string &serialNumber) {
  m_serialNumber = serialNumber;
  m_serialNumberIsSet = true;
}

const xs_string &DeviceClassificationManufacturerData::getSerialNumber() const {
  return m_serialNumber;
}

void DeviceClassificationManufacturerData::cleanSerialNumber() {
  m_serialNumber = "";
  m_serialNumberIsSet = false;
}

bool DeviceClassificationManufacturerData::getSerialNumberIsSet() const {
  return m_serialNumberIsSet;
}

void DeviceClassificationManufacturerData::setSoftwareRevision(
    const xs_string &softwareRevision) {
  m_softwareRevision = softwareRevision;
  m_softwareRevisionIsSet = true;
}

const xs_string &
DeviceClassificationManufacturerData::getSoftwareRevision() const {
  return m_softwareRevision;
}

void DeviceClassificationManufacturerData::cleanSoftwareRevision() {
  m_softwareRevision = "";
  m_softwareRevisionIsSet = false;
}

bool DeviceClassificationManufacturerData::getSoftwareRevisionIsSet() const {
  return m_softwareRevisionIsSet;
}

void DeviceClassificationManufacturerData::setHardwareRevision(
    const xs_string &hardwareRevision) {
  m_hardwareRevision = hardwareRevision;
  m_hardwareRevisionIsSet = true;
}

const xs_string &
DeviceClassificationManufacturerData::getHardwareRevision() const {
  return m_hardwareRevision;
}

void DeviceClassificationManufacturerData::cleanHardwareRevision() {
  m_hardwareRevision = "";
  m_hardwareRevisionIsSet = false;
}

bool DeviceClassificationManufacturerData::getHardwareRevisionIsSet() const {
  return m_hardwareRevisionIsSet;
}

void DeviceClassificationManufacturerData::setVendorName(
    const xs_string &vendorName) {
  m_vendorName = vendorName;
  m_vendorNameIsSet = true;
}

const xs_string &DeviceClassificationManufacturerData::getVendorName() const {
  return m_vendorName;
}

void DeviceClassificationManufacturerData::cleanVendorName() {
  m_vendorName = "";
  m_vendorNameIsSet = false;
}

bool DeviceClassificationManufacturerData::getVendorNameIsSet() const {
  return m_vendorNameIsSet;
}

void DeviceClassificationManufacturerData::setVendorCode(
    const xs_string &vendorCode) {
  m_vendorCode = vendorCode;
  m_vendorCodeIsSet = true;
}

const xs_string &DeviceClassificationManufacturerData::getVendorCode() const {
  return m_vendorCode;
}

void DeviceClassificationManufacturerData::cleanVendorCode() {
  m_vendorCode = "";
  m_vendorCodeIsSet = false;
}

bool DeviceClassificationManufacturerData::getVendorCodeIsSet() const {
  return m_vendorCodeIsSet;
}

void DeviceClassificationManufacturerData::setBrandName(
    const xs_string &brandName) {
  m_brandName = brandName;
  m_brandNameIsSet = true;
}

const xs_string &DeviceClassificationManufacturerData::getBrandName() const {
  return m_brandName;
}

void DeviceClassificationManufacturerData::cleanBrandName() {
  m_brandName = "";
  m_brandNameIsSet = false;
}

bool DeviceClassificationManufacturerData::getBrandNameIsSet() const {
  return m_brandNameIsSet;
}

void DeviceClassificationManufacturerData::setPowerSource(
    const PowerSource &powerSource) {
  m_powerSource = powerSource;
  m_powerSourceIsSet = true;
}

const PowerSource &
DeviceClassificationManufacturerData::getPowerSource() const {
  return m_powerSource;
}

void DeviceClassificationManufacturerData::cleanPowerSource() {
  m_powerSource = PowerSource();
  m_powerSourceIsSet = false;
}

bool DeviceClassificationManufacturerData::getPowerSourceIsSet() const {
  return m_powerSourceIsSet;
}

void DeviceClassificationManufacturerData::setManufacturerNodeIdentification(
    const xs_string &manufacturerNodeIdentification) {
  m_manufacturerNodeIdentification = manufacturerNodeIdentification;
  m_manufacturerNodeIdentificationIsSet = true;
}

const xs_string &
DeviceClassificationManufacturerData::getManufacturerNodeIdentification()
    const {
  return m_manufacturerNodeIdentification;
}

void DeviceClassificationManufacturerData::
    cleanManufacturerNodeIdentification() {
  m_manufacturerNodeIdentification = "";
  m_manufacturerNodeIdentificationIsSet = false;
}

bool DeviceClassificationManufacturerData::
    getManufacturerNodeIdentificationIsSet() const {
  return m_manufacturerNodeIdentificationIsSet;
}

void DeviceClassificationManufacturerData::setManufacturerLabel(
    const xs_string &manufacturerLabel) {
  m_manufacturerLabel = manufacturerLabel;
  m_manufacturerLabelIsSet = true;
}

const xs_string &
DeviceClassificationManufacturerData::getManufacturerLabel() const {
  return m_manufacturerLabel;
}

void DeviceClassificationManufacturerData::cleanManufacturerLabel() {
  m_manufacturerLabel = "";
  m_manufacturerLabelIsSet = false;
}

bool DeviceClassificationManufacturerData::getManufacturerLabelIsSet() const {
  return m_manufacturerLabelIsSet;
}

void DeviceClassificationManufacturerData::setManufacturerDescription(
    const xs_string &manufacturerDescription) {
  m_manufacturerDescription = manufacturerDescription;
  m_manufacturerDescriptionIsSet = true;
}

const xs_string &
DeviceClassificationManufacturerData::getManufacturerDescription() const {
  return m_manufacturerDescription;
}

void DeviceClassificationManufacturerData::cleanManufacturerDescription() {
  m_manufacturerDescription = "";
  m_manufacturerDescriptionIsSet = false;
}

bool DeviceClassificationManufacturerData::getManufacturerDescriptionIsSet()
    const {
  return m_manufacturerDescriptionIsSet;
}

CmdDataPtr DeviceClassificationManufacturerData::reduce(
    const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      DeviceClassificationManufacturerDataElementsPtr elements =
          std::dynamic_pointer_cast<
              DeviceClassificationManufacturerDataElements>(
              filter.getDataElements());
      if (elements) {
        DeviceClassificationManufacturerDataPtr dataOut =
            std::make_shared<DeviceClassificationManufacturerData>();
        // TODO make sure to always set identifier

        if (getDeviceNameIsSet() && elements->getDeviceNameIsSet()) {
          dataOut->setDeviceName(getDeviceName());
        }

        if (getDeviceCodeIsSet() && elements->getDeviceCodeIsSet()) {
          dataOut->setDeviceCode(getDeviceCode());
        }

        if (getSerialNumberIsSet() && elements->getSerialNumberIsSet()) {
          dataOut->setSerialNumber(getSerialNumber());
        }

        if (getSoftwareRevisionIsSet() &&
            elements->getSoftwareRevisionIsSet()) {
          dataOut->setSoftwareRevision(getSoftwareRevision());
        }

        if (getHardwareRevisionIsSet() &&
            elements->getHardwareRevisionIsSet()) {
          dataOut->setHardwareRevision(getHardwareRevision());
        }

        if (getVendorNameIsSet() && elements->getVendorNameIsSet()) {
          dataOut->setVendorName(getVendorName());
        }

        if (getVendorCodeIsSet() && elements->getVendorCodeIsSet()) {
          dataOut->setVendorCode(getVendorCode());
        }

        if (getBrandNameIsSet() && elements->getBrandNameIsSet()) {
          dataOut->setBrandName(getBrandName());
        }

        if (getPowerSourceIsSet() && elements->getPowerSourceIsSet()) {
          dataOut->setPowerSource(getPowerSource());
        }

        if (getManufacturerNodeIdentificationIsSet() &&
            elements->getManufacturerNodeIdentificationIsSet()) {
          dataOut->setManufacturerNodeIdentification(
              getManufacturerNodeIdentification());
        }

        if (getManufacturerLabelIsSet() &&
            elements->getManufacturerLabelIsSet()) {
          dataOut->setManufacturerLabel(getManufacturerLabel());
        }

        if (getManufacturerDescriptionIsSet() &&
            elements->getManufacturerDescriptionIsSet()) {
          dataOut->setManufacturerDescription(getManufacturerDescription());
        }

        return dataOut;
      } else {
        return std::make_shared<DeviceClassificationManufacturerData>(*this);
      }
    } else {
      return std::make_shared<DeviceClassificationManufacturerData>(*this);
    }
  } else {
    return std::make_shared<DeviceClassificationManufacturerData>(*this);
  }
}

bool DeviceClassificationManufacturerData::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "deviceName", &m_deviceName)) {
      m_deviceNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "deviceCode", &m_deviceCode)) {
      m_deviceCodeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "serialNumber", &m_serialNumber)) {
      m_serialNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "softwareRevision", &m_softwareRevision)) {
      m_softwareRevisionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "hardwareRevision", &m_hardwareRevision)) {
      m_hardwareRevisionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "vendorName", &m_vendorName)) {
      m_vendorNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "vendorCode", &m_vendorCode)) {
      m_vendorCodeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "brandName", &m_brandName)) {
      m_brandNameIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "powerSource", &m_powerSource)) {
      m_powerSourceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "manufacturerNodeIdentification",
                                   &m_manufacturerNodeIdentification)) {
      m_manufacturerNodeIdentificationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "manufacturerLabel", &m_manufacturerLabel)) {
      m_manufacturerLabelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "manufacturerDescription",
                                   &m_manufacturerDescription)) {
      m_manufacturerDescriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceClassificationManufacturerData::toJson() const {
  std::string result = "[";
  if (m_deviceNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("deviceName", m_deviceName);
  }
  if (m_deviceCodeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("deviceCode", m_deviceCode);
  }
  if (m_serialNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("serialNumber", m_serialNumber);
  }
  if (m_softwareRevisionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("softwareRevision", m_softwareRevision);
  }
  if (m_hardwareRevisionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("hardwareRevision", m_hardwareRevision);
  }
  if (m_vendorNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("vendorName", m_vendorName);
  }
  if (m_vendorCodeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("vendorCode", m_vendorCode);
  }
  if (m_brandNameIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("brandName", m_brandName);
  }
  if (m_powerSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("powerSource", m_powerSource);
  }
  if (m_manufacturerNodeIdentificationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("manufacturerNodeIdentification",
                                           m_manufacturerNodeIdentification);
  }
  if (m_manufacturerLabelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("manufacturerLabel", m_manufacturerLabel);
  }
  if (m_manufacturerDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("manufacturerDescription",
                                           m_manufacturerDescription);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram