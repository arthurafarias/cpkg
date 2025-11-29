#pragma once

#include "Models/TargetFactoryInterfaceDescriptor.hpp"
#include <Models/BasicTargetDescriptor.hpp>

namespace Models {
struct TargetDescriptor
    : public BasicTargetDescriptor,
      public TargetDescriptorFactoryInterface<TargetDescriptor> {
  using BasicTargetDescriptor::BasicTargetDescriptor;
};
} // namespace Models