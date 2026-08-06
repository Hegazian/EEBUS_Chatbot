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

#ifndef KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONSTATEDATAELEMENTS_H_
#define KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONSTATEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramElectricalConnection
 * @{
 */

/**
 * Declaration ElectricalConnectionStateDataElements
 */
class ElectricalConnectionStateDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  ElectricalConnectionStateDataElements();

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
  operator==(const ElectricalConnectionStateDataElements &c_classObject) const;

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
  operator!=(const ElectricalConnectionStateDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member ElectricalConnectionId.
   */
  void setElectricalConnectionId();

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
   * Set member CurrentEnergyMode.
   */
  void setCurrentEnergyMode();

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
   */
  void setConsumptionTime();

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
   */
  void setProductionTime();

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
   */
  void setTotalConsumptionTime();

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
   */
  void setTotalProductionTime();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_electricalConnectionIdIsSet;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_currentEnergyModeIsSet;

  // ElementTag
  bool m_consumptionTimeIsSet;

  // ElementTag
  bool m_productionTimeIsSet;

  // ElementTag
  bool m_totalConsumptionTimeIsSet;

  // ElementTag
  bool m_totalProductionTimeIsSet;
};

//! typedef for non-const smart pointer type
//! ElectricalConnectionStateDataElements
using ElectricalConnectionStateDataElementsPtr =
    std::shared_ptr<ElectricalConnectionStateDataElements>;

//! typedef for const type ElectricalConnectionStateDataElements
using ElectricalConnectionStateDataElementsConst =
    const ElectricalConnectionStateDataElements;

//! typedef for const type ElectricalConnectionStateDataElements
using ElectricalConnectionStateDataElementsConstPtr =
    std::shared_ptr<ElectricalConnectionStateDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONSTATEDATAELEMENTS_H_