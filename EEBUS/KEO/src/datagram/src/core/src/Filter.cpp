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

#include <keo_datagram/core/Filter.h>

#include <CreateSpineDataClass.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

Filter::Filter()
    : m_filterIdIsSet(false), m_filterId(0), m_cmdControlIsSet(false),
      m_cmdControl(CmdControl()), m_dataSelectorsIsSet(false)

      ,
      m_dataSelectors(std::vector<DataSelectorsPtr>()),
      m_dataElementsIsSet(false), m_dataElements(DataElementsPtr())

{}

Filter::Filter(const Filter &c_classObject)
    : m_filterIdIsSet(c_classObject.m_filterIdIsSet),
      m_filterId(c_classObject.m_filterId),
      m_cmdControlIsSet(c_classObject.m_cmdControlIsSet),
      m_cmdControl(c_classObject.m_cmdControl),
      m_dataSelectorsIsSet(c_classObject.m_dataSelectorsIsSet),
      m_dataSelectors(std::vector<DataSelectorsPtr>()),
      m_dataElementsIsSet(false) {
  if (c_classObject.m_dataSelectorsIsSet) {
    // Copy explicitly
    for (const auto &selector : c_classObject.m_dataSelectors) {
      m_dataSelectors.push_back(selector->clone());
    }
    m_dataSelectorsIsSet = true;
  }

  if (c_classObject.m_dataElementsIsSet) {
    // Copy explicitly
    m_dataElements = c_classObject.m_dataElements->clone();
    m_dataElementsIsSet = true;
  }
}

Filter::Filter(Filter &&c_classObject)
    : m_filterIdIsSet(c_classObject.m_filterIdIsSet),
      m_filterId(c_classObject.m_filterId),
      m_cmdControlIsSet(c_classObject.m_cmdControlIsSet),
      m_cmdControl(c_classObject.m_cmdControl),
      m_dataSelectorsIsSet(c_classObject.m_dataSelectorsIsSet),
      m_dataSelectors(c_classObject.m_dataSelectors) // steals pointees
      ,
      m_dataElementsIsSet(c_classObject.m_dataElementsIsSet),
      m_dataElements(c_classObject.m_dataElements) // steals pointee
{}

bool Filter::operator==(const Filter &c_classObject) const {
  if (m_filterIdIsSet != c_classObject.m_filterIdIsSet ||
      (m_filterIdIsSet && (m_filterId != c_classObject.m_filterId))) {
    return false;
  }
  if (m_cmdControlIsSet != c_classObject.m_cmdControlIsSet ||
      (m_cmdControlIsSet && (m_cmdControl != c_classObject.m_cmdControl))) {
    return false;
  }
  if (m_dataSelectorsIsSet != c_classObject.m_dataSelectorsIsSet ||
      (m_dataSelectorsIsSet &&
       (m_dataSelectors != c_classObject.m_dataSelectors))) {
    return false;
  }
  if (m_dataElementsIsSet != c_classObject.m_dataElementsIsSet ||
      (m_dataElementsIsSet &&
       (m_dataElements != c_classObject.m_dataElements))) {
    return false;
  }

  return true;
}

bool Filter::operator!=(const Filter &c_classObject) const {
  return !(*this == c_classObject);
}

bool Filter::isEmpty() const {
  return !m_filterIdIsSet && !m_cmdControlIsSet && !m_dataSelectorsIsSet &&
         !m_dataElementsIsSet;
}

Filter &Filter::operator=(const Filter &c_classObject) {
  if (this != &c_classObject) {
    m_filterIdIsSet = c_classObject.m_filterIdIsSet;
    m_filterId = c_classObject.m_filterId;
    m_cmdControlIsSet = c_classObject.m_cmdControlIsSet;
    m_cmdControl = c_classObject.m_cmdControl;

    if (c_classObject.m_dataSelectorsIsSet) {
      // Copy explicitely
      for (const auto &selector : m_dataSelectors) {
        m_dataSelectors.push_back(selector->clone());
      }
      m_dataSelectorsIsSet = true;
    }

    if (c_classObject.m_dataElementsIsSet) {
      // Copy explicitely
      m_dataElements = c_classObject.m_dataElements->clone();
      m_dataElementsIsSet = true;
    } else {
      m_dataElementsIsSet = false;
    }
  }
  return *this;
}

Filter &Filter::operator=(Filter &&c_classObject) {
  if (this != &c_classObject) {
    m_filterIdIsSet = c_classObject.m_filterIdIsSet;
    m_filterId = c_classObject.m_filterId;
    m_cmdControlIsSet = c_classObject.m_cmdControlIsSet;
    m_cmdControl = c_classObject.m_cmdControl;
    m_dataSelectorsIsSet = c_classObject.m_dataSelectorsIsSet;
    m_dataSelectors = c_classObject.m_dataSelectors; // steals pointees
    m_dataElementsIsSet = c_classObject.m_dataElementsIsSet;
    m_dataElements = c_classObject.m_dataElements; // steals pointee
  }
  return *this;
}

void Filter::setFilterId(const xs_unsignedInt &filterId) {
  m_filterId = filterId;
  m_filterIdIsSet = true;
}

const xs_unsignedInt &Filter::getFilterId() const { return m_filterId; }

void Filter::cleanFilterId() {
  m_filterId = 0;
  m_filterIdIsSet = false;
}

bool Filter::getFilterIdIsSet() const { return m_filterIdIsSet; }

void Filter::setCmdControl(const CmdControl &cmdControl) {
  m_cmdControl = cmdControl;
  m_cmdControlIsSet = true;
}

const CmdControl &Filter::getCmdControl() const { return m_cmdControl; }

void Filter::cleanCmdControl() {
  m_cmdControl = CmdControl();
  m_cmdControlIsSet = false;
}

bool Filter::getCmdControlIsSet() const { return m_cmdControlIsSet; }

void Filter::setDataSelectors(
    const std::vector<DataSelectorsPtr> &dataSelectors) {
  m_dataSelectors = dataSelectors;
  m_dataSelectorsIsSet = true;
}

const std::vector<DataSelectorsPtr> &Filter::getDataSelectors() const {
  return m_dataSelectors;
}

void Filter::cleanDataSelectors() {
  m_dataSelectors.clear();
  m_dataSelectorsIsSet = false;
}

bool Filter::getDataSelectorsIsSet() const { return m_dataSelectorsIsSet; }

void Filter::setDataElements(const DataElementsPtr &dataElements) {
  m_dataElements = dataElements;
  m_dataElementsIsSet = (dataElements != nullptr);
}

DataElementsPtr Filter::getDataElements() const { return m_dataElements; }

void Filter::cleanDataElements() {
  m_dataElements = DataElementsPtr();
  m_dataElementsIsSet = false;
}

bool Filter::getDataElementsIsSet() const { return m_dataElementsIsSet; }

bool Filter::getSelectorsListIsSet() const { return getDataSelectorsIsSet(); }

const std::vector<DataSelectorsPtr> &Filter::getSelectorsList() const {
  return getDataSelectors();
}

void Filter::setSelectorsList(
    const std::vector<DataSelectorsPtr> &dataSelectors) {
  setDataSelectors(dataSelectors);
}

bool Filter::getElementIsSet() const { return getDataElementsIsSet(); }

DataElementsPtr Filter::getElement() const { return getDataElements(); }

void Filter::setElement(DataElementsPtr dataElements) {
  setDataElements(dataElements);
}

bool Filter::fromJson(KeoJsonValue *json) {
  if (json->empty()) {
    return true;
  }
  auto iter = json->begin();
  if (iter != json->end() &&
      KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                 "filterId", &m_filterId)) {
    m_filterIdIsSet = true;
    ++iter;
  }
  if (iter != json->end() &&
      KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                 "cmdControl", &m_cmdControl)) {
    m_cmdControlIsSet = true;
    ++iter;
  }
  while (iter != json->end() && (*iter).begin().key().isString()) {
    std::string classname = (*iter).begin().key().asString();
    DataSelectors::Type type = DataSelectors::getTypeFromString(classname);
    if (type != DataSelectors::Type::UNDEFINED) {
      DataSelectorsPtr selector =
          CreateSpineDataClass::createDataSelectors(type);
      if (KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                     classname, selector.get())) {
        m_dataSelectors.push_back(selector);
        m_dataSelectorsIsSet = true;
      }
      ++iter;
    } else {
      break;
    }
  }
  if (iter != json->end() && (*iter).begin().key().isString()) {
    std::string classname = (*iter).begin().key().asString();
    DataElements::Type type = DataElements::getTypeFromString(classname);
    if (type != DataElements::Type::UNDEFINED) {
      m_dataElements = CreateSpineDataClass::createDataElements(type);
      if (KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                     classname, m_dataElements.get())) {
        m_dataElementsIsSet = true;
      }
    }
  }
  return true;
}

std::string Filter::toJson() const {
  std::string result = "[";

  if (m_filterIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("filterId", m_filterId);
  }

  if (m_cmdControlIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("cmdControl", m_cmdControl);
  }

  if (m_dataSelectorsIsSet && !m_dataSelectors.empty()) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    for (const auto &selector : m_dataSelectors) {
      if (selector &&
          selector->getDataType() != DataSelectors::Type::UNDEFINED) {
        KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
        result += KeoJsonTransformation::write(
            DataSelectors::getStringFromType(selector->getDataType()),
            *selector);
      }
    }
  }
  if (m_dataElementsIsSet && m_dataElements &&
      m_dataElements->getDataType() != DataElements::Type::UNDEFINED) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write(
        DataElements::getStringFromType(m_dataElements->getDataType()),
        *m_dataElements);
  }

  result += "]";
  return result;
}

} // namespace keo_datagram