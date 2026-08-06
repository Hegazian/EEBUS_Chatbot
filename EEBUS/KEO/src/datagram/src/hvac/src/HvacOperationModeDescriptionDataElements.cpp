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

#include <keo_datagram/hvac/HvacOperationModeDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOperationModeDescriptionDataElements::
    HvacOperationModeDescriptionDataElements()
    : DataElements(), m_operationModeIdIsSet(false),
      m_operationModeTypeIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool HvacOperationModeDescriptionDataElements::operator==(
    const HvacOperationModeDescriptionDataElements &c_classObject) const {
  if (m_operationModeIdIsSet != c_classObject.m_operationModeIdIsSet) {
    return false;
  }
  if (m_operationModeTypeIsSet != c_classObject.m_operationModeTypeIsSet) {
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

bool HvacOperationModeDescriptionDataElements::operator!=(
    const HvacOperationModeDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOperationModeDescriptionDataElements::isEmpty() const {
  return !m_operationModeIdIsSet && !m_operationModeTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type
HvacOperationModeDescriptionDataElements::getDataType() const {
  return DataElements::Type::HVAC_OPERATION_MODE_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr HvacOperationModeDescriptionDataElements::clone() const {
  return std::make_shared<HvacOperationModeDescriptionDataElements>(*this);
}

void HvacOperationModeDescriptionDataElements::setOperationModeId() {
  m_operationModeIdIsSet = true;
}

void HvacOperationModeDescriptionDataElements::cleanOperationModeId() {
  m_operationModeIdIsSet = false;
}

bool HvacOperationModeDescriptionDataElements::getOperationModeIdIsSet() const {
  return m_operationModeIdIsSet;
}

void HvacOperationModeDescriptionDataElements::setOperationModeType() {
  m_operationModeTypeIsSet = true;
}

void HvacOperationModeDescriptionDataElements::cleanOperationModeType() {
  m_operationModeTypeIsSet = false;
}

bool HvacOperationModeDescriptionDataElements::getOperationModeTypeIsSet()
    const {
  return m_operationModeTypeIsSet;
}

void HvacOperationModeDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void HvacOperationModeDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool HvacOperationModeDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void HvacOperationModeDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void HvacOperationModeDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool HvacOperationModeDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool HvacOperationModeDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"operationModeId", "operationModeType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "operationModeId")) {
      m_operationModeIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "operationModeType")) {
      m_operationModeTypeIsSet = true;
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

std::string HvacOperationModeDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_operationModeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("operationModeId");
  }
  if (m_operationModeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("operationModeType");
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