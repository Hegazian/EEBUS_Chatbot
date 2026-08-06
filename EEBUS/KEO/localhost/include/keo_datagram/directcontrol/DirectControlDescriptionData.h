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

#ifndef KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/EnergyDirection.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDirectControl
 * @{
 */

/**
 * Declaration DirectControlDescriptionData
 */
class DirectControlDescriptionData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  DirectControlDescriptionData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_positiveEnergyDirection the member to set
   * @param c_powerUnit the member to set
   * @param c_energyUnit the member to set
   */
  DirectControlDescriptionData(const EnergyDirection &c_positiveEnergyDirection,
                               const UnitOfMeasurement &c_powerUnit,
                               const UnitOfMeasurement &c_energyUnit);

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
  bool operator==(const DirectControlDescriptionData &c_classObject) const;

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
  bool operator!=(const DirectControlDescriptionData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member PositiveEnergyDirection.
   * @param c_positiveEnergyDirection Value to set
   */
  void
  setPositiveEnergyDirection(const EnergyDirection &c_positiveEnergyDirection);

  /**
   * Returns const reference to member PositiveEnergyDirection.
   * @return const reference to member positiveEnergyDirection
   */
  const EnergyDirection &getPositiveEnergyDirection() const;

  /**
   * Returns if member PositiveEnergyDirection is set.
   * @retval true member PositiveEnergyDirection is set
   * @retval false member PositiveEnergyDirection is not set
   */
  bool getPositiveEnergyDirectionIsSet() const;

  /**
   * Unsets member PositiveEnergyDirection
   */
  void cleanPositiveEnergyDirection();

  /**
   * Set member PowerUnit.
   * @param c_powerUnit Value to set
   */
  void setPowerUnit(const UnitOfMeasurement &c_powerUnit);

  /**
   * Returns const reference to member PowerUnit.
   * @return const reference to member powerUnit
   */
  const UnitOfMeasurement &getPowerUnit() const;

  /**
   * Returns if member PowerUnit is set.
   * @retval true member PowerUnit is set
   * @retval false member PowerUnit is not set
   */
  bool getPowerUnitIsSet() const;

  /**
   * Unsets member PowerUnit
   */
  void cleanPowerUnit();

  /**
   * Set member EnergyUnit.
   * @param c_energyUnit Value to set
   */
  void setEnergyUnit(const UnitOfMeasurement &c_energyUnit);

  /**
   * Returns const reference to member EnergyUnit.
   * @return const reference to member energyUnit
   */
  const UnitOfMeasurement &getEnergyUnit() const;

  /**
   * Returns if member EnergyUnit is set.
   * @retval true member EnergyUnit is set
   * @retval false member EnergyUnit is not set
   */
  bool getEnergyUnitIsSet() const;

  /**
   * Unsets member EnergyUnit
   */
  void cleanEnergyUnit();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_positiveEnergyDirectionIsSet;
  EnergyDirection m_positiveEnergyDirection;

  bool m_powerUnitIsSet;
  UnitOfMeasurement m_powerUnit;

  bool m_energyUnitIsSet;
  UnitOfMeasurement m_energyUnit;
};

//! typedef for non-const smart pointer type DirectControlDescriptionData
using DirectControlDescriptionDataPtr =
    std::shared_ptr<DirectControlDescriptionData>;

//! typedef for const type DirectControlDescriptionData
using DirectControlDescriptionDataConst = const DirectControlDescriptionData;

//! typedef for const type DirectControlDescriptionData
using DirectControlDescriptionDataConstPtr =
    std::shared_ptr<DirectControlDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DIRECTCONTROL_DIRECTCONTROLDESCRIPTIONDATA_H_