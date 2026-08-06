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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/EntityAddress.h>
#include <keo_datagram/core/EntityType.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/NetworkManagementStateChange.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementEntityDescriptionData
 */
class NetworkManagementEntityDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementEntityDescriptionData();

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
  operator==(const NetworkManagementEntityDescriptionData &c_classObject) const;

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
  operator!=(const NetworkManagementEntityDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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

  /**
   * Set member LastStateChange.
   * @param c_lastStateChange Value to set
   */
  void
  setLastStateChange(const NetworkManagementStateChange &c_lastStateChange);

  /**
   * Returns const reference to member LastStateChange.
   * @return const reference to member lastStateChange
   */
  const NetworkManagementStateChange &getLastStateChange() const;

  /**
   * Returns if member LastStateChange is set.
   * @retval true member LastStateChange is set
   * @retval false member LastStateChange is not set
   */
  bool getLastStateChangeIsSet() const;

  /**
   * Unsets member LastStateChange
   */
  void cleanLastStateChange();

  /**
   * Set member MinimumTrustLevel.
   * @param c_minimumTrustLevel Value to set
   */
  void setMinimumTrustLevel(const xs_string &c_minimumTrustLevel);

  /**
   * Returns const reference to member MinimumTrustLevel.
   * @return const reference to member minimumTrustLevel
   */
  const xs_string &getMinimumTrustLevel() const;

  /**
   * Returns if member MinimumTrustLevel is set.
   * @retval true member MinimumTrustLevel is set
   * @retval false member MinimumTrustLevel is not set
   */
  bool getMinimumTrustLevelIsSet() const;

  /**
   * Unsets member MinimumTrustLevel
   */
  void cleanMinimumTrustLevel();

  /**
   * Set member Label.
   * @param c_label Value to set
   */
  void setLabel(const xs_string &c_label);

  /**
   * Returns const reference to member Label.
   * @return const reference to member label
   */
  const xs_string &getLabel() const;

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

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

  bool m_entityAddressIsSet;
  EntityAddress m_entityAddress;

  bool m_entityTypeIsSet;
  EntityType m_entityType;

  bool m_lastStateChangeIsSet;
  NetworkManagementStateChange m_lastStateChange;

  bool m_minimumTrustLevelIsSet;
  xs_string m_minimumTrustLevel;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type
//! NetworkManagementEntityDescriptionData
using NetworkManagementEntityDescriptionDataPtr =
    std::shared_ptr<NetworkManagementEntityDescriptionData>;

//! typedef for const type NetworkManagementEntityDescriptionData
using NetworkManagementEntityDescriptionDataConst =
    const NetworkManagementEntityDescriptionData;

//! typedef for const type NetworkManagementEntityDescriptionData
using NetworkManagementEntityDescriptionDataConstPtr =
    std::shared_ptr<NetworkManagementEntityDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONDATA_H_