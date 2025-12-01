#pragma once

#include <Models/Target.hpp>
#include <Models/ToolchainBasicCommandInterface.hpp>

namespace Models {
struct ToolchainArchiveLinkInterface : ToolchainBasicCommandInterface {
  virtual BuildOutputResult archive_link(const TargetDescriptor &target, bool dry) = 0;
};
} // namespace Models