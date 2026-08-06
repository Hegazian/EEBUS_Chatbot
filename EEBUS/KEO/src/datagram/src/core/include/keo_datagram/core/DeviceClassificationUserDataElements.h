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

#ifndef KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONUSERDATAELEMENTS_H_
#define KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONUSERDATAELEMENTS_H_

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
 * Declaration DeviceClassificationUserDataElements
 */
class DeviceClassificationUserDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  DeviceClassificationUserDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_userNodeIdentificationIsSet the member to set
   * @param c_userLabelIsSet the member to set
   * @param c_userDescriptionIsSet the member to set
   */
  DeviceClassificationUserDataElements(xs_boolean c_userNodeIdentificationIsSet,
                                       xs_boolean c_userLabelIsSet,
                                       xs_boolean c_userDescriptionIsSet);

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
  operator==(const DeviceClassificationUserDataElements &c_classObject) const;

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
  operator!=(const DeviceClassificationUserDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member UserNodeIdentification.
   */
  void setUserNodeIdentification();

  /**
   * Returns if member UserNodeIdentification is set.
   * @retval true member UserNodeIdentification is set
   * @retval false member UserNodeIdentification is not set
   */
  bool getUserNodeIdentificationIsSet() const;

  /**
   * Unsets member UserNodeIdentification
   */
  void cleanUserNodeIdentification();

  /**
   * Set member UserLabel.
   */
  void setUserLabel();

  /**
   * Returns if member UserLabel is set.
   * @retval true member UserLabel is set
   * @retval false member UserLabel is not set
   */
  bool getUserLabelIsSet() const;

  /**
   * Unsets member UserLabel
   */
  void cleanUserLabel();

  /**
   * Set member UserDescription.
   */
  void setUserDescription();

  /**
   * Returns if member UserDescription is set.
   * @retval true member UserDescription is set
   * @retval false member UserDescription is not set
   */
  bool getUserDescriptionIsSet() const;

  /**
   * Unsets member UserDescription
   */
  void cleanUserDescription();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_userNodeIdentificationIsSet;

  // ElementTag
  bool m_userLabelIsSet;

  // ElementTag
  bool m_userDescriptionIsSet;
};

//! typedef for non-const smart pointer type
//! DeviceClassificationUserDataElements
using DeviceClassificationUserDataElementsPtr =
    std::shared_ptr<DeviceClassificationUserDataElements>;

//! typedef for const type DeviceClassificationUserDataElements
using DeviceClassificationUserDataElementsConst =
    const DeviceClassificationUserDataElements;

//! typedef for const type DeviceClassificationUserDataElements
using DeviceClassificationUserDataElementsConstPtr =
    std::shared_ptr<DeviceClassificationUserDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONUSERDATAELEMENTS_H_