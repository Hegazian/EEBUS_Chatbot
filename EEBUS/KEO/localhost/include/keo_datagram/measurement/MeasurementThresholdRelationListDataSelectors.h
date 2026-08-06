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

#ifndef KEO_DATAGRAM_MEASUREMENT_MEASUREMENTTHRESHOLDRELATIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_MEASUREMENT_MEASUREMENTTHRESHOLDRELATIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/measurement/MeasurementThresholdRelationData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramMeasurement
 * @{
 */

/**
 * Declaration MeasurementThresholdRelationListDataSelectors
 */
class MeasurementThresholdRelationListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  MeasurementThresholdRelationListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_measurementId the member to set
   * @param c_thresholdId the member to set
   */
  MeasurementThresholdRelationListDataSelectors(
      const xs_unsignedInt &c_measurementId,
      const xs_unsignedInt &c_thresholdId);

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
      const MeasurementThresholdRelationListDataSelectors &c_classObject) const;

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
      const MeasurementThresholdRelationListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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
   * Set member ThresholdId.
   * @param c_thresholdId Value to set
   */
  void setThresholdId(const xs_unsignedInt &c_thresholdId);

  /**
   * Returns const reference to member ThresholdId.
   * @return const reference to member thresholdId
   */
  const xs_unsignedInt &getThresholdId() const;

  /**
   * Returns if member ThresholdId is set.
   * @retval true member ThresholdId is set
   * @retval false member ThresholdId is not set
   */
  bool getThresholdIdIsSet() const;

  /**
   * Unsets member ThresholdId
   */
  void cleanThresholdId();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const MeasurementThresholdRelationData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_thresholdIdIsSet;
  xs_unsignedInt m_thresholdId;
};

//! typedef for non-const smart pointer type
//! MeasurementThresholdRelationListDataSelectors
using MeasurementThresholdRelationListDataSelectorsPtr =
    std::shared_ptr<MeasurementThresholdRelationListDataSelectors>;

//! typedef for const type MeasurementThresholdRelationListDataSelectors
using MeasurementThresholdRelationListDataSelectorsConst =
    const MeasurementThresholdRelationListDataSelectors;

//! typedef for const type MeasurementThresholdRelationListDataSelectors
using MeasurementThresholdRelationListDataSelectorsConstPtr =
    std::shared_ptr<MeasurementThresholdRelationListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_MEASUREMENT_MEASUREMENTTHRESHOLDRELATIONLISTDATASELECTORS_H_