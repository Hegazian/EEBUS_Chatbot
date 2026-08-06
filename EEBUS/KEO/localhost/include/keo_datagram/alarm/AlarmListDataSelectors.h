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

#ifndef KEO_DATAGRAM_ALARM_ALARMLISTDATASELECTORS_H_
#define KEO_DATAGRAM_ALARM_ALARMLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/alarm/AlarmData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramAlarm
 * @{
 */

/**
 * Declaration AlarmListDataSelectors
 */
class AlarmListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  AlarmListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_alarmId the member to set
   * @param c_scopeType the member to set
   */
  AlarmListDataSelectors(const xs_unsignedInt &c_alarmId,
                         const ScopeType &c_scopeType);

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
  bool operator==(const AlarmListDataSelectors &c_classObject) const;

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
  bool operator!=(const AlarmListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member AlarmId.
   * @param c_alarmId Value to set
   */
  void setAlarmId(const xs_unsignedInt &c_alarmId);

  /**
   * Returns const reference to member AlarmId.
   * @return const reference to member alarmId
   */
  const xs_unsignedInt &getAlarmId() const;

  /**
   * Returns if member AlarmId is set.
   * @retval true member AlarmId is set
   * @retval false member AlarmId is not set
   */
  bool getAlarmIdIsSet() const;

  /**
   * Unsets member AlarmId
   */
  void cleanAlarmId();

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
  bool selects(const AlarmData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_alarmIdIsSet;
  xs_unsignedInt m_alarmId;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;
};

//! typedef for non-const smart pointer type AlarmListDataSelectors
using AlarmListDataSelectorsPtr = std::shared_ptr<AlarmListDataSelectors>;

//! typedef for const type AlarmListDataSelectors
using AlarmListDataSelectorsConst = const AlarmListDataSelectors;

//! typedef for const type AlarmListDataSelectors
using AlarmListDataSelectorsConstPtr =
    std::shared_ptr<AlarmListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ALARM_ALARMLISTDATASELECTORS_H_