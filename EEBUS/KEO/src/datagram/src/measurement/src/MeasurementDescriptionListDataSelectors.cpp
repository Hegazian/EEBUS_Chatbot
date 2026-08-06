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

#include <keo_datagram/measurement/MeasurementDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementDescriptionListDataSelectors::
    MeasurementDescriptionListDataSelectors()
    : DataSelectors(), m_measurementIdIsSet(false), m_measurementId(0),
      m_measurementTypeIsSet(false), m_measurementType(MeasurementType()),
      m_commodityTypeIsSet(false), m_commodityType(CommodityType()),
      m_scopeTypeIsSet(false), m_scopeType(ScopeType())

{}

bool MeasurementDescriptionListDataSelectors::
operator==(const MeasurementDescriptionListDataSelectors &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_measurementTypeIsSet != c_classObject.m_measurementTypeIsSet ||
      (m_measurementTypeIsSet &&
       (m_measurementType != c_classObject.m_measurementType))) {
    return false;
  }
  if (m_commodityTypeIsSet != c_classObject.m_commodityTypeIsSet ||
      (m_commodityTypeIsSet &&
       (m_commodityType != c_classObject.m_commodityType))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool MeasurementDescriptionListDataSelectors::
operator!=(const MeasurementDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementDescriptionListDataSelectors::isEmpty() const {
  return !m_measurementIdIsSet && !m_measurementTypeIsSet &&
         !m_commodityTypeIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type
MeasurementDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr MeasurementDescriptionListDataSelectors::clone() const {
  return std::make_shared<MeasurementDescriptionListDataSelectors>(*this);
}

void MeasurementDescriptionListDataSelectors::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
MeasurementDescriptionListDataSelectors::getMeasurementId() const {
  return m_measurementId;
}

void MeasurementDescriptionListDataSelectors::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool MeasurementDescriptionListDataSelectors::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementDescriptionListDataSelectors::setMeasurementType(
    const MeasurementType &measurementType) {
  m_measurementType = measurementType;
  m_measurementTypeIsSet = true;
}

const MeasurementType &
MeasurementDescriptionListDataSelectors::getMeasurementType() const {
  return m_measurementType;
}

void MeasurementDescriptionListDataSelectors::cleanMeasurementType() {
  m_measurementType = MeasurementType();
  m_measurementTypeIsSet = false;
}

bool MeasurementDescriptionListDataSelectors::getMeasurementTypeIsSet() const {
  return m_measurementTypeIsSet;
}

void MeasurementDescriptionListDataSelectors::setCommodityType(
    const CommodityType &commodityType) {
  m_commodityType = commodityType;
  m_commodityTypeIsSet = true;
}

const CommodityType &
MeasurementDescriptionListDataSelectors::getCommodityType() const {
  return m_commodityType;
}

void MeasurementDescriptionListDataSelectors::cleanCommodityType() {
  m_commodityType = CommodityType();
  m_commodityTypeIsSet = false;
}

bool MeasurementDescriptionListDataSelectors::getCommodityTypeIsSet() const {
  return m_commodityTypeIsSet;
}

void MeasurementDescriptionListDataSelectors::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &MeasurementDescriptionListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void MeasurementDescriptionListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool MeasurementDescriptionListDataSelectors::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool MeasurementDescriptionListDataSelectors::selects(
    const MeasurementDescriptionData &data) const {
  if (getMeasurementIdIsSet() &&
      (!data.getMeasurementIdIsSet() ||
       getMeasurementId() != data.getMeasurementId())) {
    return false;
  }
  if (getMeasurementTypeIsSet() &&
      (!data.getMeasurementTypeIsSet() ||
       getMeasurementType() != data.getMeasurementType())) {
    return false;
  }
  if (getCommodityTypeIsSet() &&
      (!data.getCommodityTypeIsSet() ||
       getCommodityType() != data.getCommodityType())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool MeasurementDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "measurementType", "commodityType",
                   "scopeType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementType", &m_measurementType)) {
      m_measurementTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "commodityType", &m_commodityType)) {
      m_commodityTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_measurementTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("measurementType", m_measurementType);
  }
  if (m_commodityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("commodityType", m_commodityType);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram