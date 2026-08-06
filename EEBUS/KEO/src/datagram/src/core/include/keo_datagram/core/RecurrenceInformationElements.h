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

#ifndef KEO_DATAGRAM_CORE_RECURRENCEINFORMATIONELEMENTS_H_
#define KEO_DATAGRAM_CORE_RECURRENCEINFORMATIONELEMENTS_H_

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
 * Declaration RecurrenceInformationElements
 */
class RecurrenceInformationElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  RecurrenceInformationElements();

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
  bool operator==(const RecurrenceInformationElements &c_classObject) const;

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
  bool operator!=(const RecurrenceInformationElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member RecurringInterval.
   */
  void setRecurringInterval();

  /**
   * Returns if member RecurringInterval is set.
   * @retval true member RecurringInterval is set
   * @retval false member RecurringInterval is not set
   */
  bool getRecurringIntervalIsSet() const;

  /**
   * Unsets member RecurringInterval
   */
  void cleanRecurringInterval();

  /**
   * Set member RecurringIntervalStep.
   */
  void setRecurringIntervalStep();

  /**
   * Returns if member RecurringIntervalStep is set.
   * @retval true member RecurringIntervalStep is set
   * @retval false member RecurringIntervalStep is not set
   */
  bool getRecurringIntervalStepIsSet() const;

  /**
   * Unsets member RecurringIntervalStep
   */
  void cleanRecurringIntervalStep();

  /**
   * Set member FirstExecution.
   */
  void setFirstExecution();

  /**
   * Returns if member FirstExecution is set.
   * @retval true member FirstExecution is set
   * @retval false member FirstExecution is not set
   */
  bool getFirstExecutionIsSet() const;

  /**
   * Unsets member FirstExecution
   */
  void cleanFirstExecution();

  /**
   * Set member ExecutionCount.
   */
  void setExecutionCount();

  /**
   * Returns if member ExecutionCount is set.
   * @retval true member ExecutionCount is set
   * @retval false member ExecutionCount is not set
   */
  bool getExecutionCountIsSet() const;

  /**
   * Unsets member ExecutionCount
   */
  void cleanExecutionCount();

  /**
   * Set member LastExecution.
   */
  void setLastExecution();

  /**
   * Returns if member LastExecution is set.
   * @retval true member LastExecution is set
   * @retval false member LastExecution is not set
   */
  bool getLastExecutionIsSet() const;

  /**
   * Unsets member LastExecution
   */
  void cleanLastExecution();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_recurringIntervalIsSet;

  // ElementTag
  bool m_recurringIntervalStepIsSet;

  // ElementTag
  bool m_firstExecutionIsSet;

  // ElementTag
  bool m_executionCountIsSet;

  // ElementTag
  bool m_lastExecutionIsSet;
};

//! typedef for non-const smart pointer type RecurrenceInformationElements
using RecurrenceInformationElementsPtr =
    std::shared_ptr<RecurrenceInformationElements>;

//! typedef for const type RecurrenceInformationElements
using RecurrenceInformationElementsConst = const RecurrenceInformationElements;

//! typedef for const type RecurrenceInformationElements
using RecurrenceInformationElementsConstPtr =
    std::shared_ptr<RecurrenceInformationElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_RECURRENCEINFORMATIONELEMENTS_H_