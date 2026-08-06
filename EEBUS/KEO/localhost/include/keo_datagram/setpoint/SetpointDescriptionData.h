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

#ifndef KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/setpoint/SetpointDescriptionDataElements.h>
#include <keo_datagram/setpoint/SetpointType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSetpoint
 * @{
 */

/**
 * Declaration SetpointDescriptionData
 */
class SetpointDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SetpointDescriptionData();

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
  bool operator==(const SetpointDescriptionData &c_classObject) const;

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
  bool operator!=(const SetpointDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member SetpointId.
   * @param c_setpointId Value to set
   */
  void setSetpointId(const xs_unsignedInt &c_setpointId);

  /**
   * Returns const reference to member SetpointId.
   * @return const reference to member setpointId
   */
  const xs_unsignedInt &getSetpointId() const;

  /**
   * Returns if member SetpointId is set.
   * @retval true member SetpointId is set
   * @retval false member SetpointId is not set
   */
  bool getSetpointIdIsSet() const;

  /**
   * Unsets member SetpointId
   */
  void cleanSetpointId();

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
   * Set member TimeTableId.
   * @param c_timeTableId Value to set
   */
  void setTimeTableId(const xs_unsignedInt &c_timeTableId);

  /**
   * Returns const reference to member TimeTableId.
   * @return const reference to member timeTableId
   */
  const xs_unsignedInt &getTimeTableId() const;

  /**
   * Returns if member TimeTableId is set.
   * @retval true member TimeTableId is set
   * @retval false member TimeTableId is not set
   */
  bool getTimeTableIdIsSet() const;

  /**
   * Unsets member TimeTableId
   */
  void cleanTimeTableId();

  /**
   * Set member SetpointType.
   * @param c_setpointType Value to set
   */
  void setSetpointType(const SetpointType &c_setpointType);

  /**
   * Returns const reference to member SetpointType.
   * @return const reference to member setpointType
   */
  const SetpointType &getSetpointType() const;

  /**
   * Returns if member SetpointType is set.
   * @retval true member SetpointType is set
   * @retval false member SetpointType is not set
   */
  bool getSetpointTypeIsSet() const;

  /**
   * Unsets member SetpointType
   */
  void cleanSetpointType();

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
  SetpointDescriptionData
  reduce(const SetpointDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_setpointIdIsSet;
  xs_unsignedInt m_setpointId;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_timeTableIdIsSet;
  xs_unsignedInt m_timeTableId;

  bool m_setpointTypeIsSet;
  SetpointType m_setpointType;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type SetpointDescriptionData
using SetpointDescriptionDataPtr = std::shared_ptr<SetpointDescriptionData>;

//! typedef for const type SetpointDescriptionData
using SetpointDescriptionDataConst = const SetpointDescriptionData;

//! typedef for const type SetpointDescriptionData
using SetpointDescriptionDataConstPtr =
    std::shared_ptr<SetpointDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONDATA_H_