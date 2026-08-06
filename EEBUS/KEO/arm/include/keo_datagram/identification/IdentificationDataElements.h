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

#ifndef KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONDATAELEMENTS_H_
#define KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIdentification
 * @{
 */

/**
 * Declaration IdentificationDataElements
 */
class IdentificationDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  IdentificationDataElements();

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
  bool operator==(const IdentificationDataElements &c_classObject) const;

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
  bool operator!=(const IdentificationDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member IdentificationId.
   */
  void setIdentificationId();

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
   */
  void setIdentificationType();

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
   */
  void setIdentificationValue();

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
   */
  void setAuthorized();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_identificationIdIsSet;

  // ElementTag
  bool m_identificationTypeIsSet;

  // ElementTag
  bool m_identificationValueIsSet;

  // ElementTag
  bool m_authorizedIsSet;
};

//! typedef for non-const smart pointer type IdentificationDataElements
using IdentificationDataElementsPtr =
    std::shared_ptr<IdentificationDataElements>;

//! typedef for const type IdentificationDataElements
using IdentificationDataElementsConst = const IdentificationDataElements;

//! typedef for const type IdentificationDataElements
using IdentificationDataElementsConstPtr =
    std::shared_ptr<IdentificationDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONDATAELEMENTS_H_