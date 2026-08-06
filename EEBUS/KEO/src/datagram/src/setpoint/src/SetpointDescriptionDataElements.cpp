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

#include <keo_datagram/setpoint/SetpointDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointDescriptionDataElements::SetpointDescriptionDataElements()
    : DataElements(), m_setpointIdIsSet(false), m_measurementIdIsSet(false),
      m_timeTableIdIsSet(false), m_setpointTypeIsSet(false), m_unitIsSet(false),
      m_scopeTypeIsSet(false), m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool SetpointDescriptionDataElements::
operator==(const SetpointDescriptionDataElements &c_classObject) const {
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet) {
    return false;
  }
  if (m_setpointTypeIsSet != c_classObject.m_setpointTypeIsSet) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet) {
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

bool SetpointDescriptionDataElements::
operator!=(const SetpointDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointDescriptionDataElements::isEmpty() const {
  return !m_setpointIdIsSet && !m_measurementIdIsSet && !m_timeTableIdIsSet &&
         !m_setpointTypeIsSet && !m_unitIsSet && !m_scopeTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type SetpointDescriptionDataElements::getDataType() const {
  return DataElements::Type::SETPOINT_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SetpointDescriptionDataElements::clone() const {
  return std::make_shared<SetpointDescriptionDataElements>(*this);
}

void SetpointDescriptionDataElements::setSetpointId() {
  m_setpointIdIsSet = true;
}

void SetpointDescriptionDataElements::cleanSetpointId() {
  m_setpointIdIsSet = false;
}

bool SetpointDescriptionDataElements::getSetpointIdIsSet() const {
  return m_setpointIdIsSet;
}

void SetpointDescriptionDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void SetpointDescriptionDataElements::cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool SetpointDescriptionDataElements::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void SetpointDescriptionDataElements::setTimeTableId() {
  m_timeTableIdIsSet = true;
}

void SetpointDescriptionDataElements::cleanTimeTableId() {
  m_timeTableIdIsSet = false;
}

bool SetpointDescriptionDataElements::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void SetpointDescriptionDataElements::setSetpointType() {
  m_setpointTypeIsSet = true;
}

void SetpointDescriptionDataElements::cleanSetpointType() {
  m_setpointTypeIsSet = false;
}

bool SetpointDescriptionDataElements::getSetpointTypeIsSet() const {
  return m_setpointTypeIsSet;
}

void SetpointDescriptionDataElements::setUnit() { m_unitIsSet = true; }

void SetpointDescriptionDataElements::cleanUnit() { m_unitIsSet = false; }

bool SetpointDescriptionDataElements::getUnitIsSet() const {
  return m_unitIsSet;
}

void SetpointDescriptionDataElements::setScopeType() {
  m_scopeTypeIsSet = true;
}

void SetpointDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool SetpointDescriptionDataElements::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void SetpointDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void SetpointDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool SetpointDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void SetpointDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void SetpointDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool SetpointDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool SetpointDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"setpointId", "measurementId", "timeTableId", "setpointType",
                   "unit", "scopeType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "setpointId")) {
      m_setpointIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "measurementId")) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeTableId")) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "setpointType")) {
      m_setpointTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "unit")) {
      m_unitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scopeType")) {
      m_scopeTypeIsSet = true;
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

std::string SetpointDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("setpointId");
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeTableId");
  }
  if (m_setpointTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("setpointType");
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("unit");
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scopeType");
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