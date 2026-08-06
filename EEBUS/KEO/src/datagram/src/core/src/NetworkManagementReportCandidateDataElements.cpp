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

#include <keo_datagram/core/NetworkManagementReportCandidateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementReportCandidateDataElements::
    NetworkManagementReportCandidateDataElements()
    : DataElements(), m_candidateSetupIsSet(false),
      m_setupUsableForAddIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool NetworkManagementReportCandidateDataElements::operator==(
    const NetworkManagementReportCandidateDataElements &c_classObject) const {
  if (m_candidateSetupIsSet != c_classObject.m_candidateSetupIsSet) {
    return false;
  }
  if (m_setupUsableForAddIsSet != c_classObject.m_setupUsableForAddIsSet) {
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

bool NetworkManagementReportCandidateDataElements::operator!=(
    const NetworkManagementReportCandidateDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementReportCandidateDataElements::isEmpty() const {
  return !m_candidateSetupIsSet && !m_setupUsableForAddIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

DataElements::Type
NetworkManagementReportCandidateDataElements::getDataType() const {
  return DataElements::Type::
      NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementReportCandidateDataElements::clone() const {
  return std::make_shared<NetworkManagementReportCandidateDataElements>(*this);
}

void NetworkManagementReportCandidateDataElements::setCandidateSetup() {
  m_candidateSetupIsSet = true;
}

void NetworkManagementReportCandidateDataElements::cleanCandidateSetup() {
  m_candidateSetupIsSet = false;
}

bool NetworkManagementReportCandidateDataElements::getCandidateSetupIsSet()
    const {
  return m_candidateSetupIsSet;
}

void NetworkManagementReportCandidateDataElements::setSetupUsableForAdd() {
  m_setupUsableForAddIsSet = true;
}

void NetworkManagementReportCandidateDataElements::cleanSetupUsableForAdd() {
  m_setupUsableForAddIsSet = false;
}

bool NetworkManagementReportCandidateDataElements::getSetupUsableForAddIsSet()
    const {
  return m_setupUsableForAddIsSet;
}

void NetworkManagementReportCandidateDataElements::setLabel() {
  m_labelIsSet = true;
}

void NetworkManagementReportCandidateDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool NetworkManagementReportCandidateDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementReportCandidateDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void NetworkManagementReportCandidateDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool NetworkManagementReportCandidateDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool NetworkManagementReportCandidateDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"candidateSetup", "setupUsableForAdd", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "candidateSetup")) {
      m_candidateSetupIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "setupUsableForAdd")) {
      m_setupUsableForAddIsSet = true;
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

std::string NetworkManagementReportCandidateDataElements::toJson() const {
  std::string result = "[";
  if (m_candidateSetupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("candidateSetup");
  }
  if (m_setupUsableForAddIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("setupUsableForAdd");
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