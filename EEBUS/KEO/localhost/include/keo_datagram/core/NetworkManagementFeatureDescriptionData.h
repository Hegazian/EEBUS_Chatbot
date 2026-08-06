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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/FeatureSpecificUsage.h>
#include <keo_datagram/core/FeatureType.h>
#include <keo_datagram/core/FunctionProperty.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/NetworkManagementStateChange.h>
#include <keo_datagram/core/Role.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementFeatureDescriptionData
 */
class NetworkManagementFeatureDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementFeatureDescriptionData();

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
      const NetworkManagementFeatureDescriptionData &c_classObject) const;

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
      const NetworkManagementFeatureDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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

  /**
   * Set member SpecificUsage.
   * @param c_specificUsage Value to set
   */
  void
  setSpecificUsage(const std::vector<FeatureSpecificUsage> &c_specificUsage);

  /**
   * Returns const reference to member SpecificUsage.
   * @return const reference to member specificUsage
   */
  const std::vector<FeatureSpecificUsage> &getSpecificUsage() const;

  /**
   * Returns if member SpecificUsage is set.
   * @retval true member SpecificUsage is set
   * @retval false member SpecificUsage is not set
   */
  bool getSpecificUsageIsSet() const;

  /**
   * Unsets member SpecificUsage
   */
  void cleanSpecificUsage();

  /**
   * Set member FeatureGroup.
   * @param c_featureGroup Value to set
   */
  void setFeatureGroup(const xs_string &c_featureGroup);

  /**
   * Returns const reference to member FeatureGroup.
   * @return const reference to member featureGroup
   */
  const xs_string &getFeatureGroup() const;

  /**
   * Returns if member FeatureGroup is set.
   * @retval true member FeatureGroup is set
   * @retval false member FeatureGroup is not set
   */
  bool getFeatureGroupIsSet() const;

  /**
   * Unsets member FeatureGroup
   */
  void cleanFeatureGroup();

  /**
   * Set member Role.
   * @param c_role Value to set
   */
  void setRole(const Role &c_role);

  /**
   * Returns const reference to member Role.
   * @return const reference to member role
   */
  const Role &getRole() const;

  /**
   * Returns if member Role is set.
   * @retval true member Role is set
   * @retval false member Role is not set
   */
  bool getRoleIsSet() const;

  /**
   * Unsets member Role
   */
  void cleanRole();

  /**
   * Set member SupportedFunction.
   * @param c_supportedFunction Value to set
   */
  void setSupportedFunction(
      const std::vector<FunctionProperty> &c_supportedFunction);

  /**
   * Returns const reference to member SupportedFunction.
   * @return const reference to member supportedFunction
   */
  const std::vector<FunctionProperty> &getSupportedFunction() const;

  /**
   * Returns if member SupportedFunction is set.
   * @retval true member SupportedFunction is set
   * @retval false member SupportedFunction is not set
   */
  bool getSupportedFunctionIsSet() const;

  /**
   * Unsets member SupportedFunction
   */
  void cleanSupportedFunction();

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

  /**
   * Set member MaxResponseDelay.
   * @param c_maxResponseDelay Value to set
   */
  void setMaxResponseDelay(const xs_duration &c_maxResponseDelay);

  /**
   * Returns const reference to member MaxResponseDelay.
   * @return const reference to member maxResponseDelay
   */
  const xs_duration &getMaxResponseDelay() const;

  /**
   * Returns if member MaxResponseDelay is set.
   * @retval true member MaxResponseDelay is set
   * @retval false member MaxResponseDelay is not set
   */
  bool getMaxResponseDelayIsSet() const;

  /**
   * Unsets member MaxResponseDelay
   */
  void cleanMaxResponseDelay();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_featureAddressIsSet;
  FeatureAddress m_featureAddress;

  bool m_featureTypeIsSet;
  FeatureType m_featureType;

  bool m_specificUsageIsSet;
  std::vector<FeatureSpecificUsage> m_specificUsage;

  bool m_featureGroupIsSet;
  xs_string m_featureGroup;

  bool m_roleIsSet;
  Role m_role;

  bool m_supportedFunctionIsSet;
  std::vector<FunctionProperty> m_supportedFunction;

  bool m_lastStateChangeIsSet;
  NetworkManagementStateChange m_lastStateChange;

  bool m_minimumTrustLevelIsSet;
  xs_string m_minimumTrustLevel;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;

  bool m_maxResponseDelayIsSet;
  xs_duration m_maxResponseDelay;
};

//! typedef for non-const smart pointer type
//! NetworkManagementFeatureDescriptionData
using NetworkManagementFeatureDescriptionDataPtr =
    std::shared_ptr<NetworkManagementFeatureDescriptionData>;

//! typedef for const type NetworkManagementFeatureDescriptionData
using NetworkManagementFeatureDescriptionDataConst =
    const NetworkManagementFeatureDescriptionData;

//! typedef for const type NetworkManagementFeatureDescriptionData
using NetworkManagementFeatureDescriptionDataConstPtr =
    std::shared_ptr<NetworkManagementFeatureDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONDATA_H_