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

#include <keo_datagram/incentivetable/TariffBoundaryRelationData.h>

#include <keo_datagram/incentivetable/TariffBoundaryRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffBoundaryRelationData::TariffBoundaryRelationData()
    : m_tariffIdIsSet(false), m_tariffId(0), m_boundaryIdIsSet(false),
      m_boundaryId(std::vector<xs_unsignedInt>())

{}

TariffBoundaryRelationData::TariffBoundaryRelationData(
    const xs_unsignedInt &c_tariffId,
    const std::vector<xs_unsignedInt> &c_boundaryId)
    : m_tariffIdIsSet(true), m_tariffId(c_tariffId), m_boundaryIdIsSet(true),
      m_boundaryId(c_boundaryId)

{}

bool TariffBoundaryRelationData::
operator==(const TariffBoundaryRelationData &c_classObject) const {
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

bool TariffBoundaryRelationData::
operator!=(const TariffBoundaryRelationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffBoundaryRelationData::isEmpty() const {
  return !m_tariffIdIsSet && !m_boundaryIdIsSet;
}

void TariffBoundaryRelationData::setTariffId(const xs_unsignedInt &tariffId) {
  m_tariffId = tariffId;
  m_tariffIdIsSet = true;
}

const xs_unsignedInt &TariffBoundaryRelationData::getTariffId() const {
  return m_tariffId;
}

void TariffBoundaryRelationData::cleanTariffId() {
  m_tariffId = 0;
  m_tariffIdIsSet = false;
}

bool TariffBoundaryRelationData::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffBoundaryRelationData::setBoundaryId(
    const std::vector<xs_unsignedInt> &boundaryId) {
  m_boundaryId = boundaryId;
  m_boundaryIdIsSet = true;
}

const std::vector<xs_unsignedInt> &
TariffBoundaryRelationData::getBoundaryId() const {
  return m_boundaryId;
}

void TariffBoundaryRelationData::cleanBoundaryId() {
  m_boundaryId.clear();
  m_boundaryIdIsSet = false;
}

bool TariffBoundaryRelationData::getBoundaryIdIsSet() const {
  return m_boundaryIdIsSet;
}

TariffBoundaryRelationData TariffBoundaryRelationData::reduce(
    const TariffBoundaryRelationDataElements &elements) const {
  TariffBoundaryRelationData dataOut;
  if (getTariffIdIsSet() && elements.getTariffIdIsSet()) {
    dataOut.setTariffId(getTariffId());
  }
  if (getBoundaryIdIsSet() && elements.getBoundaryIdIsSet()) {
    dataOut.setBoundaryId(getBoundaryId());
  }
  return dataOut;
}

bool TariffBoundaryRelationData::fromJson(KeoJsonValue *json) {
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
    if (iter != json->end() && KeoJsonTransformation::getList<xs_unsignedInt>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryId", &m_boundaryId)) {
      m_boundaryIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffBoundaryRelationData::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariffId", m_tariffId);
  }
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>("boundaryId",
                                                               m_boundaryId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram