#pragma once

#include <Models/Target.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {
struct ToolchainArchiveLinkInterface : ToolchainBasicCommandInterface {
  virtual String archive_link(const TargetDescriptor &target) = 0;
  virtual ToolchainBasicCommandInterface::promise_type
  archive_link_async(const TargetDescriptor &target) = 0;
};
} // namespace Models