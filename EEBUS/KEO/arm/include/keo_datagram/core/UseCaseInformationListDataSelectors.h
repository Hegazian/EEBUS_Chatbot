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

#ifndef KEO_DATAGRAM_CORE_USECASEINFORMATIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_CORE_USECASEINFORMATIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/UseCaseSupportSelectors.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration UseCaseInformationListDataSelectors
 */
class UseCaseInformationListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  UseCaseInformationListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_address the member to set
   * @param c_actor the member to set
   * @param c_useCaseSupport the member to set
   */
  UseCaseInformationListDataSelectors(
      const FeatureAddress &c_address, const xs_string &c_actor,
      const UseCaseSupportSelectors &c_useCaseSupport);

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
  bool
  operator==(const UseCaseInformationListDataSelectors &c_classObject) const;

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
  bool
  operator!=(const UseCaseInformationListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member Address.
   * @param c_address Value to set
   */
  void setAddress(const FeatureAddress &c_address);

  /**
   * Returns const reference to member Address.
   * @return const reference to member address
   */
  const FeatureAddress &getAddress() const;

  /**
   * Returns if member Address is set.
   * @retval true member Address is set
   * @retval false member Address is not set
   */
  bool getAddressIsSet() const;

  /**
   * Unsets member Address
   */
  void cleanAddress();

  /**
   * Set member Actor.
   * @param c_actor Value to set
   */
  void setActor(const xs_string &c_actor);

  /**
   * Returns const reference to member Actor.
   * @return const reference to member actor
   */
  const xs_string &getActor() const;

  /**
   * Returns if member Actor is set.
   * @retval true member Actor is set
   * @retval false member Actor is not set
   */
  bool getActorIsSet() const;

  /**
   * Unsets member Actor
   */
  void cleanActor();

  /**
   * Set member UseCaseSupport.
   * @param c_useCaseSupport Value to set
   */
  void setUseCaseSupport(const UseCaseSupportSelectors &c_useCaseSupport);

  /**
   * Returns const reference to member UseCaseSupport.
   * @return const reference to member useCaseSupport
   */
  const UseCaseSupportSelectors &getUseCaseSupport() const;

  /**
   * Returns if member UseCaseSupport is set.
   * @retval true member UseCaseSupport is set
   * @retval false member UseCaseSupport is not set
   */
  bool getUseCaseSupportIsSet() const;

  /**
   * Unsets member UseCaseSupport
   */
  void cleanUseCaseSupport();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_addressIsSet;
  FeatureAddress m_address;

  bool m_actorIsSet;
  xs_string m_actor;

  bool m_useCaseSupportIsSet;
  UseCaseSupportSelectors m_useCaseSupport;
};

//! typedef for non-const smart pointer type UseCaseInformationListDataSelectors
using UseCaseInformationListDataSelectorsPtr =
    std::shared_ptr<UseCaseInformationListDataSelectors>;

//! typedef for const type UseCaseInformationListDataSelectors
using UseCaseInformationListDataSelectorsConst =
    const UseCaseInformationListDataSelectors;

//! typedef for const type UseCaseInformationListDataSelectors
using UseCaseInformationListDataSelectorsConstPtr =
    std::shared_ptr<UseCaseInformationListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_USECASEINFORMATIONLISTDATASELECTORS_H_