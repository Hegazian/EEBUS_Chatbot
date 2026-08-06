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

#include <keo_datagram/incentivetable/TierDescriptionData.h>

#include <keo_datagram/incentivetable/TierDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierDescriptionData::TierDescriptionData()
    : m_tierIdIsSet(false), m_tierId(0), m_tierTypeIsSet(false),
      m_tierType(TierType()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool TierDescriptionData::
operator==(const TierDescriptionData &c_classObject) const {
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet ||
      (m_tierIdIsSet && (m_tierId != c_classObject.m_tierId))) {
    return false;
  }
  if (m_tierTypeIsSet != c_classObject.m_tierTypeIsSet ||
      (m_tierTypeIsSet && (m_tierType != c_classObject.m_tierType))) {
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

bool TierDescriptionData::
operator!=(const TierDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierDescriptionData::isEmpty() const {
  return !m_tierIdIsSet && !m_tierTypeIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

void TierDescriptionData::setTierId(const xs_unsignedInt &tierId) {
  m_tierId = tierId;
  m_tierIdIsSet = true;
}

const xs_unsignedInt &TierDescriptionData::getTierId() const {
  return m_tierId;
}

void TierDescriptionData::cleanTierId() {
  m_tierId = 0;
  m_tierIdIsSet = false;
}

bool TierDescriptionData::getTierIdIsSet() const { return m_tierIdIsSet; }

void TierDescriptionData::setTierType(const TierType &tierType) {
  m_tierType = tierType;
  m_tierTypeIsSet = true;
}

const TierType &TierDescriptionData::getTierType() const { return m_tierType; }

void TierDescriptionData::cleanTierType() {
  m_tierType = TierType();
  m_tierTypeIsSet = false;
}

bool TierDescriptionData::getTierTypeIsSet() const { return m_tierTypeIsSet; }

void TierDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &TierDescriptionData::getLabel() const { return m_label; }

void TierDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool TierDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void TierDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &TierDescriptionData::getDescription() const {
  return m_description;
}

void TierDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool TierDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

TierDescriptionData
TierDescriptionData::reduce(const TierDescriptionDataElements &elements) const {
  TierDescriptionData dataOut;
  if (getTierIdIsSet() && elements.getTierIdIsSet()) {
    dataOut.setTierId(getTierId());
  }
  if (getTierTypeIsSet() && elements.getTierTypeIsSet()) {
    dataOut.setTierType(getTierType());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool TierDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tierId", "tierType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tierId", &m_tierId)) {
      m_tierIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tierType", &m_tierType)) {
      m_tierTypeIsSet = true;
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

std::string TierDescriptionData::toJson() const {
  std::string result = "[";
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tierId", m_tierId);
  }
  if (m_tierTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tierType", m_tierType);
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