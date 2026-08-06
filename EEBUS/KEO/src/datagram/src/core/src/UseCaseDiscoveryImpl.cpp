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
#include <algorithm>

/* ************************************************************************** *
 *  KEO header files                                                      *
 * ************************************************************************** */

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

UseCaseDiscovery::UseCaseDiscoveryImpl::UseCaseDiscoveryImpl(
    NodeManagementUseCaseData const &ownUseCaseData,
    NodeManagementUseCaseData const &remoteUseCaseData)
    : ownUseCaseData(ownUseCaseData), remoteUseCaseData(remoteUseCaseData) {}

UseCaseDiscovery::UseCaseDiscoveryImpl::~UseCaseDiscoveryImpl() {}

std::vector<FeatureAddress>
UseCaseDiscovery::UseCaseDiscoveryImpl::getAddressesSupporting(
    NodeManagementUseCaseData const &useCaseData,
    std::string const &useCaseName, std::string const &useCaseVersion,
    std::vector<xs_unsignedInt> const &scenarios,
    std::string const &actor) const {
  std::vector<FeatureAddress> result;
  for (auto const &useCaseInformation : useCaseData.getUseCaseInformation()) {
    if (actor == "" || (useCaseInformation.getActorIsSet() &&
                        actor == useCaseInformation.getActor())) {
      for (auto const &useCaseSupport :
           useCaseInformation.getUseCaseSupport()) {
        // According to Spec, the default value for useCaseAvailable is true
        if (!useCaseSupport.getUseCaseAvailableIsSet() ||
            (useCaseSupport.getUseCaseAvailableIsSet() &&
             useCaseSupport.getUseCaseAvailable())) {
          if (useCaseName == "" ||
              (useCaseSupport.getUseCaseNameIsSet() &&
               useCaseName == useCaseSupport.getUseCaseName())) {
            if (useCaseVersion == "" ||
                (useCaseSupport.getUseCaseVersionIsSet() &&
                 useCaseVersion == useCaseSupport.getUseCaseVersion())) {
              if (useCaseSupport.getScenarioSupport().empty() ||
                  isSubset(scenarios, useCaseSupport.getScenarioSupport())) {
                // Only add addresses that are not added yet
                if (std::find(std::begin(result), std::end(result),
                              useCaseInformation.getAddress()) ==
                    std::end(result)) {
                  result.push_back(useCaseInformation.getAddress());
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

std::vector<UseCaseSupport>
UseCaseDiscovery::UseCaseDiscoveryImpl::getMatchingUseCases() const {
  std::vector<UseCaseSupport> result;
  for (auto const &ownUseCaseInformation :
       ownUseCaseData.getUseCaseInformation()) {
    for (auto const &remoteUseCaseInformation :
         remoteUseCaseData.getUseCaseInformation()) {
      // Two use cases can only ever "match" if the actors differ
      if (ownUseCaseInformation.getActorIsSet() &&
          remoteUseCaseInformation.getActorIsSet() &&
          ownUseCaseInformation.getActor() !=
              remoteUseCaseInformation.getActor()) {
        for (auto const &ownUseCaseSupport :
             ownUseCaseInformation.getUseCaseSupport()) {
          for (auto const &remoteUseCaseSupport :
               remoteUseCaseInformation.getUseCaseSupport()) {
            // Default value for useCaseAvailable is true
            if ((!ownUseCaseSupport.getUseCaseAvailableIsSet() ||
                 (ownUseCaseSupport.getUseCaseAvailableIsSet() &&
                  ownUseCaseSupport.getUseCaseAvailable())) &&
                (!remoteUseCaseSupport.getUseCaseAvailableIsSet() ||
                 (remoteUseCaseSupport.getUseCaseAvailableIsSet() &&
                  remoteUseCaseSupport.getUseCaseAvailable()))) {
              if (ownUseCaseSupport.getUseCaseNameIsSet() &&
                  remoteUseCaseSupport.getUseCaseNameIsSet() &&
                  ownUseCaseSupport.getUseCaseName() ==
                      remoteUseCaseSupport.getUseCaseName()) {
                // TODO more complex logic may be neccessary to match version
                // numbers
                // ("only major version changed", etc...)
                if (ownUseCaseSupport.getUseCaseVersionIsSet() &&
                    remoteUseCaseSupport.getUseCaseVersionIsSet() &&
                    ownUseCaseSupport.getUseCaseVersion() ==
                        remoteUseCaseSupport.getUseCaseVersion()) {
                  bool matches = false;
                  std::vector<xs_unsignedInt> matchingScenarios;

                  if ((!ownUseCaseSupport.getScenarioSupportIsSet() ||
                       ownUseCaseSupport.getScenarioSupport().empty()) &&
                      remoteUseCaseSupport.getScenarioSupportIsSet()) {
                    // Own data supports all scenarios, remote data only a
                    // selection
                    matchingScenarios =
                        remoteUseCaseSupport.getScenarioSupport();
                    matches = true;
                  } else if ((!remoteUseCaseSupport.getScenarioSupportIsSet() ||
                              remoteUseCaseSupport.getScenarioSupport()
                                  .empty()) &&
                             ownUseCaseSupport.getScenarioSupportIsSet()) {
                    // Remote data supports all scenarios, own data only a
                    // selection
                    matchingScenarios = ownUseCaseSupport.getScenarioSupport();
                    matches = true;
                  } else if ((!ownUseCaseSupport.getScenarioSupportIsSet() ||
                              ownUseCaseSupport.getScenarioSupport().empty()) &&
                             (!remoteUseCaseSupport.getScenarioSupportIsSet() ||
                              remoteUseCaseSupport.getScenarioSupport()
                                  .empty())) {
                    // Both support all scenarios
                    matches = true;
                  } else {
                    // Both support only a selection of scenarios
                    std::vector<xs_unsignedInt> ownScenarios =
                        ownUseCaseSupport.getScenarioSupport();
                    std::vector<xs_unsignedInt> remoteScenarios =
                        remoteUseCaseSupport.getScenarioSupport();
                    std::sort(std::begin(ownScenarios), std::end(ownScenarios));
                    std::sort(std::begin(remoteScenarios),
                              std::end(remoteScenarios));
                    std::set_intersection(
                        std::begin(ownScenarios), std::end(ownScenarios),
                        std::begin(remoteScenarios), std::end(remoteScenarios),
                        std::back_inserter(matchingScenarios));
                    matches = !matchingScenarios.empty();
                  }

                  if (matches) {
                    UseCaseSupport ucs;
                    ucs.setUseCaseName(ownUseCaseSupport.getUseCaseName());
                    ucs.setUseCaseVersion(
                        ownUseCaseSupport.getUseCaseVersion());
                    if (!matchingScenarios.empty()) {
                      ucs.setScenarioSupport(matchingScenarios);
                    }
                    if (std::find(std::begin(result), std::end(result), ucs) ==
                        std::end(result)) {
                      result.push_back(ucs);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

bool UseCaseDiscovery::UseCaseDiscoveryImpl::isSubset(
    std::vector<xs_unsignedInt> const &set,
    std::vector<xs_unsignedInt> const &superset) const {
  for (auto const &x : set) {
    if (std::find(std::begin(superset), std::end(superset), x) ==
        std::end(superset)) {
      // At least one is not contained in superSet
      return false;
    }
  }
  return true;
}

} // end namespace keo_datagram