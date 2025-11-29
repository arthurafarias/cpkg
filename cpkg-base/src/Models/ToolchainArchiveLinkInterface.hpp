#pragma once

#include <Models/TargetDescriptor.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {
struct ToolchainArchiveLinkInterface : ToolchainBasicCommandInterface {
  virtual String archive_link(const BasicTargetDescriptor &target) = 0;
  virtual ToolchainBasicCommandInterface::promise_type
  archive_link_async(const BasicTargetDescriptor &target) = 0;
};
} // namespace Models