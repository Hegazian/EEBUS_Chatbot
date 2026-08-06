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

#include <keo_datagram/core/DeviceClassificationUserDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceClassificationUserDataElements::DeviceClassificationUserDataElements()
    : DataElements(), m_userNodeIdentificationIsSet(false),
      m_userLabelIsSet(false), m_userDescriptionIsSet(false)

{}

DeviceClassificationUserDataElements::DeviceClassificationUserDataElements(
    xs_boolean c_userNodeIdentificationIsSet, xs_boolean c_userLabelIsSet,
    xs_boolean c_userDescriptionIsSet)
    : DataElements(),
      m_userNodeIdentificationIsSet(c_userNodeIdentificationIsSet),
      m_userLabelIsSet(c_userLabelIsSet),
      m_userDescriptionIsSet(c_userDescriptionIsSet)

{}

bool DeviceClassificationUserDataElements::
operator==(const DeviceClassificationUserDataElements &c_classObject) const {
  if (m_userNodeIdentificationIsSet !=
      c_classObject.m_userNodeIdentificationIsSet) {
    return false;
  }
  if (m_userLabelIsSet != c_classObject.m_userLabelIsSet) {
    return false;
  }
  if (m_userDescriptionIsSet != c_classObject.m_userDescriptionIsSet) {
    return false;
  }

  return true;
}

bool DeviceClassificationUserDataElements::
operator!=(const DeviceClassificationUserDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceClassificationUserDataElements::isEmpty() const {
  return !m_userNodeIdentificationIsSet && !m_userLabelIsSet &&
         !m_userDescriptionIsSet;
}

DataElements::Type DeviceClassificationUserDataElements::getDataType() const {
  return DataElements::Type::DEVICE_CLASSIFICATION_USER_DATA_ELEMENTS_TYPE;
}

DataElementsPtr DeviceClassificationUserDataElements::clone() const {
  return std::make_shared<DeviceClassificationUserDataElements>(*this);
}

void DeviceClassificationUserDataElements::setUserNodeIdentification() {
  m_userNodeIdentificationIsSet = true;
}

void DeviceClassificationUserDataElements::cleanUserNodeIdentification() {
  m_userNodeIdentificationIsSet = false;
}

bool DeviceClassificationUserDataElements::getUserNodeIdentificationIsSet()
    const {
  return m_userNodeIdentificationIsSet;
}

void DeviceClassificationUserDataElements::setUserLabel() {
  m_userLabelIsSet = true;
}

void DeviceClassificationUserDataElements::cleanUserLabel() {
  m_userLabelIsSet = false;
}

bool DeviceClassificationUserDataElements::getUserLabelIsSet() const {
  return m_userLabelIsSet;
}

void DeviceClassificationUserDataElements::setUserDescription() {
  m_userDescriptionIsSet = true;
}

void DeviceClassificationUserDataElements::cleanUserDescription() {
  m_userDescriptionIsSet = false;
}

bool DeviceClassificationUserDataElements::getUserDescriptionIsSet() const {
  return m_userDescriptionIsSet;
}

bool DeviceClassificationUserDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"userNodeIdentification", "userLabel", "userDescription"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "userNodeIdentification")) {
      m_userNodeIdentificationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "userLabel")) {
      m_userLabelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "userDescription")) {
      m_userDescriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceClassificationUserDataElements::toJson() const {
  std::string result = "[";
  if (m_userNodeIdentificationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("userNodeIdentification");
  }
  if (m_userLabelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("userLabel");
  }
  if (m_userDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("userDescription");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram