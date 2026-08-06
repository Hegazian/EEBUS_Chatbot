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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLECONSTRAINTS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLECONSTRAINTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TariffData.h>
#include <keo_datagram/incentivetable/TariffOverallConstraintsData.h>
#include <keo_datagram/timetable/TimeTableConstraintsData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveTableConstraints
 */
class IncentiveTableConstraints : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveTableConstraints();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tariff the member to set
   * @param c_tariffConstraints the member to set
   * @param c_incentiveSlotConstraints the member to set
   */
  IncentiveTableConstraints(
      const TariffData &c_tariff,
      const TariffOverallConstraintsData &c_tariffConstraints,
      const TimeTableConstraintsData &c_incentiveSlotConstraints);

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
  bool operator==(const IncentiveTableConstraints &c_classObject) const;

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
  bool operator!=(const IncentiveTableConstraints &c_classObject) const;

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
   * Set member TariffConstraints.
   * @param c_tariffConstraints Value to set
   */
  void
  setTariffConstraints(const TariffOverallConstraintsData &c_tariffConstraints);

  /**
   * Returns const reference to member TariffConstraints.
   * @return const reference to member tariffConstraints
   */
  const TariffOverallConstraintsData &getTariffConstraints() const;

  /**
   * Returns if member TariffConstraints is set.
   * @retval true member TariffConstraints is set
   * @retval false member TariffConstraints is not set
   */
  bool getTariffConstraintsIsSet() const;

  /**
   * Unsets member TariffConstraints
   */
  void cleanTariffConstraints();

  /**
   * Set member IncentiveSlotConstraints.
   * @param c_incentiveSlotConstraints Value to set
   */
  void setIncentiveSlotConstraints(
      const TimeTableConstraintsData &c_incentiveSlotConstraints);

  /**
   * Returns const reference to member IncentiveSlotConstraints.
   * @return const reference to member incentiveSlotConstraints
   */
  const TimeTableConstraintsData &getIncentiveSlotConstraints() const;

  /**
   * Returns if member IncentiveSlotConstraints is set.
   * @retval true member IncentiveSlotConstraints is set
   * @retval false member IncentiveSlotConstraints is not set
   */
  bool getIncentiveSlotConstraintsIsSet() const;

  /**
   * Unsets member IncentiveSlotConstraints
   */
  void cleanIncentiveSlotConstraints();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffIsSet;
  TariffData m_tariff;

  bool m_tariffConstraintsIsSet;
  TariffOverallConstraintsData m_tariffConstraints;

  bool m_incentiveSlotConstraintsIsSet;
  TimeTableConstraintsData m_incentiveSlotConstraints;
};

//! typedef for non-const smart pointer type IncentiveTableConstraints
using IncentiveTableConstraintsPtr = std::shared_ptr<IncentiveTableConstraints>;

//! typedef for const type IncentiveTableConstraints
using IncentiveTableConstraintsConst = const IncentiveTableConstraints;

//! typedef for const type IncentiveTableConstraints
using IncentiveTableConstraintsConstPtr =
    std::shared_ptr<IncentiveTableConstraintsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLECONSTRAINTS_H_