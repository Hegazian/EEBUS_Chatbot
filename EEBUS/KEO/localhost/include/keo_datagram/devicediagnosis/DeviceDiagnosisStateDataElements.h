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

#ifndef KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSTATEDATAELEMENTS_H_
#define KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSTATEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDeviceDiagnosis
 * @{
 */

/**
 * Declaration DeviceDiagnosisStateDataElements
 */
class DeviceDiagnosisStateDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  DeviceDiagnosisStateDataElements();

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
  bool operator==(const DeviceDiagnosisStateDataElements &c_classObject) const;

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
  bool operator!=(const DeviceDiagnosisStateDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member Timestamp.
   */
  void setTimestamp();

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
   */
  void setOperatingState();

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
   */
  void setVendorStateCode();

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
   */
  void setLastErrorCode();

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
   */
  void setUpTime();

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
   */
  void setTotalUpTime();

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
   */
  void setPowerSupplyCondition();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_operatingStateIsSet;

  // ElementTag
  bool m_vendorStateCodeIsSet;

  // ElementTag
  bool m_lastErrorCodeIsSet;

  // ElementTag
  bool m_upTimeIsSet;

  // ElementTag
  bool m_totalUpTimeIsSet;

  // ElementTag
  bool m_powerSupplyConditionIsSet;
};

//! typedef for non-const smart pointer type DeviceDiagnosisStateDataElements
using DeviceDiagnosisStateDataElementsPtr =
    std::shared_ptr<DeviceDiagnosisStateDataElements>;

//! typedef for const type DeviceDiagnosisStateDataElements
using DeviceDiagnosisStateDataElementsConst =
    const DeviceDiagnosisStateDataElements;

//! typedef for const type DeviceDiagnosisStateDataElements
using DeviceDiagnosisStateDataElementsConstPtr =
    std::shared_ptr<DeviceDiagnosisStateDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DEVICEDIAGNOSIS_DEVICEDIAGNOSISSTATEDATAELEMENTS_H_