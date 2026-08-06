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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFOVERALLCONSTRAINTSDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFOVERALLCONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffOverallConstraintsData
 */
class TariffOverallConstraintsData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  TariffOverallConstraintsData();

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
  bool operator==(const TariffOverallConstraintsData &c_classObject) const;

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
  bool operator!=(const TariffOverallConstraintsData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member MaxTariffCount.
   * @param c_maxTariffCount Value to set
   */
  void setMaxTariffCount(const xs_unsignedInt &c_maxTariffCount);

  /**
   * Returns const reference to member MaxTariffCount.
   * @return const reference to member maxTariffCount
   */
  const xs_unsignedInt &getMaxTariffCount() const;

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
   * @param c_maxBoundaryCount Value to set
   */
  void setMaxBoundaryCount(const xs_unsignedInt &c_maxBoundaryCount);

  /**
   * Returns const reference to member MaxBoundaryCount.
   * @return const reference to member maxBoundaryCount
   */
  const xs_unsignedInt &getMaxBoundaryCount() const;

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
   * @param c_maxTierCount Value to set
   */
  void setMaxTierCount(const xs_unsignedInt &c_maxTierCount);

  /**
   * Returns const reference to member MaxTierCount.
   * @return const reference to member maxTierCount
   */
  const xs_unsignedInt &getMaxTierCount() const;

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
   * @param c_maxIncentiveCount Value to set
   */
  void setMaxIncentiveCount(const xs_unsignedInt &c_maxIncentiveCount);

  /**
   * Returns const reference to member MaxIncentiveCount.
   * @return const reference to member maxIncentiveCount
   */
  const xs_unsignedInt &getMaxIncentiveCount() const;

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
   * @param c_maxBoundariesPerTariff Value to set
   */
  void
  setMaxBoundariesPerTariff(const xs_unsignedInt &c_maxBoundariesPerTariff);

  /**
   * Returns const reference to member MaxBoundariesPerTariff.
   * @return const reference to member maxBoundariesPerTariff
   */
  const xs_unsignedInt &getMaxBoundariesPerTariff() const;

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
   * @param c_maxTiersPerTariff Value to set
   */
  void setMaxTiersPerTariff(const xs_unsignedInt &c_maxTiersPerTariff);

  /**
   * Returns const reference to member MaxTiersPerTariff.
   * @return const reference to member maxTiersPerTariff
   */
  const xs_unsignedInt &getMaxTiersPerTariff() const;

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
   * @param c_maxBoundariesPerTier Value to set
   */
  void setMaxBoundariesPerTier(const xs_unsignedInt &c_maxBoundariesPerTier);

  /**
   * Returns const reference to member MaxBoundariesPerTier.
   * @return const reference to member maxBoundariesPerTier
   */
  const xs_unsignedInt &getMaxBoundariesPerTier() const;

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
   * @param c_maxIncentivesPerTier Value to set
   */
  void setMaxIncentivesPerTier(const xs_unsignedInt &c_maxIncentivesPerTier);

  /**
   * Returns const reference to member MaxIncentivesPerTier.
   * @return const reference to member maxIncentivesPerTier
   */
  const xs_unsignedInt &getMaxIncentivesPerTier() const;

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_maxTariffCountIsSet;
  xs_unsignedInt m_maxTariffCount;

  bool m_maxBoundaryCountIsSet;
  xs_unsignedInt m_maxBoundaryCount;

  bool m_maxTierCountIsSet;
  xs_unsignedInt m_maxTierCount;

  bool m_maxIncentiveCountIsSet;
  xs_unsignedInt m_maxIncentiveCount;

  bool m_maxBoundariesPerTariffIsSet;
  xs_unsignedInt m_maxBoundariesPerTariff;

  bool m_maxTiersPerTariffIsSet;
  xs_unsignedInt m_maxTiersPerTariff;

  bool m_maxBoundariesPerTierIsSet;
  xs_unsignedInt m_maxBoundariesPerTier;

  bool m_maxIncentivesPerTierIsSet;
  xs_unsignedInt m_maxIncentivesPerTier;
};

//! typedef for non-const smart pointer type TariffOverallConstraintsData
using TariffOverallConstraintsDataPtr =
    std::shared_ptr<TariffOverallConstraintsData>;

//! typedef for const type TariffOverallConstraintsData
using TariffOverallConstraintsDataConst = const TariffOverallConstraintsData;

//! typedef for const type TariffOverallConstraintsData
using TariffOverallConstraintsDataConstPtr =
    std::shared_ptr<TariffOverallConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFOVERALLCONSTRAINTSDATA_H_