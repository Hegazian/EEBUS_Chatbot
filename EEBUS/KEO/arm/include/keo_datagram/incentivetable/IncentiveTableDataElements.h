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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDATAELEMENTS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveTableElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveTableDataElements
 */
class IncentiveTableDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveTableDataElements();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_incentiveTable the member to set
   */
  explicit IncentiveTableDataElements(
      const IncentiveTableElements &c_incentiveTable);

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
  bool operator==(const IncentiveTableDataElements &c_classObject) const;

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
  bool operator!=(const IncentiveTableDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member IncentiveTable.
   * @param c_incentiveTable Value to set
   */
  void setIncentiveTable(const IncentiveTableElements &c_incentiveTable);

  /**
   * Returns const reference to member IncentiveTable.
   * @return const reference to member incentiveTable
   */
  const IncentiveTableElements &getIncentiveTable() const;

  /**
   * Returns if member IncentiveTable is set.
   * @retval true member IncentiveTable is set
   * @retval false member IncentiveTable is not set
   */
  bool getIncentiveTableIsSet() const;

  /**
   * Unsets member IncentiveTable
   */
  void cleanIncentiveTable();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_incentiveTableIsSet;
  IncentiveTableElements m_incentiveTable;
};

//! typedef for non-const smart pointer type IncentiveTableDataElements
using IncentiveTableDataElementsPtr =
    std::shared_ptr<IncentiveTableDataElements>;

//! typedef for const type IncentiveTableDataElements
using IncentiveTableDataElementsConst = const IncentiveTableDataElements;

//! typedef for const type IncentiveTableDataElements
using IncentiveTableDataElementsConstPtr =
    std::shared_ptr<IncentiveTableDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDATAELEMENTS_H_