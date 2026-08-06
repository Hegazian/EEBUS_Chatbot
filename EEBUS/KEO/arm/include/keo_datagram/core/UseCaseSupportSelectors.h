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

#ifndef KEO_DATAGRAM_CORE_USECASESUPPORTSELECTORS_H_
#define KEO_DATAGRAM_CORE_USECASESUPPORTSELECTORS_H_

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
 * Declaration UseCaseSupportSelectors
 */
class UseCaseSupportSelectors : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  UseCaseSupportSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_useCaseName the member to set
   * @param c_useCaseVersion the member to set
   * @param c_scenarioSupport the member to set
   */
  UseCaseSupportSelectors(const xs_string &c_useCaseName,
                          const xs_string &c_useCaseVersion,
                          const xs_unsignedInt &c_scenarioSupport);

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
  bool operator==(const UseCaseSupportSelectors &c_classObject) const;

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
  bool operator!=(const UseCaseSupportSelectors &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member UseCaseName.
   * @param c_useCaseName Value to set
   */
  void setUseCaseName(const xs_string &c_useCaseName);

  /**
   * Returns const reference to member UseCaseName.
   * @return const reference to member useCaseName
   */
  const xs_string &getUseCaseName() const;

  /**
   * Returns if member UseCaseName is set.
   * @retval true member UseCaseName is set
   * @retval false member UseCaseName is not set
   */
  bool getUseCaseNameIsSet() const;

  /**
   * Unsets member UseCaseName
   */
  void cleanUseCaseName();

  /**
   * Set member UseCaseVersion.
   * @param c_useCaseVersion Value to set
   */
  void setUseCaseVersion(const xs_string &c_useCaseVersion);

  /**
   * Returns const reference to member UseCaseVersion.
   * @return const reference to member useCaseVersion
   */
  const xs_string &getUseCaseVersion() const;

  /**
   * Returns if member UseCaseVersion is set.
   * @retval true member UseCaseVersion is set
   * @retval false member UseCaseVersion is not set
   */
  bool getUseCaseVersionIsSet() const;

  /**
   * Unsets member UseCaseVersion
   */
  void cleanUseCaseVersion();

  /**
   * Set member ScenarioSupport.
   * @param c_scenarioSupport Value to set
   */
  void setScenarioSupport(const xs_unsignedInt &c_scenarioSupport);

  /**
   * Returns const reference to member ScenarioSupport.
   * @return const reference to member scenarioSupport
   */
  const xs_unsignedInt &getScenarioSupport() const;

  /**
   * Returns if member ScenarioSupport is set.
   * @retval true member ScenarioSupport is set
   * @retval false member ScenarioSupport is not set
   */
  bool getScenarioSupportIsSet() const;

  /**
   * Unsets member ScenarioSupport
   */
  void cleanScenarioSupport();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_useCaseNameIsSet;
  xs_string m_useCaseName;

  bool m_useCaseVersionIsSet;
  xs_string m_useCaseVersion;

  bool m_scenarioSupportIsSet;
  xs_unsignedInt m_scenarioSupport;
};

//! typedef for non-const smart pointer type UseCaseSupportSelectors
using UseCaseSupportSelectorsPtr = std::shared_ptr<UseCaseSupportSelectors>;

//! typedef for const type UseCaseSupportSelectors
using UseCaseSupportSelectorsConst = const UseCaseSupportSelectors;

//! typedef for const type UseCaseSupportSelectors
using UseCaseSupportSelectorsConstPtr =
    std::shared_ptr<UseCaseSupportSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_USECASESUPPORTSELECTORS_H_