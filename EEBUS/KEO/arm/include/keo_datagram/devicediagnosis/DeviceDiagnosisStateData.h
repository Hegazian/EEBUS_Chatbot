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

#ifndef KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSTATEDATA_H_
#define KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSTATEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/devicediagnosis/DeviceDiagnosisOperatingState.h>
#include <keo_datagram/devicediagnosis/PowerSupplyCondition.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceDiagnosis
 * @{
 */

/**
 * Declaration DeviceDiagnosisStateData
 */
class DeviceDiagnosisStateData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  DeviceDiagnosisStateData();

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
  bool operator==(const DeviceDiagnosisStateData &c_classObject) const;

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
  bool operator!=(const DeviceDiagnosisStateData &c_classObject) const;

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
   * Set member OperatingState.
   * @param c_operatingState Value to set
   */
  void setOperatingState(const DeviceDiagnosisOperatingState &c_operatingState);

  /**
   * Returns const reference to member OperatingState.
   * @return const reference to member operatingState
   */
  const DeviceDiagnosisOperatingState &getOperatingState() const;

  /**
   * Returns if member OperatingState is set.
   * @retval true member OperatingState is set
   * @retval false member OperatingState is not set
   */
  bool getOperatingStateIsSet() const;

  /**
   * Unsets member OperatingState
   */
  void cleanOperatingState();

  /**
   * Set member VendorStateCode.
   * @param c_vendorStateCode Value to set
   */
  void setVendorStateCode(const xs_string &c_vendorStateCode);

  /**
   * Returns const reference to member VendorStateCode.
   * @return const reference to member vendorStateCode
   */
  const xs_string &getVendorStateCode() const;

  /**
   * Returns if member VendorStateCode is set.
   * @retval true member VendorStateCode is set
   * @retval false member VendorStateCode is not set
   */
  bool getVendorStateCodeIsSet() const;

  /**
   * Unsets member VendorStateCode
   */
  void cleanVendorStateCode();

  /**
   * Set member LastErrorCode.
   * @param c_lastErrorCode Value to set
   */
  void setLastErrorCode(const xs_string &c_lastErrorCode);

  /**
   * Returns const reference to member LastErrorCode.
   * @return const reference to member lastErrorCode
   */
  const xs_string &getLastErrorCode() const;

  /**
   * Returns if member LastErrorCode is set.
   * @retval true member LastErrorCode is set
   * @retval false member LastErrorCode is not set
   */
  bool getLastErrorCodeIsSet() const;

  /**
   * Unsets member LastErrorCode
   */
  void cleanLastErrorCode();

  /**
   * Set member UpTime.
   * @param c_upTime Value to set
   */
  void setUpTime(const xs_duration &c_upTime);

  /**
   * Returns const reference to member UpTime.
   * @return const reference to member upTime
   */
  const xs_duration &getUpTime() const;

  /**
   * Returns if member UpTime is set.
   * @retval true member UpTime is set
   * @retval false member UpTime is not set
   */
  bool getUpTimeIsSet() const;

  /**
   * Unsets member UpTime
   */
  void cleanUpTime();

  /**
   * Set member TotalUpTime.
   * @param c_totalUpTime Value to set
   */
  void setTotalUpTime(const xs_duration &c_totalUpTime);

  /**
   * Returns const reference to member TotalUpTime.
   * @return const reference to member totalUpTime
   */
  const xs_duration &getTotalUpTime() const;

  /**
   * Returns if member TotalUpTime is set.
   * @retval true member TotalUpTime is set
   * @retval false member TotalUpTime is not set
   */
  bool getTotalUpTimeIsSet() const;

  /**
   * Unsets member TotalUpTime
   */
  void cleanTotalUpTime();

  /**
   * Set member PowerSupplyCondition.
   * @param c_powerSupplyCondition Value to set
   */
  void
  setPowerSupplyCondition(const PowerSupplyCondition &c_powerSupplyCondition);

  /**
   * Returns const reference to member PowerSupplyCondition.
   * @return const reference to member powerSupplyCondition
   */
  const PowerSupplyCondition &getPowerSupplyCondition() const;

  /**
   * Returns if member PowerSupplyCondition is set.
   * @retval true member PowerSupplyCondition is set
   * @retval false member PowerSupplyCondition is not set
   */
  bool getPowerSupplyConditionIsSet() const;

  /**
   * Unsets member PowerSupplyCondition
   */
  void cleanPowerSupplyCondition();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_operatingStateIsSet;
  DeviceDiagnosisOperatingState m_operatingState;

  bool m_vendorStateCodeIsSet;
  xs_string m_vendorStateCode;

  bool m_lastErrorCodeIsSet;
  xs_string m_lastErrorCode;

  bool m_upTimeIsSet;
  xs_duration m_upTime;

  bool m_totalUpTimeIsSet;
  xs_duration m_totalUpTime;

  bool m_powerSupplyConditionIsSet;
  PowerSupplyCondition m_powerSupplyCondition;
};

//! typedef for non-const smart pointer type DeviceDiagnosisStateData
using DeviceDiagnosisStateDataPtr = std::shared_ptr<DeviceDiagnosisStateData>;

//! typedef for const type DeviceDiagnosisStateData
using DeviceDiagnosisStateDataConst = const DeviceDiagnosisStateData;

//! typedef for const type DeviceDiagnosisStateData
using DeviceDiagnosisStateDataConstPtr =
    std::shared_ptr<DeviceDiagnosisStateDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSTATEDATA_H_