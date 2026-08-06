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

#include <keo_datagram/hvac/HvacOverrunDescriptionData.h>

#include <keo_datagram/hvac/HvacOverrunDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOverrunDescriptionData::HvacOverrunDescriptionData()
    : m_overrunIdIsSet(false), m_overrunId(0), m_overrunTypeIsSet(false),
      m_overrunType(HvacOverrunType()), m_affectedSystemFunctionIdIsSet(false),
      m_affectedSystemFunctionId(std::vector<xs_unsignedInt>()),
      m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description("")

{}

bool HvacOverrunDescriptionData::
operator==(const HvacOverrunDescriptionData &c_classObject) const {
  if (m_overrunIdIsSet != c_classObject.m_overrunIdIsSet ||
      (m_overrunIdIsSet && (m_overrunId != c_classObject.m_overrunId))) {
    return false;
  }
  if (m_overrunTypeIsSet != c_classObject.m_overrunTypeIsSet ||
      (m_overrunTypeIsSet && (m_overrunType != c_classObject.m_overrunType))) {
    return false;
  }
  if (m_affectedSystemFunctionIdIsSet !=
          c_classObject.m_affectedSystemFunctionIdIsSet ||
      (m_affectedSystemFunctionIdIsSet &&
       (m_affectedSystemFunctionId !=
        c_classObject.m_affectedSystemFunctionId))) {
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

bool HvacOverrunDescriptionData::
operator!=(const HvacOverrunDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOverrunDescriptionData::isEmpty() const {
  return !m_overrunIdIsSet && !m_overrunTypeIsSet &&
         !m_affectedSystemFunctionIdIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

void HvacOverrunDescriptionData::setOverrunId(const xs_unsignedInt &overrunId) {
  m_overrunId = overrunId;
  m_overrunIdIsSet = true;
}

const xs_unsignedInt &HvacOverrunDescriptionData::getOverrunId() const {
  return m_overrunId;
}

void HvacOverrunDescriptionData::cleanOverrunId() {
  m_overrunId = 0;
  m_overrunIdIsSet = false;
}

bool HvacOverrunDescriptionData::getOverrunIdIsSet() const {
  return m_overrunIdIsSet;
}

void HvacOverrunDescriptionData::setOverrunType(
    const HvacOverrunType &overrunType) {
  m_overrunType = overrunType;
  m_overrunTypeIsSet = true;
}

const HvacOverrunType &HvacOverrunDescriptionData::getOverrunType() const {
  return m_overrunType;
}

void HvacOverrunDescriptionData::cleanOverrunType() {
  m_overrunType = HvacOverrunType();
  m_overrunTypeIsSet = false;
}

bool HvacOverrunDescriptionData::getOverrunTypeIsSet() const {
  return m_overrunTypeIsSet;
}

void HvacOverrunDescriptionData::setAffectedSystemFunctionId(
    const std::vector<xs_unsignedInt> &affectedSystemFunctionId) {
  m_affectedSystemFunctionId = affectedSystemFunctionId;
  m_affectedSystemFunctionIdIsSet = true;
}

const std::vector<xs_unsignedInt> &
HvacOverrunDescriptionData::getAffectedSystemFunctionId() const {
  return m_affectedSystemFunctionId;
}

void HvacOverrunDescriptionData::cleanAffectedSystemFunctionId() {
  m_affectedSystemFunctionId.clear();
  m_affectedSystemFunctionIdIsSet = false;
}

bool HvacOverrunDescriptionData::getAffectedSystemFunctionIdIsSet() const {
  return m_affectedSystemFunctionIdIsSet;
}

void HvacOverrunDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &HvacOverrunDescriptionData::getLabel() const {
  return m_label;
}

void HvacOverrunDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool HvacOverrunDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void HvacOverrunDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &HvacOverrunDescriptionData::getDescription() const {
  return m_description;
}

void HvacOverrunDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool HvacOverrunDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

HvacOverrunDescriptionData HvacOverrunDescriptionData::reduce(
    const HvacOverrunDescriptionDataElements &elements) const {
  HvacOverrunDescriptionData dataOut;
  if (getOverrunIdIsSet() && elements.getOverrunIdIsSet()) {
    dataOut.setOverrunId(getOverrunId());
  }
  if (getOverrunTypeIsSet() && elements.getOverrunTypeIsSet()) {
    dataOut.setOverrunType(getOverrunType());
  }
  if (getAffectedSystemFunctionIdIsSet() &&
      elements.getAffectedSystemFunctionIdIsSet()) {
    dataOut.setAffectedSystemFunctionId(getAffectedSystemFunctionId());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool HvacOverrunDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"overrunId", "overrunType", "affectedSystemFunctionId",
                   "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "overrunId", &m_overrunId)) {
      m_overrunIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "overrunType", &m_overrunType)) {
      m_overrunTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<xs_unsignedInt>(
            static_cast<KeoJsonValue *>(&(*iter)), "affectedSystemFunctionId",
            &m_affectedSystemFunctionId)) {
      m_affectedSystemFunctionIdIsSet = true;
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

std::string HvacOverrunDescriptionData::toJson() const {
  std::string result = "[";
  if (m_overrunIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("overrunId", m_overrunId);
  }
  if (m_overrunTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("overrunType", m_overrunType);
  }
  if (m_affectedSystemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>(
        "affectedSystemFunctionId", m_affectedSystemFunctionId);
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