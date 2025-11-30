#pragma once

#include "Models/TargetDescriptor.hpp"
#include <Models/Target.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {
struct ToolchainObjectBuildInterface : ToolchainBasicCommandInterface {
  virtual String object_build(const String& source,
                                   const TargetDescriptor &target) = 0;

  virtual ToolchainBasicCommandInterface::promise_type
  object_build_async(const String& source, const TargetDescriptor &target) = 0;
};
} // namespace Models