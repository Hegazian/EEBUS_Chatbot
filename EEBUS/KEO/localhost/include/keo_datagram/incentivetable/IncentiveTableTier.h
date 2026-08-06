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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLETIER_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLETIER_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveData.h>
#include <keo_datagram/incentivetable/TierBoundaryData.h>
#include <keo_datagram/incentivetable/TierData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveTableTier
 */
class IncentiveTableTier : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveTableTier();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tier the member to set
   * @param c_boundary the member to set
   * @param c_incentive the member to set
   */
  IncentiveTableTier(const TierData &c_tier,
                     const std::vector<TierBoundaryData> &c_boundary,
                     const std::vector<IncentiveData> &c_incentive);

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
  bool operator==(const IncentiveTableTier &c_classObject) const;

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
  bool operator!=(const IncentiveTableTier &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Tier.
   * @param c_tier Value to set
   */
  void setTier(const TierData &c_tier);

  /**
   * Returns const reference to member Tier.
   * @return const reference to member tier
   */
  const TierData &getTier() const;

  /**
   * Returns if member Tier is set.
   * @retval true member Tier is set
   * @retval false member Tier is not set
   */
  bool getTierIsSet() const;

  /**
   * Unsets member Tier
   */
  void cleanTier();

  /**
   * Set member Boundary.
   * @param c_boundary Value to set
   */
  void setBoundary(const std::vector<TierBoundaryData> &c_boundary);

  /**
   * Returns const reference to member Boundary.
   * @return const reference to member boundary
   */
  const std::vector<TierBoundaryData> &getBoundary() const;

  /**
   * Returns if member Boundary is set.
   * @retval true member Boundary is set
   * @retval false member Boundary is not set
   */
  bool getBoundaryIsSet() const;

  /**
   * Unsets member Boundary
   */
  void cleanBoundary();

  /**
   * Set member Incentive.
   * @param c_incentive Value to set
   */
  void setIncentive(const std::vector<IncentiveData> &c_incentive);

  /**
   * Returns const reference to member Incentive.
   * @return const reference to member incentive
   */
  const std::vector<IncentiveData> &getIncentive() const;

  /**
   * Returns if member Incentive is set.
   * @retval true member Incentive is set
   * @retval false member Incentive is not set
   */
  bool getIncentiveIsSet() const;

  /**
   * Unsets member Incentive
   */
  void cleanIncentive();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tierIsSet;
  TierData m_tier;

  bool m_boundaryIsSet;
  std::vector<TierBoundaryData> m_boundary;

  bool m_incentiveIsSet;
  std::vector<IncentiveData> m_incentive;
};

//! typedef for non-const smart pointer type IncentiveTableTier
using IncentiveTableTierPtr = std::shared_ptr<IncentiveTableTier>;

//! typedef for const type IncentiveTableTier
using IncentiveTableTierConst = const IncentiveTableTier;

//! typedef for const type IncentiveTableTier
using IncentiveTableTierConstPtr = std::shared_ptr<IncentiveTableTierConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLETIER_H_