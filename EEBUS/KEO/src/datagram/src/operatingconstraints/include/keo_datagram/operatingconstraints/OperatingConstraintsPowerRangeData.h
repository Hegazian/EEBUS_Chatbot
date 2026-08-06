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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERRANGEDATA_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERRANGEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsPowerRangeData
 */
class OperatingConstraintsPowerRangeData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsPowerRangeData();

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
  operator==(const OperatingConstraintsPowerRangeData &c_classObject) const;

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
  operator!=(const OperatingConstraintsPowerRangeData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member SequenceId.
   * @param c_sequenceId Value to set
   */
  void setSequenceId(const xs_unsignedInt &c_sequenceId);

  /**
   * Returns const reference to member SequenceId.
   * @return const reference to member sequenceId
   */
  const xs_unsignedInt &getSequenceId() const;

  /**
   * Returns if member SequenceId is set.
   * @retval true member SequenceId is set
   * @retval false member SequenceId is not set
   */
  bool getSequenceIdIsSet() const;

  /**
   * Unsets member SequenceId
   */
  void cleanSequenceId();

  /**
   * Set member PowerMin.
   * @param c_powerMin Value to set
   */
  void setPowerMin(const ScaledNumber &c_powerMin);

  /**
   * Returns const reference to member PowerMin.
   * @return const reference to member powerMin
   */
  const ScaledNumber &getPowerMin() const;

  /**
   * Returns if member PowerMin is set.
   * @retval true member PowerMin is set
   * @retval false member PowerMin is not set
   */
  bool getPowerMinIsSet() const;

  /**
   * Unsets member PowerMin
   */
  void cleanPowerMin();

  /**
   * Set member PowerMax.
   * @param c_powerMax Value to set
   */
  void setPowerMax(const ScaledNumber &c_powerMax);

  /**
   * Returns const reference to member PowerMax.
   * @return const reference to member powerMax
   */
  const ScaledNumber &getPowerMax() const;

  /**
   * Returns if member PowerMax is set.
   * @retval true member PowerMax is set
   * @retval false member PowerMax is not set
   */
  bool getPowerMaxIsSet() const;

  /**
   * Unsets member PowerMax
   */
  void cleanPowerMax();

  /**
   * Set member EnergyMin.
   * @param c_energyMin Value to set
   */
  void setEnergyMin(const ScaledNumber &c_energyMin);

  /**
   * Returns const reference to member EnergyMin.
   * @return const reference to member energyMin
   */
  const ScaledNumber &getEnergyMin() const;

  /**
   * Returns if member EnergyMin is set.
   * @retval true member EnergyMin is set
   * @retval false member EnergyMin is not set
   */
  bool getEnergyMinIsSet() const;

  /**
   * Unsets member EnergyMin
   */
  void cleanEnergyMin();

  /**
   * Set member EnergyMax.
   * @param c_energyMax Value to set
   */
  void setEnergyMax(const ScaledNumber &c_energyMax);

  /**
   * Returns const reference to member EnergyMax.
   * @return const reference to member energyMax
   */
  const ScaledNumber &getEnergyMax() const;

  /**
   * Returns if member EnergyMax is set.
   * @retval true member EnergyMax is set
   * @retval false member EnergyMax is not set
   */
  bool getEnergyMaxIsSet() const;

  /**
   * Unsets member EnergyMax
   */
  void cleanEnergyMax();

  /**
   * @copydoc CmdData::reduce()
   */
  OperatingConstraintsPowerRangeData
  reduce(const OperatingConstraintsPowerRangeDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_powerMinIsSet;
  ScaledNumber m_powerMin;

  bool m_powerMaxIsSet;
  ScaledNumber m_powerMax;

  bool m_energyMinIsSet;
  ScaledNumber m_energyMin;

  bool m_energyMaxIsSet;
  ScaledNumber m_energyMax;
};

//! typedef for non-const smart pointer type OperatingConstraintsPowerRangeData
using OperatingConstraintsPowerRangeDataPtr =
    std::shared_ptr<OperatingConstraintsPowerRangeData>;

//! typedef for const type OperatingConstraintsPowerRangeData
using OperatingConstraintsPowerRangeDataConst =
    const OperatingConstraintsPowerRangeData;

//! typedef for const type OperatingConstraintsPowerRangeData
using OperatingConstraintsPowerRangeDataConstPtr =
    std::shared_ptr<OperatingConstraintsPowerRangeDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERRANGEDATA_H_