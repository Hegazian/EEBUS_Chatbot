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

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  KEO header files                                                      *
 * ************************************************************************** */
#include <keo_datagram/core/UseCaseDiscovery.h>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */
#include "UseCaseDiscoveryImpl.h"

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  definition                                                                *
 * ************************************************************************** */

namespace keo_datagram {

UseCaseDiscovery::UseCaseDiscovery(
    NodeManagementUseCaseData const &ownUseCaseData,
    NodeManagementUseCaseData const &remoteUseCaseData)
    : d(new UseCaseDiscoveryImpl(ownUseCaseData, remoteUseCaseData)) {}

UseCaseDiscovery::~UseCaseDiscovery() { delete d; }

UseCaseDiscovery::UseCaseDiscovery(UseCaseDiscovery const &other)
    : d(new UseCaseDiscoveryImpl(other.getOwnUseCaseData(),
                                 other.getRemoteUseCaseData())) {}

UseCaseDiscovery::UseCaseDiscovery(UseCaseDiscovery &&other)
    : d(new UseCaseDiscoveryImpl(std::move(other.d->ownUseCaseData),
                                 std::move(other.d->remoteUseCaseData))) {}

UseCaseDiscovery &UseCaseDiscovery::operator=(UseCaseDiscovery const &other) {
  if (this != &other) {
    d->ownUseCaseData = other.d->ownUseCaseData;
    d->remoteUseCaseData = other.d->remoteUseCaseData;
  }
  return *this;
}

UseCaseDiscovery &UseCaseDiscovery::operator=(UseCaseDiscovery &&other) {
  if (this != &other) {
    d->ownUseCaseData = std::move(other.d->ownUseCaseData);
    d->remoteUseCaseData = std::move(other.d->remoteUseCaseData);
  }
  return *this;
}

std::vector<FeatureAddress> UseCaseDiscovery::getOwnAddressesSupporting(
    std::string const &useCaseName, std::string const &useCaseVersion,
    std::vector<xs_unsignedInt> const &scenarios,
    std::string const &actor) const {
  return d->getAddressesSupporting(d->ownUseCaseData, useCaseName,
                                   useCaseVersion, scenarios, actor);
}

std::vector<FeatureAddress> UseCaseDiscovery::getOwnAddressesSupporting(
    UseCaseSupport const &useCaseSupport, std::string const &actor) const {
  return d->getAddressesSupporting(d->ownUseCaseData,
                                   useCaseSupport.getUseCaseNameIsSet()
                                       ? useCaseSupport.getUseCaseName()
                                       : "",
                                   useCaseSupport.getUseCaseVersionIsSet()
                                       ? useCaseSupport.getUseCaseVersion()
                                       : "",
                                   useCaseSupport.getScenarioSupportIsSet()
                                       ? useCaseSupport.getScenarioSupport()
                                       : std::vector<xs_unsignedInt>(),
                                   actor);
}

std::vector<FeatureAddress> UseCaseDiscovery::getRemoteAddressesSupporting(
    std::string const &useCaseName, std::string const &useCaseVersion,
    std::vector<xs_unsignedInt> const &scenarios,
    std::string const &actor) const {
  return d->getAddressesSupporting(d->remoteUseCaseData, useCaseName,
                                   useCaseVersion, scenarios, actor);
}

std::vector<FeatureAddress> UseCaseDiscovery::getRemoteAddressesSupporting(
    UseCaseSupport const &useCaseSupport, std::string const &actor) const {
  return d->getAddressesSupporting(d->remoteUseCaseData,
                                   useCaseSupport.getUseCaseNameIsSet()
                                       ? useCaseSupport.getUseCaseName()
                                       : "",
                                   useCaseSupport.getUseCaseVersionIsSet()
                                       ? useCaseSupport.getUseCaseVersion()
                                       : "",
                                   useCaseSupport.getScenarioSupportIsSet()
                                       ? useCaseSupport.getScenarioSupport()
                                       : std::vector<xs_unsignedInt>(),
                                   actor);
}

bool UseCaseDiscovery::selfSupports(
    std::string const &useCaseName, std::string const &useCaseVersion,
    std::vector<xs_unsignedInt> const &scenarios,
    std::string const &actor) const {
  return !d->getAddressesSupporting(d->ownUseCaseData, useCaseName,
                                    useCaseVersion, scenarios, actor)
              .empty();
}

bool UseCaseDiscovery::remoteSupports(
    std::string const &useCaseName, std::string const &useCaseVersion,
    std::vector<xs_unsignedInt> const &scenarios,
    std::string const &actor) const {
  return !d->getAddressesSupporting(d->remoteUseCaseData, useCaseName,
                                    useCaseVersion, scenarios, actor)
              .empty();
}

std::vector<UseCaseSupport> UseCaseDiscovery::getMatchingUseCases() const {
  return d->getMatchingUseCases();
}

NodeManagementUseCaseData const &UseCaseDiscovery::getOwnUseCaseData() const {
  return d->ownUseCaseData;
}

NodeManagementUseCaseData const &
UseCaseDiscovery::getRemoteUseCaseData() const {
  return d->remoteUseCaseData;
}

} // end namespace keo_datagram