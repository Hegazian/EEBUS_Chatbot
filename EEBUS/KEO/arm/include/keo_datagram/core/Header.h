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

#ifndef KEO_DATAGRAM_CORE_HEADER_H_
#define KEO_DATAGRAM_CORE_HEADER_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/CmdClassifier.h>
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

#include <mutex>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration Header
 */
class Header : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  Header();

  explicit Header(const CmdClassifier::Value c_classifier);
  Header(const FeatureAddress &c_addressSource,
         const FeatureAddress &c_addressDestination,
         const CmdClassifier::Value c_classifier =
             CmdClassifier::Value::UNDEFINED__);

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
  bool operator==(const Header &c_classObject) const;

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
  bool operator!=(const Header &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Checks if this header is a call header
   * @return true, if the classifier is set to CALL
   */
  bool isCall() const;

  /**
   * Checks if this header is a notify header
   * @return true, if the classifier is set to NOTIFY
   */
  bool isNotify() const;

  /**
   * Checks if this header is a read header
   * @return true, if the classifier is set to READ
   */
  bool isRead() const;

  /**
   * Checks if this header is a reply header
   * @return true, if the classifier is set to REPLY
   */
  bool isReply() const;

  /**
   * Checks if this header is a result header
   * @return true, if the classifier is set to RESULT
   */
  bool isResult() const;

  /**
   * Checks if this header is a write header
   * @return true, if ...
   */
  bool isWrite() const;

  /**
   * Check if destination and source addresses are set.
   * @return true, if destination and source addresses are set
   */
  bool areAddressesSet() const;

  /**
   * Set member SpecificationVersion.
   * @param c_specificationVersion Value to set
   */
  void setSpecificationVersion(const xs_string &c_specificationVersion);

  /**
   * Returns const reference to member SpecificationVersion.
   * @return const reference to member specificationVersion
   */
  const xs_string &getSpecificationVersion() const;

  /**
   * Returns if member SpecificationVersion is set.
   * @retval true member SpecificationVersion is set
   * @retval false member SpecificationVersion is not set
   */
  bool getSpecificationVersionIsSet() const;

  /**
   * Unsets member SpecificationVersion
   */
  void cleanSpecificationVersion();

  /**
   * Set member AddressSource.
   * @param c_addressSource Value to set
   */
  void setAddressSource(const FeatureAddress &c_addressSource);

  /**
   * Returns const reference to member AddressSource.
   * @return const reference to member addressSource
   */
  const FeatureAddress &getAddressSource() const;

  /**
   * Returns if member AddressSource is set.
   * @retval true member AddressSource is set
   * @retval false member AddressSource is not set
   */
  bool getAddressSourceIsSet() const;

  /**
   * Unsets member AddressSource
   */
  void cleanAddressSource();

  /**
   * Set member AddressDestination.
   * @param c_addressDestination Value to set
   */
  void setAddressDestination(const FeatureAddress &c_addressDestination);

  /**
   * Returns const reference to member AddressDestination.
   * @return const reference to member addressDestination
   */
  const FeatureAddress &getAddressDestination() const;

  /**
   * Returns if member AddressDestination is set.
   * @retval true member AddressDestination is set
   * @retval false member AddressDestination is not set
   */
  bool getAddressDestinationIsSet() const;

  /**
   * Unsets member AddressDestination
   */
  void cleanAddressDestination();

  /**
   * Set member AddressOriginator.
   * @param c_addressOriginator Value to set
   */
  void setAddressOriginator(const FeatureAddress &c_addressOriginator);

  /**
   * Returns const reference to member AddressOriginator.
   * @return const reference to member addressOriginator
   */
  const FeatureAddress &getAddressOriginator() const;

  /**
   * Returns if member AddressOriginator is set.
   * @retval true member AddressOriginator is set
   * @retval false member AddressOriginator is not set
   */
  bool getAddressOriginatorIsSet() const;

  /**
   * Unsets member AddressOriginator
   */
  void cleanAddressOriginator();

  /**
   * Set member MsgCounter.
   * @param c_msgCounter Value to set
   */
  void setMsgCounter(const xs_unsignedLong &c_msgCounter);

  /**
   * Returns const reference to member MsgCounter.
   * @return const reference to member msgCounter
   */
  const xs_unsignedLong &getMsgCounter() const;

  /**
   * Returns if member MsgCounter is set.
   * @retval true member MsgCounter is set
   * @retval false member MsgCounter is not set
   */
  bool getMsgCounterIsSet() const;

  /**
   * Unsets member MsgCounter
   */
  void cleanMsgCounter();

  /**
   * Set member MsgCounterReference.
   * @param c_msgCounterReference Value to set
   */
  void setMsgCounterReference(const xs_unsignedLong &c_msgCounterReference);

  /**
   * Returns const reference to member MsgCounterReference.
   * @return const reference to member msgCounterReference
   */
  const xs_unsignedLong &getMsgCounterReference() const;

  /**
   * Returns if member MsgCounterReference is set.
   * @retval true member MsgCounterReference is set
   * @retval false member MsgCounterReference is not set
   */
  bool getMsgCounterReferenceIsSet() const;

  /**
   * Unsets member MsgCounterReference
   */
  void cleanMsgCounterReference();

  /**
   * Set member CmdClassifier.
   * @param c_cmdClassifier Value to set
   */
  void setCmdClassifier(const CmdClassifier &c_cmdClassifier);

  /**
   * Returns const reference to member CmdClassifier.
   * @return const reference to member cmdClassifier
   */
  const CmdClassifier &getCmdClassifier() const;

  /**
   * Returns if member CmdClassifier is set.
   * @retval true member CmdClassifier is set
   * @retval false member CmdClassifier is not set
   */
  bool getCmdClassifierIsSet() const;

  /**
   * Unsets member CmdClassifier
   */
  void cleanCmdClassifier();

  /**
   * Set member AckRequest.
   * @param c_ackRequest Value to set
   */
  void setAckRequest(const xs_boolean &c_ackRequest);

  /**
   * Returns const reference to member AckRequest.
   * @return const reference to member ackRequest
   */
  const xs_boolean &getAckRequest() const;

  /**
   * Returns if member AckRequest is set.
   * @retval true member AckRequest is set
   * @retval false member AckRequest is not set
   */
  bool getAckRequestIsSet() const;

  /**
   * Unsets member AckRequest
   */
  void cleanAckRequest();

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
   * Get this headers CmdClassifier as a string.
   * @return the CmdClassifier of this header
   */
  std::string getClassifierAsString() const;

  /**
   * Get the CmdClassifier of this header.
   * \deprecated Use getCmdClassifier()
   * @return the CmdClassifier of this header
   */
  const CmdClassifier &getClassifier() const;

  /**
   * Set the CmdClassifier of this header.
   * \deprecated Use setCmdClassifier()
   * @param c_value the CmdClassifier for this header
   */
  void setClassifier(const CmdClassifier &c_value);

  /**
   * Prepare this header to be used for sending a response. This will swap
   * source and destination
   * address and set a new classifier.
   * @param c_classifier the classifier to set
   */
  void changeToResponse(CmdClassifier c_classifier);

  /**
   * Prepare this header to be used for sending a response. This will swap
   * source and destination
   * address and set a new classifier.
   * \deprecated use changeToResponse().
   * @param c_classifier the classifier to set
   */
  void changeToReply(CmdClassifier c_classifier);

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  xs_unsignedLong createNewMsgCounter();

  bool m_specificationVersionIsSet;
  xs_string m_specificationVersion;

  bool m_addressSourceIsSet;
  FeatureAddress m_addressSource;

  bool m_addressDestinationIsSet;
  FeatureAddress m_addressDestination;

  bool m_addressOriginatorIsSet;
  FeatureAddress m_addressOriginator;

  bool m_msgCounterIsSet;
  xs_unsignedLong m_msgCounter;

  bool m_msgCounterReferenceIsSet;
  xs_unsignedLong m_msgCounterReference;

  bool m_cmdClassifierIsSet;
  CmdClassifier m_cmdClassifier;

  bool m_ackRequestIsSet;
  xs_boolean m_ackRequest;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;
};

//! typedef for non-const smart pointer type Header
using HeaderPtr = std::shared_ptr<Header>;

//! typedef for const type Header
using HeaderConst = const Header;

//! typedef for const type Header
using HeaderConstPtr = std::shared_ptr<HeaderConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_HEADER_H_