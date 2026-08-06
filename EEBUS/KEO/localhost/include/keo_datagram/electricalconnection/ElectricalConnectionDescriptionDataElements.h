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

#ifndef KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONDESCRIPTIONDATAELEMENTS_H_

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
 * Declaration ElectricalConnectionDescriptionDataElements
 */
class ElectricalConnectionDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  ElectricalConnectionDescriptionDataElements();

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
  bool operator==(
      const ElectricalConnectionDescriptionDataElements &c_classObject) const;

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
  bool operator!=(
      const ElectricalConnectionDescriptionDataElements &c_classObject) const;

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
   * Set member PowerSupplyType.
   */
  void setPowerSupplyType();

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
   */
  void setAcConnectedPhases();

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
   */
  void setAcRmsPeriodDuration();

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
   */
  void setPositiveEnergyDirection();

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
   */
  void setScopeType();

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
   */
  void setLabel();

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
   */
  void setDescription();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_electricalConnectionIdIsSet;

  // ElementTag
  bool m_powerSupplyTypeIsSet;

  // ElementTag
  bool m_acConnectedPhasesIsSet;

  // ElementTag
  bool m_acRmsPeriodDurationIsSet;

  // ElementTag
  bool m_positiveEnergyDirectionIsSet;

  // ElementTag
  bool m_scopeTypeIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type
//! ElectricalConnectionDescriptionDataElements
using ElectricalConnectionDescriptionDataElementsPtr =
    std::shared_ptr<ElectricalConnectionDescriptionDataElements>;

//! typedef for const type ElectricalConnectionDescriptionDataElements
using ElectricalConnectionDescriptionDataElementsConst =
    const ElectricalConnectionDescriptionDataElements;

//! typedef for const type ElectricalConnectionDescriptionDataElements
using ElectricalConnectionDescriptionDataElementsConstPtr =
    std::shared_ptr<ElectricalConnectionDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONDESCRIPTIONDATAELEMENTS_H_