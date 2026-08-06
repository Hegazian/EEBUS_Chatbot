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

#ifndef KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/EnergyDirection.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionDataElements.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionVoltageType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramElectricalConnection
 * @{
 */

/**
 * Declaration ElectricalConnectionDescriptionData
 */
class ElectricalConnectionDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  ElectricalConnectionDescriptionData();

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
  operator==(const ElectricalConnectionDescriptionData &c_classObject) const;

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
  operator!=(const ElectricalConnectionDescriptionData &c_classObject) const;

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
   * Set member PowerSupplyType.
   * @param c_powerSupplyType Value to set
   */
  void
  setPowerSupplyType(const ElectricalConnectionVoltageType &c_powerSupplyType);

  /**
   * Returns const reference to member PowerSupplyType.
   * @return const reference to member powerSupplyType
   */
  const ElectricalConnectionVoltageType &getPowerSupplyType() const;

  /**
   * Returns if member PowerSupplyType is set.
   * @retval true member PowerSupplyType is set
   * @retval false member PowerSupplyType is not set
   */
  bool getPowerSupplyTypeIsSet() const;

  /**
   * Unsets member PowerSupplyType
   */
  void cleanPowerSupplyType();

  /**
   * Set member AcConnectedPhases.
   * @param c_acConnectedPhases Value to set
   */
  void setAcConnectedPhases(const xs_unsignedInt &c_acConnectedPhases);

  /**
   * Returns const reference to member AcConnectedPhases.
   * @return const reference to member acConnectedPhases
   */
  const xs_unsignedInt &getAcConnectedPhases() const;

  /**
   * Returns if member AcConnectedPhases is set.
   * @retval true member AcConnectedPhases is set
   * @retval false member AcConnectedPhases is not set
   */
  bool getAcConnectedPhasesIsSet() const;

  /**
   * Unsets member AcConnectedPhases
   */
  void cleanAcConnectedPhases();

  /**
   * Set member AcRmsPeriodDuration.
   * @param c_acRmsPeriodDuration Value to set
   */
  void setAcRmsPeriodDuration(const xs_duration &c_acRmsPeriodDuration);

  /**
   * Returns const reference to member AcRmsPeriodDuration.
   * @return const reference to member acRmsPeriodDuration
   */
  const xs_duration &getAcRmsPeriodDuration() const;

  /**
   * Returns if member AcRmsPeriodDuration is set.
   * @retval true member AcRmsPeriodDuration is set
   * @retval false member AcRmsPeriodDuration is not set
   */
  bool getAcRmsPeriodDurationIsSet() const;

  /**
   * Unsets member AcRmsPeriodDuration
   */
  void cleanAcRmsPeriodDuration();

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
  ElectricalConnectionDescriptionData
  reduce(const ElectricalConnectionDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_electricalConnectionIdIsSet;
  xs_unsignedInt m_electricalConnectionId;

  bool m_powerSupplyTypeIsSet;
  ElectricalConnectionVoltageType m_powerSupplyType;

  bool m_acConnectedPhasesIsSet;
  xs_unsignedInt m_acConnectedPhases;

  bool m_acRmsPeriodDurationIsSet;
  xs_duration m_acRmsPeriodDuration;

  bool m_positiveEnergyDirectionIsSet;
  EnergyDirection m_positiveEnergyDirection;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type ElectricalConnectionDescriptionData
using ElectricalConnectionDescriptionDataPtr =
    std::shared_ptr<ElectricalConnectionDescriptionData>;

//! typedef for const type ElectricalConnectionDescriptionData
using ElectricalConnectionDescriptionDataConst =
    const ElectricalConnectionDescriptionData;

//! typedef for const type ElectricalConnectionDescriptionData
using ElectricalConnectionDescriptionDataConstPtr =
    std::shared_ptr<ElectricalConnectionDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONDESCRIPTIONDATA_H_