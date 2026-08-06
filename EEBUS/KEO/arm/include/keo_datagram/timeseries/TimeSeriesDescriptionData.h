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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/Currency.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/timeseries/TimeSeriesType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesDescriptionData
 */
class TimeSeriesDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesDescriptionData();

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
  bool operator==(const TimeSeriesDescriptionData &c_classObject) const;

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
  bool operator!=(const TimeSeriesDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member TimeSeriesId.
   * @param c_timeSeriesId Value to set
   */
  void setTimeSeriesId(const xs_unsignedInt &c_timeSeriesId);

  /**
   * Returns const reference to member TimeSeriesId.
   * @return const reference to member timeSeriesId
   */
  const xs_unsignedInt &getTimeSeriesId() const;

  /**
   * Returns if member TimeSeriesId is set.
   * @retval true member TimeSeriesId is set
   * @retval false member TimeSeriesId is not set
   */
  bool getTimeSeriesIdIsSet() const;

  /**
   * Unsets member TimeSeriesId
   */
  void cleanTimeSeriesId();

  /**
   * Set member TimeSeriesType.
   * @param c_timeSeriesType Value to set
   */
  void setTimeSeriesType(const TimeSeriesType &c_timeSeriesType);

  /**
   * Returns const reference to member TimeSeriesType.
   * @return const reference to member timeSeriesType
   */
  const TimeSeriesType &getTimeSeriesType() const;

  /**
   * Returns if member TimeSeriesType is set.
   * @retval true member TimeSeriesType is set
   * @retval false member TimeSeriesType is not set
   */
  bool getTimeSeriesTypeIsSet() const;

  /**
   * Unsets member TimeSeriesType
   */
  void cleanTimeSeriesType();

  /**
   * Set member TimeSeriesWriteable.
   * @param c_timeSeriesWriteable Value to set
   */
  void setTimeSeriesWriteable(const xs_boolean &c_timeSeriesWriteable);

  /**
   * Returns const reference to member TimeSeriesWriteable.
   * @return const reference to member timeSeriesWriteable
   */
  const xs_boolean &getTimeSeriesWriteable() const;

  /**
   * Returns if member TimeSeriesWriteable is set.
   * @retval true member TimeSeriesWriteable is set
   * @retval false member TimeSeriesWriteable is not set
   */
  bool getTimeSeriesWriteableIsSet() const;

  /**
   * Unsets member TimeSeriesWriteable
   */
  void cleanTimeSeriesWriteable();

  /**
   * Set member UpdateRequired.
   * @param c_updateRequired Value to set
   */
  void setUpdateRequired(const xs_boolean &c_updateRequired);

  /**
   * Returns const reference to member UpdateRequired.
   * @return const reference to member updateRequired
   */
  const xs_boolean &getUpdateRequired() const;

  /**
   * Returns if member UpdateRequired is set.
   * @retval true member UpdateRequired is set
   * @retval false member UpdateRequired is not set
   */
  bool getUpdateRequiredIsSet() const;

  /**
   * Unsets member UpdateRequired
   */
  void cleanUpdateRequired();

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
   * Set member Currency.
   * @param c_currency Value to set
   */
  void setCurrency(const Currency &c_currency);

  /**
   * Returns const reference to member Currency.
   * @return const reference to member currency
   */
  const Currency &getCurrency() const;

  /**
   * Returns if member Currency is set.
   * @retval true member Currency is set
   * @retval false member Currency is not set
   */
  bool getCurrencyIsSet() const;

  /**
   * Unsets member Currency
   */
  void cleanCurrency();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timeSeriesIdIsSet;
  xs_unsignedInt m_timeSeriesId;

  bool m_timeSeriesTypeIsSet;
  TimeSeriesType m_timeSeriesType;

  bool m_timeSeriesWriteableIsSet;
  xs_boolean m_timeSeriesWriteable;

  bool m_updateRequiredIsSet;
  xs_boolean m_updateRequired;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_currencyIsSet;
  Currency m_currency;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;
};

//! typedef for non-const smart pointer type TimeSeriesDescriptionData
using TimeSeriesDescriptionDataPtr = std::shared_ptr<TimeSeriesDescriptionData>;

//! typedef for const type TimeSeriesDescriptionData
using TimeSeriesDescriptionDataConst = const TimeSeriesDescriptionData;

//! typedef for const type TimeSeriesDescriptionData
using TimeSeriesDescriptionDataConstPtr =
    std::shared_ptr<TimeSeriesDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESDESCRIPTIONDATA_H_