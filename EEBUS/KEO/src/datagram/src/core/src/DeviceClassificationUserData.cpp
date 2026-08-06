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

#include <keo_datagram/core/DeviceClassificationUserData.h>

#include <keo_datagram/core/DeviceClassificationUserDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceClassificationUserData::DeviceClassificationUserData()
    : CmdData(), m_userNodeIdentificationIsSet(false),
      m_userNodeIdentification(""), m_userLabelIsSet(false), m_userLabel(""),
      m_userDescriptionIsSet(false), m_userDescription("")

{}

DeviceClassificationUserData::DeviceClassificationUserData(
    const xs_string &c_userNodeIdentification, const xs_string &c_userLabel,
    const xs_string &c_userDescription)
    : CmdData(), m_userNodeIdentificationIsSet(true),
      m_userNodeIdentification(c_userNodeIdentification),
      m_userLabelIsSet(true), m_userLabel(c_userLabel),
      m_userDescriptionIsSet(true), m_userDescription(c_userDescription)

{}

bool DeviceClassificationUserData::
operator==(const DeviceClassificationUserData &c_classObject) const {
  if (m_userNodeIdentificationIsSet !=
          c_classObject.m_userNodeIdentificationIsSet ||
      (m_userNodeIdentificationIsSet &&
       (m_userNodeIdentification != c_classObject.m_userNodeIdentification))) {
    return false;
  }
  if (m_userLabelIsSet != c_classObject.m_userLabelIsSet ||
      (m_userLabelIsSet && (m_userLabel != c_classObject.m_userLabel))) {
    return false;
  }
  if (m_userDescriptionIsSet != c_classObject.m_userDescriptionIsSet ||
      (m_userDescriptionIsSet &&
       (m_userDescription != c_classObject.m_userDescription))) {
    return false;
  }

  return true;
}

bool DeviceClassificationUserData::
operator!=(const DeviceClassificationUserData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceClassificationUserData::isEmpty() const {
  return !m_userNodeIdentificationIsSet && !m_userLabelIsSet &&
         !m_userDescriptionIsSet;
}

CmdData::Type DeviceClassificationUserData::getDataType() const {
  return CmdData::Type::DEVICE_CLASSIFICATION_USER_DATA_TYPE;
}

CmdDataPtr DeviceClassificationUserData::clone() const {
  return std::make_shared<DeviceClassificationUserData>(*this);
}

void DeviceClassificationUserData::setUserNodeIdentification(
    const xs_string &userNodeIdentification) {
  m_userNodeIdentification = userNodeIdentification;
  m_userNodeIdentificationIsSet = true;
}

const xs_string &
DeviceClassificationUserData::getUserNodeIdentification() const {
  return m_userNodeIdentification;
}

void DeviceClassificationUserData::cleanUserNodeIdentification() {
  m_userNodeIdentification = "";
  m_userNodeIdentificationIsSet = false;
}

bool DeviceClassificationUserData::getUserNodeIdentificationIsSet() const {
  return m_userNodeIdentificationIsSet;
}

void DeviceClassificationUserData::setUserLabel(const xs_string &userLabel) {
  m_userLabel = userLabel;
  m_userLabelIsSet = true;
}

const xs_string &DeviceClassificationUserData::getUserLabel() const {
  return m_userLabel;
}

void DeviceClassificationUserData::cleanUserLabel() {
  m_userLabel = "";
  m_userLabelIsSet = false;
}

bool DeviceClassificationUserData::getUserLabelIsSet() const {
  return m_userLabelIsSet;
}

void DeviceClassificationUserData::setUserDescription(
    const xs_string &userDescription) {
  m_userDescription = userDescription;
  m_userDescriptionIsSet = true;
}

const xs_string &DeviceClassificationUserData::getUserDescription() const {
  return m_userDescription;
}

void DeviceClassificationUserData::cleanUserDescription() {
  m_userDescription = "";
  m_userDescriptionIsSet = false;
}

bool DeviceClassificationUserData::getUserDescriptionIsSet() const {
  return m_userDescriptionIsSet;
}

CmdDataPtr
DeviceClassificationUserData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      DeviceClassificationUserDataElementsPtr elements =
          std::dynamic_pointer_cast<DeviceClassificationUserDataElements>(
              filter.getDataElements());
      if (elements) {
        DeviceClassificationUserDataPtr dataOut =
            std::make_shared<DeviceClassificationUserData>();
        // TODO make sure to always set identifier

        if (getUserNodeIdentificationIsSet() &&
            elements->getUserNodeIdentificationIsSet()) {
          dataOut->setUserNodeIdentification(getUserNodeIdentification());
        }

        if (getUserLabelIsSet() && elements->getUserLabelIsSet()) {
          dataOut->setUserLabel(getUserLabel());
        }

        if (getUserDescriptionIsSet() && elements->getUserDescriptionIsSet()) {
          dataOut->setUserDescription(getUserDescription());
        }

        return dataOut;
      } else {
        return std::make_shared<DeviceClassificationUserData>(*this);
      }
    } else {
      return std::make_shared<DeviceClassificationUserData>(*this);
    }
  } else {
    return std::make_shared<DeviceClassificationUserData>(*this);
  }
}

bool DeviceClassificationUserData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"userNodeIdentification", "userLabel", "userDescription"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "userNodeIdentification",
                                   &m_userNodeIdentification)) {
      m_userNodeIdentificationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "userLabel", &m_userLabel)) {
      m_userLabelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "userDescription", &m_userDescription)) {
      m_userDescriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceClassificationUserData::toJson() const {
  std::string result = "[";
  if (m_userNodeIdentificationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("userNodeIdentification",
                                           m_userNodeIdentification);
  }
  if (m_userLabelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("userLabel", m_userLabel);
  }
  if (m_userDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("userDescription", m_userDescription);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram