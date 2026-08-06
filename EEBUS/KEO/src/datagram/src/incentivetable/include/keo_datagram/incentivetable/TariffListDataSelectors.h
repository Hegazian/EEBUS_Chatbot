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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFLISTDATASELECTORS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/incentivetable/TariffData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffListDataSelectors
 */
class TariffListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TariffListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tariffId the member to set
   * @param c_activeTierId the member to set
   */
  TariffListDataSelectors(const xs_unsignedInt &c_tariffId,
                          const xs_unsignedInt &c_activeTierId);

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
  bool operator==(const TariffListDataSelectors &c_classObject) const;

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
  bool operator!=(const TariffListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member TariffId.
   * @param c_tariffId Value to set
   */
  void setTariffId(const xs_unsignedInt &c_tariffId);

  /**
   * Returns const reference to member TariffId.
   * @return const reference to member tariffId
   */
  const xs_unsignedInt &getTariffId() const;

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
   * @param c_activeTierId Value to set
   */
  void setActiveTierId(const xs_unsignedInt &c_activeTierId);

  /**
   * Returns const reference to member ActiveTierId.
   * @return const reference to member activeTierId
   */
  const xs_unsignedInt &getActiveTierId() const;

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

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const TariffData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffIdIsSet;
  xs_unsignedInt m_tariffId;

  bool m_activeTierIdIsSet;
  xs_unsignedInt m_activeTierId;
};

//! typedef for non-const smart pointer type TariffListDataSelectors
using TariffListDataSelectorsPtr = std::shared_ptr<TariffListDataSelectors>;

//! typedef for const type TariffListDataSelectors
using TariffListDataSelectorsConst = const TariffListDataSelectors;

//! typedef for const type TariffListDataSelectors
using TariffListDataSelectorsConstPtr =
    std::shared_ptr<TariffListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFLISTDATASELECTORS_H_