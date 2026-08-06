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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFOVERALLCONSTRAINTSDATAELEMENTS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFOVERALLCONSTRAINTSDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffOverallConstraintsDataElements
 */
class TariffOverallConstraintsDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TariffOverallConstraintsDataElements();

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
  bool
  operator==(const TariffOverallConstraintsDataElements &c_classObject) const;

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
  bool
  operator!=(const TariffOverallConstraintsDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member MaxTariffCount.
   */
  void setMaxTariffCount();

  /**
   * Returns if member MaxTariffCount is set.
   * @retval true member MaxTariffCount is set
   * @retval false member MaxTariffCount is not set
   */
  bool getMaxTariffCountIsSet() const;

  /**
   * Unsets member MaxTariffCount
   */
  void cleanMaxTariffCount();

  /**
   * Set member MaxBoundaryCount.
   */
  void setMaxBoundaryCount();

  /**
   * Returns if member MaxBoundaryCount is set.
   * @retval true member MaxBoundaryCount is set
   * @retval false member MaxBoundaryCount is not set
   */
  bool getMaxBoundaryCountIsSet() const;

  /**
   * Unsets member MaxBoundaryCount
   */
  void cleanMaxBoundaryCount();

  /**
   * Set member MaxTierCount.
   */
  void setMaxTierCount();

  /**
   * Returns if member MaxTierCount is set.
   * @retval true member MaxTierCount is set
   * @retval false member MaxTierCount is not set
   */
  bool getMaxTierCountIsSet() const;

  /**
   * Unsets member MaxTierCount
   */
  void cleanMaxTierCount();

  /**
   * Set member MaxIncentiveCount.
   */
  void setMaxIncentiveCount();

  /**
   * Returns if member MaxIncentiveCount is set.
   * @retval true member MaxIncentiveCount is set
   * @retval false member MaxIncentiveCount is not set
   */
  bool getMaxIncentiveCountIsSet() const;

  /**
   * Unsets member MaxIncentiveCount
   */
  void cleanMaxIncentiveCount();

  /**
   * Set member MaxBoundariesPerTariff.
   */
  void setMaxBoundariesPerTariff();

  /**
   * Returns if member MaxBoundariesPerTariff is set.
   * @retval true member MaxBoundariesPerTariff is set
   * @retval false member MaxBoundariesPerTariff is not set
   */
  bool getMaxBoundariesPerTariffIsSet() const;

  /**
   * Unsets member MaxBoundariesPerTariff
   */
  void cleanMaxBoundariesPerTariff();

  /**
   * Set member MaxTiersPerTariff.
   */
  void setMaxTiersPerTariff();

  /**
   * Returns if member MaxTiersPerTariff is set.
   * @retval true member MaxTiersPerTariff is set
   * @retval false member MaxTiersPerTariff is not set
   */
  bool getMaxTiersPerTariffIsSet() const;

  /**
   * Unsets member MaxTiersPerTariff
   */
  void cleanMaxTiersPerTariff();

  /**
   * Set member MaxBoundariesPerTier.
   */
  void setMaxBoundariesPerTier();

  /**
   * Returns if member MaxBoundariesPerTier is set.
   * @retval true member MaxBoundariesPerTier is set
   * @retval false member MaxBoundariesPerTier is not set
   */
  bool getMaxBoundariesPerTierIsSet() const;

  /**
   * Unsets member MaxBoundariesPerTier
   */
  void cleanMaxBoundariesPerTier();

  /**
   * Set member MaxIncentivesPerTier.
   */
  void setMaxIncentivesPerTier();

  /**
   * Returns if member MaxIncentivesPerTier is set.
   * @retval true member MaxIncentivesPerTier is set
   * @retval false member MaxIncentivesPerTier is not set
   */
  bool getMaxIncentivesPerTierIsSet() const;

  /**
   * Unsets member MaxIncentivesPerTier
   */
  void cleanMaxIncentivesPerTier();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_maxTariffCountIsSet;

  // ElementTag
  bool m_maxBoundaryCountIsSet;

  // ElementTag
  bool m_maxTierCountIsSet;

  // ElementTag
  bool m_maxIncentiveCountIsSet;

  // ElementTag
  bool m_maxBoundariesPerTariffIsSet;

  // ElementTag
  bool m_maxTiersPerTariffIsSet;

  // ElementTag
  bool m_maxBoundariesPerTierIsSet;

  // ElementTag
  bool m_maxIncentivesPerTierIsSet;
};

//! typedef for non-const smart pointer type
//! TariffOverallConstraintsDataElements
using TariffOverallConstraintsDataElementsPtr =
    std::shared_ptr<TariffOverallConstraintsDataElements>;

//! typedef for const type TariffOverallConstraintsDataElements
using TariffOverallConstraintsDataElementsConst =
    const TariffOverallConstraintsDataElements;

//! typedef for const type TariffOverallConstraintsDataElements
using TariffOverallConstraintsDataElementsConstPtr =
    std::shared_ptr<TariffOverallConstraintsDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFOVERALLCONSTRAINTSDATAELEMENTS_H_