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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/EntityAddressElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementEntityDescriptionDataElements
 */
class NetworkManagementEntityDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementEntityDescriptionDataElements();

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
  bool operator==(const NetworkManagementEntityDescriptionDataElements
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
  bool operator!=(const NetworkManagementEntityDescriptionDataElements
                      &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member EntityAddress.
   * @param c_entityAddress Value to set
   */
  void setEntityAddress(const EntityAddressElements &c_entityAddress);

  /**
   * Returns const reference to member EntityAddress.
   * @return const reference to member entityAddress
   */
  const EntityAddressElements &getEntityAddress() const;

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
   */
  void setEntityType();

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
   */
  void setLastStateChange();

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
   */
  void setMinimumTrustLevel();

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
   */
  void setLabel();

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
   */
  void setDescription();

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
  EntityAddressElements m_entityAddress;

  // ElementTag
  bool m_entityTypeIsSet;

  // ElementTag
  bool m_lastStateChangeIsSet;

  // ElementTag
  bool m_minimumTrustLevelIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type
//! NetworkManagementEntityDescriptionDataElements
using NetworkManagementEntityDescriptionDataElementsPtr =
    std::shared_ptr<NetworkManagementEntityDescriptionDataElements>;

//! typedef for const type NetworkManagementEntityDescriptionDataElements
using NetworkManagementEntityDescriptionDataElementsConst =
    const NetworkManagementEntityDescriptionDataElements;

//! typedef for const type NetworkManagementEntityDescriptionDataElements
using NetworkManagementEntityDescriptionDataElementsConstPtr =
    std::shared_ptr<NetworkManagementEntityDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTENTITYDESCRIPTIONDATAELEMENTS_H_