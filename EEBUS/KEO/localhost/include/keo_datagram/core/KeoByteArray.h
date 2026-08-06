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

#ifndef KEO_DATAGRAM_CORE_KEOBYTEARRAY_H_
#define KEO_DATAGRAM_CORE_KEOBYTEARRAY_H_

#include <memory>
#include <string>
#include <vector>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * @class KeoByteArray
 * @brief Offers a small functional subset of the Qt's class QByteArray.
 *
 * Content is stored in a std::vector<char>. There exist several conversion
 * functions to parse a hex string
 * or to convert the binary content to a hex string.
 *
 * Examples:
 *  \code{.cpp}
 * KeoByteArray ba1(3, 'A');
 * ba1.toString(); // returns "AAA"
 *
 * KeoByteArray ba3;
 * ba3.fromHex("415a5A"); // creates a binary buffer, containing the three ASCII
 * characters 'A', 'Z' and 'Z'
 * ba3.toString(); // returns "AZZ" - the binary content as a string
 *
 *  \endcode
 */
class KeoByteArray {
public:
  /** Simple constructor
   */
  KeoByteArray();
  /**
   * Initializes an instance of KeoByteArray with binary content in s.
   * std::string contains explicit size information
   * to it is not zero-terminated.
   * @param s
   */
  KeoByteArray(const std::string &s);
  /**
   * Initializes an instance of KeoByteArray with binary content. In this
   * special case it is an ordinary C-String, zero-terminated.
   * @param s C-style string pointer
   */
  KeoByteArray(const char *s);
  /**
   * Initializes an instance of KeoByteArray with binary content.
   * @param s Pointer to the data
   * @param size Size of the data
   */
  KeoByteArray(const char *s, size_t size);
  /**
   * Initializes an instance of KeoByteArray from a vector of characters.
   * @param s character vector
   */
  KeoByteArray(const std::vector<char> &s);
  /**
   * Initializes an instance of KeoByteArray from a vector of unsigned
   * characters.
   * @param s unsigned character vector
   */
  KeoByteArray(const std::vector<unsigned char> &s);
  /**
   * Initializes an instance of KeoByteArray with a sequence of a single byte.
   * @param size count of bytes to initialize
   * @param fillChar filling character (byte)
   */
  KeoByteArray(size_t size, char fillChar);

  /**
   * Destructor
   */
  ~KeoByteArray() {} // nothing to destruct
                     /**
                      * Returns a hex string, representing the current binary content of the
                      * object. Copies the content.
                      * @return hex string representation of the current binary content.
                      */
  std::string toHex() const;

  // TODO add void  toHex( std::string& string );

  /**
   * Returns the binary content as a std::string. Can include zero bytes! The
   * string object contains the size.
   * @return
   */
  std::string toString() const;

  /**
   * Returns the binary content as a std::vector<char>.
   * @return
   */
  std::vector<char> toVector() const;

  /**
   * Returns the binary content as a std::vector<unsigned char>.
   * @return
   */
  std::vector<unsigned char> toVectorUnsigned() const;

  /**
   *    Initializes the object from a character array. Not zero-terminated, but
   * the explicit length is given
   */
  void setContent(const char *content, size_t sz);

  /**
   * Tries to parse a hex string, e.g. "038c7F".
   * String must have even count of characters (0..9, a-f, A-F).
   * @param hexString a hex string. Case is ignored. C-Style string,
   * zero-terminated
   * @return true, if string could be parsed. If false, the string was no valid
   * hex string or NULL
   */
  static KeoByteArray fromHex(const char *hexString);

  /**
   * @see fromHex(const char*)
   * @param hexString a hex string. Case is ignored. C-Style string,
   * zero-terminated
   * @return true, if string could be parsed. If false, the string was no valid
   * hex string
   */
  static KeoByteArray fromHex(const std::string &hexString);

  /**
   * Sets character byte c at index position c. Works only if there is already a
   * character!
   */
  void set(size_t index, char c);

  /**
   * Length of the binary content.
   * @return byte size in binary buffer
   */
  size_t length() const;

  /**
   * Resets the buffer.
   */
  void clear();

  /**
   * Fills the byte buffer.
   * @param size bytes to fill (times to repeat fillChar)
   * @param fillChar character / byte to fill
   */
  void fill(size_t size, char fillChar);

  /**
   * Compares to another instance of this class.
   * @param other instance to compare
   * @return true if byte buffer contains the same
   */
  bool equals(const KeoByteArray &other) const;

  /**
   * @see equals(const KeoByteArray &).
   * Compares to another instance of this class.
   * @param r other instance to compare
   * @return
   */
  bool operator==(const KeoByteArray &r) const { return equals(r); }

  /**
   * Compares to another instance of this class
   * @param r other instance to compare
   * @return true, if buffers do not contain the same
   */
  bool operator!=(const KeoByteArray &r) const { return !equals(r); }

  /**
   * Assignment operator. Copies the content.
   * @param other the other instance
   * @return
   */
  KeoByteArray &operator=(const KeoByteArray &other);

  /**
   * Helper to check valid hex chars
   * @param c character to test
   * @return true if character matches [0-9a-fA-F]
   */
  static bool isHexChar(char c);

  /**
   * Returns a const char representation of the byte array.
   * @return the const char representation
   */
  const char *constData() const;

private:
  std::vector<char> m_data;
};

/* ******************************************************************************
 * *
 *  typedef for shared data pointer *
 * ******************************************************************************
 */

//! typedef for non-const smart pointer type KeoByteArray
using KeoByteArrayPtr = std::shared_ptr<KeoByteArray>;

//! typedef for const type KeoByteArray
using KeoByteArrayConst = const KeoByteArray;

//! typedef for const smart pointer type KeoByteArray
using KeoByteArrayConstPtr = std::shared_ptr<KeoByteArrayConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_KEOBYTEARRAY_H_