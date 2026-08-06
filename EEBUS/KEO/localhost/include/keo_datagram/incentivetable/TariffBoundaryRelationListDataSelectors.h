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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFBOUNDARYRELATIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFBOUNDARYRELATIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/incentivetable/TariffBoundaryRelationData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffBoundaryRelationListDataSelectors
 */
class TariffBoundaryRelationListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  TariffBoundaryRelationListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_tariffId the member to set
   * @param c_boundaryId the member to set
   */
  TariffBoundaryRelationListDataSelectors(const xs_unsignedInt &c_tariffId,
                                          const xs_unsignedInt &c_boundaryId);

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
      const TariffBoundaryRelationListDataSelectors &c_classObject) const;

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
      const TariffBoundaryRelationListDataSelectors &c_classObject) const;

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
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const TariffBoundaryRelationData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffIdIsSet;
  xs_unsignedInt m_tariffId;

  bool m_boundaryIdIsSet;
  xs_unsignedInt m_boundaryId;
};

//! typedef for non-const smart pointer type
//! TariffBoundaryRelationListDataSelectors
using TariffBoundaryRelationListDataSelectorsPtr =
    std::shared_ptr<TariffBoundaryRelationListDataSelectors>;

//! typedef for const type TariffBoundaryRelationListDataSelectors
using TariffBoundaryRelationListDataSelectorsConst =
    const TariffBoundaryRelationListDataSelectors;

//! typedef for const type TariffBoundaryRelationListDataSelectors
using TariffBoundaryRelationListDataSelectorsConstPtr =
    std::shared_ptr<TariffBoundaryRelationListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFBOUNDARYRELATIONLISTDATASELECTORS_H_