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

#include <keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationData.h>

#include <keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceNodeScheduleInformationData::
    PowerSequenceNodeScheduleInformationData()
    : CmdData(), m_nodeRemoteControllableIsSet(false),
      m_nodeRemoteControllable(false),
      m_supportsSingleSlotSchedulingOnlyIsSet(false),
      m_supportsSingleSlotSchedulingOnly(false),
      m_alternativesCountIsSet(false), m_alternativesCount(0),
      m_totalSequencesCountMaxIsSet(false), m_totalSequencesCountMax(0),
      m_supportsReselectionIsSet(false), m_supportsReselection(false)

{}

bool PowerSequenceNodeScheduleInformationData::operator==(
    const PowerSequenceNodeScheduleInformationData &c_classObject) const {
  if (m_nodeRemoteControllableIsSet !=
          c_classObject.m_nodeRemoteControllableIsSet ||
      (m_nodeRemoteControllableIsSet &&
       (m_nodeRemoteControllable != c_classObject.m_nodeRemoteControllable))) {
    return false;
  }
  if (m_supportsSingleSlotSchedulingOnlyIsSet !=
          c_classObject.m_supportsSingleSlotSchedulingOnlyIsSet ||
      (m_supportsSingleSlotSchedulingOnlyIsSet &&
       (m_supportsSingleSlotSchedulingOnly !=
        c_classObject.m_supportsSingleSlotSchedulingOnly))) {
    return false;
  }
  if (m_alternativesCountIsSet != c_classObject.m_alternativesCountIsSet ||
      (m_alternativesCountIsSet &&
       (m_alternativesCount != c_classObject.m_alternativesCount))) {
    return false;
  }
  if (m_totalSequencesCountMaxIsSet !=
          c_classObject.m_totalSequencesCountMaxIsSet ||
      (m_totalSequencesCountMaxIsSet &&
       (m_totalSequencesCountMax != c_classObject.m_totalSequencesCountMax))) {
    return false;
  }
  if (m_supportsReselectionIsSet != c_classObject.m_supportsReselectionIsSet ||
      (m_supportsReselectionIsSet &&
       (m_supportsReselection != c_classObject.m_supportsReselection))) {
    return false;
  }

  return true;
}

bool PowerSequenceNodeScheduleInformationData::operator!=(
    const PowerSequenceNodeScheduleInformationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceNodeScheduleInformationData::isEmpty() const {
  return !m_nodeRemoteControllableIsSet &&
         !m_supportsSingleSlotSchedulingOnlyIsSet &&
         !m_alternativesCountIsSet && !m_totalSequencesCountMaxIsSet &&
         !m_supportsReselectionIsSet;
}

CmdData::Type PowerSequenceNodeScheduleInformationData::getDataType() const {
  return CmdData::Type::POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_TYPE;
}

CmdDataPtr PowerSequenceNodeScheduleInformationData::clone() const {
  return std::make_shared<PowerSequenceNodeScheduleInformationData>(*this);
}

void PowerSequenceNodeScheduleInformationData::setNodeRemoteControllable(
    const xs_boolean &nodeRemoteControllable) {
  m_nodeRemoteControllable = nodeRemoteControllable;
  m_nodeRemoteControllableIsSet = true;
}

const xs_boolean &
PowerSequenceNodeScheduleInformationData::getNodeRemoteControllable() const {
  return m_nodeRemoteControllable;
}

void PowerSequenceNodeScheduleInformationData::cleanNodeRemoteControllable() {
  m_nodeRemoteControllable = false;
  m_nodeRemoteControllableIsSet = false;
}

bool PowerSequenceNodeScheduleInformationData::getNodeRemoteControllableIsSet()
    const {
  return m_nodeRemoteControllableIsSet;
}

void PowerSequenceNodeScheduleInformationData::
    setSupportsSingleSlotSchedulingOnly(
        const xs_boolean &supportsSingleSlotSchedulingOnly) {
  m_supportsSingleSlotSchedulingOnly = supportsSingleSlotSchedulingOnly;
  m_supportsSingleSlotSchedulingOnlyIsSet = true;
}

const xs_boolean &
PowerSequenceNodeScheduleInformationData::getSupportsSingleSlotSchedulingOnly()
    const {
  return m_supportsSingleSlotSchedulingOnly;
}

void PowerSequenceNodeScheduleInformationData::
    cleanSupportsSingleSlotSchedulingOnly() {
  m_supportsSingleSlotSchedulingOnly = false;
  m_supportsSingleSlotSchedulingOnlyIsSet = false;
}

bool PowerSequenceNodeScheduleInformationData::
    getSupportsSingleSlotSchedulingOnlyIsSet() const {
  return m_supportsSingleSlotSchedulingOnlyIsSet;
}

void PowerSequenceNodeScheduleInformationData::setAlternativesCount(
    const xs_unsignedInt &alternativesCount) {
  m_alternativesCount = alternativesCount;
  m_alternativesCountIsSet = true;
}

const xs_unsignedInt &
PowerSequenceNodeScheduleInformationData::getAlternativesCount() const {
  return m_alternativesCount;
}

void PowerSequenceNodeScheduleInformationData::cleanAlternativesCount() {
  m_alternativesCount = 0;
  m_alternativesCountIsSet = false;
}

bool PowerSequenceNodeScheduleInformationData::getAlternativesCountIsSet()
    const {
  return m_alternativesCountIsSet;
}

void PowerSequenceNodeScheduleInformationData::setTotalSequencesCountMax(
    const xs_unsignedInt &totalSequencesCountMax) {
  m_totalSequencesCountMax = totalSequencesCountMax;
  m_totalSequencesCountMaxIsSet = true;
}

const xs_unsignedInt &
PowerSequenceNodeScheduleInformationData::getTotalSequencesCountMax() const {
  return m_totalSequencesCountMax;
}

void PowerSequenceNodeScheduleInformationData::cleanTotalSequencesCountMax() {
  m_totalSequencesCountMax = 0;
  m_totalSequencesCountMaxIsSet = false;
}

bool PowerSequenceNodeScheduleInformationData::getTotalSequencesCountMaxIsSet()
    const {
  return m_totalSequencesCountMaxIsSet;
}

void PowerSequenceNodeScheduleInformationData::setSupportsReselection(
    const xs_boolean &supportsReselection) {
  m_supportsReselection = supportsReselection;
  m_supportsReselectionIsSet = true;
}

const xs_boolean &
PowerSequenceNodeScheduleInformationData::getSupportsReselection() const {
  return m_supportsReselection;
}

void PowerSequenceNodeScheduleInformationData::cleanSupportsReselection() {
  m_supportsReselection = false;
  m_supportsReselectionIsSet = false;
}

bool PowerSequenceNodeScheduleInformationData::getSupportsReselectionIsSet()
    const {
  return m_supportsReselectionIsSet;
}

CmdDataPtr PowerSequenceNodeScheduleInformationData::reduce(
    const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      PowerSequenceNodeScheduleInformationDataElementsPtr elements =
          std::dynamic_pointer_cast<
              PowerSequenceNodeScheduleInformationDataElements>(
              filter.getDataElements());
      if (elements) {
        PowerSequenceNodeScheduleInformationDataPtr dataOut =
            std::make_shared<PowerSequenceNodeScheduleInformationData>();
        // TODO make sure to always set identifier

        if (getNodeRemoteControllableIsSet() &&
            elements->getNodeRemoteControllableIsSet()) {
          dataOut->setNodeRemoteControllable(getNodeRemoteControllable());
        }

        if (getSupportsSingleSlotSchedulingOnlyIsSet() &&
            elements->getSupportsSingleSlotSchedulingOnlyIsSet()) {
          dataOut->setSupportsSingleSlotSchedulingOnly(
              getSupportsSingleSlotSchedulingOnly());
        }

        if (getAlternativesCountIsSet() &&
            elements->getAlternativesCountIsSet()) {
          dataOut->setAlternativesCount(getAlternativesCount());
        }

        if (getTotalSequencesCountMaxIsSet() &&
            elements->getTotalSequencesCountMaxIsSet()) {
          dataOut->setTotalSequencesCountMax(getTotalSequencesCountMax());
        }

        if (getSupportsReselectionIsSet() &&
            elements->getSupportsReselectionIsSet()) {
          dataOut->setSupportsReselection(getSupportsReselection());
        }

        return dataOut;
      } else {
        return std::make_shared<PowerSequenceNodeScheduleInformationData>(
            *this);
      }
    } else {
      return std::make_shared<PowerSequenceNodeScheduleInformationData>(*this);
    }
  } else {
    return std::make_shared<PowerSequenceNodeScheduleInformationData>(*this);
  }
}

bool PowerSequenceNodeScheduleInformationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"nodeRemoteControllable", "supportsSingleSlotSchedulingOnly",
                   "alternativesCount", "totalSequencesCountMax",
                   "supportsReselection"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "nodeRemoteControllable",
                                   &m_nodeRemoteControllable)) {
      m_nodeRemoteControllableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "supportsSingleSlotSchedulingOnly",
                                   &m_supportsSingleSlotSchedulingOnly)) {
      m_supportsSingleSlotSchedulingOnlyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "alternativesCount", &m_alternativesCount)) {
      m_alternativesCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "totalSequencesCountMax",
                                   &m_totalSequencesCountMax)) {
      m_totalSequencesCountMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "supportsReselection",
                                   &m_supportsReselection)) {
      m_supportsReselectionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceNodeScheduleInformationData::toJson() const {
  std::string result = "[";
  if (m_nodeRemoteControllableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nodeRemoteControllable",
                                           m_nodeRemoteControllable);
  }
  if (m_supportsSingleSlotSchedulingOnlyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("supportsSingleSlotSchedulingOnly",
                                           m_supportsSingleSlotSchedulingOnly);
  }
  if (m_alternativesCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("alternativesCount", m_alternativesCount);
  }
  if (m_totalSequencesCountMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("totalSequencesCountMax",
                                           m_totalSequencesCountMax);
  }
  if (m_supportsReselectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("supportsReselection",
                                           m_supportsReselection);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram