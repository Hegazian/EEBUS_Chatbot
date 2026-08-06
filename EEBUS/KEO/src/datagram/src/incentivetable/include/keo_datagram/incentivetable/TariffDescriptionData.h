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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TariffDescriptionDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffDescriptionData
 */
class TariffDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  TariffDescriptionData();

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
  bool operator==(const TariffDescriptionData &c_classObject) const;

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
  bool operator!=(const TariffDescriptionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member MeasurementId.
   * @param c_measurementId Value to set
   */
  void setMeasurementId(const xs_unsignedInt &c_measurementId);

  /**
   * Returns const reference to member MeasurementId.
   * @return const reference to member measurementId
   */
  const xs_unsignedInt &getMeasurementId() const;

  /**
   * Returns if member MeasurementId is set.
   * @retval true member MeasurementId is set
   * @retval false member MeasurementId is not set
   */
  bool getMeasurementIdIsSet() const;

  /**
   * Unsets member MeasurementId
   */
  void cleanMeasurementId();

  /**
   * Set member TariffWriteable.
   * @param c_tariffWriteable Value to set
   */
  void setTariffWriteable(const xs_boolean &c_tariffWriteable);

  /**
   * Returns const reference to member TariffWriteable.
   * @return const reference to member tariffWriteable
   */
  const xs_boolean &getTariffWriteable() const;

  /**
   * Returns if member TariffWriteable is set.
   * @retval true member TariffWriteable is set
   * @retval false member TariffWriteable is not set
   */
  bool getTariffWriteableIsSet() const;

  /**
   * Unsets member TariffWriteable
   */
  void cleanTariffWriteable();

  /**
   * Set member UpdateRequired.
   * @param c_updateRequired Value to set
   */
  void setUpdateRequired(const xs_boolean &c_updateRequired);

  /**
   * Returns const reference to member UpdateRequired.
   * @return const reference to member updateRequired
   */
  const xs_boolean &getUpdateRequired() const;

  /**
   * Returns if member UpdateRequired is set.
   * @retval true member UpdateRequired is set
   * @retval false member UpdateRequired is not set
   */
  bool getUpdateRequiredIsSet() const;

  /**
   * Unsets member UpdateRequired
   */
  void cleanUpdateRequired();

  /**
   * Set member ScopeType.
   * @param c_scopeType Value to set
   */
  void setScopeType(const ScopeType &c_scopeType);

  /**
   * Returns const reference to member ScopeType.
   * @return const reference to member scopeType
   */
  const ScopeType &getScopeType() const;

  /**
   * Returns if member ScopeType is set.
   * @retval true member ScopeType is set
   * @retval false member ScopeType is not set
   */
  bool getScopeTypeIsSet() const;

  /**
   * Unsets member ScopeType
   */
  void cleanScopeType();

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
   * Set member SlotIdSupport.
   * @param c_slotIdSupport Value to set
   */
  void setSlotIdSupport(const xs_boolean &c_slotIdSupport);

  /**
   * Returns const reference to member SlotIdSupport.
   * @return const reference to member slotIdSupport
   */
  const xs_boolean &getSlotIdSupport() const;

  /**
   * Returns if member SlotIdSupport is set.
   * @retval true member SlotIdSupport is set
   * @retval false member SlotIdSupport is not set
   */
  bool getSlotIdSupportIsSet() const;

  /**
   * Unsets member SlotIdSupport
   */
  void cleanSlotIdSupport();

  /**
   * @copydoc CmdData::reduce()
   */
  TariffDescriptionData
  reduce(const TariffDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffIdIsSet;
  xs_unsignedInt m_tariffId;

  bool m_commodityIdIsSet;
  xs_unsignedInt m_commodityId;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_tariffWriteableIsSet;
  xs_boolean m_tariffWriteable;

  bool m_updateRequiredIsSet;
  xs_boolean m_updateRequired;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;

  bool m_slotIdSupportIsSet;
  xs_boolean m_slotIdSupport;
};

//! typedef for non-const smart pointer type TariffDescriptionData
using TariffDescriptionDataPtr = std::shared_ptr<TariffDescriptionData>;

//! typedef for const type TariffDescriptionData
using TariffDescriptionDataConst = const TariffDescriptionData;

//! typedef for const type TariffDescriptionData
using TariffDescriptionDataConstPtr =
    std::shared_ptr<TariffDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFDESCRIPTIONDATA_H_