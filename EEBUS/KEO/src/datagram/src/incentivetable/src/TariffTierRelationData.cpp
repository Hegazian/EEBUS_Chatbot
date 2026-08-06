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

#include <keo_datagram/incentivetable/TariffTierRelationData.h>

#include <keo_datagram/incentivetable/TariffTierRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffTierRelationData::TariffTierRelationData()
    : m_tariffIdIsSet(false), m_tariffId(0), m_tierIdIsSet(false),
      m_tierId(std::vector<xs_unsignedInt>())

{}

TariffTierRelationData::TariffTierRelationData(
    const xs_unsignedInt &c_tariffId,
    const std::vector<xs_unsignedInt> &c_tierId)
    : m_tariffIdIsSet(true), m_tariffId(c_tariffId), m_tierIdIsSet(true),
      m_tierId(c_tierId)

{}

bool TariffTierRelationData::
operator==(const TariffTierRelationData &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet ||
      (m_tariffIdIsSet && (m_tariffId != c_classObject.m_tariffId))) {
    return false;
  }
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet ||
      (m_tierIdIsSet && (m_tierId != c_classObject.m_tierId))) {
    return false;
  }

  return true;
}

bool TariffTierRelationData::
operator!=(const TariffTierRelationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffTierRelationData::isEmpty() const {
  return !m_tariffIdIsSet && !m_tierIdIsSet;
}

void TariffTierRelationData::setTariffId(const xs_unsignedInt &tariffId) {
  m_tariffId = tariffId;
  m_tariffIdIsSet = true;
}

const xs_unsignedInt &TariffTierRelationData::getTariffId() const {
  return m_tariffId;
}

void TariffTierRelationData::cleanTariffId() {
  m_tariffId = 0;
  m_tariffIdIsSet = false;
}

bool TariffTierRelationData::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffTierRelationData::setTierId(
    const std::vector<xs_unsignedInt> &tierId) {
  m_tierId = tierId;
  m_tierIdIsSet = true;
}

const std::vector<xs_unsignedInt> &TariffTierRelationData::getTierId() const {
  return m_tierId;
}

void TariffTierRelationData::cleanTierId() {
  m_tierId.clear();
  m_tierIdIsSet = false;
}

bool TariffTierRelationData::getTierIdIsSet() const { return m_tierIdIsSet; }

TariffTierRelationData TariffTierRelationData::reduce(
    const TariffTierRelationDataElements &elements) const {
  TariffTierRelationData dataOut;
  if (getTariffIdIsSet() && elements.getTariffIdIsSet()) {
    dataOut.setTariffId(getTariffId());
  }
  if (getTierIdIsSet() && elements.getTierIdIsSet()) {
    dataOut.setTierId(getTierId());
  }
  return dataOut;
}

bool TariffTierRelationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tariffId", "tierId"})) {
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
        KeoJsonTransformation::getList<xs_unsignedInt>(
            static_cast<KeoJsonValue *>(&(*iter)), "tierId", &m_tierId)) {
      m_tierIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffTierRelationData::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariffId", m_tariffId);
  }
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<xs_unsignedInt>("tierId", m_tierId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram