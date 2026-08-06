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

#include <keo_datagram/core/PossibleOperationsRead.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PossibleOperationsRead::PossibleOperationsRead()
    : m_partialIsSet(false)

{}

PossibleOperationsRead::PossibleOperationsRead(
    const xs_boolean &c_partialIsSet) {
  if (c_partialIsSet) {
    setPartial();
  }
}

bool PossibleOperationsRead::
operator==(const PossibleOperationsRead &c_classObject) const {
  if (m_partialIsSet != c_classObject.m_partialIsSet) {
    return false;
  }

  return true;
}

bool PossibleOperationsRead::
operator!=(const PossibleOperationsRead &c_classObject) const {
  return !(*this == c_classObject);
}

bool PossibleOperationsRead::isEmpty() const { return !m_partialIsSet; }

void PossibleOperationsRead::setPartial() { m_partialIsSet = true; }

void PossibleOperationsRead::cleanPartial() { m_partialIsSet = false; }

bool PossibleOperationsRead::getPartialIsSet() const { return m_partialIsSet; }

bool PossibleOperationsRead::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"partial"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "partial")) {
      m_partialIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PossibleOperationsRead::toJson() const {
  std::string result = "[";
  if (m_partialIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("partial");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram