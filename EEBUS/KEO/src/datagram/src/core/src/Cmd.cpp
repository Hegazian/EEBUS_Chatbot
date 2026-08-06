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

#include <keo_datagram/core/Cmd.h>

#include <CreateSpineDataClass.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

Cmd::Cmd()
    : m_functionIsSet(false), m_function(Function()), m_filterIsSet(false),
      m_filter(std::vector<Filter>()), m_cmdDataIsSet(false),
      m_cmdData(CmdDataPtr()), m_manufacturerSpecificExtensionIsSet(false),
      m_manufacturerSpecificExtension(xs_hexBinary()),
      m_lastUpdateAtIsSet(false), m_lastUpdateAt(AbsoluteOrRelativeTime())

{}

Cmd::Cmd(const CmdDataPtr &c_cmdData)
    : m_functionIsSet(false), m_function(Function()), m_filterIsSet(false),
      m_filter(std::vector<Filter>()), m_cmdDataIsSet(false),
      m_cmdData(c_cmdData), m_manufacturerSpecificExtensionIsSet(false),
      m_manufacturerSpecificExtension(KeoByteArray()),
      m_lastUpdateAtIsSet(false), m_lastUpdateAt(AbsoluteOrRelativeTime()) {
  if (m_cmdData) {
    m_cmdDataIsSet = true;
  }
}

Cmd::Cmd(const CmdData::Type type)
    : m_functionIsSet(false), m_function(Function()), m_filterIsSet(false),
      m_filter(std::vector<Filter>()), m_cmdDataIsSet(false),
      m_cmdData(CreateSpineDataClass::createCmdData(type)),
      m_manufacturerSpecificExtensionIsSet(false),
      m_manufacturerSpecificExtension(KeoByteArray()),
      m_lastUpdateAtIsSet(false), m_lastUpdateAt(AbsoluteOrRelativeTime()) {
  if (m_cmdData) {
    m_cmdDataIsSet = true;
  }
}

Cmd::Cmd(const Cmd &c_classObject)
    : m_functionIsSet(c_classObject.m_functionIsSet),
      m_function(c_classObject.m_function),
      m_filterIsSet(c_classObject.m_filterIsSet),
      m_filter(c_classObject.m_filter), m_cmdDataIsSet(false),
      m_manufacturerSpecificExtensionIsSet(
          c_classObject.m_manufacturerSpecificExtensionIsSet),
      m_manufacturerSpecificExtension(
          c_classObject.m_manufacturerSpecificExtension),
      m_lastUpdateAtIsSet(c_classObject.m_lastUpdateAtIsSet),
      m_lastUpdateAt(c_classObject.m_lastUpdateAt) {
  if (c_classObject.m_cmdDataIsSet) {
    // Copy explicitly
    m_cmdData = c_classObject.m_cmdData->clone();
    m_cmdDataIsSet = true;
  }
}

Cmd::Cmd(Cmd &&c_classObject)
    : m_functionIsSet(c_classObject.m_functionIsSet),
      m_function(c_classObject.m_function),
      m_filterIsSet(c_classObject.m_filterIsSet),
      m_filter(c_classObject.m_filter),
      m_cmdDataIsSet(c_classObject.m_cmdDataIsSet),
      m_cmdData(c_classObject.m_cmdData) // steals pointee
      ,
      m_manufacturerSpecificExtensionIsSet(
          c_classObject.m_manufacturerSpecificExtensionIsSet),
      m_manufacturerSpecificExtension(
          c_classObject.m_manufacturerSpecificExtension),
      m_lastUpdateAtIsSet(c_classObject.m_lastUpdateAtIsSet),
      m_lastUpdateAt(c_classObject.m_lastUpdateAt) {}

bool Cmd::operator==(const Cmd &c_classObject) const {
  if (m_functionIsSet != c_classObject.m_functionIsSet ||
      (m_functionIsSet && (m_function != c_classObject.m_function))) {
    return false;
  }
  if (m_filterIsSet != c_classObject.m_filterIsSet ||
      (m_filterIsSet && (m_filter != c_classObject.m_filter))) {
    return false;
  }
  if (m_cmdDataIsSet != c_classObject.m_cmdDataIsSet ||
      (m_cmdDataIsSet && (m_cmdData != c_classObject.m_cmdData))) {
    return false;
  }
  if (m_manufacturerSpecificExtensionIsSet !=
          c_classObject.m_manufacturerSpecificExtensionIsSet ||
      (m_manufacturerSpecificExtensionIsSet &&
       (m_manufacturerSpecificExtension !=
        c_classObject.m_manufacturerSpecificExtension))) {
    return false;
  }
  if (m_lastUpdateAtIsSet != c_classObject.m_lastUpdateAtIsSet ||
      (m_lastUpdateAtIsSet &&
       (m_lastUpdateAt != c_classObject.m_lastUpdateAt))) {
    return false;
  }

  return true;
}

bool Cmd::operator!=(const Cmd &c_classObject) const {
  return !(*this == c_classObject);
}

bool Cmd::isEmpty() const {
  return !m_functionIsSet && !m_filterIsSet && !m_cmdDataIsSet &&
         !m_manufacturerSpecificExtensionIsSet && !m_lastUpdateAtIsSet;
}

Cmd &Cmd::operator=(const Cmd &c_classObject) {
  if (this != &c_classObject) {
    m_functionIsSet = c_classObject.m_functionIsSet;
    m_function = c_classObject.m_function;
    m_filterIsSet = c_classObject.m_filterIsSet;
    m_filter = c_classObject.m_filter;
    if (c_classObject.m_cmdDataIsSet) {
      // Copy explicitly
      m_cmdData = c_classObject.m_cmdData->clone();
      m_cmdDataIsSet = true;
    } else {
      m_cmdDataIsSet = false;
    }
    m_manufacturerSpecificExtensionIsSet =
        c_classObject.m_manufacturerSpecificExtensionIsSet;
    m_manufacturerSpecificExtension =
        c_classObject.m_manufacturerSpecificExtension;
    m_lastUpdateAtIsSet = c_classObject.m_lastUpdateAtIsSet;
    m_lastUpdateAt = c_classObject.m_lastUpdateAt;
  }
  return *this;
}

Cmd &Cmd::operator=(Cmd &&c_classObject) {
  if (this != &c_classObject) {
    m_functionIsSet = c_classObject.m_functionIsSet;
    m_function = c_classObject.m_function;
    m_filterIsSet = c_classObject.m_filterIsSet;
    m_filter = c_classObject.m_filter;
    m_cmdDataIsSet = c_classObject.m_cmdDataIsSet;
    m_cmdData = c_classObject.m_cmdData; // steals pointee
    m_manufacturerSpecificExtensionIsSet =
        c_classObject.m_manufacturerSpecificExtensionIsSet;
    m_manufacturerSpecificExtension =
        c_classObject.m_manufacturerSpecificExtension;
    m_lastUpdateAtIsSet = c_classObject.m_lastUpdateAtIsSet;
    m_lastUpdateAt = c_classObject.m_lastUpdateAt;
  }
  return *this;
}

void Cmd::setFunction(const Function &function) {
  m_function = function;
  m_functionIsSet = true;
}

const Function &Cmd::getFunction() const { return m_function; }

void Cmd::cleanFunction() {
  m_function = Function();
  m_functionIsSet = false;
}

bool Cmd::getFunctionIsSet() const { return m_functionIsSet; }

void Cmd::setFilter(const std::vector<Filter> &filter) {
  m_filter = filter;
  m_filterIsSet = true;
}

const std::vector<Filter> &Cmd::getFilter() const { return m_filter; }

void Cmd::cleanFilter() {
  m_filter.clear();
  m_filterIsSet = false;
}

bool Cmd::getFilterIsSet() const { return m_filterIsSet; }

void Cmd::setCmdData(const CmdDataPtr &cmdData) {
  m_cmdData = cmdData;
  m_cmdDataIsSet = (cmdData != nullptr);
}

CmdDataPtr Cmd::getCmdData() const { return m_cmdData; }

void Cmd::cleanCmdData() {
  m_cmdData = CmdDataPtr();
  m_cmdDataIsSet = false;
}

bool Cmd::getCmdDataIsSet() const { return m_cmdDataIsSet; }

void Cmd::setManufacturerSpecificExtension(
    const xs_hexBinary &manufacturerSpecificExtension) {
  m_manufacturerSpecificExtension = manufacturerSpecificExtension;
  m_manufacturerSpecificExtensionIsSet = true;
}

const xs_hexBinary &Cmd::getManufacturerSpecificExtension() const {
  return m_manufacturerSpecificExtension;
}

void Cmd::cleanManufacturerSpecificExtension() {
  m_manufacturerSpecificExtension = xs_hexBinary();
  m_manufacturerSpecificExtensionIsSet = false;
}

bool Cmd::getManufacturerSpecificExtensionIsSet() const {
  return m_manufacturerSpecificExtensionIsSet;
}

void Cmd::setLastUpdateAt(const AbsoluteOrRelativeTime &lastUpdateAt) {
  m_lastUpdateAt = lastUpdateAt;
  m_lastUpdateAtIsSet = true;
}

const AbsoluteOrRelativeTime &Cmd::getLastUpdateAt() const {
  return m_lastUpdateAt;
}

void Cmd::cleanLastUpdateAt() {
  m_lastUpdateAt = AbsoluteOrRelativeTime();
  m_lastUpdateAtIsSet = false;
}

bool Cmd::getLastUpdateAtIsSet() const { return m_lastUpdateAtIsSet; }

void Cmd::setCmdFilterList(const std::vector<Filter> &c_data) {
  setFilter(c_data);
}

CmdData::Type Cmd::getDataType() const {
  if (m_cmdData) {
    return m_cmdData->getDataType();
  } else {
    return CmdData::Type::UNDEFINED;
  }
}

bool Cmd::hasFilters() const { return m_filterIsSet && !m_filter.empty(); }

bool Cmd::fromJson(KeoJsonValue *json) {
  auto iter = json->begin();
  if (iter != json->end() &&
      KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                 "function", &m_function)) {
    m_functionIsSet = true;
    ++iter;
  }
  if (iter != json->end() &&
      KeoJsonTransformation::getList<Filter>(
          static_cast<KeoJsonValue *>(&(*iter)), "filter", &m_filter)) {
    m_filterIsSet = true;
    ++iter;
  }
  if (iter != json->end() && (*iter).begin().key().isString()) {
    const std::string dataClassName = (*iter).begin().key().asString();
    CmdData::Type type = CmdData::getTypeFromString(dataClassName);
    m_cmdData = CreateSpineDataClass::createCmdData(type);
    if (m_cmdData &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   dataClassName, m_cmdData.get())) {
      m_cmdDataIsSet = true;
      ++iter;
    }
  }
  if (!m_cmdData) {
    throw DatagramParserException("Could not instantiate command. This may be "
                                  "caused by a missing KEO SPINE datagram "
                                  "library plugin.");
  }
  if (iter != json->end() &&
      KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                 "manufacturerSpecificExtension",
                                 &m_manufacturerSpecificExtension)) {
    m_manufacturerSpecificExtensionIsSet = true;
    ++iter;
  }
  if (iter != json->end() &&
      KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                 "lastUpdateAt", &m_lastUpdateAt)) {
    m_lastUpdateAtIsSet = true;
    ++iter;
  }
  return true;
}

std::string Cmd::toJson() const {
  std::string result = "[";
  if (m_functionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("function", m_function);
  }
  if (m_filterIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<Filter>("filter", m_filter);
  }
  if (m_cmdDataIsSet) {
    std::string cmdType = CmdData::getStringFromType(m_cmdData->getDataType());
    if (!cmdType.empty()) {
      KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
      result += KeoJsonTransformation::write(cmdType, *m_cmdData);
    }
  }
  if (m_manufacturerSpecificExtensionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("manufacturerSpecificExtension",
                                           m_manufacturerSpecificExtension);
  }
  if (m_lastUpdateAtIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("lastUpdateAt", m_lastUpdateAt);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram