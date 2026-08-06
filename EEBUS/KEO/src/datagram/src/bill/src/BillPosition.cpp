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

#include <keo_datagram/bill/BillPosition.h>

#include <keo_datagram/bill/BillPositionElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillPosition::BillPosition()
    : m_positionIdIsSet(false), m_positionId(0), m_positionTypeIsSet(false),
      m_positionType(BillPositionType()), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriod()), m_valueIsSet(false),
      m_value(std::vector<BillValue>()), m_costIsSet(false),
      m_cost(std::vector<BillCost>()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool BillPosition::operator==(const BillPosition &c_classObject) const {
  if (m_positionIdIsSet != c_classObject.m_positionIdIsSet ||
      (m_positionIdIsSet && (m_positionId != c_classObject.m_positionId))) {
    return false;
  }
  if (m_positionTypeIsSet != c_classObject.m_positionTypeIsSet ||
      (m_positionTypeIsSet &&
       (m_positionType != c_classObject.m_positionType))) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }
  if (m_costIsSet != c_classObject.m_costIsSet ||
      (m_costIsSet && (m_cost != c_classObject.m_cost))) {
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

bool BillPosition::operator!=(const BillPosition &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillPosition::isEmpty() const {
  return !m_positionIdIsSet && !m_positionTypeIsSet && !m_timePeriodIsSet &&
         !m_valueIsSet && !m_costIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

void BillPosition::setPositionId(const xs_unsignedInt &positionId) {
  m_positionId = positionId;
  m_positionIdIsSet = true;
}

const xs_unsignedInt &BillPosition::getPositionId() const {
  return m_positionId;
}

void BillPosition::cleanPositionId() {
  m_positionId = 0;
  m_positionIdIsSet = false;
}

bool BillPosition::getPositionIdIsSet() const { return m_positionIdIsSet; }

void BillPosition::setPositionType(const BillPositionType &positionType) {
  m_positionType = positionType;
  m_positionTypeIsSet = true;
}

const BillPositionType &BillPosition::getPositionType() const {
  return m_positionType;
}

void BillPosition::cleanPositionType() {
  m_positionType = BillPositionType();
  m_positionTypeIsSet = false;
}

bool BillPosition::getPositionTypeIsSet() const { return m_positionTypeIsSet; }

void BillPosition::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &BillPosition::getTimePeriod() const { return m_timePeriod; }

void BillPosition::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool BillPosition::getTimePeriodIsSet() const { return m_timePeriodIsSet; }

void BillPosition::setValue(const std::vector<BillValue> &value) {
  m_value = value;
  m_valueIsSet = true;
}

const std::vector<BillValue> &BillPosition::getValue() const { return m_value; }

void BillPosition::cleanValue() {
  m_value.clear();
  m_valueIsSet = false;
}

bool BillPosition::getValueIsSet() const { return m_valueIsSet; }

void BillPosition::setCost(const std::vector<BillCost> &cost) {
  m_cost = cost;
  m_costIsSet = true;
}

const std::vector<BillCost> &BillPosition::getCost() const { return m_cost; }

void BillPosition::cleanCost() {
  m_cost.clear();
  m_costIsSet = false;
}

bool BillPosition::getCostIsSet() const { return m_costIsSet; }

void BillPosition::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &BillPosition::getLabel() const { return m_label; }

void BillPosition::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool BillPosition::getLabelIsSet() const { return m_labelIsSet; }

void BillPosition::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &BillPosition::getDescription() const { return m_description; }

void BillPosition::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool BillPosition::getDescriptionIsSet() const { return m_descriptionIsSet; }

BillPosition BillPosition::reduce(const BillPositionElements &elements) const {
  BillPosition dataOut;
  if (getPositionIdIsSet() && elements.getPositionIdIsSet()) {
    dataOut.setPositionId(getPositionId());
  }
  if (getPositionTypeIsSet() && elements.getPositionTypeIsSet()) {
    dataOut.setPositionType(getPositionType());
  }
  if (getTimePeriodIsSet() && elements.getTimePeriodIsSet()) {
    dataOut.setTimePeriod(getTimePeriod().reduce(elements.getTimePeriod()));
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    std::vector<BillValue> values;
    for (const auto &value : getValue()) {
      values.push_back(value.reduce(elements.getValue()));
    }
    dataOut.setValue(values);
  }
  if (getCostIsSet() && elements.getCostIsSet()) {
    std::vector<BillCost> values;
    for (const auto &value : getCost()) {
      values.push_back(value.reduce(elements.getCost()));
    }
    dataOut.setCost(values);
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool BillPosition::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"positionId", "positionType", "timePeriod", "value", "cost",
                   "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "positionId", &m_positionId)) {
      m_positionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "positionType", &m_positionType)) {
      m_positionTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timePeriod", &m_timePeriod)) {
      m_timePeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<BillValue>(
            static_cast<KeoJsonValue *>(&(*iter)), "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<BillCost>(
            static_cast<KeoJsonValue *>(&(*iter)), "cost", &m_cost)) {
      m_costIsSet = true;
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

std::string BillPosition::toJson() const {
  std::string result = "[";
  if (m_positionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("positionId", m_positionId);
  }
  if (m_positionTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("positionType", m_positionType);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<BillValue>("value", m_value);
  }
  if (m_costIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<BillCost>("cost", m_cost);
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