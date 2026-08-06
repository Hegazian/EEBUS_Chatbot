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

#ifndef KEO_DATAGRAM_TIMESERIES_TIMESERIESDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMESERIES_TIMESERIESDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeSeries
 * @{
 */

/**
 * Declaration TimeSeriesDescriptionDataElements
 */
class TimeSeriesDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimeSeriesDescriptionDataElements();

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
  bool operator==(const TimeSeriesDescriptionDataElements &c_classObject) const;

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
  bool operator!=(const TimeSeriesDescriptionDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member TimeSeriesId.
   */
  void setTimeSeriesId();

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
   */
  void setTimeSeriesType();

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
   */
  void setTimeSeriesWriteable();

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
   */
  void setUpdateRequired();

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
   * Set member Currency.
   */
  void setCurrency();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timeSeriesIdIsSet;

  // ElementTag
  bool m_timeSeriesTypeIsSet;

  // ElementTag
  bool m_timeSeriesWriteableIsSet;

  // ElementTag
  bool m_updateRequiredIsSet;

  // ElementTag
  bool m_measurementIdIsSet;

  // ElementTag
  bool m_currencyIsSet;

  // ElementTag
  bool m_unitIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;

  // ElementTag
  bool m_scopeTypeIsSet;
};

//! typedef for non-const smart pointer type TimeSeriesDescriptionDataElements
using TimeSeriesDescriptionDataElementsPtr =
    std::shared_ptr<TimeSeriesDescriptionDataElements>;

//! typedef for const type TimeSeriesDescriptionDataElements
using TimeSeriesDescriptionDataElementsConst =
    const TimeSeriesDescriptionDataElements;

//! typedef for const type TimeSeriesDescriptionDataElements
using TimeSeriesDescriptionDataElementsConstPtr =
    std::shared_ptr<TimeSeriesDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMESERIES_TIMESERIESDESCRIPTIONDATAELEMENTS_H_