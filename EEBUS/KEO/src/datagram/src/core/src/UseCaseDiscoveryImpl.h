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

#ifndef __KEO_DATAGRAM_USECASEDISCOVERYIMPL_H_
#define __KEO_DATAGRAM_USECASEDISCOVERYIMPL_H_

/** @addtogroup SpineDatagram
 * @{
 */

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  KEO header files                                                      *
 * ************************************************************************** */
#include <keo_datagram/core/NodeManagementUseCaseData.h>
#include <keo_datagram/core/UseCaseDiscovery.h>

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

class UseCaseDiscovery::UseCaseDiscoveryImpl {
public:
  UseCaseDiscoveryImpl(NodeManagementUseCaseData const &ownUseCaseData,
                       NodeManagementUseCaseData const &remoteUseCaseData);
  virtual ~UseCaseDiscoveryImpl();

  std::vector<FeatureAddress>
  getAddressesSupporting(NodeManagementUseCaseData const &useCaseData,
                         std::string const &useCaseName = "",
                         std::string const &useCaseVersion = "",
                         std::vector<xs_unsignedInt> const &scenarios = {},
                         std::string const &actor = "") const;

  std::vector<UseCaseSupport> getMatchingUseCases() const;

  /**
   * Check wheter one vector is a subset of another vector.
   * @param set the potential subset
   * @param superset the potential superset
   * @return true, if set is a subset of superset
   */
  bool isSubset(std::vector<xs_unsignedInt> const &set,
                std::vector<xs_unsignedInt> const &superset) const;

  NodeManagementUseCaseData ownUseCaseData;
  NodeManagementUseCaseData remoteUseCaseData;
};

} // end namespace keo_datagram

/** @}
 * end of file
 */

#endif // __KEO_DATAGRAM_USECASEDISCOVERYIMPL_H_