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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLEVENTDATAELEMENTS_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLEVENTDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/TimePeriodElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlEventDataElements
 */
class LoadControlEventDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlEventDataElements();

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
  bool operator==(const LoadControlEventDataElements &c_classObject) const;

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
  bool operator!=(const LoadControlEventDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member Timestamp.
   */
  void setTimestamp();

  /**
   * Returns if member Timestamp is set.
   * @retval true member Timestamp is set
   * @retval false member Timestamp is not set
   */
  bool getTimestampIsSet() const;

  /**
   * Unsets member Timestamp
   */
  void cleanTimestamp();

  /**
   * Set member EventId.
   */
  void setEventId();

  /**
   * Returns if member EventId is set.
   * @retval true member EventId is set
   * @retval false member EventId is not set
   */
  bool getEventIdIsSet() const;

  /**
   * Unsets member EventId
   */
  void cleanEventId();

  /**
   * Set member EventActionConsume.
   */
  void setEventActionConsume();

  /**
   * Returns if member EventActionConsume is set.
   * @retval true member EventActionConsume is set
   * @retval false member EventActionConsume is not set
   */
  bool getEventActionConsumeIsSet() const;

  /**
   * Unsets member EventActionConsume
   */
  void cleanEventActionConsume();

  /**
   * Set member EventActionProduce.
   */
  void setEventActionProduce();

  /**
   * Returns if member EventActionProduce is set.
   * @retval true member EventActionProduce is set
   * @retval false member EventActionProduce is not set
   */
  bool getEventActionProduceIsSet() const;

  /**
   * Unsets member EventActionProduce
   */
  void cleanEventActionProduce();

  /**
   * Set member TimePeriod.
   * @param c_timePeriod Value to set
   */
  void setTimePeriod(const TimePeriodElements &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriodElements &getTimePeriod() const;

  /**
   * Returns if member TimePeriod is set.
   * @retval true member TimePeriod is set
   * @retval false member TimePeriod is not set
   */
  bool getTimePeriodIsSet() const;

  /**
   * Unsets member TimePeriod
   */
  void cleanTimePeriod();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_eventIdIsSet;

  // ElementTag
  bool m_eventActionConsumeIsSet;

  // ElementTag
  bool m_eventActionProduceIsSet;

  bool m_timePeriodIsSet;
  TimePeriodElements m_timePeriod;
};

//! typedef for non-const smart pointer type LoadControlEventDataElements
using LoadControlEventDataElementsPtr =
    std::shared_ptr<LoadControlEventDataElements>;

//! typedef for const type LoadControlEventDataElements
using LoadControlEventDataElementsConst = const LoadControlEventDataElements;

//! typedef for const type LoadControlEventDataElements
using LoadControlEventDataElementsConstPtr =
    std::shared_ptr<LoadControlEventDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLEVENTDATAELEMENTS_H_