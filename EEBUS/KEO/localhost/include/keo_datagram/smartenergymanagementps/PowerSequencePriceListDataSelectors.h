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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICELISTDATASELECTORS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICELISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/TimestampInterval.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/smartenergymanagementps/PowerSequencePriceData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequencePriceListDataSelectors
 */
class PowerSequencePriceListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequencePriceListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_sequenceId the member to set
   * @param c_potentialStartTimeInterval the member to set
   */
  PowerSequencePriceListDataSelectors(
      const xs_unsignedInt &c_sequenceId,
      const TimestampInterval &c_potentialStartTimeInterval);

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
  bool
  operator==(const PowerSequencePriceListDataSelectors &c_classObject) const;

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
  bool
  operator!=(const PowerSequencePriceListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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
   * Set member PotentialStartTimeInterval.
   * @param c_potentialStartTimeInterval Value to set
   */
  void setPotentialStartTimeInterval(
      const TimestampInterval &c_potentialStartTimeInterval);

  /**
   * Returns const reference to member PotentialStartTimeInterval.
   * @return const reference to member potentialStartTimeInterval
   */
  const TimestampInterval &getPotentialStartTimeInterval() const;

  /**
   * Returns if member PotentialStartTimeInterval is set.
   * @retval true member PotentialStartTimeInterval is set
   * @retval false member PotentialStartTimeInterval is not set
   */
  bool getPotentialStartTimeIntervalIsSet() const;

  /**
   * Unsets member PotentialStartTimeInterval
   */
  void cleanPotentialStartTimeInterval();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const PowerSequencePriceData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_potentialStartTimeIntervalIsSet;
  TimestampInterval m_potentialStartTimeInterval;
};

//! typedef for non-const smart pointer type PowerSequencePriceListDataSelectors
using PowerSequencePriceListDataSelectorsPtr =
    std::shared_ptr<PowerSequencePriceListDataSelectors>;

//! typedef for const type PowerSequencePriceListDataSelectors
using PowerSequencePriceListDataSelectorsConst =
    const PowerSequencePriceListDataSelectors;

//! typedef for const type PowerSequencePriceListDataSelectors
using PowerSequencePriceListDataSelectorsConstPtr =
    std::shared_ptr<PowerSequencePriceListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEPRICELISTDATASELECTORS_H_