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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATEDATA_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/loadcontrol/LoadControlEventAction.h>
#include <keo_datagram/loadcontrol/LoadControlEventState.h>
#include <keo_datagram/loadcontrol/LoadControlStateDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlStateData
 */
class LoadControlStateData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlStateData();

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
  bool operator==(const LoadControlStateData &c_classObject) const;

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
  bool operator!=(const LoadControlStateData &c_classObject) const;

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
   * Set member EventStateConsume.
   * @param c_eventStateConsume Value to set
   */
  void setEventStateConsume(const LoadControlEventState &c_eventStateConsume);

  /**
   * Returns const reference to member EventStateConsume.
   * @return const reference to member eventStateConsume
   */
  const LoadControlEventState &getEventStateConsume() const;

  /**
   * Returns if member EventStateConsume is set.
   * @retval true member EventStateConsume is set
   * @retval false member EventStateConsume is not set
   */
  bool getEventStateConsumeIsSet() const;

  /**
   * Unsets member EventStateConsume
   */
  void cleanEventStateConsume();

  /**
   * Set member AppliedEventActionConsume.
   * @param c_appliedEventActionConsume Value to set
   */
  void setAppliedEventActionConsume(
      const LoadControlEventAction &c_appliedEventActionConsume);

  /**
   * Returns const reference to member AppliedEventActionConsume.
   * @return const reference to member appliedEventActionConsume
   */
  const LoadControlEventAction &getAppliedEventActionConsume() const;

  /**
   * Returns if member AppliedEventActionConsume is set.
   * @retval true member AppliedEventActionConsume is set
   * @retval false member AppliedEventActionConsume is not set
   */
  bool getAppliedEventActionConsumeIsSet() const;

  /**
   * Unsets member AppliedEventActionConsume
   */
  void cleanAppliedEventActionConsume();

  /**
   * Set member EventStateProduce.
   * @param c_eventStateProduce Value to set
   */
  void setEventStateProduce(const LoadControlEventState &c_eventStateProduce);

  /**
   * Returns const reference to member EventStateProduce.
   * @return const reference to member eventStateProduce
   */
  const LoadControlEventState &getEventStateProduce() const;

  /**
   * Returns if member EventStateProduce is set.
   * @retval true member EventStateProduce is set
   * @retval false member EventStateProduce is not set
   */
  bool getEventStateProduceIsSet() const;

  /**
   * Unsets member EventStateProduce
   */
  void cleanEventStateProduce();

  /**
   * Set member AppliedEventActionProduce.
   * @param c_appliedEventActionProduce Value to set
   */
  void setAppliedEventActionProduce(
      const LoadControlEventAction &c_appliedEventActionProduce);

  /**
   * Returns const reference to member AppliedEventActionProduce.
   * @return const reference to member appliedEventActionProduce
   */
  const LoadControlEventAction &getAppliedEventActionProduce() const;

  /**
   * Returns if member AppliedEventActionProduce is set.
   * @retval true member AppliedEventActionProduce is set
   * @retval false member AppliedEventActionProduce is not set
   */
  bool getAppliedEventActionProduceIsSet() const;

  /**
   * Unsets member AppliedEventActionProduce
   */
  void cleanAppliedEventActionProduce();

  /**
   * @copydoc CmdData::reduce()
   */
  LoadControlStateData
  reduce(const LoadControlStateDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_eventIdIsSet;
  xs_unsignedInt m_eventId;

  bool m_eventStateConsumeIsSet;
  LoadControlEventState m_eventStateConsume;

  bool m_appliedEventActionConsumeIsSet;
  LoadControlEventAction m_appliedEventActionConsume;

  bool m_eventStateProduceIsSet;
  LoadControlEventState m_eventStateProduce;

  bool m_appliedEventActionProduceIsSet;
  LoadControlEventAction m_appliedEventActionProduce;
};

//! typedef for non-const smart pointer type LoadControlStateData
using LoadControlStateDataPtr = std::shared_ptr<LoadControlStateData>;

//! typedef for const type LoadControlStateData
using LoadControlStateDataConst = const LoadControlStateData;

//! typedef for const type LoadControlStateData
using LoadControlStateDataConstPtr = std::shared_ptr<LoadControlStateDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATEDATA_H_