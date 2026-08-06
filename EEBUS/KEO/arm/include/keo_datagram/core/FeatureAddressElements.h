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

#ifndef KEO_DATAGRAM_CORE_FEATUREADDRESSELEMENTS_H_
#define KEO_DATAGRAM_CORE_FEATUREADDRESSELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration FeatureAddressElements
 */
class FeatureAddressElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  FeatureAddressElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_deviceIsSet the member to set
   * @param c_entityIsSet the member to set
   * @param c_featureIsSet the member to set
   */
  FeatureAddressElements(xs_boolean c_deviceIsSet, xs_boolean c_entityIsSet,
                         xs_boolean c_featureIsSet);

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
  bool operator==(const FeatureAddressElements &c_classObject) const;

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
  bool operator!=(const FeatureAddressElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Device.
   */
  void setDevice();

  /**
   * Returns if member Device is set.
   * @retval true member Device is set
   * @retval false member Device is not set
   */
  bool getDeviceIsSet() const;

  /**
   * Unsets member Device
   */
  void cleanDevice();

  /**
   * Set member Entity.
   */
  void setEntity();

  /**
   * Returns if member Entity is set.
   * @retval true member Entity is set
   * @retval false member Entity is not set
   */
  bool getEntityIsSet() const;

  /**
   * Unsets member Entity
   */
  void cleanEntity();

  /**
   * Set member Feature.
   */
  void setFeature();

  /**
   * Returns if member Feature is set.
   * @retval true member Feature is set
   * @retval false member Feature is not set
   */
  bool getFeatureIsSet() const;

  /**
   * Unsets member Feature
   */
  void cleanFeature();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_deviceIsSet;

  // ElementTag
  bool m_entityIsSet;

  // ElementTag
  bool m_featureIsSet;
};

//! typedef for non-const smart pointer type FeatureAddressElements
using FeatureAddressElementsPtr = std::shared_ptr<FeatureAddressElements>;

//! typedef for const type FeatureAddressElements
using FeatureAddressElementsConst = const FeatureAddressElements;

//! typedef for const type FeatureAddressElements
using FeatureAddressElementsConstPtr =
    std::shared_ptr<FeatureAddressElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_FEATUREADDRESSELEMENTS_H_