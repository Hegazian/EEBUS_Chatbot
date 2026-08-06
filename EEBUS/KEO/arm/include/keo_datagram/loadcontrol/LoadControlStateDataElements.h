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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATEDATAELEMENTS_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlStateDataElements
 */
class LoadControlStateDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlStateDataElements();

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
  bool operator==(const LoadControlStateDataElements &c_classObject) const;

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
  bool operator!=(const LoadControlStateDataElements &c_classObject) const;

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
   * Set member EventStateConsume.
   */
  void setEventStateConsume();

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
   */
  void setAppliedEventActionConsume();

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
   */
  void setEventStateProduce();

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
   */
  void setAppliedEventActionProduce();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_eventIdIsSet;

  // ElementTag
  bool m_eventStateConsumeIsSet;

  // ElementTag
  bool m_appliedEventActionConsumeIsSet;

  // ElementTag
  bool m_eventStateProduceIsSet;

  // ElementTag
  bool m_appliedEventActionProduceIsSet;
};

//! typedef for non-const smart pointer type LoadControlStateDataElements
using LoadControlStateDataElementsPtr =
    std::shared_ptr<LoadControlStateDataElements>;

//! typedef for const type LoadControlStateDataElements
using LoadControlStateDataElementsConst = const LoadControlStateDataElements;

//! typedef for const type LoadControlStateDataElements
using LoadControlStateDataElementsConstPtr =
    std::shared_ptr<LoadControlStateDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATEDATAELEMENTS_H_