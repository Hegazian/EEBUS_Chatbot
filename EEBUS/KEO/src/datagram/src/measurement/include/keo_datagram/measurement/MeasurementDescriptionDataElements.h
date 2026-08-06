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

#ifndef KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramMeasurement
 * @{
 */

/**
 * Declaration MeasurementDescriptionDataElements
 */
class MeasurementDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  MeasurementDescriptionDataElements();

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
  operator==(const MeasurementDescriptionDataElements &c_classObject) const;

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
  operator!=(const MeasurementDescriptionDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

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
   * Set member MeasurementType.
   */
  void setMeasurementType();

  /**
   * Returns if member MeasurementType is set.
   * @retval true member MeasurementType is set
   * @retval false member MeasurementType is not set
   */
  bool getMeasurementTypeIsSet() const;

  /**
   * Unsets member MeasurementType
   */
  void cleanMeasurementType();

  /**
   * Set member CommodityType.
   */
  void setCommodityType();

  /**
   * Returns if member CommodityType is set.
   * @retval true member CommodityType is set
   * @retval false member CommodityType is not set
   */
  bool getCommodityTypeIsSet() const;

  /**
   * Unsets member CommodityType
   */
  void cleanCommodityType();

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
   * Set member CalibrationValue.
   * @param c_calibrationValue Value to set
   */
  void setCalibrationValue(const ScaledNumberElements &c_calibrationValue);

  /**
   * Returns const reference to member CalibrationValue.
   * @return const reference to member calibrationValue
   */
  const ScaledNumberElements &getCalibrationValue() const;

  /**
   * Returns if member CalibrationValue is set.
   * @retval true member CalibrationValue is set
   * @retval false member CalibrationValue is not set
   */
  bool getCalibrationValueIsSet() const;

  /**
   * Unsets member CalibrationValue
   */
  void cleanCalibrationValue();

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
  bool m_measurementIdIsSet;

  // ElementTag
  bool m_measurementTypeIsSet;

  // ElementTag
  bool m_commodityTypeIsSet;

  // ElementTag
  bool m_unitIsSet;

  bool m_calibrationValueIsSet;
  ScaledNumberElements m_calibrationValue;

  // ElementTag
  bool m_scopeTypeIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type MeasurementDescriptionDataElements
using MeasurementDescriptionDataElementsPtr =
    std::shared_ptr<MeasurementDescriptionDataElements>;

//! typedef for const type MeasurementDescriptionDataElements
using MeasurementDescriptionDataElementsConst =
    const MeasurementDescriptionDataElements;

//! typedef for const type MeasurementDescriptionDataElements
using MeasurementDescriptionDataElementsConstPtr =
    std::shared_ptr<MeasurementDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDESCRIPTIONDATAELEMENTS_H_