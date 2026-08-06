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

#include <keo_datagram/core/EntityAddress.h>

#include <keo_datagram/core/EntityAddressElements.h>

#include "KeoStringUtil.h"

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

EntityAddress::EntityAddress()
    : m_deviceIsSet(false), m_device(""), m_entityIsSet(false),
      m_entity(std::vector<xs_unsignedInt>())

{}

EntityAddress::EntityAddress(const EntityAddress &c_classObject)
    : EntityAddress() {
  m_deviceIsSet = c_classObject.m_deviceIsSet;
  m_device = c_classObject.m_device;
  m_entityIsSet = c_classObject.m_entityIsSet;
  m_entity = c_classObject.m_entity;
}

EntityAddress::EntityAddress(const std::string &c_device,
                             const std::vector<std::uint32_t> &c_entity)
    : EntityAddress() {
  setDevice(c_device);
  setEntity(c_entity);
}

EntityAddress::EntityAddress(const xs_string &c_device,
                             const xs_unsignedInt &c_entity)
    : EntityAddress() {
  setDevice(c_device);
  m_entity.push_back(c_entity);
  m_entityIsSet = true;
}

EntityAddress::EntityAddress(const std::vector<xs_unsignedInt> &c_entity)
    : EntityAddress() {
  setEntity(c_entity);
}

EntityAddress::EntityAddress(const xs_unsignedInt &c_entity) : EntityAddress() {
  m_entity.push_back(c_entity);
  m_entityIsSet = true;
}

bool EntityAddress::operator==(const EntityAddress &c_classObject) const {
  if (m_deviceIsSet != c_classObject.m_deviceIsSet ||
      (m_deviceIsSet && (m_device != c_classObject.m_device))) {
    return false;
  }
  if (m_entityIsSet != c_classObject.m_entityIsSet ||
      (m_entityIsSet && (m_entity != c_classObject.m_entity))) {
    return false;
  }

  return true;
}

bool EntityAddress::operator!=(const EntityAddress &c_classObject) const {
  return !(*this == c_classObject);
}

bool EntityAddress::isEmpty() const { return !m_deviceIsSet && !m_entityIsSet; }

bool EntityAddress::operator>(const EntityAddress &c_classObject) const {
  if ((this->m_deviceIsSet == c_classObject.m_deviceIsSet)) {
    int lexValue = this->getDevice().compare(c_classObject.getDevice());
    if (lexValue != 0) {
      return lexValue > 0;
    }
  }
  if ((this->m_entityIsSet == c_classObject.m_entityIsSet)) {
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
  return false;
}

bool EntityAddress::operator<(const EntityAddress &c_classObject) const {
  return !(*this > c_classObject) && !(*this == c_classObject);
}

void EntityAddress::setDevice(const xs_string &device) {

  m_device = device;
  m_deviceIsSet = !device.empty();
}

const xs_string &EntityAddress::getDevice() const { return m_device; }

void EntityAddress::cleanDevice() {
  m_device = "";
  m_deviceIsSet = false;
}

bool EntityAddress::getDeviceIsSet() const { return m_deviceIsSet; }

void EntityAddress::setEntity(const std::vector<xs_unsignedInt> &entity) {
  m_entity = entity;
  m_entityIsSet = true;
}

const std::vector<xs_unsignedInt> &EntityAddress::getEntity() const {
  return m_entity;
}

void EntityAddress::cleanEntity() {
  m_entity.clear();
  m_entityIsSet = false;
}

bool EntityAddress::getEntityIsSet() const { return m_entityIsSet; }

EntityAddress
EntityAddress::reduce(const EntityAddressElements &elements) const {
  EntityAddress dataOut;
  if (getDeviceIsSet() && elements.getDeviceIsSet()) {
    dataOut.setDevice(getDevice());
  }
  if (getEntityIsSet() && elements.getEntityIsSet()) {
    dataOut.setEntity(getEntity());
  }
  return dataOut;
}

std::string EntityAddress::toString() const {
  if (isEmpty()) {
    return std::string("");
  }
  std::string result = m_device;
  std::vector<xs_unsignedInt>::const_iterator iter = m_entity.begin();
  std::vector<xs_unsignedInt>::const_iterator iterEnd = m_entity.end();
  for (; iter != iterEnd; ++iter) {
    result += "/" + KeoStringUtil::unumber(*iter);
  }
  return result += "/";
}

bool EntityAddress::fromString(const std::string &c_addressString) {
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
          return false;
        }
      }
    } while (found != std::string::npos);
    setEntity(entityList);
    return true;
  }
  return false;
}

bool EntityAddress::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"device", "entity"})) {
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
  }
  return true;
}

std::string EntityAddress::toJson() const {
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
  result += "]";
  return result;
}

} // namespace keo_datagram