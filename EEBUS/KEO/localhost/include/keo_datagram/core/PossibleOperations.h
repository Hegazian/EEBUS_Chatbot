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

#ifndef KEO_DATAGRAM_CORE_POSSIBLEOPERATIONS_H_
#define KEO_DATAGRAM_CORE_POSSIBLEOPERATIONS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/PossibleOperationsElements.h>
#include <keo_datagram/core/PossibleOperationsRead.h>
#include <keo_datagram/core/PossibleOperationsWrite.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration PossibleOperations
 */
class PossibleOperations : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PossibleOperations();

  /**
   * Construct an instance of this class and set its member.
   * @param c_read the member to set
   * @param c_write the member to set
   */
  PossibleOperations(const PossibleOperationsRead &c_read,
                     const PossibleOperationsWrite &c_write);

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
  bool operator==(const PossibleOperations &c_classObject) const;

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
  bool operator!=(const PossibleOperations &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Read.
   * @param c_read Value to set
   */
  void setRead(const PossibleOperationsRead &c_read);

  /**
   * Returns const reference to member Read.
   * @return const reference to member read
   */
  const PossibleOperationsRead &getRead() const;

  /**
   * Returns if member Read is set.
   * @retval true member Read is set
   * @retval false member Read is not set
   */
  bool getReadIsSet() const;

  /**
   * Unsets member Read
   */
  void cleanRead();

  /**
   * Set member Write.
   * @param c_write Value to set
   */
  void setWrite(const PossibleOperationsWrite &c_write);

  /**
   * Returns const reference to member Write.
   * @return const reference to member write
   */
  const PossibleOperationsWrite &getWrite() const;

  /**
   * Returns if member Write is set.
   * @retval true member Write is set
   * @retval false member Write is not set
   */
  bool getWriteIsSet() const;

  /**
   * Unsets member Write
   */
  void cleanWrite();

  /**
   * @copydoc CmdData::reduce()
   */
  PossibleOperations reduce(const PossibleOperationsElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_readIsSet;
  PossibleOperationsRead m_read;

  bool m_writeIsSet;
  PossibleOperationsWrite m_write;
};

//! typedef for non-const smart pointer type PossibleOperations
using PossibleOperationsPtr = std::shared_ptr<PossibleOperations>;

//! typedef for const type PossibleOperations
using PossibleOperationsConst = const PossibleOperations;

//! typedef for const type PossibleOperations
using PossibleOperationsConstPtr = std::shared_ptr<PossibleOperationsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_POSSIBLEOPERATIONS_H_