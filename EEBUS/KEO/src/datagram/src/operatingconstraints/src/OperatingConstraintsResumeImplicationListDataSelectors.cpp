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

#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsResumeImplicationListDataSelectors::
    OperatingConstraintsResumeImplicationListDataSelectors()
    : DataSelectors(), m_sequenceIdIsSet(false), m_sequenceId(0)

{}

OperatingConstraintsResumeImplicationListDataSelectors::
    OperatingConstraintsResumeImplicationListDataSelectors(
        const xs_unsignedInt &c_sequenceId) {
  setSequenceId(c_sequenceId);
}

bool OperatingConstraintsResumeImplicationListDataSelectors::operator==(
    const OperatingConstraintsResumeImplicationListDataSelectors &c_classObject)
    const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsResumeImplicationListDataSelectors::operator!=(
    const OperatingConstraintsResumeImplicationListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsResumeImplicationListDataSelectors::isEmpty() const {
  return !m_sequenceIdIsSet;
}

DataSelectors::Type
OperatingConstraintsResumeImplicationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
OperatingConstraintsResumeImplicationListDataSelectors::clone() const {
  return std::make_shared<
      OperatingConstraintsResumeImplicationListDataSelectors>(*this);
}

void OperatingConstraintsResumeImplicationListDataSelectors::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
OperatingConstraintsResumeImplicationListDataSelectors::getSequenceId() const {
  return m_sequenceId;
}

void OperatingConstraintsResumeImplicationListDataSelectors::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsResumeImplicationListDataSelectors::
    getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

bool OperatingConstraintsResumeImplicationListDataSelectors::selects(
    const OperatingConstraintsResumeImplicationData &data) const {
  if (getSequenceIdIsSet() &&
      (!data.getSequenceIdIsSet() || getSequenceId() != data.getSequenceId())) {
    return false;
  }
  return true;
}

bool OperatingConstraintsResumeImplicationListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
OperatingConstraintsResumeImplicationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram