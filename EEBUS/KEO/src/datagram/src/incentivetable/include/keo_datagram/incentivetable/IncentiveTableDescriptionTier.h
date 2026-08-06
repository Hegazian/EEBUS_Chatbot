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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTIONTIER_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTIONTIER_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveDescriptionData.h>
#include <keo_datagram/incentivetable/TierBoundaryDescriptionData.h>
#include <keo_datagram/incentivetable/TierDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveTableDescriptionTier
 */
class IncentiveTableDescriptionTier : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveTableDescriptionTier();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tierDescription the member to set
   * @param c_boundaryDescription the member to set
   * @param c_incentiveDescription the member to set
   */
  IncentiveTableDescriptionTier(
      const TierDescriptionData &c_tierDescription,
      const std::vector<TierBoundaryDescriptionData> &c_boundaryDescription,
      const std::vector<IncentiveDescriptionData> &c_incentiveDescription);

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
  bool operator==(const IncentiveTableDescriptionTier &c_classObject) const;

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
  bool operator!=(const IncentiveTableDescriptionTier &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member TierDescription.
   * @param c_tierDescription Value to set
   */
  void setTierDescription(const TierDescriptionData &c_tierDescription);

  /**
   * Returns const reference to member TierDescription.
   * @return const reference to member tierDescription
   */
  const TierDescriptionData &getTierDescription() const;

  /**
   * Returns if member TierDescription is set.
   * @retval true member TierDescription is set
   * @retval false member TierDescription is not set
   */
  bool getTierDescriptionIsSet() const;

  /**
   * Unsets member TierDescription
   */
  void cleanTierDescription();

  /**
   * Set member BoundaryDescription.
   * @param c_boundaryDescription Value to set
   */
  void setBoundaryDescription(
      const std::vector<TierBoundaryDescriptionData> &c_boundaryDescription);

  /**
   * Returns const reference to member BoundaryDescription.
   * @return const reference to member boundaryDescription
   */
  const std::vector<TierBoundaryDescriptionData> &
  getBoundaryDescription() const;

  /**
   * Returns if member BoundaryDescription is set.
   * @retval true member BoundaryDescription is set
   * @retval false member BoundaryDescription is not set
   */
  bool getBoundaryDescriptionIsSet() const;

  /**
   * Unsets member BoundaryDescription
   */
  void cleanBoundaryDescription();

  /**
   * Set member IncentiveDescription.
   * @param c_incentiveDescription Value to set
   */
  void setIncentiveDescription(
      const std::vector<IncentiveDescriptionData> &c_incentiveDescription);

  /**
   * Returns const reference to member IncentiveDescription.
   * @return const reference to member incentiveDescription
   */
  const std::vector<IncentiveDescriptionData> &getIncentiveDescription() const;

  /**
   * Returns if member IncentiveDescription is set.
   * @retval true member IncentiveDescription is set
   * @retval false member IncentiveDescription is not set
   */
  bool getIncentiveDescriptionIsSet() const;

  /**
   * Unsets member IncentiveDescription
   */
  void cleanIncentiveDescription();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tierDescriptionIsSet;
  TierDescriptionData m_tierDescription;

  bool m_boundaryDescriptionIsSet;
  std::vector<TierBoundaryDescriptionData> m_boundaryDescription;

  bool m_incentiveDescriptionIsSet;
  std::vector<IncentiveDescriptionData> m_incentiveDescription;
};

//! typedef for non-const smart pointer type IncentiveTableDescriptionTier
using IncentiveTableDescriptionTierPtr =
    std::shared_ptr<IncentiveTableDescriptionTier>;

//! typedef for const type IncentiveTableDescriptionTier
using IncentiveTableDescriptionTierConst = const IncentiveTableDescriptionTier;

//! typedef for const type IncentiveTableDescriptionTier
using IncentiveTableDescriptionTierConstPtr =
    std::shared_ptr<IncentiveTableDescriptionTierConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTIONTIER_H_