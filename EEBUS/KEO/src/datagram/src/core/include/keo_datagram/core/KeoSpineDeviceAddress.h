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

#ifndef KEO_DATAGRAM_KEOSPINEDEVICEADDRESS_H_
#define KEO_DATAGRAM_KEOSPINEDEVICEADDRESS_H_

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */
#include <string>

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */

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
 *  class definition *
 * ******************************************************************************
 */

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Validate the device part of SPINE addresses and extract specific parts
 * of it.
 * A valid SPINE address device part can be validated by the following regular
 * expression (taken from EEBus_TS_ProtocolSpecification v1.0.0):
 * @n
 * \code{.unparsed}
      d:_(i:[1-9][0-9]*|n:[a-zA-Z0-9-]+)_([a-zA-Z0-9-]|\\\S)+
      |  \_____________________________/ \__________________/
      |                |                          |
      |         vendor specific               vendor-wide
      |            extension                 unique address
      |
      mandatory starter

 * \endcode
 *
 * @n
 * Within the EEBus Initiative e.V. the IANA PEN SHALL be used!
 * The device address part after the second underline SHALL be unique!
 * Each vendor is responsible for the uniqueness of its device addresses.
 *
 */
class KeoSpineDeviceAddress {
public:
  /**
   * The above mentioned regular expression is applied to the given
   * SPINE address device part.
   * @param spineAddress
   *        The SPINE address (as string) to be checked.
   * @return
   *        True if device part of the given SPINE address matches
   *        the regular expression rules, else false.
   */
  static bool isValid(std::string const &spineAddress);

  /**
   * The above mentioned regular expression is applied to the given
   * SPINE address device part. The vendor specific extension part
   * is returned (excluding the enclosing '_' characters).
   * Note: i: and n: is allowed.
   * @param spineAddress
   *        The SPINE address (as string) to be evaluated.
   * @return
   *        The vendor specific extension part or empty string.
   */
  static std::string
  getVendorSpecificExtension(std::string const &spineAddress);

  /**
   * The above mentioned regular expression is applied to the given
   * SPINE address device part. The vendor-wide unique address part
   * is returned.
   * @param spineAddress
   *        The SPINE address (as string) to be evaluated.
   * @return
   *        The vendor-wide unique address part or empty string.
   */
  static std::string getUniqueAddress(std::string const &spineAddress);
};

/** @}
 */
}

#endif /* KEO_DATAGRAM_KEOSPINEDEVICEADDRESS_H_ */