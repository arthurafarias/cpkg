#pragma once

#include <Models/Target.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {
struct ToolchainSharedObjectLinkInterface : ToolchainBasicCommandInterface {
  virtual BuildOutputResult shared_object_link(const TargetDescriptor &target, bool dry) = 0;
};
} // namespace Models