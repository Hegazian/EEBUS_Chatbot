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

#include <keo_datagram/core/Payload.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

Payload::Payload()
    : m_cmdIsSet(false), m_cmd(std::vector<Cmd>())

{}

Payload::Payload(const std::vector<Cmd> &c_cmd) { setCmd(c_cmd); }

bool Payload::operator==(const Payload &c_classObject) const {
  if (m_cmdIsSet != c_classObject.m_cmdIsSet ||
      (m_cmdIsSet && (m_cmd != c_classObject.m_cmd))) {
    return false;
  }

  return true;
}

bool Payload::operator!=(const Payload &c_classObject) const {
  return !(*this == c_classObject);
}

bool Payload::isEmpty() const { return !m_cmdIsSet; }

void Payload::setCmd(const std::vector<Cmd> &cmd) {
  m_cmd = cmd;
  m_cmdIsSet = true;
}

const std::vector<Cmd> &Payload::getCmd() const { return m_cmd; }

void Payload::cleanCmd() {
  m_cmd.clear();
  m_cmdIsSet = false;
}

bool Payload::getCmdIsSet() const { return m_cmdIsSet; }

bool Payload::hasSingleCmd() const { return (m_cmd.size() == 1); }

bool Payload::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"cmd"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<Cmd>(
            static_cast<KeoJsonValue *>(&(*iter)), "cmd", &m_cmd)) {
      m_cmdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string Payload::toJson() const {
  std::string result = "[";
  if (m_cmdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<Cmd>("cmd", m_cmd);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram