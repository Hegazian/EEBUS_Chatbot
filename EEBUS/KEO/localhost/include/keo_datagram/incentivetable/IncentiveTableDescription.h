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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTION_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTION_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveTableDescriptionTier.h>
#include <keo_datagram/incentivetable/TariffDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveTableDescription
 */
class IncentiveTableDescription : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveTableDescription();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tariffDescription the member to set
   * @param c_tier the member to set
   */
  IncentiveTableDescription(
      const TariffDescriptionData &c_tariffDescription,
      const std::vector<IncentiveTableDescriptionTier> &c_tier);

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
  bool operator==(const IncentiveTableDescription &c_classObject) const;

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
  bool operator!=(const IncentiveTableDescription &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member TariffDescription.
   * @param c_tariffDescription Value to set
   */
  void setTariffDescription(const TariffDescriptionData &c_tariffDescription);

  /**
   * Returns const reference to member TariffDescription.
   * @return const reference to member tariffDescription
   */
  const TariffDescriptionData &getTariffDescription() const;

  /**
   * Returns if member TariffDescription is set.
   * @retval true member TariffDescription is set
   * @retval false member TariffDescription is not set
   */
  bool getTariffDescriptionIsSet() const;

  /**
   * Unsets member TariffDescription
   */
  void cleanTariffDescription();

  /**
   * Set member Tier.
   * @param c_tier Value to set
   */
  void setTier(const std::vector<IncentiveTableDescriptionTier> &c_tier);

  /**
   * Returns const reference to member Tier.
   * @return const reference to member tier
   */
  const std::vector<IncentiveTableDescriptionTier> &getTier() const;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffDescriptionIsSet;
  TariffDescriptionData m_tariffDescription;

  bool m_tierIsSet;
  std::vector<IncentiveTableDescriptionTier> m_tier;
};

//! typedef for non-const smart pointer type IncentiveTableDescription
using IncentiveTableDescriptionPtr = std::shared_ptr<IncentiveTableDescription>;

//! typedef for const type IncentiveTableDescription
using IncentiveTableDescriptionConst = const IncentiveTableDescription;

//! typedef for const type IncentiveTableDescription
using IncentiveTableDescriptionConstPtr =
    std::shared_ptr<IncentiveTableDescriptionConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTION_H_