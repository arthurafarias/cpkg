#pragma once

#include <Models/BasicToolchainDescriptor.hpp>
#include <Models/BasicTargetDescriptor.hpp>

#include <deque>

namespace Models {
struct BasicProjectDescriptor {
  std::deque<BasicToolchainDescriptor> toolchains;
  std::deque<BasicTargetDescriptor> targets;
};
} // namespace Models