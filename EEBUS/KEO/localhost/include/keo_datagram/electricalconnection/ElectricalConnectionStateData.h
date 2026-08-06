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

#ifndef KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONSTATEDATA_H_
#define KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONSTATEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/EnergyMode.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionStateDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramElectricalConnection
 * @{
 */

/**
 * Declaration ElectricalConnectionStateData
 */
class ElectricalConnectionStateData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  ElectricalConnectionStateData();

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
  bool operator==(const ElectricalConnectionStateData &c_classObject) const;

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
  bool operator!=(const ElectricalConnectionStateData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member ElectricalConnectionId.
   * @param c_electricalConnectionId Value to set
   */
  void
  setElectricalConnectionId(const xs_unsignedInt &c_electricalConnectionId);

  /**
   * Returns const reference to member ElectricalConnectionId.
   * @return const reference to member electricalConnectionId
   */
  const xs_unsignedInt &getElectricalConnectionId() const;

  /**
   * Returns if member ElectricalConnectionId is set.
   * @retval true member ElectricalConnectionId is set
   * @retval false member ElectricalConnectionId is not set
   */
  bool getElectricalConnectionIdIsSet() const;

  /**
   * Unsets member ElectricalConnectionId
   */
  void cleanElectricalConnectionId();

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
   * Set member CurrentEnergyMode.
   * @param c_currentEnergyMode Value to set
   */
  void setCurrentEnergyMode(const EnergyMode &c_currentEnergyMode);

  /**
   * Returns const reference to member CurrentEnergyMode.
   * @return const reference to member currentEnergyMode
   */
  const EnergyMode &getCurrentEnergyMode() const;

  /**
   * Returns if member CurrentEnergyMode is set.
   * @retval true member CurrentEnergyMode is set
   * @retval false member CurrentEnergyMode is not set
   */
  bool getCurrentEnergyModeIsSet() const;

  /**
   * Unsets member CurrentEnergyMode
   */
  void cleanCurrentEnergyMode();

  /**
   * Set member ConsumptionTime.
   * @param c_consumptionTime Value to set
   */
  void setConsumptionTime(const xs_duration &c_consumptionTime);

  /**
   * Returns const reference to member ConsumptionTime.
   * @return const reference to member consumptionTime
   */
  const xs_duration &getConsumptionTime() const;

  /**
   * Returns if member ConsumptionTime is set.
   * @retval true member ConsumptionTime is set
   * @retval false member ConsumptionTime is not set
   */
  bool getConsumptionTimeIsSet() const;

  /**
   * Unsets member ConsumptionTime
   */
  void cleanConsumptionTime();

  /**
   * Set member ProductionTime.
   * @param c_productionTime Value to set
   */
  void setProductionTime(const xs_duration &c_productionTime);

  /**
   * Returns const reference to member ProductionTime.
   * @return const reference to member productionTime
   */
  const xs_duration &getProductionTime() const;

  /**
   * Returns if member ProductionTime is set.
   * @retval true member ProductionTime is set
   * @retval false member ProductionTime is not set
   */
  bool getProductionTimeIsSet() const;

  /**
   * Unsets member ProductionTime
   */
  void cleanProductionTime();

  /**
   * Set member TotalConsumptionTime.
   * @param c_totalConsumptionTime Value to set
   */
  void setTotalConsumptionTime(const xs_duration &c_totalConsumptionTime);

  /**
   * Returns const reference to member TotalConsumptionTime.
   * @return const reference to member totalConsumptionTime
   */
  const xs_duration &getTotalConsumptionTime() const;

  /**
   * Returns if member TotalConsumptionTime is set.
   * @retval true member TotalConsumptionTime is set
   * @retval false member TotalConsumptionTime is not set
   */
  bool getTotalConsumptionTimeIsSet() const;

  /**
   * Unsets member TotalConsumptionTime
   */
  void cleanTotalConsumptionTime();

  /**
   * Set member TotalProductionTime.
   * @param c_totalProductionTime Value to set
   */
  void setTotalProductionTime(const xs_duration &c_totalProductionTime);

  /**
   * Returns const reference to member TotalProductionTime.
   * @return const reference to member totalProductionTime
   */
  const xs_duration &getTotalProductionTime() const;

  /**
   * Returns if member TotalProductionTime is set.
   * @retval true member TotalProductionTime is set
   * @retval false member TotalProductionTime is not set
   */
  bool getTotalProductionTimeIsSet() const;

  /**
   * Unsets member TotalProductionTime
   */
  void cleanTotalProductionTime();

  /**
   * @copydoc CmdData::reduce()
   */
  ElectricalConnectionStateData
  reduce(const ElectricalConnectionStateDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_electricalConnectionIdIsSet;
  xs_unsignedInt m_electricalConnectionId;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_currentEnergyModeIsSet;
  EnergyMode m_currentEnergyMode;

  bool m_consumptionTimeIsSet;
  xs_duration m_consumptionTime;

  bool m_productionTimeIsSet;
  xs_duration m_productionTime;

  bool m_totalConsumptionTimeIsSet;
  xs_duration m_totalConsumptionTime;

  bool m_totalProductionTimeIsSet;
  xs_duration m_totalProductionTime;
};

//! typedef for non-const smart pointer type ElectricalConnectionStateData
using ElectricalConnectionStateDataPtr =
    std::shared_ptr<ElectricalConnectionStateData>;

//! typedef for const type ElectricalConnectionStateData
using ElectricalConnectionStateDataConst = const ElectricalConnectionStateData;

//! typedef for const type ElectricalConnectionStateData
using ElectricalConnectionStateDataConstPtr =
    std::shared_ptr<ElectricalConnectionStateDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONSTATEDATA_H_