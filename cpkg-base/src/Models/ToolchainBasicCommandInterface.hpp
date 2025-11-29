#pragma once

#include <Core/Containers/String.hpp>

#include <future>
#include <memory>
#include <tuple>

using namespace Core::Containers;

namespace Models {
struct ToolchainBasicCommandInterface {
  using promise_type = std::shared_ptr<std::promise<
      std::tuple<int, Core::Containers::String, Core::Containers::String>>>;
};
} // namespace Models
