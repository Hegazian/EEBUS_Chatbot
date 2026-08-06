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

#ifndef KEO_DATAGRAM_CORE_NODEMANAGEMENTSPECIFICATIONVERSIONLIST_H_
#define KEO_DATAGRAM_CORE_NODEMANAGEMENTSPECIFICATIONVERSIONLIST_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NodeManagementSpecificationVersionList
 */
class NodeManagementSpecificationVersionList : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  NodeManagementSpecificationVersionList();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_specificationVersion the member to set
   */
  explicit NodeManagementSpecificationVersionList(
      const std::vector<xs_string> &c_specificationVersion);

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
  operator==(const NodeManagementSpecificationVersionList &c_classObject) const;

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
  operator!=(const NodeManagementSpecificationVersionList &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member SpecificationVersion.
   * @param c_specificationVersion Value to set
   */
  void
  setSpecificationVersion(const std::vector<xs_string> &c_specificationVersion);

  /**
   * Returns const reference to member SpecificationVersion.
   * @return const reference to member specificationVersion
   */
  const std::vector<xs_string> &getSpecificationVersion() const;

  /**
   * Returns if member SpecificationVersion is set.
   * @retval true member SpecificationVersion is set
   * @retval false member SpecificationVersion is not set
   */
  bool getSpecificationVersionIsSet() const;

  /**
   * Unsets member SpecificationVersion
   */
  void cleanSpecificationVersion();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_specificationVersionIsSet;
  std::vector<xs_string> m_specificationVersion;
};

//! typedef for non-const smart pointer type
//! NodeManagementSpecificationVersionList
using NodeManagementSpecificationVersionListPtr =
    std::shared_ptr<NodeManagementSpecificationVersionList>;

//! typedef for const type NodeManagementSpecificationVersionList
using NodeManagementSpecificationVersionListConst =
    const NodeManagementSpecificationVersionList;

//! typedef for const type NodeManagementSpecificationVersionList
using NodeManagementSpecificationVersionListConstPtr =
    std::shared_ptr<NodeManagementSpecificationVersionListConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NODEMANAGEMENTSPECIFICATIONVERSIONLIST_H_