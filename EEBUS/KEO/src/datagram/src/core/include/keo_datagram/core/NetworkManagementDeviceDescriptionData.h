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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DeviceAddress.h>
#include <keo_datagram/core/DeviceType.h>
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/NetworkManagementFeatureSet.h>
#include <keo_datagram/core/NetworkManagementStateChange.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementDeviceDescriptionData
 */
class NetworkManagementDeviceDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementDeviceDescriptionData();

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
  operator==(const NetworkManagementDeviceDescriptionData &c_classObject) const;

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
  operator!=(const NetworkManagementDeviceDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member DeviceAddress.
   * @param c_deviceAddress Value to set
   */
  void setDeviceAddress(const DeviceAddress &c_deviceAddress);

  /**
   * Returns const reference to member DeviceAddress.
   * @return const reference to member deviceAddress
   */
  const DeviceAddress &getDeviceAddress() const;

  /**
   * Returns if member DeviceAddress is set.
   * @retval true member DeviceAddress is set
   * @retval false member DeviceAddress is not set
   */
  bool getDeviceAddressIsSet() const;

  /**
   * Unsets member DeviceAddress
   */
  void cleanDeviceAddress();

  /**
   * Set member DeviceType.
   * @param c_deviceType Value to set
   */
  void setDeviceType(const DeviceType &c_deviceType);

  /**
   * Returns const reference to member DeviceType.
   * @return const reference to member deviceType
   */
  const DeviceType &getDeviceType() const;

  /**
   * Returns if member DeviceType is set.
   * @retval true member DeviceType is set
   * @retval false member DeviceType is not set
   */
  bool getDeviceTypeIsSet() const;

  /**
   * Unsets member DeviceType
   */
  void cleanDeviceType();

  /**
   * Set member NetworkManagementResponsibleAddress.
   * @param c_networkManagementResponsibleAddress Value to set
   */
  void setNetworkManagementResponsibleAddress(
      const FeatureAddress &c_networkManagementResponsibleAddress);

  /**
   * Returns const reference to member NetworkManagementResponsibleAddress.
   * @return const reference to member networkManagementResponsibleAddress
   */
  const FeatureAddress &getNetworkManagementResponsibleAddress() const;

  /**
   * Returns if member NetworkManagementResponsibleAddress is set.
   * @retval true member NetworkManagementResponsibleAddress is set
   * @retval false member NetworkManagementResponsibleAddress is not set
   */
  bool getNetworkManagementResponsibleAddressIsSet() const;

  /**
   * Unsets member NetworkManagementResponsibleAddress
   */
  void cleanNetworkManagementResponsibleAddress();

  /**
   * Set member NativeSetup.
   * @param c_nativeSetup Value to set
   */
  void setNativeSetup(const xs_string &c_nativeSetup);

  /**
   * Returns const reference to member NativeSetup.
   * @return const reference to member nativeSetup
   */
  const xs_string &getNativeSetup() const;

  /**
   * Returns if member NativeSetup is set.
   * @retval true member NativeSetup is set
   * @retval false member NativeSetup is not set
   */
  bool getNativeSetupIsSet() const;

  /**
   * Unsets member NativeSetup
   */
  void cleanNativeSetup();

  /**
   * Set member TechnologyAddress.
   * @param c_technologyAddress Value to set
   */
  void setTechnologyAddress(const xs_string &c_technologyAddress);

  /**
   * Returns const reference to member TechnologyAddress.
   * @return const reference to member technologyAddress
   */
  const xs_string &getTechnologyAddress() const;

  /**
   * Returns if member TechnologyAddress is set.
   * @retval true member TechnologyAddress is set
   * @retval false member TechnologyAddress is not set
   */
  bool getTechnologyAddressIsSet() const;

  /**
   * Unsets member TechnologyAddress
   */
  void cleanTechnologyAddress();

  /**
   * Set member CommunicationsTechnologyInformation.
   * @param c_communicationsTechnologyInformation Value to set
   */
  void setCommunicationsTechnologyInformation(
      const xs_string &c_communicationsTechnologyInformation);

  /**
   * Returns const reference to member CommunicationsTechnologyInformation.
   * @return const reference to member communicationsTechnologyInformation
   */
  const xs_string &getCommunicationsTechnologyInformation() const;

  /**
   * Returns if member CommunicationsTechnologyInformation is set.
   * @retval true member CommunicationsTechnologyInformation is set
   * @retval false member CommunicationsTechnologyInformation is not set
   */
  bool getCommunicationsTechnologyInformationIsSet() const;

  /**
   * Unsets member CommunicationsTechnologyInformation
   */
  void cleanCommunicationsTechnologyInformation();

  /**
   * Set member NetworkFeatureSet.
   * @param c_networkFeatureSet Value to set
   */
  void
  setNetworkFeatureSet(const NetworkManagementFeatureSet &c_networkFeatureSet);

  /**
   * Returns const reference to member NetworkFeatureSet.
   * @return const reference to member networkFeatureSet
   */
  const NetworkManagementFeatureSet &getNetworkFeatureSet() const;

  /**
   * Returns if member NetworkFeatureSet is set.
   * @retval true member NetworkFeatureSet is set
   * @retval false member NetworkFeatureSet is not set
   */
  bool getNetworkFeatureSetIsSet() const;

  /**
   * Unsets member NetworkFeatureSet
   */
  void cleanNetworkFeatureSet();

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

  bool m_deviceAddressIsSet;
  DeviceAddress m_deviceAddress;

  bool m_deviceTypeIsSet;
  DeviceType m_deviceType;

  bool m_networkManagementResponsibleAddressIsSet;
  FeatureAddress m_networkManagementResponsibleAddress;

  bool m_nativeSetupIsSet;
  xs_string m_nativeSetup;

  bool m_technologyAddressIsSet;
  xs_string m_technologyAddress;

  bool m_communicationsTechnologyInformationIsSet;
  xs_string m_communicationsTechnologyInformation;

  bool m_networkFeatureSetIsSet;
  NetworkManagementFeatureSet m_networkFeatureSet;

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
//! NetworkManagementDeviceDescriptionData
using NetworkManagementDeviceDescriptionDataPtr =
    std::shared_ptr<NetworkManagementDeviceDescriptionData>;

//! typedef for const type NetworkManagementDeviceDescriptionData
using NetworkManagementDeviceDescriptionDataConst =
    const NetworkManagementDeviceDescriptionData;

//! typedef for const type NetworkManagementDeviceDescriptionData
using NetworkManagementDeviceDescriptionDataConstPtr =
    std::shared_ptr<NetworkManagementDeviceDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONDATA_H_