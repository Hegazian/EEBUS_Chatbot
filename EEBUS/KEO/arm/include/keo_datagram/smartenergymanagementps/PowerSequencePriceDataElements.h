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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICEDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICEDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequencePriceDataElements
 */
class PowerSequencePriceDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequencePriceDataElements();

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
  bool operator==(const PowerSequencePriceDataElements &c_classObject) const;

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
  bool operator!=(const PowerSequencePriceDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member SequenceId.
   */
  void setSequenceId();

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
   */
  void setPotentialStartTime();

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
  void setPrice(const ScaledNumberElements &c_price);

  /**
   * Returns const reference to member Price.
   * @return const reference to member price
   */
  const ScaledNumberElements &getPrice() const;

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
   */
  void setCurrency();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_potentialStartTimeIsSet;

  bool m_priceIsSet;
  ScaledNumberElements m_price;

  // ElementTag
  bool m_currencyIsSet;
};

//! typedef for non-const smart pointer type PowerSequencePriceDataElements
using PowerSequencePriceDataElementsPtr =
    std::shared_ptr<PowerSequencePriceDataElements>;

//! typedef for const type PowerSequencePriceDataElements
using PowerSequencePriceDataElementsConst =
    const PowerSequencePriceDataElements;

//! typedef for const type PowerSequencePriceDataElements
using PowerSequencePriceDataElementsConstPtr =
    std::shared_ptr<PowerSequencePriceDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICEDATAELEMENTS_H_