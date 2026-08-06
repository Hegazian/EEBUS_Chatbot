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

#ifndef KEO_DATAGRAM_MESSAGING_MESSAGINGDATA_H_
#define KEO_DATAGRAM_MESSAGING_MESSAGINGDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/messaging/MessagingDataElements.h>
#include <keo_datagram/messaging/MessagingType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramMessaging
 * @{
 */

/**
 * Declaration MessagingData
 */
class MessagingData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  MessagingData();

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
  bool operator==(const MessagingData &c_classObject) const;

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
  bool operator!=(const MessagingData &c_classObject) const;

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
   * Set member Type.
   * @param c_type Value to set
   */
  void setType(const MessagingType &c_type);

  /**
   * Returns const reference to member Type.
   * @return const reference to member type
   */
  const MessagingType &getType() const;

  /**
   * Returns if member Type is set.
   * @retval true member Type is set
   * @retval false member Type is not set
   */
  bool getTypeIsSet() const;

  /**
   * Unsets member Type
   */
  void cleanType();

  /**
   * Set member Text.
   * @param c_text Value to set
   */
  void setText(const xs_string &c_text);

  /**
   * Returns const reference to member Text.
   * @return const reference to member text
   */
  const xs_string &getText() const;

  /**
   * Returns if member Text is set.
   * @retval true member Text is set
   * @retval false member Text is not set
   */
  bool getTextIsSet() const;

  /**
   * Unsets member Text
   */
  void cleanText();

  /**
   * @copydoc CmdData::reduce()
   */
  MessagingData reduce(const MessagingDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_messagingNumberIsSet;
  xs_unsignedInt m_messagingNumber;

  bool m_typeIsSet;
  MessagingType m_type;

  bool m_textIsSet;
  xs_string m_text;
};

//! typedef for non-const smart pointer type MessagingData
using MessagingDataPtr = std::shared_ptr<MessagingData>;

//! typedef for const type MessagingData
using MessagingDataConst = const MessagingData;

//! typedef for const type MessagingData
using MessagingDataConstPtr = std::shared_ptr<MessagingDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_MESSAGING_MESSAGINGDATA_H_