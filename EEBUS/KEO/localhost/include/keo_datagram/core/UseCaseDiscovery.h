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

#ifndef KEO_DATAGRAM_CORE_USECASEDISCOVERY_H_
#define KEO_DATAGRAM_CORE_USECASEDISCOVERY_H_

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */
#include <string>
#include <vector>

/* ************************************************************************** *
 *  KEO header files                                                      *
 * ************************************************************************** */
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/NodeManagementUseCaseData.h>
#include <keo_datagram/core/xs_types.h>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

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

/**
 * Utility class for SPINE use case discovery.
 **/
class UseCaseDiscovery {
public:
  UseCaseDiscovery(NodeManagementUseCaseData const &ownUseCaseData,
                   NodeManagementUseCaseData const &remoteUseCaseData);
  virtual ~UseCaseDiscovery();

  UseCaseDiscovery(UseCaseDiscovery const &other);
  UseCaseDiscovery(UseCaseDiscovery &&other);
  UseCaseDiscovery &operator=(UseCaseDiscovery const &other);
  UseCaseDiscovery &operator=(UseCaseDiscovery &&other);

  /**
   * Get own addresses that currently support certain use cases.
   *
   * Note, that according to the SPINE specification these addresses must be
   * addresses that are
   * always present in the corresponding detailed disocvery. As a consequence
   * they may not have an
   * entity address or feature id set even though they are modelled as
   * FeatureAddresses. In that
   * case, only the parent device or entity that supports the use case is
   * specified.
   *
   * @param useCaseName the use case name to search (empty string to search for
   * all use cases)
   * @param useCaseVersion the use case version to search (empty string to
   * search for all versions)
   * @param scenarios the scenarios to search (empty vector to search for all
   * scenarios)
   * @param actor the actor to search (empty string to search for all actors)
   * @return the FeatureAddresses
   */
  std::vector<FeatureAddress>
  getOwnAddressesSupporting(std::string const &useCaseName = "",
                            std::string const &useCaseVersion = "",
                            std::vector<xs_unsignedInt> const &scenarios = {},
                            std::string const &actor = "") const;

  /**
   * Get own addresses that currently support certain use cases.
   *
   * Note, that according to the SPINE specification these addresses must be
   * addresses that are
   * always present in the corresponding detailed disocvery. As a consequence
   * they may not have an
   * entity address or feature id set even though they are modelled as
   * FeatureAddresses. In that
   * case, only the parent device or entity that supports the use case is
   * specified.
   *
   * @param useCaseSupport the use case to search for
   * @param actor the actor to search (empty string to search for all actors)
   * @return the FeatureAddresses
   */
  std::vector<FeatureAddress>
  getOwnAddressesSupporting(UseCaseSupport const &useCaseSupport,
                            std::string const &actor = "") const;

  /**
   * Get remote addresses that currently support certain use cases.
   *
   * Note, that according to the SPINE specification these addresses must be
   * addresses that are
   * always present in the corresponding detailed disocvery. As a consequence
   * they may not have an
   * entity address or feature id set even though they are modelled as
   * FeatureAddresses. In that
   * case, only the parent device or entity that supports the use case is
   * specified.
   *
   * @param useCaseName the use case name to search (empty string to search for
   * all use cases)
   * @param useCaseVersion the use case version to search (empty string to
   * search for all versions)
   * @param scenarios the scenarios to search (empty vector to search for all
   * scenarios)
   * @param actor the actor to search (empty string to search for all actors)
   * @return the FeatureAddresses
   */
  std::vector<FeatureAddress> getRemoteAddressesSupporting(
      std::string const &useCaseName = "",
      std::string const &useCaseVersion = "",
      std::vector<xs_unsignedInt> const &scenarios = {},
      std::string const &actor = "") const;

  /**
   * Get remote addresses that currently support certain use cases.
   *
   * Note, that according to the SPINE specification these addresses must be
   * addresses that are
   * always present in the corresponding detailed disocvery. As a consequence
   * they may not have an
   * entity address or feature id set even though they are modelled as
   * FeatureAddresses. In that
   * case, only the parent device or entity that supports the use case is
   * specified.
   *
   * @param actor the actor to search (empty string to search for all actors)
   * @param useCaseSupport the use case to search for
   * @return the FeatureAddresses
   */
  std::vector<FeatureAddress>
  getRemoteAddressesSupporting(UseCaseSupport const &useCaseSupport,
                               std::string const &actor = "") const;

  /**
   * Check if own use case data supports certain use cases.
   *
   * @param useCaseName the use case name to search (empty string to check all
   * use cases)
   * @param useCaseVersion the use case version to search (empty string to check
   * all versions)
   * @param scenarios the scenarios to search (empty vector to check all
   * scenarios)
   * @param actor the actor to search (empty string to check all actors)
   * @return true, if the remote supports the use case(s)
   */
  bool selfSupports(std::string const &useCaseName = "",
                    std::string const &useCaseVersion = "",
                    std::vector<xs_unsignedInt> const &scenarios = {},
                    std::string const &actor = "") const;

  /**
   * Check if the remote supports certain use cases.
   *
   * @param useCaseName the use case name to search (empty string to check all
   * use cases)
   * @param useCaseVersion the use case version to search (empty string to check
   * all versions)
   * @param scenarios the scenarios to search (empty vector to check all
   * scenarios)
   * @param actor the actor to search (empty string to check all actors)
   * @return true, if the remote supports the use case(s)
   */
  bool remoteSupports(std::string const &useCaseName = "",
                      std::string const &useCaseVersion = "",
                      std::vector<xs_unsignedInt> const &scenarios = {},
                      std::string const &actor = "") const;

  /**
   * Get all use cases that are supported in both use case lists.
   *
   * This will not return use cases that are currently not available
   * (useCaseAvailable=false).
   *
   * @return all supported use cases
   */
  std::vector<UseCaseSupport> getMatchingUseCases() const;

  NodeManagementUseCaseData const &getOwnUseCaseData() const;
  NodeManagementUseCaseData const &getRemoteUseCaseData() const;

private:
  class UseCaseDiscoveryImpl;
  UseCaseDiscoveryImpl *d;
};

/** @}
 */

} // end namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_USECASEDISCOVERY_H_