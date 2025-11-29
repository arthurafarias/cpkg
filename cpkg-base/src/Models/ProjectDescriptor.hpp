#pragma once

#include <Models/BasicProjectDescriptor.hpp>
#include <Models/BasicProjectDescriptorFactoryInterface.hpp>

namespace Models {
class ProjectDescriptor : public BasicProjectDescriptor {
public:
  constexpr auto &add(const BasicTargetDescriptor &target) {
    targets.push_back(target);
    return *this;
  }

  constexpr auto &add(const BasicToolchainDescriptor &toolchain) {
    toolchains.push_back(toolchain);
    return *this;
  }
};
} // namespace Models