#pragma once

#include "Core/Containers/Collection.hpp"
#include "Core/Containers/Variant.hpp"
#include <string>

using namespace Core::Containers;

namespace Serialization {
template <typename... ValueTypes>
struct KeyValueMapDescriptor : Collection<Variant<ValueTypes...>> {};
} // namespace Serialization