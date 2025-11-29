#pragma once

#include "Controllers/Project.hpp"
#include "Core/Containers/Collection.hpp"
#include "Core/Exceptions/RuntimeException.hpp"
#include "Models/BasicProjectDescriptor.hpp"
#include <Core/Containers/String.hpp>

// configs
#ifndef CPKG_BUILD_HEADERS_PATH
#define CPKG_BUILD_HEADERS_PATH "./"
#endif

#ifndef CPKG_BUILD_INSTALL_HEADERS_PATH
#define CPKG_BUILD_INSTALL_HEADERS_PATH "/usr/share/cpkg-build/private-headers/"
#endif

#ifndef CPKG_BASE_HEADERS_PATH
#define CPKG_BASE_HEADERS_PATH "./"
#endif

#ifndef CPKG_BASE_INSTALL_HEADERS_PATH
#define CPKG_BASE_INSTALL_HEADERS_PATH "/usr/share/cpkg-base/private-headers/"
#endif

namespace Controllers {

struct ProjectManager {

  static inline int
  build_manifest(const Core::Containers::String &project_path,
                 Core::Containers::Collection<Core::Containers::String>
                     extra_toolchain_search_paths) {
    return 0;
  }

  static inline Models::BasicProjectDescriptor
  load_from_manifest(const Core::Containers::String &manifest_path) {
    typedef ProjectDescriptor *(*getter_type)();

    void *handle = dlopen("./project-manifest.so", RTLD_LAZY | RTLD_DEEPBIND);

    if (handle == nullptr) {
      throw Core::Exceptions::RuntimeException(
          "Couldn't load manifest at path {}: not found!", manifest_path);
    }

    auto get_project =
        reinterpret_cast<getter_type>(dlsym(handle, "get_project"));

    if (get_project == nullptr) {
      throw Core::Exceptions::RuntimeException(
          "Couldn't load manifest at path {}: malformed get_project method",
          manifest_path);
    }

    auto _retval = *get_project();

    auto retval = std::make_shared<ProjectDescriptor>(_retval);

    dlclose(handle);

    return *retval;
  }

  static inline int clean(const Core::Containers::String &project_path,
                          Core::Containers::Collection<Core::Containers::String>
                              extra_toolchain_search_paths) {

    // objects
    for (auto source : ManifestPackage.sources) {
      std::filesystem::remove_all(std::filesystem::path(project_path.c_str())
                                      .append(source.std_string())
                                      .append(".o"));
    }

    // generate packages
    std::filesystem::remove_all(
        std::filesystem::path(project_path.c_str()).append("package.cpp.o"));

    std::filesystem::remove_all(std::filesystem::path(project_path.c_str())
                                    .append("package.loader.cpp.o"));

    std::filesystem::remove_all(std::filesystem::path(project_path.c_str())
                                    .append("package.loader.cpp"));

    return 0;
  }

  Core::Containers::Collection<Models::BasicProjectDescriptor> projects;

private:
  static inline Models::BasicTargetDescriptor ManifestPackage = {
      .name = "project-manifest",
      .type = "shared-library",
      .dependencies = {"cpkg-base"},
      .include_directories = {CPKG_BUILD_INSTALL_HEADERS_PATH,
                              CPKG_BUILD_HEADERS_PATH, CPKG_BASE_HEADERS_PATH,
                              CPKG_BASE_INSTALL_HEADERS_PATH},
      .sources = {"package.cpp", "package.loader.cpp"},
      .options = {"-std=c++23", "-Wall", "-Werror", "-pedantic"}};

  static inline const std::string BasicProjectLoaderSource = R"(
    #include <Models/BasicProjectDescriptor.hpp>
    using namespace Models;
    extern BasicProjectDescriptor project;
    // should be a weak reference that can be overriten by a custom get_project // more versatile but unsafe.
    extern "C" const BasicProjectDescriptor* get_project()  { return &project; }
  )";
};
} // namespace Controllers