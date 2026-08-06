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

#ifndef KEO_DATAGRAM_BILL_BILLPOSITION_H_
#define KEO_DATAGRAM_BILL_BILLPOSITION_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/bill/BillCost.h>
#include <keo_datagram/bill/BillPositionElements.h>
#include <keo_datagram/bill/BillPositionType.h>
#include <keo_datagram/bill/BillValue.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillPosition
 */
class BillPosition : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  BillPosition();

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
  bool operator==(const BillPosition &c_classObject) const;

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
  bool operator!=(const BillPosition &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member PositionId.
   * @param c_positionId Value to set
   */
  void setPositionId(const xs_unsignedInt &c_positionId);

  /**
   * Returns const reference to member PositionId.
   * @return const reference to member positionId
   */
  const xs_unsignedInt &getPositionId() const;

  /**
   * Returns if member PositionId is set.
   * @retval true member PositionId is set
   * @retval false member PositionId is not set
   */
  bool getPositionIdIsSet() const;

  /**
   * Unsets member PositionId
   */
  void cleanPositionId();

  /**
   * Set member PositionType.
   * @param c_positionType Value to set
   */
  void setPositionType(const BillPositionType &c_positionType);

  /**
   * Returns const reference to member PositionType.
   * @return const reference to member positionType
   */
  const BillPositionType &getPositionType() const;

  /**
   * Returns if member PositionType is set.
   * @retval true member PositionType is set
   * @retval false member PositionType is not set
   */
  bool getPositionTypeIsSet() const;

  /**
   * Unsets member PositionType
   */
  void cleanPositionType();

  /**
   * Set member TimePeriod.
   * @param c_timePeriod Value to set
   */
  void setTimePeriod(const TimePeriod &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriod &getTimePeriod() const;

  /**
   * Returns if member TimePeriod is set.
   * @retval true member TimePeriod is set
   * @retval false member TimePeriod is not set
   */
  bool getTimePeriodIsSet() const;

  /**
   * Unsets member TimePeriod
   */
  void cleanTimePeriod();

  /**
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const std::vector<BillValue> &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const std::vector<BillValue> &getValue() const;

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
   * Set member Cost.
   * @param c_cost Value to set
   */
  void setCost(const std::vector<BillCost> &c_cost);

  /**
   * Returns const reference to member Cost.
   * @return const reference to member cost
   */
  const std::vector<BillCost> &getCost() const;

  /**
   * Returns if member Cost is set.
   * @retval true member Cost is set
   * @retval false member Cost is not set
   */
  bool getCostIsSet() const;

  /**
   * Unsets member Cost
   */
  void cleanCost();

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
  BillPosition reduce(const BillPositionElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_positionIdIsSet;
  xs_unsignedInt m_positionId;

  bool m_positionTypeIsSet;
  BillPositionType m_positionType;

  bool m_timePeriodIsSet;
  TimePeriod m_timePeriod;

  bool m_valueIsSet;
  std::vector<BillValue> m_value;

  bool m_costIsSet;
  std::vector<BillCost> m_cost;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type BillPosition
using BillPositionPtr = std::shared_ptr<BillPosition>;

//! typedef for const type BillPosition
using BillPositionConst = const BillPosition;

//! typedef for const type BillPosition
using BillPositionConstPtr = std::shared_ptr<BillPositionConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLPOSITION_H_