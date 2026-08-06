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

#include <keo_datagram/datatunneling/DataTunnelingHeaderElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DataTunnelingHeaderElements::DataTunnelingHeaderElements()
    : m_purposeIdIsSet(false), m_channelIdIsSet(false), m_sequenceIdIsSet(false)

{}

DataTunnelingHeaderElements::DataTunnelingHeaderElements(
    xs_boolean c_purposeIdIsSet, xs_boolean c_channelIdIsSet,
    xs_boolean c_sequenceIdIsSet)
    : m_purposeIdIsSet(c_purposeIdIsSet), m_channelIdIsSet(c_channelIdIsSet),
      m_sequenceIdIsSet(c_sequenceIdIsSet)

{}

bool DataTunnelingHeaderElements::
operator==(const DataTunnelingHeaderElements &c_classObject) const {
  if (m_purposeIdIsSet != c_classObject.m_purposeIdIsSet) {
    return false;
  }
  if (m_channelIdIsSet != c_classObject.m_channelIdIsSet) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }

  return true;
}

bool DataTunnelingHeaderElements::
operator!=(const DataTunnelingHeaderElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DataTunnelingHeaderElements::isEmpty() const {
  return !m_purposeIdIsSet && !m_channelIdIsSet && !m_sequenceIdIsSet;
}

void DataTunnelingHeaderElements::setPurposeId() { m_purposeIdIsSet = true; }

void DataTunnelingHeaderElements::cleanPurposeId() { m_purposeIdIsSet = false; }

bool DataTunnelingHeaderElements::getPurposeIdIsSet() const {
  return m_purposeIdIsSet;
}

void DataTunnelingHeaderElements::setChannelId() { m_channelIdIsSet = true; }

void DataTunnelingHeaderElements::cleanChannelId() { m_channelIdIsSet = false; }

bool DataTunnelingHeaderElements::getChannelIdIsSet() const {
  return m_channelIdIsSet;
}

void DataTunnelingHeaderElements::setSequenceId() { m_sequenceIdIsSet = true; }

void DataTunnelingHeaderElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool DataTunnelingHeaderElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

bool DataTunnelingHeaderElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"purposeId", "channelId", "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "purposeId")) {
      m_purposeIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "channelId")) {
      m_channelIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DataTunnelingHeaderElements::toJson() const {
  std::string result = "[";
  if (m_purposeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("purposeId");
  }
  if (m_channelIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("channelId");
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram