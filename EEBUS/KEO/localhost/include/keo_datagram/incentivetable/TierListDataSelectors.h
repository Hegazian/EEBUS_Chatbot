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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TIERLISTDATASELECTORS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TIERLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/incentivetable/TierData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TierListDataSelectors
 */
class TierListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TierListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tierId the member to set
   * @param c_activeIncentiveId the member to set
   */
  TierListDataSelectors(const xs_unsignedInt &c_tierId,
                        const xs_unsignedInt &c_activeIncentiveId);

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
  bool operator==(const TierListDataSelectors &c_classObject) const;

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
  bool operator!=(const TierListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member TierId.
   * @param c_tierId Value to set
   */
  void setTierId(const xs_unsignedInt &c_tierId);

  /**
   * Returns const reference to member TierId.
   * @return const reference to member tierId
   */
  const xs_unsignedInt &getTierId() const;

  /**
   * Returns if member TierId is set.
   * @retval true member TierId is set
   * @retval false member TierId is not set
   */
  bool getTierIdIsSet() const;

  /**
   * Unsets member TierId
   */
  void cleanTierId();

  /**
   * Set member ActiveIncentiveId.
   * @param c_activeIncentiveId Value to set
   */
  void setActiveIncentiveId(const xs_unsignedInt &c_activeIncentiveId);

  /**
   * Returns const reference to member ActiveIncentiveId.
   * @return const reference to member activeIncentiveId
   */
  const xs_unsignedInt &getActiveIncentiveId() const;

  /**
   * Returns if member ActiveIncentiveId is set.
   * @retval true member ActiveIncentiveId is set
   * @retval false member ActiveIncentiveId is not set
   */
  bool getActiveIncentiveIdIsSet() const;

  /**
   * Unsets member ActiveIncentiveId
   */
  void cleanActiveIncentiveId();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const TierData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tierIdIsSet;
  xs_unsignedInt m_tierId;

  bool m_activeIncentiveIdIsSet;
  xs_unsignedInt m_activeIncentiveId;
};

//! typedef for non-const smart pointer type TierListDataSelectors
using TierListDataSelectorsPtr = std::shared_ptr<TierListDataSelectors>;

//! typedef for const type TierListDataSelectors
using TierListDataSelectorsConst = const TierListDataSelectors;

//! typedef for const type TierListDataSelectors
using TierListDataSelectorsConstPtr =
    std::shared_ptr<TierListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TIERLISTDATASELECTORS_H_