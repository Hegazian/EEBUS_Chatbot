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

#include <keo_datagram/core/DeviceAddressElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceAddressElements::DeviceAddressElements()
    : m_deviceIsSet(false)

{}

DeviceAddressElements::DeviceAddressElements(const xs_boolean &c_deviceIsSet) {
  if (c_deviceIsSet) {
    setDevice();
  }
}

bool DeviceAddressElements::
operator==(const DeviceAddressElements &c_classObject) const {
  if (m_deviceIsSet != c_classObject.m_deviceIsSet) {
    return false;
  }

  return true;
}

bool DeviceAddressElements::
operator!=(const DeviceAddressElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceAddressElements::isEmpty() const { return !m_deviceIsSet; }

void DeviceAddressElements::setDevice() { m_deviceIsSet = true; }

void DeviceAddressElements::cleanDevice() { m_deviceIsSet = false; }

bool DeviceAddressElements::getDeviceIsSet() const { return m_deviceIsSet; }

bool DeviceAddressElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"device"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "device")) {
      m_deviceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceAddressElements::toJson() const {
  std::string result = "[";
  if (m_deviceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("device");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram