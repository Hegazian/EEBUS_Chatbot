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

#ifndef KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGCALLELEMENTS_H_
#define KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGCALLELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/datatunneling/DataTunnelingHeaderElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDataTunneling
 * @{
 */

/**
 * Declaration DataTunnelingCallElements
 */
class DataTunnelingCallElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  DataTunnelingCallElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_header the member to set
   * @param c_payloadIsSet the member to set
   */
  DataTunnelingCallElements(const DataTunnelingHeaderElements &c_header,
                            xs_boolean c_payloadIsSet);

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
  bool operator==(const DataTunnelingCallElements &c_classObject) const;

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
  bool operator!=(const DataTunnelingCallElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member Header.
   * @param c_header Value to set
   */
  void setHeader(const DataTunnelingHeaderElements &c_header);

  /**
   * Returns const reference to member Header.
   * @return const reference to member header
   */
  const DataTunnelingHeaderElements &getHeader() const;

  /**
   * Returns if member Header is set.
   * @retval true member Header is set
   * @retval false member Header is not set
   */
  bool getHeaderIsSet() const;

  /**
   * Unsets member Header
   */
  void cleanHeader();

  /**
   * Set member Payload.
   */
  void setPayload();

  /**
   * Returns if member Payload is set.
   * @retval true member Payload is set
   * @retval false member Payload is not set
   */
  bool getPayloadIsSet() const;

  /**
   * Unsets member Payload
   */
  void cleanPayload();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_headerIsSet;
  DataTunnelingHeaderElements m_header;

  // ElementTag
  bool m_payloadIsSet;
};

//! typedef for non-const smart pointer type DataTunnelingCallElements
using DataTunnelingCallElementsPtr = std::shared_ptr<DataTunnelingCallElements>;

//! typedef for const type DataTunnelingCallElements
using DataTunnelingCallElementsConst = const DataTunnelingCallElements;

//! typedef for const type DataTunnelingCallElements
using DataTunnelingCallElementsConstPtr =
    std::shared_ptr<DataTunnelingCallElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGCALLELEMENTS_H_