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

#include <keo_datagram/incentivetable/TierDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierDescriptionDataElements::TierDescriptionDataElements()
    : DataElements(), m_tierIdIsSet(false), m_tierTypeIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool TierDescriptionDataElements::
operator==(const TierDescriptionDataElements &c_classObject) const {
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet) {
    return false;
  }
  if (m_tierTypeIsSet != c_classObject.m_tierTypeIsSet) {
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

bool TierDescriptionDataElements::
operator!=(const TierDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierDescriptionDataElements::isEmpty() const {
  return !m_tierIdIsSet && !m_tierTypeIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

DataElements::Type TierDescriptionDataElements::getDataType() const {
  return DataElements::Type::TIER_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TierDescriptionDataElements::clone() const {
  return std::make_shared<TierDescriptionDataElements>(*this);
}

void TierDescriptionDataElements::setTierId() { m_tierIdIsSet = true; }

void TierDescriptionDataElements::cleanTierId() { m_tierIdIsSet = false; }

bool TierDescriptionDataElements::getTierIdIsSet() const {
  return m_tierIdIsSet;
}

void TierDescriptionDataElements::setTierType() { m_tierTypeIsSet = true; }

void TierDescriptionDataElements::cleanTierType() { m_tierTypeIsSet = false; }

bool TierDescriptionDataElements::getTierTypeIsSet() const {
  return m_tierTypeIsSet;
}

void TierDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void TierDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool TierDescriptionDataElements::getLabelIsSet() const { return m_labelIsSet; }

void TierDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void TierDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool TierDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool TierDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tierId", "tierType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tierId")) {
      m_tierIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tierType")) {
      m_tierTypeIsSet = true;
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

std::string TierDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tierId");
  }
  if (m_tierTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tierType");
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