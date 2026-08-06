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

#include <keo_datagram/core/CmdControl.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

CmdControl::CmdControl()
    : m_deleteIsSet(false), m_partialIsSet(false)

{}

CmdControl::CmdControl(xs_boolean c_deleteIsSet, xs_boolean c_partialIsSet)
    : m_deleteIsSet(c_deleteIsSet), m_partialIsSet(c_partialIsSet)

{}

bool CmdControl::operator==(const CmdControl &c_classObject) const {
  if (m_deleteIsSet != c_classObject.m_deleteIsSet) {
    return false;
  }
  if (m_partialIsSet != c_classObject.m_partialIsSet) {
    return false;
  }

  return true;
}

bool CmdControl::operator!=(const CmdControl &c_classObject) const {
  return !(*this == c_classObject);
}

bool CmdControl::isEmpty() const { return !m_deleteIsSet && !m_partialIsSet; }

void CmdControl::setDelete() { m_deleteIsSet = true; }

void CmdControl::cleanDelete() { m_deleteIsSet = false; }

bool CmdControl::getDeleteIsSet() const { return m_deleteIsSet; }

void CmdControl::setPartial() { m_partialIsSet = true; }

void CmdControl::cleanPartial() { m_partialIsSet = false; }

bool CmdControl::getPartialIsSet() const { return m_partialIsSet; }

bool CmdControl::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"delete", "partial"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "delete")) {
      m_deleteIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "partial")) {
      m_partialIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string CmdControl::toJson() const {
  std::string result = "[";
  if (m_deleteIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("delete");
  }
  if (m_partialIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("partial");
  }
  result += "]";
  return result;
}

const CmdControl CmdControl::DELETE(true, false);
const CmdControl CmdControl::PARTIAL(false, true);

} // namespace keo_datagram