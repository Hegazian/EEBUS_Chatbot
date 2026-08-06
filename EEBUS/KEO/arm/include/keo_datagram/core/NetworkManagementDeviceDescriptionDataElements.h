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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/DeviceAddressElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementDeviceDescriptionDataElements
 */
class NetworkManagementDeviceDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementDeviceDescriptionDataElements();

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
  bool operator==(const NetworkManagementDeviceDescriptionDataElements
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
  bool operator!=(const NetworkManagementDeviceDescriptionDataElements
                      &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member DeviceAddress.
   * @param c_deviceAddress Value to set
   */
  void setDeviceAddress(const DeviceAddressElements &c_deviceAddress);

  /**
   * Returns const reference to member DeviceAddress.
   * @return const reference to member deviceAddress
   */
  const DeviceAddressElements &getDeviceAddress() const;

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
   */
  void setDeviceType();

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
   */
  void setNetworkManagementResponsibleAddress();

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
   */
  void setNativeSetup();

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
   */
  void setTechnologyAddress();

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
   */
  void setCommunicationsTechnologyInformation();

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
   */
  void setNetworkFeatureSet();

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

  bool m_deviceAddressIsSet;
  DeviceAddressElements m_deviceAddress;

  // ElementTag
  bool m_deviceTypeIsSet;

  // ElementTag
  bool m_networkManagementResponsibleAddressIsSet;

  // ElementTag
  bool m_nativeSetupIsSet;

  // ElementTag
  bool m_technologyAddressIsSet;

  // ElementTag
  bool m_communicationsTechnologyInformationIsSet;

  // ElementTag
  bool m_networkFeatureSetIsSet;

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
//! NetworkManagementDeviceDescriptionDataElements
using NetworkManagementDeviceDescriptionDataElementsPtr =
    std::shared_ptr<NetworkManagementDeviceDescriptionDataElements>;

//! typedef for const type NetworkManagementDeviceDescriptionDataElements
using NetworkManagementDeviceDescriptionDataElementsConst =
    const NetworkManagementDeviceDescriptionDataElements;

//! typedef for const type NetworkManagementDeviceDescriptionDataElements
using NetworkManagementDeviceDescriptionDataElementsConstPtr =
    std::shared_ptr<NetworkManagementDeviceDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONDATAELEMENTS_H_