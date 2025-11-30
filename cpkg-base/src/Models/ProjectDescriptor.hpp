#pragma once

#include <Models/ToolchainDescriptor.hpp>
#include <Models/TargetDescriptor.hpp>

#include <deque>

namespace Models {
struct ProjectDescriptor {
  std::deque<ToolchainDescriptor> toolchains;
  std::deque<TargetDescriptor> targets;
};
} // namespace Models