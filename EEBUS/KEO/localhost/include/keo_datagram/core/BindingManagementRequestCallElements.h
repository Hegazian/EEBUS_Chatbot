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

#ifndef KEO_DATAGRAM_CORE_BINDINGMANAGEMENTREQUESTCALLELEMENTS_H_
#define KEO_DATAGRAM_CORE_BINDINGMANAGEMENTREQUESTCALLELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/FeatureAddressElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration BindingManagementRequestCallElements
 */
class BindingManagementRequestCallElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  BindingManagementRequestCallElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_clientAddress the member to set
   * @param c_serverAddress the member to set
   * @param c_serverFeatureTypeIsSet the member to set
   */
  BindingManagementRequestCallElements(
      const FeatureAddressElements &c_clientAddress,
      const FeatureAddressElements &c_serverAddress,
      xs_boolean c_serverFeatureTypeIsSet);

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
  operator==(const BindingManagementRequestCallElements &c_classObject) const;

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
  operator!=(const BindingManagementRequestCallElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member ClientAddress.
   * @param c_clientAddress Value to set
   */
  void setClientAddress(const FeatureAddressElements &c_clientAddress);

  /**
   * Returns const reference to member ClientAddress.
   * @return const reference to member clientAddress
   */
  const FeatureAddressElements &getClientAddress() const;

  /**
   * Returns if member ClientAddress is set.
   * @retval true member ClientAddress is set
   * @retval false member ClientAddress is not set
   */
  bool getClientAddressIsSet() const;

  /**
   * Unsets member ClientAddress
   */
  void cleanClientAddress();

  /**
   * Set member ServerAddress.
   * @param c_serverAddress Value to set
   */
  void setServerAddress(const FeatureAddressElements &c_serverAddress);

  /**
   * Returns const reference to member ServerAddress.
   * @return const reference to member serverAddress
   */
  const FeatureAddressElements &getServerAddress() const;

  /**
   * Returns if member ServerAddress is set.
   * @retval true member ServerAddress is set
   * @retval false member ServerAddress is not set
   */
  bool getServerAddressIsSet() const;

  /**
   * Unsets member ServerAddress
   */
  void cleanServerAddress();

  /**
   * Set member ServerFeatureType.
   */
  void setServerFeatureType();

  /**
   * Returns if member ServerFeatureType is set.
   * @retval true member ServerFeatureType is set
   * @retval false member ServerFeatureType is not set
   */
  bool getServerFeatureTypeIsSet() const;

  /**
   * Unsets member ServerFeatureType
   */
  void cleanServerFeatureType();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_clientAddressIsSet;
  FeatureAddressElements m_clientAddress;

  bool m_serverAddressIsSet;
  FeatureAddressElements m_serverAddress;

  // ElementTag
  bool m_serverFeatureTypeIsSet;
};

//! typedef for non-const smart pointer type
//! BindingManagementRequestCallElements
using BindingManagementRequestCallElementsPtr =
    std::shared_ptr<BindingManagementRequestCallElements>;

//! typedef for const type BindingManagementRequestCallElements
using BindingManagementRequestCallElementsConst =
    const BindingManagementRequestCallElements;

//! typedef for const type BindingManagementRequestCallElements
using BindingManagementRequestCallElementsConstPtr =
    std::shared_ptr<BindingManagementRequestCallElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_BINDINGMANAGEMENTREQUESTCALLELEMENTS_H_