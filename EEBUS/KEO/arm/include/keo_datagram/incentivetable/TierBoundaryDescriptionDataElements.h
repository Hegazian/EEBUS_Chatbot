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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TierBoundaryDescriptionDataElements
 */
class TierBoundaryDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TierBoundaryDescriptionDataElements();

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
  operator==(const TierBoundaryDescriptionDataElements &c_classObject) const;

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
  operator!=(const TierBoundaryDescriptionDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member BoundaryId.
   */
  void setBoundaryId();

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
   */
  void setBoundaryType();

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
   * Set member ValidForTierId.
   */
  void setValidForTierId();

  /**
   * Returns if member ValidForTierId is set.
   * @retval true member ValidForTierId is set
   * @retval false member ValidForTierId is not set
   */
  bool getValidForTierIdIsSet() const;

  /**
   * Unsets member ValidForTierId
   */
  void cleanValidForTierId();

  /**
   * Set member SwitchToTierIdWhenLower.
   */
  void setSwitchToTierIdWhenLower();

  /**
   * Returns if member SwitchToTierIdWhenLower is set.
   * @retval true member SwitchToTierIdWhenLower is set
   * @retval false member SwitchToTierIdWhenLower is not set
   */
  bool getSwitchToTierIdWhenLowerIsSet() const;

  /**
   * Unsets member SwitchToTierIdWhenLower
   */
  void cleanSwitchToTierIdWhenLower();

  /**
   * Set member SwitchToTierIdWhenHigher.
   */
  void setSwitchToTierIdWhenHigher();

  /**
   * Returns if member SwitchToTierIdWhenHigher is set.
   * @retval true member SwitchToTierIdWhenHigher is set
   * @retval false member SwitchToTierIdWhenHigher is not set
   */
  bool getSwitchToTierIdWhenHigherIsSet() const;

  /**
   * Unsets member SwitchToTierIdWhenHigher
   */
  void cleanSwitchToTierIdWhenHigher();

  /**
   * Set member BoundaryUnit.
   */
  void setBoundaryUnit();

  /**
   * Returns if member BoundaryUnit is set.
   * @retval true member BoundaryUnit is set
   * @retval false member BoundaryUnit is not set
   */
  bool getBoundaryUnitIsSet() const;

  /**
   * Unsets member BoundaryUnit
   */
  void cleanBoundaryUnit();

  /**
   * Set member Label.
   */
  void setLabel();

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
   */
  void setDescription();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_boundaryIdIsSet;

  // ElementTag
  bool m_boundaryTypeIsSet;

  // ElementTag
  bool m_validForTierIdIsSet;

  // ElementTag
  bool m_switchToTierIdWhenLowerIsSet;

  // ElementTag
  bool m_switchToTierIdWhenHigherIsSet;

  // ElementTag
  bool m_boundaryUnitIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type TierBoundaryDescriptionDataElements
using TierBoundaryDescriptionDataElementsPtr =
    std::shared_ptr<TierBoundaryDescriptionDataElements>;

//! typedef for const type TierBoundaryDescriptionDataElements
using TierBoundaryDescriptionDataElementsConst =
    const TierBoundaryDescriptionDataElements;

//! typedef for const type TierBoundaryDescriptionDataElements
using TierBoundaryDescriptionDataElementsConstPtr =
    std::shared_ptr<TierBoundaryDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TIERBOUNDARYDESCRIPTIONDATAELEMENTS_H_