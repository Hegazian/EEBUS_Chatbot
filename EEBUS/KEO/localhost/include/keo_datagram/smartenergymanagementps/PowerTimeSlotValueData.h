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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTVALUEDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTVALUEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerTimeSlotValueData
 */
class PowerTimeSlotValueData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PowerTimeSlotValueData();

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
  bool operator==(const PowerTimeSlotValueData &c_classObject) const;

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
  bool operator!=(const PowerTimeSlotValueData &c_classObject) const;

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
   * Set member SlotNumber.
   * @param c_slotNumber Value to set
   */
  void setSlotNumber(const xs_unsignedInt &c_slotNumber);

  /**
   * Returns const reference to member SlotNumber.
   * @return const reference to member slotNumber
   */
  const xs_unsignedInt &getSlotNumber() const;

  /**
   * Returns if member SlotNumber is set.
   * @retval true member SlotNumber is set
   * @retval false member SlotNumber is not set
   */
  bool getSlotNumberIsSet() const;

  /**
   * Unsets member SlotNumber
   */
  void cleanSlotNumber();

  /**
   * Set member ValueType.
   * @param c_valueType Value to set
   */
  void setValueType(const PowerTimeSlotValueType &c_valueType);

  /**
   * Returns const reference to member ValueType.
   * @return const reference to member valueType
   */
  const PowerTimeSlotValueType &getValueType() const;

  /**
   * Returns if member ValueType is set.
   * @retval true member ValueType is set
   * @retval false member ValueType is not set
   */
  bool getValueTypeIsSet() const;

  /**
   * Unsets member ValueType
   */
  void cleanValueType();

  /**
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const ScaledNumber &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const ScaledNumber &getValue() const;

  /**
   * Returns if member Value is set.
   * @retval true member Value is set
   * @retval false member Value is not set
   */
  bool getValueIsSet() const;

  /**
   * Unsets member Value
   */
  void cleanValue();

  /**
   * @copydoc CmdData::reduce()
   */
  PowerTimeSlotValueData
  reduce(const PowerTimeSlotValueDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_slotNumberIsSet;
  xs_unsignedInt m_slotNumber;

  bool m_valueTypeIsSet;
  PowerTimeSlotValueType m_valueType;

  bool m_valueIsSet;
  ScaledNumber m_value;
};

//! typedef for non-const smart pointer type PowerTimeSlotValueData
using PowerTimeSlotValueDataPtr = std::shared_ptr<PowerTimeSlotValueData>;

//! typedef for const type PowerTimeSlotValueData
using PowerTimeSlotValueDataConst = const PowerTimeSlotValueData;

//! typedef for const type PowerTimeSlotValueData
using PowerTimeSlotValueDataConstPtr =
    std::shared_ptr<PowerTimeSlotValueDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTVALUEDATA_H_