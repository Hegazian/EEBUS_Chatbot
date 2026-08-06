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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTPROCESSSTATEDATAELEMENTS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTPROCESSSTATEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementProcessStateDataElements
 */
class NetworkManagementProcessStateDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementProcessStateDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_stateIsSet the member to set
   * @param c_descriptionIsSet the member to set
   */
  NetworkManagementProcessStateDataElements(xs_boolean c_stateIsSet,
                                            xs_boolean c_descriptionIsSet);

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
      const NetworkManagementProcessStateDataElements &c_classObject) const;

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
      const NetworkManagementProcessStateDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member State.
   */
  void setState();

  /**
   * Returns if member State is set.
   * @retval true member State is set
   * @retval false member State is not set
   */
  bool getStateIsSet() const;

  /**
   * Unsets member State
   */
  void cleanState();

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

  // ElementTag
  bool m_stateIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type
//! NetworkManagementProcessStateDataElements
using NetworkManagementProcessStateDataElementsPtr =
    std::shared_ptr<NetworkManagementProcessStateDataElements>;

//! typedef for const type NetworkManagementProcessStateDataElements
using NetworkManagementProcessStateDataElementsConst =
    const NetworkManagementProcessStateDataElements;

//! typedef for const type NetworkManagementProcessStateDataElements
using NetworkManagementProcessStateDataElementsConstPtr =
    std::shared_ptr<NetworkManagementProcessStateDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTPROCESSSTATEDATAELEMENTS_H_