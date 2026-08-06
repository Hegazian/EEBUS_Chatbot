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

#ifndef KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/identification/IdentificationType.h>

#include <keo_datagram/identification/IdentificationData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIdentification
 * @{
 */

/**
 * Declaration IdentificationListDataSelectors
 */
class IdentificationListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  IdentificationListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_identificationId the member to set
   * @param c_identificationType the member to set
   */
  IdentificationListDataSelectors(
      const xs_unsignedInt &c_identificationId,
      const IdentificationType &c_identificationType);

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
  bool operator==(const IdentificationListDataSelectors &c_classObject) const;

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
  bool operator!=(const IdentificationListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member IdentificationId.
   * @param c_identificationId Value to set
   */
  void setIdentificationId(const xs_unsignedInt &c_identificationId);

  /**
   * Returns const reference to member IdentificationId.
   * @return const reference to member identificationId
   */
  const xs_unsignedInt &getIdentificationId() const;

  /**
   * Returns if member IdentificationId is set.
   * @retval true member IdentificationId is set
   * @retval false member IdentificationId is not set
   */
  bool getIdentificationIdIsSet() const;

  /**
   * Unsets member IdentificationId
   */
  void cleanIdentificationId();

  /**
   * Set member IdentificationType.
   * @param c_identificationType Value to set
   */
  void setIdentificationType(const IdentificationType &c_identificationType);

  /**
   * Returns const reference to member IdentificationType.
   * @return const reference to member identificationType
   */
  const IdentificationType &getIdentificationType() const;

  /**
   * Returns if member IdentificationType is set.
   * @retval true member IdentificationType is set
   * @retval false member IdentificationType is not set
   */
  bool getIdentificationTypeIsSet() const;

  /**
   * Unsets member IdentificationType
   */
  void cleanIdentificationType();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const IdentificationData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_identificationIdIsSet;
  xs_unsignedInt m_identificationId;

  bool m_identificationTypeIsSet;
  IdentificationType m_identificationType;
};

//! typedef for non-const smart pointer type IdentificationListDataSelectors
using IdentificationListDataSelectorsPtr =
    std::shared_ptr<IdentificationListDataSelectors>;

//! typedef for const type IdentificationListDataSelectors
using IdentificationListDataSelectorsConst =
    const IdentificationListDataSelectors;

//! typedef for const type IdentificationListDataSelectors
using IdentificationListDataSelectorsConstPtr =
    std::shared_ptr<IdentificationListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONLISTDATASELECTORS_H_