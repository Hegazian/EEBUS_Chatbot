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

#ifndef KEO_DATAGRAM_CORE_DETAILEDDISCOVERYPARTIAL_H_
#define KEO_DATAGRAM_CORE_DETAILEDDISCOVERYPARTIAL_H_

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */
#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/DetailedDiscovery.h>

/* ******************************************************************************
 * *
 *  defines *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  types *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  class definition *
 * ******************************************************************************
 */

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

class DetailedDiscoveryPartial {
public:
  DetailedDiscoveryPartial();
  ~DetailedDiscoveryPartial();
  DetailedDiscoveryPartial(const DetailedDiscoveryPartial &that);
  DetailedDiscoveryPartial &operator=(const DetailedDiscoveryPartial &that);

  /**
   * Set this partial Detailed Discovery by comparing ("diff-ing") two existing
   * Detailed Discoveries.
   *
   * @param sourceDetailedDiscovery
   *          the source DetailedDiscovery
   * @param targetDetailedDiscovery
   *          the target DetailedDiscovery
   * @return true on success, otherwise false
   */
  bool setByDiffingDetailedDiscoveries(
      const DetailedDiscovery &sourceDetailedDiscovery,
      const DetailedDiscovery &targetDetailedDiscovery);

  /**
   * Merge this partial DetailedDiscovery into a full DetailedDiscovery. This
   * will apply all changes, described by this partial DetailedDiscovery, to
   * the original DetailedDiscovery.
   * @param sourceDetailedDiscovery
   *       the original DetailedDiscovery
   * @param success
           pointer to bool to indicate success (nullptr is allowed)
   * @return A DetailedDiscovery including the changes described by this
   *         partial DetailedDiscovery
   */
  DetailedDiscovery
  getMergedDetailedDiscovery(const DetailedDiscovery &sourceDetailedDiscovery,
                             bool *success) const;

  /**
   * Sets the (partial) detailed discovery information.
   * It is possible to leave entity and feature information empty.
   * Already stored data will be replaced.
   * @param detailedDiscoveryData
   *      the NodeManagementDetailedDiscoveryData detailed discovery to set
   * @return true on success, otherwise false
   */
  bool setDetailedDiscoveryData(
      const NodeManagementDetailedDiscoveryData &detailedDiscoveryData);

  /** Returns the (partial) detailed discovery information.
   *
   * @return Detailed discovery information.
   */
  NodeManagementDetailedDiscoveryDataPtr getDetailedDiscoveryDataPtr() const;

  /**
   * Adds detailed discovery data for an entity.
   * Existing discovery data for the entity will be overwritten.
   * @param entityInformation
   *          the entity information
   * @return true on success, otherwise false
   */
  bool addDetailedDiscoveryEntityInformation(
      const NodeManagementDetailedDiscoveryEntityInformation
          &entityInformation);

  /**
   * Adds detailed discovery data for a feature.
   * Existing discovery data for the feature will be overwritten.
   * @param featureInformation
   *          the feature information
   * @return true on success, otherwise false
   */
  bool addDetailedDiscoveryFeatureInformation(
      const NodeManagementDetailedDiscoveryFeatureInformation
          &featureInformation);

  /** Returns the detailed discovery information for an entity.
   *
   * @param entityAddress Entity address.
   * @return Discovery information for the entity or empty object if address did
   * not exists.
   */
  NodeManagementDetailedDiscoveryEntityInformationPtr
  getDetailedDiscoveryEntityInformation(
      const std::vector<xs_unsignedInt> &entityAddress) const;

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

  /**
   * Creates a detailed discovery datagram with cmdOption partial set.
   * @param header
   *      Header for the datagram (source, destination, classifier)
   * @return
   *      The datagram ready to send.
   */
  Datagram createPartialDetailedDiscoveryDatagram(const Header &header) const;

  /**
   * Returns DetailedDiscovery datagram with cmdOption partial set.
   * @deprecated Use createPartialDetailedDiscoveryDatagram(const Header&
   * header) const instead.
   * @param header
   *      Header for the datagram (source, destination, classifier)
   * @return
   *      The datagram ready to send.
   */
  DatagramPtr
  getPartialDetailedDiscoveryDatagram(const HeaderPtr &header) const;

  /**
   * Returns if the device name is set.
   * @return true if set, otherwise false
   */
  bool getDeviceNameIsSet() const;

  /**
   * Returns the device name.
   * @return the device name
   */
  std::string getDeviceName() const;

  /**
   * Sets the device name.
   * @param deviceName
   *      the device name to set
   */
  void setDeviceName(const std::string &deviceName);

  /**
   * Checks whether this partial detailed discovery is empty or not. It is
   * empty,
   * if it does not contain any information about entities and features.
   * @return true, if this partial detailed discovery is empty
   */
  bool isEmpty() const;

  /**
   * Get a list of all added entities.
   * @return a list of all added entities
   */
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getAddedEntities() const;

  /**
   * Get a list of all modified entities.
   * @return a list of all modified entities
   */
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getModifiedEntities() const;

  /**
   * Get a list of all removed entities.
   * @return a list of all removed entities
   */
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getRemovedEntities() const;

  /**
   * Checks whether an entity has been modified.
   * @param entityAddress
   *      the address of the entity
   * @return true, if the entity has been modified
   */
  bool isEntityModified(const EntityAddress &entityAddress) const;

  /**
   * Checks whether an entity has been removed.
   * @param entityAddress
   *      the address of the entity
   * @return true, if the entity has been removed
   */
  bool isEntityRemoved(const EntityAddress &entityAddress) const;

  /**
   * Get a list of all added features.
   * @return  a list of all added features
   */
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getAddedFeatures() const;

  /**
   * Get a list of all modified features.
   * @return  a list of all modified features
   */
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getModifiedFeatures() const;

  /**
   * Get a list of all removed features.
   *
   * Note that the list will not contain features that have been removed
   * because their parent entity has been removed. In that case only
   * getRemovedEntities() will return that the entity has been removed.
   *
   * @return a list of removed features
   */
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getRemovedFeatures() const;

  /**
   * Checks whether a feature has been modified.
   * @param featureAddress
   *      the address of the feature
   * @return true, if the feature has been modified
   */
  bool isFeatureModified(const FeatureAddress &featureAddress) const;

  /**
   * Checks whether a feature has been removed.
   *
   * Note that this method will not return true for features that have been
   * removed because their parent entity has been removed. In that case only
   * getRemovedEntities() will return that the entity has been removed.
   *
   * @param featureAddress
   *      the address of the feature
   * @return true, if the feature has been removed
   */
  bool isFeatureRemoved(const FeatureAddress &featureAddress) const;

private:
  class DetailedDiscoveryPartialImpl;
  DetailedDiscoveryPartialImpl *d;
};

inline DatagramPtr
DetailedDiscoveryPartial::getPartialDetailedDiscoveryDatagram(
    const HeaderPtr &header) const {
  return std::make_shared<Datagram>(
      createPartialDetailedDiscoveryDatagram(*header.get()));
}

//! typedef for non-const smart pointer type DetailedDiscoveryPartial
using DetailedDiscoveryPartialPtr = std::shared_ptr<DetailedDiscoveryPartial>;

//! typedef for const type DetailedDiscoveryPartial
using DetailedDiscoveryPartialConst = const DetailedDiscoveryPartial;

//! typedef for const smart pointer type DetailedDiscoveryPartial
using DetailedDiscoveryPartialConstPtr =
    std::shared_ptr<DetailedDiscoveryPartialConst>;

/** @}
 */

} /* namespace keo_datagram */

#endif // KEO_DATAGRAM_CORE_DETAILEDDISCOVERYPARTIAL_H_