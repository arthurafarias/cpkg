#pragma once

#include "Models/BasicProjectDescriptor.hpp"
#include "Models/BasicTargetDescriptor.hpp"

namespace Models {
class ToolchainInstallInterface {
public:
  virtual int install(const Models::BasicProjectDescriptor &target) = 0;
  virtual int install(const Models::BasicTargetDescriptor &target) = 0;
};
} // namespace Models