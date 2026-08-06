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

#include <keo_datagram/datatunneling/DataTunnelingCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DataTunnelingCall::DataTunnelingCall()
    : CmdData(), m_headerIsSet(false), m_header(DataTunnelingHeader()),
      m_payloadIsSet(false), m_payload(xs_hexBinary())

{}

DataTunnelingCall::DataTunnelingCall(const DataTunnelingHeader &c_header,
                                     const xs_hexBinary &c_payload)
    : CmdData(), m_headerIsSet(true), m_header(c_header), m_payloadIsSet(true),
      m_payload(c_payload)

{}

bool DataTunnelingCall::
operator==(const DataTunnelingCall &c_classObject) const {
  if (m_headerIsSet != c_classObject.m_headerIsSet ||
      (m_headerIsSet && (m_header != c_classObject.m_header))) {
    return false;
  }
  if (m_payloadIsSet != c_classObject.m_payloadIsSet ||
      (m_payloadIsSet && (m_payload != c_classObject.m_payload))) {
    return false;
  }

  return true;
}

bool DataTunnelingCall::
operator!=(const DataTunnelingCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool DataTunnelingCall::isEmpty() const {
  return !m_headerIsSet && !m_payloadIsSet;
}

CmdData::Type DataTunnelingCall::getDataType() const {
  return CmdData::Type::DATA_TUNNELING_CALL_TYPE;
}

CmdDataPtr DataTunnelingCall::clone() const {
  return std::make_shared<DataTunnelingCall>(*this);
}

void DataTunnelingCall::setHeader(const DataTunnelingHeader &header) {
  m_header = header;
  m_headerIsSet = true;
}

const DataTunnelingHeader &DataTunnelingCall::getHeader() const {
  return m_header;
}

void DataTunnelingCall::cleanHeader() {
  m_header = DataTunnelingHeader();
  m_headerIsSet = false;
}

bool DataTunnelingCall::getHeaderIsSet() const { return m_headerIsSet; }

void DataTunnelingCall::setPayload(const xs_hexBinary &payload) {
  m_payload = payload;
  m_payloadIsSet = true;
}

const xs_hexBinary &DataTunnelingCall::getPayload() const { return m_payload; }

void DataTunnelingCall::cleanPayload() {
  m_payload = xs_hexBinary();
  m_payloadIsSet = false;
}

bool DataTunnelingCall::getPayloadIsSet() const { return m_payloadIsSet; }

CmdDataPtr DataTunnelingCall::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<DataTunnelingCall>(*this);
}

bool DataTunnelingCall::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "payload", &m_payload)) {
      m_payloadIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DataTunnelingCall::toJson() const {
  std::string result = "[";
  if (m_headerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("header", m_header);
  }
  if (m_payloadIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("payload", m_payload);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram