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

#include <keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceNodeScheduleInformationDataElements::
    PowerSequenceNodeScheduleInformationDataElements()
    : DataElements(), m_nodeRemoteControllableIsSet(false),
      m_supportsSingleSlotSchedulingOnlyIsSet(false),
      m_alternativesCountIsSet(false), m_totalSequencesCountMaxIsSet(false),
      m_supportsReselectionIsSet(false)

{}

bool PowerSequenceNodeScheduleInformationDataElements::operator==(
    const PowerSequenceNodeScheduleInformationDataElements &c_classObject)
    const {
  if (m_nodeRemoteControllableIsSet !=
      c_classObject.m_nodeRemoteControllableIsSet) {
    return false;
  }
  if (m_supportsSingleSlotSchedulingOnlyIsSet !=
      c_classObject.m_supportsSingleSlotSchedulingOnlyIsSet) {
    return false;
  }
  if (m_alternativesCountIsSet != c_classObject.m_alternativesCountIsSet) {
    return false;
  }
  if (m_totalSequencesCountMaxIsSet !=
      c_classObject.m_totalSequencesCountMaxIsSet) {
    return false;
  }
  if (m_supportsReselectionIsSet != c_classObject.m_supportsReselectionIsSet) {
    return false;
  }

  return true;
}

bool PowerSequenceNodeScheduleInformationDataElements::operator!=(
    const PowerSequenceNodeScheduleInformationDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool PowerSequenceNodeScheduleInformationDataElements::isEmpty() const {
  return !m_nodeRemoteControllableIsSet &&
         !m_supportsSingleSlotSchedulingOnlyIsSet &&
         !m_alternativesCountIsSet && !m_totalSequencesCountMaxIsSet &&
         !m_supportsReselectionIsSet;
}

DataElements::Type
PowerSequenceNodeScheduleInformationDataElements::getDataType() const {
  return DataElements::Type::
      POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
PowerSequenceNodeScheduleInformationDataElements::clone() const {
  return std::make_shared<PowerSequenceNodeScheduleInformationDataElements>(
      *this);
}

void PowerSequenceNodeScheduleInformationDataElements::
    setNodeRemoteControllable() {
  m_nodeRemoteControllableIsSet = true;
}

void PowerSequenceNodeScheduleInformationDataElements::
    cleanNodeRemoteControllable() {
  m_nodeRemoteControllableIsSet = false;
}

bool PowerSequenceNodeScheduleInformationDataElements::
    getNodeRemoteControllableIsSet() const {
  return m_nodeRemoteControllableIsSet;
}

void PowerSequenceNodeScheduleInformationDataElements::
    setSupportsSingleSlotSchedulingOnly() {
  m_supportsSingleSlotSchedulingOnlyIsSet = true;
}

void PowerSequenceNodeScheduleInformationDataElements::
    cleanSupportsSingleSlotSchedulingOnly() {
  m_supportsSingleSlotSchedulingOnlyIsSet = false;
}

bool PowerSequenceNodeScheduleInformationDataElements::
    getSupportsSingleSlotSchedulingOnlyIsSet() const {
  return m_supportsSingleSlotSchedulingOnlyIsSet;
}

void PowerSequenceNodeScheduleInformationDataElements::setAlternativesCount() {
  m_alternativesCountIsSet = true;
}

void PowerSequenceNodeScheduleInformationDataElements::
    cleanAlternativesCount() {
  m_alternativesCountIsSet = false;
}

bool PowerSequenceNodeScheduleInformationDataElements::
    getAlternativesCountIsSet() const {
  return m_alternativesCountIsSet;
}

void PowerSequenceNodeScheduleInformationDataElements::
    setTotalSequencesCountMax() {
  m_totalSequencesCountMaxIsSet = true;
}

void PowerSequenceNodeScheduleInformationDataElements::
    cleanTotalSequencesCountMax() {
  m_totalSequencesCountMaxIsSet = false;
}

bool PowerSequenceNodeScheduleInformationDataElements::
    getTotalSequencesCountMaxIsSet() const {
  return m_totalSequencesCountMaxIsSet;
}

void PowerSequenceNodeScheduleInformationDataElements::
    setSupportsReselection() {
  m_supportsReselectionIsSet = true;
}

void PowerSequenceNodeScheduleInformationDataElements::
    cleanSupportsReselection() {
  m_supportsReselectionIsSet = false;
}

bool PowerSequenceNodeScheduleInformationDataElements::
    getSupportsReselectionIsSet() const {
  return m_supportsReselectionIsSet;
}

bool PowerSequenceNodeScheduleInformationDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"nodeRemoteControllable", "supportsSingleSlotSchedulingOnly",
                   "alternativesCount", "totalSequencesCountMax",
                   "supportsReselection"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "nodeRemoteControllable")) {
      m_nodeRemoteControllableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "supportsSingleSlotSchedulingOnly")) {
      m_supportsSingleSlotSchedulingOnlyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "alternativesCount")) {
      m_alternativesCountIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "totalSequencesCountMax")) {
      m_totalSequencesCountMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "supportsReselection")) {
      m_supportsReselectionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceNodeScheduleInformationDataElements::toJson() const {
  std::string result = "[";
  if (m_nodeRemoteControllableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("nodeRemoteControllable");
  }
  if (m_supportsSingleSlotSchedulingOnlyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeTag("supportsSingleSlotSchedulingOnly");
  }
  if (m_alternativesCountIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("alternativesCount");
  }
  if (m_totalSequencesCountMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("totalSequencesCountMax");
  }
  if (m_supportsReselectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("supportsReselection");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram