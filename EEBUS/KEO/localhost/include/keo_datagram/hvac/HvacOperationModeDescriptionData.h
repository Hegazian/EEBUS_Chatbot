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

#ifndef KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/hvac/HvacOperationModeDescriptionDataElements.h>
#include <keo_datagram/hvac/HvacOperationModeType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacOperationModeDescriptionData
 */
class HvacOperationModeDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  HvacOperationModeDescriptionData();

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
  bool operator==(const HvacOperationModeDescriptionData &c_classObject) const;

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
  bool operator!=(const HvacOperationModeDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member OperationModeId.
   * @param c_operationModeId Value to set
   */
  void setOperationModeId(const xs_unsignedInt &c_operationModeId);

  /**
   * Returns const reference to member OperationModeId.
   * @return const reference to member operationModeId
   */
  const xs_unsignedInt &getOperationModeId() const;

  /**
   * Returns if member OperationModeId is set.
   * @retval true member OperationModeId is set
   * @retval false member OperationModeId is not set
   */
  bool getOperationModeIdIsSet() const;

  /**
   * Unsets member OperationModeId
   */
  void cleanOperationModeId();

  /**
   * Set member OperationModeType.
   * @param c_operationModeType Value to set
   */
  void setOperationModeType(const HvacOperationModeType &c_operationModeType);

  /**
   * Returns const reference to member OperationModeType.
   * @return const reference to member operationModeType
   */
  const HvacOperationModeType &getOperationModeType() const;

  /**
   * Returns if member OperationModeType is set.
   * @retval true member OperationModeType is set
   * @retval false member OperationModeType is not set
   */
  bool getOperationModeTypeIsSet() const;

  /**
   * Unsets member OperationModeType
   */
  void cleanOperationModeType();

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
  HvacOperationModeDescriptionData
  reduce(const HvacOperationModeDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_operationModeIdIsSet;
  xs_unsignedInt m_operationModeId;

  bool m_operationModeTypeIsSet;
  HvacOperationModeType m_operationModeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type HvacOperationModeDescriptionData
using HvacOperationModeDescriptionDataPtr =
    std::shared_ptr<HvacOperationModeDescriptionData>;

//! typedef for const type HvacOperationModeDescriptionData
using HvacOperationModeDescriptionDataConst =
    const HvacOperationModeDescriptionData;

//! typedef for const type HvacOperationModeDescriptionData
using HvacOperationModeDescriptionDataConstPtr =
    std::shared_ptr<HvacOperationModeDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONDATA_H_