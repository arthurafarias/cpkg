#pragma once

#include "Models/BasicTargetDescriptor.hpp"
#include <Models/TargetDescriptor.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {

struct ToolchainExecutableLinkInterface : ToolchainBasicCommandInterface {
  virtual String executable_link(const BasicTargetDescriptor &target) = 0;
  virtual ToolchainBasicCommandInterface::promise_type
  executable_link_async(const BasicTargetDescriptor &target) = 0;
};
} // namespace Models