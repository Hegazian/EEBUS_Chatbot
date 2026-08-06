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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/EnergyDirection.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/loadcontrol/LoadControlLimitType.h>

#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlLimitDescriptionListDataSelectors
 */
class LoadControlLimitDescriptionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlLimitDescriptionListDataSelectors();

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
  bool operator==(
      const LoadControlLimitDescriptionListDataSelectors &c_classObject) const;

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
  bool operator!=(
      const LoadControlLimitDescriptionListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member LimitId.
   * @param c_limitId Value to set
   */
  void setLimitId(const xs_unsignedInt &c_limitId);

  /**
   * Returns const reference to member LimitId.
   * @return const reference to member limitId
   */
  const xs_unsignedInt &getLimitId() const;

  /**
   * Returns if member LimitId is set.
   * @retval true member LimitId is set
   * @retval false member LimitId is not set
   */
  bool getLimitIdIsSet() const;

  /**
   * Unsets member LimitId
   */
  void cleanLimitId();

  /**
   * Set member LimitType.
   * @param c_limitType Value to set
   */
  void setLimitType(const LoadControlLimitType &c_limitType);

  /**
   * Returns const reference to member LimitType.
   * @return const reference to member limitType
   */
  const LoadControlLimitType &getLimitType() const;

  /**
   * Returns if member LimitType is set.
   * @retval true member LimitType is set
   * @retval false member LimitType is not set
   */
  bool getLimitTypeIsSet() const;

  /**
   * Unsets member LimitType
   */
  void cleanLimitType();

  /**
   * Set member LimitDirection.
   * @param c_limitDirection Value to set
   */
  void setLimitDirection(const EnergyDirection &c_limitDirection);

  /**
   * Returns const reference to member LimitDirection.
   * @return const reference to member limitDirection
   */
  const EnergyDirection &getLimitDirection() const;

  /**
   * Returns if member LimitDirection is set.
   * @retval true member LimitDirection is set
   * @retval false member LimitDirection is not set
   */
  bool getLimitDirectionIsSet() const;

  /**
   * Unsets member LimitDirection
   */
  void cleanLimitDirection();

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
  bool selects(const LoadControlLimitDescriptionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_limitIdIsSet;
  xs_unsignedInt m_limitId;

  bool m_limitTypeIsSet;
  LoadControlLimitType m_limitType;

  bool m_limitDirectionIsSet;
  EnergyDirection m_limitDirection;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;
};

//! typedef for non-const smart pointer type
//! LoadControlLimitDescriptionListDataSelectors
using LoadControlLimitDescriptionListDataSelectorsPtr =
    std::shared_ptr<LoadControlLimitDescriptionListDataSelectors>;

//! typedef for const type LoadControlLimitDescriptionListDataSelectors
using LoadControlLimitDescriptionListDataSelectorsConst =
    const LoadControlLimitDescriptionListDataSelectors;

//! typedef for const type LoadControlLimitDescriptionListDataSelectors
using LoadControlLimitDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<LoadControlLimitDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONLISTDATASELECTORS_H_