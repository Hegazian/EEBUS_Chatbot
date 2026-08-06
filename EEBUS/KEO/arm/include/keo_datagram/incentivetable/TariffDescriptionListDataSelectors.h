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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/incentivetable/TariffDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffDescriptionListDataSelectors
 */
class TariffDescriptionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TariffDescriptionListDataSelectors();

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
  operator==(const TariffDescriptionListDataSelectors &c_classObject) const;

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
  operator!=(const TariffDescriptionListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member TariffId.
   * @param c_tariffId Value to set
   */
  void setTariffId(const xs_unsignedInt &c_tariffId);

  /**
   * Returns const reference to member TariffId.
   * @return const reference to member tariffId
   */
  const xs_unsignedInt &getTariffId() const;

  /**
   * Returns if member TariffId is set.
   * @retval true member TariffId is set
   * @retval false member TariffId is not set
   */
  bool getTariffIdIsSet() const;

  /**
   * Unsets member TariffId
   */
  void cleanTariffId();

  /**
   * Set member CommodityId.
   * @param c_commodityId Value to set
   */
  void setCommodityId(const xs_unsignedInt &c_commodityId);

  /**
   * Returns const reference to member CommodityId.
   * @return const reference to member commodityId
   */
  const xs_unsignedInt &getCommodityId() const;

  /**
   * Returns if member CommodityId is set.
   * @retval true member CommodityId is set
   * @retval false member CommodityId is not set
   */
  bool getCommodityIdIsSet() const;

  /**
   * Unsets member CommodityId
   */
  void cleanCommodityId();

  /**
   * Set member MeasurementId.
   * @param c_measurementId Value to set
   */
  void setMeasurementId(const xs_unsignedInt &c_measurementId);

  /**
   * Returns const reference to member MeasurementId.
   * @return const reference to member measurementId
   */
  const xs_unsignedInt &getMeasurementId() const;

  /**
   * Returns if member MeasurementId is set.
   * @retval true member MeasurementId is set
   * @retval false member MeasurementId is not set
   */
  bool getMeasurementIdIsSet() const;

  /**
   * Unsets member MeasurementId
   */
  void cleanMeasurementId();

  /**
   * Set member ScopeType.
   * @param c_scopeType Value to set
   */
  void setScopeType(const ScopeType &c_scopeType);

  /**
   * Returns const reference to member ScopeType.
   * @return const reference to member scopeType
   */
  const ScopeType &getScopeType() const;

  /**
   * Returns if member ScopeType is set.
   * @retval true member ScopeType is set
   * @retval false member ScopeType is not set
   */
  bool getScopeTypeIsSet() const;

  /**
   * Unsets member ScopeType
   */
  void cleanScopeType();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const TariffDescriptionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffIdIsSet;
  xs_unsignedInt m_tariffId;

  bool m_commodityIdIsSet;
  xs_unsignedInt m_commodityId;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;
};

//! typedef for non-const smart pointer type TariffDescriptionListDataSelectors
using TariffDescriptionListDataSelectorsPtr =
    std::shared_ptr<TariffDescriptionListDataSelectors>;

//! typedef for const type TariffDescriptionListDataSelectors
using TariffDescriptionListDataSelectorsConst =
    const TariffDescriptionListDataSelectors;

//! typedef for const type TariffDescriptionListDataSelectors
using TariffDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<TariffDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFDESCRIPTIONLISTDATASELECTORS_H_