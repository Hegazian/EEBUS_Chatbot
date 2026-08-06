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

#ifndef KEO_DATAGRAM_BILL_BILLCOST_H_
#define KEO_DATAGRAM_BILL_BILLCOST_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/bill/BillCostElements.h>
#include <keo_datagram/bill/BillCostType.h>
#include <keo_datagram/core/Currency.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillCost
 */
class BillCost : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  BillCost();

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
  bool operator==(const BillCost &c_classObject) const;

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
  bool operator!=(const BillCost &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member CostId.
   * @param c_costId Value to set
   */
  void setCostId(const xs_unsignedInt &c_costId);

  /**
   * Returns const reference to member CostId.
   * @return const reference to member costId
   */
  const xs_unsignedInt &getCostId() const;

  /**
   * Returns if member CostId is set.
   * @retval true member CostId is set
   * @retval false member CostId is not set
   */
  bool getCostIdIsSet() const;

  /**
   * Unsets member CostId
   */
  void cleanCostId();

  /**
   * Set member CostType.
   * @param c_costType Value to set
   */
  void setCostType(const BillCostType &c_costType);

  /**
   * Returns const reference to member CostType.
   * @return const reference to member costType
   */
  const BillCostType &getCostType() const;

  /**
   * Returns if member CostType is set.
   * @retval true member CostType is set
   * @retval false member CostType is not set
   */
  bool getCostTypeIsSet() const;

  /**
   * Unsets member CostType
   */
  void cleanCostType();

  /**
   * Set member ValueId.
   * @param c_valueId Value to set
   */
  void setValueId(const xs_unsignedInt &c_valueId);

  /**
   * Returns const reference to member ValueId.
   * @return const reference to member valueId
   */
  const xs_unsignedInt &getValueId() const;

  /**
   * Returns if member ValueId is set.
   * @retval true member ValueId is set
   * @retval false member ValueId is not set
   */
  bool getValueIdIsSet() const;

  /**
   * Unsets member ValueId
   */
  void cleanValueId();

  /**
   * Set member Unit.
   * @param c_unit Value to set
   */
  void setUnit(const UnitOfMeasurement &c_unit);

  /**
   * Returns const reference to member Unit.
   * @return const reference to member unit
   */
  const UnitOfMeasurement &getUnit() const;

  /**
   * Returns if member Unit is set.
   * @retval true member Unit is set
   * @retval false member Unit is not set
   */
  bool getUnitIsSet() const;

  /**
   * Unsets member Unit
   */
  void cleanUnit();

  /**
   * Set member Currency.
   * @param c_currency Value to set
   */
  void setCurrency(const Currency &c_currency);

  /**
   * Returns const reference to member Currency.
   * @return const reference to member currency
   */
  const Currency &getCurrency() const;

  /**
   * Returns if member Currency is set.
   * @retval true member Currency is set
   * @retval false member Currency is not set
   */
  bool getCurrencyIsSet() const;

  /**
   * Unsets member Currency
   */
  void cleanCurrency();

  /**
   * Set member Cost.
   * @param c_cost Value to set
   */
  void setCost(const ScaledNumber &c_cost);

  /**
   * Returns const reference to member Cost.
   * @return const reference to member cost
   */
  const ScaledNumber &getCost() const;

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
   * Set member CostPercentage.
   * @param c_costPercentage Value to set
   */
  void setCostPercentage(const ScaledNumber &c_costPercentage);

  /**
   * Returns const reference to member CostPercentage.
   * @return const reference to member costPercentage
   */
  const ScaledNumber &getCostPercentage() const;

  /**
   * Returns if member CostPercentage is set.
   * @retval true member CostPercentage is set
   * @retval false member CostPercentage is not set
   */
  bool getCostPercentageIsSet() const;

  /**
   * Unsets member CostPercentage
   */
  void cleanCostPercentage();

  /**
   * @copydoc CmdData::reduce()
   */
  BillCost reduce(const BillCostElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_costIdIsSet;
  xs_unsignedInt m_costId;

  bool m_costTypeIsSet;
  BillCostType m_costType;

  bool m_valueIdIsSet;
  xs_unsignedInt m_valueId;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_currencyIsSet;
  Currency m_currency;

  bool m_costIsSet;
  ScaledNumber m_cost;

  bool m_costPercentageIsSet;
  ScaledNumber m_costPercentage;
};

//! typedef for non-const smart pointer type BillCost
using BillCostPtr = std::shared_ptr<BillCost>;

//! typedef for const type BillCost
using BillCostConst = const BillCost;

//! typedef for const type BillCost
using BillCostConstPtr = std::shared_ptr<BillCostConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLCOST_H_