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

#ifndef KEO_DATAGRAM_CORE_CMD_H_
#define KEO_DATAGRAM_CORE_CMD_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/Filter.h>
#include <keo_datagram/core/Function.h>
#include <keo_datagram/core/KeoByteArray.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration Cmd
 */
class Cmd : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  Cmd();

  explicit Cmd(const CmdDataPtr &c_cmdData);

  /**
   * Construct a Cmd and try to create appropriate CmdData for the given type.
   *
   * If you find yourself calling this method with a constant type, e.g.
   *     keo_datagram::Cmd(keo_datagram::CmdData::Type::MEASUREMENT_LIST_DATA_TYPE);
   * you should instead create the CmdData directly, i.e.
   *     keo_datagram::Cmd(std::make_shared<keo_datagram::MeasurementListData>());
   * This way missing datagram library plugins can be identified easier and
   * earlier.
   *
   * If you really need to use this constructor, make sure to check that the
   * CmdData
   * has been created successfully.
   */
  explicit Cmd(const CmdData::Type type);

  Cmd(const Cmd &c_classObject);
  Cmd(Cmd &&c_classObject);

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
  bool operator==(const Cmd &c_classObject) const;

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
  bool operator!=(const Cmd &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  Cmd &operator=(const Cmd &c_classObject);
  Cmd &operator=(Cmd &&c_classObject);

  /**
   * Set member Function.
   * @param c_function Value to set
   */
  void setFunction(const Function &c_function);

  /**
   * Returns const reference to member Function.
   * @return const reference to member function
   */
  const Function &getFunction() const;

  /**
   * Returns if member Function is set.
   * @retval true member Function is set
   * @retval false member Function is not set
   */
  bool getFunctionIsSet() const;

  /**
   * Unsets member Function
   */
  void cleanFunction();

  /**
   * Set member Filter.
   * @param c_filter Value to set
   */
  void setFilter(const std::vector<Filter> &c_filter);

  /**
   * Returns const reference to member Filter.
   * @return const reference to member filter
   */
  const std::vector<Filter> &getFilter() const;

  /**
   * Returns if member Filter is set.
   * @retval true member Filter is set
   * @retval false member Filter is not set
   */
  bool getFilterIsSet() const;

  /**
   * Unsets member Filter
   */
  void cleanFilter();

  /**
   * Set member CmdData.
   * @param cmdData Value to set
   */
  void setCmdData(const CmdDataPtr &cmdData);

  /**
   * Returns member CmdData.
   * @return member cmdData
   */
  CmdDataPtr getCmdData() const;

  /**
   * Returns if member CmdData is set.
   * @retval true member CmdData is set
   * @retval false member CmdData is not set
   */
  bool getCmdDataIsSet() const;

  /**
   * Unsets member CmdData
   */
  void cleanCmdData();

  /**
   * Set member ManufacturerSpecificExtension.
   * @param c_manufacturerSpecificExtension Value to set
   */
  void setManufacturerSpecificExtension(
      const xs_hexBinary &c_manufacturerSpecificExtension);

  /**
   * Returns const reference to member ManufacturerSpecificExtension.
   * @return const reference to member manufacturerSpecificExtension
   */
  const xs_hexBinary &getManufacturerSpecificExtension() const;

  /**
   * Returns if member ManufacturerSpecificExtension is set.
   * @retval true member ManufacturerSpecificExtension is set
   * @retval false member ManufacturerSpecificExtension is not set
   */
  bool getManufacturerSpecificExtensionIsSet() const;

  /**
   * Unsets member ManufacturerSpecificExtension
   */
  void cleanManufacturerSpecificExtension();

  /**
   * Set member LastUpdateAt.
   * @param c_lastUpdateAt Value to set
   */
  void setLastUpdateAt(const AbsoluteOrRelativeTime &c_lastUpdateAt);

  /**
   * Returns const reference to member LastUpdateAt.
   * @return const reference to member lastUpdateAt
   */
  const AbsoluteOrRelativeTime &getLastUpdateAt() const;

  /**
   * Returns if member LastUpdateAt is set.
   * @retval true member LastUpdateAt is set
   * @retval false member LastUpdateAt is not set
   */
  bool getLastUpdateAtIsSet() const;

  /**
   * Unsets member LastUpdateAt
   */
  void cleanLastUpdateAt();

  /**
   * Set the filters on this command.
   * \deprecated Use Cmd::setFilter instead.
   */
  void setCmdFilterList(const std::vector<Filter> &c_data);

  /**
   * Get the type of this instance.
   * @return the type of this instance or UNDEFINED
   */
  CmdData::Type getDataType() const;

  /**
   * \deprecated Use CmdData::getFunctionFromType(CmdData::Type) instead.
   */
  static Function::Value getFunction(CmdData::Type type) {
    return CmdData::getFunctionFromType(type);
  }

  /**
   * \deprecated Use CmdData::getTypeFromFunction(Function::Value) instead.
   */
  static CmdData::Type getSpineDataType(Function::Value value) {
    return CmdData::getTypeFromFunction(value);
  }

  /**
   * Check if at least one filter is set
   */
  bool hasFilters() const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_functionIsSet;
  Function m_function;

  bool m_filterIsSet;
  std::vector<Filter> m_filter;

  bool m_cmdDataIsSet;
  CmdDataPtr m_cmdData;

  bool m_manufacturerSpecificExtensionIsSet;
  xs_hexBinary m_manufacturerSpecificExtension;

  bool m_lastUpdateAtIsSet;
  AbsoluteOrRelativeTime m_lastUpdateAt;
};

//! typedef for non-const smart pointer type Cmd
using CmdPtr = std::shared_ptr<Cmd>;

//! typedef for const type Cmd
using CmdConst = const Cmd;

//! typedef for const type Cmd
using CmdConstPtr = std::shared_ptr<CmdConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_CMD_H_