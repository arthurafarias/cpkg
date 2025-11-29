#pragma once

#include "Models/BasicToolchainDescriptor.hpp"
#include <Core/Containers/String.hpp>

using namespace Core::Containers;
using namespace Models;

namespace Controllers {
class ToolchainDescriptorFactoryInterface {
public:
  static ToolchainDescriptorFactoryInterface instance() {
    return ToolchainDescriptorFactoryInterface();
  }

  ToolchainDescriptorFactoryInterface
  name(const Core::Containers::String &name) {
    toolchain.name = name;
    return *this;
  }

  ToolchainDescriptorFactoryInterface
  version(const Core::Containers::String &version) {
    toolchain.version = version;
    return *this;
  }

  ToolchainDescriptorFactoryInterface
  language(const Core::Containers::String &language) {
    toolchain.language = language;
    return *this;
  }

  ToolchainDescriptorFactoryInterface
  install_prefix(const Core::Containers::String &install_prefix) {
    toolchain.install_prefix = install_prefix;
    return *this;
  }

  ToolchainDescriptorFactoryInterface include_directories(
      const Core::Containers::Collection<Core::Containers::String>
          &include_directories) {
    toolchain.include_directories.append_range(include_directories);
    return *this;
  }

  ToolchainDescriptorFactoryInterface
  compiler_executable(const Core::Containers::String &compiler_executable) {
    toolchain.compiler_executable = compiler_executable;
    return *this;
  }

  ToolchainDescriptorFactoryInterface
  compiler_options(const Core::Containers::Collection<Core::Containers::String>
                       &compiler_options) {
    toolchain.compiler_options.append_range(compiler_options);
    return *this;
  }

  ToolchainDescriptorFactoryInterface
  linker_executable(const Core::Containers::String &linker_executable) {
    toolchain.linker_executable = linker_executable;
    return *this;
  }

  ToolchainDescriptorFactoryInterface
  linker_options(const Core::Containers::Collection<Core::Containers::String>
                     &linker_options) {
    toolchain.linker_options.append_range(linker_options);
    return *this;
  }

  ToolchainDescriptorFactoryInterface
  link_directories(const Core::Containers::Collection<Core::Containers::String>
                       &link_directories) {
    toolchain.link_directories.append_range(link_directories);
    return *this;
  }

  BasicToolchainDescriptor build() { return toolchain; }

private:
  BasicToolchainDescriptor toolchain;
};
} // namespace Controllers