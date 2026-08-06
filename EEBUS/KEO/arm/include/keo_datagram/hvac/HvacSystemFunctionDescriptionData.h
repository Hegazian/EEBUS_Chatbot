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

#ifndef KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/hvac/HvacSystemFunctionDescriptionDataElements.h>
#include <keo_datagram/hvac/HvacSystemFunctionType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacSystemFunctionDescriptionData
 */
class HvacSystemFunctionDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  HvacSystemFunctionDescriptionData();

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
  bool operator==(const HvacSystemFunctionDescriptionData &c_classObject) const;

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
  bool operator!=(const HvacSystemFunctionDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member SystemFunctionId.
   * @param c_systemFunctionId Value to set
   */
  void setSystemFunctionId(const xs_unsignedInt &c_systemFunctionId);

  /**
   * Returns const reference to member SystemFunctionId.
   * @return const reference to member systemFunctionId
   */
  const xs_unsignedInt &getSystemFunctionId() const;

  /**
   * Returns if member SystemFunctionId is set.
   * @retval true member SystemFunctionId is set
   * @retval false member SystemFunctionId is not set
   */
  bool getSystemFunctionIdIsSet() const;

  /**
   * Unsets member SystemFunctionId
   */
  void cleanSystemFunctionId();

  /**
   * Set member SystemFunctionType.
   * @param c_systemFunctionType Value to set
   */
  void
  setSystemFunctionType(const HvacSystemFunctionType &c_systemFunctionType);

  /**
   * Returns const reference to member SystemFunctionType.
   * @return const reference to member systemFunctionType
   */
  const HvacSystemFunctionType &getSystemFunctionType() const;

  /**
   * Returns if member SystemFunctionType is set.
   * @retval true member SystemFunctionType is set
   * @retval false member SystemFunctionType is not set
   */
  bool getSystemFunctionTypeIsSet() const;

  /**
   * Unsets member SystemFunctionType
   */
  void cleanSystemFunctionType();

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
  HvacSystemFunctionDescriptionData
  reduce(const HvacSystemFunctionDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_systemFunctionIdIsSet;
  xs_unsignedInt m_systemFunctionId;

  bool m_systemFunctionTypeIsSet;
  HvacSystemFunctionType m_systemFunctionType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type HvacSystemFunctionDescriptionData
using HvacSystemFunctionDescriptionDataPtr =
    std::shared_ptr<HvacSystemFunctionDescriptionData>;

//! typedef for const type HvacSystemFunctionDescriptionData
using HvacSystemFunctionDescriptionDataConst =
    const HvacSystemFunctionDescriptionData;

//! typedef for const type HvacSystemFunctionDescriptionData
using HvacSystemFunctionDescriptionDataConstPtr =
    std::shared_ptr<HvacSystemFunctionDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDESCRIPTIONDATA_H_