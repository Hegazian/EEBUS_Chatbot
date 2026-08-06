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

#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceCalculationRequestCall.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SmartEnergyManagementPsPriceCalculationRequestCall::
    SmartEnergyManagementPsPriceCalculationRequestCall()
    : CmdData(), m_priceCalculationRequestIsSet(false),
      m_priceCalculationRequest(PowerSequencePriceCalculationRequestCall())

{}

SmartEnergyManagementPsPriceCalculationRequestCall::
    SmartEnergyManagementPsPriceCalculationRequestCall(
        const PowerSequencePriceCalculationRequestCall
            &c_priceCalculationRequest) {
  setPriceCalculationRequest(c_priceCalculationRequest);
}

bool SmartEnergyManagementPsPriceCalculationRequestCall::operator==(
    const SmartEnergyManagementPsPriceCalculationRequestCall &c_classObject)
    const {
  if (m_priceCalculationRequestIsSet !=
          c_classObject.m_priceCalculationRequestIsSet ||
      (m_priceCalculationRequestIsSet &&
       (m_priceCalculationRequest !=
        c_classObject.m_priceCalculationRequest))) {
    return false;
  }

  return true;
}

bool SmartEnergyManagementPsPriceCalculationRequestCall::operator!=(
    const SmartEnergyManagementPsPriceCalculationRequestCall &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool SmartEnergyManagementPsPriceCalculationRequestCall::isEmpty() const {
  return !m_priceCalculationRequestIsSet;
}

CmdData::Type
SmartEnergyManagementPsPriceCalculationRequestCall::getDataType() const {
  return CmdData::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_TYPE;
}

CmdDataPtr SmartEnergyManagementPsPriceCalculationRequestCall::clone() const {
  return std::make_shared<SmartEnergyManagementPsPriceCalculationRequestCall>(
      *this);
}

void SmartEnergyManagementPsPriceCalculationRequestCall::
    setPriceCalculationRequest(const PowerSequencePriceCalculationRequestCall
                                   &priceCalculationRequest) {
  m_priceCalculationRequest = priceCalculationRequest;
  m_priceCalculationRequestIsSet = true;
}

const PowerSequencePriceCalculationRequestCall &
SmartEnergyManagementPsPriceCalculationRequestCall::getPriceCalculationRequest()
    const {
  return m_priceCalculationRequest;
}

void SmartEnergyManagementPsPriceCalculationRequestCall::
    cleanPriceCalculationRequest() {
  m_priceCalculationRequest = PowerSequencePriceCalculationRequestCall();
  m_priceCalculationRequestIsSet = false;
}

bool SmartEnergyManagementPsPriceCalculationRequestCall::
    getPriceCalculationRequestIsSet() const {
  return m_priceCalculationRequestIsSet;
}

CmdDataPtr SmartEnergyManagementPsPriceCalculationRequestCall::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<SmartEnergyManagementPsPriceCalculationRequestCall>(
      *this);
}

bool SmartEnergyManagementPsPriceCalculationRequestCall::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"priceCalculationRequest"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "priceCalculationRequest",
                                   &m_priceCalculationRequest)) {
      m_priceCalculationRequestIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SmartEnergyManagementPsPriceCalculationRequestCall::toJson() const {
  std::string result = "[";
  if (m_priceCalculationRequestIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("priceCalculationRequest",
                                           m_priceCalculationRequest);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram