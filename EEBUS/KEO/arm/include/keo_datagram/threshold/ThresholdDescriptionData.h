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

#ifndef KEO_DATAGRAM_THRESHOLD_THRESHOLDDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_THRESHOLD_THRESHOLDDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/threshold/ThresholdDescriptionDataElements.h>
#include <keo_datagram/threshold/ThresholdType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramThreshold
 * @{
 */

/**
 * Declaration ThresholdDescriptionData
 */
class ThresholdDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  ThresholdDescriptionData();

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
  bool operator==(const ThresholdDescriptionData &c_classObject) const;

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
  bool operator!=(const ThresholdDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member ThresholdType.
   * @param c_thresholdType Value to set
   */
  void setThresholdType(const ThresholdType &c_thresholdType);

  /**
   * Returns const reference to member ThresholdType.
   * @return const reference to member thresholdType
   */
  const ThresholdType &getThresholdType() const;

  /**
   * Returns if member ThresholdType is set.
   * @retval true member ThresholdType is set
   * @retval false member ThresholdType is not set
   */
  bool getThresholdTypeIsSet() const;

  /**
   * Unsets member ThresholdType
   */
  void cleanThresholdType();

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
  ThresholdDescriptionData
  reduce(const ThresholdDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_thresholdIdIsSet;
  xs_unsignedInt m_thresholdId;

  bool m_thresholdTypeIsSet;
  ThresholdType m_thresholdType;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type ThresholdDescriptionData
using ThresholdDescriptionDataPtr = std::shared_ptr<ThresholdDescriptionData>;

//! typedef for const type ThresholdDescriptionData
using ThresholdDescriptionDataConst = const ThresholdDescriptionData;

//! typedef for const type ThresholdDescriptionData
using ThresholdDescriptionDataConstPtr =
    std::shared_ptr<ThresholdDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_THRESHOLD_THRESHOLDDESCRIPTIONDATA_H_