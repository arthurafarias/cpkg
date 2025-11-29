#pragma once

#include "Models/BasicProjectDescriptor.hpp"
#include "Models/ToolchainArchiveLinkInterface.hpp"
#include "Models/ToolchainExecutableLinkInterface.hpp"
#include "Models/ToolchainSharedObjectLinkInterface.hpp"
#include <Models/ToolchainObjectBuildInterface.hpp>

namespace Models {

struct ToolchainBuildInterface : ToolchainObjectBuildInterface,
                                 ToolchainExecutableLinkInterface,
                                 ToolchainSharedObjectLinkInterface,
                                 ToolchainArchiveLinkInterface {
  virtual int build(const BasicProjectDescriptor &project) = 0;
  virtual int build(const BasicTargetDescriptor &target) = 0;
};
} // namespace Models