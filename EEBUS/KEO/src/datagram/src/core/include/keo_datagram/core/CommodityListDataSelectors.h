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

#ifndef KEO_DATAGRAM_CORE_COMMODITYLISTDATASELECTORS_H_
#define KEO_DATAGRAM_CORE_COMMODITYLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CommodityType.h>
#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/CommodityData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration CommodityListDataSelectors
 */
class CommodityListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  CommodityListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_commodityId the member to set
   * @param c_commodityType the member to set
   */
  CommodityListDataSelectors(const xs_unsignedInt &c_commodityId,
                             const CommodityType &c_commodityType);

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
  bool operator==(const CommodityListDataSelectors &c_classObject) const;

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
  bool operator!=(const CommodityListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member CommodityId.
   * @param c_commodityId Value to set
   */
  void setCommodityId(const xs_unsignedInt &c_commodityId);

  /**
   * Returns const reference to member CommodityId.
   * @return const reference to member commodityId
   */
  const xs_unsignedInt &getCommodityId() const;

  /**
   * Returns if member CommodityId is set.
   * @retval true member CommodityId is set
   * @retval false member CommodityId is not set
   */
  bool getCommodityIdIsSet() const;

  /**
   * Unsets member CommodityId
   */
  void cleanCommodityId();

  /**
   * Set member CommodityType.
   * @param c_commodityType Value to set
   */
  void setCommodityType(const CommodityType &c_commodityType);

  /**
   * Returns const reference to member CommodityType.
   * @return const reference to member commodityType
   */
  const CommodityType &getCommodityType() const;

  /**
   * Returns if member CommodityType is set.
   * @retval true member CommodityType is set
   * @retval false member CommodityType is not set
   */
  bool getCommodityTypeIsSet() const;

  /**
   * Unsets member CommodityType
   */
  void cleanCommodityType();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const CommodityData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_commodityIdIsSet;
  xs_unsignedInt m_commodityId;

  bool m_commodityTypeIsSet;
  CommodityType m_commodityType;
};

//! typedef for non-const smart pointer type CommodityListDataSelectors
using CommodityListDataSelectorsPtr =
    std::shared_ptr<CommodityListDataSelectors>;

//! typedef for const type CommodityListDataSelectors
using CommodityListDataSelectorsConst = const CommodityListDataSelectors;

//! typedef for const type CommodityListDataSelectors
using CommodityListDataSelectorsConstPtr =
    std::shared_ptr<CommodityListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_COMMODITYLISTDATASELECTORS_H_