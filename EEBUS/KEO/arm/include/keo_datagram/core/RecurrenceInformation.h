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

#ifndef KEO_DATAGRAM_CORE_RECURRENCEINFORMATION_H_
#define KEO_DATAGRAM_CORE_RECURRENCEINFORMATION_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/RecurrenceInformationElements.h>
#include <keo_datagram/core/RecurringInterval.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration RecurrenceInformation
 */
class RecurrenceInformation : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  RecurrenceInformation();

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
  bool operator==(const RecurrenceInformation &c_classObject) const;

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
  bool operator!=(const RecurrenceInformation &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member RecurringInterval.
   * @param c_recurringInterval Value to set
   */
  void setRecurringInterval(const RecurringInterval &c_recurringInterval);

  /**
   * Returns const reference to member RecurringInterval.
   * @return const reference to member recurringInterval
   */
  const RecurringInterval &getRecurringInterval() const;

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
   * @param c_recurringIntervalStep Value to set
   */
  void setRecurringIntervalStep(const xs_unsignedInt &c_recurringIntervalStep);

  /**
   * Returns const reference to member RecurringIntervalStep.
   * @return const reference to member recurringIntervalStep
   */
  const xs_unsignedInt &getRecurringIntervalStep() const;

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
   * @param c_firstExecution Value to set
   */
  void setFirstExecution(const xs_dateTime &c_firstExecution);

  /**
   * Returns const reference to member FirstExecution.
   * @return const reference to member firstExecution
   */
  const xs_dateTime &getFirstExecution() const;

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
   * @param c_executionCount Value to set
   */
  void setExecutionCount(const xs_unsignedInt &c_executionCount);

  /**
   * Returns const reference to member ExecutionCount.
   * @return const reference to member executionCount
   */
  const xs_unsignedInt &getExecutionCount() const;

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
   * @param c_lastExecution Value to set
   */
  void setLastExecution(const xs_dateTime &c_lastExecution);

  /**
   * Returns const reference to member LastExecution.
   * @return const reference to member lastExecution
   */
  const xs_dateTime &getLastExecution() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  RecurrenceInformation
  reduce(const RecurrenceInformationElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_recurringIntervalIsSet;
  RecurringInterval m_recurringInterval;

  bool m_recurringIntervalStepIsSet;
  xs_unsignedInt m_recurringIntervalStep;

  bool m_firstExecutionIsSet;
  xs_dateTime m_firstExecution;

  bool m_executionCountIsSet;
  xs_unsignedInt m_executionCount;

  bool m_lastExecutionIsSet;
  xs_dateTime m_lastExecution;
};

//! typedef for non-const smart pointer type RecurrenceInformation
using RecurrenceInformationPtr = std::shared_ptr<RecurrenceInformation>;

//! typedef for const type RecurrenceInformation
using RecurrenceInformationConst = const RecurrenceInformation;

//! typedef for const type RecurrenceInformation
using RecurrenceInformationConstPtr =
    std::shared_ptr<RecurrenceInformationConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_RECURRENCEINFORMATION_H_