#pragma once

#include "Models/TargetFactoryInterfaceDescriptor.hpp"
#include <Models/BasicTargetDescriptor.hpp>

namespace Models {
struct TargetDescriptor : public TargetDescriptorInterface<TargetDescriptor> {
  using TargetDescriptorInterface<TargetDescriptor>::TargetDescriptorInterface;
};
} // namespace Models