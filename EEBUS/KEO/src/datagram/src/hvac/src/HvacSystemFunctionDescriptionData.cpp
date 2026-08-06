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

#include <keo_datagram/hvac/HvacSystemFunctionDescriptionData.h>

#include <keo_datagram/hvac/HvacSystemFunctionDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionDescriptionData::HvacSystemFunctionDescriptionData()
    : m_systemFunctionIdIsSet(false), m_systemFunctionId(0),
      m_systemFunctionTypeIsSet(false),
      m_systemFunctionType(HvacSystemFunctionType()), m_labelIsSet(false),
      m_label(""), m_descriptionIsSet(false), m_description("")

{}

bool HvacSystemFunctionDescriptionData::
operator==(const HvacSystemFunctionDescriptionData &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet ||
      (m_systemFunctionIdIsSet &&
       (m_systemFunctionId != c_classObject.m_systemFunctionId))) {
    return false;
  }
  if (m_systemFunctionTypeIsSet != c_classObject.m_systemFunctionTypeIsSet ||
      (m_systemFunctionTypeIsSet &&
       (m_systemFunctionType != c_classObject.m_systemFunctionType))) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionDescriptionData::
operator!=(const HvacSystemFunctionDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionDescriptionData::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_systemFunctionTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

void HvacSystemFunctionDescriptionData::setSystemFunctionId(
    const xs_unsignedInt &systemFunctionId) {
  m_systemFunctionId = systemFunctionId;
  m_systemFunctionIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionDescriptionData::getSystemFunctionId() const {
  return m_systemFunctionId;
}

void HvacSystemFunctionDescriptionData::cleanSystemFunctionId() {
  m_systemFunctionId = 0;
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionDescriptionData::getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionDescriptionData::setSystemFunctionType(
    const HvacSystemFunctionType &systemFunctionType) {
  m_systemFunctionType = systemFunctionType;
  m_systemFunctionTypeIsSet = true;
}

const HvacSystemFunctionType &
HvacSystemFunctionDescriptionData::getSystemFunctionType() const {
  return m_systemFunctionType;
}

void HvacSystemFunctionDescriptionData::cleanSystemFunctionType() {
  m_systemFunctionType = HvacSystemFunctionType();
  m_systemFunctionTypeIsSet = false;
}

bool HvacSystemFunctionDescriptionData::getSystemFunctionTypeIsSet() const {
  return m_systemFunctionTypeIsSet;
}

void HvacSystemFunctionDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &HvacSystemFunctionDescriptionData::getLabel() const {
  return m_label;
}

void HvacSystemFunctionDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool HvacSystemFunctionDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void HvacSystemFunctionDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &HvacSystemFunctionDescriptionData::getDescription() const {
  return m_description;
}

void HvacSystemFunctionDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool HvacSystemFunctionDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

HvacSystemFunctionDescriptionData HvacSystemFunctionDescriptionData::reduce(
    const HvacSystemFunctionDescriptionDataElements &elements) const {
  HvacSystemFunctionDescriptionData dataOut;
  if (getSystemFunctionIdIsSet() && elements.getSystemFunctionIdIsSet()) {
    dataOut.setSystemFunctionId(getSystemFunctionId());
  }
  if (getSystemFunctionTypeIsSet() && elements.getSystemFunctionTypeIsSet()) {
    dataOut.setSystemFunctionType(getSystemFunctionType());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool HvacSystemFunctionDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "systemFunctionType", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "systemFunctionId", &m_systemFunctionId)) {
      m_systemFunctionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "systemFunctionType",
                                   &m_systemFunctionType)) {
      m_systemFunctionTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
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

std::string HvacSystemFunctionDescriptionData::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("systemFunctionId", m_systemFunctionId);
  }
  if (m_systemFunctionTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("systemFunctionType",
                                           m_systemFunctionType);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram