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

#ifndef KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONDATA_H_
#define KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/identification/IdentificationDataElements.h>
#include <keo_datagram/identification/IdentificationType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIdentification
 * @{
 */

/**
 * Declaration IdentificationData
 */
class IdentificationData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  IdentificationData();

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
  bool operator==(const IdentificationData &c_classObject) const;

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
  bool operator!=(const IdentificationData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

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
   * Set member IdentificationValue.
   * @param c_identificationValue Value to set
   */
  void setIdentificationValue(const xs_string &c_identificationValue);

  /**
   * Returns const reference to member IdentificationValue.
   * @return const reference to member identificationValue
   */
  const xs_string &getIdentificationValue() const;

  /**
   * Returns if member IdentificationValue is set.
   * @retval true member IdentificationValue is set
   * @retval false member IdentificationValue is not set
   */
  bool getIdentificationValueIsSet() const;

  /**
   * Unsets member IdentificationValue
   */
  void cleanIdentificationValue();

  /**
   * Set member Authorized.
   * @param c_authorized Value to set
   */
  void setAuthorized(const xs_boolean &c_authorized);

  /**
   * Returns const reference to member Authorized.
   * @return const reference to member authorized
   */
  const xs_boolean &getAuthorized() const;

  /**
   * Returns if member Authorized is set.
   * @retval true member Authorized is set
   * @retval false member Authorized is not set
   */
  bool getAuthorizedIsSet() const;

  /**
   * Unsets member Authorized
   */
  void cleanAuthorized();

  /**
   * @copydoc CmdData::reduce()
   */
  IdentificationData reduce(const IdentificationDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_identificationIdIsSet;
  xs_unsignedInt m_identificationId;

  bool m_identificationTypeIsSet;
  IdentificationType m_identificationType;

  bool m_identificationValueIsSet;
  xs_string m_identificationValue;

  bool m_authorizedIsSet;
  xs_boolean m_authorized;
};

//! typedef for non-const smart pointer type IdentificationData
using IdentificationDataPtr = std::shared_ptr<IdentificationData>;

//! typedef for const type IdentificationData
using IdentificationDataConst = const IdentificationData;

//! typedef for const type IdentificationData
using IdentificationDataConstPtr = std::shared_ptr<IdentificationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONDATA_H_