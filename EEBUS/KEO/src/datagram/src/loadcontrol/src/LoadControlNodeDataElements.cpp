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

#include <keo_datagram/loadcontrol/LoadControlNodeDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlNodeDataElements::LoadControlNodeDataElements()
    : DataElements(), m_isNodeRemoteControllableIsSet(false)

{}

LoadControlNodeDataElements::LoadControlNodeDataElements(
    const xs_boolean &c_isNodeRemoteControllableIsSet) {
  if (c_isNodeRemoteControllableIsSet) {
    setIsNodeRemoteControllable();
  }
}

bool LoadControlNodeDataElements::
operator==(const LoadControlNodeDataElements &c_classObject) const {
  if (m_isNodeRemoteControllableIsSet !=
      c_classObject.m_isNodeRemoteControllableIsSet) {
    return false;
  }

  return true;
}

bool LoadControlNodeDataElements::
operator!=(const LoadControlNodeDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlNodeDataElements::isEmpty() const {
  return !m_isNodeRemoteControllableIsSet;
}

DataElements::Type LoadControlNodeDataElements::getDataType() const {
  return DataElements::Type::LOAD_CONTROL_NODE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr LoadControlNodeDataElements::clone() const {
  return std::make_shared<LoadControlNodeDataElements>(*this);
}

void LoadControlNodeDataElements::setIsNodeRemoteControllable() {
  m_isNodeRemoteControllableIsSet = true;
}

void LoadControlNodeDataElements::cleanIsNodeRemoteControllable() {
  m_isNodeRemoteControllableIsSet = false;
}

bool LoadControlNodeDataElements::getIsNodeRemoteControllableIsSet() const {
  return m_isNodeRemoteControllableIsSet;
}

bool LoadControlNodeDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"isNodeRemoteControllable"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isNodeRemoteControllable")) {
      m_isNodeRemoteControllableIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlNodeDataElements::toJson() const {
  std::string result = "[";
  if (m_isNodeRemoteControllableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isNodeRemoteControllable");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram