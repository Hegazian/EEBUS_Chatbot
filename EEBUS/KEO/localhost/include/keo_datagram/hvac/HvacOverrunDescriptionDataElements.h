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

#ifndef KEO_DATAGRAM_HVAC_HVACOVERRUNDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_HVAC_HVACOVERRUNDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacOverrunDescriptionDataElements
 */
class HvacOverrunDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  HvacOverrunDescriptionDataElements();

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
  operator==(const HvacOverrunDescriptionDataElements &c_classObject) const;

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
  operator!=(const HvacOverrunDescriptionDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member OverrunId.
   */
  void setOverrunId();

  /**
   * Returns if member OverrunId is set.
   * @retval true member OverrunId is set
   * @retval false member OverrunId is not set
   */
  bool getOverrunIdIsSet() const;

  /**
   * Unsets member OverrunId
   */
  void cleanOverrunId();

  /**
   * Set member OverrunType.
   */
  void setOverrunType();

  /**
   * Returns if member OverrunType is set.
   * @retval true member OverrunType is set
   * @retval false member OverrunType is not set
   */
  bool getOverrunTypeIsSet() const;

  /**
   * Unsets member OverrunType
   */
  void cleanOverrunType();

  /**
   * Set member AffectedSystemFunctionId.
   */
  void setAffectedSystemFunctionId();

  /**
   * Returns if member AffectedSystemFunctionId is set.
   * @retval true member AffectedSystemFunctionId is set
   * @retval false member AffectedSystemFunctionId is not set
   */
  bool getAffectedSystemFunctionIdIsSet() const;

  /**
   * Unsets member AffectedSystemFunctionId
   */
  void cleanAffectedSystemFunctionId();

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
  bool m_overrunIdIsSet;

  // ElementTag
  bool m_overrunTypeIsSet;

  // ElementTag
  bool m_affectedSystemFunctionIdIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type HvacOverrunDescriptionDataElements
using HvacOverrunDescriptionDataElementsPtr =
    std::shared_ptr<HvacOverrunDescriptionDataElements>;

//! typedef for const type HvacOverrunDescriptionDataElements
using HvacOverrunDescriptionDataElementsConst =
    const HvacOverrunDescriptionDataElements;

//! typedef for const type HvacOverrunDescriptionDataElements
using HvacOverrunDescriptionDataElementsConstPtr =
    std::shared_ptr<HvacOverrunDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACOVERRUNDESCRIPTIONDATAELEMENTS_H_