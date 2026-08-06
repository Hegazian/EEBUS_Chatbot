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

#include <keo_datagram/incentivetable/TariffBoundaryRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffBoundaryRelationListDataSelectors::
    TariffBoundaryRelationListDataSelectors()
    : DataSelectors(), m_tariffIdIsSet(false), m_tariffId(0),
      m_boundaryIdIsSet(false), m_boundaryId(0)

{}

TariffBoundaryRelationListDataSelectors::
    TariffBoundaryRelationListDataSelectors(const xs_unsignedInt &c_tariffId,
                                            const xs_unsignedInt &c_boundaryId)
    : DataSelectors(), m_tariffIdIsSet(true), m_tariffId(c_tariffId),
      m_boundaryIdIsSet(true), m_boundaryId(c_boundaryId)

{}

bool TariffBoundaryRelationListDataSelectors::
operator==(const TariffBoundaryRelationListDataSelectors &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet ||
      (m_tariffIdIsSet && (m_tariffId != c_classObject.m_tariffId))) {
    return false;
  }
  if (m_boundaryIdIsSet != c_classObject.m_boundaryIdIsSet ||
      (m_boundaryIdIsSet && (m_boundaryId != c_classObject.m_boundaryId))) {
    return false;
  }

  return true;
}

bool TariffBoundaryRelationListDataSelectors::
operator!=(const TariffBoundaryRelationListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffBoundaryRelationListDataSelectors::isEmpty() const {
  return !m_tariffIdIsSet && !m_boundaryIdIsSet;
}

DataSelectors::Type
TariffBoundaryRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TariffBoundaryRelationListDataSelectors::clone() const {
  return std::make_shared<TariffBoundaryRelationListDataSelectors>(*this);
}

void TariffBoundaryRelationListDataSelectors::setTariffId(
    const xs_unsignedInt &tariffId) {
  m_tariffId = tariffId;
  m_tariffIdIsSet = true;
}

const xs_unsignedInt &
TariffBoundaryRelationListDataSelectors::getTariffId() const {
  return m_tariffId;
}

void TariffBoundaryRelationListDataSelectors::cleanTariffId() {
  m_tariffId = 0;
  m_tariffIdIsSet = false;
}

bool TariffBoundaryRelationListDataSelectors::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffBoundaryRelationListDataSelectors::setBoundaryId(
    const xs_unsignedInt &boundaryId) {
  m_boundaryId = boundaryId;
  m_boundaryIdIsSet = true;
}

const xs_unsignedInt &
TariffBoundaryRelationListDataSelectors::getBoundaryId() const {
  return m_boundaryId;
}

void TariffBoundaryRelationListDataSelectors::cleanBoundaryId() {
  m_boundaryId = 0;
  m_boundaryIdIsSet = false;
}

bool TariffBoundaryRelationListDataSelectors::getBoundaryIdIsSet() const {
  return m_boundaryIdIsSet;
}

bool TariffBoundaryRelationListDataSelectors::selects(
    const TariffBoundaryRelationData &data) const {
  if (getTariffIdIsSet() &&
      (!data.getTariffIdIsSet() || getTariffId() != data.getTariffId())) {
    return false;
  }
  if (getBoundaryIdIsSet() &&
      (!data.getBoundaryIdIsSet() ||
       std::find(std::begin(data.getBoundaryId()),
                 std::end(data.getBoundaryId()),
                 getBoundaryId()) == std::end(data.getBoundaryId()))) {
    return false;
  }
  return true;
}

bool TariffBoundaryRelationListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tariffId", "boundaryId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariffId", &m_tariffId)) {
      m_tariffIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryId", &m_boundaryId)) {
      m_boundaryIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffBoundaryRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariffId", m_tariffId);
  }
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryId", m_boundaryId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram