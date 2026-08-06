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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVEDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVEDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/Currency.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveDescriptionDataElements.h>
#include <keo_datagram/incentivetable/IncentiveType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveDescriptionData
 */
class IncentiveDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveDescriptionData();

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
  bool operator==(const IncentiveDescriptionData &c_classObject) const;

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
  bool operator!=(const IncentiveDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member IncentiveId.
   * @param c_incentiveId Value to set
   */
  void setIncentiveId(const xs_unsignedInt &c_incentiveId);

  /**
   * Returns const reference to member IncentiveId.
   * @return const reference to member incentiveId
   */
  const xs_unsignedInt &getIncentiveId() const;

  /**
   * Returns if member IncentiveId is set.
   * @retval true member IncentiveId is set
   * @retval false member IncentiveId is not set
   */
  bool getIncentiveIdIsSet() const;

  /**
   * Unsets member IncentiveId
   */
  void cleanIncentiveId();

  /**
   * Set member IncentiveType.
   * @param c_incentiveType Value to set
   */
  void setIncentiveType(const IncentiveType &c_incentiveType);

  /**
   * Returns const reference to member IncentiveType.
   * @return const reference to member incentiveType
   */
  const IncentiveType &getIncentiveType() const;

  /**
   * Returns if member IncentiveType is set.
   * @retval true member IncentiveType is set
   * @retval false member IncentiveType is not set
   */
  bool getIncentiveTypeIsSet() const;

  /**
   * Unsets member IncentiveType
   */
  void cleanIncentiveType();

  /**
   * Set member IncentivePriority.
   * @param c_incentivePriority Value to set
   */
  void setIncentivePriority(const xs_unsignedInt &c_incentivePriority);

  /**
   * Returns const reference to member IncentivePriority.
   * @return const reference to member incentivePriority
   */
  const xs_unsignedInt &getIncentivePriority() const;

  /**
   * Returns if member IncentivePriority is set.
   * @retval true member IncentivePriority is set
   * @retval false member IncentivePriority is not set
   */
  bool getIncentivePriorityIsSet() const;

  /**
   * Unsets member IncentivePriority
   */
  void cleanIncentivePriority();

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
  IncentiveDescriptionData
  reduce(const IncentiveDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_incentiveIdIsSet;
  xs_unsignedInt m_incentiveId;

  bool m_incentiveTypeIsSet;
  IncentiveType m_incentiveType;

  bool m_incentivePriorityIsSet;
  xs_unsignedInt m_incentivePriority;

  bool m_currencyIsSet;
  Currency m_currency;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type IncentiveDescriptionData
using IncentiveDescriptionDataPtr = std::shared_ptr<IncentiveDescriptionData>;

//! typedef for const type IncentiveDescriptionData
using IncentiveDescriptionDataConst = const IncentiveDescriptionData;

//! typedef for const type IncentiveDescriptionData
using IncentiveDescriptionDataConstPtr =
    std::shared_ptr<IncentiveDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVEDESCRIPTIONDATA_H_