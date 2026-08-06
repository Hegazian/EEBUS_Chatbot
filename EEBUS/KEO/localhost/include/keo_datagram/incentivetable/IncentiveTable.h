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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLE_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLE_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveTableIncentiveSlot.h>
#include <keo_datagram/incentivetable/TariffData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveTable
 */
class IncentiveTable : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveTable();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tariff the member to set
   * @param c_incentiveSlot the member to set
   */
  IncentiveTable(
      const TariffData &c_tariff,
      const std::vector<IncentiveTableIncentiveSlot> &c_incentiveSlot);

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
  bool operator==(const IncentiveTable &c_classObject) const;

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
  bool operator!=(const IncentiveTable &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Tariff.
   * @param c_tariff Value to set
   */
  void setTariff(const TariffData &c_tariff);

  /**
   * Returns const reference to member Tariff.
   * @return const reference to member tariff
   */
  const TariffData &getTariff() const;

  /**
   * Returns if member Tariff is set.
   * @retval true member Tariff is set
   * @retval false member Tariff is not set
   */
  bool getTariffIsSet() const;

  /**
   * Unsets member Tariff
   */
  void cleanTariff();

  /**
   * Set member IncentiveSlot.
   * @param c_incentiveSlot Value to set
   */
  void setIncentiveSlot(
      const std::vector<IncentiveTableIncentiveSlot> &c_incentiveSlot);

  /**
   * Returns const reference to member IncentiveSlot.
   * @return const reference to member incentiveSlot
   */
  const std::vector<IncentiveTableIncentiveSlot> &getIncentiveSlot() const;

  /**
   * Returns if member IncentiveSlot is set.
   * @retval true member IncentiveSlot is set
   * @retval false member IncentiveSlot is not set
   */
  bool getIncentiveSlotIsSet() const;

  /**
   * Unsets member IncentiveSlot
   */
  void cleanIncentiveSlot();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffIsSet;
  TariffData m_tariff;

  bool m_incentiveSlotIsSet;
  std::vector<IncentiveTableIncentiveSlot> m_incentiveSlot;
};

//! typedef for non-const smart pointer type IncentiveTable
using IncentiveTablePtr = std::shared_ptr<IncentiveTable>;

//! typedef for const type IncentiveTable
using IncentiveTableConst = const IncentiveTable;

//! typedef for const type IncentiveTable
using IncentiveTableConstPtr = std::shared_ptr<IncentiveTableConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLE_H_