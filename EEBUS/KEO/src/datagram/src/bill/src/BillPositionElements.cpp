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

#include <keo_datagram/bill/BillPositionElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillPositionElements::BillPositionElements()
    : m_positionIdIsSet(false), m_positionTypeIsSet(false),
      m_timePeriodIsSet(false), m_timePeriod(TimePeriodElements()),
      m_valueIsSet(false), m_value(BillValueElements()), m_costIsSet(false),
      m_cost(BillCostElements()), m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool BillPositionElements::
operator==(const BillPositionElements &c_classObject) const {
  if (m_positionIdIsSet != c_classObject.m_positionIdIsSet) {
    return false;
  }
  if (m_positionTypeIsSet != c_classObject.m_positionTypeIsSet) {
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
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool BillPositionElements::
operator!=(const BillPositionElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillPositionElements::isEmpty() const {
  return !m_positionIdIsSet && !m_positionTypeIsSet && !m_timePeriodIsSet &&
         !m_valueIsSet && !m_costIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

void BillPositionElements::setPositionId() { m_positionIdIsSet = true; }

void BillPositionElements::cleanPositionId() { m_positionIdIsSet = false; }

bool BillPositionElements::getPositionIdIsSet() const {
  return m_positionIdIsSet;
}

void BillPositionElements::setPositionType() { m_positionTypeIsSet = true; }

void BillPositionElements::cleanPositionType() { m_positionTypeIsSet = false; }

bool BillPositionElements::getPositionTypeIsSet() const {
  return m_positionTypeIsSet;
}

void BillPositionElements::setTimePeriod(const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &BillPositionElements::getTimePeriod() const {
  return m_timePeriod;
}

void BillPositionElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool BillPositionElements::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

void BillPositionElements::setValue(const BillValueElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const BillValueElements &BillPositionElements::getValue() const {
  return m_value;
}

void BillPositionElements::cleanValue() {
  m_value = BillValueElements();
  m_valueIsSet = false;
}

bool BillPositionElements::getValueIsSet() const { return m_valueIsSet; }

void BillPositionElements::setCost(const BillCostElements &cost) {
  m_cost = cost;
  m_costIsSet = true;
}

const BillCostElements &BillPositionElements::getCost() const { return m_cost; }

void BillPositionElements::cleanCost() {
  m_cost = BillCostElements();
  m_costIsSet = false;
}

bool BillPositionElements::getCostIsSet() const { return m_costIsSet; }

void BillPositionElements::setLabel() { m_labelIsSet = true; }

void BillPositionElements::cleanLabel() { m_labelIsSet = false; }

bool BillPositionElements::getLabelIsSet() const { return m_labelIsSet; }

void BillPositionElements::setDescription() { m_descriptionIsSet = true; }

void BillPositionElements::cleanDescription() { m_descriptionIsSet = false; }

bool BillPositionElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool BillPositionElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"positionId", "positionType", "timePeriod", "value", "cost",
                   "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "positionId")) {
      m_positionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "positionType")) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "cost", &m_cost)) {
      m_costIsSet = true;
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

std::string BillPositionElements::toJson() const {
  std::string result = "[";
  if (m_positionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("positionId");
  }
  if (m_positionTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("positionType");
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  if (m_costIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("cost", m_cost);
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