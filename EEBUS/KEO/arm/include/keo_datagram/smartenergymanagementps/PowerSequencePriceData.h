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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICEDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/Currency.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerSequencePriceDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequencePriceData
 */
class PowerSequencePriceData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequencePriceData();

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
  bool operator==(const PowerSequencePriceData &c_classObject) const;

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
  bool operator!=(const PowerSequencePriceData &c_classObject) const;

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
   * Set member PotentialStartTime.
   * @param c_potentialStartTime Value to set
   */
  void
  setPotentialStartTime(const AbsoluteOrRelativeTime &c_potentialStartTime);

  /**
   * Returns const reference to member PotentialStartTime.
   * @return const reference to member potentialStartTime
   */
  const AbsoluteOrRelativeTime &getPotentialStartTime() const;

  /**
   * Returns if member PotentialStartTime is set.
   * @retval true member PotentialStartTime is set
   * @retval false member PotentialStartTime is not set
   */
  bool getPotentialStartTimeIsSet() const;

  /**
   * Unsets member PotentialStartTime
   */
  void cleanPotentialStartTime();

  /**
   * Set member Price.
   * @param c_price Value to set
   */
  void setPrice(const ScaledNumber &c_price);

  /**
   * Returns const reference to member Price.
   * @return const reference to member price
   */
  const ScaledNumber &getPrice() const;

  /**
   * Returns if member Price is set.
   * @retval true member Price is set
   * @retval false member Price is not set
   */
  bool getPriceIsSet() const;

  /**
   * Unsets member Price
   */
  void cleanPrice();

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
   * @copydoc CmdData::reduce()
   */
  PowerSequencePriceData
  reduce(const PowerSequencePriceDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_potentialStartTimeIsSet;
  AbsoluteOrRelativeTime m_potentialStartTime;

  bool m_priceIsSet;
  ScaledNumber m_price;

  bool m_currencyIsSet;
  Currency m_currency;
};

//! typedef for non-const smart pointer type PowerSequencePriceData
using PowerSequencePriceDataPtr = std::shared_ptr<PowerSequencePriceData>;

//! typedef for const type PowerSequencePriceData
using PowerSequencePriceDataConst = const PowerSequencePriceData;

//! typedef for const type PowerSequencePriceData
using PowerSequencePriceDataConstPtr =
    std::shared_ptr<PowerSequencePriceDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICEDATA_H_