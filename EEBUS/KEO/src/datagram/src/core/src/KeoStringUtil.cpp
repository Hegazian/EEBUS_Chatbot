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

#include "KeoStringUtil.h"
#include <cstring>
#include <stdexcept>
#include <stdio.h>

#ifdef __linux__

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <inttypes.h>

#elif _WIN32

#if (_MSC_VER >= 1600)
#include <inttypes.h>
#else

#define PRIx64 "lx"
#define PRIu64 "lu"

#endif

#else

#endif

#include <sstream>

//#include <limits>
namespace keo_datagram {

bool KeoStringUtil::startsWith(const std::string &str,
                               const std::string &utf8String,
                               bool caseInsensitive) {
  return KeoStringUtil::matchesSubstring(str, utf8String, caseInsensitive,
                                         false);
}

bool KeoStringUtil::endsWith(const std::string &str,
                             const std::string &utf8String,
                             bool caseInsensitive) {
  return KeoStringUtil::matchesSubstring(str, utf8String, caseInsensitive,
                                         true);
}

bool KeoStringUtil::contains(const std::string &str, const std::string &substr,
                             bool caseInsensitive) {
  size_t str1Sz = str.size();
  size_t substrSz = substr.size();
  if (str1Sz < substrSz ||
      (substrSz == 0)) // substring is bigger. Match not possible
    return false;

  bool found = false;

  if (caseInsensitive) {
    for (size_t i = 0; !found && i < ((str1Sz - substrSz) + 1); i++) {
      found = KeoStringUtil::matchesSubstring(str, substr, caseInsensitive,
                                              false, i);
      // FIXME: It is cleaner to step over Unicode characters instead of bytes
      // in case of multibyte characters.
      // But at least exact matches (case sensitive) will be detected.
      // False-positives will be unlikely.
    }
  } else {
    if (str.find(substr) !=
        std::string::npos) // case sensitive. Can use standard function.
      found = true;        // found somewhere.
  }
  return found;
}

int KeoStringUtil::compare(const std::string &str, const std::string &cmpstr,
                           bool caseInsensitive) {
  int retVal = 0;
  if (caseInsensitive) {
    size_t strSz = str.size();
    size_t cmpstrSz = cmpstr.size();
    size_t bytesToCompare = strSz > cmpstrSz ? cmpstrSz : strSz; // == min(a,b)
    if (strSz == 0 || cmpstrSz == 0) {
      retVal = 0;
    } else {
      unsigned char c1, c2;
      for (size_t i = 0; (retVal == 0) && (i < bytesToCompare); i++) {
        c1 = str.at(i);
        c2 = cmpstr.at(i);
        if (c1 < 128 && c2 < 128) {
          retVal = toupper(c1) - toupper(c2);
        } else {
          retVal = c1 - c2;
        }
      }

      if (retVal == 0 && strSz != cmpstrSz) {
        // strings are the same (CI) at the beginning, but have other lengths.
        retVal = strSz > cmpstrSz ? 1 : -1;
      }
    }
  } else {
    retVal = str.compare(cmpstr); // case sensitive. Use standard functionality
  }
  return retVal;
}

bool KeoStringUtil::startsWith(const std::string &str, const char *utf8String,
                               bool caseInsensitive) {
  if (utf8String == nullptr)
    return false;
  return KeoStringUtil::matchesSubstring(str, std::string(utf8String),
                                         caseInsensitive, false);
}

bool KeoStringUtil::endsWith(const std::string &str, const char *utf8String,
                             bool caseInsensitive) {
  if (utf8String == nullptr)
    return false;
  return KeoStringUtil::matchesSubstring(str, std::string(utf8String),
                                         caseInsensitive, true);
}

std::string KeoStringUtil::mid(const std::string &str, int startPos, int len,
                               bool isUTF8) {
  // adjust range
  if (!isUTF8) {
    // not UTF-8. Treat it like an ordinary string (1 byte per character)
    if (startPos >= static_cast<int>(str.size())) {
      return ""; // start pos is after string. return empty string
    }

    if (len > static_cast<int>(str.size()) - startPos) {
      len = str.size() -
            startPos; // wants more than in string. limit to existing bytes
    }
    return str.substr(startPos, len); // returns copy
  } else {
    // UTF-8.
    int charLen = KeoStringUtil::countRealCharacters(str);
    if (startPos >= charLen) // start pos too high
    {
      return "";
    }
    if (len > charLen - startPos) {
      len = charLen - startPos; // wants more than in string. limit to existing
                                // UTF-8 characters
    }
    std::string retString("");
    char buf[8];
    // TODO
    size_t index = 0;
    // adjust index to real byte pos, as startPos is an UTF-8 character index.
    bool wasSuccess =
        KeoStringUtil::getByteIndexFromRealCharacterIndex(str, startPos, index);
    bool finished = !wasSuccess; // failure. Do not go into loop.

    while (!finished && len > 0) {
      int status = KeoStringUtil::proceedOneCharacter(str, index);

      if (index > str.size() || status <= 0) {
        finished = true;
      } else {
        // copy "status" characters
        if ((status > 0) && (status < 6)) {
          for (int i = 0; i < status; i++) {
            buf[i] = str.at((index - status) + i);
          }
          buf[status] = '\0';

          retString.append(buf);
          len--;
        }
      }
    }
    return retString;
  }
}

std::vector<std::string> KeoStringUtil::split(const std::string &str,
                                              const char separator,
                                              bool isUTF8) {
  std::vector<std::string> resultTokens;
  size_t start = 0, end = 0;
  while ((end = str.find(separator, start)) != std::string::npos) {
    resultTokens.push_back(mid(str, start, end - start, isUTF8));
    start = end + 1;
  }
  resultTokens.push_back(mid(str, start, str.size() - start, isUTF8));
  return resultTokens;
}

/*

In QString::number and printf, the flags have the following meanings:
Format    Meaning
e    format as [-]9.9e[+|-]999
E    format as [-]9.9E[+|-]999
f    format as [-]9.9
g    use e or f format, whichever is the most concise
G    use E or f format, whichever is the most concise
 *
 A precision is also specified with the argument format. For the 'e', 'E', and
'f' formats,
 the precision represents the number of digits after the decimal point.

 For the 'g' and 'G' formats, the precision represents the maximum number
 of significant digits (trailing zeroes are omitted).

 */
std::string KeoStringUtil::dnumber(const double &num, char frm, int prec) {
  const int maxLength = 48;
  char buf[maxLength];

  size_t i = 0;
  if (prec > 15) {
    prec = 15;
  }
  // first build the sprintf format string out of arguments:
  char format[6] = {'%', '\0', '\0', '\0', '\0', '\0'};
  switch (frm) {
  case 'g':
  case 'G':
  case 'e':
  case 'E':
  case 'f':
    format[1] = '.';
    if (prec < 10) {
      format[2] = '0' + prec;
      i = 3;
    } else if (prec < 100) {
      format[3] = '0' + (prec % 10);
      format[2] = '0' + (prec / 10);
      i = 4;
    }
    format[i] = frm;
    // -> "%.6f" "%.3G" "%.12E" etc.
    break;
  default:
    format[1] = 'f'; // -> "%f"
    break;
  }
  snprintf(buf, maxLength, format, num);
  return std::string(buf);
}

std::string KeoStringUtil::number(int32_t num, int numBase) {
  // signed!
  char buf[32];
  if (numBase == 16)
    sprintf(buf, "%lx",
            static_cast<unsigned long>(num)); // hex numbers not negative
  else
    sprintf(buf, "%d", num);
  return std::string(buf);
}

std::string KeoStringUtil::lnumber(int64_t num, int numBase) {
  std::string valueStr;
  if (numBase == 16) {
    valueStr = static_cast<std::ostringstream *>(
                   &(std::ostringstream() << std::hex << num))
                   ->str();
  } else {
    valueStr = static_cast<std::ostringstream *>(&(std::ostringstream() << num))
                   ->str();
  }
  return valueStr;
}

std::string KeoStringUtil::unumber(uint32_t num, int numBase) {
  // unsigned!
  char buf[32];
  if (numBase == 16)
    sprintf(buf, "%x", num);
  else
    sprintf(buf, "%u", num);
  return std::string(buf);
}

std::string KeoStringUtil::ulnumber(uint64_t num, int numBase) {
  const int maxLength = 32;
  char buf[maxLength];

  if (numBase == 16) {
    snprintf(buf, maxLength, "%" PRIx64, num);
  } else {
    snprintf(buf, maxLength, "%" PRIu64, num); // TODO not really portable...
  }
  return std::string(buf);
}

std::string KeoStringUtil::toUpper(const std::string &str) {
  std::string retStr;
  unsigned char c; // must be unsigned. We compare character codes 0..255
  retStr.reserve(str.size());
  for (size_t i = 0; i < str.size(); i++) {
    c = str.at(i);
    if (c < 128) // be UTF-8 aware. omit character codes > 127
    {
      retStr += static_cast<unsigned char>(toupper(c));
    } else {
      retStr += c;
    }
  }
  return retStr;
}

std::string KeoStringUtil::toLower(const std::string &str) {
  std::string retStr;
  unsigned char c; // must be unsigned. We compare character codes 0..255
  retStr.reserve(str.size());
  for (size_t i = 0; i < str.size(); i++) {
    c = str.at(i);
    if (c < 128) // be UTF-8 aware. omit character codes > 127
    {
      retStr += static_cast<unsigned char>(tolower(c));
    } else {
      retStr += c;
    }
  }
  return retStr;
}

double KeoStringUtil::toDouble(const char *str) {
  if (str == nullptr) {
    throw std::invalid_argument("Not a number");
  } else {
    double tmp = 0;
    if (sscanf(str, "%lf", &tmp)) {
      return tmp;
    } else {
      throw std::invalid_argument("Not a number");
    }
  }
}
uint32_t KeoStringUtil::toUint32(const char *str) {
  if (str == nullptr) {
    throw std::invalid_argument("Not a number");
  } else {
    uint32_t tmp = 0;
    if (sscanf(str, "%u", &tmp)) {
      return tmp & 0xffffffff;
    } else {
      throw std::invalid_argument("Not a number");
    }
  }
}

uint16_t KeoStringUtil::toUint16(const char *str) {
  if (str == nullptr) {
    throw std::invalid_argument("Not a number");
  } else {
    unsigned int tmp = 0;
    if (sscanf(str, "%u", &tmp)) {
      return static_cast<uint16_t>(tmp) & 0xffff;
    } else {
      throw std::invalid_argument("Not a number");
    }
  }
}

uint64_t KeoStringUtil::toUint64(const char *str) {
  if (str == nullptr) {
    throw std::invalid_argument("Not a number");
  } else {
    uint64_t tmp = 0;
    if (sscanf(str, "%" PRIu64, &tmp)) {
      return static_cast<uint64_t>(tmp) & 0xffffffffffffffffULL;
    } else {
      throw std::invalid_argument("Not a number");
    }
  }
}

int64_t KeoStringUtil::toInt64(const char *str) {
  if (str != nullptr) {
    int64_t ret = 0;
    std::stringstream ss(str);
    ss >> ret;
    return (ret);
  } else {
    throw std::invalid_argument("Not a number");
  }
}

int32_t KeoStringUtil::toInt32(const char *str) {
  if (str == nullptr) {
    throw std::invalid_argument("Not a number");
  } else {
    int32_t tmp = 0;
    if (sscanf(str, "%d", &tmp)) {
      return tmp;
    } else {
      throw std::invalid_argument("Not a number");
    }
  }
}

int16_t KeoStringUtil::toInt16(const char *str) {
  if (str == nullptr) {
    throw std::invalid_argument("Not a number");
  } else {
    int16_t tmp = 0;
    if (sscanf(str, "%hd", &tmp)) {
      return tmp;
    } else {
      throw std::invalid_argument("Not a number");
    }
  }
}

int KeoStringUtil::replace(std::string &str, // modified!
                           const std::string &substr,
                           const std::string &utf8ReplaceString,
                           bool caseInsensitive) {
  //    size_t searchpos = 0;
  int retVal = 0;

  size_t str1Sz = str.size();
  size_t substrSz = substr.size();
  size_t utf8ReplaceStringSz = utf8ReplaceString.size();

  if (str1Sz < substrSz ||
      (substrSz == 0)) // substring is bigger. Match not possible
    return false;

  bool found = false;

  for (size_t i = 0; i < ((str1Sz - substrSz) + 1); i++) {
    found =
        KeoStringUtil::matchesSubstring(str, substr, caseInsensitive, false, i);
    if (found) {
      // replace
      str.replace(i, substrSz, utf8ReplaceString);
      retVal++; // count successful matches
      str1Sz =
          str.size(); // is modified if len(utf8ReplaceString) != len(substr)
      i += utf8ReplaceStringSz;
    }
  }

  return retVal;
}

int KeoStringUtil::replace(
    std::string &stringToModify,         // modified!
    const char *plainAsciiSearchString,  // char codes < 128 !!
    const char *plainAsciiReplaceString, // char codes < 128 !!
    bool caseInsensitive) {
  if (plainAsciiSearchString != nullptr && plainAsciiReplaceString != nullptr)
    return KeoStringUtil::replace(
        stringToModify, std::string(plainAsciiSearchString),
        std::string(plainAsciiReplaceString), caseInsensitive);
  else
    return 0; // nothing replaced
}

bool KeoStringUtil::matchesSubstring(const std::string &bigString,
                                     const std::string &stringToMatch,
                                     bool caseInsensitive, bool matchReverse,
                                     size_t startByte) {
  size_t bigStringLength = bigString.size();         // bytes! Not characters!
  size_t stringToMatchLength = stringToMatch.size(); // bytes! Not characters!

  if (bigStringLength == 0 && stringToMatchLength == 0) {
    return true; // two empty strings are the same!
  }
  if (bigStringLength == 0 || stringToMatchLength == 0 ||
      bigStringLength < stringToMatchLength) {
    return false; // cannot match
  }
  unsigned char c1, c2; // FIXME for real UTF-8 handling, a more complex "char"
                        // type must be used, which can hold
  // multiple bytes for a (logical) character.
  size_t matchStringIndex = 0; // index for other (in most cases smaller) string
  size_t startIndex = matchReverse
                          ? bigStringLength - stringToMatchLength
                          : startByte; // calculate first index to match
  bool isEqual = true;
  // FIXME this is a naive approach, as the string is treated as
  // one-byte-is-one-char! Anyway, it compares binary, so
  // at least an exact match will be detected.
  for (size_t i = startIndex; (i < bigStringLength) && isEqual &&
                              (matchStringIndex < stringToMatchLength);
       i++) // i++ even when "matchReverse" - checking is NOT done from right to
            // left in this mode.
  {
    c1 = static_cast<unsigned char>(bigString.at(i));
    c2 = static_cast<unsigned char>(stringToMatch.at(matchStringIndex++));
    if (caseInsensitive) {
      // works ONLY for plain ASCII characters!
      c1 = c1 < 128 ? static_cast<unsigned char>(tolower(c1)) : c1;
      c2 = c2 < 128 ? static_cast<unsigned char>(tolower(c2)) : c2;
      // TODO to check case of Unicode characters, further tables / algorithms
      // are needed!
      isEqual = (c1 == c2);
    } else {
      isEqual = (c1 == c2); // this will work even when comparing UTF-8
    }
  }
  return isEqual;
}

int KeoStringUtil::proceedOneCharacter(const std::string &str, size_t &index) {
  int increment = -1; // return value. Marks an error if negative.
  size_t sz = str.size();
  if (index < str.size()) {
    uint8_t c = static_cast<uint8_t>(str.at(index));

    increment = KeoStringUtil::extractUTF8BytesFromStartbyte(c);

    if (increment > 1) {
      // start byte of UTF-8 character. Tells how many bytes are expected (1..5)
      // check if the following bytes really match this
      if (static_cast<int>(sz - index) >= increment) {
        // the string has enough bytes left
        int incrementInsideUTF = -1;
        size_t expected = increment - 1; // expected continuation bytes
        bool fail = false;
        for (size_t i = index + 1; !fail && (expected-- > 0); i++) {
          incrementInsideUTF = KeoStringUtil::extractUTF8BytesFromStartbyte(
              static_cast<uint8_t>(str.at(i)));
          if (incrementInsideUTF != 0)
            fail = true; // function must return 0 for valid continuation bytes.
                         // If not: Failure.
        }
        if (fail) {
          increment = -2; // broken UTF-8. Not enough continuation bytes
        }
      } else {
        // not enough bytes. return "end of string" value, which is a sort of
        // error
        increment = -2; // broken UTF-8
      }
    }
    if (increment > 0)
      index += increment; // even if a simple character
  } // else: increment keeps -1 which means: index is after string end
  return increment;
}

int KeoStringUtil::countRealCharacters(const std::string &str,
                                       size_t indexFrom) {
  size_t cnt = 0;
  bool doCount = true;
  int chars = 0;
  while (doCount && (cnt <= str.size()) // be sure to break
         ) {
    chars = KeoStringUtil::proceedOneCharacter(str, indexFrom);
    if (chars > 0) {
      cnt++; // one character detected
    } else if (chars == 0) {
      // Inside UTF. This is illegal.
      doCount = false;
      cnt = -1; // illegal. index pointed inside a UTF-8 character
    } else {
      // -1 means end of string
      doCount = false;
    }
  }
  return cnt;
}

bool KeoStringUtil::getByteIndexFromRealCharacterIndex(
    const std::string &str, size_t utf8CharacterIndex, size_t &byteIndex) {
  bool wasSuccess = false;
  size_t indexIt = 0;
  size_t utf8CharCounter = 0;
  bool end = false;
  size_t stringByteSize = str.size();
  if (stringByteSize == 0 || utf8CharacterIndex >= stringByteSize) {
    return false; // not possible
  }

  while (!end) {
    // check first to handle the case with index 0
    if (utf8CharCounter >= utf8CharacterIndex) {
      byteIndex = indexIt;
      end = true;
      wasSuccess = true;
    }
    // proceed one real character
    int charInc = KeoStringUtil::proceedOneCharacter(str, indexIt);
    if (indexIt > stringByteSize) {
      return false;
    } else if (charInc <= 0) // not valid
    {
      wasSuccess = false;
      end = true;
    } else {

      utf8CharCounter++; // valid. Count utf8 characters
    }
  }
  return wasSuccess;
}

int KeoStringUtil::extractUTF8BytesFromStartbyte(uint8_t byte) {

  // "if" clauses are sorted by probability to increase speed

  if ((byte & 0x80) == static_cast<int>(0x00))
    return 1; // plain ASCII character

  else if ((byte & 0xC0) == static_cast<int>(0x80))
    return 0; // UTF-8 continuation byte

  else if ((byte & 0xE0) == static_cast<int>(0xC0))
    return 2; // 2-byte UTF-8 start byte

  else if ((byte & 0xF0) == static_cast<int>(0xE0))
    return 3; // 3-byte UTF-8 start byte

  else if ((byte & 0xF8) == static_cast<int>(0xF0))
    return 4;

  else if ((byte & 0xFC) == static_cast<int>(0xF8))
    return 5;

  else
    return -1; // should never happen
}
}