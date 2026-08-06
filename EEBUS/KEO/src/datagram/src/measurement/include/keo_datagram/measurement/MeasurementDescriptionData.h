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

#ifndef KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CommodityType.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/measurement/MeasurementDescriptionDataElements.h>
#include <keo_datagram/measurement/MeasurementType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramMeasurement
 * @{
 */

/**
 * Declaration MeasurementDescriptionData
 */
class MeasurementDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  MeasurementDescriptionData();

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
  bool operator==(const MeasurementDescriptionData &c_classObject) const;

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
  bool operator!=(const MeasurementDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member MeasurementType.
   * @param c_measurementType Value to set
   */
  void setMeasurementType(const MeasurementType &c_measurementType);

  /**
   * Returns const reference to member MeasurementType.
   * @return const reference to member measurementType
   */
  const MeasurementType &getMeasurementType() const;

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
   * @param c_commodityType Value to set
   */
  void setCommodityType(const CommodityType &c_commodityType);

  /**
   * Returns const reference to member CommodityType.
   * @return const reference to member commodityType
   */
  const CommodityType &getCommodityType() const;

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
   * Set member CalibrationValue.
   * @param c_calibrationValue Value to set
   */
  void setCalibrationValue(const ScaledNumber &c_calibrationValue);

  /**
   * Returns const reference to member CalibrationValue.
   * @return const reference to member calibrationValue
   */
  const ScaledNumber &getCalibrationValue() const;

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
  MeasurementDescriptionData
  reduce(const MeasurementDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_measurementTypeIsSet;
  MeasurementType m_measurementType;

  bool m_commodityTypeIsSet;
  CommodityType m_commodityType;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_calibrationValueIsSet;
  ScaledNumber m_calibrationValue;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type MeasurementDescriptionData
using MeasurementDescriptionDataPtr =
    std::shared_ptr<MeasurementDescriptionData>;

//! typedef for const type MeasurementDescriptionData
using MeasurementDescriptionDataConst = const MeasurementDescriptionData;

//! typedef for const type MeasurementDescriptionData
using MeasurementDescriptionDataConstPtr =
    std::shared_ptr<MeasurementDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_MEASUREMENT_MEASUREMENTDESCRIPTIONDATA_H_