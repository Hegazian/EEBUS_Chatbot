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

#ifndef KEO_DATAGRAM_CORE_FEATUREADDRESS_H_
#define KEO_DATAGRAM_CORE_FEATUREADDRESS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/FeatureAddressElements.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration FeatureAddress
 */
class FeatureAddress : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  FeatureAddress();

  /**
   * Copy constructor.
   *
   * @param c_classObject object to be copied
   */
  FeatureAddress(const FeatureAddress &c_classObject);

  /**
   * Construct a new instance.
   *
   * Note that if an empty string is passed for the device part of the address,
   * no device part is
   * set. If that is desired, one of the constructors
   * FeatureAddress(const std::uint32_t& c_entity, const std::uint32_t&
   * c_feature)
   * FeatureAddress(const std::vector<std::uint32_t>& c_entity, const
   * std::uint32_t& c_feature)
   * should be preffered.
   *
   * @param c_device the device part of the address
   * @param c_entity the entity part of the address
   * @param c_feature the feature id of the address
   */
  FeatureAddress(const std::string &c_device,
                 const std::vector<std::uint32_t> &c_entity,
                 const std::uint32_t &c_feature);

  /**
   * Construct a new instance.
   *
   * Note that if an empty string is passed for the device part of the address,
   * no device part is
   * set. If that is desired, one of the constructors
   * FeatureAddress(const std::uint32_t& c_entity, const std::uint32_t&
   * c_feature)
   * FeatureAddress(const std::vector<std::uint32_t>& c_entity, const
   * std::uint32_t& c_feature)
   * should be preffered.
   *
   * @param c_device the device part of the address
   * @param c_entity the entity part of the address (single-element)
   * @param c_feature the feature id of the address
   */
  FeatureAddress(const std::string &c_device, const std::uint32_t &c_entity,
                 const std::uint32_t &c_feature);

  /**
   * Construct a new instance.
   *
   * @param c_entity the entity part of the address
   * @param c_feature the feature id of the address
   */
  FeatureAddress(const std::vector<std::uint32_t> &c_entity,
                 const std::uint32_t &c_feature);

  /**
   * Construct a new instance.
   *
   * @param c_entity the entity part of the address (single-element)
   * @param c_feature the feature id of the address
   */
  FeatureAddress(const std::uint32_t &c_entity, const std::uint32_t &c_feature);

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
  bool operator==(const FeatureAddress &c_classObject) const;

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
  bool operator!=(const FeatureAddress &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Relational operator >
   * @param c_classObject object to compare
   */
  bool operator>(const FeatureAddress &c_classObject) const;

  /**
   * Relational operator <
   * @param c_classObject object to compare
   */
  bool operator<(const FeatureAddress &c_classObject) const;

  /**
   * Compare this instance to another FeatureAddress, but ignore the device part
   * if it is not set
   * in both addresses.
   * @param c_classObject FeatureAddress to compare
   * @return true if equal
   */
  bool equalsWeak(const FeatureAddress &c_classObject) const;

  /**
   * Set member Device.
   * @param c_device Value to set
   */
  void setDevice(const xs_string &c_device);

  /**
   * Returns const reference to member Device.
   * @return const reference to member device
   */
  const xs_string &getDevice() const;

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
   * @param c_entity Value to set
   */
  void setEntity(const std::vector<xs_unsignedInt> &c_entity);

  /**
   * Returns const reference to member Entity.
   * @return const reference to member entity
   */
  const std::vector<xs_unsignedInt> &getEntity() const;

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
   * @param c_feature Value to set
   */
  void setFeature(const xs_unsignedInt &c_feature);

  /**
   * Returns const reference to member Feature.
   * @return const reference to member feature
   */
  const xs_unsignedInt &getFeature() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  FeatureAddress reduce(const FeatureAddressElements &elements) const;

  /**
   * Returns this SPINE feature address as a string.
   * @return the address as a string
   */
  std::string toString() const;

  /**
   * Set this instance from a string representing a SPINE feature address.
   * @param c_addressString string representation of the address
   * @return true on success, else false
   */
  bool fromString(const std::string &c_addressString);

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_deviceIsSet;
  xs_string m_device;

  bool m_entityIsSet;
  std::vector<xs_unsignedInt> m_entity;

  bool m_featureIsSet;
  xs_unsignedInt m_feature;
};

//! typedef for non-const smart pointer type FeatureAddress
using FeatureAddressPtr = std::shared_ptr<FeatureAddress>;

//! typedef for const type FeatureAddress
using FeatureAddressConst = const FeatureAddress;

//! typedef for const type FeatureAddress
using FeatureAddressConstPtr = std::shared_ptr<FeatureAddressConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_FEATUREADDRESS_H_