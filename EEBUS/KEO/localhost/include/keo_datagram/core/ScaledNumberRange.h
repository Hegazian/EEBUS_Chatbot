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

#ifndef KEO_DATAGRAM_CORE_SCALEDNUMBERRANGE_H_
#define KEO_DATAGRAM_CORE_SCALEDNUMBERRANGE_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/ScaledNumberRangeElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration ScaledNumberRange
 */
class ScaledNumberRange : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  ScaledNumberRange();

  /**
   * Construct an instance of this class and set its member.
   * @param c_min the member to set
   * @param c_max the member to set
   */
  ScaledNumberRange(const ScaledNumber &c_min, const ScaledNumber &c_max);

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
  bool operator==(const ScaledNumberRange &c_classObject) const;

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
  bool operator!=(const ScaledNumberRange &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Min.
   * @param c_min Value to set
   */
  void setMin(const ScaledNumber &c_min);

  /**
   * Returns const reference to member Min.
   * @return const reference to member min
   */
  const ScaledNumber &getMin() const;

  /**
   * Returns if member Min is set.
   * @retval true member Min is set
   * @retval false member Min is not set
   */
  bool getMinIsSet() const;

  /**
   * Unsets member Min
   */
  void cleanMin();

  /**
   * Set member Max.
   * @param c_max Value to set
   */
  void setMax(const ScaledNumber &c_max);

  /**
   * Returns const reference to member Max.
   * @return const reference to member max
   */
  const ScaledNumber &getMax() const;

  /**
   * Returns if member Max is set.
   * @retval true member Max is set
   * @retval false member Max is not set
   */
  bool getMaxIsSet() const;

  /**
   * Unsets member Max
   */
  void cleanMax();

  /**
   * @copydoc CmdData::reduce()
   */
  ScaledNumberRange reduce(const ScaledNumberRangeElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_minIsSet;
  ScaledNumber m_min;

  bool m_maxIsSet;
  ScaledNumber m_max;
};

//! typedef for non-const smart pointer type ScaledNumberRange
using ScaledNumberRangePtr = std::shared_ptr<ScaledNumberRange>;

//! typedef for const type ScaledNumberRange
using ScaledNumberRangeConst = const ScaledNumberRange;

//! typedef for const type ScaledNumberRange
using ScaledNumberRangeConstPtr = std::shared_ptr<ScaledNumberRangeConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_SCALEDNUMBERRANGE_H_