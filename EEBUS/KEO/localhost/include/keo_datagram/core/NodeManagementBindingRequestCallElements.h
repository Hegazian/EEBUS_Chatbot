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

#ifndef KEO_DATAGRAM_CORE_NODEMANAGEMENTBINDINGREQUESTCALLELEMENTS_H_
#define KEO_DATAGRAM_CORE_NODEMANAGEMENTBINDINGREQUESTCALLELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/BindingManagementRequestCallElements.h>
#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NodeManagementBindingRequestCallElements
 */
class NodeManagementBindingRequestCallElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  NodeManagementBindingRequestCallElements();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_bindingRequest the member to set
   */
  explicit NodeManagementBindingRequestCallElements(
      const BindingManagementRequestCallElements &c_bindingRequest);

  /**
   * Equality operator
   *
   * Two objects a and b are considered equal if and only if
   *     - all members that are set in a are also set in b
   *     - all members that are set in b are also set in a
   *     - all members that are set in a and b are equal
   *
   * @param c_classObject the object to compare to
   * @return true if the objects are equal
   */
  bool operator==(
      const NodeManagementBindingRequestCallElements &c_classObject) const;

  /**
   * Inequality operator
   *
   * Two objects a and b are considered not equal if and only if
   *     - at least one member that is set in a is not set in b
   *     - at least one member that is set in b is not set in a
   *     - at least one member that is set in a and b differs
   *
   * @param c_classObject the object to compare to
   * @return true, if the objects are not equal
   */
  bool operator!=(
      const NodeManagementBindingRequestCallElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member BindingRequest.
   * @param c_bindingRequest Value to set
   */
  void setBindingRequest(
      const BindingManagementRequestCallElements &c_bindingRequest);

  /**
   * Returns const reference to member BindingRequest.
   * @return const reference to member bindingRequest
   */
  const BindingManagementRequestCallElements &getBindingRequest() const;

  /**
   * Returns if member BindingRequest is set.
   * @retval true member BindingRequest is set
   * @retval false member BindingRequest is not set
   */
  bool getBindingRequestIsSet() const;

  /**
   * Unsets member BindingRequest
   */
  void cleanBindingRequest();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_bindingRequestIsSet;
  BindingManagementRequestCallElements m_bindingRequest;
};

//! typedef for non-const smart pointer type
//! NodeManagementBindingRequestCallElements
using NodeManagementBindingRequestCallElementsPtr =
    std::shared_ptr<NodeManagementBindingRequestCallElements>;

//! typedef for const type NodeManagementBindingRequestCallElements
using NodeManagementBindingRequestCallElementsConst =
    const NodeManagementBindingRequestCallElements;

//! typedef for const type NodeManagementBindingRequestCallElements
using NodeManagementBindingRequestCallElementsConstPtr =
    std::shared_ptr<NodeManagementBindingRequestCallElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NODEMANAGEMENTBINDINGREQUESTCALLELEMENTS_H_