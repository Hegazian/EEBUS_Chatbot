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

#include <keo_datagram/hvac/HvacOperationModeDescriptionData.h>

#include <keo_datagram/hvac/HvacOperationModeDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOperationModeDescriptionData::HvacOperationModeDescriptionData()
    : m_operationModeIdIsSet(false), m_operationModeId(0),
      m_operationModeTypeIsSet(false),
      m_operationModeType(HvacOperationModeType()), m_labelIsSet(false),
      m_label(""), m_descriptionIsSet(false), m_description("")

{}

bool HvacOperationModeDescriptionData::
operator==(const HvacOperationModeDescriptionData &c_classObject) const {
  if (m_operationModeIdIsSet != c_classObject.m_operationModeIdIsSet ||
      (m_operationModeIdIsSet &&
       (m_operationModeId != c_classObject.m_operationModeId))) {
    return false;
  }
  if (m_operationModeTypeIsSet != c_classObject.m_operationModeTypeIsSet ||
      (m_operationModeTypeIsSet &&
       (m_operationModeType != c_classObject.m_operationModeType))) {
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

bool HvacOperationModeDescriptionData::
operator!=(const HvacOperationModeDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOperationModeDescriptionData::isEmpty() const {
  return !m_operationModeIdIsSet && !m_operationModeTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

void HvacOperationModeDescriptionData::setOperationModeId(
    const xs_unsignedInt &operationModeId) {
  m_operationModeId = operationModeId;
  m_operationModeIdIsSet = true;
}

const xs_unsignedInt &
HvacOperationModeDescriptionData::getOperationModeId() const {
  return m_operationModeId;
}

void HvacOperationModeDescriptionData::cleanOperationModeId() {
  m_operationModeId = 0;
  m_operationModeIdIsSet = false;
}

bool HvacOperationModeDescriptionData::getOperationModeIdIsSet() const {
  return m_operationModeIdIsSet;
}

void HvacOperationModeDescriptionData::setOperationModeType(
    const HvacOperationModeType &operationModeType) {
  m_operationModeType = operationModeType;
  m_operationModeTypeIsSet = true;
}

const HvacOperationModeType &
HvacOperationModeDescriptionData::getOperationModeType() const {
  return m_operationModeType;
}

void HvacOperationModeDescriptionData::cleanOperationModeType() {
  m_operationModeType = HvacOperationModeType();
  m_operationModeTypeIsSet = false;
}

bool HvacOperationModeDescriptionData::getOperationModeTypeIsSet() const {
  return m_operationModeTypeIsSet;
}

void HvacOperationModeDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &HvacOperationModeDescriptionData::getLabel() const {
  return m_label;
}

void HvacOperationModeDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool HvacOperationModeDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void HvacOperationModeDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &HvacOperationModeDescriptionData::getDescription() const {
  return m_description;
}

void HvacOperationModeDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool HvacOperationModeDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

HvacOperationModeDescriptionData HvacOperationModeDescriptionData::reduce(
    const HvacOperationModeDescriptionDataElements &elements) const {
  HvacOperationModeDescriptionData dataOut;
  if (getOperationModeIdIsSet() && elements.getOperationModeIdIsSet()) {
    dataOut.setOperationModeId(getOperationModeId());
  }
  if (getOperationModeTypeIsSet() && elements.getOperationModeTypeIsSet()) {
    dataOut.setOperationModeType(getOperationModeType());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool HvacOperationModeDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"operationModeId", "operationModeType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "operationModeId", &m_operationModeId)) {
      m_operationModeIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "operationModeType", &m_operationModeType)) {
      m_operationModeTypeIsSet = true;
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

std::string HvacOperationModeDescriptionData::toJson() const {
  std::string result = "[";
  if (m_operationModeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("operationModeId", m_operationModeId);
  }
  if (m_operationModeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("operationModeType", m_operationModeType);
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