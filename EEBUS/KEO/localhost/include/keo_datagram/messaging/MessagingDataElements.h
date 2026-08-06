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

#ifndef KEO_DATAGRAM_MESSAGING_MESSAGINGDATAELEMENTS_H_
#define KEO_DATAGRAM_MESSAGING_MESSAGINGDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramMessaging
 * @{
 */

/**
 * Declaration MessagingDataElements
 */
class MessagingDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  MessagingDataElements();

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
  bool operator==(const MessagingDataElements &c_classObject) const;

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
  bool operator!=(const MessagingDataElements &c_classObject) const;

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
   * Set member MessagingNumber.
   */
  void setMessagingNumber();

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
   */
  void setType();

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
   */
  void setText();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_messagingNumberIsSet;

  // ElementTag
  bool m_typeIsSet;

  // ElementTag
  bool m_textIsSet;
};

//! typedef for non-const smart pointer type MessagingDataElements
using MessagingDataElementsPtr = std::shared_ptr<MessagingDataElements>;

//! typedef for const type MessagingDataElements
using MessagingDataElementsConst = const MessagingDataElements;

//! typedef for const type MessagingDataElements
using MessagingDataElementsConstPtr =
    std::shared_ptr<MessagingDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_MESSAGING_MESSAGINGDATAELEMENTS_H_