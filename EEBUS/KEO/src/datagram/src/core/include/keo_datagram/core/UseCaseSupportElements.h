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

#ifndef KEO_DATAGRAM_CORE_USECASESUPPORTELEMENTS_H_
#define KEO_DATAGRAM_CORE_USECASESUPPORTELEMENTS_H_

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
 * Declaration UseCaseSupportElements
 */
class UseCaseSupportElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  UseCaseSupportElements();

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
  bool operator==(const UseCaseSupportElements &c_classObject) const;

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
  bool operator!=(const UseCaseSupportElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member UseCaseName.
   */
  void setUseCaseName();

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
   */
  void setUseCaseVersion();

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
   * Set member UseCaseAvailable.
   */
  void setUseCaseAvailable();

  /**
   * Returns if member UseCaseAvailable is set.
   * @retval true member UseCaseAvailable is set
   * @retval false member UseCaseAvailable is not set
   */
  bool getUseCaseAvailableIsSet() const;

  /**
   * Unsets member UseCaseAvailable
   */
  void cleanUseCaseAvailable();

  /**
   * Set member ScenarioSupport.
   */
  void setScenarioSupport();

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

  // ElementTag
  bool m_useCaseNameIsSet;

  // ElementTag
  bool m_useCaseVersionIsSet;

  // ElementTag
  bool m_useCaseAvailableIsSet;

  // ElementTag
  bool m_scenarioSupportIsSet;
};

//! typedef for non-const smart pointer type UseCaseSupportElements
using UseCaseSupportElementsPtr = std::shared_ptr<UseCaseSupportElements>;

//! typedef for const type UseCaseSupportElements
using UseCaseSupportElementsConst = const UseCaseSupportElements;

//! typedef for const type UseCaseSupportElements
using UseCaseSupportElementsConstPtr =
    std::shared_ptr<UseCaseSupportElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_USECASESUPPORTELEMENTS_H_