#pragma once

#include "Core/Logging/LoggerManager.hpp"
#include "Models/ToolchainDescriptorFactoryInterface.hpp"
#include "Models/ToolchainInterface.hpp"
#include "Utils/Unix/ShellManager.hpp"
#include <Models/BasicProjectDescriptor.hpp>
#include <Models/BasicToolchainDescriptor.hpp>

#include <Core/Containers/Collection.hpp>
#include <Core/Containers/String.hpp>
#include <Core/Containers/Variant.hpp>
#include <future>
#include <memory>

using namespace Core::Containers;

namespace Models {

class Toolchain : public ToolchainDescriptorFactoryInterface<Toolchain>,
                  public ToolchainInterface {

public:
  using ToolchainInterface::ToolchainInterface;
  using ToolchainDescriptorFactoryInterface<
      Toolchain>::ToolchainDescriptorFactoryInterface;

  virtual String object_build(const String &source,
                              const BasicTargetDescriptor &target) override {
    Core::Logging::LoggerManager::info("building {}: started", source.c_str());

    Collection<String> command;

    command.push_back(compiler_executable);

    command.append_range(target.options);

    command.push_back("-fPIC");

    auto include_directories_arguments =
        target.include_directories.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto include_directory_argument : include_directories_arguments) {
      command.append_range(include_directory_argument);
    }

    auto link_directories_arguments =
        target.link_directories.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto link_directory_argument : link_directories_arguments) {
      command.append_range(link_directory_argument);
    }

    auto link_libraries_arguments =
        target.link_libraries.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto link_library_argument : link_libraries_arguments) {
      command.append_range(link_library_argument);
    }

    command.append_range(Core::Containers::Collection<Core::Containers::String>{
        source_specifier_prefix, source});

    command.append_range(
        Collection<String>({object_specifier_prefix, source + ".o"}));

    auto command_line = String::join(command, " ");

    Core::Logging::LoggerManager::debug("Calling: {}", command_line.c_str());
    auto [result_code, out, err] =
        Utils::Unix::ShellManager::exec(command_line);
    Core::Logging::LoggerManager::info("building {}: ended", source.c_str());

    return out;
  }

  virtual ToolchainBasicCommandInterface::promise_type
  object_build_async(const String &source,
                     const BasicTargetDescriptor &target) override {
    return {};
  }

  virtual String executable_link(const BasicTargetDescriptor &target) override {

    Collection<String> command;

    command.push_back(compiler_executable);

    command.append_range(target.options);

    command.push_back("-fPIE");

    auto include_directories_arguments =
        target.include_directories.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto include_directory_argument : include_directories_arguments) {
      command.append_range(include_directory_argument);
    }

    auto link_directories_arguments =
        target.link_directories.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto link_directory_argument : link_directories_arguments) {
      command.append_range(link_directory_argument);
    }

    auto link_libraries_arguments =
        target.link_libraries.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto link_library_argument : link_libraries_arguments) {
      command.append_range(link_library_argument);
    }

    command.append_range(Collection<String>{"-o", target.name});

    for (auto source : target.sources) {
      command.push_back(source + ".o");
    }

    auto command_line = String::join(command, " ");

    Core::Logging::LoggerManager::debug("Calling: {}", command_line.c_str());
    auto [result_code, out, err] =
        Utils::Unix::ShellManager::exec(command_line);
    Core::Logging::LoggerManager::info("building: ended");

    return out;
  }

  virtual ToolchainBasicCommandInterface::promise_type
  executable_link_async(const BasicTargetDescriptor &target) override {
    return ToolchainBasicCommandInterface::promise_type();
  }

  virtual String
  shared_object_link(const BasicTargetDescriptor &target) override {

    Collection<String> command;

    command.push_back(compiler_executable);

    command.push_back("-fPIC");
    command.push_back("-shared");

    command.append_range(this->linker_options);

    command.append_range(target.options);

    auto include_directories_arguments =
        target.include_directories.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto include_directory_argument : include_directories_arguments) {
      command.append_range(include_directory_argument);
    }

    auto link_directories_arguments =
        target.link_directories.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto link_directory_argument : link_directories_arguments) {
      command.append_range(link_directory_argument);
    }

    auto link_libraries_arguments =
        target.link_libraries.transform<Collection<String>>(
            [this](const auto &el) {
              return Collection<String>{include_directory_prefix, el};
            });

    for (auto link_library_argument : link_libraries_arguments) {
      command.append_range(link_library_argument);
    }

    command.append_range(Collection<String>{"-o", target.name + ".so"});

    for (auto source : target.sources) {
      command.push_back(source + ".o");
    }

    auto command_line = String::join(command, " ");

    Core::Logging::LoggerManager::debug("Calling: {}", command_line.c_str());
    auto [result_code, out, err] =
        Utils::Unix::ShellManager::exec(command_line);
    Core::Logging::LoggerManager::info("building: ended");

    return out;
  }

  virtual ToolchainBasicCommandInterface::promise_type
  shared_object_link_async(const BasicTargetDescriptor &target) override {
    return ToolchainBasicCommandInterface::promise_type();
  }

  virtual String archive_link(const BasicTargetDescriptor &target) override {
    return "";
  }

  virtual ToolchainBasicCommandInterface::promise_type
  archive_link_async(const BasicTargetDescriptor &target) override {
    return ToolchainBasicCommandInterface::promise_type();
  }

  virtual int build(const BasicProjectDescriptor &project) override {
    for (auto package : project.targets) {
      if (build(package) != 0) {
        return -1;
      }
    }

    return 0;
  }

  virtual int build(const BasicTargetDescriptor &package) override {

    using promise_type =
        std::shared_ptr<std::promise<std::tuple<int, String, String>>>;

    std::deque<std::tuple<String, promise_type>> results;

    for (auto source : package.sources) {
      auto result = object_build(source, package);
      Core::Logging::LoggerManager::debug("{}", result);
    }

    if (package.type == "executable") {
      auto result = executable_link(package);
      Core::Logging::LoggerManager::debug("{}", result);
      return 0;
    }

    if (package.type == "shared-library") {
      auto result = shared_object_link(package);
      Core::Logging::LoggerManager::debug("{}", result);
      return 0;
    }

    if (package.type == "static-library") {
      auto result = archive_link(package);
      Core::Logging::LoggerManager::debug("{}", result);
      return 0;
    }
    return -1;
  }

  virtual int install(const Models::BasicProjectDescriptor &target) override {
    return 0;
  }

  virtual int install(const Models::BasicTargetDescriptor &target) override {
    return 0;
  }

  // virtual int install(const BasicProjectDescriptor &project) override {

  //   // for (auto target : project.targets) {

  //   //   if (std::get<String>((target).type) ==
  //   //       "shared-library") {

  //   //     String name =
  //   std::get<String>((target).name);

  //   //     String prefix =
  //   //     std::get<String>(install_prefix);
  //   //     // Install the SO
  //   //     std::filesystem::copy(std::filesystem::path(name).append(".so"),
  //   // std::filesystem::path(prefix).append("/lib"));

  //   //     using directory_iterator =
  //   //         std::filesystem::recursive_directory_iterator;

  //   //     for (auto _include_directory : (target).include_directories) {

  //   //       String include_directory =
  //   //           std::get<String>(_include_directory);

  //   //       /// RATIONALE: (08:50 26/11/2025)
  //   //       /// failed to install, cannot install files outside project
  //   //       /// directory! this restriction is made to avoid confusion with
  //   //       /// include_directories you can set your includes based on how
  //   you
  //   //       do
  //   //       /// stuff, we consider headers in include directories within
  //   //       project
  //   //       /// as installable to avoid unnecessary customizations that
  //   other
  //   //       /// build systems do!

  //   //       // if
  //   (!include_directory.starts_with(target.project_directory()))
  //   //       {
  //   //       //   /// TODO: warn ignoring include
  //   //       //   continue;
  //   //       // }

  //   //       for (auto _file : directory_iterator(include_directory)) {

  //   //         auto file = _file;

  //   //         /// RATIONALE: (08:55 26/11/2025)
  //   //         /// uniform prefix is easy to form and search, when
  //   //         /// dealing with dependencies, dont' look for headers other
  //   than
  //   //         /// <prefix>/include/<pn>
  //   //         if (file.path().filename().string().ends_with("h")) {

  //   //           String name =
  //   //               std::get<String>((target).name);
  //   //           String prefix =
  //   //               std::get<String>(install_prefix);

  //   //           std::filesystem::copy(file, std::filesystem::path(prefix)
  //   //                                           .append("/include")
  //   //                                           .append(name));
  //   //         }

  //   //         if (file.path().filename().string().ends_with("hpp")) {

  //   //           String name =
  //   //               std::get<String>((target).name);
  //   //           String prefix =
  //   //               std::get<String>(install_prefix);

  //   //           std::filesystem::copy(file, std::filesystem::path(prefix)
  //   //                                           .append("/include")
  //   //                                           .append(name));
  //   //         }
  //   //       }
  //   //     }
  //   //   }
  //   // }
  //   return 0;
  // }

  // int uninstall(const BasicProjectDescriptor &project) override { return 0; }
};

} // namespace Models