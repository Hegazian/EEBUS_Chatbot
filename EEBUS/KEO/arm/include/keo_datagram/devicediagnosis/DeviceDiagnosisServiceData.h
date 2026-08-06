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

#ifndef KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSERVICEDATA_H_
#define KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSERVICEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceDiagnosis
 * @{
 */

/**
 * Declaration DeviceDiagnosisServiceData
 */
class DeviceDiagnosisServiceData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  DeviceDiagnosisServiceData();

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
  bool operator==(const DeviceDiagnosisServiceData &c_classObject) const;

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
  bool operator!=(const DeviceDiagnosisServiceData &c_classObject) const;

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
   * Set member InstallationTime.
   * @param c_installationTime Value to set
   */
  void setInstallationTime(const AbsoluteOrRelativeTime &c_installationTime);

  /**
   * Returns const reference to member InstallationTime.
   * @return const reference to member installationTime
   */
  const AbsoluteOrRelativeTime &getInstallationTime() const;

  /**
   * Returns if member InstallationTime is set.
   * @retval true member InstallationTime is set
   * @retval false member InstallationTime is not set
   */
  bool getInstallationTimeIsSet() const;

  /**
   * Unsets member InstallationTime
   */
  void cleanInstallationTime();

  /**
   * Set member BootCounter.
   * @param c_bootCounter Value to set
   */
  void setBootCounter(const xs_unsignedLong &c_bootCounter);

  /**
   * Returns const reference to member BootCounter.
   * @return const reference to member bootCounter
   */
  const xs_unsignedLong &getBootCounter() const;

  /**
   * Returns if member BootCounter is set.
   * @retval true member BootCounter is set
   * @retval false member BootCounter is not set
   */
  bool getBootCounterIsSet() const;

  /**
   * Unsets member BootCounter
   */
  void cleanBootCounter();

  /**
   * Set member NextService.
   * @param c_nextService Value to set
   */
  void setNextService(const AbsoluteOrRelativeTime &c_nextService);

  /**
   * Returns const reference to member NextService.
   * @return const reference to member nextService
   */
  const AbsoluteOrRelativeTime &getNextService() const;

  /**
   * Returns if member NextService is set.
   * @retval true member NextService is set
   * @retval false member NextService is not set
   */
  bool getNextServiceIsSet() const;

  /**
   * Unsets member NextService
   */
  void cleanNextService();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_installationTimeIsSet;
  AbsoluteOrRelativeTime m_installationTime;

  bool m_bootCounterIsSet;
  xs_unsignedLong m_bootCounter;

  bool m_nextServiceIsSet;
  AbsoluteOrRelativeTime m_nextService;
};

//! typedef for non-const smart pointer type DeviceDiagnosisServiceData
using DeviceDiagnosisServiceDataPtr =
    std::shared_ptr<DeviceDiagnosisServiceData>;

//! typedef for const type DeviceDiagnosisServiceData
using DeviceDiagnosisServiceDataConst = const DeviceDiagnosisServiceData;

//! typedef for const type DeviceDiagnosisServiceData
using DeviceDiagnosisServiceDataConstPtr =
    std::shared_ptr<DeviceDiagnosisServiceDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSERVICEDATA_H_