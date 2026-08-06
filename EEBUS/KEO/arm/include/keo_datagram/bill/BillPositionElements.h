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

#ifndef KEO_DATAGRAM_BILL_BILLPOSITIONELEMENTS_H_
#define KEO_DATAGRAM_BILL_BILLPOSITIONELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/bill/BillCostElements.h>
#include <keo_datagram/bill/BillValueElements.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/TimePeriodElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillPositionElements
 */
class BillPositionElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  BillPositionElements();

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
  bool operator==(const BillPositionElements &c_classObject) const;

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
  bool operator!=(const BillPositionElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member PositionId.
   */
  void setPositionId();

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
   */
  void setPositionType();

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
  void setTimePeriod(const TimePeriodElements &c_timePeriod);

  /**
   * Returns const reference to member TimePeriod.
   * @return const reference to member timePeriod
   */
  const TimePeriodElements &getTimePeriod() const;

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
  void setValue(const BillValueElements &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const BillValueElements &getValue() const;

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
  void setCost(const BillCostElements &c_cost);

  /**
   * Returns const reference to member Cost.
   * @return const reference to member cost
   */
  const BillCostElements &getCost() const;

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
  bool m_positionIdIsSet;

  // ElementTag
  bool m_positionTypeIsSet;

  bool m_timePeriodIsSet;
  TimePeriodElements m_timePeriod;

  bool m_valueIsSet;
  BillValueElements m_value;

  bool m_costIsSet;
  BillCostElements m_cost;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type BillPositionElements
using BillPositionElementsPtr = std::shared_ptr<BillPositionElements>;

//! typedef for const type BillPositionElements
using BillPositionElementsConst = const BillPositionElements;

//! typedef for const type BillPositionElements
using BillPositionElementsConstPtr = std::shared_ptr<BillPositionElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLPOSITIONELEMENTS_H_