#pragma once

#include "Models/BasicTargetDescriptor.hpp"
#include <Models/TargetDescriptor.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {
struct ToolchainObjectBuildInterface : ToolchainBasicCommandInterface {
  virtual String object_build(const String& source,
                                   const BasicTargetDescriptor &target) = 0;

  virtual ToolchainBasicCommandInterface::promise_type
  object_build_async(const String& source, const BasicTargetDescriptor &target) = 0;
};
} // namespace Models