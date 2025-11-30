#pragma once

#include "Models/TargetDescriptor.hpp"
#include <Models/Target.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {

struct ToolchainExecutableLinkInterface : ToolchainBasicCommandInterface {
  virtual String executable_link(const TargetDescriptor &target) = 0;
  virtual ToolchainBasicCommandInterface::promise_type
  executable_link_async(const TargetDescriptor &target) = 0;
};
} // namespace Models