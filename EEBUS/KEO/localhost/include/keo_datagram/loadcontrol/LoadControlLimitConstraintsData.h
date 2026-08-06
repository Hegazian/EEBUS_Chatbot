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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITCONSTRAINTSDATA_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITCONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlLimitConstraintsData
 */
class LoadControlLimitConstraintsData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlLimitConstraintsData();

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
  bool operator==(const LoadControlLimitConstraintsData &c_classObject) const;

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
  bool operator!=(const LoadControlLimitConstraintsData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member LimitId.
   * @param c_limitId Value to set
   */
  void setLimitId(const xs_unsignedInt &c_limitId);

  /**
   * Returns const reference to member LimitId.
   * @return const reference to member limitId
   */
  const xs_unsignedInt &getLimitId() const;

  /**
   * Returns if member LimitId is set.
   * @retval true member LimitId is set
   * @retval false member LimitId is not set
   */
  bool getLimitIdIsSet() const;

  /**
   * Unsets member LimitId
   */
  void cleanLimitId();

  /**
   * Set member ValueRangeMin.
   * @param c_valueRangeMin Value to set
   */
  void setValueRangeMin(const ScaledNumber &c_valueRangeMin);

  /**
   * Returns const reference to member ValueRangeMin.
   * @return const reference to member valueRangeMin
   */
  const ScaledNumber &getValueRangeMin() const;

  /**
   * Returns if member ValueRangeMin is set.
   * @retval true member ValueRangeMin is set
   * @retval false member ValueRangeMin is not set
   */
  bool getValueRangeMinIsSet() const;

  /**
   * Unsets member ValueRangeMin
   */
  void cleanValueRangeMin();

  /**
   * Set member ValueRangeMax.
   * @param c_valueRangeMax Value to set
   */
  void setValueRangeMax(const ScaledNumber &c_valueRangeMax);

  /**
   * Returns const reference to member ValueRangeMax.
   * @return const reference to member valueRangeMax
   */
  const ScaledNumber &getValueRangeMax() const;

  /**
   * Returns if member ValueRangeMax is set.
   * @retval true member ValueRangeMax is set
   * @retval false member ValueRangeMax is not set
   */
  bool getValueRangeMaxIsSet() const;

  /**
   * Unsets member ValueRangeMax
   */
  void cleanValueRangeMax();

  /**
   * Set member ValueStepSize.
   * @param c_valueStepSize Value to set
   */
  void setValueStepSize(const ScaledNumber &c_valueStepSize);

  /**
   * Returns const reference to member ValueStepSize.
   * @return const reference to member valueStepSize
   */
  const ScaledNumber &getValueStepSize() const;

  /**
   * Returns if member ValueStepSize is set.
   * @retval true member ValueStepSize is set
   * @retval false member ValueStepSize is not set
   */
  bool getValueStepSizeIsSet() const;

  /**
   * Unsets member ValueStepSize
   */
  void cleanValueStepSize();

  /**
   * @copydoc CmdData::reduce()
   */
  LoadControlLimitConstraintsData
  reduce(const LoadControlLimitConstraintsDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_limitIdIsSet;
  xs_unsignedInt m_limitId;

  bool m_valueRangeMinIsSet;
  ScaledNumber m_valueRangeMin;

  bool m_valueRangeMaxIsSet;
  ScaledNumber m_valueRangeMax;

  bool m_valueStepSizeIsSet;
  ScaledNumber m_valueStepSize;
};

//! typedef for non-const smart pointer type LoadControlLimitConstraintsData
using LoadControlLimitConstraintsDataPtr =
    std::shared_ptr<LoadControlLimitConstraintsData>;

//! typedef for const type LoadControlLimitConstraintsData
using LoadControlLimitConstraintsDataConst =
    const LoadControlLimitConstraintsData;

//! typedef for const type LoadControlLimitConstraintsData
using LoadControlLimitConstraintsDataConstPtr =
    std::shared_ptr<LoadControlLimitConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLLIMITCONSTRAINTSDATA_H_