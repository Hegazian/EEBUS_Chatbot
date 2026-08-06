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

#ifndef KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/setpoint/SetpointType.h>

#include <keo_datagram/setpoint/SetpointDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSetpoint
 * @{
 */

/**
 * Declaration SetpointDescriptionListDataSelectors
 */
class SetpointDescriptionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  SetpointDescriptionListDataSelectors();

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
  operator==(const SetpointDescriptionListDataSelectors &c_classObject) const;

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
  operator!=(const SetpointDescriptionListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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
  bool selects(const SetpointDescriptionData &data) const;

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

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;
};

//! typedef for non-const smart pointer type
//! SetpointDescriptionListDataSelectors
using SetpointDescriptionListDataSelectorsPtr =
    std::shared_ptr<SetpointDescriptionListDataSelectors>;

//! typedef for const type SetpointDescriptionListDataSelectors
using SetpointDescriptionListDataSelectorsConst =
    const SetpointDescriptionListDataSelectors;

//! typedef for const type SetpointDescriptionListDataSelectors
using SetpointDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<SetpointDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SETPOINT_SETPOINTDESCRIPTIONLISTDATASELECTORS_H_