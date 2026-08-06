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

#ifndef KEO_DATAGRAM_CREATE_SPINE_DATA_CLASS_H_
#define KEO_DATAGRAM_CREATE_SPINE_DATA_CLASS_H_

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/Function.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/* ******************************************************************************
 * *
 *  class CreateSpineDataClass: definition *
 * ******************************************************************************
 */
/** Utility class to create a SPINE class of a specific SPINE data type. **/
class CreateSpineDataClass {
public:
  /**
   * Create a SPINE CmdData object of a given type.
   * @param type the type to create
   * @return created data object
   */
  static CmdDataPtr createCmdData(const CmdData::Type type);

  /**
   * Create a SPINE DataSelectors object of a given type.
   * @param type the type to create
   * @return created data object
   */
  static DataSelectorsPtr createDataSelectors(const DataSelectors::Type type);

  /**
   * Create a SPINE DataElements object of a given type.
   * @param type the type to create
   * @return created data object
   */
  static DataElementsPtr createDataElements(const DataElements::Type type);

private:
  CreateSpineDataClass();
  ~CreateSpineDataClass();
};

/** @}
 */

} // namespace keo_datagram

#endif