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

#ifndef KEO_DATAGRAM_CORE_KEOJSONTRANSFORMATION_H_
#define KEO_DATAGRAM_CORE_KEOJSONTRANSFORMATION_H_

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */
#include <keo_datagram/core/DatagramParserException.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/SpineEnumClass.h>

#include "KeoJsonValue.h"

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  class definition                                                          *
 * ************************************************************************** */

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

class KeoByteArray;
class KeoDate;
class KeoTime;
class KeoDateTime;
class KeoDuration;
class AbsoluteOrRelativeTime;

class KeoJsonTransformation {
public:
  KeoJsonTransformation() = delete;

  static void appendCommaIfObjectPrecedent(std::string &str);
  static bool hasCorrectOrder(const Json::Value *json,
                              const std::vector<std::string> &correctOrder);

  // ToJson
  static std::string write(const std::string &elementName,
                           const KeoJsonTransformable &value);
  static std::string write(const std::string &elementName,
                           const std::string &target);
  static std::string write(const std::string &elementName,
                           const std::int8_t &target);
  static std::string write(const std::string &elementName,
                           const std::int16_t &target);
  static std::string write(const std::string &elementName,
                           const std::int32_t &target);
  static std::string write(const std::string &elementName,
                           const std::int64_t &target);
  static std::string write(const std::string &elementName,
                           const std::uint8_t &target);
  static std::string write(const std::string &elementName,
                           const std::uint16_t &target);
  static std::string write(const std::string &elementName,
                           const std::uint32_t &target);
  static std::string write(const std::string &elementName,
                           const std::uint64_t &target);
  static std::string write(const std::string &elementName,
                           const SpineEnum &value);
  static std::string write(const std::string &elementName,
                           const KeoByteArray &target);
  static std::string write(const std::string &elementName,
                           const KeoTime &value);
  static std::string write(const std::string &elementName,
                           const KeoDate &value);
  static std::string write(const std::string &elementName,
                           const KeoDateTime &value);
  static std::string write(const std::string &elementName,
                           const KeoDuration &value);
  static std::string write(const std::string &elementName,
                           const AbsoluteOrRelativeTime &value);
  static std::string write(const std::string &elementName, const bool &value);
  static std::string writeTag(const std::string &elementName);

  template <typename T,
            typename std::enable_if<std::is_same<std::uint32_t, T>::value>::type
                * = nullptr>
  static std::string writeList(const std::string &keyname,
                               const std::vector<std::uint32_t> &value) {
    std::string result = KeoJsonTransformation::startElement(keyname);
    result += "[";
    for (const auto &element : value) {
      result += std::to_string(element);
      if (&element != &value.back()) {
        result += ",";
      }
    }
    result += "]";
    result += "}";
    return result;
  }

  template <typename T,
            typename std::enable_if<std::is_same<std::string, T>::value>::type
                * = nullptr>
  static std::string writeList(const std::string &keyname,
                               const std::vector<std::string> &value) {
    std::string result = KeoJsonTransformation::startElement(keyname);
    result += "[";
    for (const auto &element : value) {
      result += "\"" + element + "\"";
      if (&element != &value.back()) {
        result += ",";
      }
    }
    result += "]";
    result += "}";
    return result;
  }

  template <typename T, typename std::enable_if<std::is_base_of<
                            KeoJsonTransformable, T>::value>::type * = nullptr>
  static std::string writeList(const std::string &keyname,
                               const std::vector<T> &value) {
    std::string result = KeoJsonTransformation::startElement(keyname);
    result += "[";
    for (const auto &element : value) {
      result += static_cast<const KeoJsonTransformable *>(&element)->toJson();
      if (&element != &value.back()) {
        result += ",";
      }
    }
    result += "]";
    result += "}";
    return result;
  }

  template <
      typename T,
      typename std::enable_if<std::is_convertible<
          T, std::shared_ptr<KeoJsonTransformable>>::value>::type * = nullptr>
  static std::string writeList(const std::string &keyname,
                               const std::vector<T> &value) {
    std::string result = KeoJsonTransformation::startElement(keyname);
    result += "[";
    for (const auto &element : value) {
      result += element->toJson();
      if (&element != &value.back()) {
        result += ",";
      }
    }
    result += "]";
    result += "}";
    return result;
  }

  template <typename T,
            typename std::enable_if<std::is_base_of<SpineEnum, T>::value>::type
                * = nullptr>
  static std::string writeList(const std::string &keyname,
                               const std::vector<T> &value) {
    std::string result = KeoJsonTransformation::startElement(keyname);
    result += "[";
    for (const auto &element : value) {
      result += "\"" + element.toString() + "\"";
      if (&element != &value.back()) {
        result += ",";
      }
    }
    result += "]";
    result += "}";
    return result;
  }

  // FromJson
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  KeoJsonTransformable *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::string *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::int8_t *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::int16_t *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::int32_t *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::int64_t *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::uint8_t *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::uint16_t *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::uint32_t *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  std::uint64_t *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  SpineEnum *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  KeoByteArray *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  KeoDate *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  KeoTime *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  KeoDateTime *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  KeoDuration *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  AbsoluteOrRelativeTime *target);
  static bool get(KeoJsonValue *json, const std::string &elementName,
                  bool *target);
  static bool isTag(KeoJsonValue *json, const std::string &elementName);

  template <typename T,
            typename std::enable_if<std::is_same<std::string, T>::value>::type
                * = nullptr>
  static bool getList(KeoJsonValue *json, const std::string &elementName,
                      std::vector<std::string> *target) {
    if (json->isObject()) {
      if (json->isMember(elementName)) {
        if ((*json)[elementName].isArray()) {
          for (const auto &listElement : (*json)[elementName]) {
            if (listElement.isString()) {
              target->push_back(listElement.asString());
            } else {
              throw DatagramParserException("Could not parse element <" +
                                            elementName +
                                            "> (expected array of strings)");
            }
          }
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (expected array)");
        }
      } else {
        return false;
      }
    } else {
      throw DatagramParserException("Could not parse element <" + elementName +
                                    "> (expected object)");
    }
  }

  template <typename T,
            typename std::enable_if<std::is_same<std::uint32_t, T>::value>::type
                * = nullptr>
  static bool getList(KeoJsonValue *json, const std::string &elementName,
                      std::vector<std::uint32_t> *target) {
    if (json->isObject()) {
      if (json->isMember(elementName)) {
        if ((*json)[elementName].isArray()) {
          for (const auto &listElement : (*json)[elementName]) {
            uint64_t numberFromJson = listElement.asUInt64();
            std::uint32_t numberCasted =
                static_cast<std::uint32_t>(listElement.asUInt64());
            if (numberFromJson == static_cast<uint64_t>(numberCasted)) {
              target->push_back(numberCasted);
            } else {
              throw DatagramParserException("Could not parse element <" +
                                            elementName + "> (overflow)");
            }
          }
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (expected array)");
        }
      } else {
        return false;
      }
    } else {
      throw DatagramParserException("Could not parse element <" + elementName +
                                    "> (expected object)");
    }
  }

  template <typename T, typename std::enable_if<std::is_base_of<
                            KeoJsonTransformable, T>::value>::type * = nullptr>
  static bool getList(KeoJsonValue *json, const std::string &elementName,
                      std::vector<T> *target) {
    if (json->isObject()) {
      if (json->isMember(elementName)) {
        if ((*json)[elementName].isArray()) {
          for (auto &element : (*json)[elementName]) {
            T tmp;
            try {
              if (static_cast<KeoJsonTransformable *>(&tmp)->fromJson(
                      static_cast<KeoJsonValue *>(&element))) {
                target->push_back(std::move(tmp));
              } else {
                throw DatagramParserException("Could not parse element <" +
                                              elementName + ">");
              }
            } catch (DatagramParserException &e) {
              e.append("Could not parse element <" + elementName + ">");
              throw;
            }
          }
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (expected array)");
        }
      } else {
        return false;
      }
    } else {
      throw DatagramParserException("Could not parse element <" + elementName +
                                    "> (expected object)");
    }
  }

  template <
      typename T,
      typename std::enable_if<std::is_convertible<
          T, std::shared_ptr<KeoJsonTransformable>>::value>::type * = nullptr>
  static bool getList(KeoJsonValue *json, const std::string &elementName,
                      std::vector<T> *target) {
    if (json->isObject()) {
      if (json->isMember(elementName)) {
        if ((*json)[elementName].isArray()) {
          for (auto &element : (*json)[elementName]) {
            T tmp;
            if (tmp->fromJson(static_cast<KeoJsonValue *>(&element))) {
              target->push_back(tmp);
            } else {
              throw DatagramParserException("Could not parse element <" +
                                            elementName + ">");
            }
          }
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (expected array)");
        }
      } else {
        return false;
      }
    } else {
      throw DatagramParserException("Could not parse element <" + elementName +
                                    "> (expected object)");
    }
  }

  template <typename T,
            typename std::enable_if<std::is_base_of<SpineEnum, T>::value>::type
                * = nullptr>
  static bool getList(KeoJsonValue *json, const std::string &elementName,
                      std::vector<T> *target) {
    if (json->isObject()) {
      if (json->isMember(elementName)) {
        if ((*json)[elementName].isArray()) {
          for (const auto &element : (*json)[elementName]) {
            if (element.isString()) {
              T tmp;
              if (tmp.setFromString(element.asString())) {
                target->push_back(tmp);
              } else {
                throw DatagramParserException("Could not parse element <" +
                                              elementName + ">");
              }
            } else {
              throw DatagramParserException("Could not parse element <" +
                                            elementName +
                                            "> (expected string)");
            }
          }
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (expected array)");
        }
      } else {
        return false;
      }
    } else {
      throw DatagramParserException("Could not parse element <" + elementName +
                                    "> (expected object)");
    }
  }

private:
  static std::string startElement(const std::string &elementName);

  template <typename T>
  static bool getUInt(KeoJsonValue *json, const std::string &elementName,
                      T *target);
  template <typename T>
  static bool getInt(KeoJsonValue *json, const std::string &elementName,
                     T *target);
};

/** @}
 */

} // end namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_KEOJSONTRANSFORMATION_H_