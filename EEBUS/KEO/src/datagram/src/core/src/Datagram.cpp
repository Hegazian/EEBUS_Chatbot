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

#include <keo_datagram/core/Datagram.h>

#include <CreateSpineDataClass.h>
#include <keo_datagram/core/ResultData.h>
#include <keo_spine_datagramVersion.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

Datagram::Datagram()
    : m_headerIsSet(false), m_header(Header()), m_payloadIsSet(false),
      m_payload(Payload())

{

  m_header.setCmdClassifier(CmdClassifier::Value::UNDEFINED__);
  m_headerIsSet = true;
}

Datagram::Datagram(const CmdClassifier c_classifier) : Datagram() {
  m_header.setCmdClassifier(c_classifier);
  m_headerIsSet = true;
}

Datagram::Datagram(const Header &c_header, const Payload &c_payload)
    : Datagram() {
  setHeader(c_header);
  setPayload(c_payload);
}

Datagram::Datagram(const Header &c_header, const Cmd &c_cmd) : Datagram() {
  setHeader(c_header);
  std::vector<Cmd> cmds = {c_cmd};
  m_payload.setCmd(cmds);
  m_payloadIsSet = true;
}

Datagram::Datagram(const Header &c_header, const std::vector<Cmd> &c_cmds)
    : Datagram() {
  setHeader(c_header);
  m_payload.setCmd(c_cmds);
  m_payloadIsSet = true;
}

Datagram::Datagram(const HeaderPtr &c_pHeader, const CmdPtr &c_pCmd)
    : Datagram(*(c_pHeader.get()), *(c_pCmd.get())) {}

Datagram::Datagram(const HeaderPtr &c_pHeader,
                   const std::vector<CmdPtr> &c_pCmds)
    : Datagram() {
  setHeader(*c_pHeader.get());
  std::vector<Cmd> cmds;
  for (const auto &cmd : c_pCmds) {
    cmds.push_back(*cmd.get());
  }
  m_payloadIsSet = true;
  m_payload.setCmd(cmds);
}

Datagram::Datagram(const Datagram &c_classObject)
    : m_headerIsSet(c_classObject.m_headerIsSet),
      m_header(c_classObject.m_header),
      m_payloadIsSet(c_classObject.m_payloadIsSet),
      m_payload(c_classObject.m_payload) {
  if (c_classObject.m_payloadUnparsed) {
    m_payloadUnparsed = std::make_shared<KeoJsonValue>(
        *(c_classObject.m_payloadUnparsed.get())); // copies pointee
  }
}

Datagram::Datagram(Datagram &&c_classObject)
    : m_headerIsSet(c_classObject.m_headerIsSet),
      m_header(c_classObject.m_header),
      m_payloadIsSet(c_classObject.m_payloadIsSet),
      m_payload(c_classObject.m_payload),
      m_payloadUnparsed(c_classObject.m_payloadUnparsed) // steals pointee
{}

bool Datagram::operator==(const Datagram &c_classObject) const {
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

bool Datagram::operator!=(const Datagram &c_classObject) const {
  return !(*this == c_classObject);
}

bool Datagram::isEmpty() const { return !m_headerIsSet && !m_payloadIsSet; }

Datagram &Datagram::operator=(const Datagram &c_classObject) {
  if (this != &c_classObject) {
    m_headerIsSet = c_classObject.m_headerIsSet;
    m_header = c_classObject.m_header;
    m_payloadIsSet = c_classObject.m_payloadIsSet;
    m_payload = c_classObject.m_payload;
    if (c_classObject.m_payloadUnparsed) {
      m_payloadUnparsed = std::make_shared<KeoJsonValue>(
          *(c_classObject.m_payloadUnparsed.get())); // copies pointee
    }
  }
  return *this;
}

Datagram &Datagram::operator=(Datagram &&c_classObject) {
  if (this != &c_classObject) {
    m_headerIsSet = c_classObject.m_headerIsSet;
    m_header = c_classObject.m_header;
    m_payloadIsSet = c_classObject.m_payloadIsSet;
    m_payload = c_classObject.m_payload;
    m_payloadUnparsed = c_classObject.m_payloadUnparsed; // steals pointee
  }
  return *this;
}

bool Datagram::requiresResponse() const {
  // A READ datagram always requires a response. All remaining messages except
  // RESULTS
  // datagrams require responses (c.f.  EEBus SPINE TS - Protocol Specification
  // Section 5.2.4)
  // iff ackRequest==true.
  if (isResult()) {
    return false;
  } else if (isRead() ||
             (m_header.getAckRequestIsSet() && m_header.getAckRequest())) {
    return true;
  } else {
    return false;
  }
}

bool Datagram::isCall() const { return m_header.isCall(); }

bool Datagram::isNotify() const { return m_header.isNotify(); }

bool Datagram::isRead() const { return m_header.isRead(); }

bool Datagram::isReply() const { return m_header.isReply(); }

bool Datagram::isResult() const { return m_header.isResult(); }

bool Datagram::isWrite() const { return m_header.isWrite(); }

bool Datagram::isHeaderValid() const { return m_header.areAddressesSet(); }

void Datagram::setHeader(const Header &header) {
  m_header = header;
  m_headerIsSet = true;
}

const Header &Datagram::getHeader() const { return m_header; }

void Datagram::cleanHeader() {
  m_header = Header();
  m_headerIsSet = false;
}

bool Datagram::getHeaderIsSet() const { return m_headerIsSet; }

void Datagram::setPayload(const Payload &payload) {
  m_payload = payload;
  m_payloadIsSet = true;
}

const Payload &Datagram::getPayload() const { return m_payload; }

void Datagram::cleanPayload() {
  m_payload = Payload();
  m_payloadIsSet = false;
}

bool Datagram::getPayloadIsSet() const { return m_payloadIsSet; }

Header &Datagram::getHeader() { return m_header; }

void Datagram::setHeader(HeaderPtr pHeader) { m_header = *pHeader.get(); }

void Datagram::setCmd(CmdPtr pCmd) {
  std::vector<Cmd> cmds = {(*pCmd.get())};
  m_payload.setCmd(cmds);
}

void Datagram::setCmd(const Cmd &cmd) {
  std::vector<Cmd> cmds = {cmd};
  m_payload.setCmd(cmds);
}

const Cmd &Datagram::getCmd() const {
  if (isPayloadParsed() && m_payload.hasSingleCmd()) {
    return m_payload.getCmd()[0];
  } else {
    return Datagram::NO_CMD;
  }
}

CmdDataPtr Datagram::getCmdData() const {
  if (isPayloadParsed() && m_payload.hasSingleCmd()) {
    return m_payload.getCmd()[0].getCmdData();
  } else {
    return CmdDataPtr();
  }
}

CmdData::Type Datagram::getCmdDataType() const {
  if (isPayloadParsed() && m_payload.hasSingleCmd()) {
    return m_payload.getCmd()[0].getDataType();
  } else {
    return CmdData::Type::UNDEFINED;
  }
}

CmdClassifier Datagram::getCmdClassifier() const {
  return m_header.getCmdClassifier().getValue();
}

CmdClassifier Datagram::getClassifier() const { return getCmdClassifier(); }

xs_unsignedLong Datagram::getMsgCounter() const {
  return m_header.getMsgCounter();
}

xs_unsignedLong Datagram::getMsgCounterReference() const {
  return m_header.getMsgCounterReference();
}

const FeatureAddress &Datagram::getSourceAddress() const {
  return m_header.getAddressSource();
}

void Datagram::setSourceAddress(const FeatureAddress &c_address) {
  m_header.setAddressSource(c_address);
}

const FeatureAddress &Datagram::getDestinationAddress() const {
  return m_header.getAddressDestination();
}

void Datagram::setDestinationAddress(const FeatureAddress &c_address) {
  m_header.setAddressDestination(c_address);
}

void Datagram::setCmdClassifier(CmdClassifier::Value c_classifier) {
  m_header.setCmdClassifier(c_classifier);
}

Cmd Datagram::NO_CMD = Cmd();

void Datagram::changeToReply(CmdClassifier c_classifier) {
  changeToResponse(c_classifier);
}

void Datagram::changeToResponse(CmdClassifier c_classifier) {
  m_header.changeToResponse(c_classifier);
}

Datagram Datagram::createReply(const CmdDataPtr &c_data) const {
  if (isRead() && !isResult() && isHeaderValid()) {
    CmdDataPtr pData =
        c_data ? c_data : CreateSpineDataClass::createCmdData(getCmdDataType());
    if (pData) {
      Cmd cmd(pData);
      Header headerReply(getHeader());
      headerReply.changeToResponse(CmdClassifier::Value::REPLY);
      headerReply.setSpecificationVersion(SPINE_VERSION_STRING);
      return Datagram(headerReply, cmd);
    }
  }
  return Datagram();
}

Datagram Datagram::createResult(const xs_unsignedInt c_errorNumber,
                                const std::string &c_description) const {
  if (isHeaderValid() && !isResult() && !isReply()) {
    Header headerReply(getHeader());
    headerReply.changeToResponse(CmdClassifier::Value::RESULT);
    headerReply.setSpecificationVersion(SPINE_VERSION_STRING);

    ResultDataPtr pData = std::make_shared<ResultData>();
    pData->setErrorNumber(c_errorNumber);
    if (!c_description.empty()) {
      pData->setDescription(c_description);
    }
    Cmd cmd(pData);
    return Datagram(headerReply, cmd);
  }
  return Datagram();
}

bool Datagram::isPayloadValid() const {
  if (!isPayloadParsed()) {
    return false;
  }
  if (!m_header.isRead()) {
    return !m_payload.isEmpty();
  }
  return true;
}

bool Datagram::isPayloadParsed() const {
  return !m_payload.isEmpty() && !m_payload.getCmd().empty();
}

bool Datagram::parsePayload() {
  if (isPayloadParsed()) {
    return true;
  } else {
    try {
      parsePayloadThrows();
      return true;
    } catch (const DatagramParserException &e) {
      return false;
    }
  }
}

void Datagram::parsePayloadThrows() {
  if (!isPayloadParsed()) {
    try {
      if (m_payloadUnparsed && !m_payloadUnparsed->isNull() &&
          static_cast<KeoJsonTransformable *>(&m_payload)
              ->fromJson(m_payloadUnparsed.get())) {
        if (!m_payloadUnparsed->empty()) {
          m_payloadUnparsed->clear();
        }
      }

      if (m_payload.getCmd().empty()) {
        throw DatagramParserException("Could not parse cmd");
      }
    } catch (DatagramParserException &e) {
      e.append("Could not parse payload");
      throw;
    }
  }
}

Datagram Datagram::fromJson(const std::string &jsonString) {
  try {
    return fromJsonThrows(jsonString);
  } catch (const DatagramParserException &e) {
    return Datagram();
  }
}

Datagram Datagram::fromJsonThrows(const std::string &jsonString) {
  Json::CharReaderBuilder builder;
  Json::Value root;
  std::string parserErrors;

  std::istringstream ss(jsonString);
  bool result = Json::parseFromStream(builder, ss, &root, &parserErrors);

  if (result && !root.isNull()) {
    Json::Value datagram = root["datagram"];
    if (datagram.isArray()) {
      Json::Value headerJson = datagram[0]["header"];
      Header header;
      try {
        if (headerJson.isArray() &&
            static_cast<KeoJsonTransformable *>(&header)->fromJson(
                static_cast<KeoJsonValue *>(&headerJson))) {
          Json::Value payloadJson = datagram[1]["payload"];
          if (payloadJson.isArray()) {
            Datagram datagram(header, Payload());
            datagram.m_payloadUnparsed =
                std::make_shared<KeoJsonValue>(payloadJson);
            return datagram;
          } else {
            throw DatagramParserException(
                "Could not parse payload (excepted array)");
          }
        } else {
          throw DatagramParserException("Could not parse payload");
        }
      } catch (DatagramParserException &e) {
        e.append("Could not parse datagram");
        throw;
      }
    } else {
      throw DatagramParserException(
          "Could not parse datagram (excepted array)");
    }
  } else {
    throw DatagramParserException("Could not parse datagram\nCaused by: " +
                                  parserErrors);
  }
}

bool Datagram::fromJson(KeoJsonValue *json) {
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

std::string Datagram::toJson() const {
  std::string result = "{\"datagram\":[";
  if (!m_header.isEmpty()) {
    result += "{\"header\":";
    result += static_cast<const KeoJsonTransformable *>(&m_header)->toJson();
    result += "}";
  }
  if (!m_payload.isEmpty()) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += "{\"payload\":";
    result += static_cast<const KeoJsonTransformable *>(&m_payload)->toJson();
    result += "}";
  } else {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    result += "{\"payload\":";
    result += Json::writeString(builder, *(m_payloadUnparsed.get()));
    result += "}";
  }
  result += "]}";
  return result;
}

} // namespace keo_datagram