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

#ifndef KEO_DATAGRAM_CORE_ENTITYADDRESSELEMENTS_H_
#define KEO_DATAGRAM_CORE_ENTITYADDRESSELEMENTS_H_

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
 * Declaration EntityAddressElements
 */
class EntityAddressElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  EntityAddressElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_deviceIsSet the member to set
   * @param c_entityIsSet the member to set
   */
  EntityAddressElements(xs_boolean c_deviceIsSet, xs_boolean c_entityIsSet);

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
  bool operator==(const EntityAddressElements &c_classObject) const;

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
  bool operator!=(const EntityAddressElements &c_classObject) const;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_deviceIsSet;

  // ElementTag
  bool m_entityIsSet;
};

//! typedef for non-const smart pointer type EntityAddressElements
using EntityAddressElementsPtr = std::shared_ptr<EntityAddressElements>;

//! typedef for const type EntityAddressElements
using EntityAddressElementsConst = const EntityAddressElements;

//! typedef for const type EntityAddressElements
using EntityAddressElementsConstPtr =
    std::shared_ptr<EntityAddressElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_ENTITYADDRESSELEMENTS_H_