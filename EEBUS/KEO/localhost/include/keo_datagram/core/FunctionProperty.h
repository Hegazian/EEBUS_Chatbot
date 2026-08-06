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

#ifndef KEO_DATAGRAM_CORE_FUNCTIONPROPERTY_H_
#define KEO_DATAGRAM_CORE_FUNCTIONPROPERTY_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/Function.h>
#include <keo_datagram/core/FunctionPropertyElements.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/PossibleOperations.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration FunctionProperty
 */
class FunctionProperty : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  FunctionProperty();

  /**
   * Construct an instance of this class and set its member.
   * @param c_function the member to set
   * @param c_possibleOperations the member to set
   */
  FunctionProperty(const Function &c_function,
                   const PossibleOperations &c_possibleOperations);

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
  bool operator==(const FunctionProperty &c_classObject) const;

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
  bool operator!=(const FunctionProperty &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Function.
   * @param c_function Value to set
   */
  void setFunction(const Function &c_function);

  /**
   * Returns const reference to member Function.
   * @return const reference to member function
   */
  const Function &getFunction() const;

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
  void setPossibleOperations(const PossibleOperations &c_possibleOperations);

  /**
   * Returns const reference to member PossibleOperations.
   * @return const reference to member possibleOperations
   */
  const PossibleOperations &getPossibleOperations() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  FunctionProperty reduce(const FunctionPropertyElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_functionIsSet;
  Function m_function;

  bool m_possibleOperationsIsSet;
  PossibleOperations m_possibleOperations;
};

//! typedef for non-const smart pointer type FunctionProperty
using FunctionPropertyPtr = std::shared_ptr<FunctionProperty>;

//! typedef for const type FunctionProperty
using FunctionPropertyConst = const FunctionProperty;

//! typedef for const type FunctionProperty
using FunctionPropertyConstPtr = std::shared_ptr<FunctionPropertyConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_FUNCTIONPROPERTY_H_