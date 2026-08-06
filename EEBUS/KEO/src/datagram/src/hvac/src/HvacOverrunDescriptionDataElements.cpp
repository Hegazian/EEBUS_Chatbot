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

#include <keo_datagram/hvac/HvacOverrunDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOverrunDescriptionDataElements::HvacOverrunDescriptionDataElements()
    : DataElements(), m_overrunIdIsSet(false), m_overrunTypeIsSet(false),
      m_affectedSystemFunctionIdIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool HvacOverrunDescriptionDataElements::
operator==(const HvacOverrunDescriptionDataElements &c_classObject) const {
  if (m_overrunIdIsSet != c_classObject.m_overrunIdIsSet) {
    return false;
  }
  if (m_overrunTypeIsSet != c_classObject.m_overrunTypeIsSet) {
    return false;
  }
  if (m_affectedSystemFunctionIdIsSet !=
      c_classObject.m_affectedSystemFunctionIdIsSet) {
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

bool HvacOverrunDescriptionDataElements::
operator!=(const HvacOverrunDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOverrunDescriptionDataElements::isEmpty() const {
  return !m_overrunIdIsSet && !m_overrunTypeIsSet &&
         !m_affectedSystemFunctionIdIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

DataElements::Type HvacOverrunDescriptionDataElements::getDataType() const {
  return DataElements::Type::HVAC_OVERRUN_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr HvacOverrunDescriptionDataElements::clone() const {
  return std::make_shared<HvacOverrunDescriptionDataElements>(*this);
}

void HvacOverrunDescriptionDataElements::setOverrunId() {
  m_overrunIdIsSet = true;
}

void HvacOverrunDescriptionDataElements::cleanOverrunId() {
  m_overrunIdIsSet = false;
}

bool HvacOverrunDescriptionDataElements::getOverrunIdIsSet() const {
  return m_overrunIdIsSet;
}

void HvacOverrunDescriptionDataElements::setOverrunType() {
  m_overrunTypeIsSet = true;
}

void HvacOverrunDescriptionDataElements::cleanOverrunType() {
  m_overrunTypeIsSet = false;
}

bool HvacOverrunDescriptionDataElements::getOverrunTypeIsSet() const {
  return m_overrunTypeIsSet;
}

void HvacOverrunDescriptionDataElements::setAffectedSystemFunctionId() {
  m_affectedSystemFunctionIdIsSet = true;
}

void HvacOverrunDescriptionDataElements::cleanAffectedSystemFunctionId() {
  m_affectedSystemFunctionIdIsSet = false;
}

bool HvacOverrunDescriptionDataElements::getAffectedSystemFunctionIdIsSet()
    const {
  return m_affectedSystemFunctionIdIsSet;
}

void HvacOverrunDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void HvacOverrunDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool HvacOverrunDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void HvacOverrunDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void HvacOverrunDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool HvacOverrunDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool HvacOverrunDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"overrunId", "overrunType", "affectedSystemFunctionId",
                   "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "overrunId")) {
      m_overrunIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "overrunType")) {
      m_overrunTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "affectedSystemFunctionId")) {
      m_affectedSystemFunctionIdIsSet = true;
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

std::string HvacOverrunDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_overrunIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("overrunId");
  }
  if (m_overrunTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("overrunType");
  }
  if (m_affectedSystemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("affectedSystemFunctionId");
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