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

#ifndef KEO_DATAGRAM_CORE_BINDINGMANAGEMENTENTRYLISTDATASELECTORS_H_
#define KEO_DATAGRAM_CORE_BINDINGMANAGEMENTENTRYLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/BindingManagementEntryData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration BindingManagementEntryListDataSelectors
 */
class BindingManagementEntryListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  BindingManagementEntryListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_bindingId the member to set
   * @param c_clientAddress the member to set
   * @param c_serverAddress the member to set
   */
  BindingManagementEntryListDataSelectors(
      const xs_unsignedInt &c_bindingId, const FeatureAddress &c_clientAddress,
      const FeatureAddress &c_serverAddress);

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
      const BindingManagementEntryListDataSelectors &c_classObject) const;

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
      const BindingManagementEntryListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member BindingId.
   * @param c_bindingId Value to set
   */
  void setBindingId(const xs_unsignedInt &c_bindingId);

  /**
   * Returns const reference to member BindingId.
   * @return const reference to member bindingId
   */
  const xs_unsignedInt &getBindingId() const;

  /**
   * Returns if member BindingId is set.
   * @retval true member BindingId is set
   * @retval false member BindingId is not set
   */
  bool getBindingIdIsSet() const;

  /**
   * Unsets member BindingId
   */
  void cleanBindingId();

  /**
   * Set member ClientAddress.
   * @param c_clientAddress Value to set
   */
  void setClientAddress(const FeatureAddress &c_clientAddress);

  /**
   * Returns const reference to member ClientAddress.
   * @return const reference to member clientAddress
   */
  const FeatureAddress &getClientAddress() const;

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
  void setServerAddress(const FeatureAddress &c_serverAddress);

  /**
   * Returns const reference to member ServerAddress.
   * @return const reference to member serverAddress
   */
  const FeatureAddress &getServerAddress() const;

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
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const BindingManagementEntryData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_bindingIdIsSet;
  xs_unsignedInt m_bindingId;

  bool m_clientAddressIsSet;
  FeatureAddress m_clientAddress;

  bool m_serverAddressIsSet;
  FeatureAddress m_serverAddress;
};

//! typedef for non-const smart pointer type
//! BindingManagementEntryListDataSelectors
using BindingManagementEntryListDataSelectorsPtr =
    std::shared_ptr<BindingManagementEntryListDataSelectors>;

//! typedef for const type BindingManagementEntryListDataSelectors
using BindingManagementEntryListDataSelectorsConst =
    const BindingManagementEntryListDataSelectors;

//! typedef for const type BindingManagementEntryListDataSelectors
using BindingManagementEntryListDataSelectorsConstPtr =
    std::shared_ptr<BindingManagementEntryListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_BINDINGMANAGEMENTENTRYLISTDATASELECTORS_H_