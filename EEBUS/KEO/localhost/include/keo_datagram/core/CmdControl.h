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

#ifndef KEO_DATAGRAM_CORE_CMDCONTROL_H_
#define KEO_DATAGRAM_CORE_CMDCONTROL_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration CmdControl
 */
class CmdControl : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  CmdControl();

  /**
   * Construct an instance of this class and set its member.
   * @param c_deleteIsSet the member to set
   * @param c_partialIsSet the member to set
   */
  CmdControl(xs_boolean c_deleteIsSet, xs_boolean c_partialIsSet);

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
  bool operator==(const CmdControl &c_classObject) const;

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
  bool operator!=(const CmdControl &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Delete.
   */
  void setDelete();

  /**
   * Returns if member Delete is set.
   * @retval true member Delete is set
   * @retval false member Delete is not set
   */
  bool getDeleteIsSet() const;

  /**
   * Unsets member Delete
   */
  void cleanDelete();

  /**
   * Set member Partial.
   */
  void setPartial();

  /**
   * Returns if member Partial is set.
   * @retval true member Partial is set
   * @retval false member Partial is not set
   */
  bool getPartialIsSet() const;

  /**
   * Unsets member Partial
   */
  void cleanPartial();

  static const CmdControl DELETE;
  static const CmdControl PARTIAL;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_deleteIsSet;

  // ElementTag
  bool m_partialIsSet;
};

//! typedef for non-const smart pointer type CmdControl
using CmdControlPtr = std::shared_ptr<CmdControl>;

//! typedef for const type CmdControl
using CmdControlConst = const CmdControl;

//! typedef for const type CmdControl
using CmdControlConstPtr = std::shared_ptr<CmdControlConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_CMDCONTROL_H_