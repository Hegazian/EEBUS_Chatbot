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

#include <keo_datagram/actuator/ActuatorSwitchDescriptionData.h>

#include <keo_datagram/actuator/ActuatorSwitchDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ActuatorSwitchDescriptionData::ActuatorSwitchDescriptionData()
    : CmdData(), m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description("")

{}

ActuatorSwitchDescriptionData::ActuatorSwitchDescriptionData(
    const xs_string &c_label, const xs_string &c_description)
    : CmdData(), m_labelIsSet(true), m_label(c_label), m_descriptionIsSet(true),
      m_description(c_description)

{}

bool ActuatorSwitchDescriptionData::
operator==(const ActuatorSwitchDescriptionData &c_classObject) const {
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

bool ActuatorSwitchDescriptionData::
operator!=(const ActuatorSwitchDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ActuatorSwitchDescriptionData::isEmpty() const {
  return !m_labelIsSet && !m_descriptionIsSet;
}

CmdData::Type ActuatorSwitchDescriptionData::getDataType() const {
  return CmdData::Type::ACTUATOR_SWITCH_DESCRIPTION_DATA_TYPE;
}

CmdDataPtr ActuatorSwitchDescriptionData::clone() const {
  return std::make_shared<ActuatorSwitchDescriptionData>(*this);
}

void ActuatorSwitchDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &ActuatorSwitchDescriptionData::getLabel() const {
  return m_label;
}

void ActuatorSwitchDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool ActuatorSwitchDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void ActuatorSwitchDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &ActuatorSwitchDescriptionData::getDescription() const {
  return m_description;
}

void ActuatorSwitchDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool ActuatorSwitchDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

CmdDataPtr ActuatorSwitchDescriptionData::reduce(
    const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      ActuatorSwitchDescriptionDataElementsPtr elements =
          std::dynamic_pointer_cast<ActuatorSwitchDescriptionDataElements>(
              filter.getDataElements());
      if (elements) {
        ActuatorSwitchDescriptionDataPtr dataOut =
            std::make_shared<ActuatorSwitchDescriptionData>();
        // TODO make sure to always set identifier

        if (getLabelIsSet() && elements->getLabelIsSet()) {
          dataOut->setLabel(getLabel());
        }

        if (getDescriptionIsSet() && elements->getDescriptionIsSet()) {
          dataOut->setDescription(getDescription());
        }

        return dataOut;
      } else {
        return std::make_shared<ActuatorSwitchDescriptionData>(*this);
      }
    } else {
      return std::make_shared<ActuatorSwitchDescriptionData>(*this);
    }
  } else {
    return std::make_shared<ActuatorSwitchDescriptionData>(*this);
  }
}

bool ActuatorSwitchDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
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

std::string ActuatorSwitchDescriptionData::toJson() const {
  std::string result = "[";
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