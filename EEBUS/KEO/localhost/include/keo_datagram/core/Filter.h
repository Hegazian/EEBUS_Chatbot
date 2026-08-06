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

#ifndef KEO_DATAGRAM_CORE_FILTER_H_
#define KEO_DATAGRAM_CORE_FILTER_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdControl.h>
#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration Filter
 */
class Filter : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  Filter();

  Filter(const Filter &c_classObject);
  Filter(Filter &&c_classObject);

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
  bool operator==(const Filter &c_classObject) const;

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
  bool operator!=(const Filter &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  Filter &operator=(const Filter &c_classObject);
  Filter &operator=(Filter &&c_classObject);

  /**
   * Set member FilterId.
   * @param c_filterId Value to set
   */
  void setFilterId(const xs_unsignedInt &c_filterId);

  /**
   * Returns const reference to member FilterId.
   * @return const reference to member filterId
   */
  const xs_unsignedInt &getFilterId() const;

  /**
   * Returns if member FilterId is set.
   * @retval true member FilterId is set
   * @retval false member FilterId is not set
   */
  bool getFilterIdIsSet() const;

  /**
   * Unsets member FilterId
   */
  void cleanFilterId();

  /**
   * Set member CmdControl.
   * @param c_cmdControl Value to set
   */
  void setCmdControl(const CmdControl &c_cmdControl);

  /**
   * Returns const reference to member CmdControl.
   * @return const reference to member cmdControl
   */
  const CmdControl &getCmdControl() const;

  /**
   * Returns if member CmdControl is set.
   * @retval true member CmdControl is set
   * @retval false member CmdControl is not set
   */
  bool getCmdControlIsSet() const;

  /**
   * Unsets member CmdControl
   */
  void cleanCmdControl();

  void setDataSelectors(const std::vector<DataSelectorsPtr> &dataSelectors);
  const std::vector<DataSelectorsPtr> &getDataSelectors() const;

  /**
   * Returns if member DataSelectors is set.
   * @retval true member DataSelectors is set
   * @retval false member DataSelectors is not set
   */
  bool getDataSelectorsIsSet() const;

  /**
   * Unsets member DataSelectors
   */
  void cleanDataSelectors();

  /**
   * Set member DataElements.
   * @param dataElements Value to set
   */
  void setDataElements(const DataElementsPtr &dataElements);

  /**
   * Returns member DataElements.
   * @return member dataElements
   */
  DataElementsPtr getDataElements() const;

  /**
   * Returns if member DataElements is set.
   * @retval true member DataElements is set
   * @retval false member DataElements is not set
   */
  bool getDataElementsIsSet() const;

  /**
   * Unsets member DataElements
   */
  void cleanDataElements();

  /**
   * \deprecated Use getDataSelectorsIsSet() instead.
   */
  bool getSelectorsListIsSet() const;

  /**
   * \deprecated Use getDataSelectors() instead.
   */
  const std::vector<DataSelectorsPtr> &getSelectorsList() const;

  /**
   * \deprecated Use setDataSelectors() instead.
   */
  void setSelectorsList(const std::vector<DataSelectorsPtr> &dataSelectors);

  /**
   * \deprecated Use getDataElements() instead.
   */
  DataElementsPtr getElement() const;

  /**
   * \deprecated Use getDataElementsIsSet() instead.
   */
  bool getElementIsSet() const;

  /**
   * \deprecated Use setDataElements() instead.
   */
  void setElement(DataElementsPtr dataElements);

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_filterIdIsSet;
  xs_unsignedInt m_filterId;

  bool m_cmdControlIsSet;
  CmdControl m_cmdControl;

  bool m_dataSelectorsIsSet;
  std::vector<DataSelectorsPtr> m_dataSelectors;

  bool m_dataElementsIsSet;
  DataElementsPtr m_dataElements;
};

//! typedef for non-const smart pointer type Filter
using FilterPtr = std::shared_ptr<Filter>;

//! typedef for const type Filter
using FilterConst = const Filter;

//! typedef for const type Filter
using FilterConstPtr = std::shared_ptr<FilterConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_FILTER_H_