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

#ifndef KEO_STRING_UTIL_H_
#define KEO_STRING_UTIL_H_

#include <stdint.h>
#include <string>
#include <vector>

/** @addtogroup SpineDatagram
 * @{
 */

namespace keo_datagram {

/**
 * @class KeoStringUtil
 *
 * @brief Some static helper functions for std::string
 */
class KeoStringUtil {
public:
  /**
   * Checks if string starts with another string
   * @param str The given string
   * @param utf8String Start pattern
   * @param caseInsensitive Use true/false to check patter case insensitive or
   * not
   * @return True if str starts with utf8String
   */
  static bool startsWith(const std::string &str, const std::string &utf8String,
                         bool caseInsensitive = false);

  /**
   * Checks if string starts with another string
   * @param str The given string
   * @param utf8String Start pattern
   * @param caseInsensitive Use true/false to check patter case insensitive or
   * not
   * @return True if str starts with utf8String
   */
  static bool startsWith(const std::string &str, const char *utf8String,
                         bool caseInsensitive = false);

  /**
   * Checks if string ends with another string
   * @param str The given string
   * @param utf8String End pattern
   * @param caseInsensitive Use true/false to check patter case insensitive or
   * not
   * @return true if str starts with utf8String otherwise false
   */
  static bool endsWith(const std::string &str, const std::string &utf8String,
                       bool caseInsensitive = false);

  /**
   * Checks if string ends with another string
   * @param str The given string
   * @param in End pattern
   * @param caseInsensitive Use true/false to check patter case insensitive or
   * not
   * @return true if str starts with utf8String otherwise false
   */
  static bool endsWith(const std::string &str, const char *in,
                       bool caseInsensitive = false);

  /**
   * Tells if str contains the utf8String.
   * @param str The given string
   * @param utf8String Containing pattern
   * @param caseInsensitive Use true/false to check patter case insensitive or
   * not
   * @return true if matches somewhere otherwise false
   */
  static bool contains(const std::string &str, const std::string &utf8String,
                       bool caseInsensitive = false);

  /**
   * Compares two strings, if needed case sensitive (for pure ASCII characters).
   *
   * Does not support full UTF-8 comparision.
   * @param str The given string
   * @param utf8String Containing pattern
   * @param caseInsensitive Use true/false to check patter case insensitive or
   * not
   * @return 0 if strings are equal. Else > 0 or < 0, like the std::string
   * compare method.
   */
  static int compare(const std::string &str, const std::string &utf8String,
                     bool caseInsensitive = false);

  /**
   * Extracts a piece out of a string
   * @param str source string
   * @param startPos Start position
   * @param len character length
   * @param isUTF8 Is str an utf8 string
   * @return the extracted string part
   */
  static std::string mid(const std::string &str, int startPos, int len,
                         bool isUTF8 = true);

  /**
   * Splits a string separated by char
   * @param str source string
   * @param separator separator
   * @param isUTF8 Is str an utf8 string
   * @return the extracted tokens
   */
  static std::vector<std::string> split(const std::string &str, char separator,
                                        bool isUTF8 = false);

  /**
   *    Replaces all occurences of utf8SearchString in stringToModify with
   * utf8ReplaceString.
   *    These strings are treated as UTF-8 encoded (as a convention). As
   * std::string holds the size information
   *    separately, there is no problem with zero bytes within a string, which
   * is sometimes needed in UTF-8
   * characters.
   *
   *    The search and replace algorithm considers this fact (TODO!)
   *
   *    !! Case insensitive issue: Only possible for plain ASCII characters. For
   * 'a' and 'A' it works, but for
   *    'ä' and 'Ä' not - currently, there is no mapping table for Unicode,
   * which would be needed for it.
   *
   * @param stringToModifyUtf8 source string
   * @param utf8SearchString search for this string
   * @param utf8ReplaceString replace all findings with this
   * @param caseInsensitive Use true/false to check patter case insensitive or
   * not
   * @return count of replaced tokens
   */
  static int replace(std::string &stringToModifyUtf8,
                     const std::string &utf8SearchString,
                     const std::string &utf8ReplaceString,
                     bool caseInsensitive = false);

  /**
   * A variant, which replaces string constants in a std::string
   *
   * Here, char* is a standard C-Style Null-terminated string. So use this only
   * as a convenience function to replace
   * e.g. text tokens in a
   * markup language etc.
   *
   * @param stringToModifyUtf8 source string
   * @param plainAsciiSearchString search for this string
   * @param plainAsciiReplaceString replace all findings with this
   * @param caseInsensitive Use true/false to check patter case insensitive or
   * not
   * @return count of replaced tokens
   */
  static int replace(std::string &stringToModifyUtf8,
                     const char *plainAsciiSearchString,
                     const char *plainAsciiReplaceString,
                     bool caseInsensitive = false);

  /**
   * This function is a frontend to the standard sprintf.
   *
   * @param num  number
   * @param frm  format char. It is the same as in sprintf for float values (e,
   * E, g, G, f). Default 'g'
   * @param prec precision (see sprintf). Limited to 15
   * @return The resulting string
   */
  static std::string dnumber(const double &num, char frm = 'g',
                             int prec = 6); // ???
                                            /**
                                             * Creates a string from number
                                             * Only base 10 and 16 supported.
                                             * @param num Input number
                                             * @param numBase Base default: 10
                                             * @return The resulting string
                                             */
  static std::string number(int32_t num, int numBase = 10);

  /**
   * Creates a string from number
   * Only base 10 and 16 supported.
   * @param num Input number
   * @param numBase Base default: 10
   * @return The resulting string
   */
  static std::string lnumber(int64_t num, int numBase = 10);

  /**
   * Creates a string from number
   * Only base 10 and 16 supported.
   * @param num
   * @param numBase default: 10
   * @return
   */
  static std::string unumber(uint32_t num, int numBase = 10); // ???

  /**
   * Creates a string from number
   * Only base 10 and 16 supported.
   * @param num Input number
   * @param numBase Base default: 10
   * @return The resulting string
   */
  static std::string ulnumber(uint64_t num, int numBase = 10); // ???

  /**
   * Makes an upper case string from str. Only possible for plain ASCII
   * characters (but UTF-8 is accepted)
   * @param str Input string
   * @return The upper case converted string.
   */
  static std::string toUpper(const std::string &str);
  /**
   * Makes an lower case string from str. Only possible for plain ASCII
   * characters (but UTF-8 is accepted)
   * @param str Input string
   * @return The lower case converted string.
   */
  static std::string toLower(const std::string &str);

  /**
   * Creates a number from string
   * @param str Input string with containing double value.
   * @return The double value converted from string.
   */
  static double toDouble(const char *str);

  /**
   * Creates a number from string
   * @param str Input string with containing value.
   * @return The value converted from string.
   */
  static uint32_t toUint32(const char *str);

  /**
   * Creates a number from string
   * @param str Input string with containing value.
   * @return The value converted from string.
   */
  static uint16_t toUint16(const char *str);

  /**
   * Creates a number from string
   * @param str Input string with containing value.
   * @return The value converted from string.
   */
  static uint64_t toUint64(const char *str);

  /**
   * Creates a number from string
   * @param str Input string with containing value.
   * @return The value converted from string.
   */
  static int64_t toInt64(const char *str);

  /**
   * Creates a number from string
   * @param str Input string with containing value.
   * @return The value converted from string.
   */
  static int32_t toInt32(const char *str);

  /**
   * Creates a number from string
   * @param str Input string with containing value.
   * @return The value converted from string.
   */
  static int16_t toInt16(const char *str);

  /**
   * Checks if substring matches
   * @param bigString String in which substring is searched
   * @param stringToMatch substring to find
   * @param caseInsensitive true: case does not matter. Applies only for
   * character codes < 128!
   * @param matchReverse starts searching from end
   * @param startByte optional: If no reverse match, start search at this index
   * in bigString
   * @return true if it matches
   */
  static bool matchesSubstring(const std::string &bigString,
                               const std::string &stringToMatch,
                               bool caseInsensitive, bool matchReverse,
                               size_t startByte = 0);

  /**
   * UTF-8 sensitive character incrementor. Increments the byte index by one
   * character, if it currently
   * points to a valid chacacter (and not inside an UTF-8 character).
   *
   * For Plain ASCII strings (all char codes < 128) it will always increment by
   * 1.
   * For UTF-8 characters, it will increment (in practice) by 1, 2 or 3 or even
   * more.
   *
   *
   * If character at index is a plain ASCII-character, index is incremented by
   * one and 1 is returned.
   * If character at index is e.g. a 2-byte Unicode character, index is
   * incremented by 2.
   * If character at index is INSIDE a Unicode character index is not
   * incremented and 0 is returned.
   * If the index points after the end of string (index >= str.size()), a -1 is
   * returned and index is kept unchanged.
   * If there are not enough bytes in string (broken UTF-8), a -2 is returned
   * @param str input string
   * @param index byte index of the string. Not a character index!
   * @return see description above
   */
  static int proceedOneCharacter(const std::string &str, size_t &index);

  /**
   * Counts real UTF-8 characters. For plain ASCII-Strings (all codes < 128), it
   * will return
   * the byte size of the string ( equals to str.size() )
   * @param str input string
   * @param indexFrom the BYTE INDEX of the given string to start from. NOT
   * character index. Could point inside a
   * multibyte UTF-8 character.
   * @return count of UTF-8 characters from the given byte index.
   */
  static int countRealCharacters(const std::string &str, size_t indexFrom = 0);

  /**
   * Gets the first byte index of a character in the given UTF-8 string.
   * If the string would contain, for example, only 2-byte UTF-8 characters,
   * then the returned byte index would be
   * always the
   * double numeric value of the given characterIndex.
   *
   * @param str input string, UTF-8
   * @param characterIndex IN: the given index of wanted real URF-8 character
   * @param byteIndex OUT: the byte position of the first byte of the searched
   * UTF-8 character. You could use
   * countRealCharacters() to get the size if this character in bytes.
   * @return true if successful
   */
  static bool getByteIndexFromRealCharacterIndex(const std::string &str,
                                                 size_t characterIndex,
                                                 size_t &byteIndex);

private:
  KeoStringUtil() {}

  /**
   * Checks the type of byte, if interpreted as an UTF-8 character (part).
   *
   * @param byte
   * @return 0 if continuation byte, > 1: count of bytes for the UTF-8
   * character, -1: invalid
   */
  static inline int extractUTF8BytesFromStartbyte(uint8_t byte);
};
}

/** @}
 */

#endif // KEO_STRING_UTIL_H_