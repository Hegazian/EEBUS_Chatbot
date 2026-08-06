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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFDATAELEMENTS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffDataElements
 */
class TariffDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TariffDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tariffIdIsSet the member to set
   * @param c_activeTierIdIsSet the member to set
   */
  TariffDataElements(xs_boolean c_tariffIdIsSet,
                     xs_boolean c_activeTierIdIsSet);

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
  bool operator==(const TariffDataElements &c_classObject) const;

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
  bool operator!=(const TariffDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member TariffId.
   */
  void setTariffId();

  /**
   * Returns if member TariffId is set.
   * @retval true member TariffId is set
   * @retval false member TariffId is not set
   */
  bool getTariffIdIsSet() const;

  /**
   * Unsets member TariffId
   */
  void cleanTariffId();

  /**
   * Set member ActiveTierId.
   */
  void setActiveTierId();

  /**
   * Returns if member ActiveTierId is set.
   * @retval true member ActiveTierId is set
   * @retval false member ActiveTierId is not set
   */
  bool getActiveTierIdIsSet() const;

  /**
   * Unsets member ActiveTierId
   */
  void cleanActiveTierId();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_tariffIdIsSet;

  // ElementTag
  bool m_activeTierIdIsSet;
};

//! typedef for non-const smart pointer type TariffDataElements
using TariffDataElementsPtr = std::shared_ptr<TariffDataElements>;

//! typedef for const type TariffDataElements
using TariffDataElementsConst = const TariffDataElements;

//! typedef for const type TariffDataElements
using TariffDataElementsConstPtr = std::shared_ptr<TariffDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFDATAELEMENTS_H_