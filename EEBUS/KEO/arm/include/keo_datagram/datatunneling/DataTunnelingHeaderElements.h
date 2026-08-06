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

#ifndef KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGHEADERELEMENTS_H_
#define KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGHEADERELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramDataTunneling
 * @{
 */

/**
 * Declaration DataTunnelingHeaderElements
 */
class DataTunnelingHeaderElements : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  DataTunnelingHeaderElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_purposeIdIsSet the member to set
   * @param c_channelIdIsSet the member to set
   * @param c_sequenceIdIsSet the member to set
   */
  DataTunnelingHeaderElements(xs_boolean c_purposeIdIsSet,
                              xs_boolean c_channelIdIsSet,
                              xs_boolean c_sequenceIdIsSet);

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
  bool operator==(const DataTunnelingHeaderElements &c_classObject) const;

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
  bool operator!=(const DataTunnelingHeaderElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member PurposeId.
   */
  void setPurposeId();

  /**
   * Returns if member PurposeId is set.
   * @retval true member PurposeId is set
   * @retval false member PurposeId is not set
   */
  bool getPurposeIdIsSet() const;

  /**
   * Unsets member PurposeId
   */
  void cleanPurposeId();

  /**
   * Set member ChannelId.
   */
  void setChannelId();

  /**
   * Returns if member ChannelId is set.
   * @retval true member ChannelId is set
   * @retval false member ChannelId is not set
   */
  bool getChannelIdIsSet() const;

  /**
   * Unsets member ChannelId
   */
  void cleanChannelId();

  /**
   * Set member SequenceId.
   */
  void setSequenceId();

  /**
   * Returns if member SequenceId is set.
   * @retval true member SequenceId is set
   * @retval false member SequenceId is not set
   */
  bool getSequenceIdIsSet() const;

  /**
   * Unsets member SequenceId
   */
  void cleanSequenceId();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_purposeIdIsSet;

  // ElementTag
  bool m_channelIdIsSet;

  // ElementTag
  bool m_sequenceIdIsSet;
};

//! typedef for non-const smart pointer type DataTunnelingHeaderElements
using DataTunnelingHeaderElementsPtr =
    std::shared_ptr<DataTunnelingHeaderElements>;

//! typedef for const type DataTunnelingHeaderElements
using DataTunnelingHeaderElementsConst = const DataTunnelingHeaderElements;

//! typedef for const type DataTunnelingHeaderElements
using DataTunnelingHeaderElementsConstPtr =
    std::shared_ptr<DataTunnelingHeaderElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DATATUNNELING_DATATUNNELINGHEADERELEMENTS_H_