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

#include <algorithm>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoByteArray.h>
#include <keo_datagram/core/KeoDate.h>
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoTime.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

void KeoJsonTransformation::appendCommaIfObjectPrecedent(std::string &str) {
  if (str.back() == '}') {
    str += ",";
  }
}

bool KeoJsonTransformation::hasCorrectOrder(
    const Json::Value *json, const std::vector<std::string> &correctOrder) {
  if (json->isNull()) {
    // Empty json always has the correct order
    return true;
  } else if (json->isArray()) {
    size_t idx_order = 0U;
    for (auto jsonIter = json->begin(); jsonIter != json->end();
         /* jsonIter is incremented in body */) {
      if (idx_order >= correctOrder.size()) {
        // We ran out of elements in the vector containing the correct order,
        // while we still
        // have elements in the Json. If all remaining elements in the Json are
        // "unknown"
        // elements (elements that are not contained in the correct order) the
        // order is
        // still correct.
        while (jsonIter != json->end()) {
          if (std::find(correctOrder.begin(), correctOrder.end(),
                        jsonIter->getMemberNames()[0]) != correctOrder.end()) {
            return false;
          }
          ++jsonIter;
        }

        return true;
      }

      if (!jsonIter->isObject()) {
        // Json has incorrect structure
        return false;
      } else if (jsonIter->isMember(correctOrder[idx_order])) {
        ++jsonIter;
        ++idx_order;
      } else {
        ++idx_order;
      }
    }
    return true;
  } else {
    // Only an array can have an order
    return false;
  }
}

std::string KeoJsonTransformation::startElement(const std::string &keyname) {
  return "{\"" + keyname + "\":";
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const KeoByteArray &value) {
  std::string result = startElement(keyname);
  result += "\"" + value.toString() + "\"";
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const bool &value) {
  std::string result = startElement(keyname);
  result += (value ? "true" : "false");
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const std::string &value) {
  std::string result = startElement(keyname);
  result += "\"" + value + "\"";
  result += "}";
  return result;
}

std::string KeoJsonTransformation::writeTag(const std::string &keyname) {
  std::string result = startElement(keyname);
  result += "[]";
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const int8_t &value) {
  std::string result = startElement(keyname);
  result += std::to_string(value);
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const std::int16_t &value) {
  std::string result = startElement(keyname);
  result += std::to_string(value);
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const std::int32_t &value) {
  std::string result = startElement(keyname);
  result += std::to_string(value);
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const std::int64_t &value) {
  std::string result = startElement(keyname);
  result += std::to_string(value);
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const std::uint8_t &value) {
  std::string result = startElement(keyname);
  result += std::to_string(value);
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const std::uint16_t &value) {
  std::string result = startElement(keyname);
  result += std::to_string(value);
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const std::uint32_t &value) {
  std::string result = startElement(keyname);
  result += std::to_string(value);
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const std::uint64_t &value) {
  std::string result = startElement(keyname);
  result += std::to_string(value);
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const KeoJsonTransformable &value) {
  std::string result = startElement(keyname);
  result += value.toJson();
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const SpineEnum &value) {
  std::string result = startElement(keyname);
  result += "\"" + value.toString() + "\"";
  result += "}";
  return result;
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const KeoTime &value) {
  if (value.isValid()) {
    std::string result = startElement(keyname);
    result += "\"" + value.toString() + "\"";
    result += "}";
    return result;
  }
  return "";
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const KeoDate &value) {
  if (value.isValid()) {
    std::string result = startElement(keyname);
    result += "\"" + value.toString() + "\"";
    result += "}";
    return result;
  }
  return "";
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const KeoDateTime &value) {
  if (value.isValid()) {
    std::string result = startElement(keyname);
    result += "\"" + value.toString() + "\"";
    result += "}";
    return result;
  }
  return "";
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const KeoDuration &value) {
  if (value.isValid()) {
    std::string result = startElement(keyname);
    result += "\"" + value.toString() + "\"";
    result += "}";
    return result;
  }
  return "";
}

std::string KeoJsonTransformation::write(const std::string &keyname,
                                         const AbsoluteOrRelativeTime &value) {
  if (value.getDuration().isValid()) {
    return KeoJsonTransformation::write(keyname, value.getDuration());
  } else if (value.getDateTime().isValid()) {
    return KeoJsonTransformation::write(keyname, value.getDateTime());
  }
  return "";
}

bool KeoJsonTransformation::isTag(KeoJsonValue *json,
                                  const std::string &elementName) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isArray() && (*json)[elementName].empty()) {
        return true;
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected empty list)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                xs_hexBinary *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isString()) {
        *target = KeoByteArray((*json)[elementName].asString());
        return true;
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected string)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName, bool *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isBool()) {
        *target = (*json)[elementName].asBool();
        return true;
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected boolean)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                std::string *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isString()) {
        *target = std::string((*json)[elementName].asString());
        return true;
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected string)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                KeoJsonTransformable *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isArray()) {
        try {
          if (target->fromJson(
                  static_cast<KeoJsonValue *>(&(*json)[elementName]))) {
            return true;
          } else {
            throw DatagramParserException("Could not parse element <" +
                                          elementName + ">");
          }
        } catch (DatagramParserException &e) {
          e.append("Could not parse element <" + elementName + ">");
          throw;
        }
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

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                int8_t *target) {
  return KeoJsonTransformation::getInt<int8_t>(json, elementName, target);
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                int16_t *target) {
  return KeoJsonTransformation::getInt<int16_t>(json, elementName, target);
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                int32_t *target) {
  return KeoJsonTransformation::getInt<int32_t>(json, elementName, target);
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                int64_t *target) {
  return KeoJsonTransformation::getInt<int64_t>(json, elementName, target);
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                uint8_t *target) {
  return KeoJsonTransformation::getUInt<uint8_t>(json, elementName, target);
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                uint16_t *target) {
  return KeoJsonTransformation::getUInt<uint16_t>(json, elementName, target);
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                uint32_t *target) {
  return KeoJsonTransformation::getUInt<uint32_t>(json, elementName, target);
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                uint64_t *target) {
  return KeoJsonTransformation::getUInt<uint64_t>(json, elementName, target);
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                SpineEnum *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isString()) {
        if (target->setFromString((*json)[elementName].asString())) {
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (invalid format)");
        }
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected string)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                KeoDate *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isString()) {
        KeoDate date = KeoDate::parse((*json)[elementName].asString());
        if (date.isValid()) {
          *target = date;
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (invalid format)");
        }
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected string)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                KeoTime *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isString()) {
        KeoTime parsedTime = KeoTime::parse((*json)[elementName].asString());
        if (parsedTime.isValid()) {
          *target = parsedTime;
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (invalid format)");
        }
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected string)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                KeoDateTime *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isString()) {
        KeoDateTime dateTime =
            KeoDateTime::parse((*json)[elementName].asString());
        if (dateTime.isValid()) {
          *target = dateTime;
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (invalid format)");
        }
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected string)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                KeoDuration *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isString()) {
        KeoDuration duration =
            KeoDuration::parse((*json)[elementName].asString());
        if (duration.isValid()) {
          *target = duration;
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (invalid format)");
        }
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected string)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

bool KeoJsonTransformation::get(KeoJsonValue *json,
                                const std::string &elementName,
                                AbsoluteOrRelativeTime *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isString()) {
        AbsoluteOrRelativeTime time;
        KeoDuration duration;
        KeoDateTime dateTime;
        try {
          if (KeoJsonTransformation::get(json, elementName, &duration)) {
            time.setDuration(duration);
            *target = time;
            return true;
          }
        } catch (const DatagramParserException &e) {
          // Duration could not be parsed -> try to parse it as DateTime
        }

        if (KeoJsonTransformation::get(json, elementName, &dateTime)) {
          time.setDateTime(dateTime);
          *target = time;
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (element not found)");
        }
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected string)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

template <typename T>
bool KeoJsonTransformation::getUInt(KeoJsonValue *json,
                                    const std::string &elementName, T *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isUInt64()) {
        uint64_t numberFromJson = (*json)[elementName].asUInt64();
        T numberCasted = static_cast<T>((*json)[elementName].asUInt64());
        if (numberFromJson == static_cast<uint64_t>(numberCasted)) {
          *target = numberCasted;
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (out of range)");
        }
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected uint)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

template <typename T>
bool KeoJsonTransformation::getInt(KeoJsonValue *json,
                                   const std::string &elementName, T *target) {
  if (json->isObject()) {
    if (json->isMember(elementName)) {
      if ((*json)[elementName].isInt64()) {
        int64_t numberFromJson = (*json)[elementName].asInt64();
        T numberCasted = static_cast<T>((*json)[elementName].asInt64());
        if (numberFromJson == static_cast<int64_t>(numberCasted)) {
          *target = numberCasted;
          return true;
        } else {
          throw DatagramParserException("Could not parse element <" +
                                        elementName + "> (out of range)");
        }
      } else {
        throw DatagramParserException("Could not parse element <" +
                                      elementName + "> (expected int)");
      }
    } else {
      return false;
    }
  } else {
    throw DatagramParserException("Could not parse element <" + elementName +
                                  "> (expected object)");
  }
}

} // end namespace keo_datagram