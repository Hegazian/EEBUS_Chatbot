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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/EntityAddress.h>
#include <keo_datagram/core/EntityType.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementEntityDescriptionListDataSelectors
 */
class NetworkManagementEntityDescriptionListDataSelectors
    : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementEntityDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_entityAddress the member to set
   * @param c_entityType the member to set
   */
  NetworkManagementEntityDescriptionListDataSelectors(
      const EntityAddress &c_entityAddress, const EntityType &c_entityType);

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
  bool operator==(const NetworkManagementEntityDescriptionListDataSelectors
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
  bool operator!=(const NetworkManagementEntityDescriptionListDataSelectors
                      &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member EntityAddress.
   * @param c_entityAddress Value to set
   */
  void setEntityAddress(const EntityAddress &c_entityAddress);

  /**
   * Returns const reference to member EntityAddress.
   * @return const reference to member entityAddress
   */
  const EntityAddress &getEntityAddress() const;

  /**
   * Returns if member EntityAddress is set.
   * @retval true member EntityAddress is set
   * @retval false member EntityAddress is not set
   */
  bool getEntityAddressIsSet() const;

  /**
   * Unsets member EntityAddress
   */
  void cleanEntityAddress();

  /**
   * Set member EntityType.
   * @param c_entityType Value to set
   */
  void setEntityType(const EntityType &c_entityType);

  /**
   * Returns const reference to member EntityType.
   * @return const reference to member entityType
   */
  const EntityType &getEntityType() const;

  /**
   * Returns if member EntityType is set.
   * @retval true member EntityType is set
   * @retval false member EntityType is not set
   */
  bool getEntityTypeIsSet() const;

  /**
   * Unsets member EntityType
   */
  void cleanEntityType();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_entityAddressIsSet;
  EntityAddress m_entityAddress;

  bool m_entityTypeIsSet;
  EntityType m_entityType;
};

//! typedef for non-const smart pointer type
//! NetworkManagementEntityDescriptionListDataSelectors
using NetworkManagementEntityDescriptionListDataSelectorsPtr =
    std::shared_ptr<NetworkManagementEntityDescriptionListDataSelectors>;

//! typedef for const type NetworkManagementEntityDescriptionListDataSelectors
using NetworkManagementEntityDescriptionListDataSelectorsConst =
    const NetworkManagementEntityDescriptionListDataSelectors;

//! typedef for const type NetworkManagementEntityDescriptionListDataSelectors
using NetworkManagementEntityDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<NetworkManagementEntityDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONLISTDATASELECTORS_H_