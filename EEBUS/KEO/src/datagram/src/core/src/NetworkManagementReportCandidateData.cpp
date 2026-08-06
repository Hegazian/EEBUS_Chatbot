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

#include <keo_datagram/core/NetworkManagementReportCandidateData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementReportCandidateData::NetworkManagementReportCandidateData()
    : CmdData(), m_candidateSetupIsSet(false), m_candidateSetup(""),
      m_setupUsableForAddIsSet(false), m_setupUsableForAdd(false),
      m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description("")

{}

bool NetworkManagementReportCandidateData::
operator==(const NetworkManagementReportCandidateData &c_classObject) const {
  if (m_candidateSetupIsSet != c_classObject.m_candidateSetupIsSet ||
      (m_candidateSetupIsSet &&
       (m_candidateSetup != c_classObject.m_candidateSetup))) {
    return false;
  }
  if (m_setupUsableForAddIsSet != c_classObject.m_setupUsableForAddIsSet ||
      (m_setupUsableForAddIsSet &&
       (m_setupUsableForAdd != c_classObject.m_setupUsableForAdd))) {
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

bool NetworkManagementReportCandidateData::
operator!=(const NetworkManagementReportCandidateData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementReportCandidateData::isEmpty() const {
  return !m_candidateSetupIsSet && !m_setupUsableForAddIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

CmdData::Type NetworkManagementReportCandidateData::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_TYPE;
}

CmdDataPtr NetworkManagementReportCandidateData::clone() const {
  return std::make_shared<NetworkManagementReportCandidateData>(*this);
}

void NetworkManagementReportCandidateData::setCandidateSetup(
    const xs_string &candidateSetup) {
  m_candidateSetup = candidateSetup;
  m_candidateSetupIsSet = true;
}

const xs_string &
NetworkManagementReportCandidateData::getCandidateSetup() const {
  return m_candidateSetup;
}

void NetworkManagementReportCandidateData::cleanCandidateSetup() {
  m_candidateSetup = "";
  m_candidateSetupIsSet = false;
}

bool NetworkManagementReportCandidateData::getCandidateSetupIsSet() const {
  return m_candidateSetupIsSet;
}

void NetworkManagementReportCandidateData::setSetupUsableForAdd(
    const xs_boolean &setupUsableForAdd) {
  m_setupUsableForAdd = setupUsableForAdd;
  m_setupUsableForAddIsSet = true;
}

const xs_boolean &
NetworkManagementReportCandidateData::getSetupUsableForAdd() const {
  return m_setupUsableForAdd;
}

void NetworkManagementReportCandidateData::cleanSetupUsableForAdd() {
  m_setupUsableForAdd = false;
  m_setupUsableForAddIsSet = false;
}

bool NetworkManagementReportCandidateData::getSetupUsableForAddIsSet() const {
  return m_setupUsableForAddIsSet;
}

void NetworkManagementReportCandidateData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &NetworkManagementReportCandidateData::getLabel() const {
  return m_label;
}

void NetworkManagementReportCandidateData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool NetworkManagementReportCandidateData::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementReportCandidateData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &NetworkManagementReportCandidateData::getDescription() const {
  return m_description;
}

void NetworkManagementReportCandidateData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool NetworkManagementReportCandidateData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

CmdDataPtr NetworkManagementReportCandidateData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementReportCandidateData>(*this);
}

bool NetworkManagementReportCandidateData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"candidateSetup", "setupUsableForAdd", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "candidateSetup", &m_candidateSetup)) {
      m_candidateSetupIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "setupUsableForAdd", &m_setupUsableForAdd)) {
      m_setupUsableForAddIsSet = true;
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

std::string NetworkManagementReportCandidateData::toJson() const {
  std::string result = "[";
  if (m_candidateSetupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("candidateSetup", m_candidateSetup);
  }
  if (m_setupUsableForAddIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("setupUsableForAdd", m_setupUsableForAdd);
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