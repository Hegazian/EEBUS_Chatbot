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

#include <keo_datagram/core/DaysOfWeek.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DaysOfWeek::DaysOfWeek()
    : m_mondayIsSet(false), m_tuesdayIsSet(false), m_wednesdayIsSet(false),
      m_thursdayIsSet(false), m_fridayIsSet(false), m_saturdayIsSet(false),
      m_sundayIsSet(false)

{}

bool DaysOfWeek::operator==(const DaysOfWeek &c_classObject) const {
  if (m_mondayIsSet != c_classObject.m_mondayIsSet) {
    return false;
  }
  if (m_tuesdayIsSet != c_classObject.m_tuesdayIsSet) {
    return false;
  }
  if (m_wednesdayIsSet != c_classObject.m_wednesdayIsSet) {
    return false;
  }
  if (m_thursdayIsSet != c_classObject.m_thursdayIsSet) {
    return false;
  }
  if (m_fridayIsSet != c_classObject.m_fridayIsSet) {
    return false;
  }
  if (m_saturdayIsSet != c_classObject.m_saturdayIsSet) {
    return false;
  }
  if (m_sundayIsSet != c_classObject.m_sundayIsSet) {
    return false;
  }

  return true;
}

bool DaysOfWeek::operator!=(const DaysOfWeek &c_classObject) const {
  return !(*this == c_classObject);
}

bool DaysOfWeek::isEmpty() const {
  return !m_mondayIsSet && !m_tuesdayIsSet && !m_wednesdayIsSet &&
         !m_thursdayIsSet && !m_fridayIsSet && !m_saturdayIsSet &&
         !m_sundayIsSet;
}

void DaysOfWeek::setMonday() { m_mondayIsSet = true; }

void DaysOfWeek::cleanMonday() { m_mondayIsSet = false; }

bool DaysOfWeek::getMondayIsSet() const { return m_mondayIsSet; }

void DaysOfWeek::setTuesday() { m_tuesdayIsSet = true; }

void DaysOfWeek::cleanTuesday() { m_tuesdayIsSet = false; }

bool DaysOfWeek::getTuesdayIsSet() const { return m_tuesdayIsSet; }

void DaysOfWeek::setWednesday() { m_wednesdayIsSet = true; }

void DaysOfWeek::cleanWednesday() { m_wednesdayIsSet = false; }

bool DaysOfWeek::getWednesdayIsSet() const { return m_wednesdayIsSet; }

void DaysOfWeek::setThursday() { m_thursdayIsSet = true; }

void DaysOfWeek::cleanThursday() { m_thursdayIsSet = false; }

bool DaysOfWeek::getThursdayIsSet() const { return m_thursdayIsSet; }

void DaysOfWeek::setFriday() { m_fridayIsSet = true; }

void DaysOfWeek::cleanFriday() { m_fridayIsSet = false; }

bool DaysOfWeek::getFridayIsSet() const { return m_fridayIsSet; }

void DaysOfWeek::setSaturday() { m_saturdayIsSet = true; }

void DaysOfWeek::cleanSaturday() { m_saturdayIsSet = false; }

bool DaysOfWeek::getSaturdayIsSet() const { return m_saturdayIsSet; }

void DaysOfWeek::setSunday() { m_sundayIsSet = true; }

void DaysOfWeek::cleanSunday() { m_sundayIsSet = false; }

bool DaysOfWeek::getSundayIsSet() const { return m_sundayIsSet; }

bool DaysOfWeek::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"monday", "tuesday", "wednesday", "thursday", "friday",
                   "saturday", "sunday"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "monday")) {
      m_mondayIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tuesday")) {
      m_tuesdayIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "wednesday")) {
      m_wednesdayIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "thursday")) {
      m_thursdayIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "friday")) {
      m_fridayIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "saturday")) {
      m_saturdayIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sunday")) {
      m_sundayIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DaysOfWeek::toJson() const {
  std::string result = "[";
  if (m_mondayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("monday");
  }
  if (m_tuesdayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tuesday");
  }
  if (m_wednesdayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("wednesday");
  }
  if (m_thursdayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thursday");
  }
  if (m_fridayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("friday");
  }
  if (m_saturdayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("saturday");
  }
  if (m_sundayIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sunday");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram