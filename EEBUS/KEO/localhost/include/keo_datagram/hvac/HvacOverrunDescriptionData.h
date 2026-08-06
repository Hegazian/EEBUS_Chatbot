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

#ifndef KEO_DATAGRAM_HVAC_HVACOVERRUNDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_HVAC_HVACOVERRUNDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/hvac/HvacOverrunDescriptionDataElements.h>
#include <keo_datagram/hvac/HvacOverrunType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacOverrunDescriptionData
 */
class HvacOverrunDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  HvacOverrunDescriptionData();

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
  bool operator==(const HvacOverrunDescriptionData &c_classObject) const;

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
  bool operator!=(const HvacOverrunDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member OverrunId.
   * @param c_overrunId Value to set
   */
  void setOverrunId(const xs_unsignedInt &c_overrunId);

  /**
   * Returns const reference to member OverrunId.
   * @return const reference to member overrunId
   */
  const xs_unsignedInt &getOverrunId() const;

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
   * @param c_overrunType Value to set
   */
  void setOverrunType(const HvacOverrunType &c_overrunType);

  /**
   * Returns const reference to member OverrunType.
   * @return const reference to member overrunType
   */
  const HvacOverrunType &getOverrunType() const;

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
   * @param c_affectedSystemFunctionId Value to set
   */
  void setAffectedSystemFunctionId(
      const std::vector<xs_unsignedInt> &c_affectedSystemFunctionId);

  /**
   * Returns const reference to member AffectedSystemFunctionId.
   * @return const reference to member affectedSystemFunctionId
   */
  const std::vector<xs_unsignedInt> &getAffectedSystemFunctionId() const;

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
  HvacOverrunDescriptionData
  reduce(const HvacOverrunDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_overrunIdIsSet;
  xs_unsignedInt m_overrunId;

  bool m_overrunTypeIsSet;
  HvacOverrunType m_overrunType;

  bool m_affectedSystemFunctionIdIsSet;
  std::vector<xs_unsignedInt> m_affectedSystemFunctionId;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type HvacOverrunDescriptionData
using HvacOverrunDescriptionDataPtr =
    std::shared_ptr<HvacOverrunDescriptionData>;

//! typedef for const type HvacOverrunDescriptionData
using HvacOverrunDescriptionDataConst = const HvacOverrunDescriptionData;

//! typedef for const type HvacOverrunDescriptionData
using HvacOverrunDescriptionDataConstPtr =
    std::shared_ptr<HvacOverrunDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACOVERRUNDESCRIPTIONDATA_H_