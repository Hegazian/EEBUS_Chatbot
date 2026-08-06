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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/FeatureAddressElements.h>
#include <keo_datagram/core/FunctionPropertyElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementFeatureDescriptionDataElements
 */
class NetworkManagementFeatureDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementFeatureDescriptionDataElements();

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
  bool operator==(const NetworkManagementFeatureDescriptionDataElements
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
  bool operator!=(const NetworkManagementFeatureDescriptionDataElements
                      &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member FeatureAddress.
   * @param c_featureAddress Value to set
   */
  void setFeatureAddress(const FeatureAddressElements &c_featureAddress);

  /**
   * Returns const reference to member FeatureAddress.
   * @return const reference to member featureAddress
   */
  const FeatureAddressElements &getFeatureAddress() const;

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
   */
  void setFeatureType();

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
   */
  void setSpecificUsage();

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
   */
  void setFeatureGroup();

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
   */
  void setRole();

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
  void
  setSupportedFunction(const FunctionPropertyElements &c_supportedFunction);

  /**
   * Returns const reference to member SupportedFunction.
   * @return const reference to member supportedFunction
   */
  const FunctionPropertyElements &getSupportedFunction() const;

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

  /**
   * Set member MaxResponseDelay.
   */
  void setMaxResponseDelay();

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
  FeatureAddressElements m_featureAddress;

  // ElementTag
  bool m_featureTypeIsSet;

  // ElementTag
  bool m_specificUsageIsSet;

  // ElementTag
  bool m_featureGroupIsSet;

  // ElementTag
  bool m_roleIsSet;

  bool m_supportedFunctionIsSet;
  FunctionPropertyElements m_supportedFunction;

  // ElementTag
  bool m_lastStateChangeIsSet;

  // ElementTag
  bool m_minimumTrustLevelIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;

  // ElementTag
  bool m_maxResponseDelayIsSet;
};

//! typedef for non-const smart pointer type
//! NetworkManagementFeatureDescriptionDataElements
using NetworkManagementFeatureDescriptionDataElementsPtr =
    std::shared_ptr<NetworkManagementFeatureDescriptionDataElements>;

//! typedef for const type NetworkManagementFeatureDescriptionDataElements
using NetworkManagementFeatureDescriptionDataElementsConst =
    const NetworkManagementFeatureDescriptionDataElements;

//! typedef for const type NetworkManagementFeatureDescriptionDataElements
using NetworkManagementFeatureDescriptionDataElementsConstPtr =
    std::shared_ptr<NetworkManagementFeatureDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONDATAELEMENTS_H_