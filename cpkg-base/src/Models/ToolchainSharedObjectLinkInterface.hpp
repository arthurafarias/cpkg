#pragma once

#include <Models/Target.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {
struct ToolchainSharedObjectLinkInterface : ToolchainBasicCommandInterface {
  virtual String shared_object_link(const TargetDescriptor &target) = 0;
  virtual ToolchainBasicCommandInterface::promise_type
  shared_object_link_async(const TargetDescriptor &target) = 0;
};
} // namespace Models