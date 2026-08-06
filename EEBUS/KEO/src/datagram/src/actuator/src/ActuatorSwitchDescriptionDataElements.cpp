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

#include <keo_datagram/actuator/ActuatorSwitchDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ActuatorSwitchDescriptionDataElements::ActuatorSwitchDescriptionDataElements()
    : DataElements(), m_labelIsSet(false), m_descriptionIsSet(false)

{}

ActuatorSwitchDescriptionDataElements::ActuatorSwitchDescriptionDataElements(
    xs_boolean c_labelIsSet, xs_boolean c_descriptionIsSet)
    : DataElements(), m_labelIsSet(c_labelIsSet),
      m_descriptionIsSet(c_descriptionIsSet)

{}

bool ActuatorSwitchDescriptionDataElements::
operator==(const ActuatorSwitchDescriptionDataElements &c_classObject) const {
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool ActuatorSwitchDescriptionDataElements::
operator!=(const ActuatorSwitchDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ActuatorSwitchDescriptionDataElements::isEmpty() const {
  return !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type ActuatorSwitchDescriptionDataElements::getDataType() const {
  return DataElements::Type::ACTUATOR_SWITCH_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ActuatorSwitchDescriptionDataElements::clone() const {
  return std::make_shared<ActuatorSwitchDescriptionDataElements>(*this);
}

void ActuatorSwitchDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void ActuatorSwitchDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool ActuatorSwitchDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void ActuatorSwitchDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void ActuatorSwitchDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool ActuatorSwitchDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool ActuatorSwitchDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
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

std::string ActuatorSwitchDescriptionDataElements::toJson() const {
  std::string result = "[";
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