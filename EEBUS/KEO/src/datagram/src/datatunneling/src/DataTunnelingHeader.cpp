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

#include <keo_datagram/datatunneling/DataTunnelingHeader.h>

#include <keo_datagram/datatunneling/DataTunnelingHeaderElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DataTunnelingHeader::DataTunnelingHeader()
    : m_purposeIdIsSet(false), m_purposeId(""), m_channelIdIsSet(false),
      m_channelId(0), m_sequenceIdIsSet(false), m_sequenceId(0)

{}

DataTunnelingHeader::DataTunnelingHeader(const xs_string &c_purposeId,
                                         const xs_unsignedInt &c_channelId,
                                         const xs_unsignedInt &c_sequenceId)
    : m_purposeIdIsSet(true), m_purposeId(c_purposeId), m_channelIdIsSet(true),
      m_channelId(c_channelId), m_sequenceIdIsSet(true),
      m_sequenceId(c_sequenceId)

{}

bool DataTunnelingHeader::
operator==(const DataTunnelingHeader &c_classObject) const {
  if (m_purposeIdIsSet != c_classObject.m_purposeIdIsSet ||
      (m_purposeIdIsSet && (m_purposeId != c_classObject.m_purposeId))) {
    return false;
  }
  if (m_channelIdIsSet != c_classObject.m_channelIdIsSet ||
      (m_channelIdIsSet && (m_channelId != c_classObject.m_channelId))) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool DataTunnelingHeader::
operator!=(const DataTunnelingHeader &c_classObject) const {
  return !(*this == c_classObject);
}

bool DataTunnelingHeader::isEmpty() const {
  return !m_purposeIdIsSet && !m_channelIdIsSet && !m_sequenceIdIsSet;
}

void DataTunnelingHeader::setPurposeId(const xs_string &purposeId) {
  m_purposeId = purposeId;
  m_purposeIdIsSet = true;
}

const xs_string &DataTunnelingHeader::getPurposeId() const {
  return m_purposeId;
}

void DataTunnelingHeader::cleanPurposeId() {
  m_purposeId = "";
  m_purposeIdIsSet = false;
}

bool DataTunnelingHeader::getPurposeIdIsSet() const { return m_purposeIdIsSet; }

void DataTunnelingHeader::setChannelId(const xs_unsignedInt &channelId) {
  m_channelId = channelId;
  m_channelIdIsSet = true;
}

const xs_unsignedInt &DataTunnelingHeader::getChannelId() const {
  return m_channelId;
}

void DataTunnelingHeader::cleanChannelId() {
  m_channelId = 0;
  m_channelIdIsSet = false;
}

bool DataTunnelingHeader::getChannelIdIsSet() const { return m_channelIdIsSet; }

void DataTunnelingHeader::setSequenceId(const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &DataTunnelingHeader::getSequenceId() const {
  return m_sequenceId;
}

void DataTunnelingHeader::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool DataTunnelingHeader::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

DataTunnelingHeader
DataTunnelingHeader::reduce(const DataTunnelingHeaderElements &elements) const {
  DataTunnelingHeader dataOut;
  if (getPurposeIdIsSet() && elements.getPurposeIdIsSet()) {
    dataOut.setPurposeId(getPurposeId());
  }
  if (getChannelIdIsSet() && elements.getChannelIdIsSet()) {
    dataOut.setChannelId(getChannelId());
  }
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  return dataOut;
}

bool DataTunnelingHeader::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"purposeId", "channelId", "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "purposeId", &m_purposeId)) {
      m_purposeIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "channelId", &m_channelId)) {
      m_channelIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DataTunnelingHeader::toJson() const {
  std::string result = "[";
  if (m_purposeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("purposeId", m_purposeId);
  }
  if (m_channelIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("channelId", m_channelId);
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram