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

#include <keo_datagram/smartenergymanagementps/PowerSequencePriceDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequencePriceDataElements::PowerSequencePriceDataElements()
    : DataElements(), m_sequenceIdIsSet(false),
      m_potentialStartTimeIsSet(false), m_priceIsSet(false),
      m_price(ScaledNumberElements()), m_currencyIsSet(false)

{}

bool PowerSequencePriceDataElements::
operator==(const PowerSequencePriceDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_potentialStartTimeIsSet != c_classObject.m_potentialStartTimeIsSet) {
    return false;
  }
  if (m_priceIsSet != c_classObject.m_priceIsSet ||
      (m_priceIsSet && (m_price != c_classObject.m_price))) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet) {
    return false;
  }

  return true;
}

bool PowerSequencePriceDataElements::
operator!=(const PowerSequencePriceDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequencePriceDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_potentialStartTimeIsSet && !m_priceIsSet &&
         !m_currencyIsSet;
}

DataElements::Type PowerSequencePriceDataElements::getDataType() const {
  return DataElements::Type::POWER_SEQUENCE_PRICE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerSequencePriceDataElements::clone() const {
  return std::make_shared<PowerSequencePriceDataElements>(*this);
}

void PowerSequencePriceDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerSequencePriceDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerSequencePriceDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequencePriceDataElements::setPotentialStartTime() {
  m_potentialStartTimeIsSet = true;
}

void PowerSequencePriceDataElements::cleanPotentialStartTime() {
  m_potentialStartTimeIsSet = false;
}

bool PowerSequencePriceDataElements::getPotentialStartTimeIsSet() const {
  return m_potentialStartTimeIsSet;
}

void PowerSequencePriceDataElements::setPrice(
    const ScaledNumberElements &price) {
  m_price = price;
  m_priceIsSet = true;
}

const ScaledNumberElements &PowerSequencePriceDataElements::getPrice() const {
  return m_price;
}

void PowerSequencePriceDataElements::cleanPrice() {
  m_price = ScaledNumberElements();
  m_priceIsSet = false;
}

bool PowerSequencePriceDataElements::getPriceIsSet() const {
  return m_priceIsSet;
}

void PowerSequencePriceDataElements::setCurrency() { m_currencyIsSet = true; }

void PowerSequencePriceDataElements::cleanCurrency() {
  m_currencyIsSet = false;
}

bool PowerSequencePriceDataElements::getCurrencyIsSet() const {
  return m_currencyIsSet;
}

bool PowerSequencePriceDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "potentialStartTime", "price", "currency"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "potentialStartTime")) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "currency")) {
      m_currencyIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequencePriceDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_potentialStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("potentialStartTime");
  }
  if (m_priceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("price", m_price);
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("currency");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram