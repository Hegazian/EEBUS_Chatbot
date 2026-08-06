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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TIERINCENTIVERELATIONDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TIERINCENTIVERELATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TierIncentiveRelationDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TierIncentiveRelationData
 */
class TierIncentiveRelationData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TierIncentiveRelationData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tierId the member to set
   * @param c_incentiveId the member to set
   */
  TierIncentiveRelationData(const xs_unsignedInt &c_tierId,
                            const std::vector<xs_unsignedInt> &c_incentiveId);

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
  bool operator==(const TierIncentiveRelationData &c_classObject) const;

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
  bool operator!=(const TierIncentiveRelationData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member IncentiveId.
   * @param c_incentiveId Value to set
   */
  void setIncentiveId(const std::vector<xs_unsignedInt> &c_incentiveId);

  /**
   * Returns const reference to member IncentiveId.
   * @return const reference to member incentiveId
   */
  const std::vector<xs_unsignedInt> &getIncentiveId() const;

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
   * @copydoc CmdData::reduce()
   */
  TierIncentiveRelationData
  reduce(const TierIncentiveRelationDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tierIdIsSet;
  xs_unsignedInt m_tierId;

  bool m_incentiveIdIsSet;
  std::vector<xs_unsignedInt> m_incentiveId;
};

//! typedef for non-const smart pointer type TierIncentiveRelationData
using TierIncentiveRelationDataPtr = std::shared_ptr<TierIncentiveRelationData>;

//! typedef for const type TierIncentiveRelationData
using TierIncentiveRelationDataConst = const TierIncentiveRelationData;

//! typedef for const type TierIncentiveRelationData
using TierIncentiveRelationDataConstPtr =
    std::shared_ptr<TierIncentiveRelationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TIERINCENTIVERELATIONDATA_H_