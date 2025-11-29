#pragma once

#include "Models/BasicTargetDescriptor.hpp"
#include <Core/Containers/String.hpp>
using namespace Core::Containers;
namespace Models {

template <typename DerivedType> class TargetDescriptorFactoryInterface {
public:
  constexpr DerivedType &name(const Core::Containers::String &name) {
    this->target.name = name;
    return *this;
  }
  constexpr DerivedType &version(const Core::Containers::String &version) {
    this->target.version = version;
    return *this;
  }

  constexpr DerivedType &language(const Core::Containers::String &language) {
    this->target.language = language;
    return *this;
  }
  constexpr DerivedType &type(const Core::Containers::String &type) {
    this->target.type = type;
    return *this;
  }
  constexpr DerivedType &dependencies(const auto &dependencies) {
    this->target.dependencies.append_range(dependencies);
    return *this;
  }
  constexpr DerivedType &options(const auto &options) {
    this->target.options.append_range(options);
    return *this;
  }

  constexpr DerivedType &sources(const auto &sources) {
    this->target.sources.append_range(sources);
    return *this;
  }

  /** this will be removed! not necessary if dependency is correctly configured
   * under the build system */
  constexpr DerivedType &
  link_libraries(const auto &link_libraries) {
    this->target.link_libraries.append_range(link_libraries);
    return *this;
  }
  constexpr DerivedType &
  link_directories(const auto &link_directories) {
    this->target.link_directories.append_range(link_directories);
    return *this;
  }
  constexpr const BasicTargetDescriptor &create() { return target; }

private:
  BasicTargetDescriptor target;
};
} // namespace Models