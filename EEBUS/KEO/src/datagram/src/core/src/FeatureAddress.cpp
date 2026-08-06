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

#include <keo_datagram/core/FeatureAddress.h>

#include <keo_datagram/core/FeatureAddressElements.h>

#include "KeoStringUtil.h"

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

FeatureAddress::FeatureAddress()
    : m_deviceIsSet(false), m_device(""), m_entityIsSet(false),
      m_entity(std::vector<xs_unsignedInt>()), m_featureIsSet(false),
      m_feature(0)

{}

FeatureAddress::FeatureAddress(const FeatureAddress &c_classObject)
    : FeatureAddress() {
  m_deviceIsSet = c_classObject.m_deviceIsSet;
  m_device = c_classObject.m_device;
  m_entityIsSet = c_classObject.m_entityIsSet;
  m_entity = c_classObject.m_entity;
  m_featureIsSet = c_classObject.m_featureIsSet;
  m_feature = c_classObject.m_feature;
}

FeatureAddress::FeatureAddress(const std::string &c_device,
                               const std::vector<std::uint32_t> &c_entity,
                               const std::uint32_t &c_feature)
    : FeatureAddress() {
  setDevice(c_device);
  setEntity(c_entity);
  setFeature(c_feature);
}

FeatureAddress::FeatureAddress(const std::string &c_device,
                               const std::uint32_t &c_entity,
                               const std::uint32_t &c_feature)
    : FeatureAddress() {
  setDevice(c_device);
  m_entity.push_back(c_entity);
  m_entityIsSet = true;
  setFeature(c_feature);
}

FeatureAddress::FeatureAddress(const std::vector<std::uint32_t> &c_entity,
                               const std::uint32_t &c_feature)
    : FeatureAddress() {
  setEntity(c_entity);
  setFeature(c_feature);
}

FeatureAddress::FeatureAddress(const std::uint32_t &c_entity,
                               const std::uint32_t &c_feature)
    : FeatureAddress() {
  std::vector<std::uint32_t> entity = {c_entity};
  setEntity(entity);
  setFeature(c_feature);
}

bool FeatureAddress::operator==(const FeatureAddress &c_classObject) const {
  if (m_deviceIsSet != c_classObject.m_deviceIsSet ||
      (m_deviceIsSet && (m_device != c_classObject.m_device))) {
    return false;
  }
  if (m_entityIsSet != c_classObject.m_entityIsSet ||
      (m_entityIsSet && (m_entity != c_classObject.m_entity))) {
    return false;
  }
  if (m_featureIsSet != c_classObject.m_featureIsSet ||
      (m_featureIsSet && (m_feature != c_classObject.m_feature))) {
    return false;
  }

  return true;
}

bool FeatureAddress::operator!=(const FeatureAddress &c_classObject) const {
  return !(*this == c_classObject);
}

bool FeatureAddress::isEmpty() const {
  return !m_deviceIsSet && !m_entityIsSet && !m_featureIsSet;
}

bool FeatureAddress::operator>(const FeatureAddress &c_classObject) const {
  if ((this->m_deviceIsSet == c_classObject.m_deviceIsSet)) {
    int lexValue = this->getDevice().compare(c_classObject.getDevice());
    if (lexValue != 0) {
      return lexValue > 0;
    }
  }
  if ((this->m_entityIsSet == c_classObject.m_entityIsSet) &&
      (this->getEntity() != c_classObject.getEntity())) {
    std::vector<xs_unsignedInt> entity = this->getEntity();
    std::vector<xs_unsignedInt> entityOther = c_classObject.getEntity();
    std::vector<xs_unsignedInt>::const_iterator iterThis = entity.begin();
    std::vector<xs_unsignedInt>::const_iterator iterThisEnd = entity.end();
    std::vector<xs_unsignedInt>::const_iterator iterOther = entityOther.begin();
    std::vector<xs_unsignedInt>::const_iterator iterOtherEnd =
        entityOther.end();
    for (; iterThis != iterThisEnd && iterOther != iterOtherEnd;
         ++iterThis, ++iterOther) {
      if (*iterThis != *iterOther) {
        return *iterThis > *iterOther;
      }
    }
    if (this->getEntity().size() != c_classObject.getEntity().size()) {
      return this->getEntity().size() > c_classObject.getEntity().size();
    }
  }
  if ((this->m_featureIsSet == c_classObject.m_featureIsSet)) {
    return this->getFeature() > c_classObject.getFeature();
  }
  return false;
}

bool FeatureAddress::operator<(const FeatureAddress &c_classObject) const {
  return !(*this > c_classObject) && (*this != c_classObject);
}

bool FeatureAddress::equalsWeak(const FeatureAddress &c_classObject) const {
  if (this->m_deviceIsSet == c_classObject.m_deviceIsSet) {
    if (this->getDevice().compare(c_classObject.getDevice()) != 0) {
      return false;
    }
  }
  if (this->m_entityIsSet == c_classObject.m_entityIsSet) {
    if (this->getEntity() != c_classObject.getEntity()) {
      return false;
    }
  } else {
    return false;
  }
  if (this->m_featureIsSet == c_classObject.m_featureIsSet) {
    if (this->getFeature() != c_classObject.getFeature()) {
      return false;
    }
  } else {
    return false;
  }
  return true;
}

void FeatureAddress::setDevice(const xs_string &device) {

  m_device = device;
  m_deviceIsSet = !device.empty();
}

const xs_string &FeatureAddress::getDevice() const { return m_device; }

void FeatureAddress::cleanDevice() {
  m_device = "";
  m_deviceIsSet = false;
}

bool FeatureAddress::getDeviceIsSet() const { return m_deviceIsSet; }

void FeatureAddress::setEntity(const std::vector<xs_unsignedInt> &entity) {
  m_entity = entity;
  m_entityIsSet = true;
}

const std::vector<xs_unsignedInt> &FeatureAddress::getEntity() const {
  return m_entity;
}

void FeatureAddress::cleanEntity() {
  m_entity.clear();
  m_entityIsSet = false;
}

bool FeatureAddress::getEntityIsSet() const { return m_entityIsSet; }

void FeatureAddress::setFeature(const xs_unsignedInt &feature) {

  m_feature = feature;
  m_featureIsSet = true;
}

const xs_unsignedInt &FeatureAddress::getFeature() const { return m_feature; }

void FeatureAddress::cleanFeature() {
  m_feature = 0;
  m_featureIsSet = false;
}

bool FeatureAddress::getFeatureIsSet() const { return m_featureIsSet; }

FeatureAddress
FeatureAddress::reduce(const FeatureAddressElements &elements) const {
  FeatureAddress dataOut;
  if (getDeviceIsSet() && elements.getDeviceIsSet()) {
    dataOut.setDevice(getDevice());
  }
  if (getEntityIsSet() && elements.getEntityIsSet()) {
    dataOut.setEntity(getEntity());
  }
  if (getFeatureIsSet() && elements.getFeatureIsSet()) {
    dataOut.setFeature(getFeature());
  }
  return dataOut;
}

std::string FeatureAddress::toString() const {
  if (isEmpty()) {
    return std::string("");
  }
  std::string result = m_device + "/";
  std::vector<xs_unsignedInt>::const_iterator iter = m_entity.begin();
  std::vector<xs_unsignedInt>::const_iterator iterEnd = m_entity.end();
  for (; iter != iterEnd; ++iter) {
    result += KeoStringUtil::unumber(*iter) + "/";
  }
  return result + KeoStringUtil::unumber(m_feature);
}

bool FeatureAddress::fromString(const std::string &c_addressString) {
  std::size_t found = c_addressString.find("/");
  if (found != std::string::npos) {
    setDevice(c_addressString.substr(0, found));
    found++;
    std::size_t start = found;
    std::vector<xs_unsignedInt> entityList;
    do {
      found = c_addressString.find("/", start);
      if (found != std::string::npos) {
        try {
          entityList.push_back(KeoStringUtil::toUint16(
              c_addressString.substr(start, found - start).c_str()));
          found++;
          start = found;
        } catch (std::invalid_argument &e) {
          cleanDevice();
          cleanEntity();
          cleanFeature();
          return false;
        }
      }
    } while (found != std::string::npos);
    setEntity(entityList);
    try {
      setFeature(
          KeoStringUtil::toUint16(c_addressString.substr(start).c_str()));
    } catch (std::invalid_argument &e) {
      cleanDevice();
      cleanEntity();
      cleanFeature();
      return false;
    }
    return true;
  }
  return false;
}

bool FeatureAddress::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"device", "entity", "feature"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "device", &m_device)) {
      m_deviceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<xs_unsignedInt>(
            static_cast<KeoJsonValue *>(&(*iter)), "entity", &m_entity)) {
      m_entityIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "feature", &m_feature)) {
      m_featureIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string FeatureAddress::toJson() const {
  std::string result = "[";
  if (m_deviceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("device", m_device);
  }
  if (m_entityIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<xs_unsignedInt>("entity", m_entity);
  }
  if (m_featureIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("feature", m_feature);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram