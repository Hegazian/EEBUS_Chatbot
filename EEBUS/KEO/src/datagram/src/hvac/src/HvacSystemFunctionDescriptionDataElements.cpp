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

#include <keo_datagram/hvac/HvacSystemFunctionDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionDescriptionDataElements::
    HvacSystemFunctionDescriptionDataElements()
    : DataElements(), m_systemFunctionIdIsSet(false),
      m_systemFunctionTypeIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool HvacSystemFunctionDescriptionDataElements::operator==(
    const HvacSystemFunctionDescriptionDataElements &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet) {
    return false;
  }
  if (m_systemFunctionTypeIsSet != c_classObject.m_systemFunctionTypeIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionDescriptionDataElements::operator!=(
    const HvacSystemFunctionDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionDescriptionDataElements::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_systemFunctionTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type
HvacSystemFunctionDescriptionDataElements::getDataType() const {
  return DataElements::Type::
      HVAC_SYSTEM_FUNCTION_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr HvacSystemFunctionDescriptionDataElements::clone() const {
  return std::make_shared<HvacSystemFunctionDescriptionDataElements>(*this);
}

void HvacSystemFunctionDescriptionDataElements::setSystemFunctionId() {
  m_systemFunctionIdIsSet = true;
}

void HvacSystemFunctionDescriptionDataElements::cleanSystemFunctionId() {
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionDescriptionDataElements::getSystemFunctionIdIsSet()
    const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionDescriptionDataElements::setSystemFunctionType() {
  m_systemFunctionTypeIsSet = true;
}

void HvacSystemFunctionDescriptionDataElements::cleanSystemFunctionType() {
  m_systemFunctionTypeIsSet = false;
}

bool HvacSystemFunctionDescriptionDataElements::getSystemFunctionTypeIsSet()
    const {
  return m_systemFunctionTypeIsSet;
}

void HvacSystemFunctionDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void HvacSystemFunctionDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool HvacSystemFunctionDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void HvacSystemFunctionDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void HvacSystemFunctionDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool HvacSystemFunctionDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool HvacSystemFunctionDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "systemFunctionType", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "systemFunctionId")) {
      m_systemFunctionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "systemFunctionType")) {
      m_systemFunctionTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("systemFunctionId");
  }
  if (m_systemFunctionTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("systemFunctionType");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram