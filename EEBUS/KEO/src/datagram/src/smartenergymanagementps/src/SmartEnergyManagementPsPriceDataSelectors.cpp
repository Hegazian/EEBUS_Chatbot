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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsPriceDataSelectors::
    SmartEnergyManagementPsPriceDataSelectors()
    : DataSelectors(), m_priceIsSet(false),
      m_price(PowerSequencePriceListDataSelectors())

{}

SmartEnergyManagementPsPriceDataSelectors::
    SmartEnergyManagementPsPriceDataSelectors(
        const PowerSequencePriceListDataSelectors &c_price) {
  setPrice(c_price);
}

bool SmartEnergyManagementPsPriceDataSelectors::operator==(
    const SmartEnergyManagementPsPriceDataSelectors &c_classObject) const {
  if (m_priceIsSet != c_classObject.m_priceIsSet ||
      (m_priceIsSet && (m_price != c_classObject.m_price))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsPriceDataSelectors::operator!=(
    const SmartEnergyManagementPsPriceDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsPriceDataSelectors::isEmpty() const {
  return !m_priceIsSet;
}

DataSelectors::Type
SmartEnergyManagementPsPriceDataSelectors::getDataType() const {
  return DataSelectors::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SmartEnergyManagementPsPriceDataSelectors::clone() const {
  return std::make_shared<SmartEnergyManagementPsPriceDataSelectors>(*this);
}

void SmartEnergyManagementPsPriceDataSelectors::setPrice(
    const PowerSequencePriceListDataSelectors &price) {
  m_price = price;
  m_priceIsSet = true;
}

const PowerSequencePriceListDataSelectors &
SmartEnergyManagementPsPriceDataSelectors::getPrice() const {
  return m_price;
}

void SmartEnergyManagementPsPriceDataSelectors::cleanPrice() {
  m_price = PowerSequencePriceListDataSelectors();
  m_priceIsSet = false;
}

bool SmartEnergyManagementPsPriceDataSelectors::getPriceIsSet() const {
  return m_priceIsSet;
}

bool SmartEnergyManagementPsPriceDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"price"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "price", &m_price)) {
      m_priceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsPriceDataSelectors::toJson() const {
  std::string result = "[";
  if (m_priceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("price", m_price);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram