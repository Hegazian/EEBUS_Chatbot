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

#ifndef KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONUSERDATA_H_
#define KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONUSERDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration DeviceClassificationUserData
 */
class DeviceClassificationUserData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  DeviceClassificationUserData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_userNodeIdentification the member to set
   * @param c_userLabel the member to set
   * @param c_userDescription the member to set
   */
  DeviceClassificationUserData(const xs_string &c_userNodeIdentification,
                               const xs_string &c_userLabel,
                               const xs_string &c_userDescription);

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
  bool operator==(const DeviceClassificationUserData &c_classObject) const;

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
  bool operator!=(const DeviceClassificationUserData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member UserNodeIdentification.
   * @param c_userNodeIdentification Value to set
   */
  void setUserNodeIdentification(const xs_string &c_userNodeIdentification);

  /**
   * Returns const reference to member UserNodeIdentification.
   * @return const reference to member userNodeIdentification
   */
  const xs_string &getUserNodeIdentification() const;

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
   * @param c_userLabel Value to set
   */
  void setUserLabel(const xs_string &c_userLabel);

  /**
   * Returns const reference to member UserLabel.
   * @return const reference to member userLabel
   */
  const xs_string &getUserLabel() const;

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
   * @param c_userDescription Value to set
   */
  void setUserDescription(const xs_string &c_userDescription);

  /**
   * Returns const reference to member UserDescription.
   * @return const reference to member userDescription
   */
  const xs_string &getUserDescription() const;

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_userNodeIdentificationIsSet;
  xs_string m_userNodeIdentification;

  bool m_userLabelIsSet;
  xs_string m_userLabel;

  bool m_userDescriptionIsSet;
  xs_string m_userDescription;
};

//! typedef for non-const smart pointer type DeviceClassificationUserData
using DeviceClassificationUserDataPtr =
    std::shared_ptr<DeviceClassificationUserData>;

//! typedef for const type DeviceClassificationUserData
using DeviceClassificationUserDataConst = const DeviceClassificationUserData;

//! typedef for const type DeviceClassificationUserData
using DeviceClassificationUserDataConstPtr =
    std::shared_ptr<DeviceClassificationUserDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_DEVICECLASSIFICATIONUSERDATA_H_