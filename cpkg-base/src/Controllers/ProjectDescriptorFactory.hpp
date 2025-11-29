#pragma once

  namespace Controllers
  {
    struct ProjectDescriptorFactory {
    ProjectDescriptorFactory() {}
    toolchain_append(const BasicToolchainDescriptor& toolchain);
    target_append(const BasicTargetDescriptor& toolchain);
  };
  }