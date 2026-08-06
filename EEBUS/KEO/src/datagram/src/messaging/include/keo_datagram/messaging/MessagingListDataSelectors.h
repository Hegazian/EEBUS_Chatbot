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

#ifndef KEO_DATAGRAM_MESSAGING_MESSAGINGLISTDATASELECTORS_H_
#define KEO_DATAGRAM_MESSAGING_MESSAGINGLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/TimestampInterval.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/messaging/MessagingData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramMessaging
 * @{
 */

/**
 * Declaration MessagingListDataSelectors
 */
class MessagingListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  MessagingListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_timestampInterval the member to set
   * @param c_messagingNumber the member to set
   */
  MessagingListDataSelectors(const TimestampInterval &c_timestampInterval,
                             const xs_unsignedInt &c_messagingNumber);

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
  bool operator==(const MessagingListDataSelectors &c_classObject) const;

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
  bool operator!=(const MessagingListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member TimestampInterval.
   * @param c_timestampInterval Value to set
   */
  void setTimestampInterval(const TimestampInterval &c_timestampInterval);

  /**
   * Returns const reference to member TimestampInterval.
   * @return const reference to member timestampInterval
   */
  const TimestampInterval &getTimestampInterval() const;

  /**
   * Returns if member TimestampInterval is set.
   * @retval true member TimestampInterval is set
   * @retval false member TimestampInterval is not set
   */
  bool getTimestampIntervalIsSet() const;

  /**
   * Unsets member TimestampInterval
   */
  void cleanTimestampInterval();

  /**
   * Set member MessagingNumber.
   * @param c_messagingNumber Value to set
   */
  void setMessagingNumber(const xs_unsignedInt &c_messagingNumber);

  /**
   * Returns const reference to member MessagingNumber.
   * @return const reference to member messagingNumber
   */
  const xs_unsignedInt &getMessagingNumber() const;

  /**
   * Returns if member MessagingNumber is set.
   * @retval true member MessagingNumber is set
   * @retval false member MessagingNumber is not set
   */
  bool getMessagingNumberIsSet() const;

  /**
   * Unsets member MessagingNumber
   */
  void cleanMessagingNumber();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const MessagingData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIntervalIsSet;
  TimestampInterval m_timestampInterval;

  bool m_messagingNumberIsSet;
  xs_unsignedInt m_messagingNumber;
};

//! typedef for non-const smart pointer type MessagingListDataSelectors
using MessagingListDataSelectorsPtr =
    std::shared_ptr<MessagingListDataSelectors>;

//! typedef for const type MessagingListDataSelectors
using MessagingListDataSelectorsConst = const MessagingListDataSelectors;

//! typedef for const type MessagingListDataSelectors
using MessagingListDataSelectorsConstPtr =
    std::shared_ptr<MessagingListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_MESSAGING_MESSAGINGLISTDATASELECTORS_H_