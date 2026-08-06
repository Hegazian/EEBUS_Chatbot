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

#include <keo_datagram/core/DeviceAddress.h>

#include <keo_datagram/core/DeviceAddressElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceAddress::DeviceAddress()
    : m_deviceIsSet(false), m_device("")

{}

DeviceAddress::DeviceAddress(const xs_string &c_device) { setDevice(c_device); }

bool DeviceAddress::operator==(const DeviceAddress &c_classObject) const {
  if (m_deviceIsSet != c_classObject.m_deviceIsSet ||
      (m_deviceIsSet && (m_device != c_classObject.m_device))) {
    return false;
  }

  return true;
}

bool DeviceAddress::operator!=(const DeviceAddress &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceAddress::isEmpty() const { return !m_deviceIsSet; }

void DeviceAddress::setDevice(const xs_string &device) {
  m_device = device;
  m_deviceIsSet = true;
}

const xs_string &DeviceAddress::getDevice() const { return m_device; }

void DeviceAddress::cleanDevice() {
  m_device = "";
  m_deviceIsSet = false;
}

bool DeviceAddress::getDeviceIsSet() const { return m_deviceIsSet; }

DeviceAddress
DeviceAddress::reduce(const DeviceAddressElements &elements) const {
  DeviceAddress dataOut;
  if (getDeviceIsSet() && elements.getDeviceIsSet()) {
    dataOut.setDevice(getDevice());
  }
  return dataOut;
}

bool DeviceAddress::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"device"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "device", &m_device)) {
      m_deviceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceAddress::toJson() const {
  std::string result = "[";
  if (m_deviceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("device", m_device);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram