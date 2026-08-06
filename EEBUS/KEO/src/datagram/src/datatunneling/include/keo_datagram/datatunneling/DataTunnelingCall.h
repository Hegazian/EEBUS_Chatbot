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

#ifndef KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGCALL_H_
#define KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGCALL_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/KeoByteArray.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/datatunneling/DataTunnelingHeader.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDataTunneling
 * @{
 */

/**
 * Declaration DataTunnelingCall
 */
class DataTunnelingCall : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  DataTunnelingCall();

  /**
   * Construct an instance of this class and set its member.
   * @param c_header the member to set
   * @param c_payload the member to set
   */
  DataTunnelingCall(const DataTunnelingHeader &c_header,
                    const xs_hexBinary &c_payload);

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
  bool operator==(const DataTunnelingCall &c_classObject) const;

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
  bool operator!=(const DataTunnelingCall &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member Header.
   * @param c_header Value to set
   */
  void setHeader(const DataTunnelingHeader &c_header);

  /**
   * Returns const reference to member Header.
   * @return const reference to member header
   */
  const DataTunnelingHeader &getHeader() const;

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
   * @param c_payload Value to set
   */
  void setPayload(const xs_hexBinary &c_payload);

  /**
   * Returns const reference to member Payload.
   * @return const reference to member payload
   */
  const xs_hexBinary &getPayload() const;

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_headerIsSet;
  DataTunnelingHeader m_header;

  bool m_payloadIsSet;
  xs_hexBinary m_payload;
};

//! typedef for non-const smart pointer type DataTunnelingCall
using DataTunnelingCallPtr = std::shared_ptr<DataTunnelingCall>;

//! typedef for const type DataTunnelingCall
using DataTunnelingCallConst = const DataTunnelingCall;

//! typedef for const type DataTunnelingCall
using DataTunnelingCallConstPtr = std::shared_ptr<DataTunnelingCallConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGCALL_H_