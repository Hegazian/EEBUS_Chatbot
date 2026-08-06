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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLEVENTDATA_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLEVENTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/loadcontrol/LoadControlEventAction.h>
#include <keo_datagram/loadcontrol/LoadControlEventDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlEventData
 */
class LoadControlEventData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlEventData();

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
  bool operator==(const LoadControlEventData &c_classObject) const;

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
  bool operator!=(const LoadControlEventData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Timestamp.
   * @param c_timestamp Value to set
   */
  void setTimestamp(const AbsoluteOrRelativeTime &c_timestamp);

  /**
   * Returns const reference to member Timestamp.
   * @return const reference to member timestamp
   */
  const AbsoluteOrRelativeTime &getTimestamp() const;

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
   * @param c_eventId Value to set
   */
  void setEventId(const xs_unsignedInt &c_eventId);

  /**
   * Returns const reference to member EventId.
   * @return const reference to member eventId
   */
  const xs_unsignedInt &getEventId() const;

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
   * @param c_eventActionConsume Value to set
   */
  void
  setEventActionConsume(const LoadControlEventAction &c_eventActionConsume);

  /**
   * Returns const reference to member EventActionConsume.
   * @return const reference to member eventActionConsume
   */
  const LoadControlEventAction &getEventActionConsume() const;

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
   * @param c_eventActionProduce Value to set
   */
  void
  setEventActionProduce(const LoadControlEventAction &c_eventActionProduce);

  /**
   * Returns const reference to member EventActionProduce.
   * @return const reference to member eventActionProduce
   */
  const LoadControlEventAction &getEventActionProduce() const;

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
  void setTimePeriod(const TimePeriod &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriod &getTimePeriod() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  LoadControlEventData
  reduce(const LoadControlEventDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_eventIdIsSet;
  xs_unsignedInt m_eventId;

  bool m_eventActionConsumeIsSet;
  LoadControlEventAction m_eventActionConsume;

  bool m_eventActionProduceIsSet;
  LoadControlEventAction m_eventActionProduce;

  bool m_timePeriodIsSet;
  TimePeriod m_timePeriod;
};

//! typedef for non-const smart pointer type LoadControlEventData
using LoadControlEventDataPtr = std::shared_ptr<LoadControlEventData>;

//! typedef for const type LoadControlEventData
using LoadControlEventDataConst = const LoadControlEventData;

//! typedef for const type LoadControlEventData
using LoadControlEventDataConstPtr = std::shared_ptr<LoadControlEventDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLEVENTDATA_H_