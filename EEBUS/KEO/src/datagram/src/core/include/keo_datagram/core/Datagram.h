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

#ifndef KEO_DATAGRAM_CORE_DATAGRAM_H_
#define KEO_DATAGRAM_CORE_DATAGRAM_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/Header.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/Payload.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Cmd.h>
#include <keo_datagram/core/DatagramParserException.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration Datagram
 */
class Datagram : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  Datagram();

  explicit Datagram(const CmdClassifier c_classifier);
  Datagram(const Header &c_header, const Payload &c_payload);
  Datagram(const Header &c_header, const Cmd &c_cmd);
  Datagram(const Header &c_header, const std::vector<Cmd> &c_Cmds);

  /**
   * \deprecated Use Datagram(const Header& c_pHeader, const Cmd& c_pCmd)
   * instead.
   */
  Datagram(const HeaderPtr &c_pHeader, const CmdPtr &c_pCmd);

  /**
   * \deprecated Use Datagram(const Header& c_pHeader, const std::vector<Cmd>&
   * c_pCmds) instead.
   */
  Datagram(const HeaderPtr &c_pHeader, const std::vector<CmdPtr> &c_pCmds);

  Datagram(const Datagram &c_classObject);
  Datagram(Datagram &&c_classObject);

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
  bool operator==(const Datagram &c_classObject) const;

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
  bool operator!=(const Datagram &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  Datagram &operator=(const Datagram &c_classObject);
  Datagram &operator=(Datagram &&c_classObject);

  /**
   * Checks if this datagram requires a "response" message.
   *
   * The kind of response datagram that is required depends on the classifier of
   * the datagram.
   *
   * - If this datagram is a READ and this method returns true, a RESULT (with
   * error code != 0)
   *   response is required if the READ cannot be satisfied. If the READ can be
   * satisfied a REPLY
   *   response is required.
   * - If this datagram is not a READ and this methods returns true, a RESULT
   * response is
   *   required.
   *
   * @return true, if the datagram requires a response message
   */
  bool requiresResponse() const;

  /**
   * Checks if this datagram is a call datagram
   * @return true, if the headers classifier is set to CALL
   */
  bool isCall() const;

  /**
   * Checks if this datagram is a notify datagram
   * @return true, if the headers classifier is set to NOTIFY
   */
  bool isNotify() const;

  /**
   * Checks if this datagram is a read datagram
   * @return true, if the headers classifier is set to READ
   */
  bool isRead() const;

  /**
   * Checks if this datagram is a reply datagram
   * @return true, if the headers classifier is set to REPLY
   */
  bool isReply() const;

  /**
   * Checks if this datagram is a result datagram
   * @return true, if the headers classifier is set to RESULT
   */
  bool isResult() const;

  /**
   * Checks if this datagram is a write datagram
   * @return true, if ...
   */
  bool isWrite() const;

  /**
   * Set member Header.
   * @param c_header Value to set
   */
  void setHeader(const Header &c_header);

  /**
   * Returns const reference to member Header.
   * @return const reference to member header
   */
  const Header &getHeader() const;

  /**
   * Returns if member Header is set.
   * @retval true member Header is set
   * @retval false member Header is not set
   */
  bool getHeaderIsSet() const;

  /**
   * Unsets member Header
   */
  void cleanHeader();

  /**
   * Set member Payload.
   * @param c_payload Value to set
   */
  void setPayload(const Payload &c_payload);

  /**
   * Returns const reference to member Payload.
   * @return const reference to member payload
   */
  const Payload &getPayload() const;

  /**
   * Returns if member Payload is set.
   * @retval true member Payload is set
   * @retval false member Payload is not set
   */
  bool getPayloadIsSet() const;

  /**
   * Unsets member Payload
   */
  void cleanPayload();

  /**
   * Get a non-const reference to this datagrams headers.
   * @return this datagrams header
   */
  Header &getHeader();

  /**
   * Set a header for this datagram.
   * \deprecated Use getHeader(const Header&) instead.
   * @param pHeader the header to set
   */
  void setHeader(HeaderPtr pHeader);

  /**
   * Set commands for this datagram.
   * \deprecated Use setCmd(const Cmd&) instead.
   * @param pCmd the command to set
   */
  void setCmd(CmdPtr pCmd);

  /**
   * Set the command of this datagram.
   * @param cmd the cmd to set
   */
  void setCmd(const Cmd &cmd);

  /**
   * Get the command for this datagram.
   * This will parse the datagram's payload if it has not been parsed, yet.
   * @return the command
   */
  const Cmd &getCmd() const;

  /**
   * Get the command data of this datagram.
   * @return the command data
   */
  CmdDataPtr getCmdData() const;

  /**
   * Get the data type for this datagram.
   * @return the command data type
   */
  CmdData::Type getCmdDataType() const;

  /**
   * Get the command classifier of this datagram.
   * @return the command classifier
   */
  CmdClassifier getCmdClassifier() const;

  /**
   * Get the command classifier of this datagram.
   * \deprecated Use getCmdClassifier() instead.
   * @return the command classifier
   */
  CmdClassifier getClassifier() const;

  /**
   * Get the msg counter of this datagram.
   * @return the msg counter
   */
  xs_unsignedLong getMsgCounter() const;

  /**
   * Get the msg counter reference of this datagram.
   * @return the msg counter reference
   */
  xs_unsignedLong getMsgCounterReference() const;

  /**
   * Get the source address of the datagram
   * @return the source address
   */
  const FeatureAddress &getSourceAddress() const;

  /**
   * Set the source address of the datagram.
   * @param c_address the new source address
   */
  void setSourceAddress(const FeatureAddress &c_address);

  /**
   * Get the destination for the datagram.
   * @return the destination address
   */
  const FeatureAddress &getDestinationAddress() const;

  /**
   * Set the destination for the datagram.
   * @param c_address destination address
   */
  void setDestinationAddress(const FeatureAddress &c_address);

  /**
   * Set the command classifier for the datagram.
   * @param c_classifier the classifier to set
   */
  void setCmdClassifier(CmdClassifier::Value c_classifier);

  /**
   * Prepare this datagram to be used for sending a response. This will swap
   * source and destination
   * address and set a new classifier.
   * @param c_classifier the classifier to set
   */
  void changeToResponse(CmdClassifier c_classifier);

  /**
   * Prepare this datagram to be used for sending a response. This will swap
   * source and destination
   * address and set a new classifier.
   * \deprecated use changeToResponse().
   * @param c_classifier the classifier to set
   */
  void changeToReply(CmdClassifier c_classifier);

  /**
   * Prepare a reply datagram to this datagram.
   * If no CmdData is passed to this method, it only prepares the header of the
   * datagram.
   * @param c_data the CmdData to set on the new datagram
   * @return a reply datagram
   */
  Datagram createReply(const CmdDataPtr &c_data = CmdDataPtr()) const;

  /**
   * Prepare a result datagram to this datagram.
   * @param c_errorNumber status of the result
   * @param c_description description of the result
   * @return a result datagram
   */
  Datagram createResult(const xs_unsignedInt c_errorNumber,
                        const std::string &c_description = "") const;

  /**
   * Check if payload is set with at least one command.
   * @return true, if payload is valid filled out
   */
  bool isPayloadValid() const;

  /**
   * Checks if the payload is parsed.
   * @return true, if payload is parsed
   */
  bool isPayloadParsed() const;

  /**
   * Parse the payload from the saved Json.
   * @return true, if payload could be parsed correctly
   */
  bool parsePayload();

  /**
   * Parse the payload from the saved Json.
   * @throws DatagramParserException if the payload could not be parsed
   */
  void parsePayloadThrows();

  /**
   * Checks if the header is valid.
   * @return true, if header is valid filled out
   */
  bool isHeaderValid() const;

  /**
   * Creates a new Datagram from a Json string.
   * Only the header of the datagram will be parsed and checked for
   * validity. To also parse the payload, call
   * Datagram::parsePayload() on the instance.
   * @param jsonString a Json string representing a SPINE datagram
   * @return a SPINE datagram if the header portion is valid, else an empty
   * datagram (check isEmpty())
   */
  static Datagram fromJson(const std::string &jsonString);

  /**
   * Creates a new Datagram from a Json string.
   * Only the header of the datagram will be parsed and checked for
   * validity. To also parse the payload, call
   * Datagram::parsePayload() on the instance.
   * @param jsonString a Json string representing a SPINE datagram
   * @throws DatagramParserException if the payload could not be parsed
   * @return a SPINE datagram
   */
  static Datagram fromJsonThrows(const std::string &jsonString);

  std::string toJson() const override;

  static Cmd NO_CMD;

private:
  bool fromJson(KeoJsonValue *json) override;

  bool m_headerIsSet;
  Header m_header;

  bool m_payloadIsSet;
  Payload m_payload;

  std::shared_ptr<KeoJsonValue> m_payloadUnparsed;
};

//! typedef for non-const smart pointer type Datagram
using DatagramPtr = std::shared_ptr<Datagram>;

//! typedef for const type Datagram
using DatagramConst = const Datagram;

//! typedef for const type Datagram
using DatagramConstPtr = std::shared_ptr<DatagramConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_DATAGRAM_H_