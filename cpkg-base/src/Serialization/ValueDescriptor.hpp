#pragma once

#include "Core/Containers/Collection.hpp"
#include <string>

namespace Serialization {

struct AbstractTag {};

enum class MultipartElementType { Object, Array };

struct MultipartElementTag : AbstractTag {

  MultipartElementTag(const std::string &name, const MultipartElementType &type, bool start = true)
      : name(name), type(type), start(start) {}

  std::string name;
  MultipartElementType type;
  bool start;
};

template <typename ValueType> struct ValueTag : AbstractTag {
  ValueTag(const ValueType &value) : value(value) {}
  const ValueType &value;
};

template <typename ValueType> struct KeyValueTag : AbstractTag {
  KeyValueTag(const std::string &name, const ValueType &value)
      : name(name), value(value) {}
  std::string name;
  const ValueType &value;
};
} // namespace Serialization