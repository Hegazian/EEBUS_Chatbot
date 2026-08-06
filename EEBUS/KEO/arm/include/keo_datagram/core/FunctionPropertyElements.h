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

#ifndef KEO_DATAGRAM_CORE_FUNCTIONPROPERTYELEMENTS_H_
#define KEO_DATAGRAM_CORE_FUNCTIONPROPERTYELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/PossibleOperationsElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration FunctionPropertyElements
 */
class FunctionPropertyElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  FunctionPropertyElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_functionIsSet the member to set
   * @param c_possibleOperations the member to set
   */
  FunctionPropertyElements(
      xs_boolean c_functionIsSet,
      const PossibleOperationsElements &c_possibleOperations);

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
  bool operator==(const FunctionPropertyElements &c_classObject) const;

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
  bool operator!=(const FunctionPropertyElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Function.
   */
  void setFunction();

  /**
   * Returns if member Function is set.
   * @retval true member Function is set
   * @retval false member Function is not set
   */
  bool getFunctionIsSet() const;

  /**
   * Unsets member Function
   */
  void cleanFunction();

  /**
   * Set member PossibleOperations.
   * @param c_possibleOperations Value to set
   */
  void
  setPossibleOperations(const PossibleOperationsElements &c_possibleOperations);

  /**
   * Returns const reference to member PossibleOperations.
   * @return const reference to member possibleOperations
   */
  const PossibleOperationsElements &getPossibleOperations() const;

  /**
   * Returns if member PossibleOperations is set.
   * @retval true member PossibleOperations is set
   * @retval false member PossibleOperations is not set
   */
  bool getPossibleOperationsIsSet() const;

  /**
   * Unsets member PossibleOperations
   */
  void cleanPossibleOperations();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_functionIsSet;

  bool m_possibleOperationsIsSet;
  PossibleOperationsElements m_possibleOperations;
};

//! typedef for non-const smart pointer type FunctionPropertyElements
using FunctionPropertyElementsPtr = std::shared_ptr<FunctionPropertyElements>;

//! typedef for const type FunctionPropertyElements
using FunctionPropertyElementsConst = const FunctionPropertyElements;

//! typedef for const type FunctionPropertyElements
using FunctionPropertyElementsConstPtr =
    std::shared_ptr<FunctionPropertyElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_FUNCTIONPROPERTYELEMENTS_H_