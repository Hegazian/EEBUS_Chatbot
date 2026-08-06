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

#include <keo_datagram/incentivetable/TariffBoundaryRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffBoundaryRelationDataElements::TariffBoundaryRelationDataElements()
    : DataElements(), m_tariffIdIsSet(false), m_boundaryIdIsSet(false)

{}

TariffBoundaryRelationDataElements::TariffBoundaryRelationDataElements(
    xs_boolean c_tariffIdIsSet, xs_boolean c_boundaryIdIsSet)
    : DataElements(), m_tariffIdIsSet(c_tariffIdIsSet),
      m_boundaryIdIsSet(c_boundaryIdIsSet)

{}

bool TariffBoundaryRelationDataElements::
operator==(const TariffBoundaryRelationDataElements &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet) {
    return false;
  }
  if (m_boundaryIdIsSet != c_classObject.m_boundaryIdIsSet) {
    return false;
  }

  return true;
}

bool TariffBoundaryRelationDataElements::
operator!=(const TariffBoundaryRelationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffBoundaryRelationDataElements::isEmpty() const {
  return !m_tariffIdIsSet && !m_boundaryIdIsSet;
}

DataElements::Type TariffBoundaryRelationDataElements::getDataType() const {
  return DataElements::Type::TARIFF_BOUNDARY_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TariffBoundaryRelationDataElements::clone() const {
  return std::make_shared<TariffBoundaryRelationDataElements>(*this);
}

void TariffBoundaryRelationDataElements::setTariffId() {
  m_tariffIdIsSet = true;
}

void TariffBoundaryRelationDataElements::cleanTariffId() {
  m_tariffIdIsSet = false;
}

bool TariffBoundaryRelationDataElements::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffBoundaryRelationDataElements::setBoundaryId() {
  m_boundaryIdIsSet = true;
}

void TariffBoundaryRelationDataElements::cleanBoundaryId() {
  m_boundaryIdIsSet = false;
}

bool TariffBoundaryRelationDataElements::getBoundaryIdIsSet() const {
  return m_boundaryIdIsSet;
}

bool TariffBoundaryRelationDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tariffId", "boundaryId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tariffId")) {
      m_tariffIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "boundaryId")) {
      m_boundaryIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffBoundaryRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tariffId");
  }
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("boundaryId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram