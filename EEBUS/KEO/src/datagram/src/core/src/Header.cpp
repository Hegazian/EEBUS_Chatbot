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

#include <keo_datagram/core/Header.h>

#include <keo_datagram/core/DatagramParserException.h>
#include <keo_spine_datagramVersion.h>
#include <memory>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

Header::Header()
    : m_specificationVersionIsSet(false), m_specificationVersion(""),
      m_addressSourceIsSet(false), m_addressSource(FeatureAddress()),
      m_addressDestinationIsSet(false), m_addressDestination(FeatureAddress()),
      m_addressOriginatorIsSet(false), m_addressOriginator(FeatureAddress()),
      m_msgCounterIsSet(false), m_msgCounter(0),
      m_msgCounterReferenceIsSet(false), m_msgCounterReference(0),
      m_cmdClassifierIsSet(false), m_cmdClassifier(CmdClassifier()),
      m_ackRequestIsSet(false), m_ackRequest(false), m_timestampIsSet(false),
      m_timestamp(AbsoluteOrRelativeTime())

{

  m_specificationVersionIsSet = true;
  m_specificationVersion = SPINE_VERSION_STRING;
  setCmdClassifier(CmdClassifier::Value::UNDEFINED__);
  createNewMsgCounter();
}

Header::Header(const CmdClassifier::Value c_classifier) : Header() {
  m_cmdClassifier = c_classifier;
  m_cmdClassifierIsSet = true;
}

Header::Header(const FeatureAddress &c_addressSource,
               const FeatureAddress &c_addressDestination,
               const CmdClassifier::Value c_classifier)
    : Header() {
  m_cmdClassifier = c_classifier;
  m_cmdClassifierIsSet = true;
  m_addressSource = c_addressSource;
  m_addressSourceIsSet = true;
  m_addressDestination = c_addressDestination;
  m_addressDestinationIsSet = true;
}

bool Header::operator==(const Header &c_classObject) const {
  if (m_specificationVersionIsSet !=
          c_classObject.m_specificationVersionIsSet ||
      (m_specificationVersionIsSet &&
       (m_specificationVersion != c_classObject.m_specificationVersion))) {
    return false;
  }
  if (m_addressSourceIsSet != c_classObject.m_addressSourceIsSet ||
      (m_addressSourceIsSet &&
       (m_addressSource != c_classObject.m_addressSource))) {
    return false;
  }
  if (m_addressDestinationIsSet != c_classObject.m_addressDestinationIsSet ||
      (m_addressDestinationIsSet &&
       (m_addressDestination != c_classObject.m_addressDestination))) {
    return false;
  }
  if (m_addressOriginatorIsSet != c_classObject.m_addressOriginatorIsSet ||
      (m_addressOriginatorIsSet &&
       (m_addressOriginator != c_classObject.m_addressOriginator))) {
    return false;
  }
  if (m_msgCounterIsSet != c_classObject.m_msgCounterIsSet ||
      (m_msgCounterIsSet && (m_msgCounter != c_classObject.m_msgCounter))) {
    return false;
  }
  if (m_msgCounterReferenceIsSet != c_classObject.m_msgCounterReferenceIsSet ||
      (m_msgCounterReferenceIsSet &&
       (m_msgCounterReference != c_classObject.m_msgCounterReference))) {
    return false;
  }
  if (m_cmdClassifierIsSet != c_classObject.m_cmdClassifierIsSet ||
      (m_cmdClassifierIsSet &&
       (m_cmdClassifier != c_classObject.m_cmdClassifier))) {
    return false;
  }
  if (m_ackRequestIsSet != c_classObject.m_ackRequestIsSet ||
      (m_ackRequestIsSet && (m_ackRequest != c_classObject.m_ackRequest))) {
    return false;
  }
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }

  return true;
}

bool Header::operator!=(const Header &c_classObject) const {
  return !(*this == c_classObject);
}

bool Header::isEmpty() const {
  return !m_specificationVersionIsSet && !m_addressSourceIsSet &&
         !m_addressDestinationIsSet && !m_addressOriginatorIsSet &&
         !m_msgCounterIsSet && !m_msgCounterReferenceIsSet &&
         !m_cmdClassifierIsSet && !m_ackRequestIsSet && !m_timestampIsSet;
}

bool Header::isCall() const {
  return m_cmdClassifier == CmdClassifier::Value::CALL;
}

bool Header::isNotify() const {
  return m_cmdClassifier == CmdClassifier::Value::NOTIFY;
}

bool Header::isRead() const {
  return m_cmdClassifier == CmdClassifier::Value::READ;
}

bool Header::isReply() const {
  return m_cmdClassifier == CmdClassifier::Value::REPLY;
}

bool Header::isResult() const {
  return m_cmdClassifier == CmdClassifier::Value::RESULT;
}

bool Header::isWrite() const {
  return m_cmdClassifier == CmdClassifier::Value::WRITE;
}

void Header::setSpecificationVersion(const xs_string &specificationVersion) {
  m_specificationVersion = specificationVersion;
  m_specificationVersionIsSet = true;
}

const xs_string &Header::getSpecificationVersion() const {
  return m_specificationVersion;
}

void Header::cleanSpecificationVersion() {
  m_specificationVersion = "";
  m_specificationVersionIsSet = false;
}

bool Header::getSpecificationVersionIsSet() const {
  return m_specificationVersionIsSet;
}

void Header::setAddressSource(const FeatureAddress &addressSource) {
  m_addressSource = addressSource;
  m_addressSourceIsSet = true;
}

const FeatureAddress &Header::getAddressSource() const {
  return m_addressSource;
}

void Header::cleanAddressSource() {
  m_addressSource = FeatureAddress();
  m_addressSourceIsSet = false;
}

bool Header::getAddressSourceIsSet() const { return m_addressSourceIsSet; }

void Header::setAddressDestination(const FeatureAddress &addressDestination) {
  m_addressDestination = addressDestination;
  m_addressDestinationIsSet = true;
}

const FeatureAddress &Header::getAddressDestination() const {
  return m_addressDestination;
}

void Header::cleanAddressDestination() {
  m_addressDestination = FeatureAddress();
  m_addressDestinationIsSet = false;
}

bool Header::getAddressDestinationIsSet() const {
  return m_addressDestinationIsSet;
}

void Header::setAddressOriginator(const FeatureAddress &addressOriginator) {
  m_addressOriginator = addressOriginator;
  m_addressOriginatorIsSet = true;
}

const FeatureAddress &Header::getAddressOriginator() const {
  return m_addressOriginator;
}

void Header::cleanAddressOriginator() {
  m_addressOriginator = FeatureAddress();
  m_addressOriginatorIsSet = false;
}

bool Header::getAddressOriginatorIsSet() const {
  return m_addressOriginatorIsSet;
}

void Header::setMsgCounter(const xs_unsignedLong &msgCounter) {
  m_msgCounter = msgCounter;
  m_msgCounterIsSet = true;
}

const xs_unsignedLong &Header::getMsgCounter() const { return m_msgCounter; }

void Header::cleanMsgCounter() {
  m_msgCounter = 0;
  m_msgCounterIsSet = false;
}

bool Header::getMsgCounterIsSet() const { return m_msgCounterIsSet; }

void Header::setMsgCounterReference(
    const xs_unsignedLong &msgCounterReference) {
  m_msgCounterReference = msgCounterReference;
  m_msgCounterReferenceIsSet = true;
}

const xs_unsignedLong &Header::getMsgCounterReference() const {
  return m_msgCounterReference;
}

void Header::cleanMsgCounterReference() {
  m_msgCounterReference = 0;
  m_msgCounterReferenceIsSet = false;
}

bool Header::getMsgCounterReferenceIsSet() const {
  return m_msgCounterReferenceIsSet;
}

void Header::setCmdClassifier(const CmdClassifier &cmdClassifier) {
  m_cmdClassifier = cmdClassifier;
  m_cmdClassifierIsSet = true;
}

const CmdClassifier &Header::getCmdClassifier() const {
  return m_cmdClassifier;
}

void Header::cleanCmdClassifier() {
  m_cmdClassifier = CmdClassifier();
  m_cmdClassifierIsSet = false;
}

bool Header::getCmdClassifierIsSet() const { return m_cmdClassifierIsSet; }

void Header::setAckRequest(const xs_boolean &ackRequest) {
  m_ackRequest = ackRequest;
  m_ackRequestIsSet = true;
}

const xs_boolean &Header::getAckRequest() const { return m_ackRequest; }

void Header::cleanAckRequest() {
  m_ackRequest = false;
  m_ackRequestIsSet = false;
}

bool Header::getAckRequestIsSet() const { return m_ackRequestIsSet; }

void Header::setTimestamp(const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &Header::getTimestamp() const {
  return m_timestamp;
}

void Header::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool Header::getTimestampIsSet() const { return m_timestampIsSet; }

const CmdClassifier &Header::getClassifier() const {
  return getCmdClassifier();
}

std::string Header::getClassifierAsString() const {
  return m_cmdClassifier.toString();
}

void Header::setClassifier(const CmdClassifier &c_value) {
  setCmdClassifier(c_value);
}

bool Header::areAddressesSet() const {
  return m_addressDestinationIsSet && m_addressDestination.getEntityIsSet() &&
         m_addressDestination.getFeatureIsSet() && m_addressSourceIsSet &&
         m_addressSource.getEntityIsSet() && m_addressSource.getFeatureIsSet();
}

void Header::changeToReply(CmdClassifier c_classifier) {
  changeToResponse(c_classifier);
}

void Header::changeToResponse(CmdClassifier c_classifier) {
  if (m_addressSource == m_addressOriginator) {
    setAddressSource(m_addressDestination);
    setAddressDestination(m_addressOriginator);
  } else {
    FeatureAddress tmpAddress = m_addressSource;
    setAddressSource(m_addressDestination);
    setAddressDestination(tmpAddress);
  }
  setCmdClassifier(c_classifier);
  setMsgCounterReference(m_msgCounter);
  cleanAckRequest();
  createNewMsgCounter();
}

bool Header::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {

    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"specificationVersion", "addressSource", "addressDestination",
             "addressOriginator", "msgCounter", "msgCounterReference",
             "cmdClassifier", "ackRequest", "timestamp"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "specificationVersion",
                                   &m_specificationVersion)) {
      m_specificationVersionIsSet = true;
      ++iter;
    } else {
      throw DatagramParserException(
          "Could not parse mandatory field <specificationVersion>");
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "addressSource", &m_addressSource)) {
      m_addressSourceIsSet = true;
      ++iter;
    } else {
      throw DatagramParserException(
          "Could not parse mandatory field <addressSource>");
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "addressDestination",
                                   &m_addressDestination)) {
      m_addressDestinationIsSet = true;
      ++iter;
    } else {
      throw DatagramParserException(
          "Could not parse mandatory field <addressDestination>");
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "addressOriginator", &m_addressOriginator)) {
      m_addressOriginatorIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "msgCounter", &m_msgCounter)) {
      m_msgCounterIsSet = true;
      ++iter;
    } else {
      throw DatagramParserException(
          "Could not parse mandatory field <msgCounter>");
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "msgCounterReference",
                                   &m_msgCounterReference)) {
      m_msgCounterReferenceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "cmdClassifier", &m_cmdClassifier)) {
      m_cmdClassifierIsSet = true;
      ++iter;
    } else {
      throw DatagramParserException(
          "Could not parse mandatory field <cmdClassifier>");
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "ackRequest", &m_ackRequest)) {
      m_ackRequestIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestamp", &m_timestamp)) {
      m_timestampIsSet = true;
      ++iter;
    }

    return areAddressesSet();
  }
  return true;
}

std::string Header::toJson() const {
  std::string result = "[";
  if (m_specificationVersionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("specificationVersion",
                                           m_specificationVersion);
  }
  if (m_addressSourceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("addressSource", m_addressSource);
  }
  if (m_addressDestinationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("addressDestination",
                                           m_addressDestination);
  }
  if (m_addressOriginatorIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("addressOriginator", m_addressOriginator);
  }
  if (m_msgCounterIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("msgCounter", m_msgCounter);
  }
  if (m_msgCounterReferenceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("msgCounterReference",
                                           m_msgCounterReference);
  }
  if (m_cmdClassifierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("cmdClassifier", m_cmdClassifier);
  }
  if (m_ackRequestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("ackRequest", m_ackRequest);
  }
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  result += "]";
  return result;
}

xs_unsignedLong Header::createNewMsgCounter() {
  static xs_unsignedLong msgCounterStatic = 0;
  static std::mutex mtx;

  mtx.lock();
  xs_unsignedLong msgCounter = ++msgCounterStatic;
  mtx.unlock();

  setMsgCounter(msgCounter);
  return getMsgCounter();
}

} // namespace keo_datagram