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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlLimitDescriptionDataElements
 */
class LoadControlLimitDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlLimitDescriptionDataElements();

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
      const LoadControlLimitDescriptionDataElements &c_classObject) const;

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
      const LoadControlLimitDescriptionDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member LimitId.
   */
  void setLimitId();

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
   */
  void setLimitType();

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
   */
  void setLimitCategory();

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
   */
  void setLimitDirection();

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
   */
  void setMeasurementId();

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
   */
  void setUnit();

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
   */
  void setScopeType();

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
   */
  void setLabel();

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
   */
  void setDescription();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_limitIdIsSet;

  // ElementTag
  bool m_limitTypeIsSet;

  // ElementTag
  bool m_limitCategoryIsSet;

  // ElementTag
  bool m_limitDirectionIsSet;

  // ElementTag
  bool m_measurementIdIsSet;

  // ElementTag
  bool m_unitIsSet;

  // ElementTag
  bool m_scopeTypeIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type
//! LoadControlLimitDescriptionDataElements
using LoadControlLimitDescriptionDataElementsPtr =
    std::shared_ptr<LoadControlLimitDescriptionDataElements>;

//! typedef for const type LoadControlLimitDescriptionDataElements
using LoadControlLimitDescriptionDataElementsConst =
    const LoadControlLimitDescriptionDataElements;

//! typedef for const type LoadControlLimitDescriptionDataElements
using LoadControlLimitDescriptionDataElementsConstPtr =
    std::shared_ptr<LoadControlLimitDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITDESCRIPTIONDATAELEMENTS_H_