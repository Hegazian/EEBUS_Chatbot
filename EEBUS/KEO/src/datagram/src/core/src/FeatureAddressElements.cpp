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

#include <keo_datagram/core/FeatureAddressElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

FeatureAddressElements::FeatureAddressElements()
    : m_deviceIsSet(false), m_entityIsSet(false), m_featureIsSet(false)

{}

FeatureAddressElements::FeatureAddressElements(xs_boolean c_deviceIsSet,
                                               xs_boolean c_entityIsSet,
                                               xs_boolean c_featureIsSet)
    : m_deviceIsSet(c_deviceIsSet), m_entityIsSet(c_entityIsSet),
      m_featureIsSet(c_featureIsSet)

{}

bool FeatureAddressElements::
operator==(const FeatureAddressElements &c_classObject) const {
  if (m_deviceIsSet != c_classObject.m_deviceIsSet) {
    return false;
  }
  if (m_entityIsSet != c_classObject.m_entityIsSet) {
    return false;
  }
  if (m_featureIsSet != c_classObject.m_featureIsSet) {
    return false;
  }

  return true;
}

bool FeatureAddressElements::
operator!=(const FeatureAddressElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool FeatureAddressElements::isEmpty() const {
  return !m_deviceIsSet && !m_entityIsSet && !m_featureIsSet;
}

void FeatureAddressElements::setDevice() { m_deviceIsSet = true; }

void FeatureAddressElements::cleanDevice() { m_deviceIsSet = false; }

bool FeatureAddressElements::getDeviceIsSet() const { return m_deviceIsSet; }

void FeatureAddressElements::setEntity() { m_entityIsSet = true; }

void FeatureAddressElements::cleanEntity() { m_entityIsSet = false; }

bool FeatureAddressElements::getEntityIsSet() const { return m_entityIsSet; }

void FeatureAddressElements::setFeature() { m_featureIsSet = true; }

void FeatureAddressElements::cleanFeature() { m_featureIsSet = false; }

bool FeatureAddressElements::getFeatureIsSet() const { return m_featureIsSet; }

bool FeatureAddressElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"device", "entity", "feature"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "device")) {
      m_deviceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "entity")) {
      m_entityIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "feature")) {
      m_featureIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string FeatureAddressElements::toJson() const {
  std::string result = "[";
  if (m_deviceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("device");
  }
  if (m_entityIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("entity");
  }
  if (m_featureIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("feature");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram