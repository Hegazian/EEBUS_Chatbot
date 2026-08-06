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

#include <iostream>
#include <keo_datagram/core/KeoByteArray.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

namespace keo_datagram {

KeoByteArray::KeoByteArray(const std::string &s) {
  m_data.assign(s.begin(), s.end());
}

KeoByteArray::KeoByteArray(const char *s) { setContent(s, strlen(s)); }

KeoByteArray::KeoByteArray(const std::vector<char> &s) {
  m_data.assign(s.begin(), s.end());
}

KeoByteArray::KeoByteArray(const std::vector<unsigned char> &s) {
  m_data.assign(s.begin(), s.end());
}

KeoByteArray::KeoByteArray(const char *content, size_t sz) {
  setContent(content, sz);
}

void KeoByteArray::setContent(const char *s, size_t sz) {
  if (s) {
    m_data.assign(s, s + sz);
  }
}

bool KeoByteArray::isHexChar(char c) {
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
         (c >= 'A' && c <= 'F');
}

KeoByteArray KeoByteArray::fromHex(const char *hexString) {
  if (hexString == NULL) {
    return KeoByteArray();
  }

  size_t len = strlen(hexString);

  if (len < 2) {
    return KeoByteArray();
  }

  if ((len % 1) == 1) {
    return KeoByteArray(); // must be even count of characters (2 hex chars per
                           // byte)
  }

  KeoByteArray returnHex;
  returnHex.fill(len / 2, '\0');
  unsigned int parsedChar;
  char buf[3] = {'\0', '\0', '\0'};
  bool fail = false;

  size_t j = 0;
  for (size_t i = 0; i < len && !fail; i++) {
    buf[0] = hexString[i];
    buf[1] = hexString[++i];
    fail = !KeoByteArray::isHexChar(buf[0]) || !KeoByteArray::isHexChar(buf[1]);
    if (!fail) {
      if (sscanf(buf, "%02x", &parsedChar) > 0) {
        returnHex.m_data[j++] = static_cast<char>(parsedChar);
      }
    }
  }
  if (fail) {
    returnHex.m_data.clear();
    return returnHex;
  } else {
    return returnHex;
  }
}

void KeoByteArray::fill(size_t size, char fillChar) {
  m_data.assign(size, fillChar);
}

KeoByteArray::KeoByteArray(size_t size, char fillChar) { fill(size, fillChar); }

void KeoByteArray::set(size_t index, char c) {
  if (index < m_data.size()) {
    m_data[index] = c;
  }
}

bool KeoByteArray::equals(const KeoByteArray &other) const {
  return (m_data == other.m_data);
}

size_t KeoByteArray::length() const { return m_data.size(); }

std::string KeoByteArray::toHex() const {
  std::string retVal;
  retVal.reserve(m_data.size() * 2);
  char buf[3];
  for (size_t i = 0; i < m_data.size(); i++) {
    sprintf(buf, "%02x", static_cast<uint8_t>(m_data.at(i)));
    retVal.append(buf);
  }
  return retVal;
}

std::string KeoByteArray::toString() const {
  std::string str(m_data.begin(), m_data.end());
  return str;
}

std::vector<char> KeoByteArray::toVector() const { return m_data; }

std::vector<unsigned char> KeoByteArray::toVectorUnsigned() const {
  return std::vector<unsigned char>(m_data.begin(), m_data.end());
}

KeoByteArray &KeoByteArray::operator=(const KeoByteArray &other) {
  if (this == &other)
    return *this;
  m_data = other.m_data;
  return *this;
}

KeoByteArray::KeoByteArray() {}

KeoByteArray KeoByteArray::fromHex(const std::string &hexString) {
  return KeoByteArray::fromHex(hexString.c_str());
}

const char *KeoByteArray::constData() const {
  if (m_data.size()) {
    return reinterpret_cast<const char *>(&m_data[0]);
  }
  return NULL;
}

void KeoByteArray::clear() { m_data.clear(); }
}