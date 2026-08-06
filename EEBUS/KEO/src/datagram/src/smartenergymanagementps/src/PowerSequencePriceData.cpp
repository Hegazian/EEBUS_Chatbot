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

#include <keo_datagram/smartenergymanagementps/PowerSequencePriceData.h>

#include <keo_datagram/smartenergymanagementps/PowerSequencePriceDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequencePriceData::PowerSequencePriceData()
    : m_sequenceIdIsSet(false), m_sequenceId(0),
      m_potentialStartTimeIsSet(false),
      m_potentialStartTime(AbsoluteOrRelativeTime()), m_priceIsSet(false),
      m_price(ScaledNumber()), m_currencyIsSet(false), m_currency(Currency())

{}

bool PowerSequencePriceData::
operator==(const PowerSequencePriceData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_potentialStartTimeIsSet != c_classObject.m_potentialStartTimeIsSet ||
      (m_potentialStartTimeIsSet &&
       (m_potentialStartTime != c_classObject.m_potentialStartTime))) {
    return false;
  }
  if (m_priceIsSet != c_classObject.m_priceIsSet ||
      (m_priceIsSet && (m_price != c_classObject.m_price))) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet ||
      (m_currencyIsSet && (m_currency != c_classObject.m_currency))) {
    return false;
  }

  return true;
}

bool PowerSequencePriceData::
operator!=(const PowerSequencePriceData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequencePriceData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_potentialStartTimeIsSet && !m_priceIsSet &&
         !m_currencyIsSet;
}

void PowerSequencePriceData::setSequenceId(const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &PowerSequencePriceData::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequencePriceData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequencePriceData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequencePriceData::setPotentialStartTime(
    const AbsoluteOrRelativeTime &potentialStartTime) {
  m_potentialStartTime = potentialStartTime;
  m_potentialStartTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
PowerSequencePriceData::getPotentialStartTime() const {
  return m_potentialStartTime;
}

void PowerSequencePriceData::cleanPotentialStartTime() {
  m_potentialStartTime = AbsoluteOrRelativeTime();
  m_potentialStartTimeIsSet = false;
}

bool PowerSequencePriceData::getPotentialStartTimeIsSet() const {
  return m_potentialStartTimeIsSet;
}

void PowerSequencePriceData::setPrice(const ScaledNumber &price) {
  m_price = price;
  m_priceIsSet = true;
}

const ScaledNumber &PowerSequencePriceData::getPrice() const { return m_price; }

void PowerSequencePriceData::cleanPrice() {
  m_price = ScaledNumber();
  m_priceIsSet = false;
}

bool PowerSequencePriceData::getPriceIsSet() const { return m_priceIsSet; }

void PowerSequencePriceData::setCurrency(const Currency &currency) {
  m_currency = currency;
  m_currencyIsSet = true;
}

const Currency &PowerSequencePriceData::getCurrency() const {
  return m_currency;
}

void PowerSequencePriceData::cleanCurrency() {
  m_currency = Currency();
  m_currencyIsSet = false;
}

bool PowerSequencePriceData::getCurrencyIsSet() const {
  return m_currencyIsSet;
}

PowerSequencePriceData PowerSequencePriceData::reduce(
    const PowerSequencePriceDataElements &elements) const {
  PowerSequencePriceData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getPotentialStartTimeIsSet() && elements.getPotentialStartTimeIsSet()) {
    dataOut.setPotentialStartTime(getPotentialStartTime());
  }
  if (getPriceIsSet() && elements.getPriceIsSet()) {
    dataOut.setPrice(getPrice().reduce(elements.getPrice()));
  }
  if (getCurrencyIsSet() && elements.getCurrencyIsSet()) {
    dataOut.setCurrency(getCurrency());
  }
  return dataOut;
}

bool PowerSequencePriceData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "potentialStartTime", "price", "currency"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "potentialStartTime",
                                   &m_potentialStartTime)) {
      m_potentialStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "price", &m_price)) {
      m_priceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "currency", &m_currency)) {
      m_currencyIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequencePriceData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_potentialStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("potentialStartTime",
                                           m_potentialStartTime);
  }
  if (m_priceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("price", m_price);
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("currency", m_currency);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram