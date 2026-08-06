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

#include <keo_datagram/datatunneling/DataTunnelingCallElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DataTunnelingCallElements::DataTunnelingCallElements()
    : DataElements(), m_headerIsSet(false),
      m_header(DataTunnelingHeaderElements()), m_payloadIsSet(false)

{}

DataTunnelingCallElements::DataTunnelingCallElements(
    const DataTunnelingHeaderElements &c_header, xs_boolean c_payloadIsSet)
    : DataElements(), m_headerIsSet(true), m_header(c_header),
      m_payloadIsSet(c_payloadIsSet)

{}

bool DataTunnelingCallElements::
operator==(const DataTunnelingCallElements &c_classObject) const {
  if (m_headerIsSet != c_classObject.m_headerIsSet ||
      (m_headerIsSet && (m_header != c_classObject.m_header))) {
    return false;
  }
  if (m_payloadIsSet != c_classObject.m_payloadIsSet) {
    return false;
  }

  return true;
}

bool DataTunnelingCallElements::
operator!=(const DataTunnelingCallElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DataTunnelingCallElements::isEmpty() const {
  return !m_headerIsSet && !m_payloadIsSet;
}

DataElements::Type DataTunnelingCallElements::getDataType() const {
  return DataElements::Type::DATA_TUNNELING_CALL_ELEMENTS_TYPE;
}

DataElementsPtr DataTunnelingCallElements::clone() const {
  return std::make_shared<DataTunnelingCallElements>(*this);
}

void DataTunnelingCallElements::setHeader(
    const DataTunnelingHeaderElements &header) {
  m_header = header;
  m_headerIsSet = true;
}

const DataTunnelingHeaderElements &
DataTunnelingCallElements::getHeader() const {
  return m_header;
}

void DataTunnelingCallElements::cleanHeader() {
  m_header = DataTunnelingHeaderElements();
  m_headerIsSet = false;
}

bool DataTunnelingCallElements::getHeaderIsSet() const { return m_headerIsSet; }

void DataTunnelingCallElements::setPayload() { m_payloadIsSet = true; }

void DataTunnelingCallElements::cleanPayload() { m_payloadIsSet = false; }

bool DataTunnelingCallElements::getPayloadIsSet() const {
  return m_payloadIsSet;
}

bool DataTunnelingCallElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"header", "payload"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "header", &m_header)) {
      m_headerIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "payload")) {
      m_payloadIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DataTunnelingCallElements::toJson() const {
  std::string result = "[";
  if (m_headerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("header", m_header);
  }
  if (m_payloadIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("payload");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram