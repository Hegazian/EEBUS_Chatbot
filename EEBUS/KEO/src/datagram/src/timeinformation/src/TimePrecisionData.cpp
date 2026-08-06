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

#include <keo_datagram/timeinformation/TimePrecisionData.h>

#include <keo_datagram/timeinformation/TimePrecisionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimePrecisionData::TimePrecisionData()
    : CmdData(), m_isSynchronisedIsSet(false), m_isSynchronised(false),
      m_lastSyncAtIsSet(false), m_lastSyncAt(xs_dateTime()),
      m_clockDriftIsSet(false), m_clockDrift(0)

{}

TimePrecisionData::TimePrecisionData(const xs_boolean &c_isSynchronised,
                                     const xs_dateTime &c_lastSyncAt,
                                     const xs_integer &c_clockDrift)
    : CmdData(), m_isSynchronisedIsSet(true),
      m_isSynchronised(c_isSynchronised), m_lastSyncAtIsSet(true),
      m_lastSyncAt(c_lastSyncAt), m_clockDriftIsSet(true),
      m_clockDrift(c_clockDrift)

{}

bool TimePrecisionData::
operator==(const TimePrecisionData &c_classObject) const {
  if (m_isSynchronisedIsSet != c_classObject.m_isSynchronisedIsSet ||
      (m_isSynchronisedIsSet &&
       (m_isSynchronised != c_classObject.m_isSynchronised))) {
    return false;
  }
  if (m_lastSyncAtIsSet != c_classObject.m_lastSyncAtIsSet ||
      (m_lastSyncAtIsSet && (m_lastSyncAt != c_classObject.m_lastSyncAt))) {
    return false;
  }
  if (m_clockDriftIsSet != c_classObject.m_clockDriftIsSet ||
      (m_clockDriftIsSet && (m_clockDrift != c_classObject.m_clockDrift))) {
    return false;
  }

  return true;
}

bool TimePrecisionData::
operator!=(const TimePrecisionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimePrecisionData::isEmpty() const {
  return !m_isSynchronisedIsSet && !m_lastSyncAtIsSet && !m_clockDriftIsSet;
}

CmdData::Type TimePrecisionData::getDataType() const {
  return CmdData::Type::TIME_PRECISION_DATA_TYPE;
}

CmdDataPtr TimePrecisionData::clone() const {
  return std::make_shared<TimePrecisionData>(*this);
}

void TimePrecisionData::setIsSynchronised(const xs_boolean &isSynchronised) {
  m_isSynchronised = isSynchronised;
  m_isSynchronisedIsSet = true;
}

const xs_boolean &TimePrecisionData::getIsSynchronised() const {
  return m_isSynchronised;
}

void TimePrecisionData::cleanIsSynchronised() {
  m_isSynchronised = false;
  m_isSynchronisedIsSet = false;
}

bool TimePrecisionData::getIsSynchronisedIsSet() const {
  return m_isSynchronisedIsSet;
}

void TimePrecisionData::setLastSyncAt(const xs_dateTime &lastSyncAt) {
  m_lastSyncAt = lastSyncAt;
  m_lastSyncAtIsSet = true;
}

const xs_dateTime &TimePrecisionData::getLastSyncAt() const {
  return m_lastSyncAt;
}

void TimePrecisionData::cleanLastSyncAt() {
  m_lastSyncAt = xs_dateTime();
  m_lastSyncAtIsSet = false;
}

bool TimePrecisionData::getLastSyncAtIsSet() const { return m_lastSyncAtIsSet; }

void TimePrecisionData::setClockDrift(const xs_integer &clockDrift) {
  m_clockDrift = clockDrift;
  m_clockDriftIsSet = true;
}

const xs_integer &TimePrecisionData::getClockDrift() const {
  return m_clockDrift;
}

void TimePrecisionData::cleanClockDrift() {
  m_clockDrift = 0;
  m_clockDriftIsSet = false;
}

bool TimePrecisionData::getClockDriftIsSet() const { return m_clockDriftIsSet; }

CmdDataPtr TimePrecisionData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      TimePrecisionDataElementsPtr elements =
          std::dynamic_pointer_cast<TimePrecisionDataElements>(
              filter.getDataElements());
      if (elements) {
        TimePrecisionDataPtr dataOut = std::make_shared<TimePrecisionData>();
        // TODO make sure to always set identifier

        if (getIsSynchronisedIsSet() && elements->getIsSynchronisedIsSet()) {
          dataOut->setIsSynchronised(getIsSynchronised());
        }

        if (getLastSyncAtIsSet() && elements->getLastSyncAtIsSet()) {
          dataOut->setLastSyncAt(getLastSyncAt());
        }

        if (getClockDriftIsSet() && elements->getClockDriftIsSet()) {
          dataOut->setClockDrift(getClockDrift());
        }

        return dataOut;
      } else {
        return std::make_shared<TimePrecisionData>(*this);
      }
    } else {
      return std::make_shared<TimePrecisionData>(*this);
    }
  } else {
    return std::make_shared<TimePrecisionData>(*this);
  }
}

bool TimePrecisionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"isSynchronised", "lastSyncAt", "clockDrift"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isSynchronised", &m_isSynchronised)) {
      m_isSynchronisedIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "lastSyncAt", &m_lastSyncAt)) {
      m_lastSyncAtIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "clockDrift", &m_clockDrift)) {
      m_clockDriftIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimePrecisionData::toJson() const {
  std::string result = "[";
  if (m_isSynchronisedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isSynchronised", m_isSynchronised);
  }
  if (m_lastSyncAtIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("lastSyncAt", m_lastSyncAt);
  }
  if (m_clockDriftIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("clockDrift", m_clockDrift);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram