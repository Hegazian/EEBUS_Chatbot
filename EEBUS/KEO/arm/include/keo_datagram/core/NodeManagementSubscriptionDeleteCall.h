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

#ifndef KEO_DATAGRAM_CORE_NODEMANAGEMENTSUBSCRIPTIONDELETECALL_H_
#define KEO_DATAGRAM_CORE_NODEMANAGEMENTSUBSCRIPTIONDELETECALL_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/SubscriptionManagementDeleteCall.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NodeManagementSubscriptionDeleteCall
 */
class NodeManagementSubscriptionDeleteCall : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  NodeManagementSubscriptionDeleteCall();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_subscriptionDelete the member to set
   */
  explicit NodeManagementSubscriptionDeleteCall(
      const SubscriptionManagementDeleteCall &c_subscriptionDelete);

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
  bool
  operator==(const NodeManagementSubscriptionDeleteCall &c_classObject) const;

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
  bool
  operator!=(const NodeManagementSubscriptionDeleteCall &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member SubscriptionDelete.
   * @param c_subscriptionDelete Value to set
   */
  void setSubscriptionDelete(
      const SubscriptionManagementDeleteCall &c_subscriptionDelete);

  /**
   * Returns const reference to member SubscriptionDelete.
   * @return const reference to member subscriptionDelete
   */
  const SubscriptionManagementDeleteCall &getSubscriptionDelete() const;

  /**
   * Returns if member SubscriptionDelete is set.
   * @retval true member SubscriptionDelete is set
   * @retval false member SubscriptionDelete is not set
   */
  bool getSubscriptionDeleteIsSet() const;

  /**
   * Unsets member SubscriptionDelete
   */
  void cleanSubscriptionDelete();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_subscriptionDeleteIsSet;
  SubscriptionManagementDeleteCall m_subscriptionDelete;
};

//! typedef for non-const smart pointer type
//! NodeManagementSubscriptionDeleteCall
using NodeManagementSubscriptionDeleteCallPtr =
    std::shared_ptr<NodeManagementSubscriptionDeleteCall>;

//! typedef for const type NodeManagementSubscriptionDeleteCall
using NodeManagementSubscriptionDeleteCallConst =
    const NodeManagementSubscriptionDeleteCall;

//! typedef for const type NodeManagementSubscriptionDeleteCall
using NodeManagementSubscriptionDeleteCallConstPtr =
    std::shared_ptr<NodeManagementSubscriptionDeleteCallConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NODEMANAGEMENTSUBSCRIPTIONDELETECALL_H_