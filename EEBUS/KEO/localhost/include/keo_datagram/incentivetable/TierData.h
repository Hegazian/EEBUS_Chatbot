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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TIERDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TIERDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/TimePeriod.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TierDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TierData
 */
class TierData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TierData();

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
  bool operator==(const TierData &c_classObject) const;

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
  bool operator!=(const TierData &c_classObject) const;

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
   * Set member TimeTableId.
   * @param c_timeTableId Value to set
   */
  void setTimeTableId(const xs_unsignedInt &c_timeTableId);

  /**
   * Returns const reference to member TimeTableId.
   * @return const reference to member timeTableId
   */
  const xs_unsignedInt &getTimeTableId() const;

  /**
   * Returns if member TimeTableId is set.
   * @retval true member TimeTableId is set
   * @retval false member TimeTableId is not set
   */
  bool getTimeTableIdIsSet() const;

  /**
   * Unsets member TimeTableId
   */
  void cleanTimeTableId();

  /**
   * Set member ActiveIncentiveId.
   * @param c_activeIncentiveId Value to set
   */
  void
  setActiveIncentiveId(const std::vector<xs_unsignedInt> &c_activeIncentiveId);

  /**
   * Returns const reference to member ActiveIncentiveId.
   * @return const reference to member activeIncentiveId
   */
  const std::vector<xs_unsignedInt> &getActiveIncentiveId() const;

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
   * @copydoc CmdData::reduce()
   */
  TierData reduce(const TierDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tierIdIsSet;
  xs_unsignedInt m_tierId;

  bool m_timePeriodIsSet;
  TimePeriod m_timePeriod;

  bool m_timeTableIdIsSet;
  xs_unsignedInt m_timeTableId;

  bool m_activeIncentiveIdIsSet;
  std::vector<xs_unsignedInt> m_activeIncentiveId;
};

//! typedef for non-const smart pointer type TierData
using TierDataPtr = std::shared_ptr<TierData>;

//! typedef for const type TierData
using TierDataConst = const TierData;

//! typedef for const type TierData
using TierDataConstPtr = std::shared_ptr<TierDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TIERDATA_H_