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

#include <keo_datagram/core/ResultData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ResultData::ResultData()
    : CmdData(), m_errorNumberIsSet(false), m_errorNumber(0),
      m_descriptionIsSet(false), m_description("")

{}

ResultData::ResultData(const xs_unsignedInt &c_errorNumber,
                       const xs_string &c_description)
    : CmdData(), m_errorNumberIsSet(true), m_errorNumber(c_errorNumber),
      m_descriptionIsSet(true), m_description(c_description)

{}

bool ResultData::operator==(const ResultData &c_classObject) const {
  if (m_errorNumberIsSet != c_classObject.m_errorNumberIsSet ||
      (m_errorNumberIsSet && (m_errorNumber != c_classObject.m_errorNumber))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool ResultData::operator!=(const ResultData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ResultData::isEmpty() const {
  return !m_errorNumberIsSet && !m_descriptionIsSet;
}

CmdData::Type ResultData::getDataType() const {
  return CmdData::Type::RESULT_DATA_TYPE;
}

CmdDataPtr ResultData::clone() const {
  return std::make_shared<ResultData>(*this);
}

void ResultData::setErrorNumber(const xs_unsignedInt &errorNumber) {
  m_errorNumber = errorNumber;
  m_errorNumberIsSet = true;
}

const xs_unsignedInt &ResultData::getErrorNumber() const {
  return m_errorNumber;
}

void ResultData::cleanErrorNumber() {
  m_errorNumber = 0;
  m_errorNumberIsSet = false;
}

bool ResultData::getErrorNumberIsSet() const { return m_errorNumberIsSet; }

void ResultData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &ResultData::getDescription() const { return m_description; }

void ResultData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool ResultData::getDescriptionIsSet() const { return m_descriptionIsSet; }

CmdDataPtr ResultData::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<ResultData>(*this);
}

bool ResultData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"errorNumber", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "errorNumber", &m_errorNumber)) {
      m_errorNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ResultData::toJson() const {
  std::string result = "[";
  if (m_errorNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("errorNumber", m_errorNumber);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram