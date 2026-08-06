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

#ifndef KEO_DATAGRAM_CORE_NODEMANAGEMENTDETAILEDDISCOVERYENTITYINFORMATIONELEMENTS_H_
#define KEO_DATAGRAM_CORE_NODEMANAGEMENTDETAILEDDISCOVERYENTITYINFORMATIONELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/NetworkManagementEntityDescriptionDataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NodeManagementDetailedDiscoveryEntityInformationElements
 */
class NodeManagementDetailedDiscoveryEntityInformationElements
    : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  NodeManagementDetailedDiscoveryEntityInformationElements();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_description the member to set
   */
  explicit NodeManagementDetailedDiscoveryEntityInformationElements(
      const NetworkManagementEntityDescriptionDataElements &c_description);

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
  bool operator==(const NodeManagementDetailedDiscoveryEntityInformationElements
                      &c_classObject) const;

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
  bool operator!=(const NodeManagementDetailedDiscoveryEntityInformationElements
                      &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(
      const NetworkManagementEntityDescriptionDataElements &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const NetworkManagementEntityDescriptionDataElements &getDescription() const;

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_descriptionIsSet;
  NetworkManagementEntityDescriptionDataElements m_description;
};

//! typedef for non-const smart pointer type
//! NodeManagementDetailedDiscoveryEntityInformationElements
using NodeManagementDetailedDiscoveryEntityInformationElementsPtr =
    std::shared_ptr<NodeManagementDetailedDiscoveryEntityInformationElements>;

//! typedef for const type
//! NodeManagementDetailedDiscoveryEntityInformationElements
using NodeManagementDetailedDiscoveryEntityInformationElementsConst =
    const NodeManagementDetailedDiscoveryEntityInformationElements;

//! typedef for const type
//! NodeManagementDetailedDiscoveryEntityInformationElements
using NodeManagementDetailedDiscoveryEntityInformationElementsConstPtr =
    std::shared_ptr<
        NodeManagementDetailedDiscoveryEntityInformationElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NODEMANAGEMENTDETAILEDDISCOVERYENTITYINFORMATIONELEMENTS_H_