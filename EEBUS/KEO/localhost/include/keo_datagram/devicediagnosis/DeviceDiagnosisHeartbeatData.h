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

#ifndef KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISHEARTBEATDATA_H_
#define KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISHEARTBEATDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceDiagnosis
 * @{
 */

/**
 * Declaration DeviceDiagnosisHeartbeatData
 */
class DeviceDiagnosisHeartbeatData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  DeviceDiagnosisHeartbeatData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_timestamp the member to set
   * @param c_heartbeatCounter the member to set
   * @param c_heartbeatTimeout the member to set
   */
  DeviceDiagnosisHeartbeatData(const AbsoluteOrRelativeTime &c_timestamp,
                               const xs_unsignedLong &c_heartbeatCounter,
                               const xs_duration &c_heartbeatTimeout);

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
  bool operator==(const DeviceDiagnosisHeartbeatData &c_classObject) const;

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
  bool operator!=(const DeviceDiagnosisHeartbeatData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member Timestamp.
   * @param c_timestamp Value to set
   */
  void setTimestamp(const AbsoluteOrRelativeTime &c_timestamp);

  /**
   * Returns const reference to member Timestamp.
   * @return const reference to member timestamp
   */
  const AbsoluteOrRelativeTime &getTimestamp() const;

  /**
   * Returns if member Timestamp is set.
   * @retval true member Timestamp is set
   * @retval false member Timestamp is not set
   */
  bool getTimestampIsSet() const;

  /**
   * Unsets member Timestamp
   */
  void cleanTimestamp();

  /**
   * Set member HeartbeatCounter.
   * @param c_heartbeatCounter Value to set
   */
  void setHeartbeatCounter(const xs_unsignedLong &c_heartbeatCounter);

  /**
   * Returns const reference to member HeartbeatCounter.
   * @return const reference to member heartbeatCounter
   */
  const xs_unsignedLong &getHeartbeatCounter() const;

  /**
   * Returns if member HeartbeatCounter is set.
   * @retval true member HeartbeatCounter is set
   * @retval false member HeartbeatCounter is not set
   */
  bool getHeartbeatCounterIsSet() const;

  /**
   * Unsets member HeartbeatCounter
   */
  void cleanHeartbeatCounter();

  /**
   * Set member HeartbeatTimeout.
   * @param c_heartbeatTimeout Value to set
   */
  void setHeartbeatTimeout(const xs_duration &c_heartbeatTimeout);

  /**
   * Returns const reference to member HeartbeatTimeout.
   * @return const reference to member heartbeatTimeout
   */
  const xs_duration &getHeartbeatTimeout() const;

  /**
   * Returns if member HeartbeatTimeout is set.
   * @retval true member HeartbeatTimeout is set
   * @retval false member HeartbeatTimeout is not set
   */
  bool getHeartbeatTimeoutIsSet() const;

  /**
   * Unsets member HeartbeatTimeout
   */
  void cleanHeartbeatTimeout();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_heartbeatCounterIsSet;
  xs_unsignedLong m_heartbeatCounter;

  bool m_heartbeatTimeoutIsSet;
  xs_duration m_heartbeatTimeout;
};

//! typedef for non-const smart pointer type DeviceDiagnosisHeartbeatData
using DeviceDiagnosisHeartbeatDataPtr =
    std::shared_ptr<DeviceDiagnosisHeartbeatData>;

//! typedef for const type DeviceDiagnosisHeartbeatData
using DeviceDiagnosisHeartbeatDataConst = const DeviceDiagnosisHeartbeatData;

//! typedef for const type DeviceDiagnosisHeartbeatData
using DeviceDiagnosisHeartbeatDataConstPtr =
    std::shared_ptr<DeviceDiagnosisHeartbeatDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISHEARTBEATDATA_H_