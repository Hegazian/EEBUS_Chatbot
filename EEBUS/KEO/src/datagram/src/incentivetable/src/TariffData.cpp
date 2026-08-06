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

#include <keo_datagram/incentivetable/TariffData.h>

#include <keo_datagram/incentivetable/TariffDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffData::TariffData()
    : m_tariffIdIsSet(false), m_tariffId(0), m_activeTierIdIsSet(false),
      m_activeTierId(std::vector<xs_unsignedInt>())

{}

TariffData::TariffData(const xs_unsignedInt &c_tariffId,
                       const std::vector<xs_unsignedInt> &c_activeTierId)
    : m_tariffIdIsSet(true), m_tariffId(c_tariffId), m_activeTierIdIsSet(true),
      m_activeTierId(c_activeTierId)

{}

bool TariffData::operator==(const TariffData &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet ||
      (m_tariffIdIsSet && (m_tariffId != c_classObject.m_tariffId))) {
    return false;
  }
  if (m_activeTierIdIsSet != c_classObject.m_activeTierIdIsSet ||
      (m_activeTierIdIsSet &&
       (m_activeTierId != c_classObject.m_activeTierId))) {
    return false;
  }

  return true;
}

bool TariffData::operator!=(const TariffData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffData::isEmpty() const {
  return !m_tariffIdIsSet && !m_activeTierIdIsSet;
}

void TariffData::setTariffId(const xs_unsignedInt &tariffId) {
  m_tariffId = tariffId;
  m_tariffIdIsSet = true;
}

const xs_unsignedInt &TariffData::getTariffId() const { return m_tariffId; }

void TariffData::cleanTariffId() {
  m_tariffId = 0;
  m_tariffIdIsSet = false;
}

bool TariffData::getTariffIdIsSet() const { return m_tariffIdIsSet; }

void TariffData::setActiveTierId(
    const std::vector<xs_unsignedInt> &activeTierId) {
  m_activeTierId = activeTierId;
  m_activeTierIdIsSet = true;
}

const std::vector<xs_unsignedInt> &TariffData::getActiveTierId() const {
  return m_activeTierId;
}

void TariffData::cleanActiveTierId() {
  m_activeTierId.clear();
  m_activeTierIdIsSet = false;
}

bool TariffData::getActiveTierIdIsSet() const { return m_activeTierIdIsSet; }

TariffData TariffData::reduce(const TariffDataElements &elements) const {
  TariffData dataOut;
  if (getTariffIdIsSet() && elements.getTariffIdIsSet()) {
    dataOut.setTariffId(getTariffId());
  }
  if (getActiveTierIdIsSet() && elements.getActiveTierIdIsSet()) {
    dataOut.setActiveTierId(getActiveTierId());
  }
  return dataOut;
}

bool TariffData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tariffId", "activeTierId"})) {
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
                                   "activeTierId", &m_activeTierId)) {
      m_activeTierIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffData::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tariffId", m_tariffId);
  }
  if (m_activeTierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>("activeTierId",
                                                               m_activeTierId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram