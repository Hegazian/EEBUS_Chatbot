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

#include <keo_datagram/loadcontrol/LoadControlNodeData.h>

#include <keo_datagram/loadcontrol/LoadControlNodeDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlNodeData::LoadControlNodeData()
    : CmdData(), m_isNodeRemoteControllableIsSet(false),
      m_isNodeRemoteControllable(false)

{}

LoadControlNodeData::LoadControlNodeData(
    const xs_boolean &c_isNodeRemoteControllable) {
  setIsNodeRemoteControllable(c_isNodeRemoteControllable);
}

bool LoadControlNodeData::
operator==(const LoadControlNodeData &c_classObject) const {
  if (m_isNodeRemoteControllableIsSet !=
          c_classObject.m_isNodeRemoteControllableIsSet ||
      (m_isNodeRemoteControllableIsSet &&
       (m_isNodeRemoteControllable !=
        c_classObject.m_isNodeRemoteControllable))) {
    return false;
  }

  return true;
}

bool LoadControlNodeData::
operator!=(const LoadControlNodeData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlNodeData::isEmpty() const {
  return !m_isNodeRemoteControllableIsSet;
}

CmdData::Type LoadControlNodeData::getDataType() const {
  return CmdData::Type::LOAD_CONTROL_NODE_DATA_TYPE;
}

CmdDataPtr LoadControlNodeData::clone() const {
  return std::make_shared<LoadControlNodeData>(*this);
}

void LoadControlNodeData::setIsNodeRemoteControllable(
    const xs_boolean &isNodeRemoteControllable) {
  m_isNodeRemoteControllable = isNodeRemoteControllable;
  m_isNodeRemoteControllableIsSet = true;
}

const xs_boolean &LoadControlNodeData::getIsNodeRemoteControllable() const {
  return m_isNodeRemoteControllable;
}

void LoadControlNodeData::cleanIsNodeRemoteControllable() {
  m_isNodeRemoteControllable = false;
  m_isNodeRemoteControllableIsSet = false;
}

bool LoadControlNodeData::getIsNodeRemoteControllableIsSet() const {
  return m_isNodeRemoteControllableIsSet;
}

CmdDataPtr
LoadControlNodeData::reduce(const std::vector<Filter> &filters) const {
  if (!filters.empty()) {
    const auto &filter = filters[0];
    if (filter.getCmdControl() == CmdControl::PARTIAL) {
      // For READ semantics only "partial" filters make sense
      LoadControlNodeDataElementsPtr elements =
          std::dynamic_pointer_cast<LoadControlNodeDataElements>(
              filter.getDataElements());
      if (elements) {
        LoadControlNodeDataPtr dataOut =
            std::make_shared<LoadControlNodeData>();
        // TODO make sure to always set identifier

        if (getIsNodeRemoteControllableIsSet() &&
            elements->getIsNodeRemoteControllableIsSet()) {
          dataOut->setIsNodeRemoteControllable(getIsNodeRemoteControllable());
        }

        return dataOut;
      } else {
        return std::make_shared<LoadControlNodeData>(*this);
      }
    } else {
      return std::make_shared<LoadControlNodeData>(*this);
    }
  } else {
    return std::make_shared<LoadControlNodeData>(*this);
  }
}

bool LoadControlNodeData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"isNodeRemoteControllable"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isNodeRemoteControllable",
                                   &m_isNodeRemoteControllable)) {
      m_isNodeRemoteControllableIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlNodeData::toJson() const {
  std::string result = "[";
  if (m_isNodeRemoteControllableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isNodeRemoteControllable",
                                           m_isNodeRemoteControllable);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram