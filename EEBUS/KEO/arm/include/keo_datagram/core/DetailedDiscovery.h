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

#ifndef KEO_DATAGRAM_CORE_DETAILEDDISCOVERY_H_
#define KEO_DATAGRAM_CORE_DETAILEDDISCOVERY_H_

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

#include <map>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

#include <keo_datagram/core/Cmd.h>
#include <keo_datagram/core/NetworkManagementEntityDescriptionData.h>
#include <keo_datagram/core/NetworkManagementFeatureDescriptionData.h>
#include <keo_datagram/core/NodeManagementDetailedDiscoveryData.h>

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  class definition                                                          *
 * ************************************************************************** */

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/* ******************************************************************************
 * *
 *  class DetailedDiscovery: definition
 * ******************************************************************************
 */
/** Utility class to handle detailed discovery **/
class DetailedDiscovery {
public:
  DetailedDiscovery();

  ~DetailedDiscovery();

  /// copy constructor
  DetailedDiscovery(const DetailedDiscovery &that);

  /// assignment operator
  DetailedDiscovery &operator=(const DetailedDiscovery &that);

  /// Resets all data
  void clear();

  /// Check if empty
  bool isEmpty() const;

  /** Sets the data class by a NodeManagementDetailedDiscoveryInformation reply
   * or notification payload.
   * This method expects a nodeManagementDetailedDiscovery cmd with full
   * descriptions of entities and features.
   * Already stored data will be replaced.
   *
   * @param cmd Command.
   *
   * @return true if successful. Note: The data might be invalid if failed.
   */
  bool setDiscoveryInformationFromCmd(const Cmd &cmd);

  /// Returns the specification version list data.
  NodeManagementSpecificationVersionList getSpecificationVersionList() const;

  /// Sets the specification version list data.
  void
  setSpecificationVersionList(const NodeManagementSpecificationVersionList &);

  /// Gets the device description.
  NetworkManagementDeviceDescriptionData getDeviceDescription() const;

  /// Sets the device description.
  void setDeviceDescription(const NetworkManagementDeviceDescriptionData &);

  /** Sets the detailed discovery information.
   *  It is possible to leave entity and feature information empty. If the node
   * description data and/or
   *  the device description is already set, it will be replaced.
   *
   *  Already stored data will be replaced.
   *
   *  @pre
   *  - SpecificationVersionListData().getSpecificationVersionDataIsSet()
   *  - NetworkManagementNodeDescriptionData().getNodeAddress().getDeviceIsSet()
   *  Entity:
   *  - NetworkManagementNodeDescriptionData().getNodeAddressIsSet()
   *  - !NetworkManagementEntityDescriptionDataIsSet() ||
   *  NetworkManagementEntityDescriptionData().getEntityTypeIsSet() &&
   *  NetworkManagementEntityDescriptionData().getEntityTypeVersionIsSet()
   *  Feature:
   *  - Entity exists
   *  - NetworkManagementFeatureDescriptionDataIsSet()
   *  - NetworkManagementNodeDescriptionData().getNodeAddress().getEntityIsSet()
   *  -
   * NetworkManagementNodeDescriptionData().getNodeAddress().getFeatureIsSet()
   *  - NetworkManagementFeatureDescriptionData().getRoleIsSet()
   */
  bool setDetailedDiscoveryData(const NodeManagementDetailedDiscoveryData &);

  /** Returns the detailed discovery information for the device itself.
   *
   * @return Detailed discovery information.
   */
  NodeManagementDetailedDiscoveryDataPtr getDetailedDiscoveryDataPtr() const;

  /**
   * Check if device name is set
   * @return true if set, otherwise false
   */
  bool getDeviceNameIsSet() const;

  /**
   * get device name
   * @return the device address part of the device description data
   */
  std::string getDeviceName() const;

  /** Adds detailed discovery data for an entity.
   * Existing discovery data for the entity will be overwritten.
   *
   * @pre
   *  - NetworkManagementNodeDescriptionData().getNodeAddressIsSet()
   *  - !NetworkManagementEntityDescriptionDataIsSet() ||
   *  NetworkManagementEntityDescriptionData().getEntityTypeIsSet() &&
   *  NetworkManagementEntityDescriptionData().getEntityTypeVersionIsSet()
   */
  bool addDetailedDiscoveryEntityInformation(
      const NodeManagementDetailedDiscoveryEntityInformation &);

  /** Returns the detailed discovery information for an entity.
   *
   * @param entityAddress Entity address.
   * @return Discovery information for the entity or empty object if address did
   * not exists.
   */
  NodeManagementDetailedDiscoveryEntityInformationPtr
  getDetailedDiscoveryEntityInformation(
      const std::vector<xs_unsignedInt> &entityAddress) const;

  /** Adds detailed discovery data for a feature.
   * Existing discovery data for the feature will be overwritten.
   *
   * @pre
   *  - Entity exists
   *  - NetworkManagementFeatureDescriptionDataIsSet()
   *  - NetworkManagementNodeDescriptionData().getNodeAddress().getEntityIsSet()
   *  -
   * NetworkManagementNodeDescriptionData().getNodeAddress().getFeatureIsSet()
   *  - NetworkManagementFeatureDescriptionData().getRoleIsSet()
   */
  bool addDetailedDiscoveryFeatureInformation(
      const NodeManagementDetailedDiscoveryFeatureInformation &);

  /** Returns the detailed discovery information for the feature.
   *
   * @param entityAddress Entity address.
   * @param featureId Feature identifier.
   * @return Discovery information for the feature or empty object if address
   * did not exists.
   */
  NodeManagementDetailedDiscoveryFeatureInformationPtr
  getDetailedDiscoveryFeatureInformation(
      const std::vector<xs_unsignedInt> &entityAddress,
      xs_unsignedInt featureId) const;

  /** Returns the detailed discovery feature information for all features of an
   * entity.
   *
   * @param entityAddress Entity address.
   * @return Discovery feature information for all features of the entity or
   * empty object if address did not exists.
   */
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getDetailedDiscoveryFeatureInformationByEntity(
      const std::vector<xs_unsignedInt> &entityAddress) const;

  /**
   * Checks whether this detailed discovery has a certain function in its
   * primary node management feature.
   *
   * \see Function
   *
   * @param function the function to search for
   * @return true, if the function has been found
   */
  bool hasFunction(const Function &function) const;

  /// Returns true if entity address exists.
  bool
  containsEntityAddress(const std::vector<xs_unsignedInt> &entityAddress) const;

  /// Returns true if entity type exists,
  bool containsEntityType(const EntityType &entityType) const;

  /// Returns true if entity type exists,
  bool containsEntityType(const std::string &entityType) const;

  /// Returns true if feature id exists for entity address.
  bool
  containsFeatureIdOnEntity(const std::vector<xs_unsignedInt> &entityAddress,
                            xs_unsignedInt featureId) const;

  /// Returns true if process id exists.
  bool containsFeatureType(const FeatureType &featureType) const;

  /// Returns true if process id exists.
  bool containsFeatureType(const std::string &featureType) const;

  /// Returns true if process id exists for entity address.
  bool
  containsFeatureTypeOnEntity(const std::vector<xs_unsignedInt> &entityAddress,
                              const FeatureType &featureType) const;

  /// Returns true if process id exists for entity address.
  bool
  containsFeatureTypeOnEntity(const std::vector<xs_unsignedInt> &entityAddress,
                              const std::string &featureType) const;

  /// Returns all entities.
  std::vector<std::vector<xs_unsignedInt>> getEntities() const;

  /// Returns the list of all entities with entity type entityType.
  std::vector<std::vector<xs_unsignedInt>>
  getEntitiesByEntityType(const EntityType &entityType) const;

  /// Returns the list of all entities with entity type entityType.
  std::vector<std::vector<xs_unsignedInt>>
  getEntitiesByEntityType(const std::string &entityType) const;

  /// Returns the list of all entities with feature type featureType.
  std::vector<std::vector<xs_unsignedInt>>
  getEntitiesByFeatureType(const FeatureType &featureType) const;

  /// Returns the list of all entities with feature type featureType.
  std::vector<std::vector<xs_unsignedInt>>
  getEntitiesByFeatureType(const std::string &featureType) const;

  /// Returns all features on entity entityAddress.
  std::vector<xs_unsignedInt>
  getFeatures(const std::vector<xs_unsignedInt> &entityAddress) const;

  /// Returns all features with feature type featureType on entity address
  /// entityAddress.
  std::vector<xs_unsignedInt>
  getFeaturesByFeatureType(const std::vector<xs_unsignedInt> &entityAddress,
                           const FeatureType &featureType) const;

  /// Returns all features with feature type featureType on entity address
  /// entityAddress.
  std::vector<xs_unsignedInt>
  getFeaturesByFeatureType(const std::vector<xs_unsignedInt> &entityAddress,
                           const std::string &featureType) const;

  /// Returns all function properties with feature on entity address
  /// entityAddress.
  std::vector<FunctionProperty>
  getFunctionPropertiesByFeature(const EntityAddress &entityAddress,
                                 xs_unsignedInt feature) const;

private:
  class DetailedDiscoveryImpl;

  DetailedDiscoveryImpl *d;

  friend class DetailedDiscoveryPartial;
};

//! typedef for non-const smart pointer type DetailedDiscovery
using DetailedDiscoveryPtr = std::shared_ptr<DetailedDiscovery>;

//! typedef for const type DetailedDiscovery
using DetailedDiscoveryConst = const DetailedDiscovery;

//! typedef for const smart pointer type DetailedDiscovery
using DetailedDiscoveryConstPtr = std::shared_ptr<DetailedDiscoveryConst>;

/** @}
 */

} // end namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_DETAILEDDISCOVERY_H_