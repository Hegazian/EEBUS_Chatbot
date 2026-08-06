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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/EnergyDirection.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/loadcontrol/LoadControlCategory.h>
#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionDataElements.h>
#include <keo_datagram/loadcontrol/LoadControlLimitType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlLimitDescriptionData
 */
class LoadControlLimitDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlLimitDescriptionData();

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
  bool operator==(const LoadControlLimitDescriptionData &c_classObject) const;

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
  bool operator!=(const LoadControlLimitDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member LimitCategory.
   * @param c_limitCategory Value to set
   */
  void setLimitCategory(const LoadControlCategory &c_limitCategory);

  /**
   * Returns const reference to member LimitCategory.
   * @return const reference to member limitCategory
   */
  const LoadControlCategory &getLimitCategory() const;

  /**
   * Returns if member LimitCategory is set.
   * @retval true member LimitCategory is set
   * @retval false member LimitCategory is not set
   */
  bool getLimitCategoryIsSet() const;

  /**
   * Unsets member LimitCategory
   */
  void cleanLimitCategory();

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
   * Set member Unit.
   * @param c_unit Value to set
   */
  void setUnit(const UnitOfMeasurement &c_unit);

  /**
   * Returns const reference to member Unit.
   * @return const reference to member unit
   */
  const UnitOfMeasurement &getUnit() const;

  /**
   * Returns if member Unit is set.
   * @retval true member Unit is set
   * @retval false member Unit is not set
   */
  bool getUnitIsSet() const;

  /**
   * Unsets member Unit
   */
  void cleanUnit();

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
   * Set member Label.
   * @param c_label Value to set
   */
  void setLabel(const xs_string &c_label);

  /**
   * Returns const reference to member Label.
   * @return const reference to member label
   */
  const xs_string &getLabel() const;

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

  /**
   * @copydoc CmdData::reduce()
   */
  LoadControlLimitDescriptionData
  reduce(const LoadControlLimitDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_limitIdIsSet;
  xs_unsignedInt m_limitId;

  bool m_limitTypeIsSet;
  LoadControlLimitType m_limitType;

  bool m_limitCategoryIsSet;
  LoadControlCategory m_limitCategory;

  bool m_limitDirectionIsSet;
  EnergyDirection m_limitDirection;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type LoadControlLimitDescriptionData
using LoadControlLimitDescriptionDataPtr =
    std::shared_ptr<LoadControlLimitDescriptionData>;

//! typedef for const type LoadControlLimitDescriptionData
using LoadControlLimitDescriptionDataConst =
    const LoadControlLimitDescriptionData;

//! typedef for const type LoadControlLimitDescriptionData
using LoadControlLimitDescriptionDataConstPtr =
    std::shared_ptr<LoadControlLimitDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONDATA_H_