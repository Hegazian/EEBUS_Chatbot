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

/**
 *     @brief      KEDeviceAddress
 *
 *     @par        Module description
 *                 Helper methods to validate a SPINE device address
 *
 *     @author     KEO GmbH 2018 @n
 *                 All rights reserved !
 */

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */
#include <regex.h>

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */
#include <keo_datagram/core/KeoSpineDeviceAddress.h>

/* ******************************************************************************
 * *
 *  defines *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  types *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  definition *
 * ******************************************************************************
 */

namespace keo_datagram {

static char const *pattern =
    "^(d:_(i:[1-9][0-9]*|n:[a-zA-Z0-9-]+)_(([a-zA-Z0-9-]|\\\\S)+))";
// Group index:                 1   2                               34
// Group index 2 contains the vendor specific extension.
static int const groupIdxVendorSpecificExtension = 2;
// Group index 3 contains the vendor-wide unique identifier.
static int const groupIdxUid = 3;
// Maximum number of groups, used for regular expression.
static int const groupIdxCnt = 5;

bool KeoSpineDeviceAddress::isValid(std::string const &spineAddress) {
  bool ret = false;
  regex_t regex;
  int errorCode = regcomp(&regex, pattern, REG_ICASE | REG_EXTENDED);
  if (errorCode == 0) {
    errorCode = regexec(&regex, spineAddress.c_str(), 0, NULL, 0);
    ret = (errorCode == 0);
    regfree(&regex);
  } else {
    // "Failed to compile regular expression."
  }
  return (ret);
}

std::string
KeoSpineDeviceAddress::getUniqueAddress(std::string const &spineAddress) {
  std::string ret;
  regex_t regex;
  int errorCode = regcomp(&regex, pattern, REG_ICASE | REG_EXTENDED);
  if (errorCode == 0) {
    static const int sizeMatches = groupIdxCnt;
    regmatch_t matches[sizeMatches];
    errorCode = regexec(&regex, spineAddress.c_str(), sizeMatches, matches, 0);
    if (errorCode == 0) {
      if (matches[groupIdxUid].rm_so != -1) {
        ret = spineAddress.substr(matches[groupIdxUid].rm_so,
                                  matches[groupIdxUid].rm_eo -
                                      matches[groupIdxUid].rm_so);
      }
    } else {
      // "Failed to extract UID part from given SPINE address."
    }
    regfree(&regex);
  } else {
    // "Failed to compile regular expression."
  }
  return (ret);
}

std::string KeoSpineDeviceAddress::getVendorSpecificExtension(
    std::string const &spineAddress) {
  std::string ret;
  regex_t regex;
  int errorCode = regcomp(&regex, pattern, REG_ICASE | REG_EXTENDED);
  if (errorCode == 0) {
    static const int sizeMatches = 5;
    regmatch_t matches[sizeMatches];
    errorCode = regexec(&regex, spineAddress.c_str(), sizeMatches, matches, 0);
    if (errorCode == 0) {
      if (matches[groupIdxVendorSpecificExtension].rm_so != -1) {
        ret = spineAddress.substr(
            matches[groupIdxVendorSpecificExtension].rm_so,
            matches[groupIdxVendorSpecificExtension].rm_eo -
                matches[groupIdxVendorSpecificExtension].rm_so);
      }
    } else {
      // "Failed to extract vendor specific extension part from given SPINE
      // address."
    }
    regfree(&regex);
  } else {
    // "Failed to compile regular expression."
  }
  return (ret);
}
}