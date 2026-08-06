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

#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitDescriptionListDataSelectors::
    LoadControlLimitDescriptionListDataSelectors()
    : DataSelectors(), m_limitIdIsSet(false), m_limitId(0),
      m_limitTypeIsSet(false), m_limitType(LoadControlLimitType()),
      m_limitDirectionIsSet(false), m_limitDirection(EnergyDirection()),
      m_measurementIdIsSet(false), m_measurementId(0), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType())

{}

bool LoadControlLimitDescriptionListDataSelectors::operator==(
    const LoadControlLimitDescriptionListDataSelectors &c_classObject) const {
  if (m_limitIdIsSet != c_classObject.m_limitIdIsSet ||
      (m_limitIdIsSet && (m_limitId != c_classObject.m_limitId))) {
    return false;
  }
  if (m_limitTypeIsSet != c_classObject.m_limitTypeIsSet ||
      (m_limitTypeIsSet && (m_limitType != c_classObject.m_limitType))) {
    return false;
  }
  if (m_limitDirectionIsSet != c_classObject.m_limitDirectionIsSet ||
      (m_limitDirectionIsSet &&
       (m_limitDirection != c_classObject.m_limitDirection))) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool LoadControlLimitDescriptionListDataSelectors::operator!=(
    const LoadControlLimitDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitDescriptionListDataSelectors::isEmpty() const {
  return !m_limitIdIsSet && !m_limitTypeIsSet && !m_limitDirectionIsSet &&
         !m_measurementIdIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type
LoadControlLimitDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr LoadControlLimitDescriptionListDataSelectors::clone() const {
  return std::make_shared<LoadControlLimitDescriptionListDataSelectors>(*this);
}

void LoadControlLimitDescriptionListDataSelectors::setLimitId(
    const xs_unsignedInt &limitId) {
  m_limitId = limitId;
  m_limitIdIsSet = true;
}

const xs_unsignedInt &
LoadControlLimitDescriptionListDataSelectors::getLimitId() const {
  return m_limitId;
}

void LoadControlLimitDescriptionListDataSelectors::cleanLimitId() {
  m_limitId = 0;
  m_limitIdIsSet = false;
}

bool LoadControlLimitDescriptionListDataSelectors::getLimitIdIsSet() const {
  return m_limitIdIsSet;
}

void LoadControlLimitDescriptionListDataSelectors::setLimitType(
    const LoadControlLimitType &limitType) {
  m_limitType = limitType;
  m_limitTypeIsSet = true;
}

const LoadControlLimitType &
LoadControlLimitDescriptionListDataSelectors::getLimitType() const {
  return m_limitType;
}

void LoadControlLimitDescriptionListDataSelectors::cleanLimitType() {
  m_limitType = LoadControlLimitType();
  m_limitTypeIsSet = false;
}

bool LoadControlLimitDescriptionListDataSelectors::getLimitTypeIsSet() const {
  return m_limitTypeIsSet;
}

void LoadControlLimitDescriptionListDataSelectors::setLimitDirection(
    const EnergyDirection &limitDirection) {
  m_limitDirection = limitDirection;
  m_limitDirectionIsSet = true;
}

const EnergyDirection &
LoadControlLimitDescriptionListDataSelectors::getLimitDirection() const {
  return m_limitDirection;
}

void LoadControlLimitDescriptionListDataSelectors::cleanLimitDirection() {
  m_limitDirection = EnergyDirection();
  m_limitDirectionIsSet = false;
}

bool LoadControlLimitDescriptionListDataSelectors::getLimitDirectionIsSet()
    const {
  return m_limitDirectionIsSet;
}

void LoadControlLimitDescriptionListDataSelectors::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
LoadControlLimitDescriptionListDataSelectors::getMeasurementId() const {
  return m_measurementId;
}

void LoadControlLimitDescriptionListDataSelectors::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool LoadControlLimitDescriptionListDataSelectors::getMeasurementIdIsSet()
    const {
  return m_measurementIdIsSet;
}

void LoadControlLimitDescriptionListDataSelectors::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &
LoadControlLimitDescriptionListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void LoadControlLimitDescriptionListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool LoadControlLimitDescriptionListDataSelectors::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool LoadControlLimitDescriptionListDataSelectors::selects(
    const LoadControlLimitDescriptionData &data) const {
  if (getLimitIdIsSet() &&
      (!data.getLimitIdIsSet() || getLimitId() != data.getLimitId())) {
    return false;
  }
  if (getLimitTypeIsSet() &&
      (!data.getLimitTypeIsSet() || getLimitType() != data.getLimitType())) {
    return false;
  }
  if (getLimitDirectionIsSet() &&
      (!data.getLimitDirectionIsSet() ||
       getLimitDirection() != data.getLimitDirection())) {
    return false;
  }
  if (getMeasurementIdIsSet() &&
      (!data.getMeasurementIdIsSet() ||
       getMeasurementId() != data.getMeasurementId())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool LoadControlLimitDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"limitId", "limitType", "limitDirection", "measurementId",
                   "scopeType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitId", &m_limitId)) {
      m_limitIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitType", &m_limitType)) {
      m_limitTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitDirection", &m_limitDirection)) {
      m_limitDirectionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
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

std::string LoadControlLimitDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_limitIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitId", m_limitId);
  }
  if (m_limitTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitType", m_limitType);
  }
  if (m_limitDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitDirection", m_limitDirection);
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram