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

#include <keo_datagram/sensing/SensingDescriptionData.h>

#include <keo_datagram/sensing/SensingDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SensingDescriptionData::SensingDescriptionData()
    : CmdData(), m_sensingTypeIsSet(false), m_sensingType(SensingType()),
      m_unitIsSet(false), m_unit(UnitOfMeasurement()), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool SensingDescriptionData::
operator==(const SensingDescriptionData &c_classObject) const {
  if (m_sensingTypeIsSet != c_classObject.m_sensingTypeIsSet ||
      (m_sensingTypeIsSet && (m_sensingType != c_classObject.m_sensingType))) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
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

bool SensingDescriptionData::
operator!=(const SensingDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SensingDescriptionData::isEmpty() const {
  return !m_sensingTypeIsSet && !m_unitIsSet && !m_scopeTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

CmdData::Type SensingDescriptionData::getDataType() const {
  return CmdData::Type::SENSING_DESCRIPTION_DATA_TYPE;
}

CmdDataPtr SensingDescriptionData::clone() const {
  return std::make_shared<SensingDescriptionData>(*this);
}

void SensingDescriptionData::setSensingType(const SensingType &sensingType) {
  m_sensingType = sensingType;
  m_sensingTypeIsSet = true;
}

const SensingType &SensingDescriptionData::getSensingType() const {
  return m_sensingType;
}

void SensingDescriptionData::cleanSensingType() {
  m_sensingType = SensingType();
  m_sensingTypeIsSet = false;
}

bool SensingDescriptionData::getSensingTypeIsSet() const {
  return m_sensingTypeIsSet;
}

void SensingDescriptionData::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &SensingDescriptionData::getUnit() const {
  return m_unit;
}

void SensingDescriptionData::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool SensingDescriptionData::getUnitIsSet() const { return m_unitIsSet; }

void SensingDescriptionData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &SensingDescriptionData::getScopeType() const {
  return m_scopeType;
}

void SensingDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool SensingDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void SensingDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &SensingDescriptionData::getLabel() const { return m_label; }

void SensingDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool SensingDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void SensingDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &SensingDescriptionData::getDescription() const {
  return m_description;
}

void SensingDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool SensingDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

CmdDataPtr
SensingDescriptionData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      SensingDescriptionDataElementsPtr elements =
          std::dynamic_pointer_cast<SensingDescriptionDataElements>(
              filter.getDataElements());
      if (elements) {
        SensingDescriptionDataPtr dataOut =
            std::make_shared<SensingDescriptionData>();
        // TODO make sure to always set identifier

        if (getSensingTypeIsSet() && elements->getSensingTypeIsSet()) {
          dataOut->setSensingType(getSensingType());
        }

        if (getUnitIsSet() && elements->getUnitIsSet()) {
          dataOut->setUnit(getUnit());
        }

        if (getScopeTypeIsSet() && elements->getScopeTypeIsSet()) {
          dataOut->setScopeType(getScopeType());
        }

        if (getLabelIsSet() && elements->getLabelIsSet()) {
          dataOut->setLabel(getLabel());
        }

        if (getDescriptionIsSet() && elements->getDescriptionIsSet()) {
          dataOut->setDescription(getDescription());
        }

        return dataOut;
      } else {
        return std::make_shared<SensingDescriptionData>(*this);
      }
    } else {
      return std::make_shared<SensingDescriptionData>(*this);
    }
  } else {
    return std::make_shared<SensingDescriptionData>(*this);
  }
}

bool SensingDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"sensingType", "unit", "scopeType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sensingType", &m_sensingType)) {
      m_sensingTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "unit", &m_unit)) {
      m_unitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
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

std::string SensingDescriptionData::toJson() const {
  std::string result = "[";
  if (m_sensingTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sensingType", m_sensingType);
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
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