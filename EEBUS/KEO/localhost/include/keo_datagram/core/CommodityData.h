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

#ifndef KEO_DATAGRAM_CORE_COMMODITYDATA_H_
#define KEO_DATAGRAM_CORE_COMMODITYDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CommodityDataElements.h>
#include <keo_datagram/core/CommodityType.h>
#include <keo_datagram/core/EnergyDirection.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration CommodityData
 */
class CommodityData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  CommodityData();

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
  bool operator==(const CommodityData &c_classObject) const;

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
  bool operator!=(const CommodityData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member PositiveEnergyDirection.
   * @param c_positiveEnergyDirection Value to set
   */
  void
  setPositiveEnergyDirection(const EnergyDirection &c_positiveEnergyDirection);

  /**
   * Returns const reference to member PositiveEnergyDirection.
   * @return const reference to member positiveEnergyDirection
   */
  const EnergyDirection &getPositiveEnergyDirection() const;

  /**
   * Returns if member PositiveEnergyDirection is set.
   * @retval true member PositiveEnergyDirection is set
   * @retval false member PositiveEnergyDirection is not set
   */
  bool getPositiveEnergyDirectionIsSet() const;

  /**
   * Unsets member PositiveEnergyDirection
   */
  void cleanPositiveEnergyDirection();

  /**
   * Set member Label.
   * @param c_label Value to set
   */
  void setLabel(const xs_string &c_label);

  /**
   * Returns const reference to member Label.
   * @return const reference to member label
   */
  const xs_string &getLabel() const;

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

  /**
   * @copydoc CmdData::reduce()
   */
  CommodityData reduce(const CommodityDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_commodityIdIsSet;
  xs_unsignedInt m_commodityId;

  bool m_commodityTypeIsSet;
  CommodityType m_commodityType;

  bool m_positiveEnergyDirectionIsSet;
  EnergyDirection m_positiveEnergyDirection;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type CommodityData
using CommodityDataPtr = std::shared_ptr<CommodityData>;

//! typedef for const type CommodityData
using CommodityDataConst = const CommodityData;

//! typedef for const type CommodityData
using CommodityDataConstPtr = std::shared_ptr<CommodityDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_COMMODITYDATA_H_