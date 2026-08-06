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

#include <keo_datagram/core/SubscriptionManagementDeleteCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SubscriptionManagementDeleteCall::SubscriptionManagementDeleteCall()
    : CmdData(), m_subscriptionIdIsSet(false), m_subscriptionId(0),
      m_clientAddressIsSet(false), m_clientAddress(FeatureAddress()),
      m_serverAddressIsSet(false), m_serverAddress(FeatureAddress())

{}

SubscriptionManagementDeleteCall::SubscriptionManagementDeleteCall(
    const xs_unsignedInt &c_subscriptionId,
    const FeatureAddress &c_clientAddress,
    const FeatureAddress &c_serverAddress)
    : CmdData(), m_subscriptionIdIsSet(true),
      m_subscriptionId(c_subscriptionId), m_clientAddressIsSet(true),
      m_clientAddress(c_clientAddress), m_serverAddressIsSet(true),
      m_serverAddress(c_serverAddress)

{}

bool SubscriptionManagementDeleteCall::
operator==(const SubscriptionManagementDeleteCall &c_classObject) const {
  if (m_subscriptionIdIsSet != c_classObject.m_subscriptionIdIsSet ||
      (m_subscriptionIdIsSet &&
       (m_subscriptionId != c_classObject.m_subscriptionId))) {
    return false;
  }
  if (m_clientAddressIsSet != c_classObject.m_clientAddressIsSet ||
      (m_clientAddressIsSet &&
       (m_clientAddress != c_classObject.m_clientAddress))) {
    return false;
  }
  if (m_serverAddressIsSet != c_classObject.m_serverAddressIsSet ||
      (m_serverAddressIsSet &&
       (m_serverAddress != c_classObject.m_serverAddress))) {
    return false;
  }

  return true;
}

bool SubscriptionManagementDeleteCall::
operator!=(const SubscriptionManagementDeleteCall &c_classObject) const {
  return !(*this == c_classObject);
}

bool SubscriptionManagementDeleteCall::isEmpty() const {
  return !m_subscriptionIdIsSet && !m_clientAddressIsSet &&
         !m_serverAddressIsSet;
}

CmdData::Type SubscriptionManagementDeleteCall::getDataType() const {
  return CmdData::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_TYPE;
}

CmdDataPtr SubscriptionManagementDeleteCall::clone() const {
  return std::make_shared<SubscriptionManagementDeleteCall>(*this);
}

void SubscriptionManagementDeleteCall::setSubscriptionId(
    const xs_unsignedInt &subscriptionId) {
  m_subscriptionId = subscriptionId;
  m_subscriptionIdIsSet = true;
}

const xs_unsignedInt &
SubscriptionManagementDeleteCall::getSubscriptionId() const {
  return m_subscriptionId;
}

void SubscriptionManagementDeleteCall::cleanSubscriptionId() {
  m_subscriptionId = 0;
  m_subscriptionIdIsSet = false;
}

bool SubscriptionManagementDeleteCall::getSubscriptionIdIsSet() const {
  return m_subscriptionIdIsSet;
}

void SubscriptionManagementDeleteCall::setClientAddress(
    const FeatureAddress &clientAddress) {
  m_clientAddress = clientAddress;
  m_clientAddressIsSet = true;
}

const FeatureAddress &
SubscriptionManagementDeleteCall::getClientAddress() const {
  return m_clientAddress;
}

void SubscriptionManagementDeleteCall::cleanClientAddress() {
  m_clientAddress = FeatureAddress();
  m_clientAddressIsSet = false;
}

bool SubscriptionManagementDeleteCall::getClientAddressIsSet() const {
  return m_clientAddressIsSet;
}

void SubscriptionManagementDeleteCall::setServerAddress(
    const FeatureAddress &serverAddress) {
  m_serverAddress = serverAddress;
  m_serverAddressIsSet = true;
}

const FeatureAddress &
SubscriptionManagementDeleteCall::getServerAddress() const {
  return m_serverAddress;
}

void SubscriptionManagementDeleteCall::cleanServerAddress() {
  m_serverAddress = FeatureAddress();
  m_serverAddressIsSet = false;
}

bool SubscriptionManagementDeleteCall::getServerAddressIsSet() const {
  return m_serverAddressIsSet;
}

CmdDataPtr SubscriptionManagementDeleteCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<SubscriptionManagementDeleteCall>(*this);
}

bool SubscriptionManagementDeleteCall::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"subscriptionId", "clientAddress", "serverAddress"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "subscriptionId", &m_subscriptionId)) {
      m_subscriptionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "clientAddress", &m_clientAddress)) {
      m_clientAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "serverAddress", &m_serverAddress)) {
      m_serverAddressIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SubscriptionManagementDeleteCall::toJson() const {
  std::string result = "[";
  if (m_subscriptionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("subscriptionId", m_subscriptionId);
  }
  if (m_clientAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("clientAddress", m_clientAddress);
  }
  if (m_serverAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("serverAddress", m_serverAddress);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram