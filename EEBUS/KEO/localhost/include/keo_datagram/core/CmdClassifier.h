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

#ifndef KEO_DATAGRAM_CORE_CMDCLASSIFIER_H_
#define KEO_DATAGRAM_CORE_CMDCLASSIFIER_H_

#include <cstdint>
#include <string>

#include <keo_datagram/core/SpineEnumClass.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration CmdClassifier
 */
class CmdClassifier : public SpineEnum {
public:
  //! Number of possible enumeration values
  const static std::size_t MAX_ENUM = 6;

  //! Enumeration CmdClassifier::Value
  enum class Value {
    UNDEFINED__ = -1,
    READ,
    REPLY,
    NOTIFY,
    WRITE,
    CALL,
    RESULT
  };

  /** Empty Constructor */
  CmdClassifier();

  /**
  * Construct from enumeration.
  * @param c_data Classifier enumeration
  */
  CmdClassifier(CmdClassifier::Value c_data);

  /**
  * Construct from string.
  * @param c_text Classifier string
  */
  explicit CmdClassifier(const std::string &c_text);

  /**
   * Function to generate an enum object from string
   * @param c_text string for the enumeration object
   * @return enumeration object
   */
  static CmdClassifier::Value fromString(const std::string &c_text);

  /**
   * Function to generate an enum object from string
   * @param c_text string for the enumeration object
   */
  bool setFromString(const std::string &c_text);

  /**
   * Return the value of this enumeration object.
   * @return enumeration value
   */
  CmdClassifier::Value getValue() const;

  /**
   * Return the value of this enumeration object.
   * \deprecated Use getValue() instead.
   * @return enumeration value
   */
  CmdClassifier::Value getData() const;

  /**
   * Return enumeration object as string
    * @return enumeration object as string
   */
  std::string toString() const;

  /**
   * Comparison operator ==
   * @param c_enumCmdClassifier object to compare
   */
  bool operator==(const CmdClassifier &c_enumCmdClassifier) const;

  /**
   * Comparison operator !=
   * @param c_enumCmdClassifier object to compare
   */
  bool operator!=(const CmdClassifier &c_enumCmdClassifier) const;

private:
  bool setFromNumber(std::size_t c_number);
  std::size_t toNumber() const;

  CmdClassifier::Value m_data;

  // Human-readable strings of the enum data type
  static const std::string enumToString[MAX_ENUM];
};

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_CMDCLASSIFIER_H_