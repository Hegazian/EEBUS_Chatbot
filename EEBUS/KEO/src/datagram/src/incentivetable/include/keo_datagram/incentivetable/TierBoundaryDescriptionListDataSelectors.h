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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TierBoundaryType.h>

#include <keo_datagram/incentivetable/TierBoundaryDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TierBoundaryDescriptionListDataSelectors
 */
class TierBoundaryDescriptionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TierBoundaryDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_boundaryId the member to set
   * @param c_boundaryType the member to set
   */
  TierBoundaryDescriptionListDataSelectors(
      const xs_unsignedInt &c_boundaryId,
      const TierBoundaryType &c_boundaryType);

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
  bool operator==(
      const TierBoundaryDescriptionListDataSelectors &c_classObject) const;

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
  bool operator!=(
      const TierBoundaryDescriptionListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member BoundaryId.
   * @param c_boundaryId Value to set
   */
  void setBoundaryId(const xs_unsignedInt &c_boundaryId);

  /**
   * Returns const reference to member BoundaryId.
   * @return const reference to member boundaryId
   */
  const xs_unsignedInt &getBoundaryId() const;

  /**
   * Returns if member BoundaryId is set.
   * @retval true member BoundaryId is set
   * @retval false member BoundaryId is not set
   */
  bool getBoundaryIdIsSet() const;

  /**
   * Unsets member BoundaryId
   */
  void cleanBoundaryId();

  /**
   * Set member BoundaryType.
   * @param c_boundaryType Value to set
   */
  void setBoundaryType(const TierBoundaryType &c_boundaryType);

  /**
   * Returns const reference to member BoundaryType.
   * @return const reference to member boundaryType
   */
  const TierBoundaryType &getBoundaryType() const;

  /**
   * Returns if member BoundaryType is set.
   * @retval true member BoundaryType is set
   * @retval false member BoundaryType is not set
   */
  bool getBoundaryTypeIsSet() const;

  /**
   * Unsets member BoundaryType
   */
  void cleanBoundaryType();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const TierBoundaryDescriptionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_boundaryIdIsSet;
  xs_unsignedInt m_boundaryId;

  bool m_boundaryTypeIsSet;
  TierBoundaryType m_boundaryType;
};

//! typedef for non-const smart pointer type
//! TierBoundaryDescriptionListDataSelectors
using TierBoundaryDescriptionListDataSelectorsPtr =
    std::shared_ptr<TierBoundaryDescriptionListDataSelectors>;

//! typedef for const type TierBoundaryDescriptionListDataSelectors
using TierBoundaryDescriptionListDataSelectorsConst =
    const TierBoundaryDescriptionListDataSelectors;

//! typedef for const type TierBoundaryDescriptionListDataSelectors
using TierBoundaryDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<TierBoundaryDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDESCRIPTIONLISTDATASELECTORS_H_