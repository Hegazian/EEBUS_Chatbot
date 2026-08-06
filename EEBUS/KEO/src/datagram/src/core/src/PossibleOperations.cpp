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

#include <keo_datagram/core/PossibleOperations.h>

#include <keo_datagram/core/PossibleOperationsElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PossibleOperations::PossibleOperations()
    : m_readIsSet(false), m_read(PossibleOperationsRead()), m_writeIsSet(false),
      m_write(PossibleOperationsWrite())

{}

PossibleOperations::PossibleOperations(const PossibleOperationsRead &c_read,
                                       const PossibleOperationsWrite &c_write)
    : m_readIsSet(true), m_read(c_read), m_writeIsSet(true), m_write(c_write)

{}

bool PossibleOperations::
operator==(const PossibleOperations &c_classObject) const {
  if (m_readIsSet != c_classObject.m_readIsSet ||
      (m_readIsSet && (m_read != c_classObject.m_read))) {
    return false;
  }
  if (m_writeIsSet != c_classObject.m_writeIsSet ||
      (m_writeIsSet && (m_write != c_classObject.m_write))) {
    return false;
  }

  return true;
}

bool PossibleOperations::
operator!=(const PossibleOperations &c_classObject) const {
  return !(*this == c_classObject);
}

bool PossibleOperations::isEmpty() const {
  return !m_readIsSet && !m_writeIsSet;
}

void PossibleOperations::setRead(const PossibleOperationsRead &read) {
  m_read = read;
  m_readIsSet = true;
}

const PossibleOperationsRead &PossibleOperations::getRead() const {
  return m_read;
}

void PossibleOperations::cleanRead() {
  m_read = PossibleOperationsRead();
  m_readIsSet = false;
}

bool PossibleOperations::getReadIsSet() const { return m_readIsSet; }

void PossibleOperations::setWrite(const PossibleOperationsWrite &write) {
  m_write = write;
  m_writeIsSet = true;
}

const PossibleOperationsWrite &PossibleOperations::getWrite() const {
  return m_write;
}

void PossibleOperations::cleanWrite() {
  m_write = PossibleOperationsWrite();
  m_writeIsSet = false;
}

bool PossibleOperations::getWriteIsSet() const { return m_writeIsSet; }

PossibleOperations
PossibleOperations::reduce(const PossibleOperationsElements &elements) const {
  PossibleOperations dataOut;
  if (getReadIsSet() && elements.getReadIsSet()) {
    dataOut.setRead(getRead());
  }
  if (getWriteIsSet() && elements.getWriteIsSet()) {
    dataOut.setWrite(getWrite());
  }
  return dataOut;
}

bool PossibleOperations::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"read", "write"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "read", &m_read)) {
      m_readIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "write", &m_write)) {
      m_writeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PossibleOperations::toJson() const {
  std::string result = "[";
  if (m_readIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("read", m_read);
  }
  if (m_writeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("write", m_write);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram