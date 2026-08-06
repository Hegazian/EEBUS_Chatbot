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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/FeatureType.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementFeatureDescriptionListDataSelectors
 */
class NetworkManagementFeatureDescriptionListDataSelectors
    : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementFeatureDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_featureAddress the member to set
   * @param c_featureType the member to set
   */
  NetworkManagementFeatureDescriptionListDataSelectors(
      const FeatureAddress &c_featureAddress, const FeatureType &c_featureType);

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
  bool operator==(const NetworkManagementFeatureDescriptionListDataSelectors
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
  bool operator!=(const NetworkManagementFeatureDescriptionListDataSelectors
                      &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member FeatureAddress.
   * @param c_featureAddress Value to set
   */
  void setFeatureAddress(const FeatureAddress &c_featureAddress);

  /**
   * Returns const reference to member FeatureAddress.
   * @return const reference to member featureAddress
   */
  const FeatureAddress &getFeatureAddress() const;

  /**
   * Returns if member FeatureAddress is set.
   * @retval true member FeatureAddress is set
   * @retval false member FeatureAddress is not set
   */
  bool getFeatureAddressIsSet() const;

  /**
   * Unsets member FeatureAddress
   */
  void cleanFeatureAddress();

  /**
   * Set member FeatureType.
   * @param c_featureType Value to set
   */
  void setFeatureType(const FeatureType &c_featureType);

  /**
   * Returns const reference to member FeatureType.
   * @return const reference to member featureType
   */
  const FeatureType &getFeatureType() const;

  /**
   * Returns if member FeatureType is set.
   * @retval true member FeatureType is set
   * @retval false member FeatureType is not set
   */
  bool getFeatureTypeIsSet() const;

  /**
   * Unsets member FeatureType
   */
  void cleanFeatureType();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_featureAddressIsSet;
  FeatureAddress m_featureAddress;

  bool m_featureTypeIsSet;
  FeatureType m_featureType;
};

//! typedef for non-const smart pointer type
//! NetworkManagementFeatureDescriptionListDataSelectors
using NetworkManagementFeatureDescriptionListDataSelectorsPtr =
    std::shared_ptr<NetworkManagementFeatureDescriptionListDataSelectors>;

//! typedef for const type NetworkManagementFeatureDescriptionListDataSelectors
using NetworkManagementFeatureDescriptionListDataSelectorsConst =
    const NetworkManagementFeatureDescriptionListDataSelectors;

//! typedef for const type NetworkManagementFeatureDescriptionListDataSelectors
using NetworkManagementFeatureDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<NetworkManagementFeatureDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONLISTDATASELECTORS_H_